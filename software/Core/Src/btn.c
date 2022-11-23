/*
 * btn.c
 *
 *  Created on: Nov 23, 2022
 *      Author: n9996095
 */
#include "main.h"
#include "btn.h"


bool btn_pressed()
{
	bool pressed;
	uint8_t btn_counter = 0;
	while(!HAL_GPIO_ReadPin(Btn2_GPIO_Port, Btn2_Pin))
	{
		btn_counter++;
	}
	if(btn_counter > 15){
		pressed = true;
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		btn_counter = 0;
	}
	else{
		pressed = false;
	}
	return pressed;
}

