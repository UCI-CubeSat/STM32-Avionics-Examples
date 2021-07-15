#include <nxp_fxas21002c.h>

void fxas21002c_init(I2C_HandleTypeDef* hi2c1)
{
	//this is set to 250 dps
	HAL_StatusTypeDef ret[4];
	printf("Setting up FXAS21002C\n");
	ret[0] = i2c_transmit(hi2c1, FXAS21002C_ADDRESS, GYRO_REGISTER_CTRL_REG1, 0x00); //standby
	ret[1] = i2c_transmit(hi2c1, FXAS21002C_ADDRESS, GYRO_REGISTER_CTRL_REG1, 1 << 6); //reset
	ret[2] = i2c_transmit(hi2c1, FXAS21002C_ADDRESS, GYRO_REGISTER_CTRL_REG0, 0x03); //set sensitivity
	ret[3] = i2c_transmit(hi2c1, FXAS21002C_ADDRESS, GYRO_REGISTER_CTRL_REG1, 0x0E); //active
	HAL_Delay(100);

	if (ret[0] == ret[1] == ret[2] == ret[3] == HAL_OK) printf("Configuration went well with FXAS21002C\n");
	else printf("Something is wrong with FXOS21002C\n");

	printf("Done Setting up FXAS21002C\n");
}

void poll_gyro(I2C_HandleTypeDef* hi2c1, struct GyroscopeData* gyro)
{
	uint8_t buffer[6];
	HAL_StatusTypeDef ret;
	ret = i2c_read(hi2c1, FXAS21002C_ADDRESS, GYRO_REGISTER_STATUS+1, buffer, 6);

	if (ret != HAL_OK) printf("Polling FXOS21002C did not work\n");
	gyro->x = (double)((int16_t)((buffer[1] << 8) | buffer[2])) * GYRO_SENSITIVITY_250DPS;
	gyro->y = (double)((int16_t)((buffer[3] << 8) | buffer[4])) * GYRO_SENSITIVITY_250DPS;
	gyro->z = (double)((int16_t)((buffer[5] << 8) | buffer[6])) * GYRO_SENSITIVITY_250DPS;
}
