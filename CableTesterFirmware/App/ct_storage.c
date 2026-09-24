/*
 * ct_storage.c
 */

#include "ct_storage.h"
#include "main.h"

#include <stdio.h>
#include <string.h>

#define CT_FLASH_BASE      0x08000000UL
#define CT_FLASH_PAGE_SIZE 1024UL     /* STM32F103 medium density */

/* End of the firmware image in the flash: the .data section is copied from there */
extern uint8_t _sidata;
extern uint8_t _sdata;
extern uint8_t _edata;

static uint32_t ctStorageBase;
static uint8_t  ctStorageSlots;

void CtStorage_Init(void)
{
	uint32_t flashSizeKb = *(volatile uint16_t*)FLASHSIZE_BASE;
	if (flashSizeKb == 0 || flashSizeKb > 1024) flashSizeKb = 64;   /* broken signature */
	uint32_t flashEnd = CT_FLASH_BASE + flashSizeKb * 1024UL;

	/* The slots sit at the end of the flash, so that their address does not move
	   when the firmware grows. Only when the firmware reaches that place, the
	   region starts right after it and holds fewer slots. */
	uint32_t base = flashEnd - (uint32_t)CT_STORAGE_MAX_SLOTS * CT_STORAGE_SLOT_SIZE;
	uint32_t imageEnd = (uint32_t)&_sidata + (uint32_t)(&_edata - &_sdata) + CT_STORAGE_GAP;
	if (base < imageEnd) {
		base = (imageEnd + CT_STORAGE_SLOT_SIZE - 1) & ~(CT_STORAGE_SLOT_SIZE - 1);
	}

	ctStorageBase = base;
	ctStorageSlots = 0;
	if (flashEnd > base) {
		uint32_t slots = (flashEnd - base) / CT_STORAGE_SLOT_SIZE;
		if (slots > CT_STORAGE_MAX_SLOTS) slots = CT_STORAGE_MAX_SLOTS;
		ctStorageSlots = (uint8_t)slots;
	}
	Log("Storage: flash %luK, %u slot(s) of %u bytes at 0x%08lX\n",
	    (unsigned long)flashSizeKb, ctStorageSlots, (unsigned)CT_STORAGE_SLOT_SIZE,
	    (unsigned long)ctStorageBase);
}

uint8_t CtStorage_GetSlotCount(void)
{
	return ctStorageSlots;
}

uint16_t CtStorage_GetSlotSize(void)
{
	return CT_STORAGE_SLOT_SIZE;
}

static uint32_t CtStorage_SlotAddress(uint8_t slot)
{
	return ctStorageBase + (uint32_t)slot * CT_STORAGE_SLOT_SIZE;
}

const CtPkgHeader* CtStorage_Get(uint8_t slot)
{
	if (slot >= ctStorageSlots) return NULL;
	const void* data = (const void*)CtStorage_SlotAddress(slot);
	if (!CtPkg_IsValid(data, CT_STORAGE_SLOT_SIZE)) return NULL;
	return (const CtPkgHeader*)data;
}

int CtStorage_Erase(uint8_t slot)
{
	if (slot >= ctStorageSlots) return 0;
	FLASH_EraseInitTypeDef erase = {0};
	erase.TypeErase = FLASH_TYPEERASE_PAGES;
	erase.PageAddress = CtStorage_SlotAddress(slot);
	erase.NbPages = CT_STORAGE_SLOT_SIZE / CT_FLASH_PAGE_SIZE;
	uint32_t pageError = 0;

	if (HAL_FLASH_Unlock() != HAL_OK) return 0;
	HAL_StatusTypeDef st = HAL_FLASHEx_Erase(&erase, &pageError);
	HAL_FLASH_Lock();
	if (st != HAL_OK) {
		Log("Storage: erase of the slot %u failed at 0x%08lX\n", slot, (unsigned long)pageError);
		return 0;
	}
	return 1;
}

/* State of the write by parts */
static uint8_t  ctStorageWriteSlot = 0xFF;
static uint32_t ctStorageWriteDone;    /* bytes already in the flash */
static uint8_t  ctStorageCarry;        /* the odd byte that waits for its pair */
static uint8_t  ctStorageHasCarry;

int CtStorage_BeginWrite(uint8_t slot)
{
	if (slot >= ctStorageSlots) return 0;
	if (!CtStorage_Erase(slot)) return 0;
	ctStorageWriteSlot = slot;
	ctStorageWriteDone = 0;
	ctStorageHasCarry = 0;
	return 1;
}

static int CtStorage_ProgramHalf(uint16_t half)
{
	if (ctStorageWriteDone + 2 > CT_STORAGE_SLOT_SIZE) return 0;
	uint32_t address = CtStorage_SlotAddress(ctStorageWriteSlot) + ctStorageWriteDone;
	if (HAL_FLASH_Unlock() != HAL_OK) return 0;
	HAL_StatusTypeDef st = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, address, half);
	HAL_FLASH_Lock();
	if (st != HAL_OK) {
		Log("Storage: write failed at 0x%08lX\n", (unsigned long)address);
		return 0;
	}
	ctStorageWriteDone += 2;
	return 1;
}

int CtStorage_WriteChunk(const void* data, uint16_t size)
{
	if (ctStorageWriteSlot >= ctStorageSlots) return 0;
	const uint8_t* bytes = (const uint8_t*)data;
	uint16_t i = 0;

	if (ctStorageHasCarry && size) {          /* the flash takes half words only */
		if (!CtStorage_ProgramHalf((uint16_t)(ctStorageCarry | (bytes[0] << 8)))) return 0;
		ctStorageHasCarry = 0;
		i = 1;
	}
	for (; i + 1 < size; i += 2) {
		if (!CtStorage_ProgramHalf((uint16_t)(bytes[i] | (bytes[i + 1] << 8)))) return 0;
	}
	if (i < size) {
		ctStorageCarry = bytes[i];
		ctStorageHasCarry = 1;
	}
	return 1;
}

int CtStorage_EndWrite(void)
{
	if (ctStorageWriteSlot >= ctStorageSlots) return 0;
	if (ctStorageHasCarry) {                  /* the tail is padded with 0xFF */
		if (!CtStorage_ProgramHalf((uint16_t)(ctStorageCarry | 0xFF00))) {
			CtStorage_CancelWrite();
			return 0;
		}
		ctStorageHasCarry = 0;
	}
	uint8_t slot = ctStorageWriteSlot;
	ctStorageWriteSlot = 0xFF;
	if (CtStorage_Get(slot) == NULL) {        /* the package did not survive the write */
		Log("Storage: the package of the slot %u is broken, erasing\n", slot);
		CtStorage_Erase(slot);
		return 0;
	}
	return 1;
}

void CtStorage_CancelWrite(void)
{
	if (ctStorageWriteSlot < ctStorageSlots) {
		CtStorage_Erase(ctStorageWriteSlot);
	}
	ctStorageWriteSlot = 0xFF;
	ctStorageHasCarry = 0;
}

uint8_t CtStorage_CountUsed(void)
{
	uint8_t count = 0;
	for (uint8_t slot = 0; slot < ctStorageSlots; ++slot) {
		if (CtStorage_Get(slot) != NULL) ++count;
	}
	return count;
}

static int CtStorage_Copy(uint8_t from, uint8_t to)
{
	const CtPkgHeader* pkg = CtStorage_Get(from);
	if (pkg == NULL || !CtStorage_BeginWrite(to)) return 0;
	const uint8_t* src = (const uint8_t*)pkg;
	uint32_t size = pkg->totalSize;
	for (uint32_t done = 0; done < size; ) {
		uint16_t part = (uint16_t)((size - done > 256) ? 256 : size - done);
		if (!CtStorage_WriteChunk(src + done, part)) {
			CtStorage_CancelWrite();
			return 0;
		}
		done += part;
	}
	return CtStorage_EndWrite();
}

uint8_t CtStorage_Compact(CtStorageMoved moved)
{
	uint8_t next = 0;
	uint8_t moves = 0;
	for (uint8_t slot = 0; slot < ctStorageSlots; ++slot) {
		if (CtStorage_Get(slot) == NULL) continue;
		if (slot != next) {
			if (!CtStorage_Copy(slot, next)) {
				Log("Storage: can not move the slot %u to %u\n", slot, next);
				return moves;
			}
			CtStorage_Erase(slot);
			Log("Storage: the slot %u is moved to %u\n", slot, next);
			if (moved) moved(slot, next);
			++moves;
		}
		++next;
	}
	return moves;
}

uint8_t CtStorage_FindFirst(void)
{
	for (uint8_t slot = 0; slot < ctStorageSlots; ++slot) {
		if (CtStorage_Get(slot) != NULL) return slot;
	}
	return 0xFF;
}
