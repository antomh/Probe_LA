/*
 * tim.h
 *
 *  Created on: 14 авг. 2021 г.
 *      Author: Shein
 */

#ifndef INC_TIM_H_
#define INC_TIM_H_

/*-ENUMERATIONS AND TYPES DEFINITIONS----------------------------------------*/

/* Полярность внешнего источника питания при калибовке */
enum VipPolarity {
  POSITIVE_POLARITY = 0x00, // GND - GND
  NEGATIVE_POLARITY = 0x01  // GND - VCC
};

/*-FUNCTIONS-----------------------------------------------------------------*/

void tim_init_calibration(void);
void tim_set_tim3_duration_of_capture(uint16_t);
void tim_set_tim4_duration_of_capture(uint16_t);
uint16_t tim_get_tim3_duration_of_capture(void);
uint16_t tim_get_tim4_duration_of_capture(void);
void tim_set_v_polarity(enum VipPolarity);


#endif /* INC_TIM_H_ */
