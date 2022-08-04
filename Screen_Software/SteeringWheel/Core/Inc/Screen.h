/*
 * Screen.h
 *
 *  Created on: May 28, 2022
 *      Author: Shahak Kuba
 */

#ifndef INC_SCREEN_H_
#define INC_SCREEN_H_

#include "ScreenConfig.h"

// Display resolution
#define SCREEN_WIDTH       280
#define SCREEN_HEIGHT      480

// Screen commands
#define SCREEN_CMD_GATE_OUTPUT_CONTROL				0x01
#define SCREEN_CMD_DRIVING_VOLTAGE_CONTROL			0x03
#define SCREEN_CMD_SOURCE_DRIVING_VOLTAGE_CONTROL	0x04
#define SCREEN_CMD_INIT_CODE_SETTING_OTP_PROG		0x08 // initial Code Setting OTP Program
#define SCREEN_CMD_INIT_WRITE_REG_CODE_SETTING		0x09 // Write Register for Initial Code Setting
#define SCREEN_CMD_INIT_READ_REG_CODE_SETTING		0x0A // Read Register for Initial Code Setting
#define SCREEN_CMD_BOOSTER_SOFT_START_CTRL			0x0C
#define SCREEN_CMD_DEEP_SLEEP_MODE					0x10
#define SCREEN_CMD_DATA_ENTRY_MODE					0x11
#define SCREEN_CMD_SW_RESET							0x12 // Software
#define SCREEN_CMD_HV_READY_DETECTION				0x14 // High Voltage
#define SCREEN_CMD_TEMP_SENSOR_CTRL					0x18
#define SCREEN_CMD_DISPLAY_UPDATE_CTRL2				0x22
#define SCREEN_CMD_WRITE_VCOM_REG					0x2C
#define SCREEN_CMD_WRITE_DISPLAY_OPTION_REG			0x37
#define SCREEN_CMD_BORDER_WAVEFORM_CTRL				0x3C
#define SCREEN_CMD_SET_RAM_START_END_XPOS			0x44
#define SCREEN_CMD_SET_RAM_START_END_YPOS			0x45
#define SCREEN_CMD_AUTO_WRITE_RED_RAM				0x46
#define SCREEN_CMD_AUTO_WRITE_BW_RAM				0x47
#define SCREEN_CMD_


void Screen_4Gray_Clear(void);
void Screen_4Gray_Init(void);
void Screen_4Gray_Display(const UBYTE *Image);
void Screen_4Gray_ClearData(uint8_t data);

void Screen_1Gray_Clear(void);
void Screen_1Gray_Init(void);
void Screen_1Gray_Display(const UBYTE *Image);
void Screen_1Gray_Display_Part(const UBYTE *Image, UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend);

void Screen_Sleep(void);

#endif /* INC_SCREEN_H_ */