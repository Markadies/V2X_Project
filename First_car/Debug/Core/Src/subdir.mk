################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Buzzer.c \
../Core/Src/Car_Control.c \
../Core/Src/GPS.c \
../Core/Src/Help_Functions.c \
../Core/Src/LCD_I2C.c \
../Core/Src/LightSensor.c \
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
./Core/Src/Buzzer.o \
./Core/Src/Car_Control.o \
./Core/Src/GPS.o \
./Core/Src/Help_Functions.o \
./Core/Src/LCD_I2C.o \
./Core/Src/LightSensor.o \
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
./Core/Src/Buzzer.d \
./Core/Src/Car_Control.d \
./Core/Src/GPS.d \
./Core/Src/Help_Functions.d \
./Core/Src/LCD_I2C.d \
./Core/Src/LightSensor.d \
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
Core/Src/Buzzer.o: ../Core/Src/Buzzer.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/Config" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/OS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/SEGGER" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/include" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/Buzzer.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/Car_Control.o: ../Core/Src/Car_Control.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/Config" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/OS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/SEGGER" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/include" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/Car_Control.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/GPS.o: ../Core/Src/GPS.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/Config" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/OS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/SEGGER" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/include" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/GPS.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/Help_Functions.o: ../Core/Src/Help_Functions.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/Config" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/OS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/SEGGER" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/include" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/Help_Functions.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/LCD_I2C.o: ../Core/Src/LCD_I2C.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/Config" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/OS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/SEGGER" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/include" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/LCD_I2C.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/LightSensor.o: ../Core/Src/LightSensor.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/Config" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/OS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/SEGGER" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/include" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/LightSensor.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/NMEA.o: ../Core/Src/NMEA.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/Config" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/OS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/SEGGER" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/include" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/NMEA.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/Tasks.o: ../Core/Src/Tasks.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/Config" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/OS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/SEGGER" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/include" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/Tasks.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/UartRingbuffer.o: ../Core/Src/UartRingbuffer.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/Config" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/OS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/SEGGER" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/include" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/UartRingbuffer.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/bluetooth.o: ../Core/Src/bluetooth.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/Config" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/OS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/SEGGER" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/include" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/bluetooth.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/calculateSpeed.o: ../Core/Src/calculateSpeed.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/Config" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/OS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/SEGGER" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/include" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/calculateSpeed.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/main.o: ../Core/Src/main.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/Config" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/OS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/SEGGER" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/include" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32f4xx_hal_msp.o: ../Core/Src/stm32f4xx_hal_msp.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/Config" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/OS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/SEGGER" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/include" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32f4xx_hal_msp.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32f4xx_hal_timebase_tim.o: ../Core/Src/stm32f4xx_hal_timebase_tim.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/Config" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/OS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/SEGGER" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/include" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32f4xx_hal_timebase_tim.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32f4xx_it.o: ../Core/Src/stm32f4xx_it.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/Config" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/OS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/SEGGER" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/include" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32f4xx_it.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/syscalls.o: ../Core/Src/syscalls.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/Config" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/OS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/SEGGER" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/include" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/system_stm32f4xx.o: ../Core/Src/system_stm32f4xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/Config" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/OS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/SEGGER/SEGGER" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/include" -I"D:/Graduation Project/Project Repo/V2V_Project/First_car/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/system_stm32f4xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

