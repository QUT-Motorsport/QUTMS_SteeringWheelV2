/*
 * Screen.h
 *
 *  Created on: May 28, 2022
 *      Author: Shahak Kuba
 *      an adaptation of the Waveshare Epaper display GIT
 */

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
 * GPIO read and write
**/

#define Screen_Digital_Write(_pin, _port,_value) HAL_GPIO_WritePin(_pin, _port, _value == 0? GPIO_PIN_RESET:GPIO_PIN_SET)
#define Screen_Digital_Read(_pin, _port) HAL_GPIO_ReadPin(_pin, _port)

/**
 * delay ms
**/
#define Screen_Delay_ms(_ms) HAL_Delay(_ms);

void Screen_WriteByte(UBYTE value);

int Screen_Init(void);
void Screen_Exit(void);
