/*
 * usbd_winusb_if.c
 *
 *  Created on: 29 ���. 2018 �.
 *      Author: ortman
 */

#include "usbd_winusb_if.h"

static uint8_t USBD_WinUSB_interruptEvent(uint8_t epAddr, uint8_t *buff, uint16_t buffSize);
static uint8_t USBD_WinUSB_BulkEvent(uint8_t epAddr, uint8_t *buff, uint16_t buffSize);

extern USBD_HandleTypeDef hUsbDeviceFS;

uint8_t buffInterrupt[WINUSB_EP_CMD_SIZE];
uint8_t buffBulk[WINUSB_EP_DATA_SIZE];

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

static uint8_t USBD_WinUSB_interruptEvent(uint8_t epAddr, uint8_t *buff, uint16_t buffSize) {
  //my_data_in_t *data = (my_data_in_t*)buff;
  return USBD_OK;
}

static uint8_t USBD_WinUSB_BulkEvent(uint8_t epAddr, uint8_t *buff, uint16_t buffSize) {
  return USBD_OK;
}

uint8_t winUsbVendorSetupCallback(struct _USBD_HandleTypeDef *pdev , USBD_SetupReqTypedef  *req) {
  // if (req->bRequest == 0x10) {
  //   uint16_t blockCount = (sizeof(smc_state_t) + WINUSB_EP_STATE_SIZE - 1) / WINUSB_EP_STATE_SIZE;
  //   if (req->wValue < blockCount) {
  //     USBD_WinUSB_Send(&hUsbDeviceFS, WINUSB_EP_STATE_ADDR, ((uint8_t*)&data) + req->wValue * WINUSB_EP_STATE_SIZE, WINUSB_EP_STATE_SIZE);
  //   } else {
  //     //Log("ERR: Get state (%i/%i)\n", req->wValue, blockCount);
  //   }
  // }
  return USBD_OK;
}

