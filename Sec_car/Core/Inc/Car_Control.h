
#ifndef INC_CAR_CONTROL_H_
#define INC_CAR_CONTROL_H_


// Car control Functions
void Car_Move_Forward_High_Speed(void);
void Car_Move_Forward_Low_Speed(void);
void Car_Move_Backward(void);
void Car_Rotate_Right(void);
void Car_Rotate_Left(void);
void Car_Stop(void);
void Light_On(void);
void Light_OFF(void);

//Configuration Macros

/*First configure the IN1,2,3,4 to which port and pin*/
#define Motor1_Port    GPIOC
#define Motor2_Port    GPIOC
#define Motor3_Port    GPIOC
#define Motor4_Port    GPIOB

//Motor 1
#define IN1			GPIO_PIN_8
#define IN2			GPIO_PIN_9

//Motor 2
#define IN3			GPIO_PIN_2
#define IN4			GPIO_PIN_3

//Motor 3
#define IN5			GPIO_PIN_13
#define IN6			GPIO_PIN_4

//Motor 4
#define IN7			GPIO_PIN_5
#define IN8			GPIO_PIN_9


/*configure here the timer and channel for each motor
 * 1-Timer1,2,3      &htim1-&htim2-&htim3
 * 2- Channel 1,2,3,4    TIM_CHANNEL_1 - TIM_CHANNEL_2 - TIM_CHANNEL_3 - TIM_CHANNEL_4
 */

#define Motor1_Timer  &htim3
#define Motor2_Timer  &htim3
#define Motor3_Timer  &htim3
#define Motor4_Timer  &htim3



#define Motor1_Channel    TIM_CHANNEL_1
#define Motor2_Channel    TIM_CHANNEL_2
#define Motor3_Channel    TIM_CHANNEL_3
#define Motor4_Channel    TIM_CHANNEL_4


/*configure the pwm pins to
 * 1- Timer1,2,3       TIM1-TIM2-TIM3
 * 2- Channel 1,2,3,4  CCR1-CCR2-CCR3-CCR4 */

#define PWM_Motor_1			TIM3->CCR1
#define PWM_Motor_2			TIM3->CCR2
#define PWM_Motor_3	     	TIM3->CCR3
#define PWM_Motor_4			TIM3->CCR4








#endif /* INC_CAR_CONTROL_H_ */
