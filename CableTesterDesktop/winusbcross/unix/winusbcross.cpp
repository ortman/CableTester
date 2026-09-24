#ifdef __linux__

#include "../winusbcross.h"
#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

#define USBD_IDX_MSFT_STR      0xEE
#define USBD_MSFT_VENDOR_ID    0xAE

#pragma pack(push, 4)
typedef struct {
    uint32_t length;
    uint16_t bcdUSB;
    uint16_t wIndex;
    uint8_t sectionNum;
    uint8_t reserved[7];
    uint8_t interfaceNum;
    uint8_t reserved2;
    uint8_t compatibleId[8];
    uint8_t subCompatibleId[8];
} wuc_winusb_feature_descriptor_t;

typedef struct {
    uint32_t length; // 0
    uint16_t bcdUSB; // 4
    uint16_t wIndex; // 6
    uint8_t sectionNum; // 8
    uint8_t reserved1; // 9
    uint16_t dataLength; // 10
    uint16_t reserved2; // 12
    uint8_t propType; // 14
    uint8_t reserved3[3]; // 15
    uint8_t property[512-18]; //18
} wuc_winusb_property_descriptor_t;

#define WUC_MAX_DEVICES 100

typedef struct {
    libusb_device* devices[WUC_MAX_DEVICES];
    libusb_context* context;
    libusb_device** list;
    int32_t findCount;
    ssize_t count;
} wuc_data_t;

#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
    uint16_t wSize;               // 0x0028
    char16_t PropertyName[20];    // "DeviceInterfaceGUID" + null (40 bytes)
    uint32_t dwPropertyDataLength; // 76 ?
    char16_t PropertyData[39];    // "{GUID}" + null (78 байт)
} MS_Descriptor_t;
#pragma pack(pop)

#include <stdlib.h>

void wuc_dump(uint8_t *buf, uint32_t size) {
    while (size--) {
        printf("%02x ", *buf++);
        if (size % 10 == 0) {
            printf("\n");
        }
    }
}

wuc_t* wuc_init(WinUsbGUID_t guid, int32_t *findCount) {
    wuc_t* wuc = (wuc_t*) malloc(sizeof(wuc_t));
    if (wuc == nullptr) {
        return wuc;
    }
    wuc_data_t *wuc_data = (wuc_data_t*) malloc(sizeof(wuc_data_t));
    wuc->data = wuc_data;
    if (wuc_data == nullptr) {
        wuc->err = 1;
        return wuc;
    }
    MS_Descriptor_t devGuid = {
        .wSize = 0x0028,
        .PropertyName = u"DeviceInterfaceGUID",
        .dwPropertyDataLength = 76 // Why is not 78?
    };
    memcpy(devGuid.PropertyData, guid, sizeof(WinUsbGUID_t));
    wuc_data->context = nullptr;
    wuc_data->list = nullptr;
    wuc_data->count = 0;
    wuc->err = 0;
    int rc = 0;
    rc = libusb_init(&wuc_data->context);
    int32_t _findCount = 0;
    wuc_data->count = libusb_get_device_list(wuc_data->context, &wuc_data->list);
    for (size_t idx = 0; idx < wuc_data->count; ++idx) {
        libusb_device *device = wuc_data->list[idx];
        libusb_device_descriptor devDesc = {0};

        rc = libusb_get_device_descriptor(device, &devDesc);

        libusb_device_handle *handle = nullptr;
        unsigned char strDesc[200];
        int ret;
        if ((ret = libusb_open(device, &handle)) == LIBUSB_SUCCESS) {
            ret = libusb_get_string_descriptor_ascii(handle, USBD_IDX_MSFT_STR, strDesc, 200);
            if ((ret == 8) && (strcmp((const char *)strDesc, "MSFT100?")) == 0) {
                wuc_winusb_feature_descriptor_t winusbFeatureDesc;
                // get header length
                ret = libusb_control_transfer(handle, LIBUSB_ENDPOINT_IN | LIBUSB_RECIPIENT_DEVICE | LIBUSB_REQUEST_TYPE_VENDOR, USBD_MSFT_VENDOR_ID, 0x0000, 0x0004, (uint8_t*)&winusbFeatureDesc, 0x10, 1000);
                if (ret == 0x10) {
                    uint32_t length = *(uint32_t*)&winusbFeatureDesc;
                    if (length > sizeof (wuc_winusb_feature_descriptor_t)) {
                        length = sizeof(wuc_winusb_feature_descriptor_t);
                    }
                    // get descriptor
                    ret = libusb_control_transfer(handle, LIBUSB_ENDPOINT_IN | LIBUSB_RECIPIENT_DEVICE | LIBUSB_REQUEST_TYPE_VENDOR, USBD_MSFT_VENDOR_ID, 0x0000, 0x0004, (uint8_t*)&winusbFeatureDesc, length, 1000);
                    if ((ret == length) && (strcmp((const char *)winusbFeatureDesc.compatibleId, "WINUSB\0\0")) == 0) {
                        wuc_winusb_property_descriptor_t winusbPropertyDesc;
                        ret = libusb_control_transfer(handle, LIBUSB_ENDPOINT_IN | LIBUSB_RECIPIENT_INTERFACE | LIBUSB_REQUEST_TYPE_VENDOR, USBD_MSFT_VENDOR_ID, 0x0000, 0x0005, (uint8_t*)&winusbPropertyDesc, 0x0A, 1000);
                        if (ret == 0x0A) {
                            length = *(uint32_t*)&winusbPropertyDesc;
                            if (length > sizeof (wuc_winusb_property_descriptor_t)) {
                                length = sizeof(wuc_winusb_property_descriptor_t);
                            }
                            ret = libusb_control_transfer(handle, LIBUSB_ENDPOINT_IN | LIBUSB_RECIPIENT_INTERFACE | LIBUSB_REQUEST_TYPE_VENDOR, USBD_MSFT_VENDOR_ID, 0x0000, 0x0005, (uint8_t*)&winusbPropertyDesc, length, 1000);
                            if (ret == length) {
                                // comparate winusb GUID
                                if (memcmp(&devGuid, winusbPropertyDesc.property, sizeof(MS_Descriptor_t) - 2) == 0) {
                                    wuc_data->devices[_findCount] = device;
                                    ++_findCount;
                                }
                            }
                        }
                    }
                }
            }
            libusb_close(handle);
        }
        if (_findCount >= WUC_MAX_DEVICES) {
            break;
        }
    }
    *findCount = _findCount;
    wuc_data->findCount = _findCount;
    return wuc;
}

void wuc_deInit(wuc_t* wuc) {
    if (wuc != nullptr) {
        wuc_data_t *wuc_data = (wuc_data_t*)wuc->data;
        if (wuc_data != nullptr) {
            libusb_free_device_list(wuc_data->list, wuc_data->count);
            libusb_exit(wuc_data->context);
//            wuc_data->findCount = 0;
            free(wuc_data);
        }
        free(wuc);
    }
}

int32_t wuc_getSerialNumber(wuc_t* wuc, uint32_t idx, wchar_t *str, int32_t *strSize) {
    int ret;
    if (wuc == nullptr) {
        return -1;
    }
    wuc_data_t *wuc_data = (wuc_data_t*)wuc->data;
    if (wuc_data == nullptr) {
        return -2;
    }
    if (idx >= wuc_data->findCount) {
        return -3;
    }
    libusb_device *device = wuc_data->devices[idx];
    if (device == nullptr) {
        return -4;
    }
    libusb_device_descriptor devDesc = {0};
    if (libusb_get_device_descriptor(device, &devDesc) != LIBUSB_SUCCESS) {
        return -5;
    }
    uint8_t snIdx = devDesc.iSerialNumber;
    unsigned char strDesc[200];
    libusb_device_handle *handle = NULL;
    if ((ret = libusb_open(device, &handle)) == LIBUSB_SUCCESS) {
        ret = libusb_get_string_descriptor_ascii(handle, snIdx, strDesc, 200);
        if (ret <= 0) {
            libusb_close(handle);
            return -6;
        }
        strDesc[ret++] = 0x00;
        if (*strSize < (ret*4)) {
            ret = *strSize / 4;
        }
        *strSize = ret;
        mbstowcs((wchar_t*)str, (const char*)strDesc, ret);
        libusb_close(handle);
    }
    return ret;
}

int32_t wuc_getName(wuc_t* wuc, uint8_t idx, wchar_t *str, int32_t *strSize) {
    int ret, ret2;
    if (wuc == nullptr) {
        return -1;
    }
    wuc_data_t *wuc_data = (wuc_data_t*)wuc->data;
    if (wuc_data == nullptr) {
        return -2;
    }
    if (idx >= wuc_data->findCount) {
        return -3;
    }
    libusb_device *device = wuc_data->devices[idx];
//    printf("sn: %u\n", device);
    if (device == nullptr) {
        return -4;
    }
    libusb_device_descriptor devDesc = {0};
    if (libusb_get_device_descriptor(device, &devDesc) != LIBUSB_SUCCESS) {
        return -5;
    }
    uint8_t iManufacturer = devDesc.iManufacturer;
    uint8_t iProduct = devDesc.iProduct;
    unsigned char strDesc[250];
    libusb_device_handle *handle = NULL;
    if ((ret = libusb_open(device, &handle)) == LIBUSB_SUCCESS) {
        ret = libusb_get_string_descriptor_ascii(handle, iManufacturer, strDesc, 250);
        if (ret <= 0) {
            libusb_close(handle);
            return -6;
        }
        strDesc[ret++] = ' ';

        ret2 = libusb_get_string_descriptor_ascii(handle, iProduct, &strDesc[ret], 250-ret);
        if (ret2 <= 0) {
            libusb_close(handle);
            return -7;
        }
        ret = ret+ret2+1;
        strDesc[ret] = '\0';

        if (*strSize < (ret*4)) {
            ret = *strSize / 4;
        }
        mbstowcs((wchar_t*)str, (const char*)strDesc, ret);
        libusb_close(handle);
    }
    return ret;
}

wuc_device_t* wuc_connect_device(wuc_t* wuc, uint32_t idx) {
    if (wuc == nullptr) {
        return nullptr;
    }
    wuc_data_t *wuc_data = (wuc_data_t*)wuc->data;
    if (wuc_data == nullptr) {
        return nullptr;
    }
    if (idx >= wuc_data->findCount) {
        return nullptr;
    }
    libusb_device *device = wuc_data->devices[idx];
    if (device == nullptr) {
        return nullptr;
    }
    libusb_device_handle *handle = nullptr;
    if (libusb_open(device, &handle) == LIBUSB_SUCCESS) {
        return (wuc_device_t*)handle;
    }
    return nullptr;
}

int32_t wuc_disconnect_device(wuc_device_t *dev) {
    libusb_close((libusb_device_handle *)dev);
    return 0;
}

int32_t wuc_control_transfer(wuc_device_t* dev, WinUsbSetup_t *setup, uint8_t *buf, uint32_t size, uint32_t timeout) {
    return libusb_control_transfer((libusb_device_handle *)dev, setup->bmRequest, setup->bRequest, setup->wValue, setup->wIndex, buf, size, timeout);
}

int32_t wuc_bulk_read(wuc_device_t* dev, uint8_t ep, uint8_t *buf, uint32_t size, uint32_t timeout) {
    if ((ep & LIBUSB_ENDPOINT_DIR_MASK) != LIBUSB_ENDPOINT_IN) {
        return -21;
    }
    int32_t transferedLength = -22;
    int32_t ret = libusb_bulk_transfer((libusb_device_handle *)dev, ep, buf, size, &transferedLength, timeout);
    if (ret < 0) {
        return ret;
    }
    return transferedLength;
}

int32_t wuc_bulk_write(wuc_device_t* dev, uint8_t ep, uint8_t *buf, uint32_t size, uint32_t timeout) {
    if ((ep & LIBUSB_ENDPOINT_DIR_MASK) != LIBUSB_ENDPOINT_OUT) {
        return -21;
    }
    int32_t transferedLength = -22;
    int32_t ret = libusb_bulk_transfer((libusb_device_handle *)dev, ep, buf, size, &transferedLength, timeout);
    if (ret < 0) {
        return ret;
    }
    return transferedLength;
}

int32_t wuc_interrupt_read(wuc_device_t* dev, uint8_t ep, uint8_t *buf, uint32_t size, uint32_t timeout) {
    if ((ep & LIBUSB_ENDPOINT_DIR_MASK) != LIBUSB_ENDPOINT_IN) {
        return -21;
    }
    int32_t transferedLength = -22;
    int32_t ret = libusb_interrupt_transfer((libusb_device_handle *)dev, ep, buf, size, &transferedLength, timeout);
    if (ret < 0) {
        return ret;
    }
    return transferedLength;
}

int32_t wuc_interrupt_write(wuc_device_t* dev, uint8_t ep, uint8_t *buf, uint32_t size, uint32_t timeout) {
    if ((ep & LIBUSB_ENDPOINT_DIR_MASK) != LIBUSB_ENDPOINT_OUT) {
        return -21;
    }
    int32_t transferedLength = -22;
    int32_t ret = libusb_interrupt_transfer((libusb_device_handle *)dev, ep, buf, size, &transferedLength, timeout);
    if (ret < 0) {
        return ret;
    }
    return transferedLength;
}

#endif