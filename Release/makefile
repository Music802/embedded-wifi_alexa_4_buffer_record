################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include xip/subdir.mk
-include wifi_wwd/platform/subdir.mk
-include wifi_wwd/network/subdir.mk
-include wifi_wwd/WWD/internal/chips/subdir.mk
-include wifi_wwd/WWD/internal/bus_protocols/SDIO/subdir.mk
-include wifi_wwd/WWD/internal/bus_protocols/subdir.mk
-include wifi_wwd/WWD/internal/subdir.mk
-include wifi_wwd/FreeRTOS/subdir.mk
-include wifi_wwd/subdir.mk
-include utilities/subdir.mk
-include usb/phy/subdir.mk
-include usb/device/source/ehci/subdir.mk
-include usb/device/source/subdir.mk
-include startup/subdir.mk
-include source/subdir.mk
-include sdmmc/src/subdir.mk
-include sdmmc/port/subdir.mk
-include osa/subdir.mk
-include lwip/src/netif/ppp/polarssl/subdir.mk
-include lwip/src/netif/ppp/subdir.mk
-include lwip/src/netif/subdir.mk
-include lwip/src/core/ipv6/subdir.mk
-include lwip/src/core/ipv4/subdir.mk
-include lwip/src/core/subdir.mk
-include lwip/src/api/subdir.mk
-include lwip/port/subdir.mk
-include drivers/subdir.mk
-include device/subdir.mk
-include component/uart/subdir.mk
-include component/serial_manager/usb_cdc_adapter/subdir.mk
-include component/serial_manager/subdir.mk
-include component/lists/subdir.mk
-include codec/subdir.mk
-include board/subdir.mk
-include audio/pdm_mic/subdir.mk
-include audio/audio_samples/subdir.mk
-include audio/audio_processing/subdir.mk
-include audio/amplifier/subdir.mk
-include audio/amazon/subdir.mk
-include amazon-freertos/FreeRTOS/portable/subdir.mk
-include amazon-freertos/FreeRTOS/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: uvoice1060_bare_afe.axf

# Tool invocations
uvoice1060_bare_afe.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\matlab\Documents\MCUXpressoIDE_10.3.1_2233\workspace4\uvoice1060_bare_afe\libs" -L/uvoice1060_bare_afe/wifi_wwd/network -L/uvoice1060_bare_afe/wifi_wwd/WWD/include/network -L/uvoice1060_bare_afe/lwip/src/include/lwip -L/uvoice1060_bare_afe/lwip/src/api -L"C:\Users\matlab\Documents\MCUXpressoIDE_10.3.1_2233\workspace4\uvoice1060_bare_afe\wifi_wwd\WWD\include" -L"C:\Users\matlab\Documents\MCUXpressoIDE_10.3.1_2233\workspace4\uvoice1060_bare_afe\wifi_wwd" -L"C:\Users\matlab\Documents\MCUXpressoIDE_10.3.1_2233\workspace4\uvoice1060_bare_afe\Release" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker -Map="uvoice1060_bare_afe.map" -Xlinker --sort-section=alignment -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -T uvoice1060_bare_afe_Release.ld -o "uvoice1060_bare_afe.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) uvoice1060_bare_afe.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "uvoice1060_bare_afe.axf"; # arm-none-eabi-objcopy -v -O binary "uvoice1060_bare_afe.axf" "uvoice1060_bare_afe.bin" ; # checksum -p MIMXRT1062xxxxA -d "uvoice1060_bare_afe.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
