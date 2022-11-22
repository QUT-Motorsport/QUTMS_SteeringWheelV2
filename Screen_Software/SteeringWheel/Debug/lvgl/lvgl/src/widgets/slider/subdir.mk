################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/lvgl/src/widgets/slider/lv_slider.c 

OBJS += \
./lvgl/lvgl/src/widgets/slider/lv_slider.o 

C_DEPS += \
./lvgl/lvgl/src/widgets/slider/lv_slider.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/lvgl/src/widgets/slider/%.o lvgl/lvgl/src/widgets/slider/%.su: ../lvgl/lvgl/src/widgets/slider/%.c lvgl/lvgl/src/widgets/slider/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F207xx -c -I../Core/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F2xx/Include -I../Drivers/CMSIS/Include -I../lvgl -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-lvgl-2f-lvgl-2f-src-2f-widgets-2f-slider

clean-lvgl-2f-lvgl-2f-src-2f-widgets-2f-slider:
	-$(RM) ./lvgl/lvgl/src/widgets/slider/lv_slider.d ./lvgl/lvgl/src/widgets/slider/lv_slider.o ./lvgl/lvgl/src/widgets/slider/lv_slider.su

.PHONY: clean-lvgl-2f-lvgl-2f-src-2f-widgets-2f-slider

