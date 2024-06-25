/*
 * Ultrasonic.h
 *
 *  Created on: May 26, 2024
 *      Author: dell
 */

#ifndef INC_ULTRASONIC_H_
#define INC_ULTRASONIC_H_

/*****************************Configuration_Macros******************************/

/* Define the pin & port of each of the Ultrasonic pins*/
#define TRIG_PORT   GPIOB
#define TRIG_PIN    GPIO_PIN_8


#define ECHO_PORT   GPIOD
#define ECHO_PIN    GPIO_PIN_2


/* Define the timer base to use on the Ultrasonic ECHO Pin*/

/* Choose from TIM0->TIM12 based on the available timers on the chip & replace it in the Ultrasonic.c extern line*/
/* Note: The Timer tick time is (1) MicroSecond */

#define Ultasonic_BASE_TIMER   &htim10


/*****************************Private_Macros************************************/
#define TRIG_PULSE_TIME_IN_MICROS      10

#define Calculation_Failed              0
#define Calculation_Success             1
#define TIMEOUT_ECHO_OCCURED            2

#define TIMEOUT_INSTRUCTIONS_TO_10_Millis   160000 		//This is based on 16MHZ clock frequency
#define TIMEOUT_INSTRUCTIONS_TO_25_Millis   400000 		//This is based on 16MHZ clock frequency
#define TIMEOUT_INSTRUCTIONS_TO_2500_Millis 25000 	//This is based on 16MHZ clock frequency


/*******************************Library_APIs*************************************/
void Ultasonic_voidInit(void);
uint8_t Ultrasonic_uint8Get_Distance_In_Cm(uint16_t *Copy_Puint16Distance_Infront);




#endif /* INC_ULTRASONIC_H_ */
