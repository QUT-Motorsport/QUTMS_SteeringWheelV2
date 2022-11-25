/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "can.h"
#include "spi.h"
#include "gpio.h"
#include "btn.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "MS_Screen.h"
#include "heartbeat.h"
#include <queue.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
//extern UBYTE *Canvas;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
struct main_screen_text main_txt;
dispSelector_t disp_select1;
dispSelector_t disp_select2;
dispSelector_t disp_select3;
uint8_t SCR_STATE = STARTUP_SCREEN;
uint8_t DISP_STATE = MAIN_SCREEN;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint32_t ADC1_value = 0;
	bool btn_press = false;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_CAN1_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */

	// Initialise the screen
	if (Screen_Init() != 0) {
		HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
	}
	/* you have to edit the startup_stm32fxxx.s file and set a big enough heap size */

	UBYTE *DynamicScreen = Canvas_Init();
	UBYTE *Canvas_STARTUP = Canvas_Init();
	Screen_Static_Init(Canvas_STARTUP);
	Screen_Startup(Canvas_STARTUP);
	HAL_Delay(3000);
	free(Canvas_STARTUP);
	SCR_STATE = MAIN_SCREEN;

	init_Main_text();
	Screen_Dynamic_Init(DynamicScreen);
	//int8_t VCU_STATES[5] = { 0, 2, 3, 4, 5 };

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

	CAN_setup();
	CAN_TxHeaderTypeDef header;
	//HAL_CAN_Start(&hcan1);
	//uint32_t txMailbox = 0;


	while (1) {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		// READ POT VALUES
		 HAL_ADC_Start(&hadc1);
		 ADC1_value = Get_ADC_Value(&hadc1);

		 // CHECK BTN PRESS
		 btn_press = btn_pressed();

		 // READ CAN RX
		CAN_MSG_Generic_t msg;

		while (queue_next(&CAN1_Rx, &msg)) {
			HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
			// check for heartbeat
			if (check_heartbeat_msg(&msg)) {
			}
		}

		// UPDATE SCREEN PRINT
		Screen_Update(ADC1_value, btn_press);

		//HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);

		//Draw_BoardStates(DynamicScreen);
		switch(DISP_STATE){
		case MAIN_SCREEN:
			Screen_Display(DynamicScreen);
			break;
		case OTHER_SCREEN:
			Special_Display(DynamicScreen);
			break;
		}


	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
