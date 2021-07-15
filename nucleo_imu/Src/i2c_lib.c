#include <i2c_lib.h>
HAL_StatusTypeDef i2c_read(I2C_HandleTypeDef* hi2c1, uint8_t i2c_addr, uint8_t reg_addr, uint8_t* buffer, int message_size)
{
	HAL_StatusTypeDef ret;


	*buffer = reg_addr;

	ret = HAL_I2C_Master_Transmit(hi2c1, (uint16_t)(i2c_addr << 1), buffer, 1, HAL_MAX_DELAY);
	if (ret != HAL_OK)
	{
		printf("Transmission Wrong\n");
		return ret;
	}

	ret = HAL_I2C_Master_Receive(hi2c1, (uint16_t)(i2c_addr << 1) | 0x01, buffer, message_size, HAL_MAX_DELAY);
	if (ret != HAL_OK)
	{
		printf("Receiving Wrong\n");
		return ret;
	}

	return ret;
}

HAL_StatusTypeDef i2c_transmit(I2C_HandleTypeDef* hi2c1, uint8_t i2c_addr, uint8_t reg_addr, uint8_t message)
{
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Mem_Write(hi2c1, (uint16_t)(i2c_addr << 1), reg_addr, 1, &message, 1, HAL_MAX_DELAY);
	return ret;
}
