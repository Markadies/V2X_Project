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
uint8_t  Global_GPS_Speed_Completetion=0;

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
            	  Global_GPS_Speed_Completetion = Half_Completed_GPS;

              }
              else if(Global_GPS_Speed_Completetion==Half_Completed_Speed)
              {
            	  /*Deactivating the interrupts to avoid the speed interrupt to preempt*/
            	  taskENTER_CRITICAL();
            	  Global_GPS_Speed_Completetion = Nothing_Completed;
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
	 case Notify_TASK_LCDBuzzer_Light:

         Buzzer_voidMidSound();
         LCD_HighLightIntensity_Warning();



		 break;

	 default:
		 /*Do Nothing*/
		 break;


	  }


	}


}

void TASK_CarControl(void *pvParameters)
{
	uint32_t Local_Notification_Value;
	for (;;) {
		/*Waiting to be notified from the BT ISR */
		xTaskNotifyWait((uint32_t)NULL,(uint32_t)NULL,&Local_Notification_Value,portMAX_DELAY);

		// Read data from UART
		switch (received_char){
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
			//Notify the sendEspStatus task
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
void TASK_ESPSend_PeriodicData (void *pvParameters)
{

   while(1)
   {



   }


}

void TASK_ESP_SendStatus (void *pvParameters)
{

	 while(1)
	 {




	 }



}





