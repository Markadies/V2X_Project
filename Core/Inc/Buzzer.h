/*
 * Buzzer.h
 *
 *  Created on: Nov 24, 2023
 *      Author: 7ma bondary
 */

#ifndef STM32F4XX_HAL_DRIVER_INC_BUZZER_H_
#define STM32F4XX_HAL_DRIVER_INC_BUZZER_H_

void Buzzer_voidLowSound(void);
void Buzzer_voidMidSound(void);
void Buzzer_voidHighSound(void);
void Buzzer_voidStop(void);


/*Configurations Macros*/
#define Buzzer_Timer_Connected               TIMER1
#define Buzzer_TimerChannel_Connected        TIMER_CHANNEL_2

/*Private Macros*/
#define TIMER1       0
#define TIMER2       1
#define TIMER3       2

#define TIMER_CHANNEL_1    3
#define TIMER_CHANNEL_2    4
#define TIMER_CHANNEL_3    5
#define TIMER_CHANNEL_4    6


#endif /* STM32F4XX_HAL_DRIVER_INC_BUZZER_H_ */
