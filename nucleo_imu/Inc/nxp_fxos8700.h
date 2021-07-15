#ifndef NXP_FXOS8700_H
#define NXP_FXOS8700_H

#include <i2c_lib.h>

typedef enum {
  FXOS8700_REGISTER_STATUS = 0x00,    /**< 0x00 */
  FXOS8700_REGISTER_OUT_X_MSB = 0x01, /**< 0x01 */
  FXOS8700_REGISTER_OUT_X_LSB = 0x02, /**< 0x02 */
  FXOS8700_REGISTER_OUT_Y_MSB = 0x03, /**< 0x03 */
  FXOS8700_REGISTER_OUT_Y_LSB = 0x04, /**< 0x04 */
  FXOS8700_REGISTER_OUT_Z_MSB = 0x05, /**< 0x05 */
  FXOS8700_REGISTER_OUT_Z_LSB = 0x06, /**< 0x06 */
  FXOS8700_REGISTER_WHO_AM_I =
      0x0D, /**< 0x0D (default value = 0b11000111, read only) */
  FXOS8700_REGISTER_XYZ_DATA_CFG = 0x0E, /**< 0x0E */
  FXOS8700_REGISTER_CTRL_REG1 =
      0x2A, /**< 0x2A (default value = 0b00000000, read/write) */
  FXOS8700_REGISTER_CTRL_REG2 =
      0x2B, /**< 0x2B (default value = 0b00000000, read/write) */
  FXOS8700_REGISTER_CTRL_REG3 =
      0x2C, /**< 0x2C (default value = 0b00000000, read/write) */
  FXOS8700_REGISTER_CTRL_REG4 =
      0x2D, /**< 0x2D (default value = 0b00000000, read/write) */
  FXOS8700_REGISTER_CTRL_REG5 =
      0x2E, /**< 0x2E (default value = 0b00000000, read/write) */
  FXOS8700_REGISTER_MSTATUS = 0x32,    /**< 0x32 */
  FXOS8700_REGISTER_MOUT_X_MSB = 0x33, /**< 0x33 */
  FXOS8700_REGISTER_MOUT_X_LSB = 0x34, /**< 0x34 */
  FXOS8700_REGISTER_MOUT_Y_MSB = 0x35, /**< 0x35 */
  FXOS8700_REGISTER_MOUT_Y_LSB = 0x36, /**< 0x36 */
  FXOS8700_REGISTER_MOUT_Z_MSB = 0x37, /**< 0x37 */
  FXOS8700_REGISTER_MOUT_Z_LSB = 0x38, /**< 0x38 */
  FXOS8700_REGISTER_MCTRL_REG1 =
      0x5B, /**< 0x5B (default value = 0b00000000, read/write) */
  FXOS8700_REGISTER_MCTRL_REG2 =
      0x5C, /**< 0x5C (default value = 0b00000000, read/write) */
  FXOS8700_REGISTER_MCTRL_REG3 =
      0x5D, /**< 0x5D (default value = 0b00000000, read/write) */
} fxos8700Registers_t;

typedef enum {
  ACCEL_RANGE_2G = 0x00, /**< +/- 2g range */
  ACCEL_RANGE_4G = 0x01, /**< +/- 4g range */
  ACCEL_RANGE_8G = 0x02  /**< +/- 8g range */
} fxos8700AccelRange_t;



#define FXOS8700_ADDRESS 0x1F

/** Macro for mg per LSB at +/- 2g sensitivity (1 LSB = 0.000244mg) */
#define ACCEL_MG_LSB_2G (0.000244F)
/** Macro for mg per LSB at +/- 4g sensitivity (1 LSB = 0.000488mg) */
#define ACCEL_MG_LSB_4G (0.000488F)
/** Macro for mg per LSB at +/- 8g sensitivity (1 LSB = 0.000976mg) */
#define ACCEL_MG_LSB_8G (0.000976F)
/** Macro for micro tesla (uT) per LSB (1 LSB = 0.1uT) */
#define MAG_UT_LSB (0.1F)

struct AccelerometerData
{
	double x;
	double y;
	double z;
};

struct MagnetometerData
{
	double x;
	double y;
	double z;
};

void fxos8700_init(I2C_HandleTypeDef* hi2c1);
void poll_accel_mag(I2C_HandleTypeDef* hi2c1, struct AccelerometerData* accel, struct MagnetometerData* mag);

#endif
