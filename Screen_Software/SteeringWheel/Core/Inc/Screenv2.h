#ifndef SCREEN_V2_H_
#define SCREEN_V2_H_

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


// Screen data
typedef enum SCREEN_DATA_ENTRY_MODE {
	SCREEN_DATA_ENTRY_MODE_INC_X = 0b00000001,
	SCREEN_DATA_ENTRY_MODE_INC_Y = 0b00000010,
	SCREEN_DATA_ENTRY_MODE_DEC_Y = 0b00000000,
	SCREEN_DATA_ENTRY_MDOE_DEC_X = 0b00000000,
	SCREEN_DATA_ENTRY_MODE_Y_UPDATE = 0b00000100, // TODO: double check this is correct
	SCREEN_DATA_ENTRY_MODE_X_UPDATE = 0b00000000
} SCREEN_DATA_ENTRY_MODE;

void Screen_Clear();
void Screen_Setup();
void Screen_Display(const UBYTE * Image);


#endif