/*
 * btn.h
 *
 *  Created on: Nov 23, 2022
 *      Author: n9996095
 */

#ifndef INC_BTN_H_
#define INC_BTN_H_

#include "main.h"
#include <stdbool.h>

//bool btn_pressed( void );
void debounce_cb( void );
void external_btn1_cb( void );
void external_btn2_cb( void );
void external_btn3_cb( void );
void external_btn4_cb( void );
#endif /* INC_BTN_H_ */
