################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/lvgl/src/widgets/roller/lv_roller.c 

OBJS += \
./lvgl/lvgl/src/widgets/roller/lv_roller.o 

C_DEPS += \
./lvgl/lvgl/src/widgets/roller/lv_roller.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/lvgl/src/widgets/roller/%.o lvgl/lvgl/src/widgets/roller/%.su: ../lvgl/lvgl/src/widgets/roller/%.c lvgl/lvgl/src/widgets/roller/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F207xx -c -I../Core/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F2xx/Include -I../Drivers/CMSIS/Include -I../lvgl -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-lvgl-2f-lvgl-2f-src-2f-widgets-2f-roller

clean-lvgl-2f-lvgl-2f-src-2f-widgets-2f-roller:
	-$(RM) ./lvgl/lvgl/src/widgets/roller/lv_roller.d ./lvgl/lvgl/src/widgets/roller/lv_roller.o ./lvgl/lvgl/src/widgets/roller/lv_roller.su

.PHONY: clean-lvgl-2f-lvgl-2f-src-2f-widgets-2f-roller

