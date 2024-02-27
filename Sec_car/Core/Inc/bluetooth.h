/*
 * Buzzer.h
 *
 *  Created on: Dec 24, 2023
 *      Author: Abdelrahman osama
 */

#include "stm32f4xx_hal.h"

extern UART_HandleTypeDef huart3;

uint8_t recieveBluetooth(uint8_t *charRecieved);
