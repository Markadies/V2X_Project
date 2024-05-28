/*
 * Tasks.c
 *
 *  Created on: Feb 22, 2024
 *      Author: Gp team
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
#include "Build_msg.h"

extern uint8_t received_char;
extern uint8_t ESP_Recieved_Char;

uint8_t  Global_GPS_Speed_Completetion=0;

uint8_t  ESP_TX_Buffer_Status[4];
uint8_t  ESP_TX_Buffer_Periodic[27];
uint8_t  Global_LightStatus = LIGHT_OFF_STATUS;

uint16_t Global_Speed;
extern GPS_Data_t GPS_Data;


extern TaskHandle_t Handle_LCDBuzzer;
extern TaskHandle_t Handle_CarControl;
extern TaskHandle_t Handle_GPS;
extern TaskHandle_t Handle_ESP_Periodic;
extern TaskHandle_t Handle_ESP_Status;
extern TaskHandle_t Handle_LightSensor;

extern TimerHandle_t Handle_Timer_LightStop;;

extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart6;

void TASK_GPS        (void *pvParameters)
{
	uint8_t Decode_Error_Code;
	while(1)
	{
		/*Update the GPS Data*/
		Decode_Error_Code = GPS_uint8DecodeGGAData();
		if(Decode_Error_Code==Decode_Success)
		{
			/*Update the completetion flag to activate the sendESP_Periodic task*/
			if(Global_GPS_Speed_Completetion==Nothing_Completed)
			{
				/* Updating the variable to notify the speed algorithm that the gps has
				 * done decoding and it can puplish the periodic data to the WIFI module */
				Global_GPS_Speed_Completetion = Half_Completed_GPS;

			}
			else if(Global_GPS_Speed_Completetion==Half_Completed_Speed)
			{
				/* Reseting the variable for the next update cycle */
				Global_GPS_Speed_Completetion = Nothing_Completed;


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

				/*Notify the sendEspStatus task*/
				xTaskNotify(Handle_ESP_Status,Notify_TASK_ESPStatus_HardBreaking,eSetValueWithOverwrite);

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
				Light_On();

				/* Updating the car light source status*/
				Global_LightStatus = LIGHT_ON_STATUS;

				break;
			case 'f':
				Light_OFF();

				/* Updating the car light source status*/
				Global_LightStatus = LIGHT_OFF_STATUS;

				/* Stopping the unnecessary warning */
				Buzzer_voidStop();
				LCD_voidClearDisplay();

				/* Stop the unnecessary timer because the user already reacted */
				xTimerStop(Handle_Timer_LightStop,1000);

				break;

			}
		}
	}
}
void TASK_ESPSend_PeriodicData (void *pvParameters)
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
			HAL_UART_Transmit(&huart5,ESP_TX_Buffer_Periodic, sizeof(ESP_TX_Buffer_Periodic), 1500);
		}
		else
		{


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

			// Read data from Light_Sensor_Task
			switch (Local_Notification_Value)
			{
			case Notify_TASK_ESPStatus_HardBreaking:

				/*Updating the TX buffer with the problem of the hard breaking*/
				ESP_TX_Buffer_Status[1] = 'B';

				/*Transmitting the Car status to the Esp */
				HAL_UART_Transmit(&huart5,ESP_TX_Buffer_Status, sizeof(ESP_TX_Buffer_Status), 1500);

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
			case Notify_TASK_ESPRecieve_Light:

				/*Stopping preemption of other tasks in this critical section*/
				vTaskSuspendAll();

				/*Activating the warning message and the buzzer to alert the driver*/
				Buzzer_voidHighSound();
				LCD_HighLightIntensity_Warning();


				/*Start the timer to autonomously turn off the light source if the user didn't
				 * & to stop the buzzer and clear LCD after period of specified time */
				xTimerStart(Handle_Timer_LightStop,1000);

				/*Resuming the tasks*/
				xTaskResumeAll();



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





