################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/lvgl/src/libs/png/lodepng.c \
../lvgl/lvgl/src/libs/png/lv_png.c 

OBJS += \
./lvgl/lvgl/src/libs/png/lodepng.o \
./lvgl/lvgl/src/libs/png/lv_png.o 

C_DEPS += \
./lvgl/lvgl/src/libs/png/lodepng.d \
./lvgl/lvgl/src/libs/png/lv_png.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/lvgl/src/libs/png/%.o lvgl/lvgl/src/libs/png/%.su: ../lvgl/lvgl/src/libs/png/%.c lvgl/lvgl/src/libs/png/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F207xx -c -I../Core/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F2xx/Include -I../Drivers/CMSIS/Include -I../lvgl -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-lvgl-2f-lvgl-2f-src-2f-libs-2f-png

clean-lvgl-2f-lvgl-2f-src-2f-libs-2f-png:
	-$(RM) ./lvgl/lvgl/src/libs/png/lodepng.d ./lvgl/lvgl/src/libs/png/lodepng.o ./lvgl/lvgl/src/libs/png/lodepng.su ./lvgl/lvgl/src/libs/png/lv_png.d ./lvgl/lvgl/src/libs/png/lv_png.o ./lvgl/lvgl/src/libs/png/lv_png.su

.PHONY: clean-lvgl-2f-lvgl-2f-src-2f-libs-2f-png

