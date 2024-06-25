/*
 * Call_Back_functions.c
 *
 *  Created on: Mar 1, 2024
 *      Author: dell
 */
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

#include "Call_Back_functions.h"
#include "Tasks.h"
#include "Buzzer.h"
#include "LCD_I2C.h"

extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart6;

extern TaskHandle_t Handle_LCDBuzzer;
extern TaskHandle_t Handle_CarControl;
extern TaskHandle_t Handle_GPS;
extern TaskHandle_t Handle_ESP_Periodic;
extern TaskHandle_t Handle_ESP_Status;
extern TaskHandle_t Handle_LightSensor;
extern TaskHandle_t Handle_ESP_Receive;
extern TaskHandle_t Handle_Rasp_ReceiveData;
extern TaskHandle_t Handle_Rasp_SendData;

/********************************Global_Variables_Definition******************************/
extern uint8_t  received_char;
extern uint8_t  ESP_Recieved_Char;
extern uint16_t Rasp_Recieved_Char;

extern uint8_t  Global_Break_Warning_On_Status;
extern uint8_t  Global_Breaking_Status;
extern uint8_t  Global_Overtake_Warning_Status;

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
	/* ESP Interrupt */
	if(huart->Instance==UART4)
	{
		/* Reactivating the interrupt */
		HAL_UART_Receive_IT(&huart4,&ESP_Recieved_Char,2);

		if((ESP_Recieved_Char == Notify_TASK_RaspSend_Overtake_Clear) || (ESP_Recieved_Char == Notify_TASK_RaspSend_Overtake_NotClear))
		{
			/* Give the Notification to the Raspberry send task is it Clear or Not CLear to overtake */
			xTaskNotifyFromISR(Handle_Rasp_SendData,ESP_Recieved_Char,eSetValueWithOverwrite,NULL);
		}
		else
		{

			/* Give the Notification to the Receive ESP task */
			xTaskNotifyFromISR(Handle_ESP_Receive,NULL,eNoAction,NULL);

		}
	}
	/* Blue tooth interrupt */
	else if(huart->Instance==USART3)
	{
		/* Reactivating the interrupt */
		HAL_UART_Receive_IT(&huart3, &received_char, 1);

		/* Give the Notification to the CarControl task */
		xTaskNotifyFromISR(Handle_CarControl,NULL,eNoAction,NULL);

	}
	/* Raspberry pi interrupt */
	else if (huart->Instance==USART6)
	{
		/* Reactivating the interrupt */
		HAL_UART_Receive_IT(&huart6,&Rasp_Recieved_Char,1);

		/* Give the Notification to the Receive Raspberry task */
		xTaskNotifyFromISR(Handle_Rasp_ReceiveData,NULL,eNoAction,NULL);
	}

}

/*********************************************Application_Hook*************************************************************/
void vApplicationIdleHook(void)
{
	/* The processor will go to sleep in the IDLE Task */
	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);

}

/*********************************************SW_Timers_CallBacks*********************************************************/
void CallBack_TimerLCDBuzzer(TimerHandle_t xTimer)
{
	/* When the LCDBuzzer task starts the timer it should turn off the buzzer and clear the LCD */

	/* Stopping the buzzer */
	Buzzer_voidStop();

	/* Clearing the LCD */
	LCD_voidClearDisplay();

	/* Reseting the global warning status */
	Global_Break_Warning_On_Status = Warning_OFF;
	Global_Overtake_Warning_Status = Warning_OFF;
}

void CallBack_TimerBreakingStatus(TimerHandle_t xTimer){Global_Breaking_Status = Breaking_OFF;}

