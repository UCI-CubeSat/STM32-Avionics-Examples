#ifndef NXP_IMU_H
#define NXP_IMU_H

#include "main.h"
#include <nxp_fxos8700.h>
#include <nxp_fxas21002c.h>

struct IMU
{
	I2C_HandleTypeDef* hi2c;
	struct AccelerometerData accel;
	struct MagnetometerData mag;
	struct GyroscopeData gyro;
};

void read_imu(struct IMU* imu);

#endif
