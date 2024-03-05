################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Build_msg.c \
../Core/Src/Buzzer.c \
../Core/Src/Call_Back_functions.c \
../Core/Src/Car_Control.c \
../Core/Src/GPS.c \
../Core/Src/Help_Functions.c \
../Core/Src/LCD_I2C.c \
../Core/Src/NMEA.c \
../Core/Src/Tasks.c \
../Core/Src/UartRingbuffer.c \
../Core/Src/bluetooth.c \
../Core/Src/calculateSpeed.c \
../Core/Src/main.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_hal_timebase_tim.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/system_stm32f4xx.c 

OBJS += \
./Core/Src/Build_msg.o \
./Core/Src/Buzzer.o \
./Core/Src/Call_Back_functions.o \
./Core/Src/Car_Control.o \
./Core/Src/GPS.o \
./Core/Src/Help_Functions.o \
./Core/Src/LCD_I2C.o \
./Core/Src/NMEA.o \
./Core/Src/Tasks.o \
./Core/Src/UartRingbuffer.o \
./Core/Src/bluetooth.o \
./Core/Src/calculateSpeed.o \
./Core/Src/main.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_hal_timebase_tim.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/system_stm32f4xx.o 

C_DEPS += \
./Core/Src/Build_msg.d \
./Core/Src/Buzzer.d \
./Core/Src/Call_Back_functions.d \
./Core/Src/Car_Control.d \
./Core/Src/GPS.d \
./Core/Src/Help_Functions.d \
./Core/Src/LCD_I2C.d \
./Core/Src/NMEA.d \
./Core/Src/Tasks.d \
./Core/Src/UartRingbuffer.d \
./Core/Src/bluetooth.d \
./Core/Src/calculateSpeed.d \
./Core/Src/main.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_hal_timebase_tim.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"D:/Graduation Project/Project Repo/V2V_Project/Sec_car/ThirdParty/SEGGER/Config" -I"D:/Graduation Project/Project Repo/V2V_Project/Sec_car/ThirdParty/SEGGER/OS" -I"D:/Graduation Project/Project Repo/V2V_Project/Sec_car/ThirdParty/SEGGER/SEGGER" -I"D:/Graduation Project/Project Repo/V2V_Project/Sec_car/ThirdParty/FreeRTOS" -I"D:/Graduation Project/Project Repo/V2V_Project/Sec_car/ThirdParty/FreeRTOS/include" -I"D:/Graduation Project/Project Repo/V2V_Project/Sec_car/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/Build_msg.cyclo ./Core/Src/Build_msg.d ./Core/Src/Build_msg.o ./Core/Src/Build_msg.su ./Core/Src/Buzzer.cyclo ./Core/Src/Buzzer.d ./Core/Src/Buzzer.o ./Core/Src/Buzzer.su ./Core/Src/Call_Back_functions.cyclo ./Core/Src/Call_Back_functions.d ./Core/Src/Call_Back_functions.o ./Core/Src/Call_Back_functions.su ./Core/Src/Car_Control.cyclo ./Core/Src/Car_Control.d ./Core/Src/Car_Control.o ./Core/Src/Car_Control.su ./Core/Src/GPS.cyclo ./Core/Src/GPS.d ./Core/Src/GPS.o ./Core/Src/GPS.su ./Core/Src/Help_Functions.cyclo ./Core/Src/Help_Functions.d ./Core/Src/Help_Functions.o ./Core/Src/Help_Functions.su ./Core/Src/LCD_I2C.cyclo ./Core/Src/LCD_I2C.d ./Core/Src/LCD_I2C.o ./Core/Src/LCD_I2C.su ./Core/Src/NMEA.cyclo ./Core/Src/NMEA.d ./Core/Src/NMEA.o ./Core/Src/NMEA.su ./Core/Src/Tasks.cyclo ./Core/Src/Tasks.d ./Core/Src/Tasks.o ./Core/Src/Tasks.su ./Core/Src/UartRingbuffer.cyclo ./Core/Src/UartRingbuffer.d ./Core/Src/UartRingbuffer.o ./Core/Src/UartRingbuffer.su ./Core/Src/bluetooth.cyclo ./Core/Src/bluetooth.d ./Core/Src/bluetooth.o ./Core/Src/bluetooth.su ./Core/Src/calculateSpeed.cyclo ./Core/Src/calculateSpeed.d ./Core/Src/calculateSpeed.o ./Core/Src/calculateSpeed.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_hal_timebase_tim.cyclo ./Core/Src/stm32f4xx_hal_timebase_tim.d ./Core/Src/stm32f4xx_hal_timebase_tim.o ./Core/Src/stm32f4xx_hal_timebase_tim.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su

.PHONY: clean-Core-2f-Src

