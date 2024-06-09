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
#include "Ultrasonic.h"

#include <stdint.h>

extern uint8_t  received_char;
extern uint8_t  ESP_Recieved_Char;
extern uint8_t Rasp_Recieved_Char;

uint8_t  Global_GPS_Speed_Completetion=0;

uint8_t  ESP_TX_Buffer_Status[4];
uint8_t  ESP_TX_Buffer_Periodic[27];

uint8_t  Global_Breaking_Status = Breaking_OFF;
uint8_t  Global_Break_Warning_On_Status = 0;
uint16_t Global_Speed;

extern GPS_Data_t GPS_Data;

extern TaskHandle_t Handle_LCDBuzzer;
extern TaskHandle_t Handle_CarControl;
extern TaskHandle_t Handle_GPS;
extern TaskHandle_t Handle_ESP_Periodic;
extern TaskHandle_t Handle_ESP_Status;
extern TaskHandle_t Handle_LightSensor;
extern TaskHandle_t Handle_Distance_AboveThreshold;
extern TaskHandle_t Handle_Rasp_ReceiveData;
extern TaskHandle_t Handle_Rasp_SendData;

extern TimerHandle_t Handle_Timer_RecieveESP;
extern TimerHandle_t Handle_Timer_Breaking_Status;

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
				/* Updating the variable to notify the speed algorithm that the gps has
				 * done decoding and it can puplish the periodic data to the WIFI module */
				Global_GPS_Speed_Completetion=Half_Completed_GPS;

			}
			else if(Global_GPS_Speed_Completetion==Half_Completed_Speed)
			{
				/* Reseting the variable for the next update cycle */
				Global_GPS_Speed_Completetion=Nothing_Completed;


				/*Activate the ESPTask*/
				xTaskNotify(Handle_ESP_Periodic,0,eNoAction);
			}
			/*Stopping the task for 1 second to free the processor*/
			vTaskDelay(pdMS_TO_TICKS(1000));
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

				/* Updating the breaking variable to eliminate unnecessary autonomous breaking events could occur*/
				Global_Breaking_Status =Breaking_ON;

				/* This timer will reset the above variable every 1.5second to allow autonomous breaking events */
				xTimerStart(Handle_Timer_Breaking_Status,1000);

				/* Checking if a braking warning is already on to turn it off */
				if(Global_Break_Warning_On_Status == Warning_ON)
				{
					/*Stopping the buzzer*/
					Buzzer_voidStop();

					/*Clearing the LCD*/
					LCD_voidClearDisplay();

					/* Resetting the warning status */
					Global_Break_Warning_On_Status = Warning_OFF;
				}
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
			vTaskDelay(pdMS_TO_TICKS(3300));
		}
		else
		{

			/*Delaying the task to free the processor*/
			vTaskDelay(pdMS_TO_TICKS(300));
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

			case Notify_TASK_ESPSend_RequestOvertake:

				/* Updating the TX buffer with the avoid Overtaking */
				ESP_TX_Buffer_Status[1] = 'K';

				/*Transmitting the Car status to the Esp */
				HAL_UART_Transmit(&huart4,ESP_TX_Buffer_Status, sizeof(ESP_TX_Buffer_Status), 1500);
				break;


				//////////////////////////////
			}
		}
	}
}

void TASK_ESP_Receive (void *pvParameters)
{
	BaseType_t Notify_Status;
	uint32_t Local_uint32NotificationValue;
	uint16_t Local_uint16Distance = 0;
	uint8_t Local_Ultrasonic_ErrorCode = 0;
	while(1)
	{
		Notify_Status = xTaskNotifyWait((uint32_t)NULL,(uint32_t)NULL,&Local_uint32NotificationValue, portMAX_DELAY);
		if(Notify_Status == pdTRUE)
		{
			switch(ESP_Recieved_Char)
			{
			case Notify_TASK_ESPRecieve_Break:

				/* Stopping preemption of other tasks in this critical section */
				vTaskSuspendAll();

				/* Calculating the car distance */
				Local_Ultrasonic_ErrorCode = Ultrasonic_uint8Get_Distance_In_Cm(&Local_uint16Distance);

				/* Checking the Car Infront distance value & the error code to take the appropriate action */
				if((Local_Ultrasonic_ErrorCode == Calculation_Success) && (Local_uint16Distance <= THRESHOLD_DISTANCE_INFRONT_IN_CENTIMETER))
				{
					/* Taking the action of breaking */
					Car_Stop();

					/* Presenting the warning to the driver in sort of buzzer sound & display warning */
					Buzzer_voidHighSound();
					LCD_AvoidHardBraking();

					/* Updating Warning Status, so if the user uses brakes the visual and audio warning stops */
					Global_Break_Warning_On_Status = Warning_ON;

					/* Resuming the tasks */
					xTaskResumeAll();

					/* Start the timer to stop the buzzer and clear LCD after period of specified time */
					xTimerStart(Handle_Timer_RecieveESP,1000);
				}
				else if((Local_Ultrasonic_ErrorCode == Calculation_Success) && (Local_uint16Distance > THRESHOLD_DISTANCE_INFRONT_IN_CENTIMETER))
				{
					/* No Breaking */

					/* Presenting the warning to the driver in sort of buzzer sound & display warning */
					Buzzer_voidHighSound();
					LCD_AvoidHardBraking();

					/* Updating Warning Status, so if the user uses brakes the visual and audio warning stops */
					Global_Break_Warning_On_Status = Warning_ON;

					/* Resuming the tasks */
					xTaskResumeAll();

					/* Start the timer to stop the buzzer and clear LCD after period of specified time */
					xTimerStart(Handle_Timer_RecieveESP,1000);

					/* Notify a task to handle if the user didnt stop after the warning till the distance reaches the threshold*/
					xTaskNotify(Handle_Distance_AboveThreshold,NULL,eNoAction);

				}
				else if((Local_Ultrasonic_ErrorCode == Calculation_Failed) || (Local_Ultrasonic_ErrorCode == TIMEOUT_ECHO_OCCURED) )
				{
					/* Calculation failed means that most probably the front car is farther than 4 meters so just a visual alert
					 * and a weak audio alert is enough */
					LCD_Normal_Alert();
					Buzzer_voidMidSound();

					/* Start the timer to stop the buzzer and clear LCD after period of specified time */
					xTimerStart(Handle_Timer_RecieveESP,1000);

					/* Resuming the tasks */
					xTaskResumeAll();
				}
				else
				{
					/* Do Nothing */
				}



				break;

			default:
				break;

			}


		}
		else
		{
			/* Do nothing */
		}


	}


}

void TASK_Distance_AboveThreshold(void *pvParameters)
{
	BaseType_t Notify_Status;
	uint32_t Local_uint32NotificationValue;
	TickType_t Local_TickTypeTicks_Now = 0;
	uint16_t Local_uint16Distance = 0;
	uint8_t  Local_Ultrasonic_Error_Code = 0;
	while(1)
	{
		Notify_Status = xTaskNotifyWait((uint32_t)NULL,(uint32_t)NULL,&Local_uint32NotificationValue, portMAX_DELAY);
		if( (Notify_Status == pdTRUE) && (Global_Breaking_Status == Breaking_OFF))
		{
			Local_TickTypeTicks_Now = xTaskGetTickCount();
			while(((xTaskGetTickCount() - Local_TickTypeTicks_Now) < 1700) && (Global_Breaking_Status == Breaking_OFF))
			{
				Local_Ultrasonic_Error_Code = Ultrasonic_uint8Get_Distance_In_Cm(&Local_uint16Distance);

				if((Local_Ultrasonic_Error_Code == Calculation_Success) && (Local_uint16Distance <= THRESHOLD_DISTANCE_INFRONT_IN_CENTIMETER))
				{
					/* Stopping the car */
					Car_Stop();

					/* Stopping the unnecessary warning */
					Buzzer_voidStop();
					LCD_voidClearDisplay();

					/* Reseting the warning status */
					Global_Break_Warning_On_Status = Warning_OFF;

					/* Stopping the unnecessary timer */
					xTimerStop(Handle_Timer_RecieveESP,1000);

					/* Breaking out of the loop to get the task in the blocking mode to free up the processor */
					break;


				}
				else
				{
					/* Do Nothing */
				}

			}


		}
		else
		{


		}

	}



}

void TASK_Rasp_Receive(void *pvParameters)
{
	BaseType_t Notify_Status;
	uint32_t Local_uint32NotificationValue;
	uint32_t Local_uint32Timeout = 0;
	while(1)
	{
		Notify_Status = xTaskNotifyWait((uint32_t)NULL,(uint32_t)NULL,&Local_uint32NotificationValue, portMAX_DELAY);
		if(Notify_Status == pdTRUE)
		{
			if((Rasp_Recieved_Char == Notify_TASK_RaspRecieve_pass_RightLane)||(Rasp_Recieved_Char == Notify_TASK_RaspRecieve_pass_LeftLane))
			{
				xTaskNotify(Handle_ESP_Status,Notify_TASK_ESPSend_RequestOvertake,eSetValueWithOverwrite);

			}
			else if((Rasp_Recieved_Char == Notify_TASK_RaspRecieve_TurnRight))
			{
				/* Suspending the carcontrol task to ignore the life threatening wrong user decision */
				vTaskSuspend(Handle_CarControl);

				while((Rasp_Recieved_Char != 'Z') &&(Local_uint32Timeout< TIMEOUT_INSTRUCTIONS_TO_2500_Millis) )
				{
					/* Rotating right till receiving the approval of the raspberry */
					Car_Rotate_RightForward();

					/* Increasing the timeout in case of an issue with the raspberry */
					Local_uint32Timeout++;
				}

				/* After the raspberry approval, giving the control back to the user */
				vTaskResume(Handle_CarControl);

				/* Resseting the timeout */
				Local_uint32Timeout = 0;
			}
			else if((Rasp_Recieved_Char == Notify_TASK_RaspRecieve_TurnLeft))
			{
				/* Suspending the carcontrol task to ignore the life threatening wrong user decision */
				vTaskSuspend(Handle_CarControl);

				while((Rasp_Recieved_Char != 'Z') &&(Local_uint32Timeout< TIMEOUT_INSTRUCTIONS_TO_2500_Millis) )
				{
					/* Rotating right till receiving the approval of the raspberry */
					Car_Rotate_LeftForward();

					/* Increasing the timeout in case of an issue with the raspberry */
					Local_uint32Timeout++;
				}

				/* After the raspberry approval, giving the control back to the user */
				vTaskResume(Handle_CarControl);

				/* Reseting the timeout */
				Local_uint32Timeout = 0;
			}
			else
			{
				/* Do nothing */
			}


		}

		else
		{
			/* DO Nothing */
		}

	}

}

void TASK_Rasp_Send(void *pvParameters)
{
	BaseType_t Notify_Status;
	uint32_t Local_uint32NotificationValue;
	while(1)
	{
		Notify_Status = xTaskNotifyWait((uint32_t)NULL,(uint32_t)NULL,&Local_uint32NotificationValue, portMAX_DELAY);
		if(Notify_Status == pdTRUE)
		{
			/* sending the Clear_to_Overtake or NotClear_to_overtake to the Raspberry after receiving it from the ESP */
			HAL_UART_Transmit(&huart6,&Local_uint32NotificationValue, sizeof(Local_uint32NotificationValue), 1500);
		}
	}
}


