################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/misc/stm32_mem.c \
../Utilities/misc/stm32_systime.c \
../Utilities/misc/stm32_tiny_sscanf.c \
../Utilities/misc/stm32_tiny_vsnprintf.c 

OBJS += \
./Utilities/misc/stm32_mem.o \
./Utilities/misc/stm32_systime.o \
./Utilities/misc/stm32_tiny_sscanf.o \
./Utilities/misc/stm32_tiny_vsnprintf.o 

C_DEPS += \
./Utilities/misc/stm32_mem.d \
./Utilities/misc/stm32_systime.d \
./Utilities/misc/stm32_tiny_sscanf.d \
./Utilities/misc/stm32_tiny_vsnprintf.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/misc/%.o Utilities/misc/%.su Utilities/misc/%.cyclo: ../Utilities/misc/%.c Utilities/misc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DNUMBER_OF_STACKS=1 -DSX126X -DENDNODE -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -c -I../Core/Inc -I../LoRaWAN/App -I../LoRaWAN/Target -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Utilities/trace/adv_trace -I../Utilities/misc -I../Utilities/sequencer -I../Utilities/timer -I../Utilities/lpm/tiny_lpm -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lorawan_api -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_hal -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lorawan_manager -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_api -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lorawan_packages/lorawan_certification -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lr1mac/src -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lr1mac/src/lr1mac_class_b -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lr1mac/src/lr1mac_class_c -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lr1mac/src/relay/common -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lr1mac/src/relay/relay_rx -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lr1mac/src/relay/relay_tx -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lr1mac/src/services/smtc_multicast -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lr1mac/src/smtc_real/src -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/modem_services/beacon_tx_service -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/modem_services/lfu_service -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/modem_services -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/modem_services/service_template -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/modem_utilities -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/smtc_modem_crypto -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/smtc_modem_crypto/smtc_secure_element -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lr1mac -I../Middlewares/Third_Party/SubGHz_Phy/lorawan -I../Middlewares/Third_Party/SubGHz_Phy/radio_driver -I../Middlewares/Third_Party/SubGHz_Phy/lorawan/radio_drivers/sx126x_driver/src -I../Middlewares/Third_Party/SubGHz_Phy/lorawan/radio_planner/src -I../Middlewares/Third_Party/SubGHz_Phy/lorawan/smtc_ral/src -I../Middlewares/Third_Party/SubGHz_Phy/lorawan/smtc_ralf/src -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lr1mac/src/services -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/modem_services/relay_service -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/modem_services/store_and_forward -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/modem_supervisor -I../Middlewares/Third_Party/LoRaWAN/smtc_modem_core/smtc_modem_crypto/soft_secure_element -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Utilities-2f-misc

clean-Utilities-2f-misc:
	-$(RM) ./Utilities/misc/stm32_mem.cyclo ./Utilities/misc/stm32_mem.d ./Utilities/misc/stm32_mem.o ./Utilities/misc/stm32_mem.su ./Utilities/misc/stm32_systime.cyclo ./Utilities/misc/stm32_systime.d ./Utilities/misc/stm32_systime.o ./Utilities/misc/stm32_systime.su ./Utilities/misc/stm32_tiny_sscanf.cyclo ./Utilities/misc/stm32_tiny_sscanf.d ./Utilities/misc/stm32_tiny_sscanf.o ./Utilities/misc/stm32_tiny_sscanf.su ./Utilities/misc/stm32_tiny_vsnprintf.cyclo ./Utilities/misc/stm32_tiny_vsnprintf.d ./Utilities/misc/stm32_tiny_vsnprintf.o ./Utilities/misc/stm32_tiny_vsnprintf.su

.PHONY: clean-Utilities-2f-misc

