/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#define ADC_VBAT_Pin GPIO_PIN_0
#define ADC_VBAT_GPIO_Port GPIOA
#define LASER_PWM_Pin GPIO_PIN_1
#define LASER_PWM_GPIO_Port GPIOA
#define LASER_TX_Pin GPIO_PIN_2
#define LASER_TX_GPIO_Port GPIOA
#define LASER_RX_Pin GPIO_PIN_3
#define LASER_RX_GPIO_Port GPIOA
#define RX_LED_Pin GPIO_PIN_4
#define RX_LED_GPIO_Port GPIOA
#define MAG_Pin GPIO_PIN_0
#define MAG_GPIO_Port GPIOB
#define BT_TX_Pin GPIO_PIN_9
#define BT_TX_GPIO_Port GPIOA
#define BT_RX_Pin GPIO_PIN_10
#define BT_RX_GPIO_Port GPIOA
#define BOARD_LED_Pin GPIO_PIN_4
#define BOARD_LED_GPIO_Port GPIOB
#define KEY_FIRE_Pin GPIO_PIN_8
#define KEY_FIRE_GPIO_Port GPIOB
#define KEY_RELOAD_Pin GPIO_PIN_9
#define KEY_RELOAD_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
