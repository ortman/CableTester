/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define D52_Pin GPIO_PIN_0
#define D52_GPIO_Port GPIOA
#define D51_Pin GPIO_PIN_1
#define D51_GPIO_Port GPIOA
#define D50_Pin GPIO_PIN_2
#define D50_GPIO_Port GPIOA
#define D49_Pin GPIO_PIN_3
#define D49_GPIO_Port GPIOA
#define D13_Pin GPIO_PIN_4
#define D13_GPIO_Port GPIOA
#define D14_Pin GPIO_PIN_5
#define D14_GPIO_Port GPIOA
#define D15_Pin GPIO_PIN_6
#define D15_GPIO_Port GPIOA
#define D16_Pin GPIO_PIN_7
#define D16_GPIO_Port GPIOA
#define D48_Pin GPIO_PIN_4
#define D48_GPIO_Port GPIOC
#define D47_Pin GPIO_PIN_5
#define D47_GPIO_Port GPIOC
#define D46_Pin GPIO_PIN_0
#define D46_GPIO_Port GPIOB
#define D45_Pin GPIO_PIN_1
#define D45_GPIO_Port GPIOB
#define D17_Pin GPIO_PIN_7
#define D17_GPIO_Port GPIOE
#define D18_Pin GPIO_PIN_8
#define D18_GPIO_Port GPIOE
#define D19_Pin GPIO_PIN_9
#define D19_GPIO_Port GPIOE
#define D20_Pin GPIO_PIN_10
#define D20_GPIO_Port GPIOE
#define D44_Pin GPIO_PIN_11
#define D44_GPIO_Port GPIOE
#define D43_Pin GPIO_PIN_12
#define D43_GPIO_Port GPIOE
#define D42_Pin GPIO_PIN_13
#define D42_GPIO_Port GPIOE
#define D41_Pin GPIO_PIN_14
#define D41_GPIO_Port GPIOE
#define D21_Pin GPIO_PIN_15
#define D21_GPIO_Port GPIOE
#define D22_Pin GPIO_PIN_10
#define D22_GPIO_Port GPIOB
#define D23_Pin GPIO_PIN_11
#define D23_GPIO_Port GPIOB
#define D24_Pin GPIO_PIN_12
#define D24_GPIO_Port GPIOB
#define D40_Pin GPIO_PIN_13
#define D40_GPIO_Port GPIOB
#define D39_Pin GPIO_PIN_14
#define D39_GPIO_Port GPIOB
#define D38_Pin GPIO_PIN_15
#define D38_GPIO_Port GPIOB
#define D37_Pin GPIO_PIN_8
#define D37_GPIO_Port GPIOD
#define D25_Pin GPIO_PIN_9
#define D25_GPIO_Port GPIOD
#define D26_Pin GPIO_PIN_10
#define D26_GPIO_Port GPIOD
#define D27_Pin GPIO_PIN_11
#define D27_GPIO_Port GPIOD
#define D28_Pin GPIO_PIN_12
#define D28_GPIO_Port GPIOD
#define D36_Pin GPIO_PIN_13
#define D36_GPIO_Port GPIOD
#define D35_Pin GPIO_PIN_14
#define D35_GPIO_Port GPIOD
#define D34_Pin GPIO_PIN_15
#define D34_GPIO_Port GPIOD
#define D33_Pin GPIO_PIN_6
#define D33_GPIO_Port GPIOC
#define D29_Pin GPIO_PIN_7
#define D29_GPIO_Port GPIOC
#define D30_Pin GPIO_PIN_8
#define D30_GPIO_Port GPIOC
#define D31_Pin GPIO_PIN_9
#define D31_GPIO_Port GPIOC
#define D32_Pin GPIO_PIN_8
#define D32_GPIO_Port GPIOA
#define D1_Pin GPIO_PIN_15
#define D1_GPIO_Port GPIOA
#define D2_Pin GPIO_PIN_10
#define D2_GPIO_Port GPIOC
#define D3_Pin GPIO_PIN_11
#define D3_GPIO_Port GPIOC
#define D4_Pin GPIO_PIN_12
#define D4_GPIO_Port GPIOC
#define D60_Pin GPIO_PIN_0
#define D60_GPIO_Port GPIOD
#define D59_Pin GPIO_PIN_1
#define D59_GPIO_Port GPIOD
#define D58_Pin GPIO_PIN_2
#define D58_GPIO_Port GPIOD
#define D57_Pin GPIO_PIN_3
#define D57_GPIO_Port GPIOD
#define D5_Pin GPIO_PIN_4
#define D5_GPIO_Port GPIOD
#define D6_Pin GPIO_PIN_5
#define D6_GPIO_Port GPIOD
#define D7_Pin GPIO_PIN_6
#define D7_GPIO_Port GPIOD
#define D8_Pin GPIO_PIN_7
#define D8_GPIO_Port GPIOD
#define D56_Pin GPIO_PIN_4
#define D56_GPIO_Port GPIOB
#define D55_Pin GPIO_PIN_5
#define D55_GPIO_Port GPIOB
#define D54_Pin GPIO_PIN_6
#define D54_GPIO_Port GPIOB
#define D53_Pin GPIO_PIN_7
#define D53_GPIO_Port GPIOB
#define D9_Pin GPIO_PIN_8
#define D9_GPIO_Port GPIOB
#define D10_Pin GPIO_PIN_9
#define D10_GPIO_Port GPIOB
#define D11_Pin GPIO_PIN_0
#define D11_GPIO_Port GPIOE
#define D12_Pin GPIO_PIN_1
#define D12_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
