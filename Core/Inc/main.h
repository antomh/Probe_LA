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

/* Это структура, как буффер для хранения значения принятых по USB данных.
 * Размер обусловлен размером одного пакета данных
 * + ещё одно поле, как маркер того, были ли уже прочитаны эти данные и
 * + ещё для занесения размера хранимого внутри этой переменной пакета.
 * И сразу же объявлю глобальную переменную этой структуры.
 * Все обновления полей этой структуры должны осуществляться в системной
 * функции получения данных через USB - CDC_Receive_FS, кроме поля is_read.*/
struct usb_rx_data {
    uint8_t is_read;
    uint8_t len;
    uint8_t buff[64];
};

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

enum RelState {     //RelayState =|1:m12|0:m27|
    m12 = 0x01,
    m27 = 0x00
};

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
//--------------------------------------------------------------------------
void SetDacA(int16_t da);
void SetDacB(int16_t db);
void SetAllDAC();
//--------------------------------------------------------------------------
uint16_t GetDacA();
uint16_t GetDacB();
uint16_t GetADC();
uint8_t GetBtnRunState();
uint8_t GetBtnUpState();
uint8_t GetBtnDownState();
//--------------------------------------------------------------------------
uint8_t GetInHL();
uint8_t GetInLL();
void ResInHL();
void ResInLL();
//--------------------------------------------------------------------------
void EnableTIM3_PB4();
void resValTIM3_PB4();

void EnableTIM4_PB6();
void resValTIM4_PB6();
//--------------------------------------------------------------------------
uint32_t getCRC_table_a_m12();
uint32_t getCRC_table_b_m12();
uint32_t getCRC_table_a_m27();
uint32_t getCRC_table_b_m27();

void writeTable();

uint16_t GetTIM3(void);
uint16_t GetTIM4(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define AD5312_LDAC_Pin         GPIO_PIN_1
#define AD5312_LDAC_GPIO_Port   GPIOA

#define Relay_Pin               GPIO_PIN_2
#define Relay_GPIO_Port         GPIOA

#define AD5312_SYNC_Pin         GPIO_PIN_4
#define AD5312_SYNC_GPIO_Port   GPIOA

#define AD5312_SCLK_Pin         GPIO_PIN_5
#define AD5312_SCLK_GPIO_Port   GPIOA

#define AD5312_DIN_Pin          GPIO_PIN_7
#define AD5312_DIN_GPIO_Port    GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
