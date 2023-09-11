################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/lvgl/src/draw/lv_draw.c \
../lvgl/lvgl/src/draw/lv_draw_arc.c \
../lvgl/lvgl/src/draw/lv_draw_img.c \
../lvgl/lvgl/src/draw/lv_draw_label.c \
../lvgl/lvgl/src/draw/lv_draw_layer.c \
../lvgl/lvgl/src/draw/lv_draw_line.c \
../lvgl/lvgl/src/draw/lv_draw_mask.c \
../lvgl/lvgl/src/draw/lv_draw_rect.c \
../lvgl/lvgl/src/draw/lv_draw_transform.c \
../lvgl/lvgl/src/draw/lv_draw_triangle.c \
../lvgl/lvgl/src/draw/lv_img_buf.c \
../lvgl/lvgl/src/draw/lv_img_cache.c \
../lvgl/lvgl/src/draw/lv_img_decoder.c 

OBJS += \
./lvgl/lvgl/src/draw/lv_draw.o \
./lvgl/lvgl/src/draw/lv_draw_arc.o \
./lvgl/lvgl/src/draw/lv_draw_img.o \
./lvgl/lvgl/src/draw/lv_draw_label.o \
./lvgl/lvgl/src/draw/lv_draw_layer.o \
./lvgl/lvgl/src/draw/lv_draw_line.o \
./lvgl/lvgl/src/draw/lv_draw_mask.o \
./lvgl/lvgl/src/draw/lv_draw_rect.o \
./lvgl/lvgl/src/draw/lv_draw_transform.o \
./lvgl/lvgl/src/draw/lv_draw_triangle.o \
./lvgl/lvgl/src/draw/lv_img_buf.o \
./lvgl/lvgl/src/draw/lv_img_cache.o \
./lvgl/lvgl/src/draw/lv_img_decoder.o 

C_DEPS += \
./lvgl/lvgl/src/draw/lv_draw.d \
./lvgl/lvgl/src/draw/lv_draw_arc.d \
./lvgl/lvgl/src/draw/lv_draw_img.d \
./lvgl/lvgl/src/draw/lv_draw_label.d \
./lvgl/lvgl/src/draw/lv_draw_layer.d \
./lvgl/lvgl/src/draw/lv_draw_line.d \
./lvgl/lvgl/src/draw/lv_draw_mask.d \
./lvgl/lvgl/src/draw/lv_draw_rect.d \
./lvgl/lvgl/src/draw/lv_draw_transform.d \
./lvgl/lvgl/src/draw/lv_draw_triangle.d \
./lvgl/lvgl/src/draw/lv_img_buf.d \
./lvgl/lvgl/src/draw/lv_img_cache.d \
./lvgl/lvgl/src/draw/lv_img_decoder.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/lvgl/src/draw/%.o lvgl/lvgl/src/draw/%.su: ../lvgl/lvgl/src/draw/%.c lvgl/lvgl/src/draw/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F207xx -c -I../Core/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F2xx/Include -I../Drivers/CMSIS/Include -I../lvgl -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-lvgl-2f-lvgl-2f-src-2f-draw

clean-lvgl-2f-lvgl-2f-src-2f-draw:
	-$(RM) ./lvgl/lvgl/src/draw/lv_draw.d ./lvgl/lvgl/src/draw/lv_draw.o ./lvgl/lvgl/src/draw/lv_draw.su ./lvgl/lvgl/src/draw/lv_draw_arc.d ./lvgl/lvgl/src/draw/lv_draw_arc.o ./lvgl/lvgl/src/draw/lv_draw_arc.su ./lvgl/lvgl/src/draw/lv_draw_img.d ./lvgl/lvgl/src/draw/lv_draw_img.o ./lvgl/lvgl/src/draw/lv_draw_img.su ./lvgl/lvgl/src/draw/lv_draw_label.d ./lvgl/lvgl/src/draw/lv_draw_label.o ./lvgl/lvgl/src/draw/lv_draw_label.su ./lvgl/lvgl/src/draw/lv_draw_layer.d ./lvgl/lvgl/src/draw/lv_draw_layer.o ./lvgl/lvgl/src/draw/lv_draw_layer.su ./lvgl/lvgl/src/draw/lv_draw_line.d ./lvgl/lvgl/src/draw/lv_draw_line.o ./lvgl/lvgl/src/draw/lv_draw_line.su ./lvgl/lvgl/src/draw/lv_draw_mask.d ./lvgl/lvgl/src/draw/lv_draw_mask.o ./lvgl/lvgl/src/draw/lv_draw_mask.su ./lvgl/lvgl/src/draw/lv_draw_rect.d ./lvgl/lvgl/src/draw/lv_draw_rect.o ./lvgl/lvgl/src/draw/lv_draw_rect.su ./lvgl/lvgl/src/draw/lv_draw_transform.d ./lvgl/lvgl/src/draw/lv_draw_transform.o ./lvgl/lvgl/src/draw/lv_draw_transform.su ./lvgl/lvgl/src/draw/lv_draw_triangle.d ./lvgl/lvgl/src/draw/lv_draw_triangle.o ./lvgl/lvgl/src/draw/lv_draw_triangle.su ./lvgl/lvgl/src/draw/lv_img_buf.d ./lvgl/lvgl/src/draw/lv_img_buf.o ./lvgl/lvgl/src/draw/lv_img_buf.su ./lvgl/lvgl/src/draw/lv_img_cache.d ./lvgl/lvgl/src/draw/lv_img_cache.o ./lvgl/lvgl/src/draw/lv_img_cache.su ./lvgl/lvgl/src/draw/lv_img_decoder.d ./lvgl/lvgl/src/draw/lv_img_decoder.o ./lvgl/lvgl/src/draw/lv_img_decoder.su

.PHONY: clean-lvgl-2f-lvgl-2f-src-2f-draw

