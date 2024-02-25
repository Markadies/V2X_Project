/*
 * Tasks.c
 *
 *  Created on: Feb 22, 2024
 *      Author: dell
 */

#include "main.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"


#include "Tasks.h"
#include "Help_Functions.h"
#include "Buzzer.h"
#include "LCD_I2C.h"
#include "GPS.h"
#include "bluetooth.h"


void TASK_LCDBuzzer (void *parameters)
{
    uint32_t Local_uint8NotificationValue;

	while(1)
	{
      xTaskNotifyWait((uint32_t)NULL,0xFFFFFFFF,&Local_uint8NotificationValue, portMAX_DELAY);

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



