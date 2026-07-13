/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

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
#define NSLEEP_86_Pin GPIO_PIN_0
#define NSLEEP_86_GPIO_Port GPIOA
#define ENABLE_86_Pin GPIO_PIN_1
#define ENABLE_86_GPIO_Port GPIOA
#define DIR_86_Pin GPIO_PIN_2
#define DIR_86_GPIO_Port GPIOA
#define CS_86_Pin GPIO_PIN_4
#define CS_86_GPIO_Port GPIOC
#define NSLEEP_57_Pin GPIO_PIN_5
#define NSLEEP_57_GPIO_Port GPIOC
#define ENABLE_57_Pin GPIO_PIN_1
#define ENABLE_57_GPIO_Port GPIOB
#define DIR_57_Pin GPIO_PIN_2
#define DIR_57_GPIO_Port GPIOB
#define NSLEEP_57_2_Pin GPIO_PIN_12
#define NSLEEP_57_2_GPIO_Port GPIOB
#define ENABLE_57_2_Pin GPIO_PIN_13
#define ENABLE_57_2_GPIO_Port GPIOB
#define DIR_57_2_Pin GPIO_PIN_14
#define DIR_57_2_GPIO_Port GPIOB
#define CS_57_2_Pin GPIO_PIN_6
#define CS_57_2_GPIO_Port GPIOC
#define CS_57_Pin GPIO_PIN_7
#define CS_57_GPIO_Port GPIOC
#define ROLLER_Pin GPIO_PIN_8
#define ROLLER_GPIO_Port GPIOC
#define LIMIT_Pin GPIO_PIN_9
#define LIMIT_GPIO_Port GPIOC
#define KEY_485_Pin GPIO_PIN_8
#define KEY_485_GPIO_Port GPIOA
#define KTH2_CS_Pin GPIO_PIN_2
#define KTH2_CS_GPIO_Port GPIOD
#define KTH1_CS_Pin GPIO_PIN_3
#define KTH1_CS_GPIO_Port GPIOB
#define DIR_42_Pin GPIO_PIN_4
#define DIR_42_GPIO_Port GPIOB
#define ENABLE_42_Pin GPIO_PIN_6
#define ENABLE_42_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
