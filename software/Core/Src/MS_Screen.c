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
#include "main.h"

extern UBYTE *STATIC_CANVAS;
extern UBYTE *DYNAMIC_CANVAS;
extern uint8_t SCR_STATE;
extern struct main_screen_text main_txt;
extern dispSelector_t disp_select1;
extern dispSelector_t disp_select2;
extern dispSelector_t disp_select3;

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

void init_Main_text()
{

	main_txt.title = (dispText_t){.text = "QUT MS Main", .xpos = 50, .ypos = 50, .font = &Font24, .color_fg = ClrWhite, .color_bg = ClrBlack, .select_state = NOT_SELECTED};
	main_txt.driver = (dispText_t){.text = "DRIVER MODE", .xpos = 40, .ypos = 125, .font = &Font20, .color_fg = ClrWhite, .color_bg = ClrBlack, .select_state = NOT_SELECTED};
	main_txt.driverless_mission1 = (dispText_t){.text = "DVL MISSION 1", .xpos = 40, .ypos = 175, .font = &Font20, .color_fg = ClrWhite, .color_bg = ClrBlack, .select_state = NOT_SELECTED};
	main_txt.driverless_mission2 = (dispText_t){.text = "DVL MISSION 2", .xpos = 40, .ypos = 225, .font = &Font20, .color_fg = ClrWhite, .color_bg = ClrBlack, .select_state = NOT_SELECTED};
	disp_select1 = (dispSelector_t){.xpos = 25, .ypos = 135, .radius = 4, .color = ClrBlack};
	disp_select2 = (dispSelector_t){.xpos = 25, .ypos = 185, .radius = 4, .color = ClrWhite};
	disp_select3 = (dispSelector_t){.xpos = 25, .ypos = 235, .radius = 4, .color = ClrWhite};
}

void Dynamic_Clear()
{
	Screen_1Gray_Clear();
}

void Refresh_Display(UBYTE *Canvas)
{
	Paint_SelectImage(Canvas);
	Paint_SetScale(2);
	Paint_Clear(WHITE);
	Paint_ClearWindows(20, 20, 260, 460, WHITE);
}

void Screen_Display(UBYTE *Canvas)
{
	//if (SCR_STATE == MAIN_SCREEN)
	//{
		// refresh screen
		Refresh_Display(Canvas);

		// draw new screen bitmap
		Paint_DrawString_EN(main_txt.title.xpos, main_txt.title.ypos, main_txt.title.text,  main_txt.title.font,  main_txt.title.color_fg,  main_txt.title.color_bg);
		Paint_DrawString_EN(main_txt.driver.xpos, main_txt.driver.ypos, main_txt.driver.text,  main_txt.driver.font,  main_txt.driver.color_fg,  main_txt.driver.color_bg);
		Paint_DrawString_EN(main_txt.driverless_mission1.xpos, main_txt.driverless_mission1.ypos, main_txt.driverless_mission1.text,  main_txt.driverless_mission1.font,  main_txt.driverless_mission1.color_fg,  main_txt.driverless_mission1.color_bg);
		Paint_DrawString_EN(main_txt.driverless_mission2.xpos, main_txt.driverless_mission2.ypos, main_txt.driverless_mission2.text,  main_txt.driverless_mission2.font,  main_txt.driverless_mission2.color_fg,  main_txt.driverless_mission2.color_bg);
		Paint_DrawCircle(disp_select1.xpos, disp_select1.ypos, disp_select1.radius, disp_select1.color, DOT_PIXEL_1X1, DRAW_FILL_FULL);
		//Paint_DrawCircle(disp_select2.xpos, disp_select2.ypos, disp_select2.radius, disp_select2.color, DOT_PIXEL_1X1, DRAW_FILL_FULL);
		//Paint_DrawCircle(disp_select3.xpos, disp_select3.ypos, disp_select3.radius, disp_select3.color, DOT_PIXEL_1X1, DRAW_FILL_FULL);
		// display dynamic
		Dynamic_Display(Canvas);

	/*
	else if (SCR_STATE == STARTUP_SCREEN)
	{
		UBYTE *Canvas_STARTUP = Canvas_Init();
		Screen_Static_Init(Canvas_STARTUP);
		Screen_Startup(Canvas_STARTUP);
		HAL_Delay(3000);
		free(Canvas_STARTUP);
		SCR_STATE = MAIN_SCREEN;
	}*/
}

void Screen_Update(uint32_t ADC_value){
	// Test update
	if(ADC_value < 1000){
		//disp_select1.color = ClrBlack;
		//disp_select2.color = WHITE;
		//disp_select3.color = WHITE;
		disp_select1.ypos = 135;
	}
	else if(ADC_value < 2000){
		//disp_select1.color = WHITE;
		//disp_select2.color = ClrBlack;
		//disp_select3.color = WHITE;
		disp_select1.ypos = 185;
	}
	else{
		//disp_select1.color = WHITE;
		//disp_select2.color = WHITE;
		//disp_select3.color = ClrBlack;
		disp_select1.ypos = 235;
	}
}
