/*
 * flash.h
 *
 *  Created on: 17 июн. 2021 г.
 *      Author: Shein
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

void                flash_fill_calibTable(void);
HAL_StatusTypeDef   flash_write_calibTable(void);

#endif /* INC_FLASH_H_ */
