/*
 * Tasks.c
 *
 *  Created on: Feb 22, 2024
 *      Author: GP team
 */

#include "main.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

#include "Tasks.h"
#include "Car_Control.h"
#include "Help_Functions.h"
#include "Buzzer.h"
#include "LCD_I2C.h"
#include "GPS.h"
#include "bluetooth.h"
#include "Car_Control.h"
#include "Build_msg.h"
#include "LightSensor.h"

#include <stdint.h>

extern uint8_t  received_char;
extern uint8_t  ESP_Recieved_Char;

uint8_t  Global_GPS_Speed_Completetion=0;
uint8_t  ESP_TX_Buffer_Status[4];
uint8_t  ESP_TX_Buffer_Periodic[27];

uint16_t Global_Speed;
extern GPS_Data_t GPS_Data;

extern TaskHandle_t Handle_LCDBuzzer;
extern TaskHandle_t Handle_CarControl;
extern TaskHandle_t Handle_GPS;
extern TaskHandle_t Handle_ESP_Periodic;
extern TaskHandle_t Handle_ESP_Status;
extern TaskHandle_t Handle_LightSensor;

extern TimerHandle_t Handle_Timer_RecieveESP;

extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart6;

void TASK_GPS(void *pvParameters)
{
	uint8_t Decode_Error_Code;
	while(1)
	{
		/*Update the GPS Data*/
		Decode_Error_Code = GPS_uint8DecodeGGAData();
		if(Decode_Error_Code==Decode_Success)
		{
			/*Update the completion flag to activate the sendESP_Periodic task*/
			if(Global_GPS_Speed_Completetion==Nothing_Completed)
			{
				Global_GPS_Speed_Completetion=Half_Completed_GPS;

			}
			else if(Global_GPS_Speed_Completetion==Half_Completed_Speed)
			{

				Global_GPS_Speed_Completetion=Nothing_Completed;


				/*Activate the ESPTask*/
				xTaskNotify(Handle_ESP_Periodic,0,eNoAction);
			}
			/*Stopping the task for 400ms to free the processor*/
			vTaskDelay(pdMS_TO_TICKS(400));
		}
		else if(Decode_Error_Code==Decode_Failed)
		{


		}



	}




}


void TASK_CarControl(void *pvParameters)
{
	uint32_t Local_Notification_Value;
	BaseType_t Notify_Status;
	for (;;) {

		/*Waiting to be notified from the BT ISR */
		Notify_Status = xTaskNotifyWait((uint32_t)NULL,(uint32_t)NULL,&Local_Notification_Value,portMAX_DELAY);

		if(Notify_Status == pdTRUE)
		{
		// Read data from UART
		switch (received_char)
		 {
		case '1':
			Car_Rotate_LeftForward();
			break;
		case '2':
			Car_Rotate_Left();
			break;
		case '4':
			Car_Move_Forward_High_Speed();
			break;
		case '5':
			Car_Stop();
			break;
		case '6':
			Car_Move_Backward();
			break;
		case '7':
			Car_Rotate_RightForward();
			break;
		case '8':
			Car_Rotate_Right();
			break;
		case 'l':
			// light on
			break;
		case 'f':
			// light off
			break;

		    }
		}
	}
}

void TASK_LightSensor(void *pvParameters)
{
	uint16_t Local_uint16LightSensor_Flux=0;

	while(1)
	{
		/*Read the intensity*/
		LightSensor_uint8ReadIntensity(&Local_uint16LightSensor_Flux);

		if(Local_uint16LightSensor_Flux>MAX_LightIntensity)
		{
			//Notify the ESPSendStatus task with problem in light
			xTaskNotify(Handle_ESP_Status,Notify_TASK_ESPSend_HighLight,eSetValueWithOverwrite);

			/*Delaying the task to free the processor*/
			vTaskDelay(pdMS_TO_TICKS(800));
		}
		else
		{
			ESP_TX_Buffer_Status[1]='0';
			/*Delaying the task to free the processor*/
			vTaskDelay(pdMS_TO_TICKS(200));
		}
	}
}

void TASK_ESPSend_PeriodicData(void *pvParameters)
{
	BaseType_t Notify_Status;
	uint32_t Local_uint32NotificationValue;
	while(1)
	{

		/*Reading done from GPS and Speed sensor*/
		Notify_Status = xTaskNotifyWait((uint32_t)NULL,0xFFFFFFFF,&Local_uint32NotificationValue, portMAX_DELAY);
		if(Notify_Status == pdTRUE)
		{
			/*Updating the transmission buffer*/
			GPSSPEED_voidBuildMsg(ESP_TX_Buffer_Periodic, GPS_Data.Longitude,GPS_Data.Latitude , Global_Speed);

			/*Transmitting the GPS, SPEED elements */
			HAL_UART_Transmit(&huart4,ESP_TX_Buffer_Periodic, sizeof(ESP_TX_Buffer_Periodic), 1500);
		}
		else
		{

			/*Do nothing*/
		}
	}


}
void TASK_ESP_SendStatus (void *pvParameters)
{
	uint32_t Local_Notification_Value;

	BaseType_t Notify_Status;
	ESP_TX_Buffer_Status[0] = '%';
	ESP_TX_Buffer_Status[2] = '^';
	ESP_TX_Buffer_Status[3] = '!';
	while(1)
	{
		/*Waiting to be notified from the TASK_LightSensor */
		Notify_Status = xTaskNotifyWait((uint32_t)NULL,0xffffffff,&Local_Notification_Value,portMAX_DELAY);
		if(Notify_Status == pdTRUE)
		{

			/* Read data from Light_Sensor_Task */
			switch (Local_Notification_Value)
			{
			case Notify_TASK_ESPSend_HighLight:

				/*Updating the TX buffer with the problem of the high Light intensity*/
				ESP_TX_Buffer_Status[1] = 'L';

				/*Transmitting the Car status to the Esp */
				HAL_UART_Transmit(&huart4,ESP_TX_Buffer_Status, sizeof(ESP_TX_Buffer_Status), 1500);
				break;
			}
		}
	}
}

void TASK_ESP_Receive (void *pvParameters)
{
	BaseType_t Notify_Status;
	uint32_t Local_uint32NotificationValue;
	while(1)
	{
		Notify_Status = xTaskNotifyWait((uint32_t)NULL,(uint32_t)NULL,&Local_uint32NotificationValue, portMAX_DELAY);
		if(Notify_Status == pdTRUE)
		{
			switch(ESP_Recieved_Char)
			{
			case Notify_TASK_ESPRecieve_Break:

				/*Stopping preemption of other tasks in this critical section*/
				vTaskSuspendAll();

				/*Taking the action of breaking*/
				Car_Stop();

				/*Presenting the warning to the driver in sort of buzzer sound & display warning*/
				Buzzer_voidHighSound();
				LCD_AvoidHardBraking();

				/*Resuming the tasks*/
				xTaskResumeAll();

				/*Start the timer to stop the buzzer and clear LCD after period of specified time*/
				xTimerStart(Handle_Timer_RecieveESP,1000);


				break;

			default:
				break;

			}


		}
		else
		{
			/*Do nothing*/
		}


	}


}

