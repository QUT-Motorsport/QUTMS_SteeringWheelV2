################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/lvgl/src/widgets/bar/lv_bar.c 

OBJS += \
./lvgl/lvgl/src/widgets/bar/lv_bar.o 

C_DEPS += \
./lvgl/lvgl/src/widgets/bar/lv_bar.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/lvgl/src/widgets/bar/%.o lvgl/lvgl/src/widgets/bar/%.su: ../lvgl/lvgl/src/widgets/bar/%.c lvgl/lvgl/src/widgets/bar/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F207xx -c -I../Core/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F2xx/Include -I../Drivers/CMSIS/Include -I../lvgl -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-lvgl-2f-lvgl-2f-src-2f-widgets-2f-bar

clean-lvgl-2f-lvgl-2f-src-2f-widgets-2f-bar:
	-$(RM) ./lvgl/lvgl/src/widgets/bar/lv_bar.d ./lvgl/lvgl/src/widgets/bar/lv_bar.o ./lvgl/lvgl/src/widgets/bar/lv_bar.su

.PHONY: clean-lvgl-2f-lvgl-2f-src-2f-widgets-2f-bar

