/*
 * Tasks.h
 *
 *  Created on: Feb 22, 2024
 *      Author: dell
 */

#ifndef INC_TASKS_H_
#define INC_TASKS_H_

  /***************************************Library Functions**********************************************/
void TASK_LCDBuzzer  (void *pvParameters);
void TASK_CarControl (void *pvParameters);
void TASK_GPS        (void *pvParameters);
void TASK_ESPSend_PeriodicData (void *pvParameters);
void TASK_ESP_SendStatus (void *pvParameters);
void TASK_ESP_Receive (void *pvParameters);

  /*************************************Configurations Macros********************************************/

//Tasks Priority
#define Priority_TASK_LCDBuzzer             2
#define Priority_TASK_CarControl            2
#define Priority_TASK_GPS                   2
#define Priority_TASK_ESP_Periodic          2
#define Priority_TASK_ESP_Status            1
#define Priority_TASK_ESP_Receive           1

  /***************************************Private Macros*************************************************/

#define Notify_TASK_LCDBuzzer_Light            1
#define Notify_TASK_LCDBuzzer_Break            2
#define Notify_TASK_LCDBuzzer_AvoidOvertake    3
#define Notify_TASK_LCDBuzzer_BeingOvertaken   4

#define Notify_TASK_ESPStatus_HardBreaking	   5

#define Nothing_Completed                      0
#define Half_Completed_Speed                   1
#define Half_Completed_GPS                     2


#endif /* INC_TASKS_H_ */
