/*
 * ct_nextion.c
 */

#include "ct_nextion.h"
#include "main.h"
#include "usart.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define CT_NX_END           "\xFF\xFF\xFF"
#define CT_NX_TX_TIMEOUT_MS 2000

/* twfile packet header */
static const uint8_t ctNxFileConst[7] = { 0x3A, 0xA1, 0xBB, 0x44, 0x7F, 0xFF, 0xFE };
#define CT_NX_FILE_NO_CRC   0x00
#define CT_NX_FILE_ACK_OK   0x05
#define CT_NX_FILE_ACK_FAIL 0x04

static volatile uint8_t  ctNxRx[CT_NX_RX_SIZE];
static volatile uint16_t ctNxRxHead;
static volatile uint16_t ctNxRxTail;
static uint8_t           ctNxRxByte;

static uint8_t  ctNxFrame[CT_NX_RX_SIZE];
static uint16_t ctNxFrameLen;

/* twfile state */
static uint8_t  ctNxFileBuf[CT_NX_FILE_PACKET];
static uint16_t ctNxFileBufLen;
static uint16_t ctNxFilePacketId;
static uint32_t ctNxFileLeft;
static uint8_t  ctNxFileActive;
static uint8_t  ctNxFileDone;       /* the display has confirmed the end */

static void CtNextion_SetMcuBaud(uint32_t baud);
static void CtNextion_SendAbortPacket(void);
static uint32_t ctNxBaud;

void CtNextion_Init(void)
{
	ctNxRxHead = ctNxRxTail = 0;
	ctNxFrameLen = 0;
	ctNxFileActive = 0;
	ctNxBaud = huart1.Init.BaudRate;
	HAL_UART_Receive_IT(&huart1, &ctNxRxByte, 1);
}

/* The HAL callback of the receive interrupt */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
	if (huart->Instance == USART1) CtNextion_RxByte();
}

void CtNextion_RxByte(void)
{
	uint16_t next = (uint16_t)((ctNxRxHead + 1) % CT_NX_RX_SIZE);
	if (next != ctNxRxTail) {          /* the oldest byte is kept on overflow */
		ctNxRx[ctNxRxHead] = ctNxRxByte;
		ctNxRxHead = next;
	}
	HAL_UART_Receive_IT(&huart1, &ctNxRxByte, 1);
}

static int CtNextion_ReadByte(uint8_t* byte, uint32_t timeoutMs)
{
	uint32_t start = HAL_GetTick();
	while (ctNxRxTail == ctNxRxHead) {
		if ((HAL_GetTick() - start) >= timeoutMs) return 0;
	}
	*byte = ctNxRx[ctNxRxTail];
	ctNxRxTail = (uint16_t)((ctNxRxTail + 1) % CT_NX_RX_SIZE);
	return 1;
}

static void CtNextion_Write(const uint8_t* data, uint16_t size)
{
	HAL_UART_Transmit(&huart1, (uint8_t*)data, size, CT_NX_TX_TIMEOUT_MS);
}

void CtNextion_Send(const char* format, ...)
{
	static char cmd[CT_NX_CMD_SIZE];   /* static: the stack is small */
	va_list args;
	va_start(args, format);
	int len = vsnprintf(cmd, sizeof(cmd), format, args);
	va_end(args);
	if (len < 0) return;
	if (len > (int)sizeof(cmd) - 1) len = (int)sizeof(cmd) - 1;
	CtNextion_Write((const uint8_t*)cmd, (uint16_t)len);
	CtNextion_Write((const uint8_t*)CT_NX_END, 3);
}

void CtNextion_SetBaud(uint32_t baud)
{
	CtNextion_Send("baud=%lu", (unsigned long)baud);
	HAL_Delay(50);
	CtNextion_SetMcuBaud(baud);
}

/* Decodes a frame that ended with FF FF FF */
static int CtNextion_Decode(const uint8_t* frame, uint16_t len, CtNxEvent* event)
{
	if (len < 1) return 0;
	event->type = CT_NX_EVENT_NONE;
	event->value = 0;
	event->page = 0;
	event->number = 0;
	if (len == 1) {                             /* return code of an instruction */
		if (frame[0] != 0x01) {
			Log("Nextion: return code 0x%02X at %lu\n", frame[0], (unsigned long)ctNxBaud);
		}
		return 0;
	}
	if (frame[0] == 0x71 && len >= 5) {         /* number */
		event->type = CT_NX_EVENT_NUMBER;
		event->number = (int32_t)((uint32_t)frame[1] | ((uint32_t)frame[2] << 8) |
		                          ((uint32_t)frame[3] << 16) | ((uint32_t)frame[4] << 24));
		return 1;
	}
	if (frame[0] == '#') {                      /* frame of this project */
		if (len < 2) return 0;
		uint8_t value = (len > 2) ? frame[2] : 0;
		event->value = value;
		switch (frame[1]) {
			case 'T': event->type = CT_NX_EVENT_TEST; return 1;
			case 'E': event->type = CT_NX_EVENT_ERROR_SELECT; return 1;
			case 'N': event->type = CT_NX_EVENT_NEXT_ERROR; return 1;
			case 'P': event->type = CT_NX_EVENT_PREV_ERROR; return 1;
			case 'C': event->type = CT_NX_EVENT_CABLE_SELECT; return 1;
			case 'R': event->type = CT_NX_EVENT_READY; return 1;
			default: return 0;
		}
	}
	if (frame[0] == 0x65 && len >= 4) {         /* touch event */
		event->type = CT_NX_EVENT_TOUCH;
		event->page = frame[1];
		event->value = frame[2];
		event->number = frame[3];               /* 1: press, 0: release */
		return 1;
	}
#if DEBUG
	Log("Nextion: unknown frame of %u byte(s) at %lu:", len, (unsigned long)ctNxBaud);
	for (uint16_t i = 0; i < len && i < 16; ++i) Log(" %02X", frame[i]);
	Log("\n");
#endif
	return 0;
}

int CtNextion_Poll(CtNxEvent* event)
{
	uint8_t byte;
	while (!ctNxFileActive && CtNextion_ReadByte(&byte, 0)) {
		if (ctNxFrameLen < sizeof(ctNxFrame)) {
			ctNxFrame[ctNxFrameLen++] = byte;
		}
		if (ctNxFrameLen >= 3 &&
		    ctNxFrame[ctNxFrameLen - 1] == 0xFF &&
		    ctNxFrame[ctNxFrameLen - 2] == 0xFF &&
		    ctNxFrame[ctNxFrameLen - 3] == 0xFF) {
			uint16_t len = (uint16_t)(ctNxFrameLen - 3);
			ctNxFrameLen = 0;
			if (CtNextion_Decode(ctNxFrame, len, event)) return 1;
		}
	}
	return 0;
}

static int CtNextion_GetNumberWait(const char* attribute, int32_t* value, uint32_t timeoutMs)
{
	CtNxEvent event;
	while (CtNextion_Poll(&event)) {           /* drop what was before */
	}
	CtNextion_Send("get %s", attribute);
	uint32_t start = HAL_GetTick();
	while ((HAL_GetTick() - start) < timeoutMs) {
		if (CtNextion_Poll(&event) && event.type == CT_NX_EVENT_NUMBER) {
			*value = event.number;
			return 1;
		}
	}
	return 0;
}

int CtNextion_GetNumber(const char* attribute, int32_t* value)
{
	return CtNextion_GetNumberWait(attribute, value, 300);
}

static void CtNextion_SetMcuBaud(uint32_t baud)
{
	HAL_UART_AbortReceive(&huart1);
	HAL_UART_DeInit(&huart1);
	huart1.Init.BaudRate = baud;
	if (HAL_UART_Init(&huart1) != HAL_OK) {
		Error_Handler();
	}
	ctNxBaud = baud;
	ctNxRxHead = ctNxRxTail = 0;
	ctNxFrameLen = 0;
	HAL_UART_Receive_IT(&huart1, &ctNxRxByte, 1);
}

uint32_t CtNextion_Connect(uint32_t baud, uint32_t timeoutMs)
{
	static const uint32_t rates[] = { 250000, 115200, 9600, 921600, 512000, 256000,
	                                  230400, 57600, 38400, 31250, 19200, 4800, 2400 };
	uint32_t start = HAL_GetTick();
	uint8_t restarted = 0;
	/* the display may still wait for the data of a file after a failed transfer */
	CtNextion_SetMcuBaud(baud);
	CtNextion_SendAbortPacket();
	do {
		if (restarted == 0 && (HAL_GetTick() - start) > timeoutMs / 2) {
			/* the display may keep a strange rate set before: reset it at every rate,
			   after the reset it runs Program.s of the HMI and takes its baud rate */
			Log("Nextion: no answer, resetting the display\n");
			for (unsigned i = 0; i < sizeof(rates) / sizeof(rates[0]); ++i) {
				CtNextion_SetMcuBaud(rates[i]);
				CtNextion_Send("");
				CtNextion_Send("rest");
				HAL_Delay(5);
			}
			HAL_Delay(1500);
			restarted = 1;
		}
		for (unsigned i = 0; i < sizeof(rates) / sizeof(rates[0]); ++i) {
			CtNextion_SetMcuBaud(rates[i]);
			CtNextion_Send("");                /* ends what the display may have got */
			HAL_Delay(5);
			int32_t page;
			/* "get dp" and the answer take ~90 ms even at 2400 */
			if (!CtNextion_GetNumberWait("dp", &page, 120)) continue;
			Log("Nextion: answers at %lu, page %ld\n", (unsigned long)rates[i], (long)page);
			if (rates[i] != baud) {
				CtNextion_Send("baud=%lu", (unsigned long)baud);
				HAL_Delay(50);
				CtNextion_SetMcuBaud(baud);
				if (!CtNextion_GetNumber("dp", &page)) {
					Log("Nextion: no answer after the switch to %lu\n", (unsigned long)baud);
					CtNextion_SetMcuBaud(rates[i]);
					return rates[i];
				}
				Log("Nextion: switched to %lu\n", (unsigned long)baud);
			}
			return baud;
		}
	} while ((HAL_GetTick() - start) < timeoutMs);
	Log("Nextion: no answer\n");
	CtNextion_SetMcuBaud(baud);
	return 0;
}

/* Waits for "<first> FF FF FF", the answer of the display to a twfile command.
   Other frames may come before it: the answer to delfile takes more than
   100 ms on the microSD, so they are skipped */
static int CtNextion_WaitFileAnswer(uint8_t first)
{
	uint8_t frame[4];
	uint8_t len = 0;
	uint32_t start = HAL_GetTick();
	while ((HAL_GetTick() - start) < 2 * CT_NX_ACK_TIMEOUT_MS) {
		uint8_t byte;
		if (!CtNextion_ReadByte(&byte, CT_NX_ACK_TIMEOUT_MS)) break;
		if (len < sizeof(frame)) frame[len++] = byte;
		if (len >= 4 && frame[len - 1] == 0xFF && frame[len - 2] == 0xFF && frame[len - 3] == 0xFF) {
			if (frame[0] == first && len == 4) return 1;
			Log("Nextion: frame %02X before the answer %02X of the file operation\n", frame[0], first);
			len = 0;
		} else if (len == sizeof(frame)) {
			memmove(frame, frame + 1, sizeof(frame) - 1);  /* not a frame yet: shift */
			--len;
		}
	}
	Log("Nextion: no answer %02X to the file operation\n", first);
	return 0;
}

static int CtNextion_SendPacket(void)
{
	uint8_t header[12];
	memcpy(header, ctNxFileConst, sizeof(ctNxFileConst));
	header[7] = CT_NX_FILE_NO_CRC;
	header[8] = (uint8_t)(ctNxFilePacketId & 0xFF);
	header[9] = (uint8_t)(ctNxFilePacketId >> 8);
	header[10] = (uint8_t)(ctNxFileBufLen & 0xFF);
	header[11] = (uint8_t)(ctNxFileBufLen >> 8);

	CtNextion_Write(header, sizeof(header));
	CtNextion_Write(ctNxFileBuf, ctNxFileBufLen);

	/* The answer is 0x05, 0x04 or 0xFD. Other bytes may come before it (the
	   display sometimes sends a single 0x06 on the first packet), skip them */
	uint8_t ack = 0;
	int received = 0;
	uint32_t start = HAL_GetTick();
	while (!received && (HAL_GetTick() - start) < CT_NX_ACK_TIMEOUT_MS) {
		if (!CtNextion_ReadByte(&ack, CT_NX_ACK_TIMEOUT_MS)) break;
		if (ack == CT_NX_FILE_ACK_OK || ack == CT_NX_FILE_ACK_FAIL || ack == 0xFD) {
			received = 1;
		} else {
			Log("Nextion: byte %02X before the answer to the packet %u\n", ack, ctNxFilePacketId);
		}
	}
	if (received && ack == 0xFD && ctNxFileLeft == ctNxFileBufLen) {
		/* the display answers the last packet with the end of the transfer at once */
		uint8_t byte;
		for (int i = 0; i < 3; ++i) {
			if (!CtNextion_ReadByte(&byte, CT_NX_ACK_TIMEOUT_MS) || byte != 0xFF) return 0;
		}
		ctNxFileLeft = 0;
		ctNxFileBufLen = 0;
		ctNxFileDone = 1;
		return 1;
	}
	if (!received || ack != CT_NX_FILE_ACK_OK) {
		Log("Nextion: packet %u of %u byte(s) is not accepted: %02X", ctNxFilePacketId, ctNxFileBufLen, ack);
		uint8_t byte;
		while (CtNextion_ReadByte(&byte, 200)) Log(" %02X", byte);
		Log("\n");
		return 0;
	}
	ctNxFileLeft -= ctNxFileBufLen;
	ctNxFileBufLen = 0;
	++ctNxFilePacketId;
	return 1;
}

int CtNextion_FileBegin(const char* path, uint32_t size)
{
	if (size == 0) return 0;
	/* twfile does not replace a file, the old one is removed first.
	   The answer "no such file" (0x06) is expected and dropped below */
	CtNextion_Send("delfile \"%s\"", path);
	HAL_Delay(100);
	ctNxFrameLen = 0;
	ctNxFileBufLen = 0;
	ctNxFilePacketId = 0;
	ctNxFileLeft = size;
	ctNxFileDone = 0;
	ctNxFileActive = 1;
	ctNxRxTail = ctNxRxHead;                   /* drop what was received before */

	CtNextion_Send("twfile \"%s\",%lu", path, (unsigned long)size);
	if (!CtNextion_WaitFileAnswer(0xFE)) {
		Log("Nextion: twfile %s is rejected\n", path);
		CtNextion_SendAbortPacket();
		ctNxFileActive = 0;
		return 0;
	}
	return 1;
}

int CtNextion_FileData(const uint8_t* data, uint16_t size)
{
	if (!ctNxFileActive) return 0;
	while (size) {
		uint16_t free = (uint16_t)(CT_NX_FILE_PACKET - ctNxFileBufLen);
		uint16_t part = (size < free) ? size : free;
		memcpy(ctNxFileBuf + ctNxFileBufLen, data, part);
		ctNxFileBufLen = (uint16_t)(ctNxFileBufLen + part);
		data += part;
		size = (uint16_t)(size - part);
		if (ctNxFileBufLen == CT_NX_FILE_PACKET && !CtNextion_SendPacket()) {
			CtNextion_FileAbort();
			return 0;
		}
	}
	return 1;
}

int CtNextion_FileEnd(void)
{
	if (!ctNxFileActive) return 0;
	if (ctNxFileBufLen && !CtNextion_SendPacket()) {
		CtNextion_FileAbort();
		return 0;
	}
	int ok = (ctNxFileLeft == 0) && (ctNxFileDone || CtNextion_WaitFileAnswer(0xFD));
	if (!ok) {
		Log("Nextion: the file is not finished, %lu byte(s) left\n", (unsigned long)ctNxFileLeft);
	}
	ctNxFileActive = 0;
	return ok;
}

/* The display leaves the file mode on a packet without data with pkID 65535,
   sent after a pause of 20 ms. Otherwise it takes all the next instructions as
   the data of the file. */
static void CtNextion_SendAbortPacket(void)
{
	uint8_t header[12];
	memcpy(header, ctNxFileConst, sizeof(ctNxFileConst));
	header[7] = CT_NX_FILE_NO_CRC;
	header[8] = 0xFF;
	header[9] = 0xFF;
	header[10] = 0;
	header[11] = 0;
	HAL_Delay(25);
	CtNextion_Write(header, sizeof(header));
	HAL_Delay(100);
	ctNxRxTail = ctNxRxHead;
	ctNxFrameLen = 0;
}

void CtNextion_FileAbort(void)
{
	if (ctNxFileActive) CtNextion_SendAbortPacket();
	ctNxFileActive = 0;
	ctNxFileBufLen = 0;
	ctNxFileLeft = 0;
}
