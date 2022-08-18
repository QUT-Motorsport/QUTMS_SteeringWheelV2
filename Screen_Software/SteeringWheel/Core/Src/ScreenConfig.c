#include "ScreenConfig.h"
#include "stm32f2xx_hal_spi.h"

SPI_HandleTypeDef hspi1;

int Init_Spi_Handle()
{
	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
	hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
	hspi1.Init.NSS = SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial = 10;
	return (HAL_SPI_Init(&hspi1) != HAL_OK);
}

void Screen_WriteByte(UBYTE value)
{
	uint8_t data = value;
    HAL_SPI_Transmit(&hspi1, &data, 1, 1000);
}

void Screen_Digital_Write(uint16_t pin, GPIO_TypeDef* port, uint8_t value);


uint8_t Screen_Digital_Read(uint16_t pin, GPIO_TypeDef* port);

void Screen_Init(void);

void Screen_Exit(void);
