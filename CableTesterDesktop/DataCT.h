#ifndef _DATA_CT_H_
#define _DATA_CT_H_

#include <stdint.h>

typedef struct {
	uint8_t id;
	uint8_t pinCount;
	uint32_t name[100];
	uint8_t isLeft;
	uint32_t color;
	uint8_t *testerPins;
} ConnectorCT_t;

typedef struct {
	uint8_t leftConnectorId;
	uint8_t rightConnectorId;
	uint8_t leftPin;
	uint8_t rightPin;
	uint32_t color;
	uint32_t color2;
} WireCT_t;

struct CableCT {
	uint32_t color;
	uint32_t name[100];
	uint8_t wiresCount;
	WireCT_t* wires;
	uint8_t cablesCount;
	CableCT* cables;
};

typedef CableCT CableCT_t;

typedef struct {
	uint8_t connectorCount;
	ConnectorCT_t* connectors;
	CableCT_t cable;
} MainCableCT_t;

#endif
