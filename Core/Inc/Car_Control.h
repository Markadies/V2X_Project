
#ifndef INC_CAR_CONTROL_H_
#define INC_CAR_CONTROL_H_


// Car control Functions
void Car_Move_Forward_High_Speed(void);
void Car_Move_Forward_Low_Speed(void);
void Car_Move_Backward(void);
void Car_Rotate_Right(void);
void Car_Rotate_Left(void);
void Car_Stop(void);

//Configuration Macros


/*First configure the IN1,2,3,4 to which port and pin*/
#define Motor1_Port    GPIOC
#define Motor2_Port    GPIOC

#define IN1			GPIO_PIN_4
#define IN2			GPIO_PIN_5
#define IN3			GPIO_PIN_8
#define IN4			GPIO_PIN_9

/*configure here the timer and channel for each motor
 * 1-Timer1,2,3      &htim1-&htim2-&htim3
 * 2- Channel 1,2,3,4    TIM_CHANNEL_1 - TIM_CHANNEL_2 - TIM_CHANNEL_3 - TIM_CHANNEL_4*/

#define Motor1_Timer  &htim3
#define Motor2_Timer  &htim3

#define Motor1_Channel    TIM_CHANNEL_1
#define Motor2_Channel    TIM_CHANNEL_2

/*configure the pwm pins to
 * 1- Timer1,2,3       TIM1-TIM2-TIM3
 * 2- Channel 1,2,3,4  CCR1-CCR2-CCR3-CCR4 */

#define PWM_Motor_1			TIM3->CCR1
#define PWM_Motor_2			TIM3->CCR2








#endif /* INC_CAR_CONTROL_H_ */
