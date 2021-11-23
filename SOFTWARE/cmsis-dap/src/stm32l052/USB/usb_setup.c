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
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/syscfg.h>
#include <libopencm3/stm32/st_usbfs.h>

#include "USB/usb_setup.h"
#include "config.h"
#include "target.h"

const usbd_driver* target_usb_init(void) {
 
 
   // rcc_periph_reset_pulse(RST_USB);

 
//#if REMAP_USB
//#define SYSCFG_CFGR1_PA11_PA12_RMP	(1 << 4)

    ///* Remap PA11 and PA12 for use as USB */
    //rcc_periph_clock_enable(RCC_SYSCFG);
    //SYSCFG_CFGR1 |= SYSCFG_CFGR1_PA11_PA12_RMP;
//#endif
  


    return &st_usbfs_v2_usb_driver;
}
