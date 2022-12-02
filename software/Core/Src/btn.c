/*
 * btn.c
 *
 *  Created on: Nov 23, 2022
 *      Author: n9996095
 */
#include "main.h"
#include "btn.h"
#include "MS_Screen.h"
#include <stdbool.h>
#include <CAN_SW.h>


extern volatile bool btn_pressed[4];
extern uint8_t DISP_STATE;
volatile bool prev_btn_state = false;
volatile bool curr_btn_state = false;
extern SW_HeartbeatState_t SW_hbState;


void debounce_cb( void )
{
	prev_btn_state = curr_btn_state;

	if(!HAL_GPIO_ReadPin(Btn1_GPIO_Port, Btn1_Pin)){
		curr_btn_state = true;
	} else {
		curr_btn_state = false;
	}

}


void external_btn1_cb( void )
{
	if( prev_btn_state && curr_btn_state)
	{
		SW_hbState.flags._SW_Flags.FAN_ENABLE = (SW_hbState.flags._SW_Flags.FAN_ENABLE == 0) ? 1 : 0;
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

