################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/lvgl/src/widgets/tileview/lv_tileview.c 

OBJS += \
./lvgl/lvgl/src/widgets/tileview/lv_tileview.o 

C_DEPS += \
./lvgl/lvgl/src/widgets/tileview/lv_tileview.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/lvgl/src/widgets/tileview/%.o lvgl/lvgl/src/widgets/tileview/%.su: ../lvgl/lvgl/src/widgets/tileview/%.c lvgl/lvgl/src/widgets/tileview/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F207xx -c -I../Core/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F2xx/Include -I../Drivers/CMSIS/Include -I../lvgl -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-lvgl-2f-lvgl-2f-src-2f-widgets-2f-tileview

clean-lvgl-2f-lvgl-2f-src-2f-widgets-2f-tileview:
	-$(RM) ./lvgl/lvgl/src/widgets/tileview/lv_tileview.d ./lvgl/lvgl/src/widgets/tileview/lv_tileview.o ./lvgl/lvgl/src/widgets/tileview/lv_tileview.su

.PHONY: clean-lvgl-2f-lvgl-2f-src-2f-widgets-2f-tileview

