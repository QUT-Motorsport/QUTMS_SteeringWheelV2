#include "ScreenConfig.h"
#include "stm32f2xx_hal_spi.h"

extern SPI_HandleTypeDef hspi1;

void Screen_WriteByte(UBYTE value)
{
	uint8_t data = value;
    HAL_SPI_Transmit(&hspi1, &data, 1, 1000);
}

void Screen_Digital_Write(uint16_t pin, GPIO_TypeDef* port, uint8_t value) {
	HAL_GPIO_WritePin(port, pin, value == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

uint8_t Screen_Digital_Read(uint16_t pin, GPIO_TypeDef* port) {
	return HAL_GPIO_ReadPin(port, pin);
}

int Screen_Init(void)
{
    Screen_Digital_Write(SDC_Pin, SDC_GPIO_Port, 0);
    Screen_Digital_Write(SCS_Pin, SCS_GPIO_Port, 0);
    Screen_Digital_Write(SRST_Pin, SRST_GPIO_Port, 1);
	return 0;
}

void Screen_Exit(void)
{
    Screen_Digital_Write(SDC_Pin, SDC_GPIO_Port, 0);
    Screen_Digital_Write(SCS_Pin, SCS_GPIO_Port, 0);

    //close 5V
    Screen_Digital_Write(SRST_Pin, SRST_GPIO_Port, 0);
}
