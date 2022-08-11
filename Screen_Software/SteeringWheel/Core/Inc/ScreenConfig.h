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


static inline void Screen_Init()
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


#endif
