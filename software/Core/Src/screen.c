/*
 * screen.c
 *
 *  Created on: Jan 6, 2022
 *      Author: Calvin
 */

#include "screen.h"
#include "spi.h"
#include "main.h"

void epd_reset() {
	HAL_GPIO_WritePin(RST_SCREEN_GPIO_Port, RST_SCREEN_Pin, GPIO_PIN_SET);
	HAL_Delay(200);
	HAL_GPIO_WritePin(RST_SCREEN_GPIO_Port, RST_SCREEN_Pin, GPIO_PIN_RESET);
	HAL_Delay(200);
	HAL_GPIO_WritePin(RST_SCREEN_GPIO_Port, RST_SCREEN_Pin, GPIO_PIN_SET);
	HAL_Delay(200);
}

void epd_sendCmd(uint8_t reg) {
	HAL_GPIO_WritePin(DC_SCREEN_GPIO_Port, DC_SCREEN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(CS_SCREEN_GPIO_Port, CS_SCREEN_Pin, GPIO_PIN_RESET);

	uint8_t send = reg;

	HAL_SPI_Transmit(&hspi1, &send, 1, 1000);

	HAL_GPIO_WritePin(CS_SCREEN_GPIO_Port, CS_SCREEN_Pin, GPIO_PIN_SET);
}

void epd_sendData(uint8_t data) {
	HAL_GPIO_WritePin(DC_SCREEN_GPIO_Port, DC_SCREEN_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(CS_SCREEN_GPIO_Port, CS_SCREEN_Pin, GPIO_PIN_RESET);

	uint8_t send = data;

	HAL_SPI_Transmit(&hspi1, &send, 1, 1000);

	HAL_GPIO_WritePin(CS_SCREEN_GPIO_Port, CS_SCREEN_Pin, GPIO_PIN_SET);
}

void epd_waitUntilIdle() {
	uint8_t state = HAL_GPIO_ReadPin(SCREEN_BUSY_GPIO_Port, SCREEN_BUSY_Pin);
	while (state == GPIO_PIN_RESET) {
		HAL_Delay(100);
		state = HAL_GPIO_ReadPin(SCREEN_BUSY_GPIO_Port, SCREEN_BUSY_Pin);
	}
}

void epd_turnOnDisplay() {
	epd_sendCmd(EPD_DISPLAY_REFRESH);
	epd_waitUntilIdle();
}

uint8_t epd_init() {
	HAL_GPIO_WritePin(BUS_SCREEN_GPIO_Port, BUS_SCREEN_Pin, GPIO_PIN_RESET);

	epd_reset();

	epd_sendCmd(0x01);
	epd_sendData(0x2f);
	epd_sendData(0x04);
	epd_sendData(0x30);
	epd_sendData(0x30);
	epd_sendData(0x0f);

	epd_sendCmd(0x06);
	epd_sendData(0x0f);

	epd_sendCmd(0x61);
	epd_sendData(0xF0);
	epd_sendData(0x01);
	epd_sendData(0xA0);

	epd_sendCmd(0x04);
	HAL_Delay(100);
	//epd_waitUntilIdle();

	epd_sendCmd(0x30);
	epd_sendData(0x09);

	epd_sendCmd(0x82);
	epd_sendData(0x26);

	HAL_Delay(100);

	//epd_waitUntilIdle();

	epd_turnOnDisplay();

	return 0;
}

void epd_clear() {
	uint16_t width;
	uint16_t height;
	width = ((EPD_WIDTH % 8) == 0) ? (EPD_WIDTH / 8) : ((EPD_WIDTH / 8) + 1);
	height = EPD_HEIGHT;

	epd_sendCmd(EPD_DATA_START_TRANSMISSION_1);
	HAL_Delay(2);

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			epd_sendData(0xFF);
		}
	}

	epd_sendCmd(EPD_DATA_START_TRANSMISSION_2);
	HAL_Delay(2);

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			epd_sendData(0x00);
		}
	}
}

