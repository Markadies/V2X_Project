/*
 * calculateSpeed.c
 *
 *  Created on: Feb 21, 2024
 *      Author: GP team
 */
#include "calculateSpeed.h"
#include "LCD_I2C.h"

extern uint32_t edges_counter;

float Calculate_Car_Speed()
{
	float Local_uint16Speed;
	Local_uint16Speed = (edges_counter * 360 /50) * 2 * 3.14 * 0.03;
	Local_uint16Speed = Local_uint16Speed * 3.6 ;
	edges_counter=0;
	return Local_uint16Speed;
}





























