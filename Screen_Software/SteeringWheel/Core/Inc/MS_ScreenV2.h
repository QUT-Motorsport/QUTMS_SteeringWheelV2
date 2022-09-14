/*
 * MS_ScreenV2.h
 *
 *  Created on: Aug 22, 2022
 *      Author: n10255460
 */

#ifndef INC_MS_SCREENV2_H_
#define INC_MS_SCREENV2_H_

#include "Screenv2.h"
#include <stdint.h>
#include <stdlib.h>

typedef enum SET_PIXEL {
	SET_PIXEL_ON = 0xFF,
	SET_PIXEL_OFF = 0x00
} SET_PIXEL;

typedef enum BUFFER_ROW {
	BUFFER_ROW0 = 0x00,
	BUFFER_ROW1 = 0x01,
	BUFFER_ROW2 = 0x02,
	BUFFER_ROW3 = 0x03,
	BUFFER_ROW4 = 0x04
} BUFFER_ROW;


void MS_Screen_Init();
void MS_Screen_SetPixel(uint16_t x, uint16_t y, BUFFER_ROW row, SET_PIXEL pixel);
void MS_Screen_Clear_Buffer(uint8_t clearVal);
void MS_Screen_Flush(BUFFER_ROW row);


#endif /* INC_MS_SCREENV2_H_ */
