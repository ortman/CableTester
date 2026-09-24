/*
 * ct_pins.c
 */

#include "ct_pins.h"
#include "main.h"

typedef struct {
	GPIO_TypeDef* port;
	uint16_t      mask;
} CtPinMap;

/* Index = slot pin - 1. The labels come from the CubeMX pin configuration */
static const CtPinMap ctPinMap[CT_PIN_COUNT] = {
	{ D1_GPIO_Port, D1_Pin }, { D2_GPIO_Port, D2_Pin }, { D3_GPIO_Port, D3_Pin }, { D4_GPIO_Port, D4_Pin },
	{ D5_GPIO_Port, D5_Pin }, { D6_GPIO_Port, D6_Pin }, { D7_GPIO_Port, D7_Pin }, { D8_GPIO_Port, D8_Pin },
	{ D9_GPIO_Port, D9_Pin }, { D10_GPIO_Port, D10_Pin }, { D11_GPIO_Port, D11_Pin }, { D12_GPIO_Port, D12_Pin },
	{ D13_GPIO_Port, D13_Pin }, { D14_GPIO_Port, D14_Pin }, { D15_GPIO_Port, D15_Pin }, { D16_GPIO_Port, D16_Pin },
	{ D17_GPIO_Port, D17_Pin }, { D18_GPIO_Port, D18_Pin }, { D19_GPIO_Port, D19_Pin }, { D20_GPIO_Port, D20_Pin },
	{ D21_GPIO_Port, D21_Pin }, { D22_GPIO_Port, D22_Pin }, { D23_GPIO_Port, D23_Pin }, { D24_GPIO_Port, D24_Pin },
	{ D25_GPIO_Port, D25_Pin }, { D26_GPIO_Port, D26_Pin }, { D27_GPIO_Port, D27_Pin }, { D28_GPIO_Port, D28_Pin },
	{ D29_GPIO_Port, D29_Pin }, { D30_GPIO_Port, D30_Pin }, { D31_GPIO_Port, D31_Pin }, { D32_GPIO_Port, D32_Pin },
	{ D33_GPIO_Port, D33_Pin }, { D34_GPIO_Port, D34_Pin }, { D35_GPIO_Port, D35_Pin }, { D36_GPIO_Port, D36_Pin },
	{ D37_GPIO_Port, D37_Pin }, { D38_GPIO_Port, D38_Pin }, { D39_GPIO_Port, D39_Pin }, { D40_GPIO_Port, D40_Pin },
	{ D41_GPIO_Port, D41_Pin }, { D42_GPIO_Port, D42_Pin }, { D43_GPIO_Port, D43_Pin }, { D44_GPIO_Port, D44_Pin },
	{ D45_GPIO_Port, D45_Pin }, { D46_GPIO_Port, D46_Pin }, { D47_GPIO_Port, D47_Pin }, { D48_GPIO_Port, D48_Pin },
	{ D49_GPIO_Port, D49_Pin }, { D50_GPIO_Port, D50_Pin }, { D51_GPIO_Port, D51_Pin }, { D52_GPIO_Port, D52_Pin },
	{ D53_GPIO_Port, D53_Pin }, { D54_GPIO_Port, D54_Pin }, { D55_GPIO_Port, D55_Pin }, { D56_GPIO_Port, D56_Pin },
	{ D57_GPIO_Port, D57_Pin }, { D58_GPIO_Port, D58_Pin }, { D59_GPIO_Port, D59_Pin }, { D60_GPIO_Port, D60_Pin },
};

static uint32_t ctCyclesPerUs = 72;

void CtPins_Init(void)
{
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	DWT->CYCCNT = 0;
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
	ctCyclesPerUs = HAL_RCC_GetHCLKFreq() / 1000000U;

	for (uint8_t pin = 1; pin <= CT_PIN_COUNT; ++pin) {
		CtPins_Release(pin);
	}
}

void CtPins_DelayUs(uint32_t us)
{
	uint32_t start = DWT->CYCCNT;
	uint32_t ticks = us * ctCyclesPerUs;
	while ((DWT->CYCCNT - start) < ticks) {
	}
}

void CtPins_Drive(uint8_t pin)
{
	if (pin < 1 || pin > CT_PIN_COUNT) return;
	const CtPinMap* p = &ctPinMap[pin - 1];
	GPIO_InitTypeDef init = {0};
	init.Pin = p->mask;
	init.Mode = GPIO_MODE_OUTPUT_PP;
	init.Pull = GPIO_NOPULL;
	init.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(p->port, &init);
	HAL_GPIO_WritePin(p->port, p->mask, GPIO_PIN_SET);
}

void CtPins_Release(uint8_t pin)
{
	if (pin < 1 || pin > CT_PIN_COUNT) return;
	const CtPinMap* p = &ctPinMap[pin - 1];
	GPIO_InitTypeDef init = {0};
	init.Pin = p->mask;
	init.Mode = GPIO_MODE_INPUT;
	init.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(p->port, &init);
}

CtPinMask CtPins_ReadAll(void)
{
	const uint32_t idrA = GPIOA->IDR;
	const uint32_t idrB = GPIOB->IDR;
	const uint32_t idrC = GPIOC->IDR;
	const uint32_t idrD = GPIOD->IDR;
	const uint32_t idrE = GPIOE->IDR;
	CtPinMask res = 0;
	for (uint8_t i = 0; i < CT_PIN_COUNT; ++i) {
		const CtPinMap* p = &ctPinMap[i];
		uint32_t idr;
		if (p->port == GPIOA) idr = idrA;
		else if (p->port == GPIOB) idr = idrB;
		else if (p->port == GPIOC) idr = idrC;
		else if (p->port == GPIOD) idr = idrD;
		else idr = idrE;
		if (idr & p->mask) res |= (((CtPinMask)1) << i);
	}
	return res;
}
