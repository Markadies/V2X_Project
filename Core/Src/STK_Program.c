


#include "../Inc/BIT_MATH.h"
#include "../Inc/STD_TYPES.h"
#include "../Inc/STK_Config.h"
#include "../Inc/STK_Interface.h"
#include "../Inc/STK_Private.h"



void (*GPF)(void)=NULL;
/*GLobal variable to check the interval of the funtion whether its single or periodic*/
uint8_t GLobal_uint8_tIntervalMode=0;

/********************************************/
/* SWC: STK Driver                          */
/* Author: Bendary                          */
/* Version: v0.0                            */
/* Date: 20 OCT 2023                        */
/* Description: This is the implem. of STK  */
/********************************************/




/**********************************************************/
/* Func. Name:STK_voidInit                                */
/* i/p arguments:Nothing                                  */
/* o/p arguments:Nothing                                  */
/* Desc. : This API allows user to Intialize the STK Timer*/
/**********************************************************/
void STK_voidInit(void)
{
	/*I will start with disabling every thing until the user uses a function then
	 * i will enable the STK and the interrupts if needed (Busy waiting doesnt need interrupts)*/

	/*1-Disabling the STK timer*/
	CLR_BIT(STK_CTRL,STK_CTRL_ENABLE);

	/*2-Disabling the Interrupts request for the STK*/
	CLR_BIT(STK_CTRL,STK_CTRL_TICKINT);

#if STK_CLOCK_SOURCE == AHB
	/*3-Setting the STK clock source to the same value of AHB*/
	SET_BIT(STK_CTRL,STK_CTRL_CLKSOURCE);


#elif STK_CLOCK_SOURCE == AHB_Over_8

	/*3-Setting the STK clock source to the same value of (AHB/8)
	 * My AHB is 8MHZ,so my STK tick is 1 microsec*/
	CLR_BIT(STK_CTRL,STK_CTRL_CLKSOURCE);

#else #error
#endif
}




/****************************************************/
/* Func. Name:STK_voidSetBusyWait                   */
/* i/p arguments:Copy_uint32_tTimeInMillis:Time in millis*/
/* o/p arguments:Nothing                            */
/* Desc. : This API allows user todelay the system  */
/* for amount of time                               */
/****************************************************/
void STK_voidSetBusyWait(uint32_t Copy_uint32_tTimeInMillis)
{
	uint32_t Local_uint32_tNumberOfTicks=(Copy_uint32_tTimeInMillis*1000);
	/*Put the Number of ticks in the LOAD register*/
	STK_LOAD=Local_uint32_tNumberOfTicks;

	/*Start the timer*/
	SET_BIT(STK_CTRL,STK_CTRL_ENABLE); //after this line the VAl register copies the value of LOAD register

	/*Wait until the flag is raised*/
	while(GET_BIT(STK_CTRL,STK_CTRL_COUNTFLAG)==0);
	/*Stop the timer*/
	CLR_BIT(STK_CTRL,STK_CTRL_ENABLE);

	/*For verification that the timer will stop(didnt listen to the last command)*/

	/*When i make the load=0 the val will copy 0 so it will count to nothing
	 * for more verification i will set the val to 0 to reset after any random operations
	 * after i stoped the timer so it can copy the 0 from the load and count to nothing*/
	STK_LOAD=0;
	STK_VAL=0;


}
/***************************************************/
/* Func. Name:STK_voidSetIntervalSingle            */
/* i/p arguments:Copy_uint32_tTimeInMillis: Time in millis
 *               LPF:put the function that will be
 * excuted after this amount of time               */
/* o/p arguments:Nothing                           */
/* Desc. : This API allows user to set the time    */
/*between each interrupt (for one time)            */
/***************************************************/
void STK_voidSetIntervalSingle(uint32_t Copy_uint32_tTimeInMillis,void (*LPF) (void))
{
	/*Setting the interval mode to single*/
	GLobal_uint8_tIntervalMode=SingleMode;

	/*Assigning the number of ticks based on the time (1 tick= 1 microsec)*/
	uint32_t Local_uint32_tNumberOfTicks=(Copy_uint32_tTimeInMillis*1000);

	/*Put the Number of ticks in the LOAD register*/
	STK_LOAD=Local_uint32_tNumberOfTicks;

	/*Put the LPF in the GPF to excute the interrupt*/
	GPF=LPF;

	/*Enable the Interrupt*/
	SET_BIT(STK_CTRL,STK_CTRL_TICKINT);

	/*Start the timer*/
	SET_BIT(STK_CTRL,STK_CTRL_ENABLE); //after this line the VAl register copies the value of LOAD register

}
/***************************************************/
/* Func. Name:STK_voidSetIntervalSingle            */
/* i/p arguments:Copy_uint32_tTimeInMillis: Time in millis
 *               LPF:put the function that will be
 * excuted after this amount of time               */
/* o/p arguments:Nothing                           */
/* Desc. : This API allows user to set the time    */
/*between each interrupt                           */
/***************************************************/
void STK_voidSetIntervalPeriodic(uint32_t Copy_uint32_tTimeInMillis,void (*LPF)(void))
{
	/*Setting the interval mode to single*/
	GLobal_uint8_tIntervalMode=PeriodicMode;

	/*Assigning the number of ticks based on the time (1 tick= 1 microsec)*/
	uint32_t Local_uint32_tNumberOfTicks=(Copy_uint32_tTimeInMillis*1000);

	/*Put the Number of ticks in the LOAD register*/
	STK_LOAD=Local_uint32_tNumberOfTicks;

	/*Put the LPF in the GPF to excute the interrupt*/
	GPF=LPF;

	/*Enable the Interrupt*/
	SET_BIT(STK_CTRL,STK_CTRL_TICKINT);

	/*Start the timer*/
	SET_BIT(STK_CTRL,STK_CTRL_ENABLE); //after this line the VAl register copies the value of LOAD register



}
/********************************************/
/* Func. Name:STK_voidGetElapsedTime        */
/* i/p arguments:Nothing                    */
/* o/p arguments:Time in microsec           */
/* Desc. : This API allows user to          */
/*get the time done till now in this cycle  */
/********************************************/
uint32_t STK_voidGetElapsedTime(void)
{
	/*Return the time in microsec(= number of ticks)*/
	return (STK_LOAD-STK_VAL);
}
/********************************************/
/* Func. Name:STK_voidGetRemainingTime      */
/* i/p arguments:Nothing                    */
/* o/p arguments:Time in microsec           */
/* Desc. : This API allows user to          */
/*get the time remaining in this cycle      */
/********************************************/
uint32_t STK_voidGetRemainingTime(void)
{
	/*Return the time in microsec(= number of ticks)*/
	return STK_VAL;
}



/*ISR*/
void SysTick_Handler()
{
	uint8_t Local_uint8_tTemp;
	/*Checking this ISR is excuted from the Single or peridic funtion to
	 * take the descision whether to excute this ISR one time or multiple*/
	if(GLobal_uint8_tIntervalMode==SingleMode)
	{
		/*Disable the timer to avoid excuting it again*/
		CLR_BIT(STK_CTRL,STK_CTRL_ENABLE);
		STK_LOAD=0;
		STK_VAL=0;

		/*Disable the interrupt*/
		CLR_BIT(STK_CTRL,STK_CTRL_TICKINT);
	}
	else
	{
		// Do Nothing
	}

	if(GPF != NULL)
	{
		GPF();
	}
	/*Matnsa4 an al flag byt3mlo clear lma te2rah bas*/
	/*Clearing the flag*/
	Local_uint8_tTemp=GET_BIT(STK_CTRL,STK_CTRL_COUNTFLAG);


	//Note: in the first if condition(if you are single mode fuction) will disable every thing but the
	//GPF still has the LPF so it will be excuted one time normally
}



