################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/lvgl/src/libs/fsdrv/lv_fs_cbfs.c \
../lvgl/lvgl/src/libs/fsdrv/lv_fs_fatfs.c \
../lvgl/lvgl/src/libs/fsdrv/lv_fs_posix.c \
../lvgl/lvgl/src/libs/fsdrv/lv_fs_stdio.c \
../lvgl/lvgl/src/libs/fsdrv/lv_fs_win32.c 

OBJS += \
./lvgl/lvgl/src/libs/fsdrv/lv_fs_cbfs.o \
./lvgl/lvgl/src/libs/fsdrv/lv_fs_fatfs.o \
./lvgl/lvgl/src/libs/fsdrv/lv_fs_posix.o \
./lvgl/lvgl/src/libs/fsdrv/lv_fs_stdio.o \
./lvgl/lvgl/src/libs/fsdrv/lv_fs_win32.o 

C_DEPS += \
./lvgl/lvgl/src/libs/fsdrv/lv_fs_cbfs.d \
./lvgl/lvgl/src/libs/fsdrv/lv_fs_fatfs.d \
./lvgl/lvgl/src/libs/fsdrv/lv_fs_posix.d \
./lvgl/lvgl/src/libs/fsdrv/lv_fs_stdio.d \
./lvgl/lvgl/src/libs/fsdrv/lv_fs_win32.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/lvgl/src/libs/fsdrv/%.o lvgl/lvgl/src/libs/fsdrv/%.su: ../lvgl/lvgl/src/libs/fsdrv/%.c lvgl/lvgl/src/libs/fsdrv/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F207xx -c -I../Core/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F2xx/Include -I../Drivers/CMSIS/Include -I../lvgl -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-lvgl-2f-lvgl-2f-src-2f-libs-2f-fsdrv

clean-lvgl-2f-lvgl-2f-src-2f-libs-2f-fsdrv:
	-$(RM) ./lvgl/lvgl/src/libs/fsdrv/lv_fs_cbfs.d ./lvgl/lvgl/src/libs/fsdrv/lv_fs_cbfs.o ./lvgl/lvgl/src/libs/fsdrv/lv_fs_cbfs.su ./lvgl/lvgl/src/libs/fsdrv/lv_fs_fatfs.d ./lvgl/lvgl/src/libs/fsdrv/lv_fs_fatfs.o ./lvgl/lvgl/src/libs/fsdrv/lv_fs_fatfs.su ./lvgl/lvgl/src/libs/fsdrv/lv_fs_posix.d ./lvgl/lvgl/src/libs/fsdrv/lv_fs_posix.o ./lvgl/lvgl/src/libs/fsdrv/lv_fs_posix.su ./lvgl/lvgl/src/libs/fsdrv/lv_fs_stdio.d ./lvgl/lvgl/src/libs/fsdrv/lv_fs_stdio.o ./lvgl/lvgl/src/libs/fsdrv/lv_fs_stdio.su ./lvgl/lvgl/src/libs/fsdrv/lv_fs_win32.d ./lvgl/lvgl/src/libs/fsdrv/lv_fs_win32.o ./lvgl/lvgl/src/libs/fsdrv/lv_fs_win32.su

.PHONY: clean-lvgl-2f-lvgl-2f-src-2f-libs-2f-fsdrv

