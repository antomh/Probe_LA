/*
 * crc.h
 *
 *  Created on: Jun 21, 2021
 *      Author: Shein
 */

#ifndef INC_CRC_H_
#define INC_CRC_H_

/*---------------------------------------------------------------------------*/

typedef enum {
    TABLETYPE_M12,
    TABLETYPE_M27
} calTableType;

/*---------------------------------------------------------------------------*/

HAL_StatusTypeDef crc_calibTable_calculate(uint16_t *calTable, calTableType t_calTable, uint32_t *crc);

#endif /* INC_CRC_H_ */
