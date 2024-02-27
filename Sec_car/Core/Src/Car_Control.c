#include "stm32f4xx_hal.h"
#include "Car_Control.h"

/*Defining the Macros for the duty cycles to configure if needed*/
#define HIGH_SPEED    99
#define LOW_SPEED     70

extern TIM_HandleTypeDef htim3;


/*Inner functions will be called by the main functions*/
static void Motors_Disabling(void);

void Motor1_Rotate_CW(void);
void Motor1_Rotate_CCW(void);

void Motor2_Rotate_CW(void);
void Motor2_Rotate_CCW(void);

void Motor3_Rotate_CW(void);
void Motor3_Rotate_CCW(void);


void Motor4_Rotate_CW(void);
void Motor4_Rotate_CCW(void);


void Car_Move_Forward_High_Speed(void){
	/*First Disabling the two motors*/
	Motors_Disabling();

	/*Setting the PWM for both motors to high Speed & Starting the PWM generation on both motors*/
	/*Assigning the duty cycle*/
	PWM_Motor_1=HIGH_SPEED;
	PWM_Motor_2=HIGH_SPEED;
	PWM_Motor_3=HIGH_SPEED;
	PWM_Motor_4=HIGH_SPEED;

	/*Starting the generation*/
	HAL_TIM_PWM_Start(Motor1_Timer,Motor1_Channel);
	HAL_TIM_PWM_Start(Motor2_Timer,Motor2_Channel);
	HAL_TIM_PWM_Start(Motor3_Timer,Motor3_Channel);
	HAL_TIM_PWM_Start(Motor4_Timer,Motor4_Channel);

	/*Making Both motors rotate at the same direction*/
	Motor1_Rotate_CW();
	Motor2_Rotate_CW();
	Motor3_Rotate_CW();
	Motor4_Rotate_CW();
}


void Car_Move_Forward_Low_Speed(void)
{
	/*First Disabling the two motors*/
	Motors_Disabling();

	/*Setting the PWM for both motors to high Speed & Starting the PWM generation on both motors*/
	/*Assigning the duty cycle*/
	PWM_Motor_1=LOW_SPEED;
	PWM_Motor_2=LOW_SPEED;
	PWM_Motor_3=LOW_SPEED;
	PWM_Motor_4=LOW_SPEED;

	/*Starting the generation*/
	HAL_TIM_PWM_Start(Motor1_Timer,Motor1_Channel);
	HAL_TIM_PWM_Start(Motor2_Timer,Motor2_Channel);
	HAL_TIM_PWM_Start(Motor3_Timer,Motor3_Channel);
	HAL_TIM_PWM_Start(Motor4_Timer,Motor4_Channel);

	/*Making Both motors rotate at the same direction*/
	Motor1_Rotate_CW();
	Motor2_Rotate_CW();
	Motor3_Rotate_CW();
	Motor4_Rotate_CW();
}
void Car_Move_Backward(void)
{
	/*First Disabling the two motors*/
	Motors_Disabling();

	/*Setting the PWM for both motors to high Speed & Starting the PWM generation on both motors*/
	/*Assigning the duty cycle*/
	PWM_Motor_1=HIGH_SPEED;
	PWM_Motor_2=HIGH_SPEED;
	PWM_Motor_3=HIGH_SPEED;
	PWM_Motor_4=HIGH_SPEED;

	/*Starting the generation*/
	HAL_TIM_PWM_Start(Motor1_Timer,Motor1_Channel);
	HAL_TIM_PWM_Start(Motor2_Timer,Motor2_Channel);
	HAL_TIM_PWM_Start(Motor3_Timer,Motor3_Channel);
	HAL_TIM_PWM_Start(Motor4_Timer,Motor4_Channel);

	/*Making Both motors rotate at the same  direction*/
	Motor1_Rotate_CCW();
	Motor2_Rotate_CCW();
	Motor3_Rotate_CCW();
	Motor4_Rotate_CCW();
}

void Car_Rotate_Right(void)
{
	/*First Disabling the two motors*/
	Motors_Disabling();

	/*Setting the PWM for both motors to high Speed & Starting the PWM generation on both motors*/
	/*Assigning the duty cycle*/
	PWM_Motor_1=HIGH_SPEED;
	PWM_Motor_2=HIGH_SPEED;
	PWM_Motor_3=HIGH_SPEED;
	PWM_Motor_4=HIGH_SPEED;

	/*Starting the generation*/
	HAL_TIM_PWM_Start(Motor1_Timer,Motor1_Channel);
	HAL_TIM_PWM_Start(Motor2_Timer,Motor2_Channel);
	HAL_TIM_PWM_Start(Motor3_Timer,Motor3_Channel);
	HAL_TIM_PWM_Start(Motor4_Timer,Motor4_Channel);

	/*Making Both motors rotate at opposite direction*/
	Motor1_Rotate_CW();
	Motor2_Rotate_CCW();
	Motor3_Rotate_CW();
	Motor4_Rotate_CCW();
}
void Car_Rotate_Left(void)
{
	/*First Disabling the two motors*/
	Motors_Disabling();

	/*Setting the PWM for both motors to high Speed & Starting the PWM generation on both motors*/
	/*Assigning the duty cycle*/
	PWM_Motor_1=LOW_SPEED;
	PWM_Motor_2=LOW_SPEED;
	PWM_Motor_3=LOW_SPEED;
	PWM_Motor_4=LOW_SPEED;

	/*Starting the generation*/
	HAL_TIM_PWM_Start(Motor1_Timer,Motor1_Channel);
	HAL_TIM_PWM_Start(Motor2_Timer,Motor2_Channel);
	HAL_TIM_PWM_Start(Motor3_Timer,Motor3_Channel);
	HAL_TIM_PWM_Start(Motor4_Timer,Motor4_Channel);

	/*Making Both motors rotate at opposite direction*/
	Motor1_Rotate_CCW();
	Motor2_Rotate_CW();
	Motor3_Rotate_CCW();
	Motor4_Rotate_CW();

}
void Car_Rotate_RightForward(void)
{
	/*First Disabling the Four motors*/
	Motors_Disabling();

	/*Setting the PWM for both motors to high Speed & Starting the PWM generation on both motors*/
	/*Right motors rotate high speed and the Left with low speed*/
	/*Assigning the duty cycle*/

	PWM_Motor_1=LOW_SPEED;
	PWM_Motor_2=HIGH_SPEED;
	PWM_Motor_3=LOW_SPEED;
	PWM_Motor_4=HIGH_SPEED;

	/*Starting the generation*/

	HAL_TIM_PWM_Start(Motor1_Timer,Motor1_Channel);
	HAL_TIM_PWM_Start(Motor2_Timer,Motor2_Channel);
	HAL_TIM_PWM_Start(Motor3_Timer,Motor3_Channel);
	HAL_TIM_PWM_Start(Motor4_Timer,Motor4_Channel);

	/*Making  motors rotate at opposite direction*/
		Motor1_Rotate_CW();
		Motor2_Rotate_CW();
		Motor3_Rotate_CW();
		Motor4_Rotate_CW();



}
void Car_Rotate_LeftForward(void)
{

	/*First Disabling the Four motors*/
	Motors_Disabling();

	/*Setting the PWM for both motors to high Speed & Starting the PWM generation on both motors*/
	/*Right motors rotate high speed and the Left with low speed*/
	/*Assigning the duty cycle*/

	PWM_Motor_1=HIGH_SPEED;
	PWM_Motor_2=LOW_SPEED;
	PWM_Motor_3=HIGH_SPEED;
	PWM_Motor_4=LOW_SPEED;

	/*Starting the generation*/

	HAL_TIM_PWM_Start(Motor1_Timer,Motor1_Channel);
	HAL_TIM_PWM_Start(Motor2_Timer,Motor2_Channel);
	HAL_TIM_PWM_Start(Motor3_Timer,Motor3_Channel);
	HAL_TIM_PWM_Start(Motor4_Timer,Motor4_Channel);

	/*Making  motors rotate at opposite direction*/
		Motor1_Rotate_CW();
		Motor2_Rotate_CW();
		Motor3_Rotate_CW();
		Motor4_Rotate_CW();




}
void Car_Stop(void)
{
    /*Stopping the PWM generation on both motors*/
	HAL_TIM_PWM_Stop(Motor1_Timer, Motor1_Channel);
	HAL_TIM_PWM_Stop(Motor2_Timer, Motor2_Channel);
	HAL_TIM_PWM_Stop(Motor3_Timer, Motor3_Channel);
	HAL_TIM_PWM_Stop(Motor4_Timer, Motor4_Channel);
	/*Disabling both motors*/
	Motors_Disabling();

}
static void Motors_Disabling(void)
{
	HAL_GPIO_WritePin(Motor1_Port, IN1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Motor1_Port, IN2, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Motor2_Port, IN3, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Motor2_Port, IN4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Motor3_Port, IN5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Motor3_Port, IN6, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Motor4_Port, IN7, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Motor4_Port, IN8, GPIO_PIN_RESET);
}
 void Motor1_Rotate_CW(void)
{

	HAL_GPIO_WritePin(Motor1_Port,IN1, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Motor1_Port,IN2, GPIO_PIN_RESET);
}
 void Motor1_Rotate_CCW(void)
{
	HAL_GPIO_WritePin(Motor1_Port,IN1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Motor1_Port,IN2, GPIO_PIN_SET);
}
void Motor2_Rotate_CW(void)
{

	HAL_GPIO_WritePin(Motor2_Port,IN3, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Motor2_Port,IN4, GPIO_PIN_RESET);
}
void Motor2_Rotate_CCW(void)
{
	HAL_GPIO_WritePin(Motor2_Port,IN3, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Motor2_Port,IN4, GPIO_PIN_SET);
}




 void Motor3_Rotate_CW(void)
{

	HAL_GPIO_WritePin(Motor3_Port,IN5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Motor3_Port,IN6, GPIO_PIN_SET);
}
 void Motor3_Rotate_CCW(void)
{
	HAL_GPIO_WritePin(Motor3_Port,IN5, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Motor3_Port,IN6, GPIO_PIN_RESET);
}



 void Motor4_Rotate_CW(void)
{

	HAL_GPIO_WritePin(Motor4_Port,IN7, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Motor4_Port,IN8, GPIO_PIN_SET);
}
 void Motor4_Rotate_CCW(void)
{
	HAL_GPIO_WritePin(Motor4_Port,IN7, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Motor4_Port,IN8, GPIO_PIN_RESET);
}
