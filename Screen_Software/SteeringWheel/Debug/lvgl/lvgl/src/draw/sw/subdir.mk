################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/lvgl/src/draw/sw/lv_draw_sw.c \
../lvgl/lvgl/src/draw/sw/lv_draw_sw_arc.c \
../lvgl/lvgl/src/draw/sw/lv_draw_sw_blend.c \
../lvgl/lvgl/src/draw/sw/lv_draw_sw_dither.c \
../lvgl/lvgl/src/draw/sw/lv_draw_sw_gradient.c \
../lvgl/lvgl/src/draw/sw/lv_draw_sw_img.c \
../lvgl/lvgl/src/draw/sw/lv_draw_sw_layer.c \
../lvgl/lvgl/src/draw/sw/lv_draw_sw_letter.c \
../lvgl/lvgl/src/draw/sw/lv_draw_sw_line.c \
../lvgl/lvgl/src/draw/sw/lv_draw_sw_polygon.c \
../lvgl/lvgl/src/draw/sw/lv_draw_sw_rect.c \
../lvgl/lvgl/src/draw/sw/lv_draw_sw_transform.c 

OBJS += \
./lvgl/lvgl/src/draw/sw/lv_draw_sw.o \
./lvgl/lvgl/src/draw/sw/lv_draw_sw_arc.o \
./lvgl/lvgl/src/draw/sw/lv_draw_sw_blend.o \
./lvgl/lvgl/src/draw/sw/lv_draw_sw_dither.o \
./lvgl/lvgl/src/draw/sw/lv_draw_sw_gradient.o \
./lvgl/lvgl/src/draw/sw/lv_draw_sw_img.o \
./lvgl/lvgl/src/draw/sw/lv_draw_sw_layer.o \
./lvgl/lvgl/src/draw/sw/lv_draw_sw_letter.o \
./lvgl/lvgl/src/draw/sw/lv_draw_sw_line.o \
./lvgl/lvgl/src/draw/sw/lv_draw_sw_polygon.o \
./lvgl/lvgl/src/draw/sw/lv_draw_sw_rect.o \
./lvgl/lvgl/src/draw/sw/lv_draw_sw_transform.o 

C_DEPS += \
./lvgl/lvgl/src/draw/sw/lv_draw_sw.d \
./lvgl/lvgl/src/draw/sw/lv_draw_sw_arc.d \
./lvgl/lvgl/src/draw/sw/lv_draw_sw_blend.d \
./lvgl/lvgl/src/draw/sw/lv_draw_sw_dither.d \
./lvgl/lvgl/src/draw/sw/lv_draw_sw_gradient.d \
./lvgl/lvgl/src/draw/sw/lv_draw_sw_img.d \
./lvgl/lvgl/src/draw/sw/lv_draw_sw_layer.d \
./lvgl/lvgl/src/draw/sw/lv_draw_sw_letter.d \
./lvgl/lvgl/src/draw/sw/lv_draw_sw_line.d \
./lvgl/lvgl/src/draw/sw/lv_draw_sw_polygon.d \
./lvgl/lvgl/src/draw/sw/lv_draw_sw_rect.d \
./lvgl/lvgl/src/draw/sw/lv_draw_sw_transform.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/lvgl/src/draw/sw/%.o lvgl/lvgl/src/draw/sw/%.su: ../lvgl/lvgl/src/draw/sw/%.c lvgl/lvgl/src/draw/sw/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F207xx -c -I../Core/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F2xx/Include -I../Drivers/CMSIS/Include -I../lvgl -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-lvgl-2f-lvgl-2f-src-2f-draw-2f-sw

clean-lvgl-2f-lvgl-2f-src-2f-draw-2f-sw:
	-$(RM) ./lvgl/lvgl/src/draw/sw/lv_draw_sw.d ./lvgl/lvgl/src/draw/sw/lv_draw_sw.o ./lvgl/lvgl/src/draw/sw/lv_draw_sw.su ./lvgl/lvgl/src/draw/sw/lv_draw_sw_arc.d ./lvgl/lvgl/src/draw/sw/lv_draw_sw_arc.o ./lvgl/lvgl/src/draw/sw/lv_draw_sw_arc.su ./lvgl/lvgl/src/draw/sw/lv_draw_sw_blend.d ./lvgl/lvgl/src/draw/sw/lv_draw_sw_blend.o ./lvgl/lvgl/src/draw/sw/lv_draw_sw_blend.su ./lvgl/lvgl/src/draw/sw/lv_draw_sw_dither.d ./lvgl/lvgl/src/draw/sw/lv_draw_sw_dither.o ./lvgl/lvgl/src/draw/sw/lv_draw_sw_dither.su ./lvgl/lvgl/src/draw/sw/lv_draw_sw_gradient.d ./lvgl/lvgl/src/draw/sw/lv_draw_sw_gradient.o ./lvgl/lvgl/src/draw/sw/lv_draw_sw_gradient.su ./lvgl/lvgl/src/draw/sw/lv_draw_sw_img.d ./lvgl/lvgl/src/draw/sw/lv_draw_sw_img.o ./lvgl/lvgl/src/draw/sw/lv_draw_sw_img.su ./lvgl/lvgl/src/draw/sw/lv_draw_sw_layer.d ./lvgl/lvgl/src/draw/sw/lv_draw_sw_layer.o ./lvgl/lvgl/src/draw/sw/lv_draw_sw_layer.su ./lvgl/lvgl/src/draw/sw/lv_draw_sw_letter.d ./lvgl/lvgl/src/draw/sw/lv_draw_sw_letter.o ./lvgl/lvgl/src/draw/sw/lv_draw_sw_letter.su ./lvgl/lvgl/src/draw/sw/lv_draw_sw_line.d ./lvgl/lvgl/src/draw/sw/lv_draw_sw_line.o ./lvgl/lvgl/src/draw/sw/lv_draw_sw_line.su ./lvgl/lvgl/src/draw/sw/lv_draw_sw_polygon.d ./lvgl/lvgl/src/draw/sw/lv_draw_sw_polygon.o ./lvgl/lvgl/src/draw/sw/lv_draw_sw_polygon.su ./lvgl/lvgl/src/draw/sw/lv_draw_sw_rect.d ./lvgl/lvgl/src/draw/sw/lv_draw_sw_rect.o ./lvgl/lvgl/src/draw/sw/lv_draw_sw_rect.su ./lvgl/lvgl/src/draw/sw/lv_draw_sw_transform.d ./lvgl/lvgl/src/draw/sw/lv_draw_sw_transform.o ./lvgl/lvgl/src/draw/sw/lv_draw_sw_transform.su

.PHONY: clean-lvgl-2f-lvgl-2f-src-2f-draw-2f-sw

