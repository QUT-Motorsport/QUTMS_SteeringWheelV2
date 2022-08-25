/*
 * Screen.h
 *
 *  Created on: May 28, 2022
 *      Author: Shahak Kuba
 */

#ifndef INC_SCREEN_H_
#define INC_SCREEN_H_

#include "ScreenConfig.h"


void Screen_4Gray_Clear(void);
void Screen_4Gray_Init(void);
void Screen_4Gray_Display(const UBYTE *Image);
void Screen_4Gray_ClearData(uint8_t data);

void Screen_1Gray_Clear(void);
void Screen_1Gray_Init(void);
void Screen_1Gray_Display(const UBYTE *Image);
void Screen_1Gray_Display_Part(const UBYTE *Image, UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend);

void Screen_Sleep(void);

#endif /* INC_SCREEN_H_ */
