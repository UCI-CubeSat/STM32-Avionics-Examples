#ifndef NXP_FXAS21002C_H
#define NXP_FXAS21002C_H

#include <i2c_lib.h>


typedef enum {
  GYRO_REGISTER_STATUS = 0x00,    /**< 0x00 */
  GYRO_REGISTER_OUT_X_MSB = 0x01, /**< 0x01 */
  GYRO_REGISTER_OUT_X_LSB = 0x02, /**< 0x02 */
  GYRO_REGISTER_OUT_Y_MSB = 0x03, /**< 0x03 */
  GYRO_REGISTER_OUT_Y_LSB = 0x04, /**< 0x04 */
  GYRO_REGISTER_OUT_Z_MSB = 0x05, /**< 0x05 */
  GYRO_REGISTER_OUT_Z_LSB = 0x06, /**< 0x06 */
  GYRO_REGISTER_WHO_AM_I =
      0x0C, /**< 0x0C (default value = 0b11010111, read only) */
  GYRO_REGISTER_CTRL_REG0 =
      0x0D, /**< 0x0D (default value = 0b00000000, read/write) */
  GYRO_REGISTER_CTRL_REG1 =
      0x13, /**< 0x13 (default value = 0b00000000, read/write) */
  GYRO_REGISTER_CTRL_REG2 =
      0x14, /**< 0x14 (default value = 0b00000000, read/write) */
} gyroRegisters_t;

typedef enum {
  GYRO_RANGE_250DPS = 250,   /**< 250dps */
  GYRO_RANGE_500DPS = 500,   /**< 500dps */
  GYRO_RANGE_1000DPS = 1000, /**< 1000dps */
  GYRO_RANGE_2000DPS = 2000  /**< 2000dps */
} gyroRange_t;

#define FXAS21002C_ADDRESS (0x21)

/** Device ID for this sensor (used as a sanity check during init) */
#define FXAS21002C_ID (0xD7) // 1101 0111
/** Gyroscope sensitivity at 250dps */
#define GYRO_SENSITIVITY_250DPS (0.0078125F) // Table 35 of datasheet
/** Gyroscope sensitivity at 500dps */
#define GYRO_SENSITIVITY_500DPS (0.015625F)
/** Gyroscope sensitivity at 1000dps */
#define GYRO_SENSITIVITY_1000DPS (0.03125F)
/** Gyroscope sensitivity at 2000dps */
#define GYRO_SENSITIVITY_2000DPS (0.0625F)

struct GyroscopeData
{
	double x;
	double y;
	double z;
};


void fxas21002c_init(I2C_HandleTypeDef* hi2c1);
void poll_gyro(I2C_HandleTypeDef* hi2c1, struct GyroscopeData* gyro);

#endif
