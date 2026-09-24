/*
 * ct_nextion.h
 *
 * Nextion Intelligent display on USART1.
 *
 * Display -> MCU:
 *   standard returns (0x65 touch, 0x70 string, 0x71 number), every one of them
 *   ends with FF FF FF, and the frames of this project:
 *
 *     printh 23 54 FF FF FF          '#T'      run the test
 *     printh 23 45 <idx> FF FF FF    '#E' idx  the error idx (1 based) is selected
 *     printh 23 4E FF FF FF          '#N'      show the next error
 *     printh 23 50 FF FF FF          '#P'      show the previous error
 *     printh 23 43 <idx> FF FF FF    '#C' idx  the cable idx is selected
 *     printh 23 52 FF FF FF          '#R'      the page is loaded, send the state
 *
 * MCU -> display: plain instructions and the twfile transfer of a picture to
 * the microSD card of the display.
 */

#ifndef CT_NEXTION_H_
#define CT_NEXTION_H_

#include <stdint.h>

#define CT_NX_RX_SIZE        256
#define CT_NX_CMD_SIZE       768   /* one instruction without the FF FF FF end */
#define CT_NX_FILE_PACKET    1024  /* data bytes in one twfile packet, max 4096 */
#define CT_NX_ACK_TIMEOUT_MS 600   /* the display answers a file packet within 500 ms */

enum {
	CT_NX_EVENT_NONE = 0,
	CT_NX_EVENT_TEST,          /* '#T' */
	CT_NX_EVENT_ERROR_SELECT,  /* '#E', value = number of the error in the list, 1 based */
	CT_NX_EVENT_NEXT_ERROR,    /* '#N' */
	CT_NX_EVENT_PREV_ERROR,    /* '#P' */
	CT_NX_EVENT_CABLE_SELECT,  /* '#C', value = index of the cable */
	CT_NX_EVENT_READY,         /* '#R' */
	CT_NX_EVENT_TOUCH,         /* 0x65, value = component id, page = page id,
	                              number = 1 press, 0 release */
	CT_NX_EVENT_NUMBER         /* 0x71, number = the answer to "get" */
};

typedef struct {
	uint8_t type;
	uint8_t value;
	uint8_t page;
	int32_t number;
} CtNxEvent;

void CtNextion_Init(void);

/* Called from HAL_UART_RxCpltCallback, which is defined in ct_nextion.c */
void CtNextion_RxByte(void);

/* Takes one event from the display, returns 0 when there is nothing */
int CtNextion_Poll(CtNxEvent* event);

/* Sends an instruction, adds the FF FF FF end. printf format */
void CtNextion_Send(const char* format, ...);

/* Sends "get <attribute>" and waits for the number. Returns 0 on error.
   Other events that come meanwhile are lost, so it is for the start and debugging */
int CtNextion_GetNumber(const char* attribute, int32_t* value);

/* Switches the display and the MCU to another baud rate (bkcmd of the display stays) */
void CtNextion_SetBaud(uint32_t baud);

/* Finds the baud rate of the display (it may be 9600 after the power on) and
   switches it to the given one. Waits for the display up to timeoutMs.
   Returns the baud rate that works now or 0 when the display does not answer */
uint32_t CtNextion_Connect(uint32_t baud, uint32_t timeoutMs);

/* twfile: writes a file to the display.
   Begin, then Data for every part of the file, then End.
   All of them return 0 on error. */
int CtNextion_FileBegin(const char* path, uint32_t size);
int CtNextion_FileData(const uint8_t* data, uint16_t size);
int CtNextion_FileEnd(void);
void CtNextion_FileAbort(void);

#endif /* CT_NEXTION_H_ */
