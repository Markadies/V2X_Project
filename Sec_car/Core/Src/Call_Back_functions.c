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

#include "Tasks.h"
#include "Call_Back_functions.h"
#include "Buzzer.h"
#include "LCD_I2C.h"

/********************************Handles_Definition**************************************/
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart6;

extern TaskHandle_t Handle_LCDBuzzer;
extern TaskHandle_t Handle_CarControl;
extern TaskHandle_t Handle_GPS;
extern TaskHandle_t Handle_ESP_Periodic;
extern TaskHandle_t Handle_ESP_Status;
extern TaskHandle_t Handle_ESP_Receive;

/********************************Global_Variables_Definition******************************/
extern uint8_t received_char;
extern uint8_t ESP_Recieved_Char;
extern uint8_t  Global_LightStatus;
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

		/*Give the Notification to the CarControl task*/
		xTaskNotifyFromISR(Handle_CarControl,NULL,eNoAction,NULL);

	}

	/*ESP receive*/
	else if(huart->Instance==UART5)
	{
		/*Reactivating the interrupt*/
		HAL_UART_Receive_IT(&huart5,&ESP_Recieved_Char,2);

		/*Give the Notification to the Receive esp task*/
		xTaskNotifyFromISR(Handle_ESP_Receive,NULL,eNoAction,NULL);

	}

}

/*********************************************Application_Hook*************************************************************/
void vApplicationIdleHook(void)
{
	/*The processor will go to sleep in the IDLE Task*/
	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);

}

/*********************************************SW_Timers_CallBacks*********************************************************/
void CallBack_TimerLightStop(TimerHandle_t xTimer)
{
	if(Global_LightStatus == LIGHT_ON_STATUS)
	{
		/* If the still the user didn't turn off the light source it will turn off automatically */

		/* Taking the action of Turning the light beam off */
		Light_OFF();

		/* Stopping the buzzer */
		Buzzer_voidStop();

		/* Clearing the LCD */
		LCD_voidClearDisplay();



	}
	else
	{
		/* If the script reaches here means that the light source is not from this car and it reached here by mistake
		 * because if the light intensity is already off so the timer should be stopped */

		/* Stopping the buzzer */
		Buzzer_voidStop();

		/* Clearing the LCD */
		LCD_voidClearDisplay();

	}



}









