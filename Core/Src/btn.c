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
 * @brief   GPIO EXTI Callback for buttons
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    switch (GPIO_Pin) {
        case (GPIO_PIN_12):
            if ( HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == GPIO_PIN_SET ) {
                /* Поставили маркер, что начинаем отсчет, пока кнопка нажата */
                btn_pin_12.is_started = 1;
            }
            else {
                if ( btn_pin_12.counter > 40 ) {

                    /* Основной код, который надо делать по кнопке */
                    CDC_Transmit_FS( (uint8_t*)"BTN PIN 12 WAS PRESSED", 22);
                    /*---------------------------------------------*/

                    btn_pin_12.counter    = 0;
                    btn_pin_12.is_started = 0;
                }
            }
            break;
        case (GPIO_PIN_13) :
                if ( HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == GPIO_PIN_SET ) {
                    /* Поставили маркер, что начинаем отсчет, пока кнопка нажата */
                    btn_pin_13.is_started = 1;
                }
                else {
                    if ( btn_pin_13.counter > 40 ) {

                        /* Основной код, который надо делать по кнопке */
                        CDC_Transmit_FS( (uint8_t*)"BTN PIN 13 WAS PRESSED", 22);
                        /*---------------------------------------------*/

                        btn_pin_13.counter    = 0;
                        btn_pin_13.is_started = 0;
                    }
                }
                break;
        case (GPIO_PIN_14) :
                if ( HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) == GPIO_PIN_SET ) {
                    /* Поставили маркер, что начинаем отсчет, пока кнопка нажата */
                    btn_pin_14.is_started = 1;
                }
                else {
                    if ( btn_pin_14.counter > 40 ) {

                        /* Основной код, который надо делать по кнопке */
                        CDC_Transmit_FS( (uint8_t*)"BTN PIN 14 WAS PRESSED", 22);
                        /*---------------------------------------------*/

                        btn_pin_14.counter    = 0;
                        btn_pin_14.is_started = 0;
                    }
                }
                break;
    };
}

























































































