#include "ScreenConfig.h"
#include "stm32f2xx_hal_spi.h"

extern SPI_HandleTypeDef hspi1;

void Screen_WriteByte(UBYTE value)
{
	uint8_t data = value;
    HAL_SPI_Transmit(&hspi1, &data, 1, 1000);
}

void Screen_Digital_Write(uint16_t pin, GPIO_TypeDef* port, uint8_t value);


uint8_t Screen_Digital_Read(uint16_t pin, GPIO_TypeDef* port);

void Screen_Init(void);

void Screen_Exit(void);
