/*
 * MS_ScreenV2.c
 *
 *  Created on: Aug 22, 2022
 *      Author: n10255460
 */


#include "MS_ScreenV2.h"
#include "ScreenV2.h"
#include <string.h>

#define BUFFER_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 8)
#define BUFFER_PART_WIDTH 280
#define BUFFER_PART_HEIGHT 96

static uint8_t ScreenBuffer[5][BUFFER_PART_WIDTH * BUFFER_PART_HEIGHT / 8];

void MS_Screen_Init()
{
	// zeroing out buffer
	memset(&ScreenBuffer, 0x00, BUFFER_SIZE * sizeof(uint8_t));

	Screen_Device_Init();
	Screen_Setup();

	Screen_Clear();
	Screen_Delay_ms(100);
}

void MS_Screen_SetPixel(uint16_t x, uint16_t y, BUFFER_ROW row, SET_PIXEL pixel)
{
	const uint16_t xOffset = (x % 8) == 0 ? (x / 8) - 1 : (x / 8);
	const uint16_t yOffset = y * (BUFFER_PART_WIDTH / 8);
	const uint8_t binIndex = x % 8;


	if (pixel == SET_PIXEL_ON) {
		switch(binIndex)
		{
		case 0: ScreenBuffer[row][xOffset + yOffset] |= 0x01; break; // 1
		case 1: ScreenBuffer[row][xOffset + yOffset] |= 0x02; break; // 2
		case 2: ScreenBuffer[row][xOffset + yOffset] |= 0x04; break; // 4
		case 3: ScreenBuffer[row][xOffset + yOffset] |= 0x08; break; // 8
		case 4: ScreenBuffer[row][xOffset + yOffset] |= 0x10; break; // 16
		case 5: ScreenBuffer[row][xOffset + yOffset] |= 0x20; break; // 32
		case 6: ScreenBuffer[row][xOffset + yOffset] |= 0x40; break; // 64
		case 7: ScreenBuffer[row][xOffset + yOffset] |= 0x80; break; // 128
		default: break;
		}
	} else {
		switch(binIndex)
		{
		case 0: ScreenBuffer[row][xOffset + yOffset] &= 0xFE; break;
		case 1: ScreenBuffer[row][xOffset + yOffset] &= 0xFD; break;
		case 2: ScreenBuffer[row][xOffset + yOffset] &= 0xFB; break;
		case 3: ScreenBuffer[row][xOffset + yOffset] &= 0xF7; break;
		case 4: ScreenBuffer[row][xOffset + yOffset] &= 0xEF; break;
		case 5: ScreenBuffer[row][xOffset + yOffset] &= 0xDF; break;
		case 6: ScreenBuffer[row][xOffset + yOffset] &= 0xBF; break;
		case 7: ScreenBuffer[row][xOffset + yOffset] &= 0x7F; break;
		default: break;
		}
	}


}

void MS_Screen_Clear_Buffer(uint8_t clearVal)
{
	memset(&ScreenBuffer, clearVal, BUFFER_SIZE * sizeof(uint8_t));
}


void MS_Screen_Flush(BUFFER_ROW row)
{
	Screen_DisplayBufferRow(ScreenBuffer, row);
}
