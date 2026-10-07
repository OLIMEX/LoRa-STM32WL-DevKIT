/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "app_lorawan.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "sys_app.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;

RNG_HandleTypeDef hrng;

RTC_HandleTypeDef hrtc;

SUBGHZ_HandleTypeDef hsubghz;

UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_tx;

/* USER CODE BEGIN PV */
uint8_t lse_available = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_RNG_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

#define IIS2MDC_ADDR      0x1E
#define IIS2MDC_CFG_REG_A 0x60
#define IIS2MDC_CFG_REG_C 0x62
#define IIS2MDC_OUTX_L    0x68

#define AHT20_ADDR        0x38

static int I2C1_WaitFlag(uint32_t flag, uint32_t timeout_ms)
{
  uint32_t t = HAL_GetTick() + timeout_ms;
  while (!(I2C1->ISR & flag))
  {
    if (I2C1->ISR & I2C_ISR_NACKF)
    {
      I2C1->ICR = I2C_ICR_NACKCF;
      return -1;
    }
    if (HAL_GetTick() > t) return -1;
  }
  return 0;
}

static void I2C1_Init(void)
{
  __HAL_RCC_GPIOA_CLK_ENABLE();
  GPIO_InitTypeDef gpio = {0};
  gpio.Pin = GPIO_PIN_9 | GPIO_PIN_10;
  gpio.Mode = GPIO_MODE_AF_OD;
  gpio.Pull = GPIO_PULLUP;
  gpio.Speed = GPIO_SPEED_FREQ_LOW;
  gpio.Alternate = GPIO_AF4_I2C1;
  HAL_GPIO_Init(GPIOA, &gpio);

  __HAL_RCC_I2C1_CLK_ENABLE();
  I2C1->CR1 &= ~I2C_CR1_PE;
  I2C1->TIMINGR = 0x00707CBB;
  I2C1->OAR1 = 0;
  I2C1->OAR2 = 0;
  I2C1->CR1 = I2C_CR1_PE;
}

static int I2C1_WriteReg(uint8_t addr, uint8_t reg, uint8_t *data, uint16_t len)
{
  uint32_t t = HAL_GetTick() + 100;
  while (I2C1->ISR & I2C_ISR_BUSY) { if (HAL_GetTick() > t) return -1; }

  I2C1->CR2 = (addr << 1) | (((uint32_t)(len + 1)) << I2C_CR2_NBYTES_Pos)
              | I2C_CR2_AUTOEND | I2C_CR2_START;

  if (I2C1_WaitFlag(I2C_ISR_TXIS, 100) != 0) return -1;
  I2C1->TXDR = reg;

  for (uint16_t i = 0; i < len; i++)
  {
    if (I2C1_WaitFlag(I2C_ISR_TXIS, 100) != 0) return -1;
    I2C1->TXDR = data[i];
  }

  if (I2C1_WaitFlag(I2C_ISR_STOPF, 100) != 0) return -1;
  I2C1->ICR = I2C_ICR_STOPCF;
  return 0;
}

static int I2C1_ReadReg(uint8_t addr, uint8_t reg, uint8_t *data, uint16_t len)
{
  uint32_t t = HAL_GetTick() + 100;
  while (I2C1->ISR & I2C_ISR_BUSY) { if (HAL_GetTick() > t) return -1; }

  I2C1->CR2 = (addr << 1) | (1U << I2C_CR2_NBYTES_Pos) | I2C_CR2_START;
  if (I2C1_WaitFlag(I2C_ISR_TXIS, 100) != 0) return -1;
  I2C1->TXDR = reg;
  if (I2C1_WaitFlag(I2C_ISR_TC, 100) != 0) return -1;

  I2C1->CR2 = (addr << 1) | I2C_CR2_RD_WRN
              | (((uint32_t)len) << I2C_CR2_NBYTES_Pos)
              | I2C_CR2_AUTOEND | I2C_CR2_START;

  for (uint16_t i = 0; i < len; i++)
  {
    if (I2C1_WaitFlag(I2C_ISR_RXNE, 100) != 0) return -1;
    data[i] = (uint8_t)I2C1->RXDR;
  }

  if (I2C1_WaitFlag(I2C_ISR_STOPF, 100) != 0) return -1;
  I2C1->ICR = I2C_ICR_STOPCF;
  return 0;
}

static int I2C1_WriteBytes(uint8_t addr, uint8_t *data, uint16_t len)
{
  uint32_t t = HAL_GetTick() + 100;
  while (I2C1->ISR & I2C_ISR_BUSY) { if (HAL_GetTick() > t) return -1; }

  I2C1->CR2 = (addr << 1) | (((uint32_t)len) << I2C_CR2_NBYTES_Pos)
              | I2C_CR2_AUTOEND | I2C_CR2_START;

  for (uint16_t i = 0; i < len; i++)
  {
    if (I2C1_WaitFlag(I2C_ISR_TXIS, 100) != 0) return -1;
    I2C1->TXDR = data[i];
  }

  if (I2C1_WaitFlag(I2C_ISR_STOPF, 100) != 0) return -1;
  I2C1->ICR = I2C_ICR_STOPCF;
  return 0;
}

static int I2C1_ReadBytes(uint8_t addr, uint8_t *data, uint16_t len)
{
  uint32_t t = HAL_GetTick() + 100;
  while (I2C1->ISR & I2C_ISR_BUSY) { if (HAL_GetTick() > t) return -1; }

  I2C1->CR2 = (addr << 1) | I2C_CR2_RD_WRN
              | (((uint32_t)len) << I2C_CR2_NBYTES_Pos)
              | I2C_CR2_AUTOEND | I2C_CR2_START;

  for (uint16_t i = 0; i < len; i++)
  {
    if (I2C1_WaitFlag(I2C_ISR_RXNE, 100) != 0) return -1;
    data[i] = (uint8_t)I2C1->RXDR;
  }

  if (I2C1_WaitFlag(I2C_ISR_STOPF, 100) != 0) return -1;
  I2C1->ICR = I2C_ICR_STOPCF;
  return 0;
}

void IIS2MDC_Init(void)
{
  uint8_t val = 0x00;
  I2C1_WriteReg(IIS2MDC_ADDR, IIS2MDC_CFG_REG_A, &val, 1);
  val = 0x10;
  I2C1_WriteReg(IIS2MDC_ADDR, IIS2MDC_CFG_REG_C, &val, 1);
}

void IIS2MDC_Read(int16_t *x, int16_t *y, int16_t *z)
{
  uint8_t buf[6] = {0};
  I2C1_ReadReg(IIS2MDC_ADDR, IIS2MDC_OUTX_L, buf, 6);
  *x = (int16_t)((uint16_t)buf[1] << 8 | buf[0]);
  *y = (int16_t)((uint16_t)buf[3] << 8 | buf[2]);
  *z = (int16_t)((uint16_t)buf[5] << 8 | buf[4]);
}

void AHT20_Init(void)
{
  HAL_Delay(40);
  uint8_t cmd[3] = {0xBE, 0x08, 0x00};
  I2C1_WriteBytes(AHT20_ADDR, cmd, 3);
  HAL_Delay(10);
}

int16_t AHT20_ReadTemp_x10(void)
{
  uint8_t cmd[3] = {0xAC, 0x33, 0x00};
  I2C1_WriteBytes(AHT20_ADDR, cmd, 3);
  HAL_Delay(80);

  uint8_t data[7] = {0};
  I2C1_ReadBytes(AHT20_ADDR, data, 7);
  if (data[0] & 0x80)
  {
    HAL_Delay(80);
    I2C1_ReadBytes(AHT20_ADDR, data, 7);
  }

  uint32_t raw = ((uint32_t)(data[3] & 0x0F) << 16)
                 | ((uint32_t)data[4] << 8) | data[5];
  return (int16_t)((raw * 2000UL) / 1048576UL) - 500;
}

uint8_t LDR_ReadLevel(void)
{
  ADC_ChannelConfTypeDef sConfig = {0};
  MX_ADC_Init();
  if (HAL_ADCEx_Calibration_Start(&hadc) != HAL_OK) return 0;

  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK) return 0;
  if (HAL_ADC_Start(&hadc) != HAL_OK) return 0;

  HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);
  HAL_ADC_Stop(&hadc);
  uint32_t raw = HAL_ADC_GetValue(&hadc);
  HAL_ADC_DeInit(&hadc);

  return (uint8_t)(raw * 100 / 4095);
}

uint8_t Button_IsPressed(void)
{
  return (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET) ? 1 : 0;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC_Init();
  MX_RNG_Init();
  MX_RTC_Init();
  MX_USART1_UART_Init();
  MX_SUBGHZ_Init();
  MX_LoRaWAN_Init();
  /* USER CODE BEGIN 2 */
  I2C1_Init();
  IIS2MDC_Init();
  AHT20_Init();
  APP_LOG(TS_OFF, VLEVEL_L, "Sensors initialized (IIS2MDC, AHT20, Button, LDR)\r\n");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    MX_LoRaWAN_Process();

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_HIGH);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the CPU, AHB and APB buses clocks
  */
  /* Try with LSE first */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE
                              |RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.LSIDiv = RCC_LSI_DIV1;
  RCC_OscInitStruct.HSEDiv = RCC_HSE_DIV1;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* LSE failed to start — fallback without LSE */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.LSEState = RCC_LSE_OFF;
    RCC_OscInitStruct.LSIDiv = RCC_LSI_DIV1;
    RCC_OscInitStruct.HSEDiv = RCC_HSE_DIV1;
    RCC_OscInitStruct.LSIState = RCC_LSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
      HAL_UART_Transmit(&huart1, (uint8_t*)"Place1: OscConfig fallback\r\n", 27, 100);
      Error_Handler();
    }
    lse_available = 0;
  }
  else
  {
    lse_available = 1;
  }

  /** Configure the SYSCLKSource, HCLK, PCLK1 and PCLK2 clocks dividers
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK3|RCC_CLOCKTYPE_HCLK
                              |RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1
                              |RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.AHBCLK3Divider = RCC_SYSCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    HAL_UART_Transmit(&huart1, (uint8_t*)"Place2: ClockConfig\r\n", 21, 100);
    Error_Handler();
  }
}

/**
  * @brief ADC Initialization Function
  * @param None
  * @retval None
  */
void MX_ADC_Init(void)
{

  /* USER CODE BEGIN ADC_Init 0 */

  /* USER CODE END ADC_Init 0 */

  /* USER CODE BEGIN ADC_Init 1 */

  /* USER CODE END ADC_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc.Instance = ADC;
  hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerAutoPowerOff = DISABLE;
  hadc.Init.ContinuousConvMode = DISABLE;
  hadc.Init.NbrOfConversion = 1;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.DMAContinuousRequests = DISABLE;
  hadc.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  hadc.Init.SamplingTimeCommon1 = ADC_SAMPLETIME_160CYCLES_5;
  hadc.Init.SamplingTimeCommon2 = ADC_SAMPLETIME_160CYCLES_5;
  hadc.Init.OversamplingMode = DISABLE;
  hadc.Init.TriggerFrequencyMode = ADC_TRIGGER_FREQ_HIGH;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    HAL_UART_Transmit(&huart1, (uint8_t*)"Place3: ADC_Init\r\n", 18, 100);
    Error_Handler();
  }
  /* USER CODE BEGIN ADC_Init 2 */

  /* USER CODE END ADC_Init 2 */

}

/**
  * @brief RNG Initialization Function
  * @param None
  * @retval None
  */
static void MX_RNG_Init(void)
{

  /* USER CODE BEGIN RNG_Init 0 */

  /* USER CODE END RNG_Init 0 */

  /* USER CODE BEGIN RNG_Init 1 */

  /* USER CODE END RNG_Init 1 */
  hrng.Instance = RNG;
  hrng.Init.ClockErrorDetection = RNG_CED_DISABLE;
  if (HAL_RNG_Init(&hrng) != HAL_OK)
  {
    HAL_UART_Transmit(&huart1, (uint8_t*)"Place4: RNG_Init\r\n", 18, 100);
    Error_Handler();
  }
  /* USER CODE BEGIN RNG_Init 2 */

  /* USER CODE END RNG_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_AlarmTypeDef sAlarm = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_PREDIV_A; /* = 127 in binary-only mode (HAL does not reprogram PRER) */
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  hrtc.Init.OutPutPullUp = RTC_OUTPUT_PULLUP_NONE;
  hrtc.Init.BinMode = RTC_BINARY_ONLY;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    HAL_UART_Transmit(&huart1, (uint8_t*)"Place5: RTC_Init\r\n", 18, 100);
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  if (HAL_RTCEx_SetSSRU_IT(&hrtc) != HAL_OK)
  {
    HAL_UART_Transmit(&huart1, (uint8_t*)"Place6: SSRU_IT\r\n", 17, 100);
    Error_Handler();
  }

  /** Enable the Alarm A
  */
  sAlarm.BinaryAutoClr = RTC_ALARMSUBSECONDBIN_AUTOCLR_YES;
  sAlarm.AlarmTime.SubSeconds = 0x0;
  sAlarm.AlarmMask = RTC_ALARMMASK_NONE;
  sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDBINMASK_NONE;
  sAlarm.Alarm = RTC_ALARM_A;
  if (HAL_RTC_SetAlarm(&hrtc, &sAlarm, 0) != HAL_OK)
  {
    HAL_UART_Transmit(&huart1, (uint8_t*)"Place7: RTC_SetAlarm\r\n", 22, 100);
    Error_Handler();
  }

  /** Enable the WakeUp
  */
  if (HAL_RTCEx_SetWakeUpTimer(&hrtc, 0, RTC_WAKEUPCLOCK_RTCCLK_DIV16) != HAL_OK)
  {
    HAL_UART_Transmit(&huart1, (uint8_t*)"Place8: WakeUpTimer\r\n", 21, 100);
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief SUBGHZ Initialization Function
  * @param None
  * @retval None
  */
void MX_SUBGHZ_Init(void)
{

  /* USER CODE BEGIN SUBGHZ_Init 0 */
  static uint8_t already_init = 0;
  if (already_init)
  {
    /* Already initialized — skip to avoid double-init HAL error */
    return;
  }
  /* USER CODE END SUBGHZ_Init 0 */

  /* USER CODE BEGIN SUBGHZ_Init 1 */

  /* USER CODE END SUBGHZ_Init 1 */
  hsubghz.Init.BaudratePrescaler = SUBGHZSPI_BAUDRATEPRESCALER_4;
  if (HAL_SUBGHZ_Init(&hsubghz) != HAL_OK)
  {
    HAL_UART_Transmit(&huart1, (uint8_t*)"Place9: SUBGHZ_Init\r\n", 21, 100);
    Error_Handler();
  }
  /* USER CODE BEGIN SUBGHZ_Init 2 */
  already_init = 1;
  /* USER CODE END SUBGHZ_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    HAL_UART_Transmit(&huart1, (uint8_t*)"Place10: UART_Init\r\n", 20, 100);
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    HAL_UART_Transmit(&huart1, (uint8_t*)"Place11: TxFifo\r\n", 17, 100);
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    HAL_UART_Transmit(&huart1, (uint8_t*)"Place12: RxFifo\r\n", 17, 100);
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    HAL_UART_Transmit(&huart1, (uint8_t*)"Place13: DisableFifo\r\n", 22, 100);
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * Enable DMA controller clock
  */
void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMAMUX1_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(FE_CTRL2_GPIO_Port, FE_CTRL2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(FE_CTRL1_GPIO_Port, FE_CTRL1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : FE_CTRL2_Pin */
  GPIO_InitStruct.Pin = FE_CTRL2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(FE_CTRL2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : FE_CTRL1_Pin */
  GPIO_InitStruct.Pin = FE_CTRL1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(FE_CTRL1_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /*Configure GPIO pin : PA0 (Button, active LOW with pull-up) */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB4 (LDR ADC_IN3, analog) */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PB12 (output LOW) */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* Print error using polling (DMA won't work after __disable_irq) */
  const char err_msg[] = "\r\n!!! Error_Handler called !!!\r\n";
  HAL_UART_Transmit(&huart1, (uint8_t*)err_msg, sizeof(err_msg)-1, 1000);
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
