/*
 * usbd_winusb_if.h
 *
 *  Created on: 29 ���. 2018 �.
 *      Author: ortman
 */

#ifndef __USBD_WINUSB_IF_H_
#define __USBD_WINUSB_IF_H_

#include "usbd_winusb.h"

#define WINUSB_DEVICE_EP_COUNT	4

#define WINUSB_EP_STATE_ADDR	0x81
#define WINUSB_EP_STATE_SIZE	0x3C

#define WINUSB_EP_IN_ADDR		0x82
#define WINUSB_EP_IN_SIZE		0x3C

#define WINUSB_EP_CMD_ADDR		0x01
#define WINUSB_EP_CMD_SIZE		0x20

#define WINUSB_EP_DATA_ADDR		0x02
#define WINUSB_EP_DATA_SIZE		0x40

extern USBD_WinUSB_EnpointsConfig_t winUsbDeviceConfig[WINUSB_DEVICE_EP_COUNT];

uint8_t winUsbVendorSetupCallback(struct _USBD_HandleTypeDef *pdev , USBD_SetupReqTypedef  *req);

#endif /* __USBD_WINUSB_IF_H_ */
