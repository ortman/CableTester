/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : App/usbd_desc.c
  * @version        : v2.0_Cube
  * @brief          : This file implements the USB device descriptors.
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
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_conf.h"

/* USER CODE BEGIN INCLUDE */

/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @{
  */

/** @addtogroup USBD_DESC
  * @{
  */

/** @defgroup USBD_DESC_Private_TypesDefinitions USBD_DESC_Private_TypesDefinitions
  * @brief Private types.
  * @{
  */

/* USER CODE BEGIN PRIVATE_TYPES */

/* USER CODE END PRIVATE_TYPES */

/**
  * @}
  */

/** @defgroup USBD_DESC_Private_Defines USBD_DESC_Private_Defines
  * @brief Private defines.
  * @{
  */

#define USBD_VID     0x483
#define USBD_LANGID_STRING     1033
#define USBD_MANUFACTURER_STRING     "Ortman"
#define USBD_PID_FS     0x5740
#define USBD_PRODUCT_STRING_FS     "CableTester"
#define USBD_CONFIGURATION_STRING_FS     "CDC Config"
#define USBD_INTERFACE_STRING_FS     "CDC Interface"

/* USER CODE BEGIN PRIVATE_DEFINES */
#define USBD_MSFT_STRING_FS     "MSFT100"
#define USBD_MSFT_VENDOR_ID     0xAE
#define USBD_MSFT_PROP_DI_GUID_NAME	"DeviceInterfaceGUID"
#define USBD_MSFT_PROP_DI_GUID_VAL	"{92cf51ca-392a-4db5-9bff-46d0e0062c1b}\0"
#define USBD_MSFT_PROP_DI_GUID_VAL_SIZ   39

#define USB_SIZ_MSID_FD				0x28
#define USB_SIZ_MSID_EP				0x8e
/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/* USER CODE BEGIN 0 */
uint8_t *     USBD_FS_MsftStrDescriptor( USBD_SpeedTypeDef speed , uint16_t *length);
uint8_t *     USBD_FS_MSIDFeatureDescriptor( USBD_SpeedTypeDef speed , USBD_SetupReqTypedef  *req , uint16_t *length);
#if (USBD_MSFT_ENABLED == 1)
	#if defined ( __ICCARM__ ) /*!< IAR Compiler */
	  #pragma data_alignment=4
	#endif
	__ALIGN_BEGIN  uint8_t USBD_MSID_FeatureDesc[USB_SIZ_MSID_FD] __ALIGN_END =
	{
	  USB_SIZ_MSID_FD, 0x00, 0x00, 0x00,
	#if (USBD_LPM_ENABLED == 1)
	  0x01, 0x02,                       /*bcdUSB */ /* changed to USB version 2.01
												   in order to support LPM L1 suspend
												   resume test of USBCV3.0*/
	#else
	  0x00, 0x01,                      /* bcdUSB */
	#endif
	  0x04, 0x00, /* wIndex */
	  0x01, /* number of section */
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 7 bytes reserved */
	  0x00,  /* interface number */
	  0x01, /* reserved */
	  0x57, 0x49, 0x4e, 0x55, 0x53, 0x42, 0x00, 0x00, /* 8 bytes Compatible ID "WINUSB\0\0" */
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 8 bytes sub-compatible ID */
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00 /* 6 bytes reserved */
	};

	#if defined ( __ICCARM__ ) /*!< IAR Compiler */
	  #pragma data_alignment=4
	#endif
#endif /* USBD_MSFT_ENABLED */
/* USER CODE END 0 */

/** @defgroup USBD_DESC_Private_Macros USBD_DESC_Private_Macros
  * @brief Private macros.
  * @{
  */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_DESC_Private_FunctionPrototypes USBD_DESC_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */

static void Get_SerialNum(void);
static void IntToUnicode(uint32_t value, uint8_t * pbuf, uint8_t len);

/**
  * @}
  */

/** @defgroup USBD_DESC_Private_FunctionPrototypes USBD_DESC_Private_FunctionPrototypes
  * @brief Private functions declaration for FS.
  * @{
  */

uint8_t * USBD_FS_DeviceDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t * USBD_FS_LangIDStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t * USBD_FS_ManufacturerStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t * USBD_FS_ProductStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t * USBD_FS_SerialStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t * USBD_FS_ConfigStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);
uint8_t * USBD_FS_InterfaceStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length);

/**
  * @}
  */

/** @defgroup USBD_DESC_Private_Variables USBD_DESC_Private_Variables
  * @brief Private variables.
  * @{
  */

USBD_DescriptorsTypeDef FS_Desc =
{
  USBD_FS_DeviceDescriptor
, USBD_FS_LangIDStrDescriptor
, USBD_FS_ManufacturerStrDescriptor
, USBD_FS_ProductStrDescriptor
, USBD_FS_SerialStrDescriptor
, USBD_FS_ConfigStrDescriptor
, USBD_FS_InterfaceStrDescriptor
#if (USBD_MSFT_ENABLED == 1)
  ,USBD_FS_MsftStrDescriptor
  ,USBD_FS_MSIDFeatureDescriptor
  ,USBD_MSFT_VENDOR_ID
#endif
};

#if defined ( __ICCARM__ ) /* IAR Compiler */
  #pragma data_alignment=4
#endif /* defined ( __ICCARM__ ) */
/** USB standard device descriptor. */
__ALIGN_BEGIN uint8_t USBD_FS_DeviceDesc[USB_LEN_DEV_DESC] __ALIGN_END =
{
  0x12,                       /*bLength */
  USB_DESC_TYPE_DEVICE,       /*bDescriptorType*/
  0x00,                       /*bcdUSB */
  0x02,
  0x00,                       /*bDeviceClass*/
  0x00,                       /*bDeviceSubClass*/
  0x00,                       /*bDeviceProtocol*/
  USB_MAX_EP0_SIZE,           /*bMaxPacketSize*/
  LOBYTE(USBD_VID),           /*idVendor*/
  HIBYTE(USBD_VID),           /*idVendor*/
  LOBYTE(USBD_PID_FS),        /*idProduct*/
  HIBYTE(USBD_PID_FS),        /*idProduct*/
  0x00,                       /*bcdDevice rel. 2.00*/
  0x02,
  USBD_IDX_MFC_STR,           /*Index of manufacturer  string*/
  USBD_IDX_PRODUCT_STR,       /*Index of product string*/
  USBD_IDX_SERIAL_STR,        /*Index of serial number string*/
  USBD_MAX_NUM_CONFIGURATION  /*bNumConfigurations*/
};

/* USB_DeviceDescriptor */

/**
  * @}
  */

/** @defgroup USBD_DESC_Private_Variables USBD_DESC_Private_Variables
  * @brief Private variables.
  * @{
  */

#if defined ( __ICCARM__ ) /* IAR Compiler */
  #pragma data_alignment=4
#endif /* defined ( __ICCARM__ ) */

/** USB lang identifier descriptor. */
__ALIGN_BEGIN uint8_t USBD_LangIDDesc[USB_LEN_LANGID_STR_DESC] __ALIGN_END =
{
     USB_LEN_LANGID_STR_DESC,
     USB_DESC_TYPE_STRING,
     LOBYTE(USBD_LANGID_STRING),
     HIBYTE(USBD_LANGID_STRING)
};

#if defined ( __ICCARM__ ) /* IAR Compiler */
  #pragma data_alignment=4
#endif /* defined ( __ICCARM__ ) */
/* Internal string descriptor. */
__ALIGN_BEGIN uint8_t USBD_StrDesc[USBD_MAX_STR_DESC_SIZ] __ALIGN_END;

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4
#endif
__ALIGN_BEGIN uint8_t USBD_StringSerial[USB_SIZ_STRING_SERIAL] __ALIGN_END = {
  USB_SIZ_STRING_SERIAL,
  USB_DESC_TYPE_STRING,
};

/**
  * @}
  */

/** @defgroup USBD_DESC_Private_Functions USBD_DESC_Private_Functions
  * @brief Private functions.
  * @{
  */

/**
  * @brief  Return the device descriptor
  * @param  speed : Current device speed
  * @param  length : Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t * USBD_FS_DeviceDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  UNUSED(speed);
  *length = sizeof(USBD_FS_DeviceDesc);
  return USBD_FS_DeviceDesc;
}

/**
  * @brief  Return the LangID string descriptor
  * @param  speed : Current device speed
  * @param  length : Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t * USBD_FS_LangIDStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  UNUSED(speed);
  *length = sizeof(USBD_LangIDDesc);
  return USBD_LangIDDesc;
}

/**
  * @brief  Return the product string descriptor
  * @param  speed : Current device speed
  * @param  length : Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t * USBD_FS_ProductStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  if(speed == 0)
  {
    USBD_GetString((uint8_t *)USBD_PRODUCT_STRING_FS, USBD_StrDesc, length);
  }
  else
  {
    USBD_GetString((uint8_t *)USBD_PRODUCT_STRING_FS, USBD_StrDesc, length);
  }
  return USBD_StrDesc;
}

/**
  * @brief  Return the manufacturer string descriptor
  * @param  speed : Current device speed
  * @param  length : Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t * USBD_FS_ManufacturerStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  UNUSED(speed);
  USBD_GetString((uint8_t *)USBD_MANUFACTURER_STRING, USBD_StrDesc, length);
  return USBD_StrDesc;
}

/**
  * @brief  Return the serial number string descriptor
  * @param  speed : Current device speed
  * @param  length : Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t * USBD_FS_SerialStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  UNUSED(speed);
  *length = USB_SIZ_STRING_SERIAL;

  /* Update the serial number string descriptor with the data from the unique
   * ID */
  Get_SerialNum();
  /* USER CODE BEGIN USBD_FS_SerialStrDescriptor */
  //USBD_GetString((uint8_t *)USBD_MANUFACTURER_STRING, USBD_StrDesc, length);

  /* USER CODE END USBD_FS_SerialStrDescriptor */
  return (uint8_t *) USBD_StringSerial;
}

/**
  * @brief  Return the configuration string descriptor
  * @param  speed : Current device speed
  * @param  length : Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t * USBD_FS_ConfigStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  if(speed == USBD_SPEED_HIGH)
  {
    USBD_GetString((uint8_t *)USBD_CONFIGURATION_STRING_FS, USBD_StrDesc, length);
  }
  else
  {
    USBD_GetString((uint8_t *)USBD_CONFIGURATION_STRING_FS, USBD_StrDesc, length);
  }
  return USBD_StrDesc;
}

/**
  * @brief  Return the interface string descriptor
  * @param  speed : Current device speed
  * @param  length : Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t * USBD_FS_InterfaceStrDescriptor(USBD_SpeedTypeDef speed, uint16_t *length)
{
  if(speed == 0)
  {
    USBD_GetString((uint8_t *)USBD_INTERFACE_STRING_FS, USBD_StrDesc, length);
  }
  else
  {
    USBD_GetString((uint8_t *)USBD_INTERFACE_STRING_FS, USBD_StrDesc, length);
  }
  return USBD_StrDesc;
}

/**
  * @brief  Create the serial number string descriptor
  * @param  None
  * @retval None
  */
static void Get_SerialNum(void)
{
  uint32_t deviceserial0;
  uint32_t deviceserial1;
  uint32_t deviceserial2;

  deviceserial0 = *(uint32_t *) DEVICE_ID1;
  deviceserial1 = *(uint32_t *) DEVICE_ID2;
  deviceserial2 = *(uint32_t *) DEVICE_ID3;

  deviceserial0 += deviceserial2;

  if (deviceserial0 != 0)
  {
    IntToUnicode(deviceserial0, &USBD_StringSerial[2], 8);
    IntToUnicode(deviceserial1, &USBD_StringSerial[18], 4);
  }
}

/**
  * @brief  Convert Hex 32Bits value into char
  * @param  value: value to convert
  * @param  pbuf: pointer to the buffer
  * @param  len: buffer length
  * @retval None
  */
static void IntToUnicode(uint32_t value, uint8_t * pbuf, uint8_t len)
{
  uint8_t idx = 0;

  for (idx = 0; idx < len; idx++)
  {
    if (((value >> 28)) < 0xA)
    {
      pbuf[2 * idx] = (value >> 28) + '0';
    }
    else
    {
      pbuf[2 * idx] = (value >> 28) + 'A' - 10;
    }

    value = value << 4;

    pbuf[2 * idx + 1] = 0;
  }
}

#if (USBD_MSFT_ENABLED == 1)
uint8_t *USBD_FS_MsftStrDescriptor( USBD_SpeedTypeDef speed , uint16_t *length)
{
  if(speed == 0)
  {
	  USBD_GetString ((uint8_t *)USBD_MSFT_STRING_FS, USBD_StrDesc, length);
  }
  else
  {
	  USBD_GetString ((uint8_t *)USBD_MSFT_STRING_FS, USBD_StrDesc, length);
  }
  *(USBD_StrDesc+*length) = USBD_MSFT_VENDOR_ID;
  *(USBD_StrDesc+*length+1) = 0x00;
  *length = *length + 2;
  *USBD_StrDesc = *length;
  return USBD_StrDesc;
}

uint8_t *USBD_FS_MSIDFeatureDescriptor( USBD_SpeedTypeDef speed , USBD_SetupReqTypedef  *req , uint16_t *length) {
  if ((req->bmRequest == USB_REQ_RECIPIENT_MS_FD) && req->wIndex == 0x0004) {
    *length = sizeof(USBD_MSID_FeatureDesc);
    return (uint8_t*)USBD_MSID_FeatureDesc;
  } else if ((req->bmRequest == USB_REQ_RECIPIENT_MS_EP) && req->wIndex == 0x0005/* && req->wValue == 0*/) {
	  USBD_MSFT_GetExtendedProp(REG_SZ, USBD_MSFT_PROP_DI_GUID_NAME, USBD_MSFT_PROP_DI_GUID_VAL, USBD_MSFT_PROP_DI_GUID_VAL_SIZ, USBD_StrDesc, length);
  } else {
    *length = 0;
  }
  return USBD_StrDesc;
}

#endif
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

