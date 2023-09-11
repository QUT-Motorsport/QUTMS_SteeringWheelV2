################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/lvgl/src/draw/sdl/lv_draw_sdl.c \
../lvgl/lvgl/src/draw/sdl/lv_draw_sdl_arc.c \
../lvgl/lvgl/src/draw/sdl/lv_draw_sdl_bg.c \
../lvgl/lvgl/src/draw/sdl/lv_draw_sdl_composite.c \
../lvgl/lvgl/src/draw/sdl/lv_draw_sdl_img.c \
../lvgl/lvgl/src/draw/sdl/lv_draw_sdl_label.c \
../lvgl/lvgl/src/draw/sdl/lv_draw_sdl_layer.c \
../lvgl/lvgl/src/draw/sdl/lv_draw_sdl_line.c \
../lvgl/lvgl/src/draw/sdl/lv_draw_sdl_mask.c \
../lvgl/lvgl/src/draw/sdl/lv_draw_sdl_polygon.c \
../lvgl/lvgl/src/draw/sdl/lv_draw_sdl_rect.c \
../lvgl/lvgl/src/draw/sdl/lv_draw_sdl_stack_blur.c \
../lvgl/lvgl/src/draw/sdl/lv_draw_sdl_texture_cache.c \
../lvgl/lvgl/src/draw/sdl/lv_draw_sdl_utils.c 

OBJS += \
./lvgl/lvgl/src/draw/sdl/lv_draw_sdl.o \
./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_arc.o \
./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_bg.o \
./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_composite.o \
./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_img.o \
./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_label.o \
./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_layer.o \
./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_line.o \
./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_mask.o \
./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_polygon.o \
./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_rect.o \
./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_stack_blur.o \
./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_texture_cache.o \
./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_utils.o 

C_DEPS += \
./lvgl/lvgl/src/draw/sdl/lv_draw_sdl.d \
./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_arc.d \
./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_bg.d \
./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_composite.d \
./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_img.d \
./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_label.d \
./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_layer.d \
./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_line.d \
./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_mask.d \
./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_polygon.d \
./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_rect.d \
./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_stack_blur.d \
./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_texture_cache.d \
./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_utils.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/lvgl/src/draw/sdl/%.o lvgl/lvgl/src/draw/sdl/%.su: ../lvgl/lvgl/src/draw/sdl/%.c lvgl/lvgl/src/draw/sdl/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F207xx -c -I../Core/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F2xx/Include -I../Drivers/CMSIS/Include -I../lvgl -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-lvgl-2f-lvgl-2f-src-2f-draw-2f-sdl

clean-lvgl-2f-lvgl-2f-src-2f-draw-2f-sdl:
	-$(RM) ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl.d ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl.o ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl.su ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_arc.d ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_arc.o ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_arc.su ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_bg.d ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_bg.o ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_bg.su ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_composite.d ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_composite.o ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_composite.su ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_img.d ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_img.o ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_img.su ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_label.d ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_label.o ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_label.su ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_layer.d ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_layer.o ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_layer.su ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_line.d ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_line.o ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_line.su ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_mask.d ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_mask.o ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_mask.su ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_polygon.d ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_polygon.o ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_polygon.su ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_rect.d ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_rect.o ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_rect.su ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_stack_blur.d ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_stack_blur.o ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_stack_blur.su ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_texture_cache.d ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_texture_cache.o ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_texture_cache.su ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_utils.d ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_utils.o ./lvgl/lvgl/src/draw/sdl/lv_draw_sdl_utils.su

.PHONY: clean-lvgl-2f-lvgl-2f-src-2f-draw-2f-sdl

