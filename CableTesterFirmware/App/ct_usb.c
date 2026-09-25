/*
 * ct_usb.c
 */

#include "ct_usb.h"
#include "ct_app.h"
#include "ct_nextion.h"
#include "ct_protocol.h"
#include "ct_storage.h"
#include "ct_test.h"
#include "main.h"
#include "usbd_winusb_if.h"

#include <stdio.h>
#include <string.h>

extern USBD_HandleTypeDef hUsbDeviceFS;
extern uint8_t buffBulk[];              /* receive buffer of EP 0x02, usbd_winusb_if.c */

#define CT_USB_SEND_TIMEOUT_MS 50

enum {
	CT_XFER_NONE = 0,
	CT_XFER_PKG,
	CT_XFER_IMG
};

/* data of EP 0x02 */
static volatile uint8_t  ctUsbRing[CT_USB_RING_SIZE];
static volatile uint16_t ctUsbRingHead;
static volatile uint16_t ctUsbRingTail;
static volatile uint8_t  ctUsbNeedRearm;

/* pending command */
static volatile uint8_t  ctUsbCmdPending;
static CtCmd             ctUsbCmd;

/* transfer */
static uint8_t  ctUsbXfer;
static uint8_t  ctUsbXferSlot;
static uint32_t ctUsbXferSize;
static uint32_t ctUsbXferDone;
static uint8_t  ctUsbXferFailed;

static uint16_t CtUsb_RingCount(void)
{
	return (uint16_t)((ctUsbRingHead - ctUsbRingTail + CT_USB_RING_SIZE) % CT_USB_RING_SIZE);
}

static uint16_t CtUsb_RingFree(void)
{
	return (uint16_t)(CT_USB_RING_SIZE - 1 - CtUsb_RingCount());
}

static uint32_t ctUsbDisconnectTick;

void CtUsb_Disconnect(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef dp = {0};
	dp.Pin = GPIO_PIN_12;                      /* USB D+ */
	dp.Mode = GPIO_MODE_OUTPUT_PP;
	dp.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_GPIO_Init(GPIOA, &dp);
	ctUsbDisconnectTick = HAL_GetTick();
}

void CtUsb_Connect(void)
{
	/* the host takes a low D+ for a disconnect after some ms */
	while ((HAL_GetTick() - ctUsbDisconnectTick) < 20) {
	}
	HAL_GPIO_DeInit(GPIOA, GPIO_PIN_12);
}

void CtUsb_Init(void)
{
	ctUsbRingHead = ctUsbRingTail = 0;
	ctUsbNeedRearm = 0;
	ctUsbCmdPending = 0;
	ctUsbXfer = CT_XFER_NONE;
}

uint8_t CtUsb_OnData(uint8_t epAddr, uint8_t* data, uint16_t size)
{
	(void)epAddr;
	for (uint16_t i = 0; i < size; ++i) {
		uint16_t next = (uint16_t)((ctUsbRingHead + 1) % CT_USB_RING_SIZE);
		if (next == ctUsbRingTail) {
			ctUsbXferFailed = 1;            /* must not happen, the endpoint is not re-armed */
			break;
		}
		ctUsbRing[ctUsbRingHead] = data[i];
		ctUsbRingHead = next;
	}
	if (CtUsb_RingFree() < WINUSB_EP_DATA_SIZE) {
		ctUsbNeedRearm = 1;                 /* the host waits until the buffer is drained */
		return USBD_WINUSB_OUT_HOLD;
	}
	return USBD_OK;
}

uint8_t CtUsb_OnCmd(uint8_t epAddr, uint8_t* data, uint16_t size)
{
	(void)epAddr;
	if (size < 3) return USBD_OK;
	if (ctUsbCmdPending) {
		CtRsp rsp;
		rsp.cmd = (uint8_t)(data[0] | 0x80);
		rsp.seq = data[1];
		rsp.status = CT_ST_BUSY;
		rsp.len = 0;
		USBD_WinUSB_Send(&hUsbDeviceFS, CT_EP_RSP, (uint8_t*)&rsp, 4);
		return USBD_OK;
	}
	memset(&ctUsbCmd, 0, sizeof(ctUsbCmd));
	memcpy(&ctUsbCmd, data, (size < sizeof(ctUsbCmd)) ? size : sizeof(ctUsbCmd));
	ctUsbCmdPending = 1;
	return USBD_OK;
}

static void CtUsb_Send(uint8_t endpoint, const void* data, uint16_t size)
{
	uint32_t start = HAL_GetTick();
	while (USBD_WinUSB_getStateSend(endpoint) == USBD_BUSY) {
		if ((HAL_GetTick() - start) >= CT_USB_SEND_TIMEOUT_MS) return;
	}
	USBD_WinUSB_Send(&hUsbDeviceFS, endpoint, (uint8_t*)data, size);
}

void CtUsb_SendEvent(uint8_t event, const void* data, uint8_t len)
{
	CtEvent ev;
	memset(&ev, 0, sizeof(ev));
	ev.event = event;
	ev.len = (len > CT_EVENT_DATA_SIZE) ? CT_EVENT_DATA_SIZE : len;
	if (ev.len) memcpy(ev.data, data, ev.len);
	CtUsb_Send(CT_EP_STATE, &ev, (uint16_t)(2 + ev.len));
}

static void CtUsb_Answer(uint8_t status, const void* data, uint8_t len)
{
	CtRsp rsp;
	memset(&rsp, 0, sizeof(rsp));
	rsp.cmd = (uint8_t)(ctUsbCmd.cmd | 0x80);
	rsp.seq = ctUsbCmd.seq;
	rsp.status = status;
	rsp.len = (len > CT_RSP_DATA_SIZE) ? CT_RSP_DATA_SIZE : len;
	if (rsp.len) memcpy(rsp.data, data, rsp.len);
	CtUsb_Send(CT_EP_RSP, &rsp, (uint16_t)(4 + rsp.len));
}

static void CtUsb_AbortXfer(void)
{
	if (ctUsbXfer == CT_XFER_IMG) CtNextion_FileAbort();
	if (ctUsbXfer == CT_XFER_PKG) CtStorage_CancelWrite();
	ctUsbXfer = CT_XFER_NONE;
	ctUsbRingTail = ctUsbRingHead;
	ctUsbXferDone = 0;
	ctUsbXferFailed = 0;
}

/* Moves the received bytes of the transfer out of the ring buffer */
static void CtUsb_DrainRing(void)
{
	while (CtUsb_RingCount()) {
		if (ctUsbXfer == CT_XFER_NONE) {        /* nothing waits for these bytes */
			ctUsbRingTail = ctUsbRingHead;
			break;
		}
		/* a linear part of the ring */
		uint16_t tail = ctUsbRingTail;
		uint16_t part = (ctUsbRingHead > tail) ? (uint16_t)(ctUsbRingHead - tail)
		                                       : (uint16_t)(CT_USB_RING_SIZE - tail);
		uint32_t left = (ctUsbXferSize > ctUsbXferDone) ? (ctUsbXferSize - ctUsbXferDone) : 0;
		if (part > left) {
			if (left == 0) {                    /* the host has sent more than it promised */
				ctUsbXferFailed = 1;
				ctUsbRingTail = ctUsbRingHead;
				break;
			}
			part = (uint16_t)left;
		}
		const uint8_t* data = (const uint8_t*)&ctUsbRing[tail];
		int ok = (ctUsbXfer == CT_XFER_PKG) ? CtStorage_WriteChunk(data, part)
		                                    : CtNextion_FileData(data, part);
		if (!ok) {
			ctUsbXferFailed = 1;
			ctUsbRingTail = ctUsbRingHead;
			break;
		}
		ctUsbXferDone += part;
		ctUsbRingTail = (uint16_t)((tail + part) % CT_USB_RING_SIZE);
	}
	if (ctUsbNeedRearm && CtUsb_RingFree() >= WINUSB_EP_DATA_SIZE) {
		ctUsbNeedRearm = 0;
		USBD_LL_PrepareReceive(&hUsbDeviceFS, CT_EP_DATA, buffBulk, WINUSB_EP_DATA_SIZE);
	}
}

static void CtUsb_CmdInfo(void)
{
	CtRspInfo info;
	memset(&info, 0, sizeof(info));
	info.protocolVersion = CT_PROTOCOL_VERSION;
	info.firmwareVersion = 1;
	info.slotCount = CtStorage_GetSlotCount();
	info.currentSlot = CtApp_GetSlot();
	info.slotSize = CtStorage_GetSlotSize();
	info.imageWidth = 480;
	info.imageHeight = 760;
	const CtPkgHeader* pkg = CtApp_GetPackage();
	if (pkg) {
		info.imageWidth = pkg->imageWidth;
		info.imageHeight = pkg->imageHeight;
	}
	CtUsb_Answer(CT_ST_OK, &info, sizeof(info));
}

static void CtUsb_CmdSlotInfo(void)
{
	if (ctUsbCmd.len < 1 || ctUsbCmd.arg[0] >= CtStorage_GetSlotCount()) {
		CtUsb_Answer(CT_ST_BAD_ARG, NULL, 0);
		return;
	}
	CtRspSlot slot;
	memset(&slot, 0, sizeof(slot));
	slot.slot = ctUsbCmd.arg[0];
	const CtPkgHeader* pkg = CtStorage_Get(slot.slot);
	if (pkg) {
		slot.used = 1;
		slot.wireCount = pkg->wireCount;
		slot.netCount = pkg->netCount;
		memcpy(slot.name, pkg->name, sizeof(slot.name) - 1);
	}
	CtUsb_Answer(CT_ST_OK, &slot, sizeof(slot));
}

static void CtUsb_CmdPkgBegin(void)
{
	if (ctUsbXfer != CT_XFER_NONE) {
		CtUsb_Answer(CT_ST_BUSY, NULL, 0);
		return;
	}
	if (ctUsbCmd.len < sizeof(CtCmdPkgBegin)) {
		CtUsb_Answer(CT_ST_BAD_ARG, NULL, 0);
		return;
	}
	CtCmdPkgBegin arg;
	memcpy(&arg, ctUsbCmd.arg, sizeof(arg));
	/* no gaps: a stored cable is replaced or the new one goes right after the last */
	if (arg.slot >= CtStorage_GetSlotCount() || arg.slot > CtStorage_CountUsed()) {
		CtUsb_Answer(CT_ST_NO_SLOT, NULL, 0);
		return;
	}
	if (arg.size == 0 || arg.size > CT_PKG_MAX_SIZE || arg.size > CtStorage_GetSlotSize()) {
		CtUsb_Answer(CT_ST_TOO_BIG, NULL, 0);
		return;
	}
	if (!CtStorage_BeginWrite(arg.slot)) {
		CtUsb_Answer(CT_ST_FLASH, NULL, 0);
		return;
	}
	ctUsbRingTail = ctUsbRingHead;
	ctUsbXfer = CT_XFER_PKG;
	ctUsbXferSlot = arg.slot;
	ctUsbXferSize = arg.size;
	ctUsbXferDone = 0;
	ctUsbXferFailed = 0;
	CtUsb_Answer(CT_ST_OK, NULL, 0);
}

static void CtUsb_CmdPkgEnd(void)
{
	CtRspSize size;
	size.size = ctUsbXferDone;
	if (ctUsbXfer != CT_XFER_PKG) {
		CtUsb_Answer(CT_ST_NO_DATA, &size, sizeof(size));
		return;
	}
	uint8_t status = CT_ST_OK;
	if (ctUsbXferFailed || ctUsbXferDone != ctUsbXferSize) {
		CtStorage_CancelWrite();
		status = CT_ST_NO_DATA;
	} else if (!CtStorage_EndWrite()) {
		/* EndWrite checks the written package and erases a broken one */
		status = CT_ST_BAD_CRC;
	}
	uint8_t slot = ctUsbXferSlot;
	ctUsbXfer = CT_XFER_NONE;
	if (status == CT_ST_OK) {
		Log("Package of %lu byte(s) is written to the slot %u\n", (unsigned long)ctUsbXferDone, slot);
		if (CtApp_GetSlot() == slot || CtApp_GetSlot() == CT_APP_NO_SLOT) {
			CtApp_SelectSlot(slot);
		} else {
			CtApp_RefreshCableList();
		}
	}
	CtUsb_Answer(status, &size, sizeof(size));
}

static void CtUsb_CmdImgBegin(void)
{
	if (ctUsbXfer != CT_XFER_NONE) {
		CtUsb_Answer(CT_ST_BUSY, NULL, 0);
		return;
	}
	if (ctUsbCmd.len < sizeof(CtCmdImgBegin)) {
		CtUsb_Answer(CT_ST_BAD_ARG, NULL, 0);
		return;
	}
	CtCmdImgBegin arg;
	memcpy(&arg, ctUsbCmd.arg, sizeof(arg));
	/* the picture belongs to a stored cable, so the package goes first */
	if (arg.slot >= CtStorage_CountUsed() || arg.size == 0) {
		CtUsb_Answer(CT_ST_BAD_ARG, NULL, 0);
		return;
	}
	char path[24];
	snprintf(path, sizeof(path), "sd0/c%u.jpg", arg.slot);
	if (!CtNextion_FileBegin(path, arg.size)) {
		CtUsb_Answer(CT_ST_DISPLAY, NULL, 0);
		return;
	}
	ctUsbRingTail = ctUsbRingHead;
	ctUsbXfer = CT_XFER_IMG;
	ctUsbXferSlot = arg.slot;
	ctUsbXferSize = arg.size;
	ctUsbXferDone = 0;
	ctUsbXferFailed = 0;
	CtUsb_Answer(CT_ST_OK, NULL, 0);
}

static void CtUsb_CmdImgEnd(void)
{
	CtRspSize size;
	size.size = ctUsbXferDone;
	if (ctUsbXfer != CT_XFER_IMG) {
		CtUsb_Answer(CT_ST_NO_DATA, &size, sizeof(size));
		return;
	}
	uint8_t status = CT_ST_OK;
	if (ctUsbXferFailed || ctUsbXferDone != ctUsbXferSize) {
		CtNextion_FileAbort();
		status = CT_ST_NO_DATA;
	} else if (!CtNextion_FileEnd()) {
		status = CT_ST_DISPLAY;
	}
	ctUsbXfer = CT_XFER_NONE;
	if (status == CT_ST_OK) {
		Log("Picture of %lu byte(s) is written to sd0/c%u.jpg\n",
		    (unsigned long)ctUsbXferDone, ctUsbXferSlot);
		if (CtApp_GetSlot() == ctUsbXferSlot) CtApp_Refresh();
	}
	CtUsb_Answer(status, &size, sizeof(size));
}

static void CtUsb_CmdRunTest(void)
{
	CtRspTest test;
	memset(&test, 0, sizeof(test));
	if (CtApp_GetPackage() == NULL) {
		CtUsb_Answer(CT_ST_NO_DATA, &test, sizeof(test));
		return;
	}
	test.errorCount = CtApp_RunTest();
	const CtTestResult* result = CtApp_GetResult();
	test.overflow = result ? result->overflow : 0;
	CtUsb_Answer(CT_ST_OK, &test, sizeof(test));
}

static void CtUsb_CmdGetError(void)
{
	const CtTestResult* result = CtApp_GetResult();
	if (result == NULL) {
		CtUsb_Answer(CT_ST_NO_DATA, NULL, 0);
		return;
	}
	if (ctUsbCmd.len < 1 || ctUsbCmd.arg[0] >= result->errorCount) {
		CtUsb_Answer(CT_ST_BAD_ARG, NULL, 0);
		return;
	}
	CtRspError error;
	error.index = ctUsbCmd.arg[0];
	error.type = result->errors[error.index].type;
	error.pinA = result->errors[error.index].pinA;
	error.pinB = result->errors[error.index].pinB;
	CtUsb_Answer(CT_ST_OK, &error, sizeof(error));
}

static void CtUsb_CmdGetRow(void)
{
	const CtTestResult* result = CtApp_GetResult();
	if (result == NULL) {
		CtUsb_Answer(CT_ST_NO_DATA, NULL, 0);
		return;
	}
	if (ctUsbCmd.len < 1 || ctUsbCmd.arg[0] < 1 || ctUsbCmd.arg[0] > CT_PIN_COUNT) {
		CtUsb_Answer(CT_ST_BAD_ARG, NULL, 0);
		return;
	}
	CtRspRow row;
	row.pin = ctUsbCmd.arg[0];
	CtPinMask mask = result->conn[row.pin - 1];
	for (int i = 0; i < 8; ++i) {
		row.mask[i] = (uint8_t)(mask >> (8 * i));
	}
	CtUsb_Answer(CT_ST_OK, &row, sizeof(row));
}

static void CtUsb_CmdNxCmd(void)
{
	char text[CT_CMD_ARG_SIZE + 1];
	uint8_t len = (ctUsbCmd.len > CT_CMD_ARG_SIZE) ? CT_CMD_ARG_SIZE : ctUsbCmd.len;
	memcpy(text, ctUsbCmd.arg, len);
	text[len] = 0;
	CtNextion_Send("%s", text);
	CtUsb_Answer(CT_ST_OK, NULL, 0);
}

static void CtUsb_Process(void)
{
	switch (ctUsbCmd.cmd) {
		case CT_CMD_INFO:      CtUsb_CmdInfo(); break;
		case CT_CMD_SLOT_INFO: CtUsb_CmdSlotInfo(); break;
		case CT_CMD_PKG_BEGIN: CtUsb_CmdPkgBegin(); break;
		case CT_CMD_PKG_END:   CtUsb_CmdPkgEnd(); break;
		case CT_CMD_IMG_BEGIN: CtUsb_CmdImgBegin(); break;
		case CT_CMD_IMG_END:   CtUsb_CmdImgEnd(); break;
		case CT_CMD_RUN_TEST:  CtUsb_CmdRunTest(); break;
		case CT_CMD_GET_ERROR: CtUsb_CmdGetError(); break;
		case CT_CMD_GET_ROW:   CtUsb_CmdGetRow(); break;
		case CT_CMD_NX_CMD:    CtUsb_CmdNxCmd(); break;

		case CT_CMD_PKG_ERASE:
			if (ctUsbCmd.len < 1 || ctUsbCmd.arg[0] >= CtStorage_CountUsed()) {
				CtUsb_Answer(CT_ST_BAD_ARG, NULL, 0);
			} else {
				CtApp_EraseSlot(ctUsbCmd.arg[0]);   /* the next cables move down */
				CtUsb_Answer(CT_ST_OK, NULL, 0);
			}
			break;

		case CT_CMD_SELECT:
			if (ctUsbCmd.len < 1) {
				CtUsb_Answer(CT_ST_BAD_ARG, NULL, 0);
			} else {
				CtUsb_Answer(CtApp_SelectSlot(ctUsbCmd.arg[0]) ? CT_ST_OK : CT_ST_NO_DATA, NULL, 0);
			}
			break;

		case CT_CMD_ABORT:
			CtUsb_AbortXfer();
			CtUsb_Answer(CT_ST_OK, NULL, 0);
			break;

		default:
			CtUsb_Answer(CT_ST_BAD_CMD, NULL, 0);
			break;
	}
}

void CtUsb_Poll(void)
{
	CtUsb_DrainRing();
	if (ctUsbCmdPending) {
		CtUsb_Process();
		ctUsbCmdPending = 0;
	}
}
