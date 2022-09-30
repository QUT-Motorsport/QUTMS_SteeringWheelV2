/*
 * MS_ScreenV2.c
 *
 *  Created on: Aug 22, 2022
 *      Author: n10255460
 */


#include "MS_ScreenV2.h"
#include "Screenv2.h"
#include <stdint.h>
#include <string.h>

#define BUFFER_MEM_SIZE BUFFER_SIZE * sizeof(uint8_t)

extern lv_disp_draw_buf_t display_buffer;
extern lv_color_t buffer[BUFFER_SIZE * 8];
extern lv_disp_drv_t display_driver;
extern lv_disp_t * display;

void driver_init()
{
	Screen_Device_Init();
	Screen_Setup();
	Screen_Clear(COLOR_BLACK); // don't delay cause already wait busy
}

void lvgl_driver_init()
{
	lv_disp_drv_init(&display_driver);            		/*Basic initialization*/
	display_driver.draw_buf = &display_buffer;    		/*Set an initialized buffer*/
	display_driver.flush_cb = Screen_lvgl_Display;   	/*Set a flush callback to draw to the display*/
	display_driver.hor_res = SCREEN_WIDTH;        		/*Set the horizontal resolution in pixels*/
	display_driver.ver_res = SCREEN_HEIGHT;       		/*Set the vertical resolution in pixels*/
	display_driver.direct_mode = 1;
	display_driver.full_refresh = 1;
	display_driver.antialiasing = 0;

	display = lv_disp_drv_register(&display_driver); 	/*Register the driver and save the created display objects*/
}

void MS_Screen_Init()
{
	//lv_init();
	driver_init();
	//lv_disp_draw_buf_init(&display_buffer, buffer, NULL, BUFFER_SIZE);
}

void MS_Draw()
{
	lv_obj_t * btn = lv_btn_create(lv_scr_act());
	lv_obj_center(btn);
	lv_obj_set_size(btn, 100, 50);
}
