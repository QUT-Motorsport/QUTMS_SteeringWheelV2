/*
 * screen.h
 *
 *  Created on: Jan 6, 2022
 *      Author: Calvin
 */

#ifndef INC_SCREEN_H_
#define INC_SCREEN_H_

#include <stdint.h>

#define EPD_WIDTH       240
#define EPD_HEIGHT      416

#define EPD_PANEL_SETTING                               0x00
#define EPD_POWER_SETTING                               0x01
#define EPD_POWER_OFF                                   0x02
#define EPD_POWER_OFF_SEQUENCE_SETTING                  0x03
#define EPD_POWER_ON                                    0x04
#define EPD_POWER_ON_MEASURE                            0x05
#define EPD_BOOSTER_SOFT_START                          0x06
#define EPD_DEEP_SLEEP                                  0x07
#define EPD_DATA_START_TRANSMISSION_1                   0x10
#define EPD_DATA_STOP                                   0x11
#define EPD_DISPLAY_REFRESH                             0x12
#define EPD_DATA_START_TRANSMISSION_2                   0x13
#define EPD_PARTIAL_DATA_START_TRANSMISSION_1           0x14
#define EPD_PARTIAL_DATA_START_TRANSMISSION_2           0x15
#define EPD_PARTIAL_DISPLAY_REFRESH                     0x16
#define EPD_LUT_FOR_VCOM                                0x20
#define EPD_LUT_WHITE_TO_WHITE                          0x21
#define EPD_LUT_BLACK_TO_WHITE                          0x22
#define EPD_LUT_WHITE_TO_BLACK                          0x23
#define EPD_LUT_BLACK_TO_BLACK                          0x24
#define EPD_PLL_CONTROL                                 0x30
#define EPD_TEMPERATURE_SENSOR_COMMAND                  0x40
#define EPD_TEMPERATURE_SENSOR_CALIBRATION              0x41
#define EPD_TEMPERATURE_SENSOR_WRITE                    0x42
#define EPD_TEMPERATURE_SENSOR_READ                     0x43
#define EPD_VCOM_AND_DATA_INTERVAL_SETTING              0x50
#define EPD_LOW_POWER_DETECTION                         0x51
#define EPD_TCON_SETTING                                0x60
#define EPD_TCON_RESOLUTION                             0x61
#define EPD_SOURCE_AND_GATE_START_SETTING               0x62
#define EPD_GET_STATUS                                  0x71
#define EPD_AUTO_MEASURE_VCOM                           0x80
#define EPD_VCOM_VALUE                                  0x81
#define EPD_VCM_DC_SETTING_REGISTER                     0x82
#define EPD_PROGRAM_MODE                                0xA0
#define EPD_ACTIVE_PROGRAM                              0xA1
#define EPD_READ_OTP_DATA                               0xA2

void epd_reset();
void epd_sendCmd(uint8_t reg);
void epd_sendData(uint8_t data);
void epd_waitUntilIdle();

void epd_turnOnDisplay();
uint8_t epd_init();
void epd_clear();


#endif /* INC_SCREEN_H_ */
