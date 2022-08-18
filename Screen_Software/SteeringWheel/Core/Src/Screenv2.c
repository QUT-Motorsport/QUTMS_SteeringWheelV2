/*
 * Screenv2.c
 *
 *  Created on: 11 Aug. 2022
 *      Author: n10255460
 */

#include "Screenv2.h"

static const UBYTE lut_4Gray_GC[] =
{
	0x2A,0x06,0x15,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//1
	0x28,0x06,0x14,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//2
	0x20,0x06,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//3
	0x14,0x06,0x28,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//4
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//5
	0x00,0x02,0x02,0x0A,0x00,0x00,0x00,0x08,0x08,0x02,//6
	0x00,0x02,0x02,0x0A,0x00,0x00,0x00,0x00,0x00,0x00,//7
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//8
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//9
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//10
	0x22,0x22,0x22,0x22,0x22
};

/*void Screen_Clear()                                                                                                                                                                                                              x
{

}*/

// TODO: Figure out what this does, hex codes?
void Screen_RedRam_Init()
{
	Screen_SendCommand(SCREEN_CMD_AUTO_WRITE_RED_RAM);
	Screen_SendData(0xF7);
	Screen_ReadBusy_HIGH();

	Screen_SendCommand(SCREEN_CMD_AUTO_WRITE_BW_RAM);
	Screen_SendData(0xF7);
	Screen_ReadBusy_HIGH();
}


void Screen_Software_Reset()
{
	Screen_Reset();
	Screen_SendCommand(SCREEN_CMD_SW_RESET);
	Screen_Delay_ms(300);
}

void Screen_Gate_Init()
{
	Screen_SendCommand(SCREEN_CMD_GATE_OUTPUT_CONTROL); // setting gate number
	Screen_SendData(0xDF);
	Screen_SendData(0x01);
	Screen_SendData(0x00);

	Screen_SendCommand(SCREEN_CMD_DRIVING_VOLTAGE_CONTROL); // set gate voltage
	Screen_SendData(0x00);
}

void Screen_Set_DataEntryMode(SCREEN_DATA_ENTRY_MODE mode)
{
	Screen_SendCommand(SCREEN_CMD_DATA_ENTRY_MODE);
	Screen_SendData(mode);
}

void Screen_Set_Border() // TODO: use enum for custmoisation if necessary
{
	Screen_SendCommand(SCREEN_CMD_BORDER_WAVEFORM_CTRL); // set border
	Screen_SendData(0x00);
}

void Screen_Set_Booster_Soft_Start()
{
	Screen_SendCommand(SCREEN_CMD_BOOSTER_SOFT_START_CTRL); // set booster strength
	Screen_SendData(0xAE);
	Screen_SendData(0xC7);
	Screen_SendData(0xC3);
	Screen_SendData(0xC0);
	Screen_SendData(0xC0);
}

void Screen_Set_Internal_TempSensor_On()
{
	Screen_SendCommand(SCREEN_CMD_TEMP_SENSOR_CTRL); // set internal sensor on
	Screen_SendData(0x80);
}

void Screen_Set_Vcom_Value(uint8_t val)
{
	Screen_SendCommand(SCREEN_CMD_WRITE_VCOM_REG); // set vcom value
	Screen_SendData(val);
}

void Screen_Setup()
{
	Screen_Software_Reset();
	Screen_RedRam_Init();
	Screen_Gate_Init();
	Screen_Set_DataEntryMode(SCREEN_DATA_ENTRY_MODE_INC_X | SCREEN_DATA_ENTRY_MODE_INC_Y | SCREEN_DATA_ENTRY_MODE_X_UPDATE);
	Screen_Set_Border();
	Screen_Set_Booster_Soft_Start();
	Screen_Set_Internal_TempSensor_On();
	Screen_set_Vcom_Value(0x44);

}

void Screen_Display(const UBYTE * Image)
{

}