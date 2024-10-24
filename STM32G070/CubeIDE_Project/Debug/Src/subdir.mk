################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/adc.c \
../Src/exti.c \
../Src/led.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_stm32g070xx.c \
../Src/tim.c \
../Src/uart.c 

OBJS += \
./Src/adc.o \
./Src/exti.o \
./Src/led.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_stm32g070xx.o \
./Src/tim.o \
./Src/uart.o 

C_DEPS += \
./Src/adc.d \
./Src/exti.d \
./Src/led.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32g070xx.d \
./Src/tim.d \
./Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32G070xx -c -I../Inc -I/Users/bhageerath/Documents/Firmware/STM32/STM32G070/CubeIDE_Project/Drivers/CMSIS/Include -I/Users/bhageerath/Documents/Firmware/STM32/STM32G070/CubeIDE_Project/Drivers/CMSIS/Device/ST/STM32G0xx/Include -I/Users/bhageerath/Documents/Firmware/STM32/STM32G070/CubeIDE_Project/Drivers/STM32G0xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/adc.cyclo ./Src/adc.d ./Src/adc.o ./Src/adc.su ./Src/exti.cyclo ./Src/exti.d ./Src/exti.o ./Src/exti.su ./Src/led.cyclo ./Src/led.d ./Src/led.o ./Src/led.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/system_stm32g070xx.cyclo ./Src/system_stm32g070xx.d ./Src/system_stm32g070xx.o ./Src/system_stm32g070xx.su ./Src/tim.cyclo ./Src/tim.d ./Src/tim.o ./Src/tim.su ./Src/uart.cyclo ./Src/uart.d ./Src/uart.o ./Src/uart.su

.PHONY: clean-Src

