#include "bluetooth.h"

uint8_t recieveBluetooth(uint8_t *charRecieved)
{
//	uint8_t charRecieved
	HAL_UART_Receive_IT(&huart3, charRecieved, 1);
//	return charRecieved;
}
