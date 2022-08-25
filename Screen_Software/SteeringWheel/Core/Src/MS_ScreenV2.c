/*
 * MS_ScreenV2.c
 *
 *  Created on: Aug 22, 2022
 *      Author: n10255460
 */


#include "MS_ScreenV2.h"
#include "Screen.h"

#define BUFFER_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 8)
uint8_t Buffer[BUFFER_SIZE];

void MS_Screen_Init()
{
	// zeroing out buffer
	memset(&Buffer, 0x00, BUFFER_SIZE * sizeof(uint8_t));

	Screen_Device_Init();
	Screen_Setup();

	Screen_Clear(); // don't delay cause already wait busy
}

void MS_Screen_DrawPixel(uint16_t x, uint16_t y)
{
	Buffer[(x + (y * SCREEN_WIDTH)) / 8] = 0xFF;
}


void MS_Screen_Clear_Buffer()
{

	//Screen_DrawBlank();

	memset(&Buffer, 0x02, BUFFER_SIZE * sizeof(uint8_t) / 2);
}


void MS_Screen_Flush()
{
	Screen_DrawBlank();
}
