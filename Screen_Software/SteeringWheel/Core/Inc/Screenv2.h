#ifndef SCREEN_V2_H_
#define SCREEN_V2_H_

#include "ScreenConfig.h"
#include "lvgl/lvgl.h"

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

void Screen_Clear4G(void);
void Screen_Display4G(const uint8_t * image);

void Screen_lvgl_Display(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);

void Screen_Setup(void);
void Screen_Clear(uint8_t color);
void Screen_Display(const uint8_t * image);
void Screen_DisplayPartial(const uint8_t * image, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
void Screen_Sleep(void);

#endif
