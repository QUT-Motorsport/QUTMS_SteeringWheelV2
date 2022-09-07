#ifndef SCREEN_V2_H_
#define SCREEN_V2_H_

#include "ScreenConfig.h"

// Display Mode
#define SCREEN_DISPLAY_MODE_1						0xC7
#define SCREEN_DISPLAY_MODE_2						0xCF
#define SCREEN_DISPLAY_MODE_1_HARDNFAST				0x91
#define SCREEN_DISPLAY_MODE_2_HARDNFAST				0x99

// Screen data
typedef enum SCREEN_DATA_ENTRY_MODE {
	SCREEN_DATA_ENTRY_MODE_INC_X = 0b00000001,
	SCREEN_DATA_ENTRY_MODE_INC_Y = 0b00000010,
	SCREEN_DATA_ENTRY_MODE_DEC_Y = 0b00000000,
	SCREEN_DATA_ENTRY_MDOE_DEC_X = 0b00000000,
	SCREEN_DATA_ENTRY_MODE_Y_UPDATE = 0b00000100, // TODO: double check this is correct
	SCREEN_DATA_ENTRY_MODE_X_UPDATE = 0b00000000
} SCREEN_DATA_ENTRY_MODE;

typedef enum SCREEN_DISPLAY_MODE {
	SCREEN_DISPLAY_MODE_1GRAY = 0x00,
	SCREEN_DISPLAY_MODE_4GRAY = 0xFF
} SCREEN_DISPLAY_MODE;

void Screen_Clear(void);
void Screen_Setup(void);
void Screen_Display(const UBYTE * Image);
void Screen_DisplayBufferRow(const uint8_t Buffer[5][280 * 96 / 8], uint8_t row);
void Screen_DisplayPartial(const UBYTE * Image, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
void Screen_Sleep(void);

#endif
