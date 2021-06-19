#ifndef IMU_LIB_H
#define IMU_LIB_H

#include "main.h"

//accelerometer/magnetometer
#define FXOS8700_ADDR 0x1F

#define ACCEL_XYZ_CONFIG_ADDR 0x0E
#define ACCEL_CTRL_REG1 0x2A
#define ACCEL_CTRL_REG2 0x2B
#define ACCEL_CTRL_REG3 0x2C
#define ACCEL_CTRL_REG4 0x2D
#define ACCEL_CTRL_REG5 0x2E

#define MAG_CTRL_REG1 0x5B
#define MAG_CTRL_REG2 0x5C
#define MAG_CTRL_REG3 0x5D

#define ACCEL_OUTX_MSB_ADDR 0x39
#define ACCEL_OUTX_LSB_ADDR 0x3A
#define ACCEL_OUTY_MSB_ADDR 0x3B
#define ACCEL_OUTY_LSB_ADDR 0x3C
#define ACCEL_OUTZ_MSB_ADDR 0x3D
#define ACCEL_OUTZ_LSB_ADDR 0x3E

#define MAG_OUTX_MSB_ADDR 0x33
#define MAG_OUTX_LSB_ADDR 0x34
#define MAG_OUTY_MSB_ADDR 0x35
#define MAG_OUTY_LSB_ADDR 0x36
#define MAG_OUTZ_MSB_ADDR 0x37
#define MAG_OUTZ_LSB_ADDR 0x38

#define ACCEL_RANGE_2G 0.000244
#define ACCEL_RANGE_4G 0.000488
#define ACCEL_RANGE_8G 0.000976

#define GRAVITY_CONST 9.80665 // 1g in m/s^2

#define ACCEL_CTRL_RANGE_2G 0x00
#define ACCEL_CTRL_RANGE_4G 0x01
#define ACCEL_CTRL_RANGE_8G 0x02

#define MAG_TO_uTESLA 0.1

//gyroscope
#define FXAS2100C_ADDR 0x21

#define GYRO_CTRL_REG0 0x0D //ctrl set full scale range of gyro
#define GYRO_CTRL_REG1 0x13 //ctrl set operating mode of gyro
#define GYRO_CTRL_REG2 0x14 //ctrl set
#define GYRO_CTRL_REG3 0x15 //ctrl FSR expansion and auto-increment address

//read bytes MSB/LSB
#define GYRO_OUTX_MSB_ADDR 0x01
#define GYRO_OUTX_LSB_ADDR 0x02
#define GYRO_OUTY_MSB_ADDR 0x03
#define GYRO_OUTY_LSB_ADDR 0x04
#define GYRO_OUTZ_MSB_ADDR 0x05
#define GYRO_OUTZ_LSB_ADDR 0x06

#define GYRO_SENSITIVITY_2500DPS 0.0078125
#define GYRO_SENSITIVITY_500DPS 0.015625
#define GYRO_SENSITIVITY_1000DPS 0.03125
#define GYRO_SENSITIVITY_2000DPS 0.0625

#define GYRO_RANGE_2500DPS 250
#define GYRO_RANGE_500DPS 500
#define GYRO_RANGE_1000DPS 1000
#define GYRO_RANGE_2000DPS 2000

#define GYRO_CTRL_RANGE_2000DPS 0x00
#define GYRO_CTRL_RANGE_1000DPS 0x01
#define GYRO_CTRL_RANGE_500DPS 0x02
#define GYRO_CTRL_RANGE_250DPS 0x03

struct Sensor_I2C
{
	I2C_HandleTypeDef* hi2c1;
	uint8_t i2c_addr;
};


void configure_gyroscope(struct Sensor_I2C* sensor, uint8_t reg0, uint8_t reg1, uint8_t reg2, uint8_t reg3);
void configure_accelerometer(struct Sensor_I2C* sensor, uint8_t reg0, uint8_t reg1, uint8_t reg2, uint8_t reg3, uint8_t reg4, uint8_t reg5);
void configure_magnetometer(struct Sensor_I2C* sensor, uint8_t reg1, uint8_t reg2, uint8_t reg3);


void calibrate_gyroscope(struct Sensor_I2C* sensor, double conversion, double* calib_gx, double* calib_gy, double* calib_gz);
void calibrate_accelerometer(struct Sensor_I2C* sensor, double conversion, double* calib_ax, double* calib_ay, double* calib_az);
void calibrate_magnetometer(struct Sensor_I2C* sensor, double conversion, double* calib_mx, double* calib_my, double* calib_mz);

void read_gyroscope(struct Sensor_I2C* sensor, double conversion, double* gx, double* gy, double* gz);
void read_accelerometer(struct Sensor_I2C* sensor, double conversion, double* ax, double* gy, double* gz);
void read_magnetometer(struct Sensor_I2C* sensor, double conversion, double* mx, double* my, double* mz);

#endif
