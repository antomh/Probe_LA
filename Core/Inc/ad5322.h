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

// Прототипы функций
void DAC_AD5322_Init(SPI_HandleTypeDef *pSPI);
void DAC_AD5322_Ch1(SPI_HandleTypeDef *pSPI, uint16_t data_ch1);	// Инициализация цифро-аналогового преобразователя
void DAC_AD5322_Ch2(SPI_HandleTypeDef *pSPI, uint16_t data_ch2);	// Инициализация цифро-аналогового преобразователя
void DAC_AD5322_Ch1Ch2(SPI_HandleTypeDef *pSPI, uint16_t data_ch1, uint16_t data_ch2);

#endif /* DAC_AD5322_H */

