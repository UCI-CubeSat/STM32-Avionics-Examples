#ifndef UART_LIB_H
#define UART_LIB_H
#include "main.h"

HAL_StatusTypeDef uart_transmit(UART_HandleTypeDef* huart, char* msg_ptr);

#endif
