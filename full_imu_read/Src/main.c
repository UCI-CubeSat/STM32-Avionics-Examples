#include "imu_lib.h"
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
I2C_HandleTypeDef hi2c1;

int _write(int file, char *ptr, int len) {
	for(int i = 0; i < len; i++) {
		ITM_SendChar(*ptr++);
	}
	return len;
}

int main(void)
{
	HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();
    MX_I2C1_Init();

    struct Sensor_I2C fxas2100c = {.hi2c1 = &hi2c1, .i2c_addr = FXAS2100C_ADDR};
    struct Sensor_I2C fxos8700 = {.hi2c1 = &hi2c1, .i2c_addr = FXOS8700_ADDR};
    double gx,gy,gz;
    double ax,ay,az;
    double mx,my,mz;

    printf("Configuring Sensors\n");
    configure_gyroscope(&fxas2100c, 0x02, 0x0E, 0x00, 0x00);
    configure_accelerometer(&fxos8700, 0x01, 0x15, 0x02, 0x00, 0x00, 0x00);
    configure_magnetometer(&fxos8700, 0x1F, 0x20, 0x00);
    HAL_Delay(1000);
    printf("Done Configuring Sensors\n");

    while (1)
    {
    	read_gyroscope(&fxas2100c, GYRO_SENSITIVITY_500DPS, &gx, &gy, &gz);
    	read_accelerometer(&fxos8700, ACCEL_RANGE_4G * GRAVITY_CONST, &ax, &ay, &az);
    	read_magnetometer(&fxos8700, MAG_TO_uTESLA, &mx, &my, &mz);

    	printf("Gyro Data in DPS	Accel Data in G		Mag Data in uTeslas\n");
    	printf("GX: %.3f	GY: %.3f	GZ: %.3f\n", gx, gy, gz);
    	printf("AX: %.3f	AY: %.3f	GZ: %.3f\n", ax, ay, az);
    	printf("MX: %.3f	MY: %.3f	MZ: %.3f\n", mx, my, mz);
    	HAL_Delay(1000);
    }
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_I2C1_Init(void)
{

  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

}

static void MX_GPIO_Init(void)
{

  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

}


void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
}
#endif
