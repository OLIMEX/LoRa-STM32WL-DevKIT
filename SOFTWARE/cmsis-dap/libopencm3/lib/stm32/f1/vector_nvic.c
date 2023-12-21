/* This file is part of the libopencm3 project.
 *
 * It was generated by the irq2nvic_h script.
 *
 * This part needs to get included in the compilation unit where
 * blocking_handler gets defined due to the way #pragma works.
 */


/** @defgroup CM3_nvic_isrdecls_STM32F1 User interrupt service routines (ISR) defaults for STM32 F1 series
    @ingroup CM3_nvic_isrdecls

    @{*/

void wwdg_isr(void) __attribute__((weak, alias("blocking_handler")));
void pvd_isr(void) __attribute__((weak, alias("blocking_handler")));
void tamper_isr(void) __attribute__((weak, alias("blocking_handler")));
void rtc_isr(void) __attribute__((weak, alias("blocking_handler")));
void flash_isr(void) __attribute__((weak, alias("blocking_handler")));
void rcc_isr(void) __attribute__((weak, alias("blocking_handler")));
void exti0_isr(void) __attribute__((weak, alias("blocking_handler")));
void exti1_isr(void) __attribute__((weak, alias("blocking_handler")));
void exti2_isr(void) __attribute__((weak, alias("blocking_handler")));
void exti3_isr(void) __attribute__((weak, alias("blocking_handler")));
void exti4_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma1_channel1_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma1_channel2_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma1_channel3_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma1_channel4_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma1_channel5_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma1_channel6_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma1_channel7_isr(void) __attribute__((weak, alias("blocking_handler")));
void adc1_2_isr(void) __attribute__((weak, alias("blocking_handler")));
void usb_hp_can_tx_isr(void) __attribute__((weak, alias("blocking_handler")));
void usb_lp_can_rx0_isr(void) __attribute__((weak, alias("blocking_handler")));
void can_rx1_isr(void) __attribute__((weak, alias("blocking_handler")));
void can_sce_isr(void) __attribute__((weak, alias("blocking_handler")));
void exti9_5_isr(void) __attribute__((weak, alias("blocking_handler")));
void tim1_brk_isr(void) __attribute__((weak, alias("blocking_handler")));
void tim1_up_isr(void) __attribute__((weak, alias("blocking_handler")));
void tim1_trg_com_isr(void) __attribute__((weak, alias("blocking_handler")));
void tim1_cc_isr(void) __attribute__((weak, alias("blocking_handler")));
void tim2_isr(void) __attribute__((weak, alias("blocking_handler")));
void tim3_isr(void) __attribute__((weak, alias("blocking_handler")));
void tim4_isr(void) __attribute__((weak, alias("blocking_handler")));
void i2c1_ev_isr(void) __attribute__((weak, alias("blocking_handler")));
void i2c1_er_isr(void) __attribute__((weak, alias("blocking_handler")));
void i2c2_ev_isr(void) __attribute__((weak, alias("blocking_handler")));
void i2c2_er_isr(void) __attribute__((weak, alias("blocking_handler")));
void spi1_isr(void) __attribute__((weak, alias("blocking_handler")));
void spi2_isr(void) __attribute__((weak, alias("blocking_handler")));
void usart1_isr(void) __attribute__((weak, alias("blocking_handler")));
void usart2_isr(void) __attribute__((weak, alias("blocking_handler")));
void usart3_isr(void) __attribute__((weak, alias("blocking_handler")));
void exti15_10_isr(void) __attribute__((weak, alias("blocking_handler")));
void rtc_alarm_isr(void) __attribute__((weak, alias("blocking_handler")));
void usb_wakeup_isr(void) __attribute__((weak, alias("blocking_handler")));
void tim8_brk_isr(void) __attribute__((weak, alias("blocking_handler")));
void tim8_up_isr(void) __attribute__((weak, alias("blocking_handler")));
void tim8_trg_com_isr(void) __attribute__((weak, alias("blocking_handler")));
void tim8_cc_isr(void) __attribute__((weak, alias("blocking_handler")));
void adc3_isr(void) __attribute__((weak, alias("blocking_handler")));
void fsmc_isr(void) __attribute__((weak, alias("blocking_handler")));
void sdio_isr(void) __attribute__((weak, alias("blocking_handler")));
void tim5_isr(void) __attribute__((weak, alias("blocking_handler")));
void spi3_isr(void) __attribute__((weak, alias("blocking_handler")));
void uart4_isr(void) __attribute__((weak, alias("blocking_handler")));
void uart5_isr(void) __attribute__((weak, alias("blocking_handler")));
void tim6_isr(void) __attribute__((weak, alias("blocking_handler")));
void tim7_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma2_channel1_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma2_channel2_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma2_channel3_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma2_channel4_5_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma2_channel5_isr(void) __attribute__((weak, alias("blocking_handler")));
void eth_isr(void) __attribute__((weak, alias("blocking_handler")));
void eth_wkup_isr(void) __attribute__((weak, alias("blocking_handler")));
void can2_tx_isr(void) __attribute__((weak, alias("blocking_handler")));
void can2_rx0_isr(void) __attribute__((weak, alias("blocking_handler")));
void can2_rx1_isr(void) __attribute__((weak, alias("blocking_handler")));
void can2_sce_isr(void) __attribute__((weak, alias("blocking_handler")));
void otg_fs_isr(void) __attribute__((weak, alias("blocking_handler")));

/**@}*/

/* Initialization template for the interrupt vector table. This definition is
 * used by the startup code generator (vector.c) to set the initial values for
 * the interrupt handling routines to the chip family specific _isr weak
 * symbols. */

#define IRQ_HANDLERS \
    [NVIC_WWDG_IRQ] = wwdg_isr, \
    [NVIC_PVD_IRQ] = pvd_isr, \
    [NVIC_TAMPER_IRQ] = tamper_isr, \
    [NVIC_RTC_IRQ] = rtc_isr, \
    [NVIC_FLASH_IRQ] = flash_isr, \
    [NVIC_RCC_IRQ] = rcc_isr, \
    [NVIC_EXTI0_IRQ] = exti0_isr, \
    [NVIC_EXTI1_IRQ] = exti1_isr, \
    [NVIC_EXTI2_IRQ] = exti2_isr, \
    [NVIC_EXTI3_IRQ] = exti3_isr, \
    [NVIC_EXTI4_IRQ] = exti4_isr, \
    [NVIC_DMA1_CHANNEL1_IRQ] = dma1_channel1_isr, \
    [NVIC_DMA1_CHANNEL2_IRQ] = dma1_channel2_isr, \
    [NVIC_DMA1_CHANNEL3_IRQ] = dma1_channel3_isr, \
    [NVIC_DMA1_CHANNEL4_IRQ] = dma1_channel4_isr, \
    [NVIC_DMA1_CHANNEL5_IRQ] = dma1_channel5_isr, \
    [NVIC_DMA1_CHANNEL6_IRQ] = dma1_channel6_isr, \
    [NVIC_DMA1_CHANNEL7_IRQ] = dma1_channel7_isr, \
    [NVIC_ADC1_2_IRQ] = adc1_2_isr, \
    [NVIC_USB_HP_CAN_TX_IRQ] = usb_hp_can_tx_isr, \
    [NVIC_USB_LP_CAN_RX0_IRQ] = usb_lp_can_rx0_isr, \
    [NVIC_CAN_RX1_IRQ] = can_rx1_isr, \
    [NVIC_CAN_SCE_IRQ] = can_sce_isr, \
    [NVIC_EXTI9_5_IRQ] = exti9_5_isr, \
    [NVIC_TIM1_BRK_IRQ] = tim1_brk_isr, \
    [NVIC_TIM1_UP_IRQ] = tim1_up_isr, \
    [NVIC_TIM1_TRG_COM_IRQ] = tim1_trg_com_isr, \
    [NVIC_TIM1_CC_IRQ] = tim1_cc_isr, \
    [NVIC_TIM2_IRQ] = tim2_isr, \
    [NVIC_TIM3_IRQ] = tim3_isr, \
    [NVIC_TIM4_IRQ] = tim4_isr, \
    [NVIC_I2C1_EV_IRQ] = i2c1_ev_isr, \
    [NVIC_I2C1_ER_IRQ] = i2c1_er_isr, \
    [NVIC_I2C2_EV_IRQ] = i2c2_ev_isr, \
    [NVIC_I2C2_ER_IRQ] = i2c2_er_isr, \
    [NVIC_SPI1_IRQ] = spi1_isr, \
    [NVIC_SPI2_IRQ] = spi2_isr, \
    [NVIC_USART1_IRQ] = usart1_isr, \
    [NVIC_USART2_IRQ] = usart2_isr, \
    [NVIC_USART3_IRQ] = usart3_isr, \
    [NVIC_EXTI15_10_IRQ] = exti15_10_isr, \
    [NVIC_RTC_ALARM_IRQ] = rtc_alarm_isr, \
    [NVIC_USB_WAKEUP_IRQ] = usb_wakeup_isr, \
    [NVIC_TIM8_BRK_IRQ] = tim8_brk_isr, \
    [NVIC_TIM8_UP_IRQ] = tim8_up_isr, \
    [NVIC_TIM8_TRG_COM_IRQ] = tim8_trg_com_isr, \
    [NVIC_TIM8_CC_IRQ] = tim8_cc_isr, \
    [NVIC_ADC3_IRQ] = adc3_isr, \
    [NVIC_FSMC_IRQ] = fsmc_isr, \
    [NVIC_SDIO_IRQ] = sdio_isr, \
    [NVIC_TIM5_IRQ] = tim5_isr, \
    [NVIC_SPI3_IRQ] = spi3_isr, \
    [NVIC_UART4_IRQ] = uart4_isr, \
    [NVIC_UART5_IRQ] = uart5_isr, \
    [NVIC_TIM6_IRQ] = tim6_isr, \
    [NVIC_TIM7_IRQ] = tim7_isr, \
    [NVIC_DMA2_CHANNEL1_IRQ] = dma2_channel1_isr, \
    [NVIC_DMA2_CHANNEL2_IRQ] = dma2_channel2_isr, \
    [NVIC_DMA2_CHANNEL3_IRQ] = dma2_channel3_isr, \
    [NVIC_DMA2_CHANNEL4_5_IRQ] = dma2_channel4_5_isr, \
    [NVIC_DMA2_CHANNEL5_IRQ] = dma2_channel5_isr, \
    [NVIC_ETH_IRQ] = eth_isr, \
    [NVIC_ETH_WKUP_IRQ] = eth_wkup_isr, \
    [NVIC_CAN2_TX_IRQ] = can2_tx_isr, \
    [NVIC_CAN2_RX0_IRQ] = can2_rx0_isr, \
    [NVIC_CAN2_RX1_IRQ] = can2_rx1_isr, \
    [NVIC_CAN2_SCE_IRQ] = can2_sce_isr, \
    [NVIC_OTG_FS_IRQ] = otg_fs_isr
