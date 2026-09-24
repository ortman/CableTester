#ifdef _WIN32

#include "../winusbcross.h"

#include <stdio.h>

#include <windows.h>
#include <winusb.h>
#include <setupapi.h>
#include <devguid.h>
#undef LowSpeed
#include <usbioctl.h>

const WinUsbGUID_t winUsbClassGuid = {u"{88BAE032-5A81-49f0-BC3D-A4FF138216D6}"};

typedef struct {
    GUID devGuid;
    HDEVINFO deviceInfo;
    uint32_t foundDevCount;
    DWORD devIndexes[10];
} wuc_data_t;

wuc_t* wuc_init(WinUsbGUID_t guid, int32_t *findCount) {
  wuc_t *wuc = (wuc_t*)malloc(sizeof(wuc_t));
  if (wuc == 0) {
    return (wuc_t*)0;
  }
  wuc_data_t *data = (wuc_data_t*)malloc(sizeof(wuc_data_t));
  if (data == 0) {
    wuc->err = 1;
    return wuc;
  }
  wuc->data = data;
  data->foundDevCount = 0;

  GUID winusbClassGuid;
  if (FAILED(CLSIDFromString(reinterpret_cast<LPCOLESTR>(guid), &data->devGuid)) ||
      FAILED(CLSIDFromString(reinterpret_cast<LPCOLESTR>(winUsbClassGuid), &winusbClassGuid))) {
    wuc->err = 2;
    return wuc;
  }

  HDEVINFO deviceInfo  = SetupDiGetClassDevs(&data->devGuid, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
  if (deviceInfo == INVALID_HANDLE_VALUE) {
    wuc->err = GetLastError();
    return wuc;
  }
  data->deviceInfo = deviceInfo;

  SP_DEVINFO_DATA devInfoData;
  devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
  DWORD devIndex = 0;
  wuc->err = 0;
  while (SetupDiEnumDeviceInfo(deviceInfo, devIndex, &devInfoData)) {
    if (IsEqualGUID(devInfoData.ClassGuid, winusbClassGuid)) {
        data->devIndexes[data->foundDevCount] = devIndex;
        data->foundDevCount++;
        if (data->foundDevCount >= 10) {
            break;
        }
    }
    devIndex++;
  }
  *findCount = data->foundDevCount;
  return wuc;
}

void wuc_deInit(wuc_t* wuc) {
    if (wuc) {
        if (wuc->data) free(wuc->data);
        free(wuc);
    }
}

int32_t wuc_getSerialNumber(wuc_t* wuc, uint32_t idx, wchar_t *str, int32_t *strSize) {
    wuc->err = 1;
    if (wuc == 0 || wuc->data == 0) {
        return -1;
    }
    wuc_data_t *data = (wuc_data_t*) wuc->data;
    if (idx >= data->foundDevCount) {
        return -2;
    }

    SP_DEVINFO_DATA devInfoData;
    devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
    SP_DEVICE_INTERFACE_DATA interfaceData;
    interfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
    if (SetupDiEnumDeviceInterfaces(data->deviceInfo, NULL, &data->devGuid, data->devIndexes[idx], &interfaceData)) {
        CHAR devdetailbuffer[1024];
        PSP_DEVICE_INTERFACE_DETAIL_DATA_W detailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA_W)devdetailbuffer;
        detailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA_W);
        if (SetupDiGetDeviceInterfaceDetailW(data->deviceInfo, &interfaceData, detailData, sizeof(devdetailbuffer), NULL, NULL)) {
            wchar_t *snPid = wcsstr(detailData->DevicePath, L"&pid");
            if (snPid != nullptr) {
                wchar_t *snEnd = wcsrchr(snPid, L'{');
                wchar_t *snBegin = wcschr(snPid, L'#');
                if (snEnd != nullptr && snBegin != nullptr && (snEnd-snBegin)>3) {
                    int32_t size = (int32_t)(snEnd - snBegin) - 2;
                    if (size > *strSize) {
                        return -3;
                    }
                    *strSize = size;
                    wcsncpy(str, snBegin+1, size);
                    str[size] = 0;
                    wuc->err = 0;
                    return size;
                }
            }
        }
    }
    wuc->err = GetLastError();
    return -4;
}

typedef struct {
    HANDLE hDeviceHandle;
    WINUSB_INTERFACE_HANDLE usbHandle;
} wuc_device_win_t;

int32_t wuc_getName(wuc_t* wuc, uint8_t idx, wchar_t *str, int32_t *strSize) {
    if (wuc == 0 || wuc->data == 0) {
        return -1;
    }
    wuc_data_t *data = (wuc_data_t*) wuc->data;
    if (idx >= data->foundDevCount) {
        return -2;
    }

    SP_DEVINFO_DATA devInfoData;
    devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
    if (SetupDiEnumDeviceInfo(data->deviceInfo, data->devIndexes[idx], &devInfoData)) {
       if (SetupDiGetDeviceRegistryPropertyW(data->deviceInfo, &devInfoData, SPDRP_FRIENDLYNAME, NULL, (PBYTE)str, *strSize, (PDWORD)strSize)) {
         return *strSize;
       }
    }
    wuc->err = GetLastError();
    return -3;
}

wuc_device_t* wuc_connect_device(wuc_t* wuc, uint32_t idx) {
  if (wuc == 0 || wuc->data == 0) {
    return NULL;
  }
  wuc_data_t *data = (wuc_data_t*) wuc->data;
  if (idx >= data->foundDevCount) {
    return NULL;
  }
  wuc->err = 0;

  wuc_device_win_t *hWucDev = (wuc_device_win_t*)malloc(sizeof(wuc_device_win_t));
  if (hWucDev == NULL) {
      wuc->err = ERROR_OUTOFMEMORY;
      return NULL;
  }

  SP_DEVICE_INTERFACE_DATA interfaceData;
  interfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
  if (SetupDiEnumDeviceInterfaces(data->deviceInfo, NULL, &data->devGuid, data->devIndexes[idx], &interfaceData)) {
      CHAR devdetailbuffer[512];
      PSP_DEVICE_INTERFACE_DETAIL_DATA_A detailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA_A)devdetailbuffer;
      detailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA_A);
      if (SetupDiGetDeviceInterfaceDetailA(data->deviceInfo, &interfaceData, detailData, sizeof(devdetailbuffer), NULL, NULL)) {
//          printf("DevicePath: %s\n", detailData->DevicePath);
          hWucDev->hDeviceHandle = CreateFileA (detailData->DevicePath,
                                        GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
                                        NULL, OPEN_EXISTING, /*FILE_ATTRIBUTE_NORMAL*/ FILE_FLAG_OVERLAPPED, NULL);

//          printf("hDeviceHandle: %i\n", hWucDev->hDeviceHandle);
          if (hWucDev->hDeviceHandle != INVALID_HANDLE_VALUE) {
              if (WinUsb_Initialize(hWucDev->hDeviceHandle, &hWucDev->usbHandle)) {
//                  printf("WinUsb_Initialize OK %i\n", usbHandle);
//                  BOOL allowPartialReadsVal = FALSE;
//                  if (!WinUsb_SetPipePolicy(hWucDev->usbHandle, 0x82, ALLOW_PARTIAL_READS, sizeof(BOOL), &allowPartialReadsVal)) {
////                    printf("WinUsb_SetPipePolicy ALLOW_PARTIAL_READS error.\n");
//                  } else {
////                    printf("WinUsb_SetPipePolicy ALLOW_PARTIAL_READS ok.\n");
//                  }

//                  UCHAR speed;
//                  ULONG lenn = 1;
//                  if (WinUsb_QueryDeviceInformation(hWucDev->usbHandle, DEVICE_SPEED, &lenn, &speed)) {
//                      printf("WinUsb_QueryDeviceInformation SPEED OK: %i\n", speed);
//                      USB_INTERFACE_DESCRIPTOR ifaceDescriptor;
//                      if (WinUsb_QueryInterfaceSettings(hWucDev->usbHandle, 0, &ifaceDescriptor)) {
//                          printf("WinUsb_QueryInterface %i (%i ep)\n", ifaceDescriptor.bInterfaceNumber, ifaceDescriptor.bNumEndpoints);
//                          WINUSB_PIPE_INFORMATION pipeInfo;
//                          for(int i=0;i<ifaceDescriptor.bNumEndpoints;i++) {
//                              if (WinUsb_QueryPipe(usbHandle,
//                               0,
//                               (UCHAR) i,
//                               &pipeInfo)) {
//                                  printf("EP %i: addr:%02x, type:%i\n", i, pipeInfo.PipeId, pipeInfo.PipeType);
//                              } else {
//                                  printf("EP %i error\n", i);
//                              }
//                          }
                          //return (wuc_device_t*) usbHandle;
//                      }
//                  }
                  wuc->err = 0;
                  return (wuc_device_t*)hWucDev;
              }
          }
      }
  }
  wuc->err = GetLastError();
  free(hWucDev);
  return NULL;
}

int32_t wuc_disconnect_device(wuc_device_t *dev) {
    if (dev == 0) {
        return -1;
    }
    if (WinUsb_Free(((wuc_device_win_t*)dev)->usbHandle)) {
        if (CloseHandle(((wuc_device_win_t*)dev)->hDeviceHandle)) {
            free(dev);
            return 0;
        }
        return -3;
    }
    return -2;
}

int32_t wuc_control_transfer(wuc_device_t *dev, WinUsbSetup_t *setup, uint8_t *buf, uint32_t size, uint32_t timeout) {
    if (dev == 0) {
        return -1;
    }
    WINUSB_INTERFACE_HANDLE usbHandle = ((wuc_device_win_t*)dev)->usbHandle;
    if (usbHandle == 0) {
        return -2;
    }
    int32_t transferSize;
    WINUSB_SETUP_PACKET setupPack = {
        setup->bmRequest,
        setup->bRequest,
        setup->wValue,
        setup->wIndex,
        setup->wLength
    };
    if (WinUsb_ControlTransfer(usbHandle, setupPack, buf, size, (PULONG)&transferSize, NULL)) {
        return transferSize;
    }
    return -3;
}

int32_t wuc_bulk_read(wuc_device_t* dev, uint8_t ep, uint8_t *buf, uint32_t size, uint32_t timeout) {
    if (dev == 0) {
        return -1;
    }
    WINUSB_INTERFACE_HANDLE usbHandle = ((wuc_device_win_t*)dev)->usbHandle;
    if (usbHandle == 0) {
        return -2;
    }
    int32_t transferSize;
    if (WinUsb_ReadPipe(usbHandle, ep, buf, size, (PULONG)&transferSize, NULL)) {
        return transferSize;
    }
    return -3;
}

int32_t wuc_bulk_write(wuc_device_t* dev, uint8_t ep, uint8_t *buf, uint32_t size, uint32_t timeout) {
    if (dev == 0) {
        return -1;
    }
    WINUSB_INTERFACE_HANDLE usbHandle = ((wuc_device_win_t*)dev)->usbHandle;
    if (usbHandle == 0) {
        return -2;
    }
    int32_t transferSize;
//    WinUsb_SetPipePolicy((WINUSB_INTERFACE_HANDLE)dev, ep, PIPE_TRANSFER_TIMEOUT, sizeof(ULONG), &timeout);
//    SetLastError(0);
    if (WinUsb_WritePipe(usbHandle, ep, buf, size, (PULONG)&transferSize, NULL)) {
        return transferSize;
    }
    return -3;
}

int32_t wuc_interrupt_read(wuc_device_t* dev, uint8_t ep, uint8_t *buf, uint32_t size, uint32_t timeout) {
    if (dev == 0) {
        return -1;
    }
    WINUSB_INTERFACE_HANDLE usbHandle = ((wuc_device_win_t*)dev)->usbHandle;
    if (usbHandle == 0) {
        return -2;
    }
    int32_t transferSize;
    WinUsb_SetPipePolicy(usbHandle, ep, PIPE_TRANSFER_TIMEOUT, sizeof(ULONG), &timeout);
//    SetLastError(0);
    if (WinUsb_ReadPipe(usbHandle, ep, buf, size, (PULONG)&transferSize, NULL)) {
//        printf("LastErr: %i\n", GetLastError());
//        if (WinUsb_GetOverlappedResult((WINUSB_INTERFACE_HANDLE)dev, ))
        return transferSize;
    }
    return -3;
}

int32_t wuc_interrupt_write(wuc_device_t* dev, uint8_t ep, uint8_t *buf, uint32_t size, uint32_t timeout) {
    if (dev == 0) {
        return -1;
    }
    WINUSB_INTERFACE_HANDLE usbHandle = ((wuc_device_win_t*)dev)->usbHandle;
    if (usbHandle == 0) {
        return -2;
    }
    int32_t transferSize;
    if (WinUsb_WritePipe(usbHandle, ep, buf, size, (PULONG)&transferSize, NULL)) {
        return transferSize;
    }
    return -3;
}

#endif