/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "can.h"
#include "dma.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <QUTMS_can.h>
#include <CAN_SW.h>
#include <CAN_VCU.h>
#include <obj_dic.h>
#include <Timer.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define MAX_REGEN_CURRENT 120
#define MAX_REGEN_DEADZONE 100

void update_buttons();

bool is_btn_pressed(uint8_t idx);
void button_one_function();
void button_two_function();
void button_three_function();
void button_four_function();

#define DEBOUNCE_MASK 0b00111111
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint16_t dma_raw[3];
uint16_t pot_value[3];
int pot_result[3];
uint8_t button_debounce_count[4];
uint8_t button_current_state[4];
uint8_t button_prev_state[4];
char buff[256];

ms_timer_t timer_heartbeat;
SW_HeartbeatState_t SW_hbState;

void heartbeat_timer_cb(void *args);
bool is_btn_pressed(uint8_t idx);
void button_one_function();
void button_two_function();
void button_three_function();
void button_four_function();

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
	if (hadc == &hadc1) {
		memcpy(pot_value, dma_raw, sizeof(uint16_t) * 3);
	}
}

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

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
	MX_DMA_Init();
	MX_ADC1_Init();
	MX_CAN1_Init();
	MX_USART3_UART_Init();
	/* USER CODE BEGIN 2 */

	SW_hbState.stateID = SW_STATE_START;

	setup_CAN();

	if (HAL_ADC_Start_DMA(&hadc1, (uint32_t*) dma_raw, 3) != HAL_OK) {
		Error_Handler();
	}

	timer_heartbeat = timer_init(100, true, heartbeat_timer_cb);
	timer_start(&timer_heartbeat);

	SW_hbState.stateID = SW_STATE_READY;


	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	/* enum{
	 DISPLAY_POTVALUES,
	 NOTHING,
	 TOGGLE_FAN,
	 HORN

	 };*/

	for (int i = 0; i < 4; i++) {
		button_prev_state[i] = 1;
	}

	while (1) {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */

		// update button values w/ debouncing
		update_buttons();

		//int numchars = sprintf(buff, "B1: %i\r\n", state_b1);
		// int numchars = sprintf(buff, "B1: %i B2: %i B3: %i B4: %i\r\n", button_current_state[0], button_current_state[1], button_current_state[2], button_current_state[3]);
		// HAL_UART_Transmit(&huart3,
		//		  buff, numchars, 2000);

		// for(int i = 0; i < 3; i++)
		//
		pot_result[0] = pot_value[0] / 4095.0f * MAX_REGEN_CURRENT;
		pot_result[1] = pot_value[1] / 4095.0f * MAX_REGEN_DEADZONE;

		//potValues

		//buttton 3 fan on and off
		//button 4 is horn
		if (is_btn_pressed(0)) {
			button_one_function();
		}
		if (is_btn_pressed(1)) {
			button_two_function();
		}
		if (is_btn_pressed(2)) {
			button_three_function();
		}
		if (button_current_state[3] == 0) {
			button_four_function();
		}

		for (int i = 0; i < 4; i++) {
			button_prev_state[i] = button_current_state[i];
		}

		//HAL_UART_Transmit(&huart3, buff, pot_value, 2000);

		HAL_Delay(1);
	}
}

/* USER CODE END 3 */

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
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 10;
	RCC_OscInitStruct.PLL.PLLN = 200;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV4;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

void update_buttons() {
	for (int i = 0; i < 4; i++) {
		button_debounce_count[i] = button_debounce_count[i] << 1;
		button_debounce_count[i] &= DEBOUNCE_MASK;
	}

	button_debounce_count[0] |= HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin);
	button_debounce_count[1] |= HAL_GPIO_ReadPin(B2_GPIO_Port, B2_Pin);
	button_debounce_count[2] |= HAL_GPIO_ReadPin(B3_GPIO_Port, B3_Pin);
	button_debounce_count[3] |= HAL_GPIO_ReadPin(B4_GPIO_Port, B4_Pin);

	for (int i = 0; i < 4; i++) {
		if (button_debounce_count[i] == DEBOUNCE_MASK) {
			button_current_state[i] = 1;
		} else if (button_debounce_count[i] == 0) {
			button_current_state[i] = 0;
		}
	}
}

void heartbeat_timer_cb(void *args) {

	SW_Heartbeat_t msg = Compose_SW_Heartbeat(&SW_hbState);

	CAN_TxHeaderTypeDef header = { .ExtId = msg.id, .IDE =
		CAN_ID_EXT, .RTR = CAN_RTR_DATA, .DLC = sizeof(msg.data),
				.TransmitGlobalTime = DISABLE };

		HAL_CAN_AddTxMessage(&hcan1, &header, msg.data, &txMailbox_CAN1);
}


bool is_btn_pressed(uint8_t idx) {
	if (button_current_state[idx] == 0 && button_prev_state[idx] == 1) {
		return true;
	}
	return false;
}

void button_one_function() {
	uint16_t max_regen = pot_result[0];

	uint8_t data[8];
	OD_generateCAN(OD_MSG_SET, VCU_OD_ID_CTRL_REGEN_MAX_CURRENT, &max_regen,
			OD_TYPE_UINT16, data);

	VCU_OBJ_DICT_t msg = Compose_VCU_OBJ_DICT(VCU_ID_CTRL, data);

	CAN_TxHeaderTypeDef header = { .ExtId = msg.id, .IDE =
	CAN_ID_EXT, .RTR = CAN_RTR_DATA, .DLC = sizeof(msg.data),
			.TransmitGlobalTime = DISABLE };

	HAL_CAN_AddTxMessage(&hcan1, &header, msg.data, &txMailbox_CAN1);

	//int value_results = sprintf(buff, "value 1: %i value 2: %i value 3: %i\r\n",
	//		pot_result[0], pot_result[1], pot_result[2]);
	//HAL_UART_Transmit(&huart3, buff, value_results, 2000);
}

void button_two_function() {
	//int numchars = sprintf(buff, "This does nothing at the moment\r\n");
	//HAL_UART_Transmit(&huart3, buff, numchars, 2000);
}

void button_three_function() {
	SW_hbState.flags.FAN_ENABLE = !SW_hbState.flags.FAN_ENABLE;

	//int fan_toggle = sprintf(buff, "Fan button Pressed\r\n");
	//HAL_UART_Transmit(&huart3, buff, fan_toggle, 2000);
}

void button_four_function() {
	//int car_horn = sprintf(buff, "Beep Beep! get out of the way\r\n");
	//HAL_UART_Transmit(&huart3, buff, car_horn, 2000);

	SW_ActivateHorn_t msg = Compose_SW_ActivateHorn();
	CAN_TxHeaderTypeDef header = { .ExtId = msg.id, .IDE =
	CAN_ID_EXT, .RTR = CAN_RTR_DATA, .DLC = 0, .TransmitGlobalTime = DISABLE };

	HAL_CAN_AddTxMessage(&hcan1, &header, NULL, &txMailbox_CAN1);
}

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

