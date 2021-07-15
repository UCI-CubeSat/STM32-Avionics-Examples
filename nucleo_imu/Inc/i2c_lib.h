#ifndef I2C_LIB_H
#define I2C_LIB_H
#include "main.h"

HAL_StatusTypeDef i2c_read(I2C_HandleTypeDef* hi2c1, uint8_t i2c_addr, uint8_t reg_addr, uint8_t* buffer, int message_size);
HAL_StatusTypeDef i2c_transmit(I2C_HandleTypeDef* hi2c1, uint8_t i2c_addr, uint8_t reg_addr, uint8_t message);

#endif
