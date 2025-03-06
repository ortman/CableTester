/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_winusb_if.h
  * @brief          : Header for usbd_winusb_if.c file.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

#ifndef __USBD_WINUSB_IF_H_
#define __USBD_WINUSB_IF_H_

/* Includes ------------------------------------------------------------------*/
#include "usbd_winusb.h"

/* USER CODE BEGIN INCLUDE */

/* USER CODE END INCLUDE */

/* USER CODE BEGIN 0 */
#define WINUSB_DEVICE_EP_COUNT	4

#define WINUSB_EP_STATE_ADDR	0x81
#define WINUSB_EP_STATE_SIZE	0x3C

#define WINUSB_EP_IN_ADDR		0x82
#define WINUSB_EP_IN_SIZE		0x3C

#define WINUSB_EP_CMD_ADDR		0x01
#define WINUSB_EP_CMD_SIZE		0x20

#define WINUSB_EP_DATA_ADDR		0x02
#define WINUSB_EP_DATA_SIZE		0x40
/* USER CODE END 0 */

/* USER CODE BEGIN EXPORTED_DEFINES */

/* USER CODE END EXPORTED_DEFINES */

/* USER CODE BEGIN EXPORTED_TYPES */

/* USER CODE END EXPORTED_TYPES */

/* USER CODE BEGIN EXPORTED_MACRO */

/* USER CODE END EXPORTED_MACRO */

extern USBD_WinUSB_EnpointsConfig_t winUsbDeviceConfig[WINUSB_DEVICE_EP_COUNT];

/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */

uint8_t winUsbVendorSetupCallback(struct _USBD_HandleTypeDef *pdev , USBD_SetupReqTypedef  *req);

/* USER CODE BEGIN EXPORTED_FUNCTIONS */

/* USER CODE END EXPORTED_FUNCTIONS */

#endif /* __USBD_WINUSB_IF_H_ */

