/*
 * ct_pins.h
 *
 * Slot pins D1..D60 of the tester board.
 * Every pin is connected to a GPIO through a 1 kOhm resistor. An idle pin is
 * an input with the pull-down, a tested pin is a push-pull output driven high.
 */

#ifndef CT_PINS_H_
#define CT_PINS_H_

#include <stdint.h>

#define CT_PIN_COUNT      60
#define CT_PIN_MASK_ALL   0x0FFFFFFFFFFFFFFFULL  /* bits 0..59 */

/* Bit (pin - 1) of the mask belongs to the slot pin */
typedef uint64_t CtPinMask;

#define CT_PIN_BIT(pin)   (((CtPinMask)1) << ((pin) - 1))

/* All pins to inputs with the pull-down, starts the microsecond timer */
void CtPins_Init(void);

void CtPins_DelayUs(uint32_t us);

/* pin: 1..CT_PIN_COUNT */
void CtPins_Drive(uint8_t pin);
void CtPins_Release(uint8_t pin);

/* Reads all the slot pins at once */
CtPinMask CtPins_ReadAll(void);

#endif /* CT_PINS_H_ */
