################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/lvgl/src/draw/nxp/pxp/lv_draw_pxp_blend.c \
../lvgl/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp.c \
../lvgl/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.c 

OBJS += \
./lvgl/lvgl/src/draw/nxp/pxp/lv_draw_pxp_blend.o \
./lvgl/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp.o \
./lvgl/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.o 

C_DEPS += \
./lvgl/lvgl/src/draw/nxp/pxp/lv_draw_pxp_blend.d \
./lvgl/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp.d \
./lvgl/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/lvgl/src/draw/nxp/pxp/%.o lvgl/lvgl/src/draw/nxp/pxp/%.su: ../lvgl/lvgl/src/draw/nxp/pxp/%.c lvgl/lvgl/src/draw/nxp/pxp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F207xx -c -I../Core/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F2xx/Include -I../Drivers/CMSIS/Include -I../lvgl -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-lvgl-2f-lvgl-2f-src-2f-draw-2f-nxp-2f-pxp

clean-lvgl-2f-lvgl-2f-src-2f-draw-2f-nxp-2f-pxp:
	-$(RM) ./lvgl/lvgl/src/draw/nxp/pxp/lv_draw_pxp_blend.d ./lvgl/lvgl/src/draw/nxp/pxp/lv_draw_pxp_blend.o ./lvgl/lvgl/src/draw/nxp/pxp/lv_draw_pxp_blend.su ./lvgl/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp.d ./lvgl/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp.o ./lvgl/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp.su ./lvgl/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.d ./lvgl/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.o ./lvgl/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.su

.PHONY: clean-lvgl-2f-lvgl-2f-src-2f-draw-2f-nxp-2f-pxp

