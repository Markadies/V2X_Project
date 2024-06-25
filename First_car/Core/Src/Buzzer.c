
#include "stm32f4xx_hal.h"
#include "Buzzer.h"

extern TIM_HandleTypeDef htim12;
void Buzzer_voidLowSound(void)
{
#if Buzzer_Timer_Connected == TIMER1
#if Buzzer_TimerChannel_Connected == TIMER_CHANNEL_1
	TIM1->CCR1=20;
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);

#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_2
	TIM1->CCR2=20;
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);


#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_3
	TIM1->CCR3=20;
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);

#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_4

	TIM1->CCR4=20;
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
#endif
#elif Buzzer_Timer_Connected == TIMER2

#if Buzzer_TimerChannel_Connected == TIMER_CHANNEL_1
	TIM2->CCR1=20;
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);


#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_2
	TIM2->CCR2=20;
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);

#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_3

	TIM2->CCR3=20;
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_4
	TIM2->CCR4=20;
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_4);



#endif




#elif Buzzer_Timer_Connected == TIMER3
#if Buzzer_TimerChannel_Connected == TIMER_CHANNEL_1
	TIM3->CCR1=20;
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);


#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_2
	TIM3->CCR2=20;
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);



#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_3
	TIM3->CCR3=20;
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);


#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_4
	TIM3->CCR4=20;
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);


#endif

#elif Buzzer_Timer_Connected == TIMER12
#if Buzzer_TimerChannel_Connected == TIMER_CHANNEL_1
	TIM12->CCR1=20;
	HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_1);


#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_2
	TIM12->CCR2=20;
	HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_2);

#endif



#endif
}
void Buzzer_voidMidSound(void)
{
#if Buzzer_Timer_Connected == TIMER1
#if Buzzer_TimerChannel_Connected == TIMER_CHANNEL_1
	TIM1->CCR1=50;
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);

#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_2
	TIM1->CCR2=50;
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);


#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_3
	TIM1->CCR3=50;
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);

#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_4

	TIM1->CCR4=50;
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
#endif
#elif Buzzer_Timer_Connected == TIMER2

#if Buzzer_TimerChannel_Connected == TIMER_CHANNEL_1
	TIM2->CCR1=50;
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);


#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_2
	TIM2->CCR2=50;
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);


#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_3

	TIM2->CCR3=50;
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_4
	TIM2->CCR4=50;
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_4);



#endif




#elif Buzzer_Timer_Connected == TIMER3
#if Buzzer_TimerChannel_Connected == TIMER_CHANNEL_1
	TIM3->CCR1=50;
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);


#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_2
	TIM3->CCR2=50;
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);



#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_3
	TIM3->CCR3=50;
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);


#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_4
	TIM3->CCR4=50;
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);


#endif

#elif Buzzer_Timer_Connected == TIMER12
#if Buzzer_TimerChannel_Connected == TIMER_CHANNEL_1
	TIM12->CCR1=50;
	HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_1);


#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_2
	TIM12->CCR2=50;
	HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_2);



#endif




#endif


}
void Buzzer_voidHighSound(void)
{
#if Buzzer_Timer_Connected == TIMER1
#if Buzzer_TimerChannel_Connected == TIMER_CHANNEL_1
	TIM1->CCR1=90;
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);

#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_2
	TIM1->CCR2=90;
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);


#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_3
	TIM1->CCR3=90;
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);

#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_4

	TIM1->CCR4=90;
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
#endif
#elif Buzzer_Timer_Connected == TIMER2

#if Buzzer_TimerChannel_Connected == TIMER_CHANNEL_1
	TIM2->CCR1=90;
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);


#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_2
	TIM2->CCR2=90;
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);


#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_3

	TIM2->CCR3=90;
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_4
	TIM2->CCR4=90;
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_4);



#endif




#elif Buzzer_Timer_Connected == TIMER3
#if Buzzer_TimerChannel_Connected == TIMER_CHANNEL_1
	TIM3->CCR1=90;
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);


#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_2
	TIM3->CCR2=90;
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);



#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_3
	TIM3->CCR3=90;
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);


#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_4
	TIM3->CCR4=90;
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);


#endif
#elif Buzzer_Timer_Connected == TIMER12
#if Buzzer_TimerChannel_Connected == TIMER_CHANNEL_1
	TIM12->CCR1=99;
	HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_1);


#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_2
	TIM12->CCR2=90;
	HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_2);


#endif





#endif



}

void Buzzer_voidStop(void)
{
#if Buzzer_Timer_Connected == TIMER1
#if Buzzer_TimerChannel_Connected == TIMER_CHANNEL_1
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);

#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_2
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);

#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_3

	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);

#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_4
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_4);

#endif
#elif Buzzer_Timer_Connected == TIMER2

#if Buzzer_TimerChannel_Connected == TIMER_CHANNEL_1

	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);

#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_2

	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);
#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_3

	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3);
#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_4
	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4);



#endif




#elif Buzzer_Timer_Connected == TIMER3
#if Buzzer_TimerChannel_Connected == TIMER_CHANNEL_1

	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_2

	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);

#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_3

	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);

#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_4

	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4);

#endif

#elif Buzzer_Timer_Connected == TIMER12
#if Buzzer_TimerChannel_Connected == TIMER_CHANNEL_1

	HAL_TIM_PWM_Stop(&htim12, TIM_CHANNEL_1);


#elif Buzzer_TimerChannel_Connected == TIMER_CHANNEL_2

	HAL_TIM_PWM_Stop(&htim12, TIM_CHANNEL_2);


#endif




#endif
}



