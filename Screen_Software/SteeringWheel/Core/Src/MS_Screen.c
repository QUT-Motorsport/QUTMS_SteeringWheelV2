/*
 * MS_Screen.c
 *
 *  Created on: May 28, 2022
 *      Author: Shahak Kuba
 */

#include "MS_Screen.h"
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
	Screen_4Gray_Display(Canvas);
}

void Screen_Dynamic_Init()
{
	Screen_1Gray_Init();
	Screen_1Gray_Clear();
	Screen_Delay_ms(500);

}

void Dynamic_Display(UBYTE *Canvas)
{
	Screen_1Gray_Display(Canvas);
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

	Paint_DrawString_EN(15, 200, "QUT Motorsports", &Font24, WHITE, ClrBlack);
	Paint_DrawString_EN(25, 225, "Steering Wheel", &Font24, WHITE, ClrBlack);
	Paint_DrawString_EN(35, 250, "Version 1.0", &Font24, WHITE, ClrBlack);
	Static_Display(Canvas);
	HAL_Delay(10000);
	Paint_Clear(WHITE);
	Static_Display(Canvas);
}

void Dynamic_Counter(UBYTE *Canvas, int32_t value)
{
	Paint_NewImage(Canvas, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_ORIENTATION, NONINVERTED);
	Paint_SelectImage(Canvas);
	Paint_SetScale(4);
	Paint_Clear(WHITE);
	Paint_ClearWindows(20, 20, 80, 80, WHITE);
	Paint_DrawNum(50, 50, value, &Font24, WHITE, ClrBlack);
	Dynamic_Display(Canvas);
	HAL_Delay(1000);
}
