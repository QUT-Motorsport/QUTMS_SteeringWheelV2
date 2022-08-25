/*
 * Screen.c
 *
 *  Created on: May 28, 2022
 *      Author: Shahak Kuba
 */

#include "Screen.h"
#include "Debug.h"

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

static const UBYTE lut_1Gray_GC[] =
{
0x2A,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//1
0x05,0x2A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//2
0x2A,0x15,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//3
0x05,0x0A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//4
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//5
0x00,0x02,0x03,0x0A,0x00,0x02,0x06,0x0A,0x05,0x00,//6
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//7
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//8
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//9
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//10
0x22,0x22,0x22,0x22,0x22
};

static const UBYTE lut_1Gray_DU[] =
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//1
0x01,0x2A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x0A,0x55,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//3
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//5
0x00,0x00,0x05,0x05,0x00,0x05,0x03,0x05,0x05,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//7
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//9
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x22,0x22,0x22,0x22,0x22
};

static const UBYTE lut_1Gray_A2[] =
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //1
0x0A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //2
0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //3
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //4
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //5
0x00,0x00,0x03,0x05,0x00,0x00,0x00,0x00,0x00,0x00, //6
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //7
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //8
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //9
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //10
0x22,0x22,0x22,0x22,0x22
};

static void Screen_ReadBusy_HIGH(void)
{
    Debug("e-Paper busy\r\n");
    UBYTE busy;
    do {
        busy = Screen_Digital_Read(SBUSY_Pin, SBUSY_GPIO_Port);
    } while(busy);
    Screen_Delay_ms(200);
    Debug("e-Paper busy release\r\n");
}

/******************************************************************************
function :	set the look-up tables
parameter:
******************************************************************************/
void Screen_Load_LUT(UBYTE lut)
{
  UWORD i;
  Screen_SendCommand(0x32);
  for (i = 0; i < 105; i++)
  {
    if(lut == 0)
        Screen_SendData(lut_4Gray_GC[i]);
    else if(lut == 1)
        Screen_SendData(lut_1Gray_GC[i]);
    else if(lut == 2)
        Screen_SendData(lut_1Gray_DU[i]);
    else if(lut == 3)
        Screen_SendData(lut_1Gray_A2[i]);
    else
        Debug("There is no such lut \r\n");
  }
}

/******************************************************************************
function :	Initialize the e-Paper register
parameter:
******************************************************************************/
void Screen_4Gray_Init(void)
{
    Screen_Reset();

    Screen_SendCommand(SCREEN_CMD_SW_RESET);
    Screen_Delay_ms(300);

    Screen_SendCommand(SCREEN_CMD_AUTO_WRITE_RED_RAM);
    Screen_SendData(0xF7);
    Screen_ReadBusy_HIGH();
    Screen_SendCommand(SCREEN_CMD_AUTO_WRITE_BW_RAM);
    Screen_SendData(0xF7);
    Screen_ReadBusy_HIGH();

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

    Screen_SendCommand(SCREEN_CMD_DATA_ENTRY_MODE); // set data entry sequence
    Screen_SendData(0x03);

    Screen_SendCommand(SCREEN_CMD_BORDER_WAVEFORM_CTRL); // set border
    Screen_SendData(0x00);

    Screen_SendCommand(SCREEN_CMD_BOOSTER_SOFT_START_CTRL); // set booster strength
    Screen_SendData(0xAE);
    Screen_SendData(0xC7);
    Screen_SendData(0xC3);
    Screen_SendData(0xC0);
    Screen_SendData(0xC0);

    Screen_SendCommand(SCREEN_CMD_TEMP_SENSOR_CTRL); // set internal sensor on
    Screen_SendData(0x80);

    Screen_SendCommand(SCREEN_CMD_WRITE_VCOM_REG); // set vcom value
    Screen_SendData(0x44);

    Screen_SendCommand(SCREEN_CMD_WRITE_DISPLAY_OPTION_REG); // set display option, these setting turn on previous function
    Screen_SendData(0x00);
    Screen_SendData(0x00);
    Screen_SendData(0x00);
    Screen_SendData(0x00);
    Screen_SendData(0x00);
    Screen_SendData(0x00);
    Screen_SendData(0x00);
    Screen_SendData(0x00);
    Screen_SendData(0x00);
    Screen_SendData(0x00);

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

    Screen_SendCommand(SCREEN_CMD_DISPLAY_UPDATE_CTRL2); // Display Update Control 2
    Screen_SendData(0xCF);
}

/******************************************************************************
function :  Initialize the e-Paper register
parameter:
******************************************************************************/
void Screen_1Gray_Init(void)
{
    Screen_Reset();

    Screen_SendCommand(SCREEN_CMD_SW_RESET);
    Screen_Delay_ms(300);

    Screen_SendCommand(SCREEN_CMD_AUTO_WRITE_RED_RAM);
    Screen_SendData(0xF7);
    Screen_ReadBusy_HIGH();
    Screen_SendCommand(SCREEN_CMD_AUTO_WRITE_BW_RAM);
    Screen_SendData(0xF7);
    Screen_ReadBusy_HIGH();

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

    Screen_SendCommand(SCREEN_CMD_DATA_ENTRY_MODE); // set data entry sequence
    Screen_SendData(0x03);

    Screen_SendCommand(SCREEN_CMD_BORDER_WAVEFORM_CTRL); // set border
    Screen_SendData(0x00);

    Screen_SendCommand(SCREEN_CMD_BOOSTER_SOFT_START_CTRL); // set booster strength
    Screen_SendData(0xAE);
    Screen_SendData(0xC7);
    Screen_SendData(0xC3);
    Screen_SendData(0xC0);
    Screen_SendData(0xC0);

    Screen_SendCommand(SCREEN_CMD_TEMP_SENSOR_CTRL); // set internal sensor on
    Screen_SendData(0x80);

    Screen_SendCommand(SCREEN_CMD_WRITE_VCOM_REG); // set vcom value
    Screen_SendData(0x44);

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

    Screen_SendCommand(SCREEN_CMD_DISPLAY_UPDATE_CTRL2); // Display Update Control 2
    Screen_SendData(0xCF);
}

/******************************************************************************
function :	Clear screen
parameter:
******************************************************************************/
void Screen_4Gray_ClearData(uint8_t data)
{
    UWORD Width, Height;
    Width = (SCREEN_WIDTH % 8 == 0)? (SCREEN_WIDTH / 8 ): (SCREEN_WIDTH / 8 + 1);
    Height = SCREEN_HEIGHT;

    /*Screen_SendCommand(0x18);
    Screen_SendData(0x00);*/

    Screen_SendCommand(0x4E);
    Screen_SendData(0x00);
    Screen_SendData(0x00);
    Screen_SendCommand(0x4F);
    Screen_SendData(0x00);
    Screen_SendData(0x00);

    Screen_SendCommand(0x24);
    for (UWORD j = 0; j < (Height*Width); j++) {
    	   Screen_SendData(j % 4 == 0 ? 0x00 : 0xff);
    }

    Screen_SendCommand(0x4E);
    Screen_SendData(0x00);
    Screen_SendData(0x00);

    Screen_SendCommand(0x4F);
    Screen_SendData(0x00);
    Screen_SendData(0x00);

    Screen_SendCommand(0x26);
    for (UWORD j = 0; j < (Height*Width); j++) {
    	   Screen_SendData(j % 4 == 0 ? 0x00 : 0xff);
    }

    Screen_Load_LUT(0);
    Screen_SendCommand(0x22);
    Screen_SendData(0xC7);

    Screen_SendCommand(0x20);
    Screen_ReadBusy_HIGH();
}


void Screen_4Gray_Clear(void)
{
    UWORD Width, Height;
    Width = (SCREEN_WIDTH % 8 == 0)? (SCREEN_WIDTH / 8 ): (SCREEN_WIDTH / 8 + 1);
    Height = SCREEN_HEIGHT;

    Screen_SendCommand(0x49);
    Screen_SendData(0x00);
    Screen_SendCommand(0x4E);
    Screen_SendData(0x00);
    Screen_SendData(0x00);
    Screen_SendCommand(0x4F);
    Screen_SendData(0x00);
    Screen_SendData(0x00);

    Screen_SendCommand(0x24);
    for (UWORD j = 0; j < Height; j++) {
       for (UWORD i = 0; i < Width; i++) {
           Screen_SendData(0xff);
       }
    }

    Screen_SendCommand(0x4E);
    Screen_SendData(0x00);
    Screen_SendData(0x00);

    Screen_SendCommand(0x4F);
    Screen_SendData(0x00);
    Screen_SendData(0x00);

    Screen_SendCommand(0x26);
    for (UWORD j = 0; j < Height; j++) {
       for (UWORD i = 0; i < Width; i++) {
           Screen_SendData(0xff);
       }
    }

    Screen_Load_LUT(0);
    Screen_SendCommand(0x22);
    Screen_SendData(0xC7);

    Screen_SendCommand(0x20);
    Screen_ReadBusy_HIGH();
}

/******************************************************************************
function :  Clear screen
parameter:
******************************************************************************/
void Screen_1Gray_Clear(void)
{
  UWORD i;
  UWORD IMAGE_COUNTER = SCREEN_WIDTH * SCREEN_HEIGHT / 8;

  Screen_SendCommand(0x4E);
  Screen_SendData(0x00);
  Screen_SendData(0x00);
  Screen_SendCommand(0x4F);
  Screen_SendData(0x00);
  Screen_SendData(0x00);

  Screen_SendCommand(0x24);
  for (i = 0; i < IMAGE_COUNTER; i++)
  {
    Screen_SendData(0xff);
  }

  Screen_Load_LUT(2);

  Screen_SendCommand(0x20);
  Screen_ReadBusy_HIGH();
}

/******************************************************************************
function :	Sends the image buffer in RAM to e-Paper and displays
parameter:
******************************************************************************/
void Screen_4Gray_Display(const UBYTE *Image)
{
    UDOUBLE i,j,k;
    UBYTE temp1,temp2,temp3;

    Screen_SendCommand(0x49);
    Screen_SendData(0x00);


    Screen_SendCommand(0x4E);
    Screen_SendData(0x00);
    Screen_SendData(0x00);


    Screen_SendCommand(0x4F);
    Screen_SendData(0x00);
    Screen_SendData(0x00);

    Screen_SendCommand(0x24);
    for(i=0;i<16800;i++){
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
    Screen_SendCommand(0x4E);
    Screen_SendData(0x00);
    Screen_SendData(0x00);


    Screen_SendCommand(0x4F);
    Screen_SendData(0x00);
    Screen_SendData(0x00);

    Screen_SendCommand(0x26);
    for(i=0; i<16800; i++) {
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

    Screen_Load_LUT(0);

    Screen_SendCommand(0x22);
    Screen_SendData(0xC7);

    Screen_SendCommand(0x20);

    Screen_ReadBusy_HIGH();
}

/******************************************************************************
function :  Sends the image buffer in RAM to e-Paper and displays
parameter:
******************************************************************************/
void Screen_1Gray_Display(const UBYTE *Image)
{
  UWORD i;
  UWORD IMAGE_COUNTER = SCREEN_WIDTH * SCREEN_HEIGHT / 8;

  Screen_SendCommand(0x4E);
  Screen_SendData(0x00);
  Screen_SendData(0x00);
  Screen_SendCommand(0x4F);
  Screen_SendData(0x00);
  Screen_SendData(0x00);

  Screen_SendCommand(0x24);
  for (i = 0; i < IMAGE_COUNTER; i++)
  {
    Screen_SendData(Image[i]);
  }

  Screen_Load_LUT(2);
  Screen_SendCommand(0x20);
  Screen_ReadBusy_HIGH();
}

/******************************************************************************
function :  Sends the image buffer in RAM to e-Paper and displays
parameter:
******************************************************************************/
void Screen_1Gray_Display_Part(const UBYTE *Image, UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend)
{
  UWORD i, Width;
  Width = (Xend-Xstart)%8 == 0 ? (Xend-Xstart)/8 : (Xend-Xstart)/8+1;
  UWORD IMAGE_COUNTER = Width * (Yend-Ystart);

  Screen_SendCommand(0x44);
  Screen_SendData(Xstart & 0xff);
  Screen_SendData((Xstart>>8) & 0x03);
  Screen_SendData(Xend & 0xff);
  Screen_SendData((Xend>>8) & 0x03);
  Screen_SendCommand(0x45);
  Screen_SendData(Ystart & 0xff);
  Screen_SendData((Ystart>>8) & 0x03);
  Screen_SendData(Yend & 0xff);
  Screen_SendData((Yend>>8) & 0x03);

  Screen_SendCommand(0x24);
  for (i = 0; i < IMAGE_COUNTER; i++)
  {
    Screen_SendData(Image[i]);
  }

  Screen_Load_LUT(2);
  Screen_SendCommand(0x20);
  Screen_ReadBusy_HIGH();
}
