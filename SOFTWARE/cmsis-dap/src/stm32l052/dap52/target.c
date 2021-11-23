/*
 * Copyright (c) 2016, Devan Lai
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose with or without fee is hereby granted, provided
 * that the above copyright notice and this permission notice
 * appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/crs.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/syscfg.h>
#include <libopencm3/stm32/common/pwr_common_v1.h>

#include "target.h"
#include "config.h"


#define LED_GREEN_PIN GPIO4
#define LED_GREEN_PORT GPIOB
#define LED_RED_PIN GPIO3
#define LED_RED_PORT GPIOB
#define USBDET_GPIO_PORT         GPIOA
#define USBDET_GPIO_PIN          GPIO7
/* Reconfigure processor settings */
void cpu_setup(void) {
    


}

/* Set STM32 to 48 MHz. */
void clock_setup(void) {
        rcc_periph_reset_pulse(RST_CRS);  
	rcc_osc_on(RCC_HSI48); 	
	rcc_osc_on(RCC_HSI16);  
 
        rcc_set_sysclk_source(RCC_HSI16);
	rcc_periph_clock_enable(RCC_SYSCFG);
	
	rcc_periph_clock_enable(RCC_USB);
        rcc_periph_clock_enable(RCC_CRS);
	//rcc_periph_clock_enable(RCC_RNG);
	//rcc_periph_clock_enable(RCC_CRC);	
        
	rcc_set_usart2_sel(RCC_CCIPR_USART2SEL_APB);
	 // Trim from USB sync frame
	crs_autotrim_usb_enable();	
	rcc_set_hsi48_source_rc48();
	SYSCFG_CFGR3 |= SYSCFG_CFGR3_ENREF_HSI48 | SYSCFG_CFGR3_EN_VREFINT;
	RCC_CCIPR |= RCC_CCIPR_HSI48SEL;

}

static void button_setup(void) {
    /* Enable GPIOAB clock. */
    //rcc_periph_clock_enable(RCC_GPIOA);

    /* Set PA7 to an input */
    
    gpio_mode_setup(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO6);
  
    if (gpio_get(GPIOA, GPIO6) == 0)
    {
    //gpio_mode_setup(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_NONE,
   //                 GPIO4 | GPIO5 );
    //gpio_set(GPIOA, GPIO4); 		   
		     led_num(2);
		 while (gpio_get(GPIOA, GPIO6) == 0);
	    }
}

void gpio_setup(void) {

    /* Enable GPIOA and GPIOB clocks. */
    rcc_periph_clock_enable(RCC_GPIOA);

    
    gpio_mode_setup(USBDET_GPIO_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, USBDET_GPIO_PIN);
    
    while (gpio_get(USBDET_GPIO_PORT,USBDET_GPIO_PIN) == 0)
    {
	//sleep 
	pwr_set_standby_mode();
    }
    
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_GPIOC);  

    /* Setup LEDs as PP outputs */
    gpio_set_output_options(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_LOW,
                            GPIO4 | GPIO5 );

    gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
                    GPIO3| GPIO4 | GPIO5 );
 
  button_setup();
  

    
    

    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE,
                    GPIO11 | GPIO12);
    gpio_set_af(GPIOA, GPIO_AF2, GPIO11 | GPIO12);
 
}

void target_console_init(void) {
    /* Enable UART clock */
    rcc_periph_clock_enable(CONSOLE_USART_CLOCK);
    gpio_mode_setup(GPIOA,  GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2 | GPIO3);
    gpio_set_af(GPIOA, GPIO_AF4, GPIO2 | GPIO3);
}

void led_bit(uint8_t position, bool state) {
    uint32_t gpio = 0xFFFFFFFFU;
    if (position == 0) {
        gpio = GPIO4;
    } else if (position == 1) {
        gpio = GPIO3;
    } else if (position == 2) {
        gpio = GPIO5;
    }

    if (gpio != 0xFFFFFFFFU) {
        if (state) {
            gpio_clear(GPIOB, gpio);
        } else {
            gpio_set(GPIOB, gpio);
        }
    }
}

void led_num(uint8_t value) {
    if (value & 0x4) {
        gpio_clear(GPIOB, GPIO5);
    } else {
        gpio_set(GPIOB, GPIO5);
    }
    if (value & 0x2) {
        gpio_clear(GPIOB, GPIO3);
    } else {
        gpio_set(GPIOB, GPIO3);
    }
    if (value & 0x1) {
        gpio_clear(GPIOB, GPIO4);
    } else {
        gpio_set(GPIOB, GPIO4);
    }
}
