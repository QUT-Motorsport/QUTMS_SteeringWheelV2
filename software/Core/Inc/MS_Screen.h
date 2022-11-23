/*
 * MS_Screen.h
 *
 *  Created on: May 28, 2022
 *      Author: Shahak Kuba
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MSSCREEN_H
#define __MSSCREEN_H

#ifndef INC_MS_SCREEN_H_
#define INC_MS_SCREEN_H_

#include "Screen.h"
#include "ScreenConfig.h"
#include "fonts.h"
#include "GUI_Paint.h"
#include "Debug.h"
#include <stdlib.h>

/*
 * Type Definitions
 */
typedef struct
{
	char text[20];
	uint16_t xpos;
	uint16_t ypos;
	sFONT *font;
	uint16_t color_fg;
	uint16_t color_bg;
	uint8_t select_state;

} dispText_t;

typedef struct
{
	uint16_t xpos;
	uint16_t ypos;
	uint16_t radius;
	uint16_t color;

} dispSelector_t;

struct main_screen_text
{
	dispText_t title;
	dispText_t driver;
	dispText_t driverless_mission1;
	dispText_t driverless_mission2;
};

enum TEXT_STATE{
	NOT_SELECTED = 0,
	SELECTED
};

// TODO Add more screen states
enum SCREEN_STATE{
	STARTUP_SCREEN = 0,
	MAIN_SCREEN,
	OTHER_SCREEN
};
/*
 * Global Defines
 */
// orientation angle of the screen
#define SCREEN_ORIENTATION 180
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
void Screen_Static_Init(UBYTE *Canvas);
void Screen_Dynamic_Init(UBYTE *Canvas);
UBYTE* Canvas_Init( void );
void Screen_Startup(UBYTE * Canvas);
void Static_Display(UBYTE *Canvas);
void Dynamic_Display(UBYTE *Canvas);
void Dynamic_Clear( void );

void Dynamic_Counter(UBYTE *Canvas, int8_t *VCU_STATES); // NOT USING
void Draw_BoardStates(UBYTE *Canvas);

void init_Main_text( void );
void Refresh_Display(UBYTE *Canvas);
void Screen_Display(UBYTE *Canvas);
void Screen_Update( uint32_t ADC_value );

#endif
#endif
