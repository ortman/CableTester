#ifndef WINUSBCROSS_H
#define WINUSBCROSS_H

#include <stdint.h>

using WinUsbGUID_t = char16_t[39];

typedef struct {
  uint8_t   bmRequest;
  uint8_t   bRequest;
  uint16_t  wValue;
  uint16_t  wIndex;
  uint16_t  wLength;
} WinUsbSetup_t;

typedef void* wuc_device_t;

typedef struct {
  uint32_t err;
  void *data;
} wuc_t;

#ifdef __linux__
  #define WINUSBCROSS_EXPORT
#elif WINDOWS
  #define WINUSBCROSS_EXPORT
#else
  #define WINUSBCROSS_EXPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif

  WINUSBCROSS_EXPORT wuc_t* wuc_init(WinUsbGUID_t guid, int32_t *findCount);
  WINUSBCROSS_EXPORT void wuc_deInit(wuc_t* wuc);

  WINUSBCROSS_EXPORT int32_t wuc_getSerialNumber(wuc_t* wuc, uint32_t idx, wchar_t *str, int32_t *strSize);
  WINUSBCROSS_EXPORT int32_t wuc_getName(wuc_t* wuc, uint8_t idx, wchar_t *str, int32_t *strSize);

  WINUSBCROSS_EXPORT wuc_device_t* wuc_connect_device(wuc_t* wuc, uint32_t idx);
  WINUSBCROSS_EXPORT int32_t wuc_disconnect_device(wuc_device_t *dev);
  WINUSBCROSS_EXPORT int32_t wuc_control_transfer(wuc_device_t* dev, WinUsbSetup_t *setup, uint8_t *buf, uint32_t size, uint32_t timeout);
  WINUSBCROSS_EXPORT int32_t wuc_bulk_read(wuc_device_t* dev, uint8_t ep, uint8_t *buf, uint32_t size, uint32_t timeout);
  WINUSBCROSS_EXPORT int32_t wuc_bulk_write(wuc_device_t* dev, uint8_t ep, uint8_t *buf, uint32_t size, uint32_t timeout);
  WINUSBCROSS_EXPORT int32_t wuc_interrupt_read(wuc_device_t* dev, uint8_t ep, uint8_t *buf, uint32_t size, uint32_t timeout);
  WINUSBCROSS_EXPORT int32_t wuc_interrupt_write(wuc_device_t* dev, uint8_t ep, uint8_t *buf, uint32_t size, uint32_t timeout);

#ifdef __cplusplus
}
#endif

#endif // WINUSBCROSS_H
