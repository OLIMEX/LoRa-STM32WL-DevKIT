################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/adc_if.c \
../Core/Src/flash_if.c \
../Core/Src/main.c \
../Core/Src/stm32_lpm_if.c \
../Core/Src/stm32wlxx_hal_msp.c \
../Core/Src/stm32wlxx_it.c \
../Core/Src/sys_app.c \
../Core/Src/sys_debug.c \
../Core/Src/sys_sensors.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32wlxx.c \
../Core/Src/timer_if.c \
../Core/Src/usart_if.c 

OBJS += \
./Core/Src/adc_if.o \
./Core/Src/flash_if.o \
./Core/Src/main.o \
./Core/Src/stm32_lpm_if.o \
./Core/Src/stm32wlxx_hal_msp.o \
./Core/Src/stm32wlxx_it.o \
./Core/Src/sys_app.o \
./Core/Src/sys_debug.o \
./Core/Src/sys_sensors.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32wlxx.o \
./Core/Src/timer_if.o \
./Core/Src/usart_if.o 

C_DEPS += \
./Core/Src/adc_if.d \
./Core/Src/flash_if.d \
./Core/Src/main.d \
./Core/Src/stm32_lpm_if.d \
./Core/Src/stm32wlxx_hal_msp.d \
./Core/Src/stm32wlxx_it.d \
./Core/Src/sys_app.d \
./Core/Src/sys_debug.d \
./Core/Src/sys_sensors.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32wlxx.d \
./Core/Src/timer_if.d \
./Core/Src/usart_if.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DNUMBER_OF_STACKS=1 -DSX126X -DENDNODE -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -c -I../Core/Inc -I../LoRaWAN/App -I../LoRaWAN/Target -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Utilities/trace/adv_trace -I../Utilities/misc -I../Utilities/sequencer -I../Utilities/timer -I../Utilities/lpm/tiny_lpm -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lorawan_api -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_hal -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lorawan_manager -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_api -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lorawan_packages/lorawan_certification -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lr1mac/src -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lr1mac/src/lr1mac_class_b -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lr1mac/src/lr1mac_class_c -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lr1mac/src/relay/common -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lr1mac/src/relay/relay_rx -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lr1mac/src/relay/relay_tx -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lr1mac/src/services/smtc_multicast -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lr1mac/src/smtc_real/src -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/modem_services/beacon_tx_service -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/modem_services/lfu_service -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/modem_services -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/modem_services/service_template -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/modem_utilities -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/smtc_modem_crypto -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/smtc_modem_crypto/smtc_secure_element -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lr1mac -I../Middlewares/Third_Party/SubGHz_Phy/lorawan -I../Middlewares/Third_Party/SubGHz_Phy/radio_driver -I../Middlewares/Third_Party/SubGHz_Phy/lorawan/radio_drivers/sx126x_driver/src -I../Middlewares/Third_Party/SubGHz_Phy/lorawan/radio_planner/src -I../Middlewares/Third_Party/SubGHz_Phy/lorawan/smtc_ral/src -I../Middlewares/Third_Party/SubGHz_Phy/lorawan/smtc_ralf/src -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lr1mac/src/services -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/modem_services/relay_service -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/modem_services/store_and_forward -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/modem_supervisor -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/smtc_modem_crypto/soft_secure_element -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/adc_if.cyclo ./Core/Src/adc_if.d ./Core/Src/adc_if.o ./Core/Src/adc_if.su ./Core/Src/flash_if.cyclo ./Core/Src/flash_if.d ./Core/Src/flash_if.o ./Core/Src/flash_if.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32_lpm_if.cyclo ./Core/Src/stm32_lpm_if.d ./Core/Src/stm32_lpm_if.o ./Core/Src/stm32_lpm_if.su ./Core/Src/stm32wlxx_hal_msp.cyclo ./Core/Src/stm32wlxx_hal_msp.d ./Core/Src/stm32wlxx_hal_msp.o ./Core/Src/stm32wlxx_hal_msp.su ./Core/Src/stm32wlxx_it.cyclo ./Core/Src/stm32wlxx_it.d ./Core/Src/stm32wlxx_it.o ./Core/Src/stm32wlxx_it.su ./Core/Src/sys_app.cyclo ./Core/Src/sys_app.d ./Core/Src/sys_app.o ./Core/Src/sys_app.su ./Core/Src/sys_debug.cyclo ./Core/Src/sys_debug.d ./Core/Src/sys_debug.o ./Core/Src/sys_debug.su ./Core/Src/sys_sensors.cyclo ./Core/Src/sys_sensors.d ./Core/Src/sys_sensors.o ./Core/Src/sys_sensors.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32wlxx.cyclo ./Core/Src/system_stm32wlxx.d ./Core/Src/system_stm32wlxx.o ./Core/Src/system_stm32wlxx.su ./Core/Src/timer_if.cyclo ./Core/Src/timer_if.d ./Core/Src/timer_if.o ./Core/Src/timer_if.su ./Core/Src/usart_if.cyclo ./Core/Src/usart_if.d ./Core/Src/usart_if.o ./Core/Src/usart_if.su

.PHONY: clean-Core-2f-Src

