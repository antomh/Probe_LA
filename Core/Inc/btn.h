/*
 * btn.h
 *
 *  Created on: Jun 29, 2021
 *      Author: Shein
 */

#ifndef INC_BTN_H_
#define INC_BTN_H_

/*
 * Соответствие кнопок пинам, к которым они подключены:
 * RUN  - PIN_12
 * UP   - PIN_13
 * DOWN - PIN_14
 * */

enum BTN_STATE {
    BTN_NOT_PRESSED     = 0x00,
    BTN_SHORT_PRESS     = 0x01,
    BTN_LONG_PRESS      = 0x02
};

/*-USER STRUCTURES-----------------------------------------------------------*/

/* Структура для обработки нажатия кнопок и работы с прерываниями*/
struct btn {
    uint8_t  was_short_pressed;
    uint8_t  is_long_press;
    uint8_t  is_count_started;
    uint16_t counter;
};

/*-USER FUNCTIONS------------------------------------------------------------*/

uint8_t btn_run_get_state(void);
uint8_t btn_up_get_state(void);
uint8_t btn_down_get_state(void);

/*---------------------------------------------------------------------------*/

#endif /* INC_BTN_H_ */
