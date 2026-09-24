/*
 * ct_usb.h
 *
 * The USB protocol of the tester, see Common/ct_protocol.h.
 *
 * The endpoint callbacks are called from the USB interrupt, so they only copy
 * the data and the work is done in CtUsb_Poll() from the main loop: the test
 * takes tens of milliseconds and the display answers a file packet in up to
 * 500 ms, and neither may happen inside the interrupt.
 *
 * The data endpoint is not re-armed while the buffer is full, so the host
 * simply waits on NAK and no flow control is needed in the protocol.
 */

#ifndef CT_USB_H_
#define CT_USB_H_

#include <stdint.h>

#define CT_USB_RING_SIZE  2048

/* The pull-up of D+ is soldered to 3.3 V, so the PC does not notice a reset of
   the MCU and keeps talking to the old address. Holding D+ low makes the PC
   see a disconnect and enumerate the device again when it is released.
   Call Disconnect first at the start, do the flash work (it stalls the CPU and
   the enumeration would fail), then Connect before MX_USB_DEVICE_Init(). */
void CtUsb_Disconnect(void);
void CtUsb_Connect(void);

void CtUsb_Init(void);

/* Call it in the main loop */
void CtUsb_Poll(void);

/* EP 0x01, from USBD_WinUSB_interruptEvent */
uint8_t CtUsb_OnCmd(uint8_t epAddr, uint8_t* data, uint16_t size);

/* EP 0x02, from USBD_WinUSB_BulkEvent. Returns 0xEE to stop the receiving */
uint8_t CtUsb_OnData(uint8_t epAddr, uint8_t* data, uint16_t size);

/* Sends an event to the PC (EP 0x81), CT_EV_xxx */
void CtUsb_SendEvent(uint8_t event, const void* data, uint8_t len);

#endif /* CT_USB_H_ */
