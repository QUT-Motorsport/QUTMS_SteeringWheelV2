/*
 * btn.c
 *
 *  Created on: Nov 23, 2022
 *      Author: n9996095
 */
#include "main.h"
#include "btn.h"
#include "MS_Screen.h"
#include <CAN_SW.h>
extern volatile bool btn_pressed[4];
extern uint8_t DISP_STATE;
extern SW_HeartbeatState_t SW_hbState;


/*
bool btn_pressed()
{
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
}*/

void external_btn1_cb( void )
{
	SW_hbState.flags._SW_Flags.FAN_ENABLE = (SW_hbState.flags._SW_Flags.FAN_ENABLE == 0) ? 1 : 0;
	for(int i = 0; i < 100; i++)
	{

	}
}

void external_btn2_cb( void )
{
	DISP_STATE = VCU_STATE_SCREEN;
}

void external_btn3_cb( void )
{
	DISP_STATE = MAIN_SCREEN;
}

void external_btn4_cb( void )
{
	btn_pressed[0] = true;
	HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
}

