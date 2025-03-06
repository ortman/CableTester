/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(D31_GPIO_Port, D31_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : D52_Pin D51_Pin D50_Pin D49_Pin
                           D13_Pin D14_Pin D15_Pin D16_Pin
                           D32_Pin D1_Pin */
  GPIO_InitStruct.Pin = D52_Pin|D51_Pin|D50_Pin|D49_Pin
                          |D13_Pin|D14_Pin|D15_Pin|D16_Pin
                          |D32_Pin|D1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : D48_Pin D47_Pin D33_Pin D29_Pin
                           D30_Pin D2_Pin D3_Pin D4_Pin */
  GPIO_InitStruct.Pin = D48_Pin|D47_Pin|D33_Pin|D29_Pin
                          |D30_Pin|D2_Pin|D3_Pin|D4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : D46_Pin D45_Pin D22_Pin D23_Pin
                           D24_Pin D40_Pin D39_Pin D38_Pin
                           D56_Pin D55_Pin D54_Pin D53_Pin
                           D9_Pin D10_Pin */
  GPIO_InitStruct.Pin = D46_Pin|D45_Pin|D22_Pin|D23_Pin
                          |D24_Pin|D40_Pin|D39_Pin|D38_Pin
                          |D56_Pin|D55_Pin|D54_Pin|D53_Pin
                          |D9_Pin|D10_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : D17_Pin D18_Pin D19_Pin D20_Pin
                           D44_Pin D43_Pin D42_Pin D41_Pin
                           D21_Pin D11_Pin D12_Pin */
  GPIO_InitStruct.Pin = D17_Pin|D18_Pin|D19_Pin|D20_Pin
                          |D44_Pin|D43_Pin|D42_Pin|D41_Pin
                          |D21_Pin|D11_Pin|D12_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : D37_Pin D25_Pin D26_Pin D27_Pin
                           D28_Pin D36_Pin D35_Pin D34_Pin
                           D60_Pin D59_Pin D58_Pin D57_Pin
                           D5_Pin D6_Pin D7_Pin D8_Pin */
  GPIO_InitStruct.Pin = D37_Pin|D25_Pin|D26_Pin|D27_Pin
                          |D28_Pin|D36_Pin|D35_Pin|D34_Pin
                          |D60_Pin|D59_Pin|D58_Pin|D57_Pin
                          |D5_Pin|D6_Pin|D7_Pin|D8_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : D31_Pin */
  GPIO_InitStruct.Pin = D31_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(D31_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
