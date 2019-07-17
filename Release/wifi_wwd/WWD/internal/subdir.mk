################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../wifi_wwd/WWD/internal/tlv.c \
../wifi_wwd/WWD/internal/wwd_ap_common.c \
../wifi_wwd/WWD/internal/wwd_clm.c \
../wifi_wwd/WWD/internal/wwd_debug.c \
../wifi_wwd/WWD/internal/wwd_eapol.c \
../wifi_wwd/WWD/internal/wwd_internal.c \
../wifi_wwd/WWD/internal/wwd_management.c \
../wifi_wwd/WWD/internal/wwd_rtos_interface.c \
../wifi_wwd/WWD/internal/wwd_sdpcm.c \
../wifi_wwd/WWD/internal/wwd_thread.c \
../wifi_wwd/WWD/internal/wwd_thread_internal.c \
../wifi_wwd/WWD/internal/wwd_wifi.c \
../wifi_wwd/WWD/internal/wwd_wifi_chip_common.c \
../wifi_wwd/WWD/internal/wwd_wifi_sleep.c 

OBJS += \
./wifi_wwd/WWD/internal/tlv.o \
./wifi_wwd/WWD/internal/wwd_ap_common.o \
./wifi_wwd/WWD/internal/wwd_clm.o \
./wifi_wwd/WWD/internal/wwd_debug.o \
./wifi_wwd/WWD/internal/wwd_eapol.o \
./wifi_wwd/WWD/internal/wwd_internal.o \
./wifi_wwd/WWD/internal/wwd_management.o \
./wifi_wwd/WWD/internal/wwd_rtos_interface.o \
./wifi_wwd/WWD/internal/wwd_sdpcm.o \
./wifi_wwd/WWD/internal/wwd_thread.o \
./wifi_wwd/WWD/internal/wwd_thread_internal.o \
./wifi_wwd/WWD/internal/wwd_wifi.o \
./wifi_wwd/WWD/internal/wwd_wifi_chip_common.o \
./wifi_wwd/WWD/internal/wwd_wifi_sleep.o 

C_DEPS += \
./wifi_wwd/WWD/internal/tlv.d \
./wifi_wwd/WWD/internal/wwd_ap_common.d \
./wifi_wwd/WWD/internal/wwd_clm.d \
./wifi_wwd/WWD/internal/wwd_debug.d \
./wifi_wwd/WWD/internal/wwd_eapol.d \
./wifi_wwd/WWD/internal/wwd_internal.d \
./wifi_wwd/WWD/internal/wwd_management.d \
./wifi_wwd/WWD/internal/wwd_rtos_interface.d \
./wifi_wwd/WWD/internal/wwd_sdpcm.d \
./wifi_wwd/WWD/internal/wwd_thread.d \
./wifi_wwd/WWD/internal/wwd_thread_internal.d \
./wifi_wwd/WWD/internal/wwd_wifi.d \
./wifi_wwd/WWD/internal/wwd_wifi_chip_common.d \
./wifi_wwd/WWD/internal/wwd_wifi_sleep.d 


# Each subdirectory must supply rules for building sources it contributes
wifi_wwd/WWD/internal/%.o: ../wifi_wwd/WWD/internal/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DPRINTF_FLOAT_ENABLE=0 -DSCANF_FLOAT_ENABLE=0 -DPRINTF_ADVANCED_ENABLE=0 -DSCANF_ADVANCED_ENABLE=0 -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DXIP_BOOT_HEADER_DCD_ENABLE=1 -D__SEMIHOST_HARDFAULT_DISABLE=1 -DSERIAL_PORT_TYPE_USBCDC=1 -DSERIAL_MANAGER_NON_BLOCKING_MODE=1 -DUSB_STACK_FREERTOS_HEAP_SIZE=65536 -DUSB_STACK_FREERTOS -DARM_MATH_CM7 -DCR_INTEGER_PRINTF -DUSE_RTOS=1 -DFSL_RTOS_FREE_RTOS -DDEBUG_CONSOLE_RX_ENABLE=0 -DCPU_MIMXRT1062DVL6A -DCPU_MIMXRT1062DVL6A_cm7 -DSDK_DEBUGCONSOLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -D__FPU_PRESENT=1 -I../board -I../source -I../ -I../drivers -I../device -I../CMSIS -I../codec -I../amazon-freertos/include -I../amazon-freertos/FreeRTOS/portable -I../usb/device/source/ehci -I../usb/include -I../osa -I../usb/device/include -I../usb/device/source -I../usb/phy -I../utilities -I../component/serial_manager -I../component/serial_manager/usb_cdc_adapter -I../other -I../audio/voice -I../audio/amazon -I../component/uart -I../component/lists -I../xip -I../audio/amplifier -I../audio/audio_samples -I../audio/pdm_mic -I../audio/audio_processing -O0 -fno-common -g -Wall -g  -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


