################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/gpio_poller.c \
../Src/joystick.c \
../Src/main.c \
../Src/stm32f0xx_hal_msp.c \
../Src/stm32f0xx_it.c \
../Src/syscalls.c \
../Src/system_stm32f0xx.c \
../Src/usb_device.c \
../Src/usbd_conf.c \
../Src/usbd_desc.c 

OBJS += \
./Src/gpio_poller.o \
./Src/joystick.o \
./Src/main.o \
./Src/stm32f0xx_hal_msp.o \
./Src/stm32f0xx_it.o \
./Src/syscalls.o \
./Src/system_stm32f0xx.o \
./Src/usb_device.o \
./Src/usbd_conf.o \
./Src/usbd_desc.o 

C_DEPS += \
./Src/gpio_poller.d \
./Src/joystick.d \
./Src/main.d \
./Src/stm32f0xx_hal_msp.d \
./Src/stm32f0xx_it.d \
./Src/syscalls.d \
./Src/system_stm32f0xx.d \
./Src/usb_device.d \
./Src/usbd_conf.d \
./Src/usbd_desc.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F042x6 -I"/home/donovan/STM/League_Final/Inc" -I"/home/donovan/STM/League_Final/Drivers/STM32F0xx_HAL_Driver/Inc" -I"/home/donovan/STM/League_Final/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"/home/donovan/STM/League_Final/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/donovan/STM/League_Final/Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc" -I"/home/donovan/STM/League_Final/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"/home/donovan/STM/League_Final/Drivers/CMSIS/Include"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


