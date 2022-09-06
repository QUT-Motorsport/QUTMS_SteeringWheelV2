/*
 * Screenv2.c
 *
 *  Created on: 11 Aug. 2022
 *      Author: n10255460
 */

#include "Screenv2.h"
#include "Debug.h"

static const UBYTE lut_4Gray_GC[] = { 0x2A, 0x06, 0x15, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, //1
		0x28, 0x06, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //2
		0x20, 0x06, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //3
		0x14, 0x06, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //4
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //5
		0x00, 0x02, 0x02, 0x0A, 0x00, 0x00, 0x00, 0x08, 0x08, 0x02, //6
		0x00, 0x02, 0x02, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //7
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //8
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //9
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //10
		0x22, 0x22, 0x22, 0x22, 0x22 };

static const UBYTE lut_1Gray_GC[] = { 0x2A, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, //1
		0x05, 0x2A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //2
		0x2A, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //3
		0x05, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //4
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //5
		0x00, 0x02, 0x03, 0x0A, 0x00, 0x02, 0x06, 0x0A, 0x05, 0x00, //6
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //7
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //8
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //9
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //10
		0x22, 0x22, 0x22, 0x22, 0x22 };

static const UBYTE lut_1Gray_DU[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00,
		0x00, //1
		0x01, 0x2A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x55,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, //3
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, //5
		0x00, 0x00, 0x05, 0x05, 0x00, 0x05, 0x03, 0x05, 0x05, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, //7
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, //9
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22,
		0x22, 0x22, 0x22 };

static const UBYTE lut_1Gray_A2[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, //1
		0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //2
		0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //3
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //4
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //5
		0x00, 0x00, 0x03, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //6
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //7
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //8
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //9
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //10
		0x22, 0x22, 0x22, 0x22, 0x22 };

void Screen_ReadBusy_HIGH(void) {
	UBYTE busy;
	do {
		busy = Screen_Digital_Read(SBUSY_Pin, SBUSY_GPIO_Port);
	} while (busy);
}

void Screen_General_Reset() {
	Screen_Reset();
	Screen_SendCommand(SCREEN_CMD_SW_RESET);
	Screen_Delay_ms(300);
}

void Screen_RAM_Init() {

	Screen_SendCommand(SCREEN_CMD_AUTO_WRITE_RED_RAM);
	Screen_SendData(0xF7);
	Screen_ReadBusy_HIGH();
	Screen_Delay_ms(200);

	Screen_SendCommand(SCREEN_CMD_AUTO_WRITE_BW_RAM);
	Screen_SendData(0xF7);
	Screen_ReadBusy_HIGH();
	Screen_Delay_ms(200);
}

void Screen_Gate_Init() {
	Screen_SendCommand(SCREEN_CMD_GATE_OUTPUT_CONTROL); // setting gate number
	Screen_SendData(0xDF);
	Screen_SendData(0x01);
	Screen_SendData(0x00);

	Screen_SendCommand(SCREEN_CMD_DRIVING_VOLTAGE_CONTROL); // set gate voltage
	Screen_SendData(0x00);

	Screen_SendCommand(SCREEN_CMD_SOURCE_DRIVING_VOLTAGE_CONTROL); // set source voltage
	Screen_SendData(0x41);
	Screen_SendData(0xA8);
	Screen_SendData(0x32);
}

void Screen_Set_DataEntryMode() {
	Screen_SendCommand(SCREEN_CMD_DATA_ENTRY_MODE);
	Screen_SendData(0x03);
}

void Screen_Set_Border() // TODO: use enum for custmoisation if necessary
{
	Screen_SendCommand(SCREEN_CMD_BORDER_WAVEFORM_CTRL); // set border
	Screen_SendData(0x00);
}

void Screen_Set_Booster_Soft_Start() {
	Screen_SendCommand(SCREEN_CMD_BOOSTER_SOFT_START_CTRL); // set booster strength
	Screen_SendData(0xAE);
	Screen_SendData(0xC7);
	Screen_SendData(0xC3);
	Screen_SendData(0xC0);
	Screen_SendData(0xC0);
}

void Screen_Set_Internal_TempSensor_On() {
	Screen_SendCommand(SCREEN_CMD_TEMP_SENSOR_CTRL); // set internal sensor on
	Screen_SendData(0x80);
}

void Screen_Set_Vcom_Value(uint8_t val) {
	Screen_SendCommand(SCREEN_CMD_WRITE_VCOM_REG); // set vcom value
	Screen_SendData(val);
}

void Screen_Setup_DisplayOption() {
	Screen_SendCommand(SCREEN_CMD_WRITE_DISPLAY_OPTION_REG); // set display option, these setting turn on previous function
	Screen_SendData(0x00);     //can switch 1 gray or 4 gray
	Screen_SendData(0xFF);
	Screen_SendData(0xFF);
	Screen_SendData(0xFF);
	Screen_SendData(0xFF);
	Screen_SendData(0x4F);
	Screen_SendData(0xFF);
	Screen_SendData(0xFF);
	Screen_SendData(0xFF);
	Screen_SendData(0xFF);
}

void Screen_Setup_Ram_StartEndPos() // TODO: double check
{
	Screen_SendCommand(SCREEN_CMD_SET_RAM_START_END_XPOS); // setting X direction start/end position of RAM
	Screen_SendData(0x00);
	Screen_SendData(0x00);
	Screen_SendData(0x17);
	Screen_SendData(0x01);

	Screen_SendCommand(SCREEN_CMD_SET_RAM_START_END_YPOS); // setting Y direction start/end position of RAM
	Screen_SendData(0x00);
	Screen_SendData(0x00);
	Screen_SendData(0xDF);
	Screen_SendData(0x01);
}

void Screen_Update_Display_Mode(UBYTE mode) {
	Screen_SendCommand(SCREEN_CMD_DISPLAY_UPDATE_CTRL2); // Display Update Control 2
	Screen_SendData(mode);
}

void Screen_ResetRamCounter() {
	Screen_SendCommand(SCREEN_CMD_SET_RAM_X_COUNTER);
	Screen_SendData(0x00);
	Screen_SendData(0x00);

	Screen_SendCommand(SCREEN_CMD_SET_RAM_Y_COUNTER);
	Screen_SendData(0x00);
	Screen_SendData(0x00);
}

void Screen_SetRamCounter(UWORD x, UWORD y)
{
	  Screen_SendCommand(SCREEN_CMD_SET_RAM_X_COUNTER);
	  Screen_SendData(x & 0xff);
	  Screen_SendData((x >> 8) & 0x03);

	  Screen_SendCommand(SCREEN_CMD_SET_RAM_Y_COUNTER);
	  Screen_SendData(y & 0xff);
	  Screen_SendData((y >> 8) & 0x03);
}

void Screen_SetRam_StartEndPos(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend)
{
	  Screen_SendCommand(SCREEN_CMD_SET_RAM_START_END_XPOS);
	  Screen_SendData(Xstart & 0xff);
	  Screen_SendData((Xstart >> 8) & 0x03);
	  Screen_SendData(Xend & 0xff);
	  Screen_SendData((Xend >> 8) & 0x03);

	  Screen_SendCommand(SCREEN_CMD_SET_RAM_START_END_YPOS);
	  Screen_SendData(Ystart & 0xff);
	  Screen_SendData((Ystart >> 8) & 0x03);
	  Screen_SendData(Yend & 0xff);
	  Screen_SendData((Yend >> 8) & 0x03);
}

void Screen_Load_LUT_constant(const UBYTE *lut)
{
	Screen_SendCommand(SCREEN_CMD_WRITE_LUT_REG);
	int i;
	for (i = 0; i < 105; i++) {
		Screen_SendData(lut[i]);
	}
}

void Screen_Setup(void)
{
	Screen_General_Reset();

	Screen_RAM_Init();

	Screen_Gate_Init();

	Screen_Set_DataEntryMode();

	Screen_Set_Border();

	Screen_Set_Booster_Soft_Start();

	Screen_Set_Internal_TempSensor_On();

	Screen_Set_Vcom_Value(0x44);

	Screen_Setup_DisplayOption();

	Screen_Setup_Ram_StartEndPos();

	Screen_Update_Display_Mode(SCREEN_DISPLAY_MODE_2);
}

void Screen_Clear(void) {
	const uint32_t IMAGE_COUNTER = SCREEN_WIDTH * SCREEN_HEIGHT / 8;

	Screen_ResetRamCounter();

	Screen_SendCommand(SCREEN_CMD_WRITE_BW_RAM);
	for (uint32_t i = 0; i < IMAGE_COUNTER; ++i) {
		Screen_SendData(0xFF);
	}

	Screen_ResetRamCounter();

	Screen_SendCommand(SCREEN_CMD_WRITE_RED_RAM);
	for (uint32_t i = 0; i < IMAGE_COUNTER; ++i) {
		Screen_SendData(0xFF);
	}

	Screen_Load_LUT_constant(lut_4Gray_GC);

	Screen_SendCommand(SCREEN_CMD_MASTER_ACTIVATION);
	Screen_ReadBusy_HIGH();
	Screen_Delay_ms(20);
}

void Screen_Display(const UBYTE *Image) { // TODO: support Red as well
	const uint32_t IMAGE_COUNTER = SCREEN_WIDTH * SCREEN_HEIGHT / 8;
    UDOUBLE i,j,k;
    UBYTE temp1,temp2,temp3;

    Screen_SendCommand(0x49);
    Screen_SendData(0x00);

    Screen_ResetRamCounter();

    Screen_SendCommand(SCREEN_CMD_WRITE_BW_RAM);
    for(i=0;i<IMAGE_COUNTER;i++){
        temp3=0;
        for(j=0; j<2; j++) {
            temp1 = Image[i*2+j];
            for(k=0; k<2; k++) {
                temp2 = temp1&0xC0;
                if(temp2 == 0xC0)
                    temp3 |= 0x01;//white
                else if(temp2 == 0x00)
                    temp3 |= 0x00;  //black
                else if(temp2 == 0x80)
                    temp3 |= 0x00;  //gray1
                else //0x40
                    temp3 |= 0x01; //gray2
                temp3 <<= 1;

                temp1 <<= 2;
                temp2 = temp1&0xC0 ;
                if(temp2 == 0xC0)  //white
                    temp3 |= 0x01;
                else if(temp2 == 0x00) //black
                    temp3 |= 0x00;
                else if(temp2 == 0x80)
                    temp3 |= 0x00; //gray1
                else    //0x40
                    temp3 |= 0x01;	//gray2
                if(j!=1 || k!=1)
                    temp3 <<= 1;

                temp1 <<= 2;
            }

        }
        Screen_SendData(temp3);
    }
    // new  data
    Screen_ResetRamCounter();

    Screen_SendCommand(SCREEN_CMD_WRITE_RED_RAM);
    for(i=0; i<IMAGE_COUNTER; i++) {
        temp3=0;
        for(j=0; j<2; j++) {
            temp1 = Image[i*2+j];
            for(k=0; k<2; k++) {
                temp2 = temp1&0xC0 ;
                if(temp2 == 0xC0)
                    temp3 |= 0x01;//white
                else if(temp2 == 0x00)
                    temp3 |= 0x00;  //black
                else if(temp2 == 0x80)
                    temp3 |= 0x01;  //gray1
                else //0x40
                    temp3 |= 0x00; //gray2
                temp3 <<= 1;

                temp1 <<= 2;
                temp2 = temp1&0xC0 ;
                if(temp2 == 0xC0)  //white
                    temp3 |= 0x01;
                else if(temp2 == 0x00) //black
                    temp3 |= 0x00;
                else if(temp2 == 0x80)
                    temp3 |= 0x01; //gray1
                else    //0x40
                    temp3 |= 0x00;	//gray2
                if(j!=1 || k!=1)
                    temp3 <<= 1;

                temp1 <<= 2;
            }
        }
        Screen_SendData(temp3);
    }

    Screen_Load_LUT_constant(lut_4Gray_GC);

    Screen_Update_Display_Mode(SCREEN_DISPLAY_MODE_1);

    Screen_SendCommand(SCREEN_CMD_MASTER_ACTIVATION);

    Screen_ReadBusy_HIGH();
}

void Screen_DisplayPartial(const UBYTE * Image, uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend)
{
	const UWORD Width = (Xend-Xstart)%8 == 0 ? (Xend-Xstart)/8 : (Xend-Xstart)/8+1;
	const UWORD IMAGE_COUNTER = Width * (Yend-Ystart);

	Screen_SetRam_StartEndPos(Xstart, Ystart, Xend, Yend);
	Screen_SetRamCounter(Xstart, Ystart);

	Screen_SendCommand(SCREEN_CMD_WRITE_RED_RAM);
	for(UWORD i; i < IMAGE_COUNTER; ++i)
	{
		Screen_SendData(Image[i]);
	}

	Screen_Load_LUT_constant(lut_1Gray_DU);

	Screen_Update_Display_Mode(SCREEN_DISPLAY_MODE_2);

	Screen_SendCommand(SCREEN_CMD_MASTER_ACTIVATION);

	Screen_ReadBusy_HIGH();
}

void Screen_Sleep(void)
{
    Screen_SendCommand(0X50); // mystery command
    Screen_SendData(0xf7);
    Screen_SendCommand(SCREEN_CMD_POWER_OFF);  	//power off
    Screen_SendCommand(SCREEN_CMD_SLEEP);  	//deep sleep
    Screen_SendData(0xA5);
}
