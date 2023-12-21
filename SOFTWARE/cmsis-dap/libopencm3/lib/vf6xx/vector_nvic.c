/* This file is part of the libopencm3 project.
 *
 * It was generated by the irq2nvic_h script.
 *
 * This part needs to get included in the compilation unit where
 * blocking_handler gets defined due to the way #pragma works.
 */


/** @defgroup CM3_nvic_isrdecls_VF6XX User interrupt service routines (ISR) defaults for VF6xx series
    @ingroup CM3_nvic_isrdecls

    @{*/

void cpu2cpu_int0_isr(void) __attribute__((weak, alias("blocking_handler")));
void cpu2cpu_int1_isr(void) __attribute__((weak, alias("blocking_handler")));
void cpu2cpu_int2_isr(void) __attribute__((weak, alias("blocking_handler")));
void cpu2cpu_int3_isr(void) __attribute__((weak, alias("blocking_handler")));
void directed0_sema4_isr(void) __attribute__((weak, alias("blocking_handler")));
void directed1_mcm_isr(void) __attribute__((weak, alias("blocking_handler")));
void directed2_isr(void) __attribute__((weak, alias("blocking_handler")));
void directed3_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma0_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma0_error_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma1_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma1_error_isr(void) __attribute__((weak, alias("blocking_handler")));
void reserved0_isr(void) __attribute__((weak, alias("blocking_handler")));
void reserved1_isr(void) __attribute__((weak, alias("blocking_handler")));
void mscm_ecc0_isr(void) __attribute__((weak, alias("blocking_handler")));
void mscm_ecc1_isr(void) __attribute__((weak, alias("blocking_handler")));
void csu_alarm_isr(void) __attribute__((weak, alias("blocking_handler")));
void reserved2_isr(void) __attribute__((weak, alias("blocking_handler")));
void mscm_actzs_isr(void) __attribute__((weak, alias("blocking_handler")));
void reserved3_isr(void) __attribute__((weak, alias("blocking_handler")));
void wdog_a5_isr(void) __attribute__((weak, alias("blocking_handler")));
void wdog_m4_isr(void) __attribute__((weak, alias("blocking_handler")));
void wdog_snvs_isr(void) __attribute__((weak, alias("blocking_handler")));
void cp1_boot_fail_isr(void) __attribute__((weak, alias("blocking_handler")));
void qspi0_isr(void) __attribute__((weak, alias("blocking_handler")));
void qspi1_isr(void) __attribute__((weak, alias("blocking_handler")));
void ddrmc_isr(void) __attribute__((weak, alias("blocking_handler")));
void sdhc0_isr(void) __attribute__((weak, alias("blocking_handler")));
void sdhc1_isr(void) __attribute__((weak, alias("blocking_handler")));
void reserved4_isr(void) __attribute__((weak, alias("blocking_handler")));
void dcu0_isr(void) __attribute__((weak, alias("blocking_handler")));
void dcu1_isr(void) __attribute__((weak, alias("blocking_handler")));
void viu_isr(void) __attribute__((weak, alias("blocking_handler")));
void reserved5_isr(void) __attribute__((weak, alias("blocking_handler")));
void reserved6_isr(void) __attribute__((weak, alias("blocking_handler")));
void rle_isr(void) __attribute__((weak, alias("blocking_handler")));
void seg_lcd_isr(void) __attribute__((weak, alias("blocking_handler")));
void reserved7_isr(void) __attribute__((weak, alias("blocking_handler")));
void reserved8_isr(void) __attribute__((weak, alias("blocking_handler")));
void pit_isr(void) __attribute__((weak, alias("blocking_handler")));
void lptimer0_isr(void) __attribute__((weak, alias("blocking_handler")));
void reserved9_isr(void) __attribute__((weak, alias("blocking_handler")));
void flextimer0_isr(void) __attribute__((weak, alias("blocking_handler")));
void flextimer1_isr(void) __attribute__((weak, alias("blocking_handler")));
void flextimer2_isr(void) __attribute__((weak, alias("blocking_handler")));
void flextimer3_isr(void) __attribute__((weak, alias("blocking_handler")));
void reserved10_isr(void) __attribute__((weak, alias("blocking_handler")));
void reserved11_isr(void) __attribute__((weak, alias("blocking_handler")));
void reserved12_isr(void) __attribute__((weak, alias("blocking_handler")));
void reserved13_isr(void) __attribute__((weak, alias("blocking_handler")));
void usbphy0_isr(void) __attribute__((weak, alias("blocking_handler")));
void usbphy1_isr(void) __attribute__((weak, alias("blocking_handler")));
void reserved14_isr(void) __attribute__((weak, alias("blocking_handler")));
void adc0_isr(void) __attribute__((weak, alias("blocking_handler")));
void adc1_isr(void) __attribute__((weak, alias("blocking_handler")));
void dac0_isr(void) __attribute__((weak, alias("blocking_handler")));
void dac1_isr(void) __attribute__((weak, alias("blocking_handler")));
void reserved15_isr(void) __attribute__((weak, alias("blocking_handler")));
void flexcan0_isr(void) __attribute__((weak, alias("blocking_handler")));
void flexcan1_isr(void) __attribute__((weak, alias("blocking_handler")));
void reserved16_isr(void) __attribute__((weak, alias("blocking_handler")));
void uart0_isr(void) __attribute__((weak, alias("blocking_handler")));
void uart1_isr(void) __attribute__((weak, alias("blocking_handler")));
void uart2_isr(void) __attribute__((weak, alias("blocking_handler")));
void uart3_isr(void) __attribute__((weak, alias("blocking_handler")));
void uart4_isr(void) __attribute__((weak, alias("blocking_handler")));
void uart5_isr(void) __attribute__((weak, alias("blocking_handler")));
void spi0_isr(void) __attribute__((weak, alias("blocking_handler")));
void spi1_isr(void) __attribute__((weak, alias("blocking_handler")));
void spi2_isr(void) __attribute__((weak, alias("blocking_handler")));
void spi3_isr(void) __attribute__((weak, alias("blocking_handler")));
void i2c0_isr(void) __attribute__((weak, alias("blocking_handler")));
void i2c1_isr(void) __attribute__((weak, alias("blocking_handler")));
void i2c2_isr(void) __attribute__((weak, alias("blocking_handler")));
void i2c3_isr(void) __attribute__((weak, alias("blocking_handler")));
void usbc0_isr(void) __attribute__((weak, alias("blocking_handler")));
void usbc1_isr(void) __attribute__((weak, alias("blocking_handler")));
void reserved17_isr(void) __attribute__((weak, alias("blocking_handler")));
void enet0_isr(void) __attribute__((weak, alias("blocking_handler")));
void enet1_isr(void) __attribute__((weak, alias("blocking_handler")));
void enet0_1588_isr(void) __attribute__((weak, alias("blocking_handler")));
void enet1_1588_isr(void) __attribute__((weak, alias("blocking_handler")));
void enet_switch_isr(void) __attribute__((weak, alias("blocking_handler")));
void nfc_isr(void) __attribute__((weak, alias("blocking_handler")));
void sai0_isr(void) __attribute__((weak, alias("blocking_handler")));
void sai1_isr(void) __attribute__((weak, alias("blocking_handler")));
void sai2_isr(void) __attribute__((weak, alias("blocking_handler")));
void sai3_isr(void) __attribute__((weak, alias("blocking_handler")));
void esai_bififo_isr(void) __attribute__((weak, alias("blocking_handler")));
void spdif_isr(void) __attribute__((weak, alias("blocking_handler")));
void asrc_isr(void) __attribute__((weak, alias("blocking_handler")));
void vreg_isr(void) __attribute__((weak, alias("blocking_handler")));
void wkpu0_isr(void) __attribute__((weak, alias("blocking_handler")));
void reserved18_isr(void) __attribute__((weak, alias("blocking_handler")));
void ccm_fxosc_isr(void) __attribute__((weak, alias("blocking_handler")));
void ccm_isr(void) __attribute__((weak, alias("blocking_handler")));
void src_isr(void) __attribute__((weak, alias("blocking_handler")));
void pdb_isr(void) __attribute__((weak, alias("blocking_handler")));
void ewm_isr(void) __attribute__((weak, alias("blocking_handler")));
void reserved19_isr(void) __attribute__((weak, alias("blocking_handler")));
void reserved20_isr(void) __attribute__((weak, alias("blocking_handler")));
void reserved21_isr(void) __attribute__((weak, alias("blocking_handler")));
void reserved22_isr(void) __attribute__((weak, alias("blocking_handler")));
void reserved23_isr(void) __attribute__((weak, alias("blocking_handler")));
void reserved24_isr(void) __attribute__((weak, alias("blocking_handler")));
void reserved25_isr(void) __attribute__((weak, alias("blocking_handler")));
void reserved26_isr(void) __attribute__((weak, alias("blocking_handler")));
void gpio0_isr(void) __attribute__((weak, alias("blocking_handler")));
void gpio1_isr(void) __attribute__((weak, alias("blocking_handler")));
void gpio2_isr(void) __attribute__((weak, alias("blocking_handler")));
void gpio3_isr(void) __attribute__((weak, alias("blocking_handler")));
void gpio4_isr(void) __attribute__((weak, alias("blocking_handler")));

/**@}*/

/* Initialization template for the interrupt vector table. This definition is
 * used by the startup code generator (vector.c) to set the initial values for
 * the interrupt handling routines to the chip family specific _isr weak
 * symbols. */

#define IRQ_HANDLERS \
    [NVIC_CPU2CPU_INT0_IRQ] = cpu2cpu_int0_isr, \
    [NVIC_CPU2CPU_INT1_IRQ] = cpu2cpu_int1_isr, \
    [NVIC_CPU2CPU_INT2_IRQ] = cpu2cpu_int2_isr, \
    [NVIC_CPU2CPU_INT3_IRQ] = cpu2cpu_int3_isr, \
    [NVIC_DIRECTED0_SEMA4_IRQ] = directed0_sema4_isr, \
    [NVIC_DIRECTED1_MCM_IRQ] = directed1_mcm_isr, \
    [NVIC_DIRECTED2_IRQ] = directed2_isr, \
    [NVIC_DIRECTED3_IRQ] = directed3_isr, \
    [NVIC_DMA0_IRQ] = dma0_isr, \
    [NVIC_DMA0_ERROR_IRQ] = dma0_error_isr, \
    [NVIC_DMA1_IRQ] = dma1_isr, \
    [NVIC_DMA1_ERROR_IRQ] = dma1_error_isr, \
    [NVIC_RESERVED0_IRQ] = reserved0_isr, \
    [NVIC_RESERVED1_IRQ] = reserved1_isr, \
    [NVIC_MSCM_ECC0_IRQ] = mscm_ecc0_isr, \
    [NVIC_MSCM_ECC1_IRQ] = mscm_ecc1_isr, \
    [NVIC_CSU_ALARM_IRQ] = csu_alarm_isr, \
    [NVIC_RESERVED2_IRQ] = reserved2_isr, \
    [NVIC_MSCM_ACTZS_IRQ] = mscm_actzs_isr, \
    [NVIC_RESERVED3_IRQ] = reserved3_isr, \
    [NVIC_WDOG_A5_IRQ] = wdog_a5_isr, \
    [NVIC_WDOG_M4_IRQ] = wdog_m4_isr, \
    [NVIC_WDOG_SNVS_IRQ] = wdog_snvs_isr, \
    [NVIC_CP1_BOOT_FAIL_IRQ] = cp1_boot_fail_isr, \
    [NVIC_QSPI0_IRQ] = qspi0_isr, \
    [NVIC_QSPI1_IRQ] = qspi1_isr, \
    [NVIC_DDRMC_IRQ] = ddrmc_isr, \
    [NVIC_SDHC0_IRQ] = sdhc0_isr, \
    [NVIC_SDHC1_IRQ] = sdhc1_isr, \
    [NVIC_RESERVED4_IRQ] = reserved4_isr, \
    [NVIC_DCU0_IRQ] = dcu0_isr, \
    [NVIC_DCU1_IRQ] = dcu1_isr, \
    [NVIC_VIU_IRQ] = viu_isr, \
    [NVIC_RESERVED5_IRQ] = reserved5_isr, \
    [NVIC_RESERVED6_IRQ] = reserved6_isr, \
    [NVIC_RLE_IRQ] = rle_isr, \
    [NVIC_SEG_LCD_IRQ] = seg_lcd_isr, \
    [NVIC_RESERVED7_IRQ] = reserved7_isr, \
    [NVIC_RESERVED8_IRQ] = reserved8_isr, \
    [NVIC_PIT_IRQ] = pit_isr, \
    [NVIC_LPTIMER0_IRQ] = lptimer0_isr, \
    [NVIC_RESERVED9_IRQ] = reserved9_isr, \
    [NVIC_FLEXTIMER0_IRQ] = flextimer0_isr, \
    [NVIC_FLEXTIMER1_IRQ] = flextimer1_isr, \
    [NVIC_FLEXTIMER2_IRQ] = flextimer2_isr, \
    [NVIC_FLEXTIMER3_IRQ] = flextimer3_isr, \
    [NVIC_RESERVED10_IRQ] = reserved10_isr, \
    [NVIC_RESERVED11_IRQ] = reserved11_isr, \
    [NVIC_RESERVED12_IRQ] = reserved12_isr, \
    [NVIC_RESERVED13_IRQ] = reserved13_isr, \
    [NVIC_USBPHY0_IRQ] = usbphy0_isr, \
    [NVIC_USBPHY1_IRQ] = usbphy1_isr, \
    [NVIC_RESERVED14_IRQ] = reserved14_isr, \
    [NVIC_ADC0_IRQ] = adc0_isr, \
    [NVIC_ADC1_IRQ] = adc1_isr, \
    [NVIC_DAC0_IRQ] = dac0_isr, \
    [NVIC_DAC1_IRQ] = dac1_isr, \
    [NVIC_RESERVED15_IRQ] = reserved15_isr, \
    [NVIC_FLEXCAN0_IRQ] = flexcan0_isr, \
    [NVIC_FLEXCAN1_IRQ] = flexcan1_isr, \
    [NVIC_RESERVED16_IRQ] = reserved16_isr, \
    [NVIC_UART0_IRQ] = uart0_isr, \
    [NVIC_UART1_IRQ] = uart1_isr, \
    [NVIC_UART2_IRQ] = uart2_isr, \
    [NVIC_UART3_IRQ] = uart3_isr, \
    [NVIC_UART4_IRQ] = uart4_isr, \
    [NVIC_UART5_IRQ] = uart5_isr, \
    [NVIC_SPI0_IRQ] = spi0_isr, \
    [NVIC_SPI1_IRQ] = spi1_isr, \
    [NVIC_SPI2_IRQ] = spi2_isr, \
    [NVIC_SPI3_IRQ] = spi3_isr, \
    [NVIC_I2C0_IRQ] = i2c0_isr, \
    [NVIC_I2C1_IRQ] = i2c1_isr, \
    [NVIC_I2C2_IRQ] = i2c2_isr, \
    [NVIC_I2C3_IRQ] = i2c3_isr, \
    [NVIC_USBC0_IRQ] = usbc0_isr, \
    [NVIC_USBC1_IRQ] = usbc1_isr, \
    [NVIC_RESERVED17_IRQ] = reserved17_isr, \
    [NVIC_ENET0_IRQ] = enet0_isr, \
    [NVIC_ENET1_IRQ] = enet1_isr, \
    [NVIC_ENET0_1588_IRQ] = enet0_1588_isr, \
    [NVIC_ENET1_1588_IRQ] = enet1_1588_isr, \
    [NVIC_ENET_SWITCH_IRQ] = enet_switch_isr, \
    [NVIC_NFC_IRQ] = nfc_isr, \
    [NVIC_SAI0_IRQ] = sai0_isr, \
    [NVIC_SAI1_IRQ] = sai1_isr, \
    [NVIC_SAI2_IRQ] = sai2_isr, \
    [NVIC_SAI3_IRQ] = sai3_isr, \
    [NVIC_ESAI_BIFIFO_IRQ] = esai_bififo_isr, \
    [NVIC_SPDIF_IRQ] = spdif_isr, \
    [NVIC_ASRC_IRQ] = asrc_isr, \
    [NVIC_VREG_IRQ] = vreg_isr, \
    [NVIC_WKPU0_IRQ] = wkpu0_isr, \
    [NVIC_RESERVED18_IRQ] = reserved18_isr, \
    [NVIC_CCM_FXOSC_IRQ] = ccm_fxosc_isr, \
    [NVIC_CCM_IRQ] = ccm_isr, \
    [NVIC_SRC_IRQ] = src_isr, \
    [NVIC_PDB_IRQ] = pdb_isr, \
    [NVIC_EWM_IRQ] = ewm_isr, \
    [NVIC_RESERVED19_IRQ] = reserved19_isr, \
    [NVIC_RESERVED20_IRQ] = reserved20_isr, \
    [NVIC_RESERVED21_IRQ] = reserved21_isr, \
    [NVIC_RESERVED22_IRQ] = reserved22_isr, \
    [NVIC_RESERVED23_IRQ] = reserved23_isr, \
    [NVIC_RESERVED24_IRQ] = reserved24_isr, \
    [NVIC_RESERVED25_IRQ] = reserved25_isr, \
    [NVIC_RESERVED26_IRQ] = reserved26_isr, \
    [NVIC_GPIO0_IRQ] = gpio0_isr, \
    [NVIC_GPIO1_IRQ] = gpio1_isr, \
    [NVIC_GPIO2_IRQ] = gpio2_isr, \
    [NVIC_GPIO3_IRQ] = gpio3_isr, \
    [NVIC_GPIO4_IRQ] = gpio4_isr