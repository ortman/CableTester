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
#include <stddef.h>

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

/* Pins and wires follow the header */
#define CT_PKG_PINS(pkg)  ((const CtPkgPin*)((const uint8_t*)(pkg) + (pkg)->headerSize))
#define CT_PKG_WIRES(pkg) ((const CtPkgWire*)((const uint8_t*)CT_PKG_PINS(pkg) + (pkg)->pinCount * sizeof(CtPkgPin)))

static inline uint32_t CtPkg_Crc32(const void* data, uint32_t size)
{
	const uint8_t* p = (const uint8_t*)data;
	uint32_t crc = 0xFFFFFFFFu;
	for (uint32_t i = 0; i < size; ++i) {
		crc ^= p[i];
		for (int b = 0; b < 8; ++b) {
			crc = (crc >> 1) ^ (0xEDB88320u & (uint32_t)(-(int32_t)(crc & 1)));
		}
	}
	return ~crc;
}

/* Checks the header, the size and the CRC of the package in memory */
static inline int CtPkg_IsValid(const void* data, uint32_t size)
{
	const CtPkgHeader* h = (const CtPkgHeader*)data;
	if (size < sizeof(CtPkgHeader)) return 0;
	if (h->magic[0] != 'C' || h->magic[1] != 'T' || h->magic[2] != 'P' || h->magic[3] != 'K') return 0;
	if (h->version != CT_PKG_VERSION || h->headerSize < sizeof(CtPkgHeader)) return 0;
	if (h->pinCount != CT_PKG_PIN_COUNT || h->totalSize > size || h->totalSize > CT_PKG_MAX_SIZE) return 0;
	if (h->totalSize != h->headerSize + (uint32_t)h->pinCount * sizeof(CtPkgPin)
	                                  + (uint32_t)h->wireCount * sizeof(CtPkgWire)) return 0;

	uint32_t crc = 0xFFFFFFFFu;
	const uint8_t* p = (const uint8_t*)data;
	for (uint32_t i = 0; i < h->totalSize; ++i) {
		/* the crc32 field itself is counted as zero */
		uint8_t b = (i >= offsetof(CtPkgHeader, crc32) && i < offsetof(CtPkgHeader, crc32) + 4) ? 0 : p[i];
		crc ^= b;
		for (int n = 0; n < 8; ++n) {
			crc = (crc >> 1) ^ (0xEDB88320u & (uint32_t)(-(int32_t)(crc & 1)));
		}
	}
	return (~crc) == h->crc32;
}

#endif /* CT_PACKAGE_H_ */
