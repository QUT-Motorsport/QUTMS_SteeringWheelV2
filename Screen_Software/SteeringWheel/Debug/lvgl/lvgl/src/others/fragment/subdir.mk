################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/lvgl/src/others/fragment/lv_fragment.c \
../lvgl/lvgl/src/others/fragment/lv_fragment_manager.c 

OBJS += \
./lvgl/lvgl/src/others/fragment/lv_fragment.o \
./lvgl/lvgl/src/others/fragment/lv_fragment_manager.o 

C_DEPS += \
./lvgl/lvgl/src/others/fragment/lv_fragment.d \
./lvgl/lvgl/src/others/fragment/lv_fragment_manager.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/lvgl/src/others/fragment/%.o lvgl/lvgl/src/others/fragment/%.su: ../lvgl/lvgl/src/others/fragment/%.c lvgl/lvgl/src/others/fragment/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F207xx -c -I../Core/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F2xx/Include -I../Drivers/CMSIS/Include -I../lvgl -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-lvgl-2f-lvgl-2f-src-2f-others-2f-fragment

clean-lvgl-2f-lvgl-2f-src-2f-others-2f-fragment:
	-$(RM) ./lvgl/lvgl/src/others/fragment/lv_fragment.d ./lvgl/lvgl/src/others/fragment/lv_fragment.o ./lvgl/lvgl/src/others/fragment/lv_fragment.su ./lvgl/lvgl/src/others/fragment/lv_fragment_manager.d ./lvgl/lvgl/src/others/fragment/lv_fragment_manager.o ./lvgl/lvgl/src/others/fragment/lv_fragment_manager.su

.PHONY: clean-lvgl-2f-lvgl-2f-src-2f-others-2f-fragment

