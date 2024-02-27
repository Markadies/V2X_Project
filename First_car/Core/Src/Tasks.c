/*
 * Tasks.c
 *
 *  Created on: Feb 22, 2024
 *      Author: dell
 */

#include "main.h"
#include "stm32f4xx_hal.h"



#include "Tasks.h"
#include "Help_Functions.h"
#include "Buzzer.h"
#include "LCD_I2C.h"
#include "GPS.h"
#include "bluetooth.h"
#include "Car_Control.h"
#include <stdint.h>

extern uint8_t received_char;

void TASK_LCDBuzzer (void *parameters)
{
    uint32_t Local_uint8NotificationValue;

	while(1)
	{
      //xTaskNotifyWait((uint32_t)NULL,0xFFFFFFFF,&Local_uint8NotificationValue, portMAX_DELAY);

	 switch(Local_uint8NotificationValue)
	 {
	 case Notify_TASK_LCDBuzzer_Break:

         Buzzer_voidHighSound();
         LCD_HighLightIntensity_Warning();



		 break;

	 default:
		 /*Do Nothing*/
		 break;


	 }


	}


}

void UART_Task(void *pvParameters) {
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



