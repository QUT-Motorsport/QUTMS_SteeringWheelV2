/*
 * MS_Screen.c
 *
 *  Created on: May 28, 2022
 *      Author: Shahak Kuba
 */

#include "MS_Screen.h"

UBYTE *Canvas;

int MS_Screen_Init()
{
	// Initialise the screen
	if(Screen_Init()!=0){
	        return -1;
	 }

	Screen_4Gray_Init();
	Screen_1Gray_Init();
	Screen_Delay_ms(500);

	/* you have to edit the startup_stm32fxxx.s file and set a big enough heap size */
	UWORD Imagesize = ((SCREEN_WIDTH % 4 == 0)? (SCREEN_WIDTH / 4 ): (SCREEN_WIDTH / 4 + 1)) * SCREEN_HEIGHT;
	if((Canvas = (UBYTE *)malloc(Imagesize)) == NULL) {
		return -1;
	}
	return 0;
}


