/*
 * MS_Screen.h
 *
 *  Created on: May 28, 2022
 *      Author: Shahak Kuba
 */

#ifndef INC_MS_SCREEN_H_
#define INC_MS_SCREEN_H_

#include "Screen.h"
#include "ScreenConfig.h"
#include "GUI_Paint.h"
#include "Debug.h"
#include <stdlib.h>

/*
 * Global Defines
 */
// orientation angle of the screen
#define SCREEN_ORIENTATION 0
// colors
#define ClrWhite    0x03
#define ClrGray     0x02
#define ClrDarkGray 0x01
#define ClrBlack    0x00
// Color inversion
#define INVERTED 0xFF
#define NONINVERTED 0x00

/*
 * Global variables definitions
 */
extern uint8_t *STATIC_CANVAS;
extern uint8_t *DYNAMIC_CANVAS;

/*
 * Function Predeclaration
 */
void Screen_Static_Init(void);
void Screen_Dynamic_Init(void);
UBYTE* Canvas_Init(void);
void Screen_Startup(UBYTE * Canvas);
void Static_Display(UBYTE *Canvas);
void Dynamic_Display(UBYTE *Canvas);
void Dynamic_Counter(UBYTE *Canvas, int32_t value);

#endif /* INC_MS_SCREEN_H_ */
