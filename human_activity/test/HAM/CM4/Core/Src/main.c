/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "app_x-cube-ai.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <stdio.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#ifndef HSEM_ID_0
#define HSEM_ID_0 (0U) /* HW semaphore 0*/
#endif
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

I2C_HandleTypeDef hi2c4;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* MPU6500 寄存器地址定义 */
#define MPU6500_ADDR 0xD0 // MPU6500的I2C地址 (0x68<<1)，若AD0接VCC则为0xD2
#define MPU6500_WHO_AM_I 0x75 // 身份寄存器
#define MPU6500_PWR_MGMT_1 0x6B // 电源管理寄存器1
#define MPU6500_PWR_MGMT_2 0x6C // 电源管理寄存器2
#define MPU6500_SMPLRT_DIV 0x19 // 采样率分频寄存器
#define MPU6500_CONFIG 0x1A // 配置寄存器
#define MPU6500_GYRO_CONFIG 0x1B // 陀螺仪配置寄存器
#define MPU6500_ACCEL_CONFIG 0x1C // 加速度计配置寄存器
#define MPU6500_ACCEL_CONFIG_2 0x1D // 加速度计配置寄存器2
#define MPU6500_INT_PIN_CFG 0x37 // 中断引脚配置寄存器
#define MPU6500_INT_ENABLE 0x38 // 中断使能寄存器

/* 数据寄存器 */
#define MPU6500_ACCEL_XOUT_H 0x3B // 加速度计X轴高字节
#define MPU6500_ACCEL_XOUT_L 0x3C // 加速度计X轴低字节
#define MPU6500_ACCEL_YOUT_H 0x3D // 加速度计Y轴高字节
#define MPU6500_ACCEL_YOUT_L 0x3E // 加速度计Y轴低字节
#define MPU6500_ACCEL_ZOUT_H 0x3F // 加速度计Z轴高字节
#define MPU6500_ACCEL_ZOUT_L 0x40 // 加速度计Z轴低字节
#define MPU6500_TEMP_OUT_H 0x41 // 温度高字节
#define MPU6500_TEMP_OUT_L 0x42 // 温度低字节
#define MPU6500_GYRO_XOUT_H 0x43 // 陀螺仪X轴高字节
#define MPU6500_GYRO_XOUT_L 0x44 // 陀螺仪X轴低字节
#define MPU6500_GYRO_YOUT_H 0x45 // 陀螺仪Y轴高字节
#define MPU6500_GYRO_YOUT_L 0x46 // 陀螺仪Y轴低字节
#define MPU6500_GYRO_ZOUT_H 0x47 // 陀螺仪Z轴高字节
#define MPU6500_GYRO_ZOUT_L 0x48 // 陀螺仪Z轴低字节

/* 量程配置 */
#define MPU6500_ACCEL_SCALE_2G 0x00 // ±2g
#define MPU6500_ACCEL_SCALE_4G 0x08 // ±4g
#define MPU6500_ACCEL_SCALE_8G 0x10 // ±8g
#define MPU6500_ACCEL_SCALE_16G 0x18 // ±16g

/* 数据类型定义 */
typedef struct {
float accel_x; // 加速度X轴 (单位: g)
float accel_y; // 加速度Y轴 (单位: g)
float accel_z; // 加速度Z轴 (单位: g)
} MPU6500_t;

/* 函数声明 */
uint8_t MPU6500_Init(void);
uint8_t MPU6500_ReadID(void);
uint8_t MPU6500_WriteReg(uint8_t reg, uint8_t data);
uint8_t MPU6500_ReadReg(uint8_t reg);
void MPU6500_ReadAccel(MPU6500_t *data);
void I2C_Scan(void);
HAL_StatusTypeDef MPU6500_TestConnection(void);
float accel_scale = 4096.0f; // 加速度计比例因子


MPU6500_t mpu_data; // 加速度数据结构体
uint8_t count = 0;
float data_mpu[72]; // 存储加速度数据的数组
uint8_t init_status = 0; // 初始化状态


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static void MX_MDMA_Init(void);
static void MX_GPIO_Init(void);
static void MX_I2C4_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

#ifdef __GNUC__									//串口重定向
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif
PUTCHAR_PROTOTYPE
{
    HAL_UART_Transmit(&huart1 , (uint8_t *)&ch, 1, 0xFFFF);
    return ch;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

/* USER CODE BEGIN Boot_Mode_Sequence_1 */
  /*HW semaphore Clock enable*/
  __HAL_RCC_HSEM_CLK_ENABLE();
  /* Activate HSEM notification for Cortex-M4*/
  HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_0));
  /*
  Domain D2 goes to STOP mode (Cortex-M4 in deep-sleep) waiting for Cortex-M7 to
  perform system initialization (system clock config, external memory configuration.. )
  */
  HAL_PWREx_ClearPendingEvent();
  HAL_PWREx_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFE, PWR_D2_DOMAIN);
  /* Clear HSEM flag */
  __HAL_HSEM_CLEAR_FLAG(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_0));

/* USER CODE END Boot_Mode_Sequence_1 */
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_MDMA_Init();
  MX_GPIO_Init();
  MX_I2C4_Init();
  MX_USART1_UART_Init();
  MX_X_CUBE_AI_Init();
  /* USER CODE BEGIN 2 */

  // 延迟等待系统稳定
  HAL_Delay(100);


  // 首先扫描I2C总线查看连接的设备
  I2C_Scan();

  // 尝试初始化MPU6500
  HAL_Delay(50); // 再次延迟确保I2C总线稳定
  init_status = MPU6500_Init();
  if (init_status != 0) {


  // 第二次尝试（这是因为有时首次初始化可能失败）
  HAL_Delay(100);
  init_status = MPU6500_Init();
  if (init_status != 0) {

  } else {

  }
  } else {

  }

  uint32_t last = HAL_GetTick();
  uint32_t now;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */


    /* USER CODE BEGIN 3 */

	  now = HAL_GetTick();

	  // 每100ms读取一次数据
	  if(now >= (last + 100))
	  {
	  last = now;

	  // 只有在初始化成功的情况下才读取数据
	  if (init_status == 0) {
	  // 读取加速度数据
	  MPU6500_ReadAccel(&mpu_data);

	  // 确认读取的数据在合理范围内
	  if (mpu_data.accel_x >= -10.0f && mpu_data.accel_x <= 10.0f &&
	  mpu_data.accel_y >= -10.0f && mpu_data.accel_y <= 10.0f &&
	  mpu_data.accel_z >= -10.0f && mpu_data.accel_z <= 10.0f) {
		  printf("Accel: X=%.2f g, Y=%.2f g, Z=%.2f g\r\n",
		                       mpu_data.accel_x, mpu_data.accel_y, mpu_data.accel_z);
	  // 存储数据到数组
	  if(count < 24) {
	  data_mpu[count*3] = -mpu_data.accel_x;
	  data_mpu[count*3+1] = -mpu_data.accel_y;
	  data_mpu[count*3+2] = mpu_data.accel_z;
	  count++;

	  // 当收集到24组数据时重置
	  if(count == 24) {
		  printf("AI data collection complete\r\n");
		  MX_X_CUBE_AI_Process();
		  count = 0;
	  // 这里可以添加处理数据的代码
	  }
	  }
	  } else {

	  }
	  } else {
	  // 如果初始化失败，每2秒再尝试初始化一次
	  static uint32_t retry_time = 0;
	  if (now >= retry_time + 2000) {
	  retry_time = now;

	  init_status = MPU6500_Init();
	  if (init_status == 0) {

	  }
	  }
	  }
	  }
  }
  /* USER CODE END 3 */
}

/**
  * @brief I2C4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C4_Init(void)
{

  /* USER CODE BEGIN I2C4_Init 0 */

  /* USER CODE END I2C4_Init 0 */

  /* USER CODE BEGIN I2C4_Init 1 */

  /* USER CODE END I2C4_Init 1 */
  hi2c4.Instance = I2C4;
  hi2c4.Init.Timing = 0x10C0ECFF;
  hi2c4.Init.OwnAddress1 = 0;
  hi2c4.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c4.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c4.Init.OwnAddress2 = 0;
  hi2c4.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c4.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c4.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c4) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c4, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c4, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C4_Init 2 */

  /* USER CODE END I2C4_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * Enable MDMA controller clock
  */
static void MX_MDMA_Init(void)
{

  /* MDMA controller clock enable */
  __HAL_RCC_MDMA_CLK_ENABLE();
  /* Local variables */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/**
* @brief 检查I2C总线上的所有设备
* @param 无
* @retval 无
*/
void I2C_Scan(void) {
uint8_t data;
uint8_t devices_found = 0;

for(uint8_t i = 1; i < 128; i++) {
// I2C地址是7位的，需要左移1位
uint16_t device_addr = (i << 1);

// 尝试读取数据，超时设为10ms
HAL_StatusTypeDef result = HAL_I2C_Master_Transmit(&hi2c4, device_addr, &data, 0, 10);

if(result == HAL_OK) {

devices_found++;
}
}
}

/**
* @brief 测试与MPU6500的连接
* @param 无
* @retval HAL状态
*/
HAL_StatusTypeDef MPU6500_TestConnection(void) {
uint8_t data = 0;
return HAL_I2C_Mem_Read(&hi2c4, MPU6500_ADDR, MPU6500_WHO_AM_I, I2C_MEMADD_SIZE_8BIT, &data, 1, 100);
}

/**
* @brief 初始化MPU6500
* @param 无
* @retval 0: 成功, 1: 失败
*/
uint8_t MPU6500_Init(void) {
uint8_t id;
uint8_t accel_range = MPU6500_ACCEL_SCALE_8G; // 默认±8g
HAL_StatusTypeDef status;

// 延迟等待MPU6500上电稳定
HAL_Delay(50);

// 测试I2C连接
status = MPU6500_TestConnection();
if (status != HAL_OK) {

return 1;
}

// 检查设备ID
id = MPU6500_ReadID();


// 检查是否为有效ID (MPU6500为0x70, MPU6050为0x68, 某些兼容芯片可能有不同的ID)
if (id != 0x70 && id != 0x68) {

// 尝试调整地址并再次读取

uint8_t temp;
if (HAL_I2C_Mem_Read(&hi2c4, 0xD2, MPU6500_WHO_AM_I, I2C_MEMADD_SIZE_8BIT, &temp, 1, 100) == HAL_OK) {

}
return 1;
}

// 复位MPU
MPU6500_WriteReg(MPU6500_PWR_MGMT_1, 0x80);
HAL_Delay(100); // 等待复位完成

// 唤醒MPU
MPU6500_WriteReg(MPU6500_PWR_MGMT_1, 0x00);
HAL_Delay(10); // 等待唤醒

// 设置时钟源为PLL with X axis gyroscope reference
MPU6500_WriteReg(MPU6500_PWR_MGMT_1, 0x01);
HAL_Delay(10);

// 设置加速度计量程为±8g
MPU6500_WriteReg(MPU6500_ACCEL_CONFIG, accel_range);

// 根据量程设置加速度计比例因子
switch(accel_range) {
case MPU6500_ACCEL_SCALE_2G:
accel_scale = 16384.0f; // 16384 LSB/g
break;
case MPU6500_ACCEL_SCALE_4G:
accel_scale = 8192.0f; // 8192 LSB/g
break;
case MPU6500_ACCEL_SCALE_8G:
accel_scale = 4096.0f; // 4096 LSB/g
break;
case MPU6500_ACCEL_SCALE_16G:
accel_scale = 2048.0f; // 2048 LSB/g
break;
}

// 设置采样率为1kHz
MPU6500_WriteReg(MPU6500_SMPLRT_DIV, 0x00);

// 设置数字低通滤波器
MPU6500_WriteReg(MPU6500_CONFIG, 0x03);

// 设置加速度计低通滤波器
MPU6500_WriteReg(MPU6500_ACCEL_CONFIG_2, 0x03);

// 使能所有轴
MPU6500_WriteReg(MPU6500_PWR_MGMT_2, 0x00);

return 0;
}

/**
* @brief 读取MPU6500的ID
* @param 无
* @retval ID值
*/
uint8_t MPU6500_ReadID(void) {
return MPU6500_ReadReg(MPU6500_WHO_AM_I);
}

/**
* @brief 读取MPU6500寄存器值
* @param reg: 寄存器地址
* @retval 寄存器值，如读取失败返回0xFF
*/
uint8_t MPU6500_ReadReg(uint8_t reg) {
uint8_t value = 0xFF;
HAL_StatusTypeDef status;

status = HAL_I2C_Mem_Read(&hi2c4, MPU6500_ADDR, reg, I2C_MEMADD_SIZE_8BIT, &value, 1, 100);

if (status != HAL_OK) {

}

return value;
}

/**
* @brief 写入MPU6500寄存器值
* @param reg: 寄存器地址
* @param data: 要写入的数据
* @retval 0: 成功，1: 失败
*/
uint8_t MPU6500_WriteReg(uint8_t reg, uint8_t data) {
HAL_StatusTypeDef status;

status = HAL_I2C_Mem_Write(&hi2c4, MPU6500_ADDR, reg, I2C_MEMADD_SIZE_8BIT, &data, 1, 100);

if (status != HAL_OK) {

return 1;
}

return 0;
}

/**
* @brief 读取加速度计数据并转换为g值
* @param data: 数据结构体指针
* @retval 无
*/
void MPU6500_ReadAccel(MPU6500_t *data) {
uint8_t buf[6];
int16_t raw_x, raw_y, raw_z;
HAL_StatusTypeDef status;

// 读取加速度计原始数据
status = HAL_I2C_Mem_Read(&hi2c4, MPU6500_ADDR, MPU6500_ACCEL_XOUT_H, I2C_MEMADD_SIZE_8BIT, buf, 6, 100);

if (status != HAL_OK) {

// 如果读取失败，设置为零
data->accel_x = 0.0f;
data->accel_y = 0.0f;
data->accel_z = 0.0f;
return;
}

// 组合高低字节成16位数据
raw_x = ((int16_t)buf[0] << 8) | buf[1];
raw_y = ((int16_t)buf[2] << 8) | buf[3];
raw_z = ((int16_t)buf[4] << 8) | buf[5];

// 转换为g值 (原始值/比例因子)
data->accel_x = (float)raw_x / accel_scale;
data->accel_y = (float)raw_y / accel_scale;
data->accel_z = (float)raw_z / accel_scale;
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
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
