################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/STM32_USB_Device_Library/Class/HID/Src/usbd_hid.c 

OBJS += \
./Middlewares/ST/STM32_USB_Device_Library/Class/HID/Src/usbd_hid.o 

C_DEPS += \
./Middlewares/ST/STM32_USB_Device_Library/Class/HID/Src/usbd_hid.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STM32_USB_Device_Library/Class/HID/Src/%.o: ../Middlewares/ST/STM32_USB_Device_Library/Class/HID/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F042x6 -I"/home/donovan/STM/League_Final/Inc" -I"/home/donovan/STM/League_Final/Drivers/STM32F0xx_HAL_Driver/Inc" -I"/home/donovan/STM/League_Final/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"/home/donovan/STM/League_Final/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/home/donovan/STM/League_Final/Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc" -I"/home/donovan/STM/League_Final/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"/home/donovan/STM/League_Final/Drivers/CMSIS/Include"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


