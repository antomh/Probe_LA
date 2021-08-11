/*
 * dac.h
 *
 *  Created on: Aug 10, 2021
 *      Author: Shein
 */

#ifndef INC_DAC_H_
#define INC_DAC_H_

void dac_set_A_volt(struct comparison_parameters *cp, union NVRAM *ram);
void dac_set_B_volt(struct comparison_parameters *cp, union NVRAM *ram);
void dac_set_A_B_volt(struct comparison_parameters *cp, union NVRAM *ram);

void dac_set_A_dgt(struct comparison_parameters *cp);
void dac_set_B_dgt(struct comparison_parameters *cp);
void dac_set_A_B_dgt(struct comparison_parameters *cp);

#endif /* INC_DAC_H_ */
