/*
 * btn.c
 *
 *  Created on: Jun 29, 2021
 *      Author: Shein
 */

/*-USER FILES----------------------------------------------------------------*/
#include "main.h"
#include "btn.h"

/*-STM LIBRARY FILES---------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "usbd_cdc_if.h"

/*-STANDART C FILES----------------------------------------------------------*/

/*-EXTERNAL VARIABLES--------------------------------------------------------*/
extern struct btn btn_pin_12;
extern struct btn btn_pin_13;
extern struct btn btn_pin_14;

/*---------------------------------------------------------------------------*/

/*
 * @brief   Get run button state
 * @retval  One of three state : not pressed(0x00), short press(0x01), long press(0x02)
 */
uint8_t btn_run_get_state(void) {
    uint8_t state = BTN_NOT_PRESSED;

    if ( btn_pin_12.was_short_pressed == 1 ) {
        state = BTN_SHORT_PRESS;
        btn_pin_12.was_short_pressed = 0;
    }
    else if ( btn_pin_12.is_long_press == 1 ) {
        state = BTN_LONG_PRESS;
    }

    return state;
}

/*---------------------------------------------------------------------------*/

/*
 * @brief   Get up button state
 * @retval  One of three state : not pressed, short press, long press
 */
uint8_t btn_up_get_state(void) {
    uint8_t state = BTN_NOT_PRESSED;

    if ( btn_pin_13.was_short_pressed == 1 ) {
        state = BTN_SHORT_PRESS;
        btn_pin_13.was_short_pressed = 0;
    }
    else if ( btn_pin_13.is_long_press == 1 ) {
        state = BTN_LONG_PRESS;
    }

    return state;
}

/*---------------------------------------------------------------------------*/

/*
 * @brief   Get down button state
 * @retval  One of three state : not pressed, short press, long press
 */
uint8_t btn_down_get_state(void) {
    uint8_t state = BTN_NOT_PRESSED;

    if ( btn_pin_14.was_short_pressed == 1 ) {
        state = BTN_SHORT_PRESS;
        btn_pin_14.was_short_pressed = 0;
    }
    else if ( btn_pin_14.is_long_press == 1 ) {
        state = BTN_LONG_PRESS;
    }

    return state;
}

/*---------------------------------------------------------------------------*/

/*
 * @brief   GPIO EXTI Callback for buttons
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    switch (GPIO_Pin) {
        case (GPIO_PIN_12):
            if ( HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == GPIO_PIN_RESET ) {
                /* Поставили маркер, что начинаем отсчет, пока кнопка нажата */
                btn_pin_12.is_count_started = 1;
            }
            else {
                /* Если кнопка нажата больше 40 мс, но меньше 800 мс, то есть однократное нажатие */
                if ( btn_pin_12.counter > 40 &&
                     btn_pin_12.counter < 1000 ) {

                    /* Основной код, который надо делать по кнопке */
                    btn_pin_12.was_short_pressed = 1;

                    /* DELETE THIS */
                    HAL_GPIO_WritePin(POLARITY_CONTROL_GPIO_Port, POLARITY_CONTROL_Pin, GPIO_PIN_SET);
                    /*-------------*/

                    /*---------------------------------------------*/

                    btn_pin_12.counter    = 0;
                    btn_pin_12.is_count_started = 0;
                    break;
                }
                /* Обнуляем статус того, что кнопка долго нажата только после того, как она была ОТЖАТА */
                if ( btn_pin_12.is_long_press == 1 ) {
                    btn_pin_12.is_long_press    = 0;
                    btn_pin_12.counter          = 0;
                    btn_pin_12.is_count_started = 0;
                }
            }
            break;
        case (GPIO_PIN_13) :
                if ( HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == GPIO_PIN_RESET ) {
                    /* Поставили маркер, что начинаем отсчет, пока кнопка нажата */
                    btn_pin_13.is_count_started = 1;
                }
                else {
                    /* Если кнопка нажата больше 40 мс, но меньше 800 мс, то есть однократное нажатие */
                    if ( btn_pin_13.counter > 40 &&
                         btn_pin_13.counter < 1000 ) {

                        /* Основной код, который надо делать по кнопке */
                        btn_pin_13.was_short_pressed = 1;

                        /* DELETE THIS */
                        HAL_GPIO_WritePin(POLARITY_CONTROL_GPIO_Port, POLARITY_CONTROL_Pin, GPIO_PIN_RESET);
                        /*-------------*/

                        /*---------------------------------------------*/

                        btn_pin_13.counter    = 0;
                        btn_pin_13.is_count_started = 0;
                        break;
                    }
                    /* Обнуляем статус того, что кнопка долго нажата только после того, как она была ОТЖАТА */
                    if ( btn_pin_13.is_long_press == 1 ) {
                      btn_pin_13.is_long_press    = 0;
                      btn_pin_13.counter          = 0;
                      btn_pin_13.is_count_started = 0;
                    }
                }
                break;
        case (GPIO_PIN_14) :
                if ( HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) == GPIO_PIN_RESET ) {
                    /* Поставили маркер, что начинаем отсчет, пока кнопка нажата */
                    btn_pin_14.is_count_started = 1;
                }
                else {
                    /* Если кнопка нажата больше 40 мс, но меньше 800 мс, то есть однократное нажатие */
                    if ( btn_pin_14.counter > 40 &&
                         btn_pin_14.counter < 1000 ) {

                        /* Основной код, который надо делать по кнопке */
                        btn_pin_14.was_short_pressed = 1;
                        /*---------------------------------------------*/

                        btn_pin_14.counter    = 0;
                        btn_pin_14.is_count_started = 0;
                        break;
                    }
                    /* Обнуляем статус того, что кнопка долго нажата только после того, как она была ОТЖАТА */
                    if ( btn_pin_14.is_long_press == 1 ) {
                      btn_pin_14.is_long_press    = 0;
                      btn_pin_14.counter          = 0;
                      btn_pin_14.is_count_started = 0;
                    }
                }
                break;
    };
}

























































































