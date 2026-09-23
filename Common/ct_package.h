/*
 * ct_package.h
 *
 * Test package: the flat description of a cable which is stored in the tester.
 * Created by CableTesterDesktop from the .cbl file, used by CableTesterFirmware.
 * All values are little-endian, structures are packed.
 *
 * Layout:
 *   CtPkgHeader
 *   CtPkgPin     pins[CT_PKG_PIN_COUNT]   (index 0 = slot pin 1)
 *   CtPkgWire    wires[header.wireCount]
 *
 * crc32 is CRC-32 (zlib: poly 0xEDB88320 reflected, init 0xFFFFFFFF, final xor 0xFFFFFFFF)
 * of the whole package calculated with the crc32 field set to 0.
 */

#ifndef CT_PACKAGE_H_
#define CT_PACKAGE_H_

#include <stdint.h>

#define CT_PKG_MAGIC          "CTPK"
#define CT_PKG_VERSION        1
#define CT_PKG_PIN_COUNT      60      /* slot pins D1..D60 */
#define CT_PKG_LEFT_PIN_MAX   30      /* left cable end: pins 1..30, right end: 31..60 */
#define CT_PKG_NAME_SIZE      64
#define CT_PKG_LABEL_SIZE     34
#define CT_PKG_MAX_WIRES      255
#define CT_PKG_NET_NONE       0       /* pin is not connected to other pins by the schema */

/* CtPkgPin.flags */
#define CT_PKG_PIN_USED       0x01    /* pin belongs to a connector of the cable */
#define CT_PKG_PIN_LEFT       0x02    /* pin belongs to a left connector */

#pragma pack(push, 1)

typedef struct {
	char     magic[4];                /* "CTPK" */
	uint16_t version;                 /* CT_PKG_VERSION */
	uint16_t headerSize;              /* sizeof(CtPkgHeader) */
	uint32_t totalSize;               /* size of the whole package in bytes */
	uint32_t crc32;
	char     name[CT_PKG_NAME_SIZE];  /* cable name, UTF-8, zero terminated */
	uint16_t imageWidth;              /* size of the cable picture, pixels */
	uint16_t imageHeight;
	uint8_t  pinCount;                /* CT_PKG_PIN_COUNT */
	uint8_t  wireCount;
	uint8_t  netCount;                /* nets are numbered 1..netCount */
	uint8_t  reserved;
} CtPkgHeader;

typedef struct {
	uint8_t  net;                     /* CT_PKG_NET_NONE or 1..netCount */
	uint8_t  flags;                   /* CT_PKG_PIN_xxx */
	uint16_t x;                       /* pin point on the picture, pixels */
	uint16_t y;
	char     label[CT_PKG_LABEL_SIZE];/* "Connector:pin", UTF-8, zero terminated */
} CtPkgPin;

typedef struct {
	uint8_t  pinA;                    /* slot pin 1..60 */
	uint8_t  pinB;                    /* slot pin 1..60 */
} CtPkgWire;

#pragma pack(pop)

#define CT_PKG_MAX_SIZE (sizeof(CtPkgHeader) + CT_PKG_PIN_COUNT * sizeof(CtPkgPin) + CT_PKG_MAX_WIRES * sizeof(CtPkgWire))

#endif /* CT_PACKAGE_H_ */
