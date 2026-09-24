/*
 * host_test.c
 *
 * Checks CtTest_Compare() on the PC, without the board: the pin scan is faked
 * with a matrix, the package is built in memory.
 *
 * Build and run (any host compiler):
 *   clang -std=c11 -Wall -I../App -I../../Common host_test.c ../App/ct_test.c -o host_test
 *   ./host_test
 */
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "ct_test.h"

/* ---- stubs of ct_pins ---- */
static CtPinMask fakeConn[CT_PIN_COUNT];
static uint8_t driven;
void CtPins_Init(void) {}
void CtPins_DelayUs(uint32_t us) { (void)us; }
void CtPins_Drive(uint8_t pin) { driven = pin; }
void CtPins_Release(uint8_t pin) { (void)pin; driven = 0; }
CtPinMask CtPins_ReadAll(void) { return driven ? (fakeConn[driven - 1] | CT_PIN_BIT(driven)) : 0; }

/* ---- package builder ---- */
static uint8_t pkgBuf[CT_PKG_MAX_SIZE];

static CtPkgHeader* BuildPackage(const uint8_t (*wires)[2], uint8_t wireCount)
{
	memset(pkgBuf, 0, sizeof(pkgBuf));
	CtPkgHeader* h = (CtPkgHeader*)pkgBuf;
	memcpy(h->magic, CT_PKG_MAGIC, 4);
	h->version = CT_PKG_VERSION;
	h->headerSize = sizeof(CtPkgHeader);
	h->pinCount = CT_PKG_PIN_COUNT;
	h->wireCount = wireCount;
	h->imageWidth = 480;
	h->imageHeight = 760;
	CtPkgPin* pins = (CtPkgPin*)(pkgBuf + h->headerSize);
	CtPkgWire* w = (CtPkgWire*)(pkgBuf + h->headerSize + CT_PKG_PIN_COUNT * sizeof(CtPkgPin));
	uint8_t net = 0;
	for (uint8_t i = 0; i < wireCount; ++i) {
		w[i].pinA = wires[i][0];
		w[i].pinB = wires[i][1];
		uint8_t netA = pins[wires[i][0] - 1].net;
		uint8_t netB = pins[wires[i][1] - 1].net;
		uint8_t n = netA ? netA : (netB ? netB : ++net);
		pins[wires[i][0] - 1].net = n;
		pins[wires[i][1] - 1].net = n;
		pins[wires[i][0] - 1].flags = CT_PKG_PIN_USED | CT_PKG_PIN_LEFT;
		pins[wires[i][1] - 1].flags = CT_PKG_PIN_USED;
	}
	h->netCount = net;
	h->totalSize = h->headerSize + CT_PKG_PIN_COUNT * sizeof(CtPkgPin) + wireCount * sizeof(CtPkgWire);
	h->crc32 = 0;
	h->crc32 = CtPkg_Crc32(pkgBuf, h->totalSize);
	return h;
}

static void Connect(uint8_t a, uint8_t b)
{
	fakeConn[a - 1] |= CT_PIN_BIT(b);
	fakeConn[b - 1] |= CT_PIN_BIT(a);
}

/* Real measurement sees the whole connected group, not only the pairs set above */
static void Closure(void)
{
	for (int k = 0; k < CT_PIN_COUNT; ++k) {
		for (int i = 0; i < CT_PIN_COUNT; ++i) {
			if (fakeConn[i] & CT_PIN_BIT(k + 1)) fakeConn[i] |= fakeConn[k] & ~CT_PIN_BIT(i + 1);
		}
	}
}

static void Report(const char* title, CtTestResult* r)
{
	printf("%s: %u error(s)%s\n", title, r->errorCount, r->overflow ? " (overflow)" : "");
	for (uint8_t i = 0; i < r->errorCount; ++i) {
		printf("   %s D%u - D%u\n", r->errors[i].type == CT_ERROR_OPEN ? "open " : "short",
		       r->errors[i].pinA, r->errors[i].pinB);
	}
}

int main(void)
{
	/* a cable: 1-31, 2-32, 3-33, and a net of three pins 4-34, 4-35 */
	static const uint8_t wires[][2] = {{1, 31}, {2, 32}, {3, 33}, {4, 34}, {4, 35}};
	CtPkgHeader* pkg = BuildPackage(wires, 5);
	printf("package: size %u nets %u wires %u valid %d\n",
	       pkg->totalSize, pkg->netCount, pkg->wireCount, CtPkg_IsValid(pkg, sizeof(pkgBuf)));
	assert(CtPkg_IsValid(pkg, sizeof(pkgBuf)));

	CtTestResult r;

	/* 1. a good cable */
	memset(fakeConn, 0, sizeof(fakeConn));
	for (unsigned i = 0; i < 5; ++i) Connect(wires[i][0], wires[i][1]);
	Connect(34, 35); /* the net of three pins is connected through pin 4 */
	Closure();
	CtTest_Run(pkg, &r);
	Report("good cable", &r);
	assert(r.errorCount == 0);

	/* 2. a broken wire 2-32 */
	memset(fakeConn, 0, sizeof(fakeConn));
	for (unsigned i = 0; i < 5; ++i) if (i != 1) Connect(wires[i][0], wires[i][1]);
	Connect(34, 35);
	Closure();
	CtTest_Run(pkg, &r);
	Report("open 2-32", &r);
	assert(r.errorCount == 1 && r.errors[0].type == CT_ERROR_OPEN &&
	       r.errors[0].pinA == 2 && r.errors[0].pinB == 32);

	/* 3. a short between the nets 1-31 and 2-32: all four pins see each other */
	memset(fakeConn, 0, sizeof(fakeConn));
	for (unsigned i = 0; i < 5; ++i) Connect(wires[i][0], wires[i][1]);
	Connect(34, 35);
	Connect(1, 2); Connect(1, 32); Connect(31, 2); Connect(31, 32);
	Closure();
	CtTest_Run(pkg, &r);
	Report("short of two nets", &r);
	assert(r.errorCount == 1 && r.errors[0].type == CT_ERROR_SHORT);

	/* 4. a short to a pin that is not in the schema */
	memset(fakeConn, 0, sizeof(fakeConn));
	for (unsigned i = 0; i < 5; ++i) Connect(wires[i][0], wires[i][1]);
	Connect(34, 35);
	Connect(3, 40);
	Closure();
	CtTest_Run(pkg, &r);
	Report("short to the free pin 40", &r);
	assert(r.errorCount == 1); /* the whole net 3-33 is shorted to the free pin, reported once */

	/* 5. one side only: the connection is seen from one pin, not from the other */
	memset(fakeConn, 0, sizeof(fakeConn));
	for (unsigned i = 0; i < 5; ++i) Connect(wires[i][0], wires[i][1]);
	Connect(34, 35);
	fakeConn[1 - 1] &= ~CT_PIN_BIT(31); /* pin 1 does not see 31, but 31 sees 1 */
	CtTest_Run(pkg, &r);
	Report("one side only", &r);
	assert(r.errorCount == 0);

	/* 6. an empty cable: everything is open */
	memset(fakeConn, 0, sizeof(fakeConn));
	Closure();
	CtTest_Run(pkg, &r);
	Report("nothing connected", &r);
	assert(r.errorCount == 5);

	printf("\nAll checks passed\n");
	return 0;
}
