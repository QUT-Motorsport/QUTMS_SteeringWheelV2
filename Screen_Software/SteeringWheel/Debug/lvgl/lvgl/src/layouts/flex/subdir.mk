################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/lvgl/src/layouts/flex/lv_flex.c 

OBJS += \
./lvgl/lvgl/src/layouts/flex/lv_flex.o 

C_DEPS += \
./lvgl/lvgl/src/layouts/flex/lv_flex.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/lvgl/src/layouts/flex/%.o lvgl/lvgl/src/layouts/flex/%.su: ../lvgl/lvgl/src/layouts/flex/%.c lvgl/lvgl/src/layouts/flex/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F207xx -c -I../Core/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F2xx/Include -I../Drivers/CMSIS/Include -I../lvgl -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-lvgl-2f-lvgl-2f-src-2f-layouts-2f-flex

clean-lvgl-2f-lvgl-2f-src-2f-layouts-2f-flex:
	-$(RM) ./lvgl/lvgl/src/layouts/flex/lv_flex.d ./lvgl/lvgl/src/layouts/flex/lv_flex.o ./lvgl/lvgl/src/layouts/flex/lv_flex.su

.PHONY: clean-lvgl-2f-lvgl-2f-src-2f-layouts-2f-flex

