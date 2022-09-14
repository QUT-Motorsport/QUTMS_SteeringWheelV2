/*
 * MS_GL.c
 *
 *  Created on: 14 Sep. 2022
 *      Author: n10255460
 */

#include "MS_GL.h"
#include "ScreenConfig.h"
#include <string.h>

#define BUFFER_MEM_SIZE BUFFER_SIZE * sizeof(uint8_t)
extern uint8_t Buffer[BUFFER_SIZE];



void MSGL_Clear(uint8_t color)
{
	memset(&Buffer, color, BUFFER_MEM_SIZE);
}

void MSGL_DrawPixel(uint8_t color, uint16_t x, uint16_t y)
{
	Buffer[x + y] = color;
}

void MSGL_DrawLine(uint8_t color, uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end)
{

}

void MSGL_DrawChar(char c, uint16_t x, uint16_t y)
{

}
