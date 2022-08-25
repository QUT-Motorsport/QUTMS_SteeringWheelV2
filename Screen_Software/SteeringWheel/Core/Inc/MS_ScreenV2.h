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

void MS_Screen_Init();
void MS_Screen_DrawPixel(uint16_t x, uint16_t y);
void MS_Screen_Clear_Buffer();
void MS_Screen_Flush();


#endif /* INC_MS_SCREENV2_H_ */