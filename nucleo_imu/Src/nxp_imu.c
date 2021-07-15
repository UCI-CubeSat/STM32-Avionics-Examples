#include <nxp_imu.h>

void read_imu(struct IMU* imu)
{
	poll_accel_mag( imu->hi2c, &(imu->accel), &(imu->mag));
	poll_gyro( imu->hi2c, &(imu->gyro));
}
