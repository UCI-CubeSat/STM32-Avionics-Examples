#include <uart_lib.h>
#include "string.h"
HAL_StatusTypeDef uart_transmit(UART_HandleTypeDef* huart, char* msg_ptr)
{
	HAL_StatusTypeDef ret;
	ret = HAL_UART_Transmit(huart, (uint8_t *) msg_ptr, strlen(msg_ptr), HAL_MAX_DELAY);
	return ret;
}
