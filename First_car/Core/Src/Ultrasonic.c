
#include "main.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_tim.h"
#include "Ultrasonic.h"

/* Define your base timer for the ultrasonic calculations , and in the configuration macros edit it*/
extern TIM_HandleTypeDef htim10;

const char Global_Inverse_Sound_Speed_In_MicroSecond_Centimeter = 58;

void Ultasonic_voidInit(void)
{
	/* Making sure that the TRIG pin is LOW*/
	HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_RESET);

	/* Making Sure that the Ultrasionic base timer is stopped */
	HAL_TIM_Base_Stop(Ultasonic_BASE_TIMER);

}

uint8_t Ultrasonic_uint8Get_Distance_In_Cm(uint16_t *Copy_Puint16Distance_Infront)
{

	uint8_t  Local_uint8ErrorCode = Calculation_Failed;
	uint16_t Local_uint16Counts_Before = 0,Local_uint16Counts_After = 0;
	uint16_t Local_uint16Echo_ELapsed_Time_In_Micros = 0;
	uint32_t Local_uint32Timeout = 0;

	/* First is to Start the timer */
	HAL_TIM_Base_Start(Ultasonic_BASE_TIMER);

	/* For Synchronization, reseting the Counter by setting it to zero */
	__HAL_TIM_SET_COUNTER(Ultasonic_BASE_TIMER,0);

	/* Starting the TRIGGER to send the sound wave */
	HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_SET);

	/* Waiting for 10Micro Seconds specified in the datasheet */
	while(__HAL_TIM_GET_COUNTER(Ultasonic_BASE_TIMER) < TRIG_PULSE_TIME_IN_MICROS);

	/* Setting the TRIG PIN as LOW */
	HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_RESET);

	/* Waiting till the ECHO PIN is HIGH or a timeout occurred at 10 milliseconds*/
	while(!(HAL_GPIO_ReadPin(ECHO_PORT, ECHO_PIN)) && (Local_uint32Timeout < TIMEOUT_INSTRUCTIONS_TO_10_Millis)) Local_uint32Timeout++;

	/* Getting the start value which the ECHO is triggered*/
	Local_uint16Counts_Before = __HAL_TIM_GET_COUNTER(Ultasonic_BASE_TIMER);

	if(Local_uint32Timeout == TIMEOUT_INSTRUCTIONS_TO_10_Millis)
	{
		/* Stopping the timer after completing the operation */
		HAL_TIM_Base_Stop(Ultasonic_BASE_TIMER);

		/* Alert the user that something is wrong*/
		Local_uint8ErrorCode = Calculation_Failed;

		return Local_uint8ErrorCode;
	}
	else
	{
		/* Resetting the timeout variable */
		Local_uint32Timeout = 0 ;

		/* Waiting till the ECHO is LOW to calculate the distance */
		while((HAL_GPIO_ReadPin(ECHO_PORT, ECHO_PIN)) && (Local_uint32Timeout < TIMEOUT_INSTRUCTIONS_TO_25_Millis)) Local_uint32Timeout++;

		/* Getting the end value after the ECHO is back to reset */
		Local_uint16Counts_After = __HAL_TIM_GET_COUNTER(Ultasonic_BASE_TIMER);

		if(Local_uint32Timeout == TIMEOUT_INSTRUCTIONS_TO_25_Millis)
		{
			/* Stopping the timer after completing the operation */
			HAL_TIM_Base_Stop(Ultasonic_BASE_TIMER);

			/* Alert the user that something is wrong*/
			Local_uint8ErrorCode = TIMEOUT_ECHO_OCCURED;

			return Local_uint8ErrorCode;

		}
		else
		{
			/* Calculating the time which the ECHO pin is high for */
			Local_uint16Echo_ELapsed_Time_In_Micros = Local_uint16Counts_After - Local_uint16Counts_Before;

			/* Calculating the Distance in centimeters & Change the user distance variable with the calculated one*/
			*Copy_Puint16Distance_Infront =(Local_uint16Echo_ELapsed_Time_In_Micros / Global_Inverse_Sound_Speed_In_MicroSecond_Centimeter );

			/* Stopping the timer after completing the operation */
			HAL_TIM_Base_Stop(Ultasonic_BASE_TIMER);

			/* Updating the Error code to alert the user with the calculation success*/
			Local_uint8ErrorCode = Calculation_Success;

			return Local_uint8ErrorCode;
		}

	}

}





