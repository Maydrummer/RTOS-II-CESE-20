################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/app/src/app.c 

OBJS += \
./src/app/src/app.o 

C_DEPS += \
./src/app/src/app.d 


# Each subdirectory must supply rules for building sources it contributes
src/app/src/%.o src/app/src/%.su src/app/src/%.cyclo: ../src/app/src/%.c src/app/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/thony/Documents/Maestria/RTOS II/Practica/tp1_rtos_ii_maisincho/src/app/inc" -I"C:/Users/thony/Documents/Maestria/RTOS II/Practica/tp1_rtos_ii_maisincho/src/hal/inc" -I"C:/Users/thony/Documents/Maestria/RTOS II/Practica/tp1_rtos_ii_maisincho/src/lib/inc" -I"C:/Users/thony/Documents/Maestria/RTOS II/Practica/tp1_rtos_ii_maisincho/src/task/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-src-2f-app-2f-src

clean-src-2f-app-2f-src:
	-$(RM) ./src/app/src/app.cyclo ./src/app/src/app.d ./src/app/src/app.o ./src/app/src/app.su

.PHONY: clean-src-2f-app-2f-src

