/*
 * MS_ScreenV2.c
 *
 *  Created on: Aug 22, 2022
 *      Author: n10255460
 */


#include "MS_ScreenV2.h"
#include "Screenv2.h"
#include "SCreen.h"
#include "MS_GL.h"
#include <stdint.h>
#include <string.h>

#define BUFFER_MEM_SIZE BUFFER_SIZE * sizeof(uint8_t)
extern uint8_t Buffer[BUFFER_SIZE];

void MS_Screen_Init()
{
	// zeroing out buffer
	memset(Buffer, COLOR_WHITE, BUFFER_MEM_SIZE);

	Screen_Device_Init();
	Screen_Setup();

	Screen_Clear(COLOR_BLACK); // don't delay cause already wait busy
}

void MS_Screen_Flush()
{
	Screen_Display(Buffer);
}
