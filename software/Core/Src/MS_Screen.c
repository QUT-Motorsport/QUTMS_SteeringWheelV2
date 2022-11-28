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
extern uint8_t DISP_STATE;
extern struct main_screen_text main_txt;
extern dispSelector_t disp_select1;
extern volatile PAINT_TIME sPaint_time;

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
	HAL_Delay(500);
	Paint_DrawString_EN(15, 200, "QUT Motorsports", &Font24, WHITE, ClrBlack);
	Paint_DrawString_EN(25, 225, "Steering Wheel", &Font24, WHITE, ClrBlack);
	Paint_DrawString_EN(35, 250, "Version 1.0", &Font24, WHITE, ClrBlack);
	Static_Display(Canvas);
	HAL_Delay(3000);
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

	main_txt.missions[0] = (dispText_t){.text = "QUT MS Main", .xpos = 50, .ypos = 50, .font = &Font24, .color_fg = ClrWhite, .color_bg = ClrBlack, .select_state = NOT_SELECTED, .mission_ID = 69};
	main_txt.missions[1] = (dispText_t){.text = "MANUAL DRIVING", .xpos = 40, .ypos = 125, .font = &Font20, .color_fg = ClrWhite, .color_bg = ClrBlack, .select_state = NOT_SELECTED, .mission_ID = 0};
	main_txt.missions[2] = (dispText_t){.text = "MISSION: EBS", .xpos = 40, .ypos = 175, .font = &Font20, .color_fg = ClrWhite, .color_bg = ClrBlack, .select_state = NOT_SELECTED, .mission_ID = 1};
	main_txt.missions[3] = (dispText_t){.text = "MISSION: TRACK", .xpos = 40, .ypos = 225, .font = &Font20, .color_fg = ClrWhite, .color_bg = ClrBlack, .select_state = NOT_SELECTED, .mission_ID = 2};
	main_txt.missions[4] = (dispText_t){.text = "INSPECTION", .xpos = 40, .ypos = 275, .font = &Font20, .color_fg = ClrWhite, .color_bg = ClrBlack, .select_state = NOT_SELECTED, .mission_ID = 3};
	main_txt.missions[5] = (dispText_t){.text = "SPECIAL", .xpos = 40, .ypos = 325, .font = &Font20, .color_fg = ClrWhite, .color_bg = ClrBlack, .select_state = NOT_SELECTED, .mission_ID = 4};
	disp_select1 = (dispSelector_t){.xpos = 25, .ypos = 135, .radius = 4, .color = ClrBlack};
	//disp_select2 = (dispSelector_t){.xpos = 25, .ypos = 185, .radius = 4, .color = ClrWhite};
	//disp_select3 = (dispSelector_t){.xpos = 25, .ypos = 235, .radius = 4, .color = ClrWhite};
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
		for (int i = 0; i < 6; i++)
		{
			Paint_DrawString_EN(main_txt.missions[i].xpos, main_txt.missions[i].ypos, main_txt.missions[i].text,  main_txt.missions[i].font,  main_txt.missions[i].color_fg,  main_txt.missions[i].color_bg);
		}
		/*
		Paint_DrawString_EN(main_txt.missions[0].xpos, main_txt.missions[0].ypos, main_txt.missions[0].text,  main_txt.missions[0].font,  main_txt.missions[0].color_fg,  main_txt.missions[0].color_bg);
		Paint_DrawString_EN(main_txt.missions[1].xpos, main_txt.missions[1].ypos, main_txt.missions[1].text,  main_txt.missions[1].font,  main_txt.missions[1].color_fg,  main_txt.missions[1].color_bg);
		Paint_DrawString_EN(main_txt.missions[2].xpos, main_txt.missions[2].ypos, main_txt.missions[2].text,  main_txt.missions[2].font,  main_txt.missions[2].color_fg,  main_txt.missions[2].color_bg);
		Paint_DrawString_EN(main_txt.missions[3].xpos, main_txt.missions[3].ypos, main_txt.missions[3].text,  main_txt.missions[3].font,  main_txt.missions[3].color_fg,  main_txt.missions[3].color_bg);
		Paint_DrawString_EN(main_txt.missions[4].xpos, main_txt.missions[4].ypos, main_txt.missions[4].text,  main_txt.missions[4].font,  main_txt.missions[4].color_fg,  main_txt.missions[4].color_bg);
		Paint_DrawString_EN(main_txt.missions[5].xpos, main_txt.missions[5].ypos, main_txt.missions[5].text,  main_txt.missions[5].font,  main_txt.missions[5].color_fg,  main_txt.missions[5].color_bg);
		*/
		Paint_DrawCircle(disp_select1.xpos, disp_select1.ypos, disp_select1.radius, disp_select1.color, DOT_PIXEL_1X1, DRAW_FILL_FULL);
		Paint_DrawTime(85, 90, &sPaint_time, &Font16, ClrWhite, ClrBlack);
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

void user_select(uint8_t selected_ID)
{
	for(int i = 0; i < 3; i++)
	{
		if(selected_ID == main_txt.missions[i+1].mission_ID)
		{
			main_txt.missions[i+1].color_bg = ClrWhite;
			main_txt.missions[i+1].color_fg = ClrBlack;
			main_txt.missions[i+1].select_state = SELECTED;
		}
		else{
			main_txt.missions[i+1].color_bg = ClrBlack;
			main_txt.missions[i+1].color_fg = ClrWhite;
			main_txt.missions[i+1].select_state = NOT_SELECTED;
		}
	}
	if (selected_ID == 4)
	{
		DISP_STATE = OTHER_SCREEN;
	}
}

void Screen_Update(uint32_t ADC_value, bool btn_pressed){
	// Test update
	if(ADC_value < 300){
		//disp_select1.color = ClrBlack;
		//disp_select2.color = WHITE;
		//disp_select3.color = WHITE;
		disp_select1.ypos = 135;
		if(btn_pressed && (!main_txt.missions[1].select_state) ){
			user_select(0);
		}
	}
	else if(ADC_value < 1500){
		//disp_select1.color = WHITE;
		//disp_select2.color = ClrBlack;
		//disp_select3.color = WHITE;
		disp_select1.ypos = 185;
		if(btn_pressed && (!main_txt.missions[2].select_state) ){
			user_select(1);
		}
	}
	else if(ADC_value < 2700){
		disp_select1.ypos = 235;
		if(btn_pressed && (!main_txt.missions[3].select_state) ){
					user_select(2);
				}
	}
	else if(ADC_value < 4000){
			disp_select1.ypos = 285;
			if(btn_pressed && (!main_txt.missions[4].select_state) ){
						user_select(3);
					}
		}
	else{
		//disp_select1.color = WHITE;
		//disp_select2.color = WHITE;
		//disp_select3.color = ClrBlack;
		disp_select1.ypos = 335;
		if(btn_pressed && (!main_txt.missions[5].select_state) ){
			user_select(4);
		}
	}
}

void Special_Display(UBYTE *Canvas)
{
	Refresh_Display(Canvas);
    Paint_DrawBitMap(pepe_img);
    Dynamic_Display(Canvas);
}
