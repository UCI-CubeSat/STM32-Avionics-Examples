#include "imu_lib.h"

HAL_StatusTypeDef read_i2c(struct Sensor_I2C* sensor, uint8_t reg_addr, uint8_t* buffer, int reg_length, int message_size)
{
	HAL_StatusTypeDef ret;

	for(int i = 0; i < reg_length; i++) {
		*(buffer+i) = reg_addr+i;
	}

	ret = HAL_I2C_Master_Transmit(sensor->hi2c1, sensor->i2c_addr << 1, buffer, reg_length, HAL_MAX_DELAY);
	if (ret != HAL_OK)
	{
		printf("Cannot Read\n");
		return ret;
	}

	ret = HAL_I2C_Master_Receive(sensor->hi2c1, (sensor->i2c_addr << 1), buffer, message_size, HAL_MAX_DELAY);

	return ret;
}

void configure_gyroscope(struct Sensor_I2C* sensor, uint8_t reg0, uint8_t reg1, uint8_t reg2, uint8_t reg3) //configure gyroscope sensor
{
	//passes sensor and reg arguments from 0-3 for the configuration of sensor
	/*
		reg0: Full Scale Range, SPI Mode Selection, High Pass Filter Setting
		reg1: Operating mode, ODR Selection, Self-test, and soft-reset
		reg2: Interrupt Configuration Setting
		reg3: Auto-Increment Address Configuration, External Power Control, FSR Expansion
	*/
	uint8_t ctrl_arg = reg0;
	HAL_I2C_Mem_Write(sensor->hi2c1, FXAS2100C_ADDR << 1, GYRO_CTRL_REG0, 1, &ctrl_arg, 1 , HAL_MAX_DELAY);
	ctrl_arg = reg1;
	HAL_I2C_Mem_Write(sensor->hi2c1, FXAS2100C_ADDR << 1, GYRO_CTRL_REG1, 1, &ctrl_arg, 1, HAL_MAX_DELAY);
	ctrl_arg = reg2;
	HAL_I2C_Mem_Write(sensor->hi2c1, FXAS2100C_ADDR << 1, GYRO_CTRL_REG2, 1, &ctrl_arg, 1, HAL_MAX_DELAY);
	ctrl_arg = reg3;
	HAL_I2C_Mem_Write(sensor->hi2c1, FXAS2100C_ADDR << 1, GYRO_CTRL_REG3, 1, &ctrl_arg, 1, HAL_MAX_DELAY);
}

void configure_accelerometer(struct Sensor_I2C* sensor, uint8_t reg0, uint8_t reg1, uint8_t reg2, uint8_t reg3, uint8_t reg4, uint8_t reg5) //configure accel sensor
{
	//passes sensor and reg arguments from 1-5 for the configuration of sensor
	/*
	 	 reg0: xyz register for FSR
	 	 reg1: System ODR, Accelerometer OSR, Operating Mode
	 	 reg2: Self-test, reset, acccelerometer OSR and sleep mode
	 	 reg3: Sleep mode interrupt wake enable, interrupt polarity, push-pull/open-drain configuration
	 	 reg4: Interrupt enable register
	 	 reg5: Interrupt Pin (INT1/INT2) map
	*/

	uint8_t ctrl_arg = reg0;
	HAL_I2C_Mem_Write(sensor->hi2c1, FXOS8700_ADDR << 1, ACCEL_XYZ_CONFIG_ADDR, 1, &ctrl_arg, 1, HAL_MAX_DELAY);
	ctrl_arg = reg1;
	HAL_I2C_Mem_Write(sensor->hi2c1, FXOS8700_ADDR << 1, ACCEL_CTRL_REG1, 1, &ctrl_arg, 1, HAL_MAX_DELAY);
	ctrl_arg = reg2;
	HAL_I2C_Mem_Write(sensor->hi2c1, FXOS8700_ADDR << 1, ACCEL_CTRL_REG2, 1, &ctrl_arg, 1, HAL_MAX_DELAY);
	ctrl_arg = reg3;
	HAL_I2C_Mem_Write(sensor->hi2c1, FXOS8700_ADDR << 1, ACCEL_CTRL_REG3, 1, &ctrl_arg, 1, HAL_MAX_DELAY);
	ctrl_arg = reg4;
	HAL_I2C_Mem_Write(sensor->hi2c1, FXOS8700_ADDR << 1, ACCEL_CTRL_REG4, 1, &ctrl_arg, 1, HAL_MAX_DELAY);
	ctrl_arg = reg5;
	HAL_I2C_Mem_Write(sensor->hi2c1, FXOS8700_ADDR << 1, ACCEL_CTRL_REG5, 1, &ctrl_arg, 1, HAL_MAX_DELAY);
}

void configure_magnetometer(struct Sensor_I2C* sensor, uint8_t reg1, uint8_t reg2, uint8_t reg3)
{
	uint8_t ctrl_arg = reg1;
	HAL_I2C_Mem_Write(sensor->hi2c1, FXOS8700_ADDR << 1, MAG_CTRL_REG1, 1, &ctrl_arg, 1, HAL_MAX_DELAY);
	ctrl_arg = reg2;
	HAL_I2C_Mem_Write(sensor->hi2c1, FXOS8700_ADDR << 1, MAG_CTRL_REG2, 1, &ctrl_arg, 1, HAL_MAX_DELAY);
	ctrl_arg = reg3;
	HAL_I2C_Mem_Write(sensor->hi2c1, FXOS8700_ADDR << 1, MAG_CTRL_REG3, 1, &ctrl_arg, 1, HAL_MAX_DELAY);

}

void calibrate_gyroscope(struct Sensor_I2C* sensor, double conversion, double* calib_gx, double* calib_gy, double* calib_gz)
{
	double read_gx, read_gy, read_gz;
	for (int i = 0; i < 100; i++)
	{
		read_gyroscope(sensor, conversion, &read_gx, &read_gy, &read_gz);
		*calib_gx += read_gx;
		*calib_gy += read_gy;
		*calib_gz += read_gz;
		HAL_Delay(20);
	}
	*calib_gx /= 100;
	*calib_gy /= 100;
	*calib_gz /= 100;
}
void calibrate_accelerometer(struct Sensor_I2C* sensor, double conversion, double* calib_ax, double* calib_ay, double* calib_az)
{
	double read_ax, read_ay, read_az;
	for (int i = 0; i < 100; i++)
	{
		read_gyroscope(sensor, conversion, &read_ax, &read_ay, &read_az);
		*calib_ax += read_ax;
		*calib_ay += read_ay;
		*calib_az += read_az;
		HAL_Delay(20);
	}
	*calib_ax /= 100;
	*calib_ay /= 100;
	*calib_az /= 100;
}
void calibrate_magnetometer(struct Sensor_I2C* sensor, double conversion, double* calib_mx, double* calib_my, double* calib_mz)
{
	double read_mx, read_my, read_mz;
	for (int i = 0; i < 100; i++)
	{
		read_gyroscope(sensor, conversion, &read_mx, &read_my, &read_mz);
		*calib_mx += read_mx;
		*calib_my += read_my;
		*calib_mz += read_mz;
		HAL_Delay(20);
	}
	*calib_mx /= 100;
	*calib_my /= 100;
	*calib_mz /= 100;
}

void read_gyroscope(struct Sensor_I2C* sensor, double conversion,  double* gx, double* gy, double* gz)
{
	int raw_gx, raw_gy, raw_gz;
	uint8_t buffer[6] = {0,0,0,0,0,0}; //if possible, try to implement burst reading

	read_i2c(sensor, GYRO_OUTX_MSB_ADDR, buffer, 2, 2);
	raw_gx = ((int)buffer[0] << 8) | buffer[1];

	read_i2c(sensor, GYRO_OUTY_MSB_ADDR, buffer, 2, 2);
	raw_gy = ((int)buffer[0] << 8) | buffer[1];

	read_i2c(sensor, GYRO_OUTZ_MSB_ADDR, buffer, 2, 2);
	raw_gz = ((int)buffer[0] << 8) | buffer[1];

	if (raw_gx >= 0x8000) raw_gx -= 0x10000;
	if (raw_gy >= 0x8000) raw_gy -= 0x10000;
	if (raw_gz >= 0x8000) raw_gz -= 0x10000;

	*gx = raw_gx * conversion;
	*gy = raw_gy * conversion;
	*gz = raw_gz * conversion;
}
void read_accelerometer(struct Sensor_I2C* sensor, double conversion, double* ax, double* ay, double* az)
{
	int raw_ax, raw_ay, raw_az;
	uint8_t buffer[6] = {0,0,0,0,0,0};
	read_i2c(sensor, ACCEL_OUTX_MSB_ADDR, buffer, 2, 2);
	raw_ax = ((int)buffer[0] << 6) | buffer[1];

	read_i2c(sensor, ACCEL_OUTY_MSB_ADDR, buffer, 2, 2);
	raw_ay = ((int)buffer[0] << 6) | buffer[1];

	read_i2c(sensor, ACCEL_OUTZ_MSB_ADDR, buffer, 2 ,2);
	raw_az = ((int)buffer[0] << 6) | buffer[1];

	if (raw_ax >= 0x2000) raw_ax -= 0x4000;
	if (raw_ay >= 0x2000) raw_ay -= 0x4000;
	if (raw_az >= 0x2000) raw_az -= 0x4000;

	*ax = raw_ax * conversion;
	*ay = raw_ay * conversion;
	*az = raw_az * conversion;
}
void read_magnetometer(struct Sensor_I2C* sensor, double conversion, double* mx, double* my, double* mz)
{
	int raw_mx, raw_my, raw_mz;
	uint8_t buffer[6] = {0,0,0,0,0,0};
	read_i2c(sensor, MAG_OUTX_MSB_ADDR, buffer, 2, 2);
	raw_mx = ((int)buffer[0] << 8) | buffer[1];

	read_i2c(sensor, MAG_OUTY_MSB_ADDR, buffer, 2, 2);
	raw_my = ((int)buffer[0] << 8) | buffer[1];

	read_i2c(sensor, MAG_OUTZ_MSB_ADDR, buffer, 2 ,2);
	raw_mz = ((int)buffer[0] << 8) | buffer[1];

	if (raw_mx >= 0x8000) raw_mx -= 0x10000;
	if (raw_my >= 0x8000) raw_my -= 0x10000;
	if (raw_mz >= 0x8000) raw_mz -= 0x10000;

	*mx = raw_mx * conversion;
	*my = raw_my * conversion;
	*mz = raw_mz * conversion;
}

