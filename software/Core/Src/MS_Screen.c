/*
 * MS_Screen.c
 *
 *  Created on: May 28, 2022
 *      Author: Shahak Kuba
 */

#include "MS_Screen.h"
#include "ScreenConfig.h"
#include <stdio.h>
#include "heartbeat.h"

extern UBYTE *STATIC_CANVAS;
extern UBYTE *DYNAMIC_CANVAS;

void Screen_Static_Init(UBYTE *Canvas) {
	Screen_4Gray_Init();
	Screen_4Gray_Clear();
	Screen_Delay_ms(500);
	Paint_NewImage(Canvas, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_ORIENTATION,
			NONINVERTED);
}

void Static_Display(UBYTE *Canvas) {
	Screen_4Gray_Display(Canvas);
}

void Screen_Dynamic_Init(UBYTE *Canvas) {
	Screen_1Gray_Init();
	Screen_1Gray_Clear();
	Screen_Delay_ms(500);
	Paint_NewImage(Canvas, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_ORIENTATION,
			NONINVERTED);
}

void Dynamic_Display(UBYTE *Canvas) {
	Screen_1Gray_Display(Canvas);
}

UBYTE* Canvas_Init() {
	UBYTE *canvas;
	UWORD Imagesize = (
			(SCREEN_WIDTH % 4 == 0) ?
					(SCREEN_WIDTH / 4) : (SCREEN_WIDTH / 4 + 1)) * SCREEN_HEIGHT;
	if ((canvas = (UBYTE*) malloc(Imagesize)) == NULL) {
		return NULL;
	}
	return canvas;
}

void Screen_Startup(UBYTE *Canvas) {
	Paint_NewImage(Canvas, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_ORIENTATION,
			NONINVERTED);
	Paint_SelectImage(Canvas);
	Paint_SetScale(4);
	Paint_Clear(WHITE);
	Static_Display(Canvas);
	HAL_Delay(2000);
	Paint_DrawString_EN(15, 200, "QUT Motorsports", &Font24, WHITE, ClrBlack);
	Paint_DrawString_EN(25, 225, "Steering Wheel", &Font24, WHITE, ClrBlack);
	Paint_DrawString_EN(35, 250, "Version 1.0", &Font24, WHITE, ClrBlack);
	Static_Display(Canvas);
	HAL_Delay(5000);
	Paint_Clear(WHITE);
	Static_Display(Canvas);
}

void Draw_BoardStates(UBYTE *Canvas) {
	Paint_SelectImage(Canvas);
	Paint_SetScale(2);
	Paint_Clear(WHITE);
	Paint_ClearWindows(20, 20, 260, 460, WHITE);
	//Paint_DrawNum(50, 50, value, &Font24, ClrBlack, ClrWhite);
	Paint_DrawString_EN(25, 50, "QUT MS VCU STATUS", &Font20, WHITE, ClrBlack);
	char text[15];

	sprintf(text, "CTRL: 0x%02X", VCU_hbState_CTRL.stateID);
	Paint_DrawString_EN(75, 100, text, &Font20, WHITE, ClrBlack);

	sprintf(text, "DASH: 0x%02X", VCU_hbState_DASH.stateID);
	Paint_DrawString_EN(75, 150, text, &Font20, WHITE, ClrBlack);

	sprintf(text, "EBS:  0x%02X", VCU_hbState_EBS.stateID);
	Paint_DrawString_EN(75, 200, text, &Font20, WHITE, ClrBlack);

	sprintf(text, "BMU:  0x%02X", BMU_hbState.stateID);
	Paint_DrawString_EN(75, 250, text, &Font20, WHITE, ClrBlack);

	sprintf(text, "DVL:  0x%02X", DVL_hbState.stateID);
	Paint_DrawString_EN(75, 300, text, &Font20, WHITE, ClrBlack);

//	Paint_DrawString_EN(75, 150, "DASH: 0x00", &Font20, WHITE, ClrBlack);
//	Paint_DrawString_EN(75, 200, "EBS:  0x00", &Font20, WHITE, ClrBlack);
//	Paint_DrawString_EN(75, 250, "BMU:  0x00", &Font20, WHITE, ClrBlack);
//	Paint_DrawString_EN(75, 300, "DVL:  0x00", &Font20, WHITE, ClrBlack);
	Dynamic_Display(Canvas);
}

void Dynamic_Counter(UBYTE *Canvas, int8_t *VCU_STATES) {
	Paint_SelectImage(Canvas);
	Paint_SetScale(2);
	Paint_Clear(WHITE);
	Paint_ClearWindows(20, 20, 260, 460, WHITE);
	//Paint_DrawNum(50, 50, value, &Font24, ClrBlack, ClrWhite);
	Paint_DrawString_EN(25, 50, "QUT MS VCU STATUS", &Font20, WHITE, ClrBlack);
	char text[15];
	sprintf(text, "CTRL: 0x%02X", VCU_STATES[0]);
	Paint_DrawString_EN(75, 100, text, &Font20, WHITE, ClrBlack);
	Paint_DrawString_EN(75, 150, "DASH: 0x00", &Font20, WHITE, ClrBlack);
	Paint_DrawString_EN(75, 200, "EBS:  0x00", &Font20, WHITE, ClrBlack);
	Paint_DrawString_EN(75, 250, "BMU:  0x00", &Font20, WHITE, ClrBlack);
	Paint_DrawString_EN(75, 300, "DVL:  0x00", &Font20, WHITE, ClrBlack);
	Dynamic_Display(Canvas);
//	HAL_Delay(100);
}

