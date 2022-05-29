#include "ScreenConfig.h"
#include "stm32f2xx_hal_spi.h"

extern SPI_HandleTypeDef hspi1;

void Screen_WriteByte(UBYTE value)
{
    HAL_SPI_Transmit(&hspi1, &value, 1, 1000);
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
