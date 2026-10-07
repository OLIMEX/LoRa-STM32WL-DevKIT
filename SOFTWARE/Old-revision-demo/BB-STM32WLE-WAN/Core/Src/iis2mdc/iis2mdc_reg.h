/**
  ******************************************************************************
  * @file    iis2mdc_reg.h
  * @author  Sensors Software Solution Team
  * @brief   This file contains all the functions prototypes for the
  *          iis2mdc_reg.c driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef IIS2MDC_REGS_H
#define IIS2MDC_REGS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include <math.h>
#include "stm32wlxx_hal.h"
/** @addtogroup IIS2MDC
  * @{
  *
  */

/** @defgroup  Endianness definitions
  * @{
  *
  */

#ifndef DRV_BYTE_ORDER
#ifndef __BYTE_ORDER__

#define DRV_LITTLE_ENDIAN 1234
#define DRV_BIG_ENDIAN    4321

/** if _BYTE_ORDER is not defined, choose the endianness of your architecture
  * by uncommenting the define which fits your platform endianness
  */
//#define DRV_BYTE_ORDER    DRV_BIG_ENDIAN
#define DRV_BYTE_ORDER    DRV_LITTLE_ENDIAN

#else /* defined __BYTE_ORDER__ */

#define DRV_LITTLE_ENDIAN  __ORDER_LITTLE_ENDIAN__
#define DRV_BIG_ENDIAN     __ORDER_BIG_ENDIAN__
#define DRV_BYTE_ORDER     __BYTE_ORDER__

#endif /* __BYTE_ORDER__*/
#endif /* DRV_BYTE_ORDER */

/**
  * @}
  *
  */

/** @defgroup STMicroelectronics sensors common types
  * @{
  *
  */

#ifndef MEMS_SHARED_TYPES
#define MEMS_SHARED_TYPES

typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t bit0       : 1;
  uint8_t bit1       : 1;
  uint8_t bit2       : 1;
  uint8_t bit3       : 1;
  uint8_t bit4       : 1;
  uint8_t bit5       : 1;
  uint8_t bit6       : 1;
  uint8_t bit7       : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t bit7       : 1;
  uint8_t bit6       : 1;
  uint8_t bit5       : 1;
  uint8_t bit4       : 1;
  uint8_t bit3       : 1;
  uint8_t bit2       : 1;
  uint8_t bit1       : 1;
  uint8_t bit0       : 1;
#endif /* DRV_BYTE_ORDER */
} bitwise_t;

#define PROPERTY_DISABLE                (0U)
#define PROPERTY_ENABLE                 (1U)

/** @addtogroup  Interfaces_Functions
  * @brief       This section provide a set of functions used to read and
  *              write a generic register of the device.
  *              MANDATORY: return 0 -> no Error.
  * @{
  *
  */

typedef int32_t (*stmdev_write_ptr)(void *, uint8_t, const uint8_t *, uint16_t);
typedef int32_t (*stmdev_read_ptr)(void *, uint8_t, uint8_t *, uint16_t);

typedef struct
{
  /** Component mandatory fields **/
  stmdev_write_ptr  write_reg;
  stmdev_read_ptr   read_reg;
  /** Customizable optional pointer **/
 // void *handle;
  uint16_t addr;
  I2C_HandleTypeDef* i2c;
} MAG_HandleTypedef;

/**
  * @}
  *
  */

#endif /* MEMS_SHARED_TYPES */

#ifndef MEMS_UCF_SHARED_TYPES
#define MEMS_UCF_SHARED_TYPES

/** @defgroup    Generic address-data structure definition
  * @brief       This structure is useful to load a predefined configuration
  *              of a sensor.
  *              You can create a sensor configuration by your own or using
  *              Unico / Unicleo tools available on STMicroelectronics
  *              web site.
  *
  * @{
  *
  */

typedef struct
{
  uint8_t address;
  uint8_t data;
} ucf_line_t;

/**
  * @}
  *
  */

#endif /* MEMS_UCF_SHARED_TYPES */

/**
  * @}
  *
  */

/** @defgroup iis2mdc_Infos
  * @{
  *
  */

/** I2C Device Address 8 bit format **/
#define IIS2MDC_I2C_ADD       0x1EU

/** Device Identification (Who am I) **/
#define IIS2MDC_ID            0x40U

/**
  * @}
  *
  */

#define IIS2MDC_OFFSET_X_REG_L          0x45U
#define IIS2MDC_OFFSET_X_REG_H          0x46U
#define IIS2MDC_OFFSET_Y_REG_L          0x47U
#define IIS2MDC_OFFSET_Y_REG_H          0x48U
#define IIS2MDC_OFFSET_Z_REG_L          0x49U
#define IIS2MDC_OFFSET_Z_REG_H          0x4AU
#define IIS2MDC_WHO_AM_I                0x4FU
#define IIS2MDC_CFG_REG_A               0x60U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t md                     : 2;
  uint8_t odr                    : 2;
  uint8_t lp                     : 1;
  uint8_t soft_rst               : 1;
  uint8_t reboot                 : 1;
  uint8_t comp_temp_en           : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t comp_temp_en           : 1;
  uint8_t reboot                 : 1;
  uint8_t soft_rst               : 1;
  uint8_t lp                     : 1;
  uint8_t odr                    : 2;
  uint8_t md                     : 2;
#endif /* DRV_BYTE_ORDER */
} iis2mdc_cfg_reg_a_t;

#define IIS2MDC_CFG_REG_B               0x61U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t lpf                    : 1;
  uint8_t set_rst                : 2; /* OFF_CANC + Set_FREQ */
  uint8_t int_on_dataoff         : 1;
  uint8_t off_canc_one_shot      : 1;
  uint8_t not_used_01            : 3;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01            : 3;
  uint8_t off_canc_one_shot      : 1;
  uint8_t int_on_dataoff         : 1;
  uint8_t set_rst                : 2; /* OFF_CANC + Set_FREQ */
  uint8_t lpf                    : 1;
#endif /* DRV_BYTE_ORDER */
} iis2mdc_cfg_reg_b_t;

#define IIS2MDC_CFG_REG_C               0x62U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t drdy_on_pin            : 1;
  uint8_t self_test              : 1;
  uint8_t not_used_01            : 1;
  uint8_t ble                    : 1;
  uint8_t bdu                    : 1;
  uint8_t i2c_dis                : 1;
  uint8_t int_on_pin             : 1;
  uint8_t not_used_02            : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_02            : 1;
  uint8_t int_on_pin             : 1;
  uint8_t i2c_dis                : 1;
  uint8_t bdu                    : 1;
  uint8_t ble                    : 1;
  uint8_t not_used_01            : 1;
  uint8_t self_test              : 1;
  uint8_t drdy_on_pin            : 1;
#endif /* DRV_BYTE_ORDER */
} iis2mdc_cfg_reg_c_t;

#define IIS2MDC_INT_CRTL_REG            0x63U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t ien                    : 1;
  uint8_t iel                    : 1;
  uint8_t iea                    : 1;
  uint8_t not_used_01            : 2;
  uint8_t zien                   : 1;
  uint8_t yien                   : 1;
  uint8_t xien                   : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t xien                   : 1;
  uint8_t yien                   : 1;
  uint8_t zien                   : 1;
  uint8_t not_used_01            : 2;
  uint8_t iea                    : 1;
  uint8_t iel                    : 1;
  uint8_t ien                    : 1;
#endif /* DRV_BYTE_ORDER */
} iis2mdc_int_crtl_reg_t;

#define IIS2MDC_INT_SOURCE_REG          0x64U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t _int                   : 1;
  uint8_t mroi                   : 1;
  uint8_t n_th_s_z               : 1;
  uint8_t n_th_s_y               : 1;
  uint8_t n_th_s_x               : 1;
  uint8_t p_th_s_z               : 1;
  uint8_t p_th_s_y               : 1;
  uint8_t p_th_s_x               : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t p_th_s_x               : 1;
  uint8_t p_th_s_y               : 1;
  uint8_t p_th_s_z               : 1;
  uint8_t n_th_s_x               : 1;
  uint8_t n_th_s_y               : 1;
  uint8_t n_th_s_z               : 1;
  uint8_t mroi                   : 1;
  uint8_t _int                   : 1;
#endif /* DRV_BYTE_ORDER */

} iis2mdc_int_source_reg_t;

#define IIS2MDC_INT_THS_L_REG           0x65U
#define IIS2MDC_INT_THS_H_REG           0x66U
#define IIS2MDC_STATUS_REG              0x67U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t xda                    : 1;
  uint8_t yda                    : 1;
  uint8_t zda                    : 1;
  uint8_t zyxda                  : 1;
  uint8_t _xor                   : 1;
  uint8_t yor                    : 1;
  uint8_t zor                    : 1;
  uint8_t zyxor                  : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t zyxor                  : 1;
  uint8_t zor                    : 1;
  uint8_t yor                    : 1;
  uint8_t _xor                   : 1;
  uint8_t zyxda                  : 1;
  uint8_t zda                    : 1;
  uint8_t yda                    : 1;
  uint8_t xda                    : 1;
#endif /* DRV_BYTE_ORDER */
} iis2mdc_status_reg_t;

#define IIS2MDC_OUTX_L_REG              0x68U
#define IIS2MDC_OUTX_H_REG              0x69U
#define IIS2MDC_OUTY_L_REG              0x6AU
#define IIS2MDC_OUTY_H_REG              0x6BU
#define IIS2MDC_OUTZ_L_REG              0x6CU
#define IIS2MDC_OUTZ_H_REG              0x6DU
#define IIS2MDC_TEMP_OUT_L_REG          0x6EU
#define IIS2MDC_TEMP_OUT_H_REG          0x6FU

typedef union
{
  iis2mdc_cfg_reg_a_t            cfg_reg_a;
  iis2mdc_cfg_reg_b_t            cfg_reg_b;
  iis2mdc_cfg_reg_c_t            cfg_reg_c;
  iis2mdc_int_crtl_reg_t         int_crtl_reg;
  iis2mdc_int_source_reg_t       int_source_reg;
  iis2mdc_status_reg_t           status_reg;
  bitwise_t                      bitwise;
  uint8_t                        byte;
} iis2mdc_reg_t;

int32_t iis2mdc_read_reg(MAG_HandleTypedef *ctx, uint8_t reg,
                         uint8_t *data,
                         uint16_t len);
int32_t iis2mdc_write_reg(MAG_HandleTypedef *ctx, uint8_t reg,
                          uint8_t *data,
                          uint16_t len);

float_t iis2mdc_from_lsb_to_mgauss(int16_t lsb);
float_t iis2mdc_from_lsb_to_celsius(int16_t lsb);

int32_t iis2mdc_mag_user_offset_set(MAG_HandleTypedef *ctx, int16_t *val);
int32_t iis2mdc_mag_user_offset_get(MAG_HandleTypedef *ctx, int16_t *val);
typedef enum
{
  IIS2MDC_CONTINUOUS_MODE  = 0,
  IIS2MDC_SINGLE_TRIGGER   = 1,
  IIS2MDC_POWER_DOWN       = 2,
} iis2mdc_md_t;
int32_t iis2mdc_operating_mode_set(MAG_HandleTypedef *ctx,
                                   iis2mdc_md_t val);
int32_t iis2mdc_operating_mode_get(MAG_HandleTypedef *ctx,
                                   iis2mdc_md_t *val);

typedef enum
{
  IIS2MDC_ODR_10Hz   = 0,
  IIS2MDC_ODR_20Hz   = 1,
  IIS2MDC_ODR_50Hz   = 2,
  IIS2MDC_ODR_100Hz  = 3,
} iis2mdc_odr_t;
int32_t iis2mdc_data_rate_set(MAG_HandleTypedef *ctx, iis2mdc_odr_t val);
int32_t iis2mdc_data_rate_get(MAG_HandleTypedef *ctx, iis2mdc_odr_t *val);

typedef enum
{
  IIS2MDC_HIGH_RESOLUTION  = 0,
  IIS2MDC_LOW_POWER        = 1,
} iis2mdc_lp_t;
int32_t iis2mdc_power_mode_set(MAG_HandleTypedef *ctx, iis2mdc_lp_t val);
int32_t iis2mdc_power_mode_get(MAG_HandleTypedef *ctx, iis2mdc_lp_t *val);

int32_t iis2mdc_offset_temp_comp_set(MAG_HandleTypedef *ctx, uint8_t val);
int32_t iis2mdc_offset_temp_comp_get(MAG_HandleTypedef *ctx, uint8_t *val);

typedef enum
{
  IIS2MDC_ODR_DIV_2  = 0,
  IIS2MDC_ODR_DIV_4  = 1,
} iis2mdc_lpf_t;
int32_t iis2mdc_low_pass_bandwidth_set(MAG_HandleTypedef *ctx,
                                       iis2mdc_lpf_t val);
int32_t iis2mdc_low_pass_bandwidth_get(MAG_HandleTypedef *ctx,
                                       iis2mdc_lpf_t *val);

typedef enum
{
  IIS2MDC_SET_SENS_ODR_DIV_63        = 0,
  IIS2MDC_SENS_OFF_CANC_EVERY_ODR    = 1,
  IIS2MDC_SET_SENS_ONLY_AT_POWER_ON  = 2,
} iis2mdc_set_rst_t;
int32_t iis2mdc_set_rst_mode_set(MAG_HandleTypedef *ctx,
                                 iis2mdc_set_rst_t val);
int32_t iis2mdc_set_rst_mode_get(MAG_HandleTypedef *ctx,
                                 iis2mdc_set_rst_t *val);

int32_t iis2mdc_set_rst_sensor_single_set(MAG_HandleTypedef *ctx,
                                          uint8_t val);
int32_t iis2mdc_set_rst_sensor_single_get(MAG_HandleTypedef *ctx,
                                          uint8_t *val);

int32_t iis2mdc_block_data_update_set(MAG_HandleTypedef *ctx, uint8_t val);
int32_t iis2mdc_block_data_update_get(MAG_HandleTypedef *ctx,
                                      uint8_t *val);

int32_t iis2mdc_mag_data_ready_get(MAG_HandleTypedef *ctx, uint8_t *val);

int32_t iis2mdc_mag_data_ovr_get(MAG_HandleTypedef *ctx, uint8_t *val);

int32_t iis2mdc_magnetic_raw_get(MAG_HandleTypedef *ctx, int16_t *val);

int32_t iis2mdc_temperature_raw_get(MAG_HandleTypedef *ctx, int16_t *val);

int32_t iis2mdc_device_id_get(MAG_HandleTypedef *ctx, uint8_t *buff);

int32_t iis2mdc_reset_set(MAG_HandleTypedef *ctx, uint8_t val);
int32_t iis2mdc_reset_get(MAG_HandleTypedef *ctx, uint8_t *val);

int32_t iis2mdc_boot_set(MAG_HandleTypedef *ctx, uint8_t val);
int32_t iis2mdc_boot_get(MAG_HandleTypedef *ctx, uint8_t *val);

int32_t iis2mdc_self_test_set(MAG_HandleTypedef *ctx, uint8_t val);
int32_t iis2mdc_self_test_get(MAG_HandleTypedef *ctx, uint8_t *val);

typedef enum
{
  IIS2MDC_LSB_AT_LOW_ADD  = 0,
  IIS2MDC_MSB_AT_LOW_ADD  = 1,
} iis2mdc_ble_t;
int32_t iis2mdc_data_format_set(MAG_HandleTypedef *ctx, iis2mdc_ble_t val);
int32_t iis2mdc_data_format_get(MAG_HandleTypedef *ctx,
                                iis2mdc_ble_t *val);

int32_t iis2mdc_status_get(MAG_HandleTypedef *ctx,
                           iis2mdc_status_reg_t *val);
#define IIS2MDC_MAG_SENSITIVITY_FS_50GAUSS  1.500f  /**< Sensitivity value for 50 gauss full scale [mgauss/LSB] */
typedef enum
{
  IIS2MDC_CHECK_BEFORE  = 0,
  IIS2MDC_CHECK_AFTER   = 1,
} iis2mdc_int_on_dataoff_t;
int32_t iis2mdc_offset_int_conf_set(MAG_HandleTypedef *ctx,
                                    iis2mdc_int_on_dataoff_t val);
int32_t iis2mdc_offset_int_conf_get(MAG_HandleTypedef *ctx,
                                    iis2mdc_int_on_dataoff_t *val);

int32_t iis2mdc_drdy_on_pin_set(MAG_HandleTypedef *ctx, uint8_t val);
int32_t iis2mdc_drdy_on_pin_get(MAG_HandleTypedef *ctx, uint8_t *val);

int32_t iis2mdc_int_on_pin_set(MAG_HandleTypedef *ctx, uint8_t val);
int32_t iis2mdc_int_on_pin_get(MAG_HandleTypedef *ctx, uint8_t *val);

int32_t iis2mdc_int_gen_conf_set(MAG_HandleTypedef *ctx,
                                 iis2mdc_int_crtl_reg_t *val);
int32_t iis2mdc_int_gen_conf_get(MAG_HandleTypedef *ctx,
                                 iis2mdc_int_crtl_reg_t *val);

int32_t iis2mdc_int_gen_source_get(MAG_HandleTypedef *ctx,
                                   iis2mdc_int_source_reg_t *val);

int32_t iis2mdc_int_gen_treshold_set(MAG_HandleTypedef *ctx, int16_t val);
int32_t iis2mdc_int_gen_treshold_get(MAG_HandleTypedef *ctx, int16_t *val);
typedef enum
{
  IIS2MDC_OK = 0,
  IIS2MDC_ERROR =-1
} IIS2MDCStatusTypeDef;
typedef struct
{
  int16_t x;
  int16_t y;
  int16_t z;
} IIS2MDC_AxesRaw_t;

typedef struct
{
  int32_t x;
  int32_t y;
  int32_t z;
} IIS2MDC_Axes_t;
typedef union{
  int16_t i16bit[3];
  uint8_t u8bit[6];
} axis3bit16_t;

typedef union{
  int16_t i16bit;
  uint8_t u8bit[2];
} axis1bit16_t;

typedef union{
  int32_t i32bit[3];
  uint8_t u8bit[12];
} axis3bit32_t;

typedef union{
  int32_t i32bit;
  uint8_t u8bit[4];
} axis1bit32_t;
typedef enum
{
  IIS2MDC_I2C_ENABLE   = 0,
  IIS2MDC_I2C_DISABLE  = 1,
} iis2mdc_i2c_dis_t;
int32_t iis2mdc_i2c_interface_set(MAG_HandleTypedef *ctx,
                                  iis2mdc_i2c_dis_t val);
int32_t iis2mdc_i2c_interface_get(MAG_HandleTypedef *ctx,
                                  iis2mdc_i2c_dis_t *val);

/**
  * @}
  *
  */

#ifdef __cplusplus
}
#endif

#endif /* IIS2MDC_REGS_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
