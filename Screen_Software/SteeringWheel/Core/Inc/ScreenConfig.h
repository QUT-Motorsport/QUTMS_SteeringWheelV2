/*
 * Screen.h
 *
 *  Created on: May 28, 2022
 *      Author: Shahak Kuba
 *      an adaptation of the Waveshare Epaper display GIT
 */

#ifndef SCREEN_CONFIG_H_
#define SCREEN_CONFIG_H_

#include "main.h"
#include "stm32f2xx_hal.h"
#include "stm32f2xx_hal_gpio.h"
#include <stdint.h>
#include <stdio.h>

// Display resolution
#define SCREEN_WIDTH       280
#define SCREEN_HEIGHT      480

// Screen commands
#define SCREEN_CMD_GATE_OUTPUT_CONTROL				0x01
#define SCREEN_CMD_POWER_OFF						0x02
#define SCREEN_CMD_DRIVING_VOLTAGE_CONTROL			0x03
#define SCREEN_CMD_SOURCE_DRIVING_VOLTAGE_CONTROL	0x04
#define SCREEN_CMD_INIT_CODE_SETTING_OTP_PROG		0x08 // initial Code Setting OTP Program
#define SCREEN_CMD_SLEEP							0x07
#define SCREEN_CMD_INIT_WRITE_REG_CODE_SETTING		0x09 // Write Register for Initial Code Setting
#define SCREEN_CMD_INIT_READ_REG_CODE_SETTING		0x0A // Read Register for Initial Code Setting
#define SCREEN_CMD_BOOSTER_SOFT_START_CTRL			0x0C
#define SCREEN_CMD_DEEP_SLEEP_MODE					0x10
#define SCREEN_CMD_DATA_ENTRY_MODE					0x11
#define SCREEN_CMD_SW_RESET							0x12 // Software
#define SCREEN_CMD_HV_READY_DETECTION				0x14 // High Voltage
#define SCREEN_CMD_TEMP_SENSOR_CTRL					0x18
#define SCREEN_CMD_MASTER_ACTIVATION				0x20
#define SCREEN_CMD_DISPLAY_UPDATE_CTRL2				0x22
#define SCREEN_CMD_WRITE_BW_RAM						0x24
#define SCREEN_CMD_WRITE_RED_RAM					0x26
#define SCREEN_CMD_WRITE_VCOM_REG					0x2C
#define SCREEN_CMD_WRITE_LUT_REG					0x32
#define SCREEN_CMD_WRITE_DISPLAY_OPTION_REG			0x37
#define SCREEN_CMD_BORDER_WAVEFORM_CTRL				0x3C
#define SCREEN_CMD_SET_RAM_START_END_XPOS			0x44
#define SCREEN_CMD_SET_RAM_START_END_YPOS			0x45
#define SCREEN_CMD_AUTO_WRITE_RED_RAM				0x46
#define SCREEN_CMD_AUTO_WRITE_BW_RAM				0x47
#define SCREEN_CMD_SET_RAM_X_COUNTER				0x4E
#define SCREEN_CMD_SET_RAM_Y_COUNTER				0x4F

/**
 * data
**/
#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

/**
 * delay ms
**/
#define Screen_Delay_ms(_ms) HAL_Delay(_ms);

void Screen_WriteByte(UBYTE value);

static inline void Screen_Digital_Write(uint16_t pin, GPIO_TypeDef* port, uint8_t value)
{
	HAL_GPIO_WritePin(port, pin, value == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

static inline uint8_t Screen_Digital_Read(uint16_t pin, GPIO_TypeDef* port)
{
	return HAL_GPIO_ReadPin(port, pin);
}


static inline void Screen_Device_Init()
{
    Screen_Digital_Write(SDC_Pin, SDC_GPIO_Port, 0);
    Screen_Digital_Write(SCS_Pin, SCS_GPIO_Port, 0);
    Screen_Digital_Write(SRST_Pin, SRST_GPIO_Port, 1);
}

static inline void Screen_Exit()
{
    Screen_Digital_Write(SDC_Pin, SDC_GPIO_Port, 0);
    Screen_Digital_Write(SCS_Pin, SCS_GPIO_Port, 0);
    Screen_Digital_Write(SRST_Pin, SRST_GPIO_Port, 0);
}

/******************************************************************************
function :	Software reset
parameter:
******************************************************************************/
static inline void Screen_Reset(void)
{
    Screen_Digital_Write(SRST_Pin, SRST_GPIO_Port, 1);
    Screen_Delay_ms(20);
    Screen_Digital_Write(SRST_Pin, SRST_GPIO_Port, 0);
    Screen_Delay_ms(2);
    Screen_Digital_Write(SRST_Pin, SRST_GPIO_Port, 1);
    Screen_Delay_ms(20);
}

/******************************************************************************
function :	send command
parameter:
     Reg : Command register
******************************************************************************/
static inline void Screen_SendCommand(UBYTE Reg)
{
    Screen_Digital_Write(SDC_Pin, SDC_GPIO_Port, 0);

    Screen_Digital_Write(SCS_Pin, SCS_GPIO_Port, 0);
    Screen_WriteByte(Reg);
    Screen_Digital_Write(SCS_Pin, SCS_GPIO_Port, 1);
}

/******************************************************************************
function :	send data
parameter:
    Data : Write data
******************************************************************************/
static inline void Screen_SendData(UBYTE Data)
{
    Screen_Digital_Write(SDC_Pin, SDC_GPIO_Port, 1);

    Screen_Digital_Write(SCS_Pin, SCS_GPIO_Port, 0);
    Screen_WriteByte(Data);
    Screen_Digital_Write(SCS_Pin, SCS_GPIO_Port, 1);
}

#endif
