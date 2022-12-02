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
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "MS_Screen.h"
#include "heartbeat.h"
#include <queue.h>
#include <CAN_SW.h>
#include "btn.h"

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

// screen variables
struct main_screen_text main_txt;
dispSelector_t disp_select1;
volatile PAINT_TIME sPaint_time;
uint8_t SCR_STATE = STARTUP_SCREEN;
uint8_t DISP_STATE = MAIN_SCREEN;
UBYTE DynamicScreen[33600];
UBYTE Canvas_STARTUP[33600];

// ADC
uint32_t ADC1_value = 0;
uint32_t ADC1_buffer;

// buttons
volatile bool btn_pressed[4] = { false, false, false, false };

// initiating heartbeat
SW_HeartbeatState_t SW_hbState;
extern DVL_HeartbeatState_t DVL_hbState;
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
int main(void) {
	/* USER CODE BEGIN 1 */
	sPaint_time.Hour = 0;
	sPaint_time.Min = 0;
	sPaint_time.Sec = 0;
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
	MX_TIM9_Init();
	MX_TIM3_Init();
	MX_TIM12_Init();
	/* USER CODE BEGIN 2 */

	SW_hbState.flags.rawMem = 0;
	SW_hbState.missionID = MISSION_NONE;
	SW_hbState.stateID = SW_STATE_START;

	// Initialise the screen
	if (Screen_Init() != 0) {
		HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
	}
	/* you have to edit the startup_stm32fxxx.s file and set a big enough heap size */

	Screen_Static_Init(Canvas_STARTUP);
	Screen_Startup(Canvas_STARTUP);
	HAL_Delay(3000);
	SCR_STATE = MAIN_SCREEN;

	init_Main_text();
	Screen_Dynamic_Init(DynamicScreen);

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */

	CAN_setup();
	HAL_CAN_Start(&hcan1);

	HAL_TIM_Base_Start_IT(&htim9);
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_Base_Start_IT(&htim12);

	SW_hbState.stateID = SW_STATE_READY;

	while (1) {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */

		// process incoming can message
		CAN_MSG_Generic_t msg;

		while (queue_next(&CAN1_Rx, &msg)) {
			HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
			// check for heartbeat
			if (check_heartbeat_msg(&msg)) {
				HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
			}
		}

		// SW state machine

		switch (SW_hbState.stateID) {

		case SW_STATE_READY:
			//HAL_Delay(100);
			//Screen_Waiting_Display(DynamicScreen);
			while (DVL_hbState.stateID != DVL_STATE_SELECT_MISSION) {
				HAL_Delay(100);
				//Special_Display(DynamicScreen);
				Draw_BoardStates(DynamicScreen);
				HAL_Delay(10);
				while (queue_next(&CAN1_Rx, &msg)) {
					HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
					// check for heartbeat
					if (check_heartbeat_msg(&msg)) {
						HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
					}
				}
			}

			SW_hbState.stateID = SW_STATE_SELECT_MISSION;
			break;

		case SW_STATE_SELECT_MISSION:
			// UPDATE SCREEN PRINT
			Screen_Update(ADC1_value);

			//Draw_BoardStates(DynamicScreen);
			switch (DISP_STATE) {
			case MAIN_SCREEN:
				HAL_Delay(100);
				Screen_Display(DynamicScreen);
				HAL_Delay(10);
				break;
			case VCU_STATE_SCREEN:
				HAL_Delay(100);
				Draw_BoardStates(DynamicScreen);
				HAL_Delay(10);
				break;
			case OTHER_SCREEN:
				HAL_Delay(50);
				Special_Display(DynamicScreen);
				DISP_STATE = MAIN_SCREEN;
				HAL_Delay(10);
				break;
			}

			break;

		case SW_STATE_MISSION_ACK:
			HAL_Delay(100);
			while (DVL_hbState.stateID != DVL_STATE_CHECK_EBS) {
				while (queue_next(&CAN1_Rx, &msg)) {
					HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
					// check for heartbeat
					if (check_heartbeat_msg(&msg)) {
						HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
					}
				}
			}
			SW_hbState.stateID = SW_STATE_IN_MISSION;
			break;

		case SW_STATE_IN_MISSION:
			HAL_Delay(100);
			while (DVL_hbState.stateID != DVL_STATE_SELECT_MISSION) {
				while (queue_next(&CAN1_Rx, &msg)) {
					HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
					// check for heartbeat
					if (check_heartbeat_msg(&msg)) {
						HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
					}
				}
			}

			SW_hbState.flags._SW_Flags.MISSION_SELECTED = 0;
			SW_hbState.stateID = SW_STATE_SELECT_MISSION;
			SW_hbState.missionID = MISSION_NONE;
			clear_main();
			break;
		}
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 10;
	RCC_OscInitStruct.PLL.PLLN = 192;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV6;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
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
