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
#include "stdbool.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* Режим работы делителя щупа */
enum RelayState {       //RelayState =|1:m12|0:m27|
    M12 = 0x01,
    M27 = 0x00
};

/* Режим работы щупа (калибровка или обычная работа) */
enum CalibrationState {
  CALIBRATION_OFF = 0x00,
  CALIBRATION_ON  = 0x01
};

/* Каналы ЦАП */
enum DacChannel {
    CH_A = 0x00,         // ЦАП А
    CH_B = 0x01          // ЦАП B
};

/* Полярность внешнего источника питания при калибовке */
enum VipPolarity {
    POSITIVE_POLARITY = 0x00, // GND - GND
    NEGATIVE_POLARITY = 0x01  // GND - VCC
};

/*-USER TYPES AND STRUCTURES-------------------------------------------------*/

/* Переменные для установки компарирования для работы ЦАП и реле */
struct comparison_parameters {
  int16_t   dac_A_volt;     // ЦАП А, в вольтах
  int16_t   dac_B_volt;     // ЦАП B, в вольтах
  uint16_t  dac_A_dgt;      // ЦАП А, в значениях ЦАП
  uint16_t  dac_B_dgt;      // ЦАП B, в значениях ЦАП

  enum RelayState       relay_state;        // режим работы |1:M12|0:M27|
  enum CalibrationState calibration_state;  // состояние калибровки (включена/нет)
  bool                  set_level_status;   // статус выполнения установки уровня

  const uint16_t  dac_dgt_val_max;      // максимальное значение ЦАП
  const uint16_t  dac_dgt_val_min;      // минимальное  значение ЦАП
};

/* Переменные для калибровки */
struct calibration_parameters {
    uint8_t is_tim3_working;
    uint16_t g_tim3;
    uint16_t g_tim4;

    enum VipPolarity v_polarity;    // Полярность источника питания
};

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define AD5312_LDAC_Pin GPIO_PIN_1
#define AD5312_LDAC_GPIO_Port GPIOA
#define RELAY_CONTROL_Pin GPIO_PIN_2
#define RELAY_CONTROL_GPIO_Port GPIOA
#define AD5312_SYNC_Pin GPIO_PIN_4
#define AD5312_SYNC_GPIO_Port GPIOA
#define AD5312_SCLK_Pin GPIO_PIN_5
#define AD5312_SCLK_GPIO_Port GPIOA
#define AD5312_DIN_Pin GPIO_PIN_7
#define AD5312_DIN_GPIO_Port GPIOA
#define POLARITY_CONTROL_Pin GPIO_PIN_15
#define POLARITY_CONTROL_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
