/*
 * Tasks.c
 *
 *  Created on: Feb 22, 2024
 *      Author: dell
 */

#include "main.h"
#include "stm32f4xx_hal.h"

#include "FreeRTOS.h"
#include "task.h"

#include "Tasks.h"
#include "Car_Control.h"
#include "Help_Functions.h"
#include "Buzzer.h"
#include "LCD_I2C.h"
#include "GPS.h"
#include "bluetooth.h"
#include "Car_Control.h"
#include "Build_msg.h"
#include <stdint.h>

extern uint8_t received_char;
uint8_t  Global_GPS_Speed_Completetion=0;
uint8_t  Light_Sensor_Status=0;

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
            	  Global_GPS_Speed_Completetion==Half_Completed_GPS;

              }
              else if(Global_GPS_Speed_Completetion==Half_Completed_Speed)
              {
            	  /*Deactivating the interrupts to avoid the speed interrupt to preempt*/
            	  taskENTER_CRITICAL();
            	  Global_GPS_Speed_Completetion=Nothing_Completed;
            	  taskEXIT_CRITICAL();

            	  /*Activate the ESPTask*/
                  //xTaskNotify();
              }
        	  /*Stopping the task for 400ms to free the processor*/
              vTaskDelay(pdMS_TO_TICKS(400));
         }
         else if(Decode_Error_Code==Decode_Failed)
		 {


		 }



	}




}

void TASK_LCDBuzzer (void *pvParameters)
{
	uint32_t Local_uint8NotificationValue;

	while(1)
	{
		xTaskNotifyWait((uint32_t)NULL,0xFFFFFFFF,&Local_uint8NotificationValue, portMAX_DELAY);

		switch(Local_uint8NotificationValue)
		{
		case Notify_TASK_LCDBuzzer_Break:

			Buzzer_voidHighSound();
			LCD_AvoidHardBraking();
			break;

		default:
			/*Do Nothing*/
			break;


		}


	}


}

void TASK_CarControl(void *pvParameters)
{
	for (;;) {
		// Read data from UART
		switch (received_char){
		case '1':

			break;
		case '2':
			Car_Move_Forward_High_Speed();
			break;
		case '3':
			break;
		case '4':
			Car_Rotate_Right();
			break;
		case '5':
			Car_Stop();
			break;
		case '6':
			Car_Rotate_Left();
			break;
		case '7':
			break;
		case '8':
			Car_Move_Backward();
			break;
		case '9':
			break;
		case 'b':
			Car_Stop();
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
void TASK_ESPSend_PeriodicData (void *pvParameters)
{

    while(1)
    {


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
    	/*Update the status*/
    	Light_Sensor_Status=1;

    	//Notify the ESPSendStatus task with problem in light
    	//xTaskNotifyGive();

    	/*Delaying the task to free the processor*/
    	vTaskDelay(pdMS_TO_TICKS(800));
    }
    else
	{
    	/*Delaying the task to free the processor*/
    	vTaskDelay(pdMS_TO_TICKS(600));

	}

  }




}

