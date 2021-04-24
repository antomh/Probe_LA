/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "utils.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

////--------------------------------------------------------------------------
//#define FLASH_TABLE_START_ADDR		ADDR_FLASH_PAGE_127
//#define FLASH_TABLE_STOP_ADDR		FLASH_TABLE_START_ADDR+FLASH_PAGE_SIZE
////--------------------------------------------------------------------------
//#define MAGIC_KEY_DEFINE			0x48151623
//#define HARDWIRE_DEFINE 			0x06
//#define FIRMWARE_DEFINE 			0x05
//#define SN_DEFINE 					0x1121001
////--------------------------------------------------------------------------
//#define MAX_VAL_M12 				88//	шаг 0,2В в диапозоне [-5:12:0,2] 85  TODO:найти что за 3 значения?!
//#define MAX_VAL_M27 				163//	шаг 0,2В в диапозоне [-30:30:0,2] 163*0.2= 32,6
////--------------------------------------------------------------------------
//
//	typedef struct // 							4+4+4+176+176+326+326 = 1016 байт
//	{
//		uint16_t Hardwire; //					2 байта
//		uint16_t Firmware; //					2 байта
//		uint32_t SN; //							4 байта
//
//		uint32_t MagicNum; //0x4815162342		4 байта ==>4+4+2+2 = 12
//
//		uint16_t dacValA_m12[MAX_VAL_M12]; //	88*2 = 176 байта
//		uint16_t dacValB_m12[MAX_VAL_M12]; //	88*2 = 176 байта
//		uint16_t dacValA_m27[MAX_VAL_M27]; //	163*2 = 326 байта
//		uint16_t dacValB_m27[MAX_VAL_M27]; //	163*2 = 326 байта ==> 1004 + 12 = 1016
//
//	} Table_t;
//
//	struct FLASH_Sector {
//		uint32_t data[256 - 2]; // 	254* 4 = 1016 байта (1016 байт)
//		uint32_t NWrite; //			4 байта
//		uint32_t CheckSum; //		4 байта ==>1016 + 4 + 4 = 1024
//	};
//
//	union NVRAM {
//		Table_t calibration_table; //			1016 байт
//		struct FLASH_Sector sector; //			1024 байт
//
//		uint32_t data32[256]; // 			1024 байт
//		uint8_t data16[256 * 2]; // 		1024 байт
//		uint8_t data8[256 * 4]; // 			1024 байт
//	};
//	//										1024 байт
//
////--------------------------------------------------------------------------
//	union NVRAM DevNVRAM;

//--------------------------------------------------------------------------
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

//--------------------------------------------------------------------------
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void SetDacA(uint16_t);
void SetDacB(uint16_t);
void SetAllDAC();

uint16_t GetDacA();
uint16_t GetDacB();
uint16_t GetADC();
uint8_t GetBtnRunState();
uint8_t GetBtnUpState();
uint8_t GetBtnDownState();

uint8_t GetInHL();
uint8_t GetInLL();
void ResInHL();
void ResInLL();

void EnableTIM3_PB4();
void resValTIM3_PB4();

void EnableTIM4_PB6();
void resValTIM4_PB6();

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define AD5312_LDAC_Pin GPIO_PIN_1
#define AD5312_LDAC_GPIO_Port GPIOA
#define Relay_Pin GPIO_PIN_2
#define Relay_GPIO_Port GPIOA
#define AD5312_SYNC_Pin GPIO_PIN_4
#define AD5312_SYNC_GPIO_Port GPIOA
#define AD5312_SCLK_Pin GPIO_PIN_5
#define AD5312_SCLK_GPIO_Port GPIOA
#define AD5312_DIN_Pin GPIO_PIN_7
#define AD5312_DIN_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
