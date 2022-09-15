/*
 * MS_GL.h
 *
 *  Created on: Aug 25, 2022
 *      Author: n10255460
 */

#ifndef INC_MS_GL_H_
#define INC_MS_GL_H_
#include <stdint.h>

typedef enum COLOR {
	COLOR_WHITE = 0x00,
	COLOR_BLACK = 0xFF
} COLOR;

void MSGL_Clear(uint8_t color);
void MSGL_DrawPixel(uint8_t color, uint16_t x, uint16_t y);
void MSGL_DrawLine(uint8_t color, uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end);
void MSGL_DrawChar(char c, uint16_t x, uint16_t y);

#endif /* INC_MS_GL_H_ */
