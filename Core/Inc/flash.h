/*
 * flash.h
 *
 *  Created on: 17 июн. 2021 г.
 *      Author: Shein
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

void                flash_fill_calibTable(void);
uint8_t             flash_is_calibTable_null(void);
HAL_StatusTypeDef   flash_write_calibTable(union NVRAM *ram);
void                flash_read_calibTable(Table_t *ct);


#endif /* INC_FLASH_H_ */
