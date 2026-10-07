################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Utilities/trace/adv_trace/subdir.mk
-include Utilities/timer/subdir.mk
-include Utilities/sequencer/subdir.mk
-include Utilities/misc/subdir.mk
-include Utilities/lpm/tiny_lpm/subdir.mk
-include Middlewares/Third_Party/SubGHz_Phy/lorawan/smtc_ralf/src/subdir.mk
-include Middlewares/Third_Party/SubGHz_Phy/lorawan/smtc_ral/src/subdir.mk
-include Middlewares/Third_Party/SubGHz_Phy/lorawan/radio_planner/src/subdir.mk
-include Middlewares/Third_Party/SubGHz_Phy/lorawan/radio_drivers/sx126x_driver/src/subdir.mk
-include Middlewares/Third_Party/LoRaWAN/smtc_modem_core/smtc_modem_crypto/soft_secure_element/subdir.mk
-include Middlewares/Third_Party/LoRaWAN/smtc_modem_core/smtc_modem_crypto/subdir.mk
-include Middlewares/Third_Party/LoRaWAN/smtc_modem_core/modem_utilities/subdir.mk
-include Middlewares/Third_Party/LoRaWAN/smtc_modem_core/modem_supervisor/subdir.mk
-include Middlewares/Third_Party/LoRaWAN/smtc_modem_core/modem_services/store_and_forward/subdir.mk
-include Middlewares/Third_Party/LoRaWAN/smtc_modem_core/modem_services/service_template/subdir.mk
-include Middlewares/Third_Party/LoRaWAN/smtc_modem_core/modem_services/relay_service/subdir.mk
-include Middlewares/Third_Party/LoRaWAN/smtc_modem_core/modem_services/lfu_service/subdir.mk
-include Middlewares/Third_Party/LoRaWAN/smtc_modem_core/modem_services/beacon_tx_service/subdir.mk
-include Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lr1mac/src/smtc_real/src/subdir.mk
-include Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lr1mac/src/services/smtc_multicast/subdir.mk
-include Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lr1mac/src/services/subdir.mk
-include Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lr1mac/src/relay/relay_tx/subdir.mk
-include Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lr1mac/src/relay/relay_rx/subdir.mk
-include Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lr1mac/src/relay/common/subdir.mk
-include Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lr1mac/src/lr1mac_class_c/subdir.mk
-include Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lr1mac/src/lr1mac_class_b/subdir.mk
-include Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lr1mac/src/subdir.mk
-include Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lorawan_packages/lorawan_certification/subdir.mk
-include Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lorawan_manager/subdir.mk
-include Middlewares/Third_Party/LoRaWAN/smtc_modem_core/lorawan_api/subdir.mk
-include Middlewares/Third_Party/LoRaWAN/smtc_modem_core/subdir.mk
-include LoRaWAN/Target/subdir.mk
-include LoRaWAN/App/subdir.mk
-include Drivers/STM32WLxx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := LoRa-WAN-915MHz
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
LoRa-WAN-915MHz.elf \

MAP_FILES += \
LoRa-WAN-915MHz.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
LoRa-WAN-915MHz.list \


# All Target
all: main-build

# Main-build Target
main-build: LoRa-WAN-915MHz.elf secondary-outputs

# Tool invocations
LoRa-WAN-915MHz.elf LoRa-WAN-915MHz.map: $(OBJS) $(USER_OBJS) /home/kalata23/STM_TEST/STM32-WL_915MHz/LoRa-WAN-915MHz/STM32WLE5CCUX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "LoRa-WAN-915MHz.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"/home/kalata23/STM_TEST/STM32-WL_915MHz/LoRa-WAN-915MHz/STM32WLE5CCUX_FLASH.ld" --specs=nosys.specs -Wl,-Map="LoRa-WAN-915MHz.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

LoRa-WAN-915MHz.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "LoRa-WAN-915MHz.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) LoRa-WAN-915MHz.elf LoRa-WAN-915MHz.list LoRa-WAN-915MHz.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
