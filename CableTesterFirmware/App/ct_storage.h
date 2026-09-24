/*
 * ct_storage.h
 *
 * Test packages in the internal flash of the MCU.
 *
 * The region takes the last CT_STORAGE_MAX_SLOTS slots of the flash, the real
 * size of which is taken from the device signature: on STM32F103VB it is
 * 0x08010000..0x0801FFFF, right above the 64 KB the linker gives to the
 * firmware, so the slots keep their place when the firmware changes. On a
 * smaller flash the region starts after the firmware image and has fewer slots.
 * Every slot holds one package, an empty or a damaged slot is the one where
 * CtPkg_IsValid() fails, so a moved region only loses the stored packages, it
 * can not read garbage.
 */

#ifndef CT_STORAGE_H_
#define CT_STORAGE_H_

#include "ct_package.h"

#define CT_STORAGE_SLOT_SIZE   4096   /* 4 pages of 1 KB */
#define CT_STORAGE_MAX_SLOTS   16     /* 64 KB at the end of the flash */
#define CT_STORAGE_GAP         2048   /* keep this far away from the firmware image */

void CtStorage_Init(void);

uint8_t CtStorage_GetSlotCount(void);

/* Bytes available for one package */
uint16_t CtStorage_GetSlotSize(void);

/* The package of the slot or NULL when the slot is empty or damaged.
   The pointer goes right into the flash, the data are not copied. */
const CtPkgHeader* CtStorage_Get(uint8_t slot);

/* Writing of a package by parts, so that it is not kept in RAM:
   BeginWrite erases the slot, WriteChunk adds the next bytes of the package,
   EndWrite checks what has been written and erases the slot when it is broken.
   All of them return 0 on error. */
int CtStorage_BeginWrite(uint8_t slot);
int CtStorage_WriteChunk(const void* data, uint16_t size);
int CtStorage_EndWrite(void);
void CtStorage_CancelWrite(void);

int CtStorage_Erase(uint8_t slot);

/* The first slot with a valid package or 0xFF */
uint8_t CtStorage_FindFirst(void);

/* The cables are kept in the slots 0..N-1 without gaps: the line of the cable
   list on the display is the slot number. */

/* Number of the stored packages */
uint8_t CtStorage_CountUsed(void);

/* Called when a package moves to a lower slot, to move its picture as well */
typedef void (*CtStorageMoved)(uint8_t from, uint8_t to);

/* Moves the packages down to close the gaps. Returns the number of moves */
uint8_t CtStorage_Compact(CtStorageMoved moved);

#endif /* CT_STORAGE_H_ */
