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
extern lv_color_t buffer0[BUFFER_SIZE];
extern lv_color_t buffer1[BUFFER_SIZE];
extern lv_disp_drv_t display_driver;
extern lv_disp_t * display;

void driver_init()
{
	Screen_Device_Init();
	Screen_Setup();
	Screen_Clear(COLOR_WHITE); // don't delay cause already wait busy
}

void lvgl_driver_init()
{
	lv_disp_drv_init(&disp_drv);            	/*Basic initialization*/
	disp_drv.draw_buf = &display_buffer;    	/*Set an initialized buffer*/
	disp_drv.flush_cb = Screen_lvgl_Display;    /*Set a flush callback to draw to the display*/
	disp_drv.hor_res = SCREEN_WIDTH;        	/*Set the horizontal resolution in pixels*/
	disp_drv.ver_res = SCREEN_HEIGHT;       	/*Set the vertical resolution in pixels*/
	disp_drv.

	display = lv_disp_drv_register(&disp_drv); 	/*Register the driver and save the created display objects*/
}

void MS_Screen_Init()
{
	lv_init();
	driver_init();
	lv_disp_draw_buf_init(&display_buffer, buffer0, buffer1, BUFFER_SIZE);
}
