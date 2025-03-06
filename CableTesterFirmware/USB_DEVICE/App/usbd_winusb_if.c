/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_winusb_if.c
  * @brief          : WinUSB
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

/* Includes ------------------------------------------------------------------*/
#include "usbd_winusb_if.h"

/* USER CODE BEGIN INCLUDE */

/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief Usb device.
  * @{
  */

/** @defgroup USBD_DFU
  * @brief Usb DFU device module.
  * @{
  */

/** @defgroup USBD_DFU_Private_TypesDefinitions
  * @brief Private types.
  * @{
  */

/* USER CODE BEGIN PRIVATE_TYPES */

/* USER CODE END PRIVATE_TYPES */

/**
  * @}
  */

/** @defgroup USBD_DFU_Private_Defines
  * @brief Private defines.
  * @{
  */

/* USER CODE BEGIN PRIVATE_DEFINES */

/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_DFU_Private_Macros
  * @brief Private macros.
  * @{
  */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_DFU_Private_Variables
  * @brief Private variables.
  * @{
  */

/* USER CODE BEGIN PRIVATE_VARIABLES */

/* USER CODE END PRIVATE_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_DFU_Exported_Variables
  * @brief Public variables.
  * @{
  */

extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_DFU_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */

static uint8_t USBD_WinUSB_interruptEvent(uint8_t epAddr, uint8_t *buff, uint16_t buffSize);
static uint8_t USBD_WinUSB_BulkEvent(uint8_t epAddr, uint8_t *buff, uint16_t buffSize);

uint8_t buffInterrupt[WINUSB_EP_CMD_SIZE];
uint8_t buffBulk[WINUSB_EP_DATA_SIZE];

/* USER CODE BEGIN PRIVATE_FUNCTIONS_DECLARATION */

/* USER CODE END PRIVATE_FUNCTIONS_DECLARATION */

/**
  * @}
  */
/* USER CODE BEGIN 0 */
USBD_WinUSB_EnpointsConfig_t winUsbDeviceConfig[WINUSB_DEVICE_EP_COUNT] = {
  {
    .epType = USBD_EP_TYPE_INTR,
    .epAddr = WINUSB_EP_STATE_ADDR,
    .epSize = WINUSB_EP_STATE_SIZE,
    .epInterval = 0x0A,
    .outEvent = NULL,
    .state = USBD_OK,
    .buff = NULL,
    .buffSize = 0
  }, {
    .epType = USBD_EP_TYPE_INTR,
    .epAddr = WINUSB_EP_IN_ADDR,
    .epSize = WINUSB_EP_IN_SIZE,
    .epInterval = 0x01,
    .outEvent = NULL,
    .state = USBD_OK,
    .buff = NULL,
    .buffSize = 0
  }, {
    .epType = USBD_EP_TYPE_INTR,
    .epAddr = WINUSB_EP_CMD_ADDR,
    .epSize = WINUSB_EP_CMD_SIZE,
    .epInterval = 0x01,
    .outEvent = USBD_WinUSB_interruptEvent,
    .state = USBD_OK,
    .buff = buffInterrupt,
    .buffSize = WINUSB_EP_CMD_SIZE
  }, {
    .epType = USBD_EP_TYPE_BULK,
    .epAddr = WINUSB_EP_DATA_ADDR,
    .epSize = WINUSB_EP_DATA_SIZE,
    .epInterval = 0x00,
    .outEvent = USBD_WinUSB_BulkEvent,
    .state = USBD_OK,
    .buff = buffBulk,
    .buffSize = WINUSB_EP_DATA_SIZE
  }
};
/* USER CODE END 0 */

/* Private functions ---------------------------------------------------------*/
static uint8_t USBD_WinUSB_interruptEvent(uint8_t epAddr, uint8_t *buff, uint16_t buffSize) {
  /* USER CODE BEGIN 1 */
  return USBD_OK;
  /* USER CODE END 1 */
}

static uint8_t USBD_WinUSB_BulkEvent(uint8_t epAddr, uint8_t *buff, uint16_t buffSize) {
  /* USER CODE BEGIN 2 */
  return USBD_OK;
  /* USER CODE END 2 */
}

uint8_t winUsbVendorSetupCallback(struct _USBD_HandleTypeDef *pdev , USBD_SetupReqTypedef  *req) {
  /* USER CODE BEGIN 3 */
  return USBD_OK;
  /* USER CODE END 3 */
}

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */

/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */

/**
  * @}
  */

/**
  * @}
  */

