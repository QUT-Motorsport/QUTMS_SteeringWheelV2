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
 * delay ms
**/
#define Screen_Delay_ms(_ms) HAL_Delay(_ms);

void Screen_WriteByte(UBYTE value);
void Screen_Digital_Write(uint16_t pin, GPIO_TypeDef* port, uint8_t value);
uint8_t Screen_Digital_Read(uint16_t pin, GPIO_TypeDef* port);

int Screen_Init(void);
void Screen_Exit(void);
