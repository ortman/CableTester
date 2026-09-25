/*
 * ct_test.h
 *
 * Cable test: drives every slot pin one by one and reads all the others,
 * then compares the measured connections with the test package.
 */

#ifndef CT_TEST_H_
#define CT_TEST_H_

#include "ct_pins.h"
#include "ct_package.h"

#define CT_TEST_MAX_ERRORS   64
#define CT_TEST_SETTLE_US    200   /* time to charge the cable before reading */

enum {
	CT_ERROR_OPEN  = 0,   /* the schema has the wire, the cable has not */
	CT_ERROR_SHORT = 1    /* the cable connects the pins of different nets */
};

typedef struct {
	uint8_t type;   /* CT_ERROR_xxx */
	uint8_t pinA;   /* slot pin 1..60 */
	uint8_t pinB;
} CtTestError;

typedef struct {
	CtPinMask   conn[CT_PIN_COUNT];  /* conn[i] bit j: pin j+1 is seen while pin i+1 is driven */
	uint8_t     errorCount;
	uint8_t     overflow;            /* there were more errors than CT_TEST_MAX_ERRORS */
	CtTestError errors[CT_TEST_MAX_ERRORS];
} CtTestResult;

/* Measures the connection matrix, fills result->conn */
void CtTest_Scan(CtTestResult* result);

/* Measures only the given pins, the rows of the other pins stay empty */
void CtTest_ScanPins(CtTestResult* result, CtPinMask pins);

/* The pins that belong to the connectors of the cable (CT_PKG_PIN_USED) */
CtPinMask CtTest_UsedPins(const CtPkgHeader* package);

/* Measures and compares with the package. Only the pins of the schema are
   checked: a module may carry the connectors of other cables.
   Returns the number of errors */
uint8_t CtTest_Run(const CtPkgHeader* package, CtTestResult* result);

/* Compares an already measured matrix with the package */
uint8_t CtTest_Compare(const CtPkgHeader* package, CtTestResult* result);

#endif /* CT_TEST_H_ */
