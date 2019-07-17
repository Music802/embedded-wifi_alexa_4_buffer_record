################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../device/system_MIMXRT1062.c 

OBJS += \
./device/system_MIMXRT1062.o 

C_DEPS += \
./device/system_MIMXRT1062.d 


# Each subdirectory must supply rules for building sources it contributes
device/%.o: ../device/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DSCANF_FLOAT_ENABLE=0 -DPRINTF_ADVANCED_ENABLE=0 -DSCANF_ADVANCED_ENABLE=0 -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DXIP_BOOT_HEADER_DCD_ENABLE=1 -D__SEMIHOST_HARDFAULT_DISABLE=1 -DUSE_RTOS=1 -DFSL_RTOS_FREE_RTOS -DLWIP_DNS=1 -DLWIP_DHCP=1 -DCPU_MIMXRT106ADVL6A -DCPU_MIMXRT106ADVL6A_cm7 -DPRINTF_FLOAT_ENABLE=0 -DCR_INTEGER_PRINTF -DSDK_DEBUGCONSOLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -DSERIAL_PORT_TYPE_USBCDC=1 -DSERIAL_MANAGER_NON_BLOCKING_MODE=1 -DUSB_STACK_FREERTOS_HEAP_SIZE=65536 -DUSB_STACK_FREERTOS -DDEBUG_CONSOLE_RX_ENABLE=0 -DCPU_MIMXRT1062DVL6A -DCPU_MIMXRT1062DVL6A_cm7 -D__FPU_PRESENT=1 -DARM_MATH_CM7 -I../board -I../source -I../drivers -I../utilities -I../component/serial_manager -I../device -I../CMSIS -I../amazon-freertos/include -I../amazon-freertos/FreeRTOS/portable -I../lwip/port/arch -I../lwip/src/include/compat/posix -I../lwip/src/include/compat/posix/arpa -I../lwip/src/include/compat/posix/net -I../lwip/src/include/compat/posix/sys -I../lwip/src/include/compat/stdc -I../lwip/src/include/lwip -I../lwip/src/include/lwip/priv -I../lwip/src/include/lwip/prot -I../lwip/src/include/netif -I../lwip/src/include/netif/ppp -I../lwip/src/include/netif/ppp/polarssl -I../lwip/port -I../wifi_wwd/FreeRTOS -I../wifi_wwd/network -I../wifi_wwd/platform -I../wifi_wwd/WWD/include/network -I../wifi_wwd/WWD/include/platform -I../wifi_wwd/WWD/include/RTOS -I../wifi_wwd/WWD/include -I../wifi_wwd/WWD/internal/bus_protocols/SDIO -I../wifi_wwd/WWD/internal/bus_protocols -I../wifi_wwd/WWD/internal/chips -I../wifi_wwd/WWD/internal -I../wifi_wwd/WWD -I../wifi_wwd -I../sdmmc/inc -I../sdmmc/port -I../component/uart -I../component/lists -I../xip -I../lwip/src -I../lwip/src/include -I../ -I../codec -I../usb/device/source/ehci -I../usb/include -I../osa -I../usb/device/include -I../usb/device/source -I../usb/phy -I../component/serial_manager/usb_cdc_adapter -I../other -I../audio/voice -I../audio/amazon -I../audio/amplifier -I../audio/audio_samples -I../audio/pdm_mic -I../audio/audio_processing -O0 -fno-common -g -Wall -g  -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


