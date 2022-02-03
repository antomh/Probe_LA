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
  uint16_t tim3_duration_of_capture;
  uint16_t tim4_duration_of_capture;
enum VipPolarity v_polarity;
};

static struct calibration_parameters calibration;

/*---------------------------------------------------------------------------*/

/*
 * @brief   Calibration structure initialization
 * @note    Call it when device is started
 */
void tim_init_calibration(void)
{
  /* Заполнение структуры для калибровки */
  calibration.tim3_duration_of_capture  = 0xFFFF;
  calibration.tim4_duration_of_capture  = 0xFFFF;
  main_set_positive_polarity();
}

/*---------------------------------------------------------------------------*/

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

/*---------------------------------------------------------------------------*/

/*
 * @brief   Get value of tim3_duration_of_capture
 */
uint16_t tim_get_tim3_duration_of_capture(void)
{
  return calibration.tim3_duration_of_capture;
}

/*
 * @brief   Get value of tim4_duration_of_capture
 */
uint16_t tim_get_tim4_duration_of_capture(void)
{
  return calibration.tim4_duration_of_capture;
}

/*---------------------------------------------------------------------------*/

/*
 * @brief   Set value of v_polarity
 */
void tim_set_v_polarity(enum VipPolarity v)
{
  calibration.v_polarity = v;
}

/*---------------------------------------------------------------------------*/

/*
 * @brief   TIM3 and TIM4 interrupt callback
 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  uint16_t tim3_ccr[3], tim4_ccr[3];

  if (htim->Instance == TIM4) {
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2) {
      tim4_ccr[1] = TIM4->CCR1;
      tim4_ccr[2] = TIM4->CCR2;
      int32_t tim4_delta = tim4_ccr[2] - tim4_ccr[1];

      /* Тут костыль. Мне больно смотреть на этот код. Да простят меня боги программирования. */
      if (tim4_delta < 0 && tim4_delta > -TIME_PERIOD_MS_MAX) {
        tim_set_tim4_duration_of_capture(TIME_PERIOD_MS_MAX + tim4_delta);
      } else if (tim4_delta >= 0 && tim4_delta < TIME_PERIOD_MS_MAX) {
        tim_set_tim4_duration_of_capture(tim4_delta);
      } else {
        /* В случае ошибки: получения некорректного значения, запись в
         * переменную длительности захваченного импульса заведомо неправильного
         * значения */
        tim_set_tim4_duration_of_capture(0xFFFF);
      }
    }
  }

  if (htim->Instance == TIM3) {
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2) {
      tim3_ccr[1] = TIM3->CCR1;
      tim3_ccr[2] = TIM3->CCR2;
      int32_t tim3_delta = tim3_ccr[2] - tim3_ccr[1];

      /* Тут костыль. Мне больно смотреть на этот код. Да простят меня боги программирования. */
      if (tim3_delta < 0 && tim3_delta > -TIME_PERIOD_MS_MAX) {
        tim_set_tim3_duration_of_capture(TIME_PERIOD_MS_MAX + tim3_delta);
      } else if (tim3_delta >= 0 && tim3_delta < TIME_PERIOD_MS_MAX) {
        tim_set_tim3_duration_of_capture(tim3_delta);
      } else {
        /* В случае ошибки: получения некорректного значения, запись в
         * переменную длительности захваченного импульса заведомо неправильного
         * значения */
        tim_set_tim3_duration_of_capture(0xFFFF);
      }
    }
  }
}
