/*
 * ct_app.c
 */

#include "ct_app.h"
#include "ct_nextion.h"
#include "ct_storage.h"
#include "ct_usb.h"
#include "ct_protocol.h"
#include "main.h"

#include <stdio.h>
#include <string.h>

/* Words of the messages, UTF-8 as the HMI project expects */
#define CT_APP_TEXT_OPEN    "Обрыв"
#define CT_APP_TEXT_SHORT   "Замыкание"
#define CT_APP_TEXT_NO_ERR  "OK!"
#define CT_APP_TEXT_ERRORS  "Ошибок: %u"
#define CT_APP_TEXT_NO_PKG  "Нет кабелей"
#define CT_APP_TEXT_MORE    "ещё"
#define CT_APP_TEXT_READY   "TEST"

static uint8_t      ctAppSlot = CT_APP_NO_SLOT;
static uint8_t      ctAppErrorIndex = 0xFF;
static uint8_t      ctAppTested = 0;
static CtTestResult ctAppResult;
static int32_t      ctAppTestId = -1;    /* component id of errorList, the TEST button */
static int32_t      ctAppCableId = -1;   /* component id of cableName */
static char         ctAppList[CT_NX_CMD_SIZE - 32];  /* text of a ComboBox list */

uint8_t CtApp_GetSlot(void)
{
	return ctAppSlot;
}

const CtPkgHeader* CtApp_GetPackage(void)
{
	return (ctAppSlot == CT_APP_NO_SLOT) ? NULL : CtStorage_Get(ctAppSlot);
}

const CtTestResult* CtApp_GetResult(void)
{
	return ctAppTested ? &ctAppResult : NULL;
}

/* Copies a text of the package into a Nextion string: the quote and the end of
   the line would break the instruction */
static void CtApp_SafeText(char* dst, uint16_t size, const char* src, uint16_t limit)
{
	uint16_t n = 0;
	if (size == 0) return;
	if (limit > size - 1) limit = (uint16_t)(size - 1);
	while (src[n] && n < limit) {
		char c = src[n];
		if (c == '"') c = '\'';
		else if (c == '\r' || c == '\n' || c == 0x7F) c = ' ';
		dst[n] = c;
		++n;
	}
	/* do not cut a UTF-8 character in the middle */
	while (n > 0 && (dst[n - 1] & 0xC0) == 0x80) --n;
	dst[n] = 0;
}

static const char* CtApp_PinLabel(const CtPkgHeader* pkg, uint8_t pin)
{
	if (pkg == NULL || pin < 1 || pin > pkg->pinCount) return "?";
	return CT_PKG_PINS(pkg)[pin - 1].label;
}

/* One line of the error list: "Обрыв: A:1 - B:2".
   labelLimit cuts the labels of the pins: the list of the ComboBox must fit
   into one instruction, while the selected error is shown in full */
static int CtApp_ErrorLine(char* dst, uint16_t size, const CtTestError* error, uint16_t labelLimit)
{
	const CtPkgHeader* pkg = CtApp_GetPackage();
	char labelA[CT_PKG_LABEL_SIZE];
	char labelB[CT_PKG_LABEL_SIZE];
	CtApp_SafeText(labelA, sizeof(labelA), CtApp_PinLabel(pkg, error->pinA), labelLimit);
	CtApp_SafeText(labelB, sizeof(labelB), CtApp_PinLabel(pkg, error->pinB), labelLimit);
	return snprintf(dst, size, "%s: %s - %s",
	                error->type == CT_ERROR_OPEN ? CT_APP_TEXT_OPEN : CT_APP_TEXT_SHORT,
	                labelA, labelB);
}

/* The items of a ComboBox are separated by \r inside the string */
static void CtApp_SendErrorList(void)
{
	const CtPkgHeader* pkg = CtApp_GetPackage();
	ctAppList[0] = 0;

	if (pkg == NULL) {
		CtNextion_Send("errorList.path=\"\"");
		CtNextion_Send("errorList.txt=\"%s\"", CT_APP_TEXT_NO_PKG);
		CtNextion_Send("errorList.bco=%u", CT_APP_COLOR_GOOD);
		return;
	}
	if (!ctAppTested) {
		CtNextion_Send("errorList.path=\"\"");
		CtNextion_Send("errorList.txt=\"%s\"", CT_APP_TEXT_READY);
		CtNextion_Send("errorList.bco=%u", CT_APP_COLOR_GOOD);
		return;
	}
	if (ctAppResult.errorCount == 0) {
		CtNextion_Send("errorList.path=\"\"");
		CtNextion_Send("errorList.txt=\"%s\"", CT_APP_TEXT_NO_ERR);
		CtNextion_Send("errorList.bco=%u", CT_APP_COLOR_GOOD);
		return;
	}

	uint16_t used = 0;
	uint8_t count = ctAppResult.errorCount;
	if (count > CT_APP_MAX_LIST) count = CT_APP_MAX_LIST;
	for (uint8_t i = 0; i < count; ++i) {
		char line[CT_APP_LINE_SIZE];
		CtApp_ErrorLine(line, sizeof(line), &ctAppResult.errors[i], CT_APP_LIST_LABEL);
		int written = snprintf(ctAppList + used, sizeof(ctAppList) - used,
		                       "%s%s", used ? "\\r" : "", line);
		if (written < 0 || (uint16_t)written >= sizeof(ctAppList) - used) {
			ctAppList[used] = 0;            /* no room for one more line */
			break;
		}
		used = (uint16_t)(used + written);
	}
	if (ctAppResult.errorCount > count) {
		snprintf(ctAppList + used, sizeof(ctAppList) - used, "\\r%s %u",
		         CT_APP_TEXT_MORE, ctAppResult.errorCount - count);
	}
	CtNextion_Send("errorList.path=\"%s\"", ctAppList);
	CtNextion_Send("errorList.txt=\"" CT_APP_TEXT_ERRORS "\"", ctAppResult.errorCount);
	CtNextion_Send("errorList.bco=%u", CT_APP_COLOR_ERROR);
}

void CtApp_ShowError(uint8_t index)
{
	const CtPkgHeader* pkg = CtApp_GetPackage();
	if (pkg == NULL || !ctAppTested || index >= ctAppResult.errorCount) {
		ctAppErrorIndex = 0xFF;
		CtNextion_Send("errFlash.en=0");
		CtNextion_Send("errPic1.aph=0");
		CtNextion_Send("errPic2.aph=0");
		return;
	}
	ctAppErrorIndex = index;
	const CtTestError* error = &ctAppResult.errors[index];
	const CtPkgPin* pins = CT_PKG_PINS(pkg);
	const CtPkgPin* a = &pins[error->pinA - 1];
	const CtPkgPin* b = &pins[error->pinB - 1];

	CtNextion_Send("errPic1.x=%d", CT_APP_IMAGE_X + a->x - CT_APP_ICON_CX / 2);
	CtNextion_Send("errPic1.y=%d", CT_APP_IMAGE_Y + a->y - CT_APP_ICON_CY / 2);
	CtNextion_Send("errPic2.x=%d", CT_APP_IMAGE_X + b->x - CT_APP_ICON_CX / 2);
	CtNextion_Send("errPic2.y=%d", CT_APP_IMAGE_Y + b->y - CT_APP_ICON_CY / 2);
	CtNextion_Send("errPic1.aph=127");
	CtNextion_Send("errPic2.aph=127");
	CtNextion_Send("errFlash.en=1");
}

/* The line of cableName is the slot number: the HMI builds the path of the
   picture sd0/c<cableName.val>.jpg itself. The cables are kept in the slots
   0..N-1 without gaps (see CtApp_EraseSlot), so the list is just all of them. */
void CtApp_RefreshCableList(void)
{
	uint16_t used = 0;
	ctAppList[0] = 0;
	for (uint8_t slot = 0; slot < CtStorage_GetSlotCount(); ++slot) {
		const CtPkgHeader* pkg = CtStorage_Get(slot);
		if (pkg == NULL) break;
		char name[CT_PKG_NAME_SIZE];
		CtApp_SafeText(name, sizeof(name), pkg->name, CT_APP_NAME_LABEL);
		int written = snprintf(ctAppList + used, sizeof(ctAppList) - used,
		                       "%s%s", slot ? "\\r" : "", name);
		if (written < 0 || (uint16_t)written >= sizeof(ctAppList) - used) {
			ctAppList[used] = 0;
			break;
		}
		used = (uint16_t)(used + written);
	}
	CtNextion_Send("cableName.path=\"%s\"", ctAppList);
}

/* The package has moved to a lower slot: its picture on the microSD follows */
static void CtApp_PictureMoved(uint8_t from, uint8_t to)
{
	CtNextion_Send("delfile \"sd0/c%u.jpg\"", to);
	CtNextion_Send("refile \"sd0/c%u.jpg\",\"sd0/c%u.jpg\"", from, to);
}

void CtApp_EraseSlot(uint8_t slot)
{
	if (!CtStorage_Erase(slot)) return;
	CtNextion_Send("delfile \"sd0/c%u.jpg\"", slot);
	CtStorage_Compact(CtApp_PictureMoved);
	/* the selected cable stays selected, it has moved one slot down when it
	   was above the erased one; instead of the erased one the first is taken */
	uint8_t target = 0;
	if (ctAppSlot != CT_APP_NO_SLOT && ctAppSlot != slot) {
		target = (ctAppSlot > slot) ? (uint8_t)(ctAppSlot - 1) : ctAppSlot;
	}
	ctAppSlot = CT_APP_NO_SLOT;
	if (!CtApp_SelectSlot(target)) CtApp_Refresh();
}

void CtApp_Refresh(void)
{
	CtApp_RefreshCableList();
	const CtPkgHeader* pkg = CtApp_GetPackage();
	if (pkg == NULL) {
		CtApp_ShowError(0xFF);
		CtApp_SendErrorList();
		return;
	}
	CtNextion_Send("cableName.val=%u", ctAppSlot);
	CtNextion_Send("cablePic.path=\"sd0/c%u.jpg\"", ctAppSlot);
	CtApp_ShowError(ctAppErrorIndex);
	CtApp_SendErrorList();
}

int CtApp_SelectSlot(uint8_t slot)
{
	if (CtStorage_Get(slot) == NULL) return 0;
	ctAppSlot = slot;
	ctAppTested = 0;
	ctAppErrorIndex = 0xFF;
	CtApp_Refresh();
	return 1;
}

uint8_t CtApp_RunTest(void)
{
	const CtPkgHeader* pkg = CtApp_GetPackage();
	if (pkg == NULL) {
		ctAppTested = 0;
		CtApp_SendErrorList();
		return 0;
	}
	CtTest_Run(pkg, &ctAppResult);
	ctAppTested = 1;
#if DEBUG
	Log("Test of \"%s\": %u error(s)%s\n", pkg->name, ctAppResult.errorCount,
	    ctAppResult.overflow ? " (too many)" : "");
	for (uint8_t i = 0; i < ctAppResult.errorCount; ++i) {
		const CtTestError* e = &ctAppResult.errors[i];
		Log("  %s D%u - D%u (%s - %s)\n", e->type == CT_ERROR_OPEN ? "open " : "short",
		    e->pinA, e->pinB, CtApp_PinLabel(pkg, e->pinA), CtApp_PinLabel(pkg, e->pinB));
	}
#endif
	CtApp_SendErrorList();
	CtApp_ShowError(ctAppResult.errorCount ? 0 : 0xFF);
	return ctAppResult.errorCount;
}

/* "Send Component ID" of the HMI: the press of errorList (the TEST button)
   runs the test, the release of a ComboBox means an item may be chosen */
static void CtApp_OnTouch(const CtNxEvent* event)
{
	int pressed = (event->number != 0);
	Log("Display: %s of page %u, component %u\n", pressed ? "press" : "release",
	    event->page, event->value);
	int32_t value;
	if (event->value == ctAppTestId) {
		if (pressed) {
			CtApp_RunTest();
		} else if (CtNextion_GetNumber("errorList.val", &value) && value >= 0) {
			CtApp_ShowError((uint8_t)value);
		}
	} else if (event->value == ctAppCableId && !pressed) {
		if (CtNextion_GetNumber("cableName.val", &value) && value >= 0 &&
		    value != ctAppSlot && value < CT_APP_NO_SLOT) {
			CtApp_SelectSlot((uint8_t)value);
		}
	}
}

static void CtApp_OnEvent(const CtNxEvent* event)
{
	switch (event->type) {
		case CT_NX_EVENT_TEST:
			CtApp_RunTest();
			break;

		case CT_NX_EVENT_ERROR_SELECT:
			CtApp_ShowError(event->value);
			break;

		case CT_NX_EVENT_NEXT_ERROR:
		case CT_NX_EVENT_PREV_ERROR: {
			if (!ctAppTested || ctAppResult.errorCount == 0) break;
			int step = (event->type == CT_NX_EVENT_NEXT_ERROR) ? 1 : -1;
			int index = (ctAppErrorIndex >= ctAppResult.errorCount) ? 0
			            : (int)ctAppErrorIndex + step;
			if (index < 0) index = ctAppResult.errorCount - 1;
			if (index >= ctAppResult.errorCount) index = 0;
			CtApp_ShowError((uint8_t)index);
			break;
		}

		case CT_NX_EVENT_CABLE_SELECT:
			CtApp_SelectSlot(event->value);
			break;

		case CT_NX_EVENT_READY:
			CtApp_Refresh();
			break;

		case CT_NX_EVENT_TOUCH:
			CtApp_OnTouch(event);
			break;

		case CT_NX_EVENT_NUMBER:
			Log("Display: number %ld\n", (long)event->number);
			break;

		default:
			break;
	}
}

/* Packages moved at the start, before the display is ready */
static uint8_t ctAppMovedCount;
static uint8_t ctAppMovedFrom[CT_STORAGE_MAX_SLOTS];
static uint8_t ctAppMovedTo[CT_STORAGE_MAX_SLOTS];

static void CtApp_RememberMove(uint8_t from, uint8_t to)
{
	if (ctAppMovedCount < CT_STORAGE_MAX_SLOTS) {
		ctAppMovedFrom[ctAppMovedCount] = from;
		ctAppMovedTo[ctAppMovedCount] = to;
		++ctAppMovedCount;
	}
}

void CtApp_EarlyInit(void)
{
	CtStorage_Init();
	/* the packages written before the rule "no gaps" are moved down */
	CtStorage_Compact(CtApp_RememberMove);
}

void CtApp_Init(void)
{
	CtNextion_Init();
	if (CtNextion_Connect(CT_APP_DISPLAY_BAUD, 5000)) {
		/* the ids come in the touch events of the components */
		CtNextion_GetNumber("errorList.id", &ctAppTestId);
		CtNextion_GetNumber("cableName.id", &ctAppCableId);
		Log("Display: errorList id %ld, cableName id %ld\n", (long)ctAppTestId, (long)ctAppCableId);
	}
	CtUsb_Init();

	/* the pictures follow the packages moved in CtApp_EarlyInit */
	for (uint8_t i = 0; i < ctAppMovedCount; ++i) {
		CtApp_PictureMoved(ctAppMovedFrom[i], ctAppMovedTo[i]);
	}
	ctAppMovedCount = 0;

	uint8_t slot = CtStorage_FindFirst();
	if (slot != CT_APP_NO_SLOT) {
		CtApp_SelectSlot(slot);
		Log("Cable \"%s\" of the slot %u is selected\n", CtApp_GetPackage()->name, slot);
	} else {
		Log("No stored cables\n");
		CtApp_Refresh();
	}
}

void CtApp_Poll(void)
{
	CtNxEvent event;
	while (CtNextion_Poll(&event)) {
		CtApp_OnEvent(&event);
	}
	CtUsb_Poll();
}
