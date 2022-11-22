/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    can.c
 * @brief   This file provides code for the configuration
 *          of the CAN instances.
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
#include "can.h"

/* USER CODE BEGIN 0 */
#include <QUTMS_can.h>

message_queue_t CAN1_Rx;
message_queue_t CAN1_Tx;

uint32_t txMailbox_CAN1 = 0;
/* USER CODE END 0 */

CAN_HandleTypeDef hcan1;

/* CAN1 init function */
void MX_CAN1_Init(void) {

	/* USER CODE BEGIN CAN1_Init 0 */

	/* USER CODE END CAN1_Init 0 */

	/* USER CODE BEGIN CAN1_Init 1 */

	/* USER CODE END CAN1_Init 1 */
	hcan1.Instance = CAN1;
	hcan1.Init.Prescaler = 2;
	hcan1.Init.Mode = CAN_MODE_NORMAL;
	hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
	hcan1.Init.TimeSeg1 = CAN_BS1_13TQ;
	hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;
	hcan1.Init.TimeTriggeredMode = DISABLE;
	hcan1.Init.AutoBusOff = DISABLE;
	hcan1.Init.AutoWakeUp = DISABLE;
	hcan1.Init.AutoRetransmission = DISABLE;
	hcan1.Init.ReceiveFifoLocked = DISABLE;
	hcan1.Init.TransmitFifoPriority = DISABLE;
	if (HAL_CAN_Init(&hcan1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN CAN1_Init 2 */

	/* USER CODE END CAN1_Init 2 */

}

void HAL_CAN_MspInit(CAN_HandleTypeDef *canHandle) {

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	if (canHandle->Instance == CAN1) {
		/* USER CODE BEGIN CAN1_MspInit 0 */

		/* USER CODE END CAN1_MspInit 0 */
		/* CAN1 clock enable */
		__HAL_RCC_CAN1_CLK_ENABLE();

		__HAL_RCC_GPIOB_CLK_ENABLE();
		/**CAN1 GPIO Configuration
		 PB8     ------> CAN1_RX
		 PB9     ------> CAN1_TX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/* CAN1 interrupt Init */
		HAL_NVIC_SetPriority(CAN1_TX_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(CAN1_TX_IRQn);
		HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
		HAL_NVIC_SetPriority(CAN1_RX1_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(CAN1_RX1_IRQn);
		/* USER CODE BEGIN CAN1_MspInit 1 */

		/* USER CODE END CAN1_MspInit 1 */
	}
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef *canHandle) {

	if (canHandle->Instance == CAN1) {
		/* USER CODE BEGIN CAN1_MspDeInit 0 */

		/* USER CODE END CAN1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_CAN1_CLK_DISABLE();

		/**CAN1 GPIO Configuration
		 PB8     ------> CAN1_RX
		 PB9     ------> CAN1_TX
		 */
		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8 | GPIO_PIN_9);

		/* CAN1 interrupt Deinit */
		HAL_NVIC_DisableIRQ(CAN1_TX_IRQn);
		HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
		HAL_NVIC_DisableIRQ(CAN1_RX1_IRQn);
		/* USER CODE BEGIN CAN1_MspDeInit 1 */

		/* USER CODE END CAN1_MspDeInit 1 */
	}
}

/* USER CODE BEGIN 1 */
void CAN_setup(void) {
	queue_init(&CAN1_Rx, sizeof(CAN_MSG_Generic_t));
	queue_init(&CAN1_Tx, sizeof(CAN_MSG_Generic_t));

	if (HAL_CAN_Start(&hcan1) != HAL_OK) {
		Error_Handler();
	}

	CAN_FilterTypeDef GLVFilterConfig;

	GLVFilterConfig.FilterBank = 0;
	GLVFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	GLVFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	GLVFilterConfig.FilterIdHigh = 0x0000;
	GLVFilterConfig.FilterIdLow = 0x0001;
	GLVFilterConfig.FilterMaskIdHigh = 0x0000;
	GLVFilterConfig.FilterMaskIdLow = 0x0001;
	GLVFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	GLVFilterConfig.FilterActivation = ENABLE;

	if (HAL_CAN_ConfigFilter(&hcan1, &GLVFilterConfig) != HAL_OK) {
		Error_Handler();
	}

	// Activating CAN Interrupts
	if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO1_MSG_PENDING)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_TX_MAILBOX_EMPTY)
			!= HAL_OK) {
		Error_Handler();
	}
}

HAL_StatusTypeDef send_can_msg(CAN_HandleTypeDef *hcan,
		CAN_TxHeaderTypeDef *pHeader, uint8_t aData[]) {
	HAL_StatusTypeDef result;

	uint32_t *pTxMailbox = NULL;
	if (hcan == &hcan1) {
		pTxMailbox = &txMailbox_CAN1;
	}

	if (HAL_CAN_GetTxMailboxesFreeLevel(hcan) > 0) {
		result = HAL_CAN_AddTxMessage(hcan, pHeader, aData, pTxMailbox);
	} else {
		// unable to send, queue for later
		CAN_MSG_Generic_t msg;
		msg.ID = pHeader->IDE == CAN_ID_EXT ? pHeader->ExtId : pHeader->StdId;
		msg.ID_TYPE = pHeader->IDE == CAN_ID_EXT ? 1 : 0;
		msg.DLC = pHeader->DLC;
		for (int i = 0; i < msg.DLC; i++) {
			msg.data[i] = aData[i];
		}
		msg.hcan = hcan;

		if (hcan == &hcan1) {
			queue_add(&CAN1_Tx, &msg);
		}
	}

	return result;
}

void can_tx_interrupt(CAN_HandleTypeDef *hcan) {
	// refresh watchdog when tx occurs
	// TODO:

	//__disable_irq();
	CAN_MSG_Generic_t msg;
	uint32_t *pTxMailbox;

	if (hcan == &hcan1) {
		pTxMailbox = &txMailbox_CAN1;
		if (!queue_empty(&CAN1_Tx)) {
			// queue isnt empty, so try and send

			if (HAL_CAN_GetTxMailboxesFreeLevel(&hcan1) > 0) {
				// confirm free spot -> grab message off queue
				queue_next(&CAN1_Tx, &msg);
			} else {
				// no free space, do nothing
				return;
			}
		} else {
			// nothing in queue do nothing
			return;
		}
	}

	CAN_TxHeaderTypeDef header;
	header.ExtId = msg.ID;
	header.StdId = msg.ID;
	header.IDE = msg.ID_TYPE == 1 ? CAN_ID_EXT : CAN_ID_STD;
	header.RTR = CAN_RTR_DATA;
	header.DLC = msg.DLC;

	HAL_CAN_AddTxMessage(hcan, &header, msg.data, pTxMailbox);
	//__enable_irq();
}

void can_rx_interrupt(CAN_HandleTypeDef *hcan, int fifo) {
	__disable_irq();

	CAN_MSG_Generic_t msg;
	CAN_RxHeaderTypeDef header;

	while (HAL_CAN_GetRxFifoFillLevel(hcan, fifo) > 0) {
		if (HAL_CAN_GetRxMessage(hcan, fifo, &header, msg.data) != HAL_OK) {

		} else {
			msg.hcan = hcan;
			msg.ID = header.IDE == CAN_ID_EXT ? header.ExtId : header.StdId;
			msg.ID_TYPE = header.IDE == CAN_ID_EXT ? 1 : 0;
			msg.DLC = header.DLC;
			msg.timestamp = HAL_GetTick();

			queue_add(&CAN1_Rx, &msg);

		}
	}
	__enable_irq();
}

/* USER CODE END 1 */
