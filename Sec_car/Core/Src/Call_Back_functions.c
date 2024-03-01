/*
 * Call_Back_functions.c
 *
 *  Created on: Mar 1, 2024
 *      Author: dell
 */
#include "stm32f4xx_hal.h"
#include "Call_Back_functions.h"

extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart6;


extern uint8_t received_char;
uint32_t edges_counter = 0;

     /***************************************Interrupts_Call_Backs********************************************************/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM2 && (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1 || htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2))
	{
		edges_counter++;
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	/*BT interrupt*/
	if(huart->Instance==USART3)
	{
		/*Reactivating the interrupt*/
		HAL_UART_Receive_IT(&huart3, &received_char, 1);

		/*Give the semaphore*/

	}

}

/*********************************************Application_Hook*************************************************************/
void vApplicationIdleHook(void)
{
	/*The processer will go to sleep in the IDLE Task*/
	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);

}


