/*
 * Tasks.h
 *
 *  Created on: Feb 22, 2024
 *      Author: dell
 */

#ifndef INC_TASKS_H_
#define INC_TASKS_H_

/***************************************Library Functions**********************************************/

void TASK_CarControl (void *pvParameters);
void TASK_GPS        (void *pvParameters);
void TASK_ESPSend_PeriodicData (void *pvParameters);
void TASK_ESP_SendStatus (void *pvParameters);
void TASK_ESP_Receive (void *pvParameters);
void TASK_LightSensor(void *pvParameters);
void TASK_Distance_AboveThreshold(void *pvParameters);
void TASK_Rasp_Receive(void *pvParameters);
void TASK_Rasp_Send(void *pvParameters);

/*************************************Configurations Macros********************************************/

//Tasks Priority
#define Priority_TASK_CarControl            			3
#define Priority_TASK_GPS                   			2
#define Priority_TASK_ESP_Periodic          			2
#define Priority_TASK_ESP_Status                        3
#define Priority_TASK_ESP_Receive                       3
#define Priority_TASK_LightSensor                       2
#define Priority_TASK_Distance_AboveThreshold           2
#define Priority_TASK_Rasp_Recieve			            3
#define Priority_TASK_Rasp_Send				            3


//For light sensor task
/*Configure the Max flux intensity that consider a problem */
#define MAX_LightIntensity           20

//For light sensor task
/*Configure the threshold distance to take the appropriate action*/
#define THRESHOLD_DISTANCE_INFRONT_IN_CENTIMETER   60

/***************************************Private Macros*************************************************/

#define Notify_TASK_ESPRecieve_Light            	'L'
#define Notify_TASK_ESPRecieve_Break            	'B'
#define Notify_TASK_ESPSend_AvoidOvertake	  	  	'o'
#define Notify_TASK_ESPSend_RequestOvertake			'v'

#define Notify_TASK_RaspRecieve_pass_RightLane  	146
#define Notify_TASK_RaspRecieve_pass_LeftLane   	158
#define Notify_TASK_RaspSend_Overtake_Clear     	'O'
#define Notify_TASK_RaspSend_Overtake_NotClear  	'N'

#define  Notify_TASK_RaspRecieve_TurnRight			'A'
#define  Notify_TASK_RaspRecieve_TurnLeft	 		'Z'


#define Notify_TASK_ESPSend_HighLight		   5

#define Nothing_Completed                      0
#define Half_Completed_Speed                   1
#define Half_Completed_GPS                     2


#define Warning_OFF                            0
#define Warning_ON                             1

#define Breaking_OFF                           0
#define Breaking_ON                            1

#endif /* INC_TASKS_H_ */
