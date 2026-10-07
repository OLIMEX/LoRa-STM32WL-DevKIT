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
#include "stm32wlxx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
extern uint8_t lse_available;
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
void MX_DMA_Init(void);
void MX_ADC_Init(void);
void MX_RTC_Init(void);
void MX_SUBGHZ_Init(void);
void MX_USART1_UART_Init(void);

/* USER CODE BEGIN EFP */
void IIS2MDC_Init(void);
void IIS2MDC_Read(int16_t *x, int16_t *y, int16_t *z);
void AHT20_Init(void);
int16_t AHT20_ReadTemp_x10(void);
uint8_t LDR_ReadLevel(void);
uint8_t Button_IsPressed(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RTC_N_PREDIV_S 8 /* PREDIV_A=127 fixed by HAL in binary-only mode -> 32768/128=256Hz -> 2^8=256 */
#define RTC_PREDIV_S ((1<<RTC_N_PREDIV_S)-1)
#define RTC_PREDIV_A ((1<<(15-RTC_N_PREDIV_S))-1)
#define FE_CTRL2_Pin GPIO_PIN_8
#define FE_CTRL2_GPIO_Port GPIOB
#define FE_CTRL1_Pin GPIO_PIN_13
#define FE_CTRL1_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
