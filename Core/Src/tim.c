/*
 * tim.c
 *
 *  Created on: 14 авг. 2021 г.
 *      Author: Shein
 */

#include <main.h>
#include <stm32f1xx_hal.h>
#include <tim.h>

/* Объявление структуры для калибровки */

/* Переменные для калибровки */
struct calibration_parameters {
  uint8_t  is_tim3_working;
  uint8_t  is_tim4_working;
  uint16_t tim3_duration_of_capture;
  uint16_t tim4_duration_of_capture;
  enum VipPolarity v_polarity;
};

static struct calibration_parameters calibration;

/*
 * @brief   Calibration structure initialization
 * @note    Call it when device is started
 */
void tim_init_calibration(void)
{
  /* Заполнение структуры для калибровки */
  calibration.is_tim3_working           = 1;
  calibration.is_tim4_working           = 0;
  calibration.tim3_duration_of_capture  = 0;
  calibration.tim4_duration_of_capture  = 0;
  main_set_positive_polarity();
}

/*
 * @brief   Set variable tim3_duration_of_capture
 */
void tim_set_tim3_duration_of_capture(uint16_t d)
{
  calibration.tim3_duration_of_capture = d;
}

/*
 * @brief   Set variable tim4_duration_of_capture
 */
void tim_set_tim4_duration_of_capture(uint16_t d)
{
  calibration.tim4_duration_of_capture = d;
}

/*
 * @brief   Get value of tim3_duration_of_capture
 */
uint16_t tim_get_tim3_duration_of_capture(void)
{
  return calibration.tim3_duration_of_capture;
}

/*
 * @brief   Set value of tim4_duration_of_capture
 */
uint16_t tim_get_tim4_duration_of_capture(void)
{
  return calibration.tim4_duration_of_capture;
}

/*
 * @brief   Set value of v_polarity
 */
void tim_set_v_polarity(enum VipPolarity v)
{
  calibration.v_polarity = v;
}
