/*******************************************************************************
 * @File: DAC_AD5322.c
 * @Author: Kozlov-dev, A.
 * @Project: Probe_LA.c
 * @Microcontroller: STM32F103C8T
 * @Device: Probe_LA
 * @Date: 07.04.2020
 * @Purpose: Управление цифро-аналоговым преобразователем DAC_AD5322
 * @Datasheet : https://www.analog.com/media/en/technical-documentation/data-sheets/AD5302_5312_5322.pdf
 *******************************************************************************/

#ifndef DAC_AD5322_H
#define DAC_AD5322_H

// Подключение заголовочных файлов модулей проекта
#include "stm32f1xx_hal.h"

// Опорное напряжение ЦАП (в вольтах)
#define DAC_REF 4.096F

// Максимальное значение кода ЦАП
#define DAC_MAX 4096

// Макрос для перевода напряжения (в вольтах) в код ЦАП
//#define VLT_TO_DGT(V) (uint16_t)(((V) / DAC_REF) * DAC_MAX)
//#define VLT_TO_DGT(V) (float)(((V) / DAC_REF) * DAC_MAX)

#define AD5312_LDAC_Pin			GPIO_PIN_1
#define AD5312_LDAC_GPIO_Port	GPIOA
#define Relay_Pin				GPIO_PIN_2
#define Relay_GPIO_Port			GPIOA
#define AD5312_SYNC_Pin			GPIO_PIN_4
#define AD5312_SYNC_GPIO_Port	GPIOA
#define AD5312_SCLK_Pin			GPIO_PIN_5
#define AD5312_SCLK_GPIO_Port	GPIOA
#define AD5312_DIN_Pin			GPIO_PIN_7
#define AD5312_DIN_GPIO_Port	GPIOA


// Прототипы функций
void DAC_AD5322_Init(SPI_HandleTypeDef *pSPI);
void DAC_AD5322_Ch1(SPI_HandleTypeDef *pSPI, uint16_t data_ch1);	// Инициализация цифро-аналогового преобразователя
void DAC_AD5322_Ch2(SPI_HandleTypeDef *pSPI, uint16_t data_ch2);	// Инициализация цифро-аналогового преобразователя
void DAC_AD5322_Ch1Ch2(SPI_HandleTypeDef *pSPI, uint16_t data_ch1, uint16_t data_ch2);

#endif /* DAC_AD5322_H */

