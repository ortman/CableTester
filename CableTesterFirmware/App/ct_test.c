/*
 * ct_test.c
 */

#include "ct_test.h"

#include <string.h>

static void CtTest_AddError(CtTestResult* result, uint8_t type, uint8_t pinA, uint8_t pinB)
{
	if (result->errorCount >= CT_TEST_MAX_ERRORS) {
		result->overflow = 1;
		return;
	}
	CtTestError* e = &result->errors[result->errorCount++];
	e->type = type;
	e->pinA = pinA;
	e->pinB = pinB;
}

void CtTest_Scan(CtTestResult* result)
{
	CtTest_ScanPins(result, CT_PIN_MASK_ALL);
}

void CtTest_ScanPins(CtTestResult* result, CtPinMask pins)
{
	memset(result->conn, 0, sizeof(result->conn));
	for (uint8_t pin = 1; pin <= CT_PIN_COUNT; ++pin) {
		if ((pins & CT_PIN_BIT(pin)) == 0) continue;
		CtPins_Drive(pin);
		CtPins_DelayUs(CT_TEST_SETTLE_US);
		/* the driven pin always reads high, it is not a connection */
		result->conn[pin - 1] = CtPins_ReadAll() & ~CT_PIN_BIT(pin);
		CtPins_Release(pin);
		CtPins_DelayUs(CT_TEST_SETTLE_US);
	}
}

/* A connection is accepted when it is seen from either side */
static int CtTest_IsConnected(const CtTestResult* result, uint8_t a, uint8_t b)
{
	return (result->conn[a - 1] & CT_PIN_BIT(b)) != 0 ||
	       (result->conn[b - 1] & CT_PIN_BIT(a)) != 0;
}

uint8_t CtTest_Compare(const CtPkgHeader* package, CtTestResult* result)
{
	const CtPkgPin* pins = CT_PKG_PINS(package);
	const CtPkgWire* wires = CT_PKG_WIRES(package);

	result->errorCount = 0;
	result->overflow = 0;

	/* Broken wires */
	for (uint8_t i = 0; i < package->wireCount; ++i) {
		uint8_t a = wires[i].pinA;
		uint8_t b = wires[i].pinB;
		if (a < 1 || a > CT_PIN_COUNT || b < 1 || b > CT_PIN_COUNT) continue;
		if (!CtTest_IsConnected(result, a, b)) {
			CtTest_AddError(result, CT_ERROR_OPEN, a, b);
		}
	}

	/* Shorts: a connection between the pins of different nets.
	   A pin without a net is a net of its own. Every pair of nets is reported once. */
	uint8_t reportedA[CT_TEST_MAX_ERRORS];
	uint8_t reportedB[CT_TEST_MAX_ERRORS];
	uint8_t reportedCount = 0;
	for (uint8_t a = 1; a <= CT_PIN_COUNT; ++a) {
		/* the pins that are not in the schema belong to the connectors of other
		   cables on the same module, a connection to them is not an error */
		if ((pins[a - 1].flags & CT_PKG_PIN_USED) == 0) continue;
		for (uint8_t b = a + 1; b <= CT_PIN_COUNT; ++b) {
			if ((pins[b - 1].flags & CT_PKG_PIN_USED) == 0) continue;
			uint8_t netA = pins[a - 1].net;
			uint8_t netB = pins[b - 1].net;
			if (netA != CT_PKG_NET_NONE && netA == netB) continue;  /* the same net, it must be connected */
			if (!CtTest_IsConnected(result, a, b)) continue;

			/* key of the net: the net number or the pin number when there is no net */
			uint8_t keyA = (netA != CT_PKG_NET_NONE) ? netA : (uint8_t)(CT_PIN_COUNT + a);
			uint8_t keyB = (netB != CT_PKG_NET_NONE) ? netB : (uint8_t)(CT_PIN_COUNT + b);
			uint8_t known = 0;
			for (uint8_t i = 0; i < reportedCount; ++i) {
				if ((reportedA[i] == keyA && reportedB[i] == keyB) ||
				    (reportedA[i] == keyB && reportedB[i] == keyA)) {
					known = 1;
					break;
				}
			}
			if (known) continue;
			if (reportedCount < CT_TEST_MAX_ERRORS) {
				reportedA[reportedCount] = keyA;
				reportedB[reportedCount] = keyB;
				++reportedCount;
			}
			CtTest_AddError(result, CT_ERROR_SHORT, a, b);
		}
	}
	return result->errorCount;
}

CtPinMask CtTest_UsedPins(const CtPkgHeader* package)
{
	const CtPkgPin* pins = CT_PKG_PINS(package);
	CtPinMask mask = 0;
	for (uint8_t pin = 1; pin <= CT_PIN_COUNT; ++pin) {
		if (pins[pin - 1].flags & CT_PKG_PIN_USED) mask |= CT_PIN_BIT(pin);
	}
	return mask;
}

uint8_t CtTest_Run(const CtPkgHeader* package, CtTestResult* result)
{
	/* only the pins of the schema are driven, the other connectors of the
	   module are left alone */
	CtTest_ScanPins(result, CtTest_UsedPins(package));
	return CtTest_Compare(package, result);
}
