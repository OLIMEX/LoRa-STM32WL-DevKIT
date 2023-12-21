/* This file is part of the libopencm3 project.
 *
 * It was generated by the irq2nvic_h script from ./include/libopencm3/sam/3u/irq.json
 */

#ifndef LIBOPENCM3_SAM3U_NVIC_H
#define LIBOPENCM3_SAM3U_NVIC_H

#include <libopencm3/cm3/nvic.h>

/** @defgroup CM3_nvic_defines_irqs User interrupts for Atmel SAM3U series
    @ingroup CM3_nvic_defines

    @{*/

#define NVIC_SUPC_IRQ 0
#define NVIC_RSTC_IRQ 1
#define NVIC_RTC_IRQ 2
#define NVIC_RTT_IRQ 3
#define NVIC_WDT_IRQ 4
#define NVIC_PMC_IRQ 5
#define NVIC_EEFC0_IRQ 6
#define NVIC_EEFC1_IRQ 7
#define NVIC_UART_IRQ 8
#define NVIC_SMC_IRQ 9
#define NVIC_PIOA_IRQ 10
#define NVIC_PIOB_IRQ 11
#define NVIC_PIOC_IRQ 12
#define NVIC_USART0_IRQ 13
#define NVIC_USART1_IRQ 14
#define NVIC_USART2_IRQ 15
#define NVIC_USART3_IRQ 16
#define NVIC_HSMCI_IRQ 17
#define NVIC_TWI0_IRQ 18
#define NVIC_TWI1_IRQ 19
#define NVIC_SPI_IRQ 20
#define NVIC_SSC_IRQ 21
#define NVIC_TC0_IRQ 22
#define NVIC_TC1_IRQ 23
#define NVIC_TC2_IRQ 24
#define NVIC_PWM_IRQ 25
#define NVIC_ADC12B_IRQ 26
#define NVIC_ADC_IRQ 27
#define NVIC_DMAC_IRQ 28
#define NVIC_UDPHS_IRQ 29

#define NVIC_IRQ_COUNT 30

/**@}*/

/** @defgroup CM3_nvic_isrprototypes_SAM3U User interrupt service routines (ISR) prototypes for Atmel SAM3U series
    @ingroup CM3_nvic_isrprototypes

    @{*/

BEGIN_DECLS

void supc_isr(void);
void rstc_isr(void);
void rtc_isr(void);
void rtt_isr(void);
void wdt_isr(void);
void pmc_isr(void);
void eefc0_isr(void);
void eefc1_isr(void);
void uart_isr(void);
void smc_isr(void);
void pioa_isr(void);
void piob_isr(void);
void pioc_isr(void);
void usart0_isr(void);
void usart1_isr(void);
void usart2_isr(void);
void usart3_isr(void);
void hsmci_isr(void);
void twi0_isr(void);
void twi1_isr(void);
void spi_isr(void);
void ssc_isr(void);
void tc0_isr(void);
void tc1_isr(void);
void tc2_isr(void);
void pwm_isr(void);
void adc12b_isr(void);
void adc_isr(void);
void dmac_isr(void);
void udphs_isr(void);

END_DECLS

/**@}*/

#endif /* LIBOPENCM3_SAM3U_NVIC_H */
