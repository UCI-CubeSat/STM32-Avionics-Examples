#include <nxp_fxos8700.h>

void fxos8700_init(I2C_HandleTypeDef* hi2c1)
{
	printf("Setting up FXOS8700\n");
	HAL_StatusTypeDef ret[5];
	/* Set to standby mode (required to make changes to this register) */
	ret[0] = i2c_transmit(hi2c1, FXOS8700_ADDRESS, FXOS8700_REGISTER_CTRL_REG1, 0x00);
	/* High resolution */
	ret[1] = i2c_transmit(hi2c1, FXOS8700_ADDRESS, FXOS8700_REGISTER_CTRL_REG2, 0x02);
	/* Active, Normal Mode, Low Noise, 100Hz in Hybrid Mode */
	ret[2] = i2c_transmit(hi2c1, FXOS8700_ADDRESS, FXOS8700_REGISTER_CTRL_REG1, 0x15);

	/* Configure the magnetometer */
	/* Hybrid Mode, Over Sampling Rate = 16 */
	ret[3] = i2c_transmit(hi2c1, FXOS8700_ADDRESS, FXOS8700_REGISTER_MCTRL_REG1, 0x1F);
	/* Jump to reg 0x33 after reading 0x06 */
	ret[4] = i2c_transmit(hi2c1, FXOS8700_ADDRESS, FXOS8700_REGISTER_MCTRL_REG2, 0x20);

	if (ret[0] == ret[1] == ret[2] == ret[3] == ret[4] == HAL_OK) printf("Configuration went well with FXOS8700\n");
	else printf("Something is wrong with FXOS8700\n");
	HAL_Delay(100);
	printf("Done Setting up FXOS8700\n");
}

void poll_accel_mag(I2C_HandleTypeDef* hi2c1, struct AccelerometerData* accel, struct MagnetometerData* mag)
{
	uint8_t buffer[12];
	HAL_StatusTypeDef ret;
	ret = i2c_read(hi2c1, FXOS8700_ADDRESS, FXOS8700_REGISTER_STATUS+1, buffer, 12);
	if (ret != HAL_OK) printf("Polling FXOS8700 did not work\n");

	accel->x = (double)((int16_t)((buffer[1] << 8) | buffer[2]) >> 2) * ACCEL_MG_LSB_2G;
	accel->y = (double)((int16_t)((buffer[3] << 8) | buffer[4]) >> 2) * ACCEL_MG_LSB_2G;
	accel->z = (double)((int16_t)((buffer[5] << 8) | buffer[6]) >> 2) * ACCEL_MG_LSB_2G;

	mag->x = (double)((int16_t)((buffer[7] << 8) | buffer[8])) * MAG_UT_LSB;
	mag->y = (double)((int16_t)((buffer[9] << 8) | buffer[10])) * MAG_UT_LSB;
	mag->z = (double)((int16_t)((buffer[11] << 8) | buffer[12])) * MAG_UT_LSB;
}
