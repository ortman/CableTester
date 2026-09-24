/*
 * ct_protocol.h
 *
 * USB protocol of the tester (WinUSB, vendor interface).
 * Shared by CableTesterFirmware and CableTesterDesktop.
 *
 * Endpoints:
 *   0x01 INT OUT  32 B  commands from the PC        (CtCmd)
 *   0x82 INT IN   60 B  answers to the commands     (CtRsp)
 *   0x02 BULK OUT 64 B  raw data of the active transfer (no header)
 *   0x81 INT IN   60 B  events of the device        (CtEvent)
 *
 * A transfer of a package or of a picture goes like this:
 *   CT_CMD_PKG_BEGIN / CT_CMD_IMG_BEGIN  -> answer with the status
 *   the bytes of the file into EP 0x02    -> no answer, the device counts them
 *   CT_CMD_PKG_END / CT_CMD_IMG_END      -> answer with the status and the size
 * The device stops reading EP 0x02 while it is busy, so the host may stream
 * the data without waiting for anything.
 *
 * The cables are kept in the slots 0..N-1 without gaps (the line of the cable
 * list on the display is the slot number):
 *   PKG_BEGIN takes a stored slot (replace) or N (a new cable);
 *   IMG_BEGIN takes a stored slot only, so the package goes first;
 *   PKG_ERASE moves the next cables and their pictures one slot down.
 *
 * All values are little-endian, structures are packed.
 */

#ifndef CT_PROTOCOL_H_
#define CT_PROTOCOL_H_

#include <stdint.h>

#define CT_USB_VID              0x0483
#define CT_USB_PID              0x5744
#define CT_USB_GUID             "{92cf51ca-392a-4db5-9bff-46d0e0062c1b}"

#define CT_PROTOCOL_VERSION     1

#define CT_EP_CMD               0x01
#define CT_EP_DATA              0x02
#define CT_EP_STATE             0x81
#define CT_EP_RSP               0x82

#define CT_CMD_ARG_SIZE         29
#define CT_RSP_DATA_SIZE        56
#define CT_EVENT_DATA_SIZE      58

/* Commands */
enum {
	CT_CMD_INFO      = 0x01,  /* -> CtRspInfo */
	CT_CMD_SLOT_INFO = 0x02,  /* arg: slot -> CtRspSlot */
	CT_CMD_PKG_BEGIN = 0x03,  /* arg: CtCmdPkgBegin */
	CT_CMD_PKG_END   = 0x04,  /* -> CtRspSize */
	CT_CMD_PKG_ERASE = 0x05,  /* arg: slot */
	CT_CMD_IMG_BEGIN = 0x06,  /* arg: CtCmdImgBegin */
	CT_CMD_IMG_END   = 0x07,  /* -> CtRspSize */
	CT_CMD_SELECT    = 0x08,  /* arg: slot, shows the cable on the display */
	CT_CMD_RUN_TEST  = 0x09,  /* -> CtRspTest */
	CT_CMD_GET_ERROR = 0x0A,  /* arg: index -> CtRspError */
	CT_CMD_GET_ROW   = 0x0B,  /* arg: pin -> CtRspRow, the measured connections */
	CT_CMD_NX_CMD    = 0x0C,  /* arg: text of a display instruction, for debugging */
	CT_CMD_ABORT     = 0x0D   /* stops the active transfer */
};

/* Statuses */
enum {
	CT_ST_OK        = 0x00,
	CT_ST_BAD_CMD   = 0x01,
	CT_ST_BAD_ARG   = 0x02,
	CT_ST_BUSY      = 0x03,
	CT_ST_BAD_CRC   = 0x04,
	CT_ST_FLASH     = 0x05,
	CT_ST_DISPLAY   = 0x06,
	CT_ST_NO_DATA   = 0x07,
	CT_ST_TOO_BIG   = 0x08,
	CT_ST_NO_SLOT   = 0x09
};

/* Events of the device (EP 0x81) */
enum {
	CT_EV_TEST_DONE   = 0x01,  /* the test was started from the display, data: CtRspTest */
	CT_EV_CABLE_SHOWN = 0x02   /* the cable was selected on the display, data: slot */
};

#pragma pack(push, 1)

typedef struct {
	uint8_t cmd;
	uint8_t seq;                    /* the answer repeats it */
	uint8_t len;                    /* used bytes of arg */
	uint8_t arg[CT_CMD_ARG_SIZE];
} CtCmd;

typedef struct {
	uint8_t cmd;                    /* the command it answers */
	uint8_t seq;
	uint8_t status;                 /* CT_ST_xxx */
	uint8_t len;                    /* used bytes of data */
	uint8_t data[CT_RSP_DATA_SIZE];
} CtRsp;

typedef struct {
	uint8_t event;                  /* CT_EV_xxx */
	uint8_t len;
	uint8_t data[CT_EVENT_DATA_SIZE];
} CtEvent;

typedef struct {
	uint8_t  protocolVersion;
	uint8_t  firmwareVersion;
	uint8_t  slotCount;
	uint8_t  currentSlot;           /* 0xFF: nothing is selected */
	uint16_t slotSize;              /* bytes available for one package */
	uint16_t imageWidth;            /* size of the picture the display expects */
	uint16_t imageHeight;
} CtRspInfo;

typedef struct {
	uint8_t slot;
	uint8_t used;                   /* 0: the slot is empty or damaged */
	uint8_t wireCount;
	uint8_t netCount;
	char    name[32];               /* UTF-8, zero terminated */
} CtRspSlot;

typedef struct {
	uint8_t  slot;
	uint16_t size;                  /* size of the package */
} CtCmdPkgBegin;

typedef struct {
	uint8_t  slot;                  /* the picture is written as sd0/c<slot>.jpg */
	uint32_t size;
} CtCmdImgBegin;

typedef struct {
	uint32_t size;                  /* bytes the device has received */
} CtRspSize;

typedef struct {
	uint8_t errorCount;
	uint8_t overflow;               /* there were more errors than the device can keep */
} CtRspTest;

typedef struct {
	uint8_t index;
	uint8_t type;                   /* 0: open, 1: short (CT_ERROR_xxx of ct_test.h) */
	uint8_t pinA;
	uint8_t pinB;
} CtRspError;

typedef struct {
	uint8_t pin;                    /* 1..60 */
	uint8_t mask[8];                /* bit (n-1): the pin n is connected to this pin */
} CtRspRow;

#pragma pack(pop)

#endif /* CT_PROTOCOL_H_ */
