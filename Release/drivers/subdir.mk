################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/flexspi_hyper_flash.c \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_dcp.c \
../drivers/fsl_dmamux.c \
../drivers/fsl_edma.c \
../drivers/fsl_enet.c \
../drivers/fsl_flexram.c \
../drivers/fsl_flexspi.c \
../drivers/fsl_gpio.c \
../drivers/fsl_gpt.c \
../drivers/fsl_lpi2c.c \
../drivers/fsl_lpuart.c \
../drivers/fsl_pit.c \
../drivers/fsl_pwm.c \
../drivers/fsl_sai.c \
../drivers/fsl_sai_edma.c \
../drivers/fsl_trng.c \
../drivers/fsl_usdhc_uvoice.c \
../drivers/fsl_xbara.c \
../drivers/sln_RT10xx_RGB_LED_driver.c 

OBJS += \
./drivers/flexspi_hyper_flash.o \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_dcp.o \
./drivers/fsl_dmamux.o \
./drivers/fsl_edma.o \
./drivers/fsl_enet.o \
./drivers/fsl_flexram.o \
./drivers/fsl_flexspi.o \
./drivers/fsl_gpio.o \
./drivers/fsl_gpt.o \
./drivers/fsl_lpi2c.o \
./drivers/fsl_lpuart.o \
./drivers/fsl_pit.o \
./drivers/fsl_pwm.o \
./drivers/fsl_sai.o \
./drivers/fsl_sai_edma.o \
./drivers/fsl_trng.o \
./drivers/fsl_usdhc_uvoice.o \
./drivers/fsl_xbara.o \
./drivers/sln_RT10xx_RGB_LED_driver.o 

C_DEPS += \
./drivers/flexspi_hyper_flash.d \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_dcp.d \
./drivers/fsl_dmamux.d \
./drivers/fsl_edma.d \
./drivers/fsl_enet.d \
./drivers/fsl_flexram.d \
./drivers/fsl_flexspi.d \
./drivers/fsl_gpio.d \
./drivers/fsl_gpt.d \
./drivers/fsl_lpi2c.d \
./drivers/fsl_lpuart.d \
./drivers/fsl_pit.d \
./drivers/fsl_pwm.d \
./drivers/fsl_sai.d \
./drivers/fsl_sai_edma.d \
./drivers/fsl_trng.d \
./drivers/fsl_usdhc_uvoice.d \
./drivers/fsl_xbara.d \
./drivers/sln_RT10xx_RGB_LED_driver.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DPRINTF_FLOAT_ENABLE=0 -DSCANF_FLOAT_ENABLE=0 -DPRINTF_ADVANCED_ENABLE=0 -DSCANF_ADVANCED_ENABLE=0 -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DXIP_BOOT_HEADER_DCD_ENABLE=1 -D__SEMIHOST_HARDFAULT_DISABLE=1 -DSERIAL_PORT_TYPE_USBCDC=1 -DSERIAL_MANAGER_NON_BLOCKING_MODE=1 -DUSB_STACK_FREERTOS_HEAP_SIZE=65536 -DUSB_STACK_FREERTOS -DARM_MATH_CM7 -DCR_INTEGER_PRINTF -DUSE_RTOS=1 -DFSL_RTOS_FREE_RTOS -DDEBUG_CONSOLE_RX_ENABLE=0 -DCPU_MIMXRT1062DVL6A -DCPU_MIMXRT1062DVL6A_cm7 -DSDK_DEBUGCONSOLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -D__FPU_PRESENT=1 -I../board -I../source -I../ -I../drivers -I../device -I../CMSIS -I../codec -I../amazon-freertos/include -I../amazon-freertos/FreeRTOS/portable -I../usb/device/source/ehci -I../usb/include -I../osa -I../usb/device/include -I../usb/device/source -I../usb/phy -I../utilities -I../component/serial_manager -I../component/serial_manager/usb_cdc_adapter -I../other -I../audio/voice -I../audio/amazon -I../component/uart -I../component/lists -I../xip -I../audio/amplifier -I../audio/audio_samples -I../audio/pdm_mic -I../audio/audio_processing -O0 -fno-common -g -Wall -g  -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


