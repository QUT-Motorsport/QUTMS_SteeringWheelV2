/*
 * CapEst.c
 *
 *  Created on: Jun 15, 2023
 *      Author: kuba
 */


#include "CapEst.h"

extern uint32_t ADC2_value;

int CapEstConversion(uint32_t ADC_Value)
{
	return (int) ( 200.0*(((float)ADC_Value/(float)MAX_ADC) - 0.5) );
}


