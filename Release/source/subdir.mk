################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/RealityAI_sound_classifier.c \
../source/audio_processing_task.c \
../source/dhcp_server.c \
../source/join_wifi.c \
../source/main.c \
../source/os_hooks.c \
../source/semihost_hardfault.c \
../source/sln_shell.c \
../source/tcp_send.c \
../source/tcpecho.c \
../source/test_apsta.c \
../source/test_join.c \
../source/test_scan.c \
../source/udpecho.c \
../source/wlanif_add.c 

OBJS += \
./source/RealityAI_sound_classifier.o \
./source/audio_processing_task.o \
./source/dhcp_server.o \
./source/join_wifi.o \
./source/main.o \
./source/os_hooks.o \
./source/semihost_hardfault.o \
./source/sln_shell.o \
./source/tcp_send.o \
./source/tcpecho.o \
./source/test_apsta.o \
./source/test_join.o \
./source/test_scan.o \
./source/udpecho.o \
./source/wlanif_add.o 

C_DEPS += \
./source/RealityAI_sound_classifier.d \
./source/audio_processing_task.d \
./source/dhcp_server.d \
./source/join_wifi.d \
./source/main.d \
./source/os_hooks.d \
./source/semihost_hardfault.d \
./source/sln_shell.d \
./source/tcp_send.d \
./source/tcpecho.d \
./source/test_apsta.d \
./source/test_join.d \
./source/test_scan.d \
./source/udpecho.d \
./source/wlanif_add.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DPRINTF_FLOAT_ENABLE=0 -DSCANF_FLOAT_ENABLE=0 -DPRINTF_ADVANCED_ENABLE=0 -DSCANF_ADVANCED_ENABLE=0 -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DXIP_BOOT_HEADER_DCD_ENABLE=1 -D__SEMIHOST_HARDFAULT_DISABLE=1 -DSERIAL_PORT_TYPE_USBCDC=1 -DSERIAL_MANAGER_NON_BLOCKING_MODE=1 -DUSB_STACK_FREERTOS_HEAP_SIZE=65536 -DUSB_STACK_FREERTOS -DARM_MATH_CM7 -DCR_INTEGER_PRINTF -DUSE_RTOS=1 -DFSL_RTOS_FREE_RTOS -DDEBUG_CONSOLE_RX_ENABLE=0 -DCPU_MIMXRT1062DVL6A -DCPU_MIMXRT1062DVL6A_cm7 -DSDK_DEBUGCONSOLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -D__FPU_PRESENT=1 -I../board -I../source -I../ -I../drivers -I../device -I../CMSIS -I../codec -I../amazon-freertos/include -I../amazon-freertos/FreeRTOS/portable -I../usb/device/source/ehci -I../usb/include -I../osa -I../usb/device/include -I../usb/device/source -I../usb/phy -I../utilities -I../component/serial_manager -I../component/serial_manager/usb_cdc_adapter -I../other -I../audio/voice -I../audio/amazon -I../component/uart -I../component/lists -I../xip -I../audio/amplifier -I../audio/audio_samples -I../audio/pdm_mic -I../audio/audio_processing -O0 -fno-common -g -Wall -g  -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


