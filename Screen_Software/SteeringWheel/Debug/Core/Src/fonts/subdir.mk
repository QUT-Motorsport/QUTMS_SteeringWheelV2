################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/fonts/font12.c \
../Core/Src/fonts/font12CN.c \
../Core/Src/fonts/font16.c \
../Core/Src/fonts/font20.c \
../Core/Src/fonts/font24.c \
../Core/Src/fonts/font24CN.c \
../Core/Src/fonts/font8.c 

OBJS += \
./Core/Src/fonts/font12.o \
./Core/Src/fonts/font12CN.o \
./Core/Src/fonts/font16.o \
./Core/Src/fonts/font20.o \
./Core/Src/fonts/font24.o \
./Core/Src/fonts/font24CN.o \
./Core/Src/fonts/font8.o 

C_DEPS += \
./Core/Src/fonts/font12.d \
./Core/Src/fonts/font12CN.d \
./Core/Src/fonts/font16.d \
./Core/Src/fonts/font20.d \
./Core/Src/fonts/font24.d \
./Core/Src/fonts/font24CN.d \
./Core/Src/fonts/font8.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/fonts/%.o: ../Core/Src/fonts/%.c Core/Src/fonts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F207xx -c -I../Core/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F2xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-fonts

clean-Core-2f-Src-2f-fonts:
	-$(RM) ./Core/Src/fonts/font12.d ./Core/Src/fonts/font12.o ./Core/Src/fonts/font12CN.d ./Core/Src/fonts/font12CN.o ./Core/Src/fonts/font16.d ./Core/Src/fonts/font16.o ./Core/Src/fonts/font20.d ./Core/Src/fonts/font20.o ./Core/Src/fonts/font24.d ./Core/Src/fonts/font24.o ./Core/Src/fonts/font24CN.d ./Core/Src/fonts/font24CN.o ./Core/Src/fonts/font8.d ./Core/Src/fonts/font8.o

.PHONY: clean-Core-2f-Src-2f-fonts

