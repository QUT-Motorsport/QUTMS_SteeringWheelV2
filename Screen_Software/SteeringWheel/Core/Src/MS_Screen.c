/*
 * MS_Screen.c
 *
 *  Created on: May 28, 2022
 *      Author: Shahak Kuba
 */

#include "MS_Screen.h"
#include "ScreenV2.h"
#include "Screen.h"
#include "ScreenConfig.h"

extern UBYTE *STATIC_CANVAS;
extern UBYTE *DYNAMIC_CANVAS;

void Screen_Static_Init()
{
	Screen_4Gray_Init();
	Screen_4Gray_Clear();
	Screen_Delay_ms(500);
}

void Static_Display(UBYTE *Canvas)
{
	Screen_Display(Canvas);
}

void Screen_Dynamic_Init()
{
	Screen_1Gray_Init();
	Screen_1Gray_Clear();
	Screen_Delay_ms(500);

}

void Dynamic_Display(UBYTE *Canvas)
{
	Screen_1Gray_Display_Part(Canvas, 0, 0, 280, 96);
}

UBYTE* Canvas_Init()
{
	UBYTE *canvas;
	UWORD Imagesize = ((SCREEN_WIDTH % 4 == 0)? (SCREEN_WIDTH / 4 ): (SCREEN_WIDTH / 4 + 1)) * SCREEN_HEIGHT;
	if((canvas = (UBYTE *)malloc(Imagesize)) == NULL) {
		return NULL;
	}
	return canvas;
}

void Screen_Startup(UBYTE * Canvas)
{
	Paint_NewImage(Canvas, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_ORIENTATION, NONINVERTED);
	Paint_SelectImage(Canvas);
	Paint_SetScale(4);
	Paint_Clear(WHITE);

	Static_Display(Canvas);
	HAL_Delay(500);

	Paint_DrawString_EN(15, 200, "QUT Motorsports", &Font24, BLACK, ClrWhite);
	Paint_DrawString_EN(25, 225, "Steering Wheel", &Font24, BLACK, ClrWhite);
	Paint_DrawString_EN(35, 250, "Version 1.0", &Font24, BLACK, ClrWhite);
	Static_Display(Canvas);
	HAL_Delay(2000);
	Paint_Clear(WHITE);
	Static_Display(Canvas);
}

void Dynamic_Counter(UBYTE *Canvas, int32_t value)
{
	Paint_NewImage(Canvas, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_ORIENTATION, NONINVERTED);
	Paint_SelectImage(Canvas);
	Paint_SetScale(4);
	Paint_Clear(BLACK);
	Paint_DrawRectangle(0, 0, 100, 100, 0x02, 0, 0);

	//Static_Display(Canvas);
	Dynamic_Display(Canvas);
}

