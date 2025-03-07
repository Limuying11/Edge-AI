################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/Touchgfx/HAM/CM4/X-CUBE-AI/App/app_x-cube-ai.c \
F:/Touchgfx/HAM/CM4/X-CUBE-AI/App/network.c \
F:/Touchgfx/HAM/CM4/X-CUBE-AI/App/network_data.c \
F:/Touchgfx/HAM/CM4/X-CUBE-AI/App/network_data_params.c 

C_DEPS += \
./Application/User/X-CUBE-AI/App/app_x-cube-ai.d \
./Application/User/X-CUBE-AI/App/network.d \
./Application/User/X-CUBE-AI/App/network_data.d \
./Application/User/X-CUBE-AI/App/network_data_params.d 

OBJS += \
./Application/User/X-CUBE-AI/App/app_x-cube-ai.o \
./Application/User/X-CUBE-AI/App/network.o \
./Application/User/X-CUBE-AI/App/network_data.o \
./Application/User/X-CUBE-AI/App/network_data_params.o 


# Each subdirectory must supply rules for building sources it contributes
Application/User/X-CUBE-AI/App/app_x-cube-ai.o: F:/Touchgfx/HAM/CM4/X-CUBE-AI/App/app_x-cube-ai.c Application/User/X-CUBE-AI/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32H747xx -DUSE_PWR_DIRECT_SMPS_SUPPLY -c -I../../../CM4/Core/Inc -I../../../Drivers/BSP/Components -I../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../Drivers/CMSIS/Include -I../../../CM4/X-CUBE-AI/App -I../../../CM4/X-CUBE-AI -I../../../Middlewares/ST/AI/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/X-CUBE-AI/App/network.o: F:/Touchgfx/HAM/CM4/X-CUBE-AI/App/network.c Application/User/X-CUBE-AI/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32H747xx -DUSE_PWR_DIRECT_SMPS_SUPPLY -c -I../../../CM4/Core/Inc -I../../../Drivers/BSP/Components -I../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../Drivers/CMSIS/Include -I../../../CM4/X-CUBE-AI/App -I../../../CM4/X-CUBE-AI -I../../../Middlewares/ST/AI/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/X-CUBE-AI/App/network_data.o: F:/Touchgfx/HAM/CM4/X-CUBE-AI/App/network_data.c Application/User/X-CUBE-AI/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32H747xx -DUSE_PWR_DIRECT_SMPS_SUPPLY -c -I../../../CM4/Core/Inc -I../../../Drivers/BSP/Components -I../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../Drivers/CMSIS/Include -I../../../CM4/X-CUBE-AI/App -I../../../CM4/X-CUBE-AI -I../../../Middlewares/ST/AI/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/X-CUBE-AI/App/network_data_params.o: F:/Touchgfx/HAM/CM4/X-CUBE-AI/App/network_data_params.c Application/User/X-CUBE-AI/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32H747xx -DUSE_PWR_DIRECT_SMPS_SUPPLY -c -I../../../CM4/Core/Inc -I../../../Drivers/BSP/Components -I../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../Drivers/CMSIS/Include -I../../../CM4/X-CUBE-AI/App -I../../../CM4/X-CUBE-AI -I../../../Middlewares/ST/AI/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-User-2f-X-2d-CUBE-2d-AI-2f-App

clean-Application-2f-User-2f-X-2d-CUBE-2d-AI-2f-App:
	-$(RM) ./Application/User/X-CUBE-AI/App/app_x-cube-ai.cyclo ./Application/User/X-CUBE-AI/App/app_x-cube-ai.d ./Application/User/X-CUBE-AI/App/app_x-cube-ai.o ./Application/User/X-CUBE-AI/App/app_x-cube-ai.su ./Application/User/X-CUBE-AI/App/network.cyclo ./Application/User/X-CUBE-AI/App/network.d ./Application/User/X-CUBE-AI/App/network.o ./Application/User/X-CUBE-AI/App/network.su ./Application/User/X-CUBE-AI/App/network_data.cyclo ./Application/User/X-CUBE-AI/App/network_data.d ./Application/User/X-CUBE-AI/App/network_data.o ./Application/User/X-CUBE-AI/App/network_data.su ./Application/User/X-CUBE-AI/App/network_data_params.cyclo ./Application/User/X-CUBE-AI/App/network_data_params.d ./Application/User/X-CUBE-AI/App/network_data_params.o ./Application/User/X-CUBE-AI/App/network_data_params.su

.PHONY: clean-Application-2f-User-2f-X-2d-CUBE-2d-AI-2f-App

