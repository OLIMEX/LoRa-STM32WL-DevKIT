/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    lora_app.c
  * @author  MCD Application Team
  * @brief   Application of the LRWAN Middleware
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
#include "platform.h"
#include "sys_app.h"
#include "lora_app.h"
#include "stm32_seq.h"
#include "stm32_timer.h"
#include "utilities_def.h"
#include "app_version.h"
#include "Commissioning.h"
#include "subghz_phy_version.h"
#include "smtc_modem_api.h"
#include "smtc_modem_utilities.h"
#include "smtc_modem_hal.h"
#include "smtc_modem_relay_api.h"
#include "adc_if.h"
#include "CayenneLpp.h"
#include "sys_sensors.h"
#include "flash_if.h"
#include "lorawan_api.h"
#include "stm32_lpm.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* External variables ---------------------------------------------------------*/
extern RNG_HandleTypeDef hrng;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Private typedef -----------------------------------------------------------*/
/**
  * @brief LoRa State Machine states
  */
typedef enum TxEventType_e
{
  /**
    * @brief Appdata Transmission issue based on timer every TxDutyCycleTime
    */
  TX_ON_TIMER,
  /**
    * @brief Appdata Transmission external event plugged on OnSendEvent( )
    */
  TX_ON_EVENT
  /* USER CODE BEGIN TxEventType_t */

  /* USER CODE END TxEventType_t */
} TxEventType_t;

/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/**
  * LEDs period value of the timer in ms
  */
#define LED_PERIOD_TIME 500

/**
  * Join switch period value of the timer in ms
  */
#define JOIN_TIME 2000

/**
  * Uplink time interval in Certification mode is 10s (recommended value)
  */
#define CERT_TX_DUTYCYCLE   10

/**
  * Stack id value (multistacks modem is not yet available)
  */
#define STACK_ID 0

/*---------------------------------------------------------------------------*/
/*                             LoRaWAN NVM configuration                     */
/*---------------------------------------------------------------------------*/
/**
  * @brief LoRaWAN NVM Flash address
  * @note last 2 sector of a 256kBytes device
  */
#define LORAWAN_NVM_BASE_ADDRESS        (0x0803F000UL)

#define SECURE_ELEMENT_CONTEXT_SIZE     0x2A0UL
#define MODEM_CONTEXT_SIZE              0x10UL
#define LORAWAN_CONTEXT_SIZE            0x28UL

#define ADDR_FLASH_LORAWAN_CONTEXT              LORAWAN_NVM_BASE_ADDRESS
#define ADDR_FLASH_MODEM_CONTEXT                (void *)(LORAWAN_NVM_BASE_ADDRESS + LORAWAN_CONTEXT_SIZE)
#define ADDR_FLASH_SECURE_ELEMENT_CONTEXT       (void *)(LORAWAN_NVM_BASE_ADDRESS + LORAWAN_CONTEXT_SIZE + MODEM_CONTEXT_SIZE)

/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/

/*!
 * @brief Stringify constants
 */
#define xstr( a ) str( a )
#define str( a ) #a

/*!
 * @brief Helper macro that returned a human-friendly message if a command does not return SMTC_MODEM_RC_OK
 *
 * @remark The macro is implemented to be used with functions returning a @ref smtc_modem_return_code_t
 *
 * @param[in] rc  Return code
 */

#define ASSERT_SMTC_MODEM_RC( rc_func )                                                     \
  do                                                                                        \
  {                                                                                         \
    smtc_modem_return_code_t rc = rc_func;                                                  \
    if( rc == SMTC_MODEM_RC_NOT_INIT )                                                      \
    {                                                                                       \
      APP_LOG(TS_OFF, VLEVEL_H,  "In %s - %s (line %d): %s\r\n", __FILE__, __func__, __LINE__,   \
              xstr( SMTC_MODEM_RC_NOT_INIT ) );                             \
    }                                                                                       \
    else if( rc == SMTC_MODEM_RC_INVALID )                                                  \
    {                                                                                       \
      APP_LOG(TS_OFF, VLEVEL_H,  "In %s - %s (line %d): %s\r\n", __FILE__, __func__, __LINE__,   \
              xstr( SMTC_MODEM_RC_INVALID ) );                              \
    }                                                                                       \
    else if( rc == SMTC_MODEM_RC_BUSY )                                                     \
    {                                                                                       \
      APP_LOG(TS_OFF, VLEVEL_H,  "In %s - %s (line %d): %s\r\n", __FILE__, __func__, __LINE__,   \
              xstr( SMTC_MODEM_RC_BUSY ) );                                 \
    }                                                                                       \
    else if( rc == SMTC_MODEM_RC_FAIL )                                                     \
    {                                                                                       \
      APP_LOG(TS_OFF, VLEVEL_H,  "In %s - %s (line %d): %s\r\n", __FILE__, __func__, __LINE__,   \
              xstr( SMTC_MODEM_RC_FAIL ) );                                 \
    }                                                                                       \
    else if( rc == SMTC_MODEM_RC_NO_TIME )                                                  \
    {                                                                                       \
      APP_LOG(TS_OFF, VLEVEL_L,  "In %s - %s (line %d): %s\r\n", __FILE__, __func__, __LINE__, \
              xstr( SMTC_MODEM_RC_NO_TIME ) );                            \
    }                                                                                       \
    else if( rc == SMTC_MODEM_RC_INVALID_STACK_ID )                                         \
    {                                                                                       \
      APP_LOG(TS_OFF, VLEVEL_H,  "In %s - %s (line %d): %s\r\n", __FILE__, __func__, __LINE__,   \
              xstr( SMTC_MODEM_RC_INVALID_STACK_ID ) );                     \
    }                                                                                       \
    else if( rc == SMTC_MODEM_RC_NO_EVENT )                                                 \
    {                                                                                       \
      APP_LOG(TS_OFF, VLEVEL_M,  "In %s - %s (line %d): %s\r\n", __FILE__, __func__, __LINE__,    \
              xstr( SMTC_MODEM_RC_NO_EVENT ) );                              \
    }                                                                                       \
  } while( 0 )

/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private function prototypes -----------------------------------------------*/

/**
  * @brief  LoRa End Node send request
  */
static void SendTxData(uint8_t port);
#if defined (LOW_POWER_DISABLE) && (LOW_POWER_DISABLE == 0)
/**
  * @brief  Sleep timer callback function
  * @param  context ptr
  */
static void OnSleepTimerEvent(void *context);
#endif /* (LOW_POWER_DISABLE) && (LOW_POWER_DISABLE == 0) */

/**
  * @brief User callback for event
  *
  *  This callback is called every time an event ( see smtc_modem_event_t ) appears in the modem.
  *  .........................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
  *  Several events may have to be read from the modem when this callback is called.
  */
static void EventCallback(void);

/*!
 * Restore the NVM Data context from the Flash
 *
* @param [in]  ctx_type   Type of modem context that need to be restored
* @param [in]  offset     Memory offset after ctx_type address
* @param [out] buffer     Buffer pointer to write to
* @param [in]  size       Buffer size to read in bytes
*/
static void RestoreContext(const modem_context_type_t ctx_type, uint32_t offset, uint8_t *buffer, const uint32_t size);
/*!
 * Store the NVM Data context to the Flash
 *
* @param [in] ctx_type   Type of modem context that need to be saved
* @param [in] offset     Memory offset after ctx_type address
* @param [in] buffer     Buffer pointer to write from
* @param [in] size       Buffer size to write in bytes
*/
static void StoreContext(const modem_context_type_t ctx_type, uint32_t offset, const uint8_t *buffer,
                         const uint32_t size);
/*!
 * Get Random value using the RNG module
 *
 * \retval value  Return the random value
 */
static uint32_t GetRandomValue(void);

/*!
 * Will be called to reset the system
 * \note Compliance test protocol callbacks used when TS001-1.0.4 + TS009 1.0.0 are defined
 */
static void SystemReset(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private variables ---------------------------------------------------------*/

/**
  * @brief LoRaWAN User credentials
  */
static uint8_t user_dev_eui[8]      = FORMAT32_KEY(LORAWAN_DEVICE_EUI);
static uint8_t user_join_eui[8]     = FORMAT32_KEY(LORAWAN_JOIN_EUI);
static uint8_t user_gen_app_key[16] = FORMAT_KEY(LORAWAN_GEN_APP_KEY);
static uint8_t user_app_key[16]     = FORMAT_KEY(LORAWAN_APP_KEY);
/**
  * @brief  Buffer for rx payload
  */
static uint8_t                  rx_payload[SMTC_MODEM_MAX_LORAWAN_PAYLOAD_LENGTH] = { 0 };

/**
  * @brief  Size of the payload in the rx_payload buffer
  */
static uint8_t                  rx_payload_size = 0;

/**
  * @brief  Metadata of downlink
  */
static smtc_modem_dl_metadata_t rx_metadata     = { 0 };

/**
  * @brief  Remaining downlink payload in modem
  */
static uint8_t                  rx_remaining    = 0;

/**
  * @brief  Flag for button status
  */
static volatile bool user_button_is_press = false;

/**
  * @brief LoRaWAN Certification Mode
  */
static bool CertMode = LORAWAN_CERTIFICATION_MODE;
static bool tx_in_progress = false;

/**
  * @brief Type of Event to generate application Tx
  */
static TxEventType_t EventType = TX_ON_TIMER;

#if defined (LOW_POWER_DISABLE) && (LOW_POWER_DISABLE == 0)
/**
  * @brief Timer to handle the sleep time
  */
static UTIL_TIMER_Object_t SleepTimer;
#endif /* (LOW_POWER_DISABLE) && (LOW_POWER_DISABLE == 0) */

/**
  * Temp buffer to store a FLASH page in RAM when partial replacement is needed
  */
static uint8_t FLASH_RAM_buffer[FLASH_IF_BUFFER_SIZE];

/**
  * @brief Handler Callbacks
  */
static Callbacks_t Callbacks =
{
  .EventCallback =                EventCallback,
  .RestoreContext =               RestoreContext,
  .StoreContext =                 StoreContext,
  .GetRandomValue =               GetRandomValue,
  .GetBatteryLevel =              GetBatteryLevel,
  .GetTemperatureLevel =          GetTemperatureLevel,
  .SystemReset =                  SystemReset,
};

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Exported functions ---------------------------------------------------------*/
/* USER CODE BEGIN EF */

/* USER CODE END EF */

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC FUNCTIONS DEFINITION ---------------------------------------------
 */

void LoRaWAN_Init(void)
{
  /* USER CODE BEGIN LoRaWAN_Init_LV */

  /* USER CODE END LoRaWAN_Init_LV */

  /* USER CODE BEGIN LoRaWAN_Init_1 */
  APP_LOG(TS_OFF, VLEVEL_M, "LoRaWAN_Init: starting...\r\n");
  /* USER CODE END LoRaWAN_Init_1 */

  if (FLASH_IF_Init(FLASH_RAM_buffer) != FLASH_IF_OK)
  {
    Error_Handler();
  }

#if defined (LOW_POWER_DISABLE) && (LOW_POWER_DISABLE == 0)
  UTIL_TIMER_Create(&SleepTimer, LED_PERIOD_TIME, UTIL_TIMER_ONESHOT, OnSleepTimerEvent, NULL);
#endif /* (LOW_POWER_DISABLE) && (LOW_POWER_DISABLE == 0) */
  /* Init the Lora Stack*/
  /* Init the modem and use EventCallback as event callback, please note that the callback will be */
  /* called immediately after the first call to smtc_modem_run_engine because of the reset detection */
  APP_LOG(TS_OFF, VLEVEL_M, "LoRaWAN_Init: calling smtc_modem_init...\r\n");
  HAL_Delay(100);
  smtc_modem_init(&Callbacks);
  APP_LOG(TS_OFF, VLEVEL_M, "LoRaWAN_Init: modem init done\r\n");

  /* Certification mode is disabled by default. It can be enabled setting LORAWAN_CERTIFICATION_MODE to true */
  smtc_modem_set_certification_mode(STACK_ID, CertMode);

  /* BSP crystal accurrancy could be set to a different value. By default it is 10. */
  smtc_modem_set_crystal_error_ppm(BSP_CRYSTAL_ERROR);

  /* USER CODE BEGIN LoRaWAN_Init_Last */

  /* USER CODE END LoRaWAN_Init_Last */
}

void LoRaWAN_Process(void)
{
  uint32_t sleep_time_ms = 0;

  /* One-shot: after modem init, force one ISR cycle to clear any stale
   * radio IRQ state that blocks subsequent SUBGHZ interrupts.
   * Must run AFTER sx126x_init_irq has set RadioOnDioIrqCb. */
  {
    static uint8_t radio_irq_primed = 0;
    if (!radio_irq_primed)
    {
      radio_irq_primed = 1;
      NVIC_SetPendingIRQ(SUBGHZ_Radio_IRQn);
      __DSB();
      __ISB();
    }
  }

  /* Check button */
  if (user_button_is_press == true)
  {
    user_button_is_press = false;

    smtc_modem_status_mask_t status_mask = 0;
    smtc_modem_get_status(STACK_ID, &status_mask);
    /* Check if the device has already joined a network */
    if ((status_mask & SMTC_MODEM_STATUS_JOINED) == SMTC_MODEM_STATUS_JOINED)
    {
      /* Send packet */
      SendTxData(LORAWAN_USER_APP_PORT);
    }
  }

  /* Periodic diagnostic: print IRQ counters every ~10 seconds */
  {
    extern volatile uint32_t rp_timer_irq_cnt;
    extern volatile uint32_t rp_radio_irq_cnt;
    extern volatile uint32_t rp_radio_process_cnt;
    extern volatile uint32_t subghz_isr_cnt;
    static uint32_t last_diag_ms = 0;
    uint32_t now_ms = SysTimeToMs(SysTimeGet());
    if (now_ms - last_diag_ms >= 10000)
    {
      last_diag_ms = now_ms;
      MW_LOG(TS_ON, VLEVEL_M, "DIAG: tmr=%u isr=%u proc=%u lbt=%u\r\n",
             (unsigned)rp_timer_irq_cnt, (unsigned)subghz_isr_cnt,
             (unsigned)rp_radio_process_cnt, (unsigned)rp_radio_irq_cnt);
    }
  }

  /* Modem process launch */
  sleep_time_ms = smtc_modem_run_engine();

  /* Atomically check sleep conditions (button was not pressed and no modem flags pending) */

  if ((user_button_is_press == false) && (smtc_modem_is_irq_flag_pending() == false))
  {
    if (sleep_time_ms > 0)
    {
#if defined (LOW_POWER_DISABLE) && (LOW_POWER_DISABLE == 0)
      UTIL_TIMER_SetPeriod(&SleepTimer, sleep_time_ms);
      UTIL_TIMER_Start(&SleepTimer);
      UTIL_LPM_EnterLowPower();
#endif
    }
  }

}

static void SystemReset(void)
{
  /* USER CODE BEGIN SystemReset_1 */

  /* USER CODE END SystemReset_1 */
  __disable_irq();
  HAL_NVIC_SystemReset();   /* Restart system */
  /* USER CODE BEGIN SystemReset_Last */

  /* USER CODE END SystemReset_Last */
}

static uint32_t GetRandomValue(void)
{
  uint32_t rand_nb = 0;
  /* hrng is initialized once by MX_RNG_Init() in main() and stays active */
  if (HAL_RNG_GenerateRandomNumber(&hrng, &rand_nb) != HAL_OK)
  {
    Error_Handler();
  }
  return rand_nb;
}

static void RestoreContext(const modem_context_type_t ctx_type, uint32_t offset, uint8_t *buffer,
                           const uint32_t size)
{
  /* Offset is only used for fuota and store and forward purpose and for multistack features. To avoid ram consumption */
  /* the use of hal_flash_read_modify_write is only done in these cases */
  /* USER CODE BEGIN RestoreContext_1 */

  /* USER CODE END RestoreContext_1 */
  FLASH_IF_StatusTypedef ret_status = FLASH_IF_OK;
  switch (ctx_type)
  {
    case CONTEXT_MODEM:
      ret_status = FLASH_IF_Read(buffer, ADDR_FLASH_MODEM_CONTEXT, MODEM_CONTEXT_SIZE);
      break;
    case CONTEXT_LORAWAN_STACK:
      ret_status = FLASH_IF_Read(buffer, (void *)((uint32_t)(ADDR_FLASH_LORAWAN_CONTEXT + offset)), LORAWAN_CONTEXT_SIZE);
      break;
    case CONTEXT_SECURE_ELEMENT:
      ret_status = FLASH_IF_Read(buffer, ADDR_FLASH_SECURE_ELEMENT_CONTEXT, SECURE_ELEMENT_CONTEXT_SIZE);
      break;
    default:
      break;
  }
  if (ret_status != 0)
  {
    APP_LOG(TS_OFF, VLEVEL_M, "restore ctx type %d, FLASH_IF return: %d\r\n", ctx_type, ret_status);
  }
  /* USER CODE BEGIN RestoreContext_Last */

  /* USER CODE END RestoreContext_Last */
}

static void StoreContext(const modem_context_type_t ctx_type, uint32_t offset, const uint8_t *buffer,
                         const uint32_t size)
{
  /* USER CODE BEGIN StoreContext_1 */

  /* USER CODE END StoreContext_1 */
  FLASH_IF_StatusTypedef ret_status = FLASH_IF_OK;
  /* Offset is only used for fuota and store and forward purpose and for multistack features. To avoid ram consumption
   * the use of hal_flash_read_modify_write is only done in these cases */
  switch (ctx_type)
  {
    case CONTEXT_MODEM:
    {
      ret_status = FLASH_IF_Write(ADDR_FLASH_MODEM_CONTEXT, (const void *)buffer, MODEM_CONTEXT_SIZE);
    }

    break;
    case CONTEXT_LORAWAN_STACK:
    {
      ret_status = FLASH_IF_Write((void *)ADDR_FLASH_LORAWAN_CONTEXT, (const void *)buffer, (uint32_t)LORAWAN_CONTEXT_SIZE);
    }
    break;
    case CONTEXT_SECURE_ELEMENT:
    {
      ret_status = FLASH_IF_Write(ADDR_FLASH_SECURE_ELEMENT_CONTEXT, (const void *)buffer, SECURE_ELEMENT_CONTEXT_SIZE);
    }
    break;

    default:
      break;
  }
  if (ret_status != 0)
  {
    APP_LOG(TS_OFF, VLEVEL_M, "store ctx type %d, FLASH_IF return: %d\r\n", ctx_type, ret_status);
  }
  /* USER CODE BEGIN StoreContext_Last */

  /* USER CODE END StoreContext_Last */
}

static void EventCallback(void)
{
  smtc_modem_event_t current_event;
  uint8_t            event_pending_count;
  uint8_t            stack_id = STACK_ID;
  smtc_modem_status_mask_t status_mask = 0;

  /* Continue to read modem event until all event has been processed */
  do
  {
    /* Read modem event */
    ASSERT_SMTC_MODEM_RC(smtc_modem_get_event(&current_event, &event_pending_count));

    switch (current_event.event_type)
    {
      case SMTC_MODEM_EVENT_RESET:
        APP_LOG(TS_OFF, VLEVEL_L, "Event received: RESET\r\n");

        /* Set user credentials */
        ASSERT_SMTC_MODEM_RC(smtc_modem_set_deveui(stack_id, user_dev_eui));
        ASSERT_SMTC_MODEM_RC(smtc_modem_set_joineui(stack_id, user_join_eui));
        ASSERT_SMTC_MODEM_RC(smtc_modem_set_appkey(stack_id, user_gen_app_key));
        ASSERT_SMTC_MODEM_RC(smtc_modem_set_nwkkey(stack_id, user_app_key));

        /* Set user region */
        ASSERT_SMTC_MODEM_RC(smtc_modem_set_region(stack_id, ACTIVE_REGION));
        APP_LOG(TS_OFF, VLEVEL_L, "Region set to %d (US915=3)\r\n", (int)ACTIVE_REGION);

        /* Print Security material */
        SecureElementPrintKeys(stack_id);
        CertMode = (smtc_modem_is_certification_port_disabled(STACK_ID)) ? 0 : CertMode;
        if (CertMode == false)
        {
          APP_LOG(TS_OFF, VLEVEL_L, "Joining LoRaWAN on US915 sub-band 2 (ch 8-15 + 65)...\r\n");
          /* Schedule a Join LoRaWAN network */
          ASSERT_SMTC_MODEM_RC(smtc_modem_join_network(stack_id));
        }
        break;

      case SMTC_MODEM_EVENT_ALARM:
        APP_LOG(TS_OFF, VLEVEL_H,  "Event received: ALARM\r\n");
        if (CertMode == true)
        {
          ASSERT_SMTC_MODEM_RC(smtc_modem_alarm_clear_timer());
        }
        else
        {
          /* Send periodical uplink */
          SendTxData(LORAWAN_USER_APP_PORT);
        }
        break;

      case SMTC_MODEM_EVENT_JOINED:
        APP_LOG(TS_OFF, VLEVEL_L,  "[DONE]\r\n");
        APP_LOG(TS_OFF, VLEVEL_L,  "Event received: JOINED\r\n");
        APP_LOG(TS_OFF, VLEVEL_H,  "Modem is now joined \r\n");
        /* USER CODE BEGIN EventCallback_1 */
        {
          const uint8_t custom_adr[SMTC_MODEM_CUSTOM_ADR_DATA_LENGTH] =
              { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
          ASSERT_SMTC_MODEM_RC(smtc_modem_adr_set_profile(stack_id, SMTC_MODEM_ADR_PROFILE_CUSTOM, custom_adr));
          APP_LOG(TS_OFF, VLEVEL_L, "ADR set to custom: DR0 only (SF10)\r\n");
        }
        /* USER CODE END EventCallback_1 */
        if (CertMode == false)
        {
          /* Send first periodical uplink */
          SendTxData(LORAWAN_USER_APP_PORT);
        }
        break;

      case SMTC_MODEM_EVENT_TXDONE:
        APP_LOG(TS_OFF, VLEVEL_L,  "[DONE]\r\n");
        APP_LOG(TS_OFF, VLEVEL_L,  "Event received: TXDONE\r\n");
        APP_LOG(TS_OFF, VLEVEL_H,  "Transmission done \r\n");
        tx_in_progress = false;
        smtc_modem_get_status(STACK_ID, &status_mask);
        /* USER CODE BEGIN EventCallback_2 */

        /* USER CODE END EventCallback_2 */
        break;

      case SMTC_MODEM_EVENT_DOWNDATA:
        APP_LOG(TS_OFF, VLEVEL_L,  "Event received: DOWNDATA\r\n");
        /* Get downlink data */
        ASSERT_SMTC_MODEM_RC(smtc_modem_get_downlink_data(rx_payload, &rx_payload_size, &rx_metadata, &rx_remaining));
        APP_LOG(TS_OFF, VLEVEL_L, "RX port=%u rssi=%d snr=%d size=%u win=%u payload=",
                rx_metadata.fport, rx_metadata.rssi - 64, rx_metadata.snr >> 2,
                rx_payload_size, rx_metadata.window);
        for (uint8_t i = 0; i < rx_payload_size; i++)
        {
          APP_LOG(TS_OFF, VLEVEL_L, "%02X", rx_payload[i]);
        }
        APP_LOG(TS_OFF, VLEVEL_L, "\r\n");
        break;

      case SMTC_MODEM_EVENT_JOINFAIL:
        APP_LOG(TS_OFF, VLEVEL_L,  "[FAILED]\r\n");
        APP_LOG(TS_OFF, VLEVEL_L,  "Event received: JOINFAIL\r\n");
        APP_LOG(TS_OFF, VLEVEL_L,  "Joining LoRaWAN..............");
        smtc_modem_get_status(STACK_ID, &status_mask);
        /* USER CODE BEGIN EventCallback_4 */

        /* USER CODE END EventCallback_4 */
        break;

      case SMTC_MODEM_EVENT_ALCSYNC_TIME:
        APP_LOG(TS_OFF, VLEVEL_M,  "Event received: ALCSync service TIME\r\n");
        break;

      case SMTC_MODEM_EVENT_LINK_CHECK:
        APP_LOG(TS_OFF, VLEVEL_M,  "Event received: LINK_CHECK\r\n");
        break;

      case SMTC_MODEM_EVENT_CLASS_B_PING_SLOT_INFO:
        APP_LOG(TS_OFF, VLEVEL_M,  "Event received: CLASS_B_PING_SLOT_INFO\r\n");
        break;

      case SMTC_MODEM_EVENT_CLASS_B_STATUS:
        APP_LOG(TS_OFF, VLEVEL_M,  "Event received: CLASS_B_STATUS\r\n");
        break;

      case SMTC_MODEM_EVENT_LORAWAN_MAC_TIME:
        APP_LOG(TS_OFF, VLEVEL_L,  "Event received: LORAWAN MAC TIME\r\n");
        break;

      case SMTC_MODEM_EVENT_LORAWAN_FUOTA_DONE:
      {
        bool status = current_event.event_data.fuota_status.successful;
        if (status == true)
        {
          APP_LOG(TS_OFF, VLEVEL_M,  "Event received: FUOTA SUCCESSFUL\r\n");
        }
        else
        {
          APP_LOG(TS_OFF, VLEVEL_L,  "Event received: FUOTA FAIL\r\n");
        }
        break;
      }

      case SMTC_MODEM_EVENT_NO_MORE_MULTICAST_SESSION_CLASS_C:
        APP_LOG(TS_OFF, VLEVEL_M,  "Event received: MULTICAST CLASS_C STOP\r\n");
        break;

      case SMTC_MODEM_EVENT_NO_MORE_MULTICAST_SESSION_CLASS_B:
        APP_LOG(TS_OFF, VLEVEL_M,  "Event received: MULTICAST CLASS_B STOP\r\n");
        break;

      case SMTC_MODEM_EVENT_NEW_MULTICAST_SESSION_CLASS_C:
        APP_LOG(TS_OFF, VLEVEL_M,  "Event received: New MULTICAST CLASS_C \r\n");
        break;

      case SMTC_MODEM_EVENT_NEW_MULTICAST_SESSION_CLASS_B:
        APP_LOG(TS_OFF, VLEVEL_M,  "Event received: New MULTICAST CLASS_B\r\n");
        break;

      case SMTC_MODEM_EVENT_FIRMWARE_MANAGEMENT:
        APP_LOG(TS_OFF, VLEVEL_M,  "Event received: FIRMWARE_MANAGEMENT\r\n");
        if (current_event.event_data.fmp.status == SMTC_MODEM_EVENT_FMP_REBOOT_IMMEDIATELY)
        {
          HAL_NVIC_SystemReset();
        }
        break;

      case SMTC_MODEM_EVENT_STREAM_DONE:
        APP_LOG(TS_OFF, VLEVEL_M,  "Event received: STREAM_DONE\r\n");
        break;

      case SMTC_MODEM_EVENT_UPLOAD_DONE:
        APP_LOG(TS_OFF, VLEVEL_M,  "Event received: UPLOAD_DONE\r\n");
        break;

      case SMTC_MODEM_EVENT_DM_SET_CONF:
        APP_LOG(TS_OFF, VLEVEL_M,  "Event received: DM_SET_CONF\r\n");
        break;

      case SMTC_MODEM_EVENT_MUTE:
        APP_LOG(TS_OFF, VLEVEL_M,  "Event received: MUTE\r\n");
        break;
      case SMTC_MODEM_EVENT_REGIONAL_DUTY_CYCLE:
      {
        uint8_t duty_cycle_status = current_event.event_data.regional_duty_cycle.status;
        APP_LOG(TS_OFF, VLEVEL_M,  "Event received: DUTY_CYCLE busy %d\r\n", duty_cycle_status);
      }
      break;
      default:
        APP_LOG(TS_OFF, VLEVEL_M,  "Unknown event %u\r\n", current_event.event_type);
        break;
    }
  } while (event_pending_count > 0);
}

/* USER CODE BEGIN PB_Callbacks */

/* USER CODE END PB_Callbacks */

static void SendTxData(uint8_t port)
{
  /* USER CODE BEGIN SendTxData_1 */

  /* USER CODE END SendTxData_1 */
  smtc_modem_status_mask_t status_mask = 0;
  smtc_modem_get_status(STACK_ID, &status_mask);

  if ((status_mask & SMTC_MODEM_STATUS_JOINED) == SMTC_MODEM_STATUS_JOINED)
  {
    /* Simple test payload: temperature + battery level */
    uint8_t tx_buffer[3];
    int16_t temperature = GetTemperatureLevel(); /* returns degrees C */
    uint8_t battery = GetBatteryLevel();

    tx_buffer[0] = (uint8_t)((temperature >> 8) & 0xFF);
    tx_buffer[1] = (uint8_t)(temperature & 0xFF);
    tx_buffer[2] = battery;

    if (tx_in_progress == false)
    {
      APP_LOG(TS_OFF, VLEVEL_L, "STM32WL uplink sent..........");
      tx_in_progress = true;
    }

    ASSERT_SMTC_MODEM_RC(smtc_modem_request_uplink(STACK_ID, port, true, tx_buffer, sizeof(tx_buffer)));

    /* Schedule next transmission */
    ASSERT_SMTC_MODEM_RC(smtc_modem_alarm_start_timer(APP_TX_DUTYCYCLE));

    APP_LOG(TS_ON, VLEVEL_M, "SendTxData on port %d: temp=%d C, bat=%d\r\n",
            port, temperature, battery);
  }
}

/* USER CODE BEGIN PrFD_LedEvents */

/* USER CODE END PrFD_LedEvents */

#if defined (LOW_POWER_DISABLE) && (LOW_POWER_DISABLE == 0)
static void OnSleepTimerEvent(void *context)
{
  /* USER CODE BEGIN OnSleepTimerEvent_1 */

  /* USER CODE END OnSleepTimerEvent_1 */
  APP_LOG(TS_ON, VLEVEL_H, "Sleep timer\r\n");

  /* USER CODE BEGIN OnSleepTimerEvent_Last */

  /* USER CODE END OnSleepTimerEvent_Last */
}
#endif /*(LOW_POWER_DISABLE) && (LOW_POWER_DISABLE == 0) */

/* --- EOF ------------------------------------------------------------------ */
