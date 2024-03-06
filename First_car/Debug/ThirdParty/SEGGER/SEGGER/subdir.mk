################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ThirdParty/SEGGER/SEGGER/SEGGER_RTT.c \
../ThirdParty/SEGGER/SEGGER/SEGGER_RTT_printf.c \
../ThirdParty/SEGGER/SEGGER/SEGGER_SYSVIEW.c 

S_UPPER_SRCS += \
../ThirdParty/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.S 

OBJS += \
./ThirdParty/SEGGER/SEGGER/SEGGER_RTT.o \
./ThirdParty/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.o \
./ThirdParty/SEGGER/SEGGER/SEGGER_RTT_printf.o \
./ThirdParty/SEGGER/SEGGER/SEGGER_SYSVIEW.o 

S_UPPER_DEPS += \
./ThirdParty/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.d 

C_DEPS += \
./ThirdParty/SEGGER/SEGGER/SEGGER_RTT.d \
./ThirdParty/SEGGER/SEGGER/SEGGER_RTT_printf.d \
./ThirdParty/SEGGER/SEGGER/SEGGER_SYSVIEW.d 


# Each subdirectory must supply rules for building sources it contributes
ThirdParty/SEGGER/SEGGER/%.o ThirdParty/SEGGER/SEGGER/%.su ThirdParty/SEGGER/SEGGER/%.cyclo: ../ThirdParty/SEGGER/SEGGER/%.c ThirdParty/SEGGER/SEGGER/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"D:/GP/WS/V2X_Project/First_car/ThirdParty/SEGGER/Config" -I"D:/GP/WS/V2X_Project/First_car/ThirdParty/SEGGER/OS" -I"D:/GP/WS/V2X_Project/First_car/ThirdParty/SEGGER/SEGGER" -I"D:/GP/WS/V2X_Project/First_car/ThirdParty/FreeRTOS" -I"D:/GP/WS/V2X_Project/First_car/ThirdParty/FreeRTOS/include" -I"D:/GP/WS/V2X_Project/First_car/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThirdParty/SEGGER/SEGGER/%.o: ../ThirdParty/SEGGER/SEGGER/%.S ThirdParty/SEGGER/SEGGER/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"D:/GP/WS/V2X_Project/First_car/ThirdParty/SEGGER/Config" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-ThirdParty-2f-SEGGER-2f-SEGGER

clean-ThirdParty-2f-SEGGER-2f-SEGGER:
	-$(RM) ./ThirdParty/SEGGER/SEGGER/SEGGER_RTT.cyclo ./ThirdParty/SEGGER/SEGGER/SEGGER_RTT.d ./ThirdParty/SEGGER/SEGGER/SEGGER_RTT.o ./ThirdParty/SEGGER/SEGGER/SEGGER_RTT.su ./ThirdParty/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.d ./ThirdParty/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.o ./ThirdParty/SEGGER/SEGGER/SEGGER_RTT_printf.cyclo ./ThirdParty/SEGGER/SEGGER/SEGGER_RTT_printf.d ./ThirdParty/SEGGER/SEGGER/SEGGER_RTT_printf.o ./ThirdParty/SEGGER/SEGGER/SEGGER_RTT_printf.su ./ThirdParty/SEGGER/SEGGER/SEGGER_SYSVIEW.cyclo ./ThirdParty/SEGGER/SEGGER/SEGGER_SYSVIEW.d ./ThirdParty/SEGGER/SEGGER/SEGGER_SYSVIEW.o ./ThirdParty/SEGGER/SEGGER/SEGGER_SYSVIEW.su

.PHONY: clean-ThirdParty-2f-SEGGER-2f-SEGGER

