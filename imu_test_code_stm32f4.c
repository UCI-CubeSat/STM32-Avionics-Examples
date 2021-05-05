#include "main.h"
#include "stdio.h"
I2C_HandleTypeDef hi2c1;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);

//forced to store 8-bits
#define FXOS8700_ADDR 0x1F
#define FXAS2100C_ADDR 0x21

#define CTRL_REG1_ADDR 0x13
/*
 * NOTE must burst all 6 registers of I2C to prevent loss of data for the gyro.
 * each axis is 16 bits.
 *
*/

/*
 * This is for requesting data from a register from i2c bus.
 * HAL_I2C_Master_Transmit(&hi2c1, (0x48) << 1 , &pdata, 1, HAL_MAX_delay);
 *
 * This is to receive data from a register in i2c bus.
 * HAL_I2C_Master_Receive(&hi2c1, (0x48) << 1, &pdata, message_length, HAL_MAX_Delay);
 *
 * This is to write into a register under i2c bus.
 * HAL_I2C_Mem_Write(&hi2c1, FXAS2100C_ADDR << 1, CTRL_REG1_ADDR, address length, &message, message length, HAL_MAX_DELAY);
 *
 * The _write function allows printf to work on SWV ITM Data Console.
 * This is for debugging when plugged into STM32F4.
 *
 *
 */

int _write(int file, char *ptr, int len) {
	for(int i = 0; i < len; i++) {
		ITM_SendChar(*ptr++);
	}
	return len;
}

HAL_StatusTypeDef read_i2c(uint8_t* buffer, uint8_t i2c_addr, uint8_t reg_addr, int reg_length, int size_message) {

	HAL_StatusTypeDef ret;

	for(int i = 0; i < reg_length; i++) {
		*(buffer+i) = reg_addr+i;
	}

	ret = HAL_I2C_Master_Transmit(&hi2c1, i2c_addr << 1, buffer, reg_length, HAL_MAX_DELAY);
	if (ret != HAL_OK) return ret;

	ret = HAL_I2C_Master_Receive(&hi2c1, (i2c_addr << 1), buffer, size_message, HAL_MAX_DELAY);

	return ret;
}

int main(void)
{
  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_I2C1_Init();

  uint8_t ctrl_buffer = 0x3;
  uint8_t buffer[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
  HAL_StatusTypeDef ret;
  printf("Hello World!\n");

  printf("Configuring Gyro.\n");
  //ret = HAL_I2C_Master_Transmit(&hi2c1, (FXAS2100C_ADDR << 1) | 0x01, ctrl_buffer, HAL_MAX_DELAY);
  HAL_I2C_Mem_Write(&hi2c1, FXAS2100C_ADDR << 1, CTRL_REG1_ADDR, 1, &ctrl_buffer, 1, HAL_MAX_DELAY);
  printf("Finished Configuring Gyro.\n");
  HAL_Delay(1000);

  while (1) {
	  ret = read_i2c(buffer, FXAS2100C_ADDR, 0x01, 6, 6);

	  if (ret != HAL_OK) { //if there is error in reading from i2c, print this to say that it didn't work.
		  printf("UHOH\n");
		  printf("UHOH\n");
	  }

	  printf("Reading Buffer: \n");
	  for(int i = 0; i < 12; i++) { //in this case, first 6 of the buffers should be reading.
		  printf("buffer[i]: %u\n", buffer[i]);
	  }
	  printf("\n\n");

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
  /** Initializes the CPU, AHB and APB buses clocks
  */
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

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
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

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

}

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
