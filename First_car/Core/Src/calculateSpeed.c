/*
 * calculateSpeed.c
 *
 *  Created on: Feb 21, 2024
 *      Author: abdelrahman
 */
#include "calculateSpeed.h"

extern uint32_t edges_counter;

float Calculate_Car_Speed()
{
	float Local_uint16Speed;
	Local_uint16Speed = (edges_counter * 360 /50) * 2 * 3.14 * 0.03;
	edges_counter=0;
	return Local_uint16Speed;
}





























