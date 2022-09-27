/*
 * MS_ScreenV2.h
 *
 *  Created on: Aug 22, 2022
 *      Author: n10255460
 */

#ifndef INC_MS_SCREENV2_H_
#define INC_MS_SCREENV2_H_

#include "Screenv2.h"
#include <stdint.h>
#include <stdlib.h>

#include "lvgl/lvgl.h"


typedef enum COLOR {
	COLOR_WHITE = 0xFF,
	COLOR_BLACK = 0x00
} COLOR;

void driver_init();
void lvgl_driver_init();
void MS_Screen_Init();
void MS_Draw();

#endif /* INC_MS_SCREENV2_H_ */
