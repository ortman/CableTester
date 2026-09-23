#ifndef _DATA_CT_H_
#define _DATA_CT_H_

#include <stdint.h>

// Fixed-size fields of the .cbl records. Names and arrays are stored
// separately, see CableFormatFile.md

typedef struct {
	uint8_t id;
	uint8_t pinCount;
	uint8_t isLeft;
	uint32_t color;
} ConnectorCT_t;

typedef struct {
	uint8_t leftConnectorId;
	uint8_t rightConnectorId;
	uint8_t leftPin;
	uint8_t rightPin;
	uint32_t color;
	uint32_t color2;
} WireCT_t;

typedef struct {
	uint32_t color;
	uint8_t wiresCount;
	uint8_t cablesCount;
} CableCT_t;

typedef struct {
	uint8_t connectorCount;
} MainCableCT_t;

#endif
