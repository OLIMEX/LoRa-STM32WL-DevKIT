/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    lora_app.c
  * @author  MCD Application Team
  * @brief   Application of the LRWAN Middleware
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "platform.h"
#include "Region.h" /* Needed for LORAWAN_DEFAULT_DATA_RATE */
#include "sys_app.h"
#include "lora_app.h"
#include "stm32_seq.h"
#include "LmHandler.h"

/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "timer.h"
#include "lora_info.h"
#include "utilities_def.h"
/* USER CODE END Includes */

/* External variables ---------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/**
  * @brief LoRaWAN handler parameters
  */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private function prototypes -----------------------------------------------*/
/**
  * @brief  join event callback function
  * @param  joinParams status of join
  */
static void OnJoinRequest(LmHandlerJoinParams_t *joinParams);

/**
  * @brief  tx event callback function
  * @param  params status of last Tx
  */
static void OnTxData(LmHandlerTxParams_t *params);

/**
  * @brief callback when LoRa application has received a frame
  * @param appData data received in the last Rx
  * @param params status of last Rx
  */
static void OnRxData(LmHandlerAppData_t *appData, LmHandlerRxParams_t *params);

/*!
 * Will be called each time a Radio IRQ is handled by the MAC layer
 *
 */
static void OnMacProcessNotify(void);

/* USER CODE BEGIN PFP */


/* USER CODE END PFP */

/* Private variables ---------------------------------------------------------*/
/**
  * @brief LoRaWAN handler Callbacks
  */
static LmHandlerCallbacks_t LmHandlerCallbacks =
{
  .GetBatteryLevel =           GetBatteryLevel,
  .GetTemperature =            GetTemperatureLevel,
  .GetUniqueId =               GetUniqueId,
  .GetDevAddr =                GetDevAddr,
  .OnMacProcess =              OnMacProcessNotify,
  .OnJoinRequest =             OnJoinRequest,
  .OnTxData =                  OnTxData,
  .OnRxData =                  OnRxData
};

/* USER CODE BEGIN PV */
static ActivationType_t ActivationType = LORAWAN_DEFAULT_ACTIVATION_TYPE;
/**
  * @brief LoRaWAN handler parameters
  */
static LmHandlerParams_t LmHandlerParams =
{
  .ActiveRegion =             ACTIVE_REGION,
  .DefaultClass =             LORAWAN_DEFAULT_CLASS,
  .AdrEnable =                LORAWAN_ADR_STATE,
  .TxDatarate =               LORAWAN_DEFAULT_DATA_RATE,
  .PingPeriodicity =          LORAWAN_DEFAULT_PING_SLOT_PERIODICITY
};
/* USER CODE END PV */

/* Exported functions ---------------------------------------------------------*/
/* USER CODE BEGIN EF */

/* USER CODE END EF */

void LoRaWAN_Init(void)
{
  /* USER CODE BEGIN LoRaWAN_Init_1 */
	 UTIL_TIMER_Init();
	 UTIL_SEQ_RegTask((1 << CFG_SEQ_Task_LmHandlerProcess), UTIL_SEQ_RFU, LmHandlerProcess);
	//  UTIL_SEQ_RegTask((1 << CFG_SEQ_Task_LoRaSendOnTxTimerOrButtonEvent), UTIL_SEQ_RFU, SendTxData);
	  /* Init Info table used by LmHandler*/
	   LoraInfo_Init();
  /* USER CODE END LoRaWAN_Init_1 */

  /* Init the Lora Stack*/
  LmHandlerInit(&LmHandlerCallbacks);

  /* USER CODE BEGIN LoRaWAN_Init_Last */

  LmHandlerConfigure(&LmHandlerParams);
  LmHandlerJoin(ActivationType);
  /* USER CODE END LoRaWAN_Init_Last */
}

/* USER CODE BEGIN PB_Callbacks */

/* USER CODE END PB_Callbacks */

/* Private functions ---------------------------------------------------------*/
/* USER CODE BEGIN PrFD */


/* USER CODE END PrFD */

static void OnRxData(LmHandlerAppData_t *appData, LmHandlerRxParams_t *params)
{
  /* USER CODE BEGIN OnRxData_1 */
	  uint32_t rxbuffer = 0;
	  if ((appData != NULL) && (params != NULL))
	  {
	    printf( "\r\n Received Downlink on F_PORT:%d \r\n", appData->Port);
	    /*
	    rxbuffer = sensors_downlink_conf_check(appData);
	    if (rxbuffer)
	    {
	        UTIL_TIMER_Create(&RxLedTimer, 0xFFFFFFFFU, UTIL_TIMER_PERIODIC, OnRxTimerLedEvent, NULL);
	        UTIL_TIMER_SetPeriod(&RxLedTimer, SENSORS_LED_RX_PERIOD_MS);
	        UTIL_TIMER_Start(&RxLedTimer);
	        UTIL_TIMER_SetPeriod(&TxTimer, rxbuffer);
	    }
	    else // Function returns 0 on fail
	    {
	        UTIL_TIMER_Create(&RxLedTimer, 0xFFFFFFFFU, UTIL_TIMER_PERIODIC, OnRxTimerLedEvent, NULL);
	        UTIL_TIMER_SetPeriod(&RxLedTimer, SENSORS_LED_UNHANDLED_RX_PERIOD_MS);
	        UTIL_TIMER_Start(&RxLedTimer);
	    }
	    */
	  }
  /* USER CODE END OnRxData_1 */
}

/* USER CODE BEGIN PrFD_LedEvents */

/* USER CODE END PrFD_LedEvents */

static void OnTxData(LmHandlerTxParams_t *params)
{
  /* USER CODE BEGIN OnTxData_1 */
	 if ((params != NULL) && (params->IsMcpsConfirm != 0))
	  {
	    printf("\r\n###### ========== MCPS-Confirm =============\r\n");
	    printf("###### U/L FRAME:%04d | PORT:%d | DR:%d | PWR:%d", params->UplinkCounter,
	            params->AppData.Port, params->Datarate, params->TxPower);

	    printf(" | MSG TYPE:");
	    if (params->MsgType == LORAMAC_HANDLER_CONFIRMED_MSG)
	    {
	      printf("CONFIRMED [%s]\r\n", (params->AckReceived != 0) ? "ACK" : "NACK");
	    }
	    else
	    {
	      printf("UNCONFIRMED\r\n");
	    }
	  }
  /* USER CODE END OnTxData_1 */
}

static void OnJoinRequest(LmHandlerJoinParams_t *joinParams)
{
  /* USER CODE BEGIN OnJoinRequest_1 */
	if (joinParams != NULL)
	  {
	    if (joinParams->Status == LORAMAC_HANDLER_SUCCESS)
	    {
	      printf("\r\n###### = JOINED = ");
	      if (joinParams->Mode == ACTIVATION_TYPE_ABP)
	      {
	        printf( "ABP ======================\r\n");
	      }
	      else
	      {
	        printf("OTAA =====================\r\n");
	      }
	    }
	    else
	    {
	      printf("\r\n###### = JOIN FAILED\r\n");
	    }
	  }
  /* USER CODE END OnJoinRequest_1 */
}

static void OnMacProcessNotify(void)
{
  /* USER CODE BEGIN OnMacProcessNotify_1 */
	 UTIL_SEQ_SetTask((1 << CFG_SEQ_Task_LmHandlerProcess), CFG_SEQ_Prio_0);
  /* USER CODE END OnMacProcessNotify_1 */
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
