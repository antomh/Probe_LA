/*
 * crc.c
 *
 *  Created on: 18 июн. 2021 г.
 *      Author: Shein
 */

#include "stm32f1xx_hal.h"
#include "crc.h"

/*---------------------------------------------------------------------------*/

extern CRC_HandleTypeDef hcrc;

/*---------------------------------------------------------------------------*/
/*
 * @brief   Calculate calibration table CRC
 * @param   Start pointer at calibration table
 * @param   @calTableType : TABLETYPE_M12 or TABLETYPE_M27
 * @param   Pointer at variable for calculated CRC
 * @retval  HAL Status
 */
HAL_StatusTypeDef crc_calibTable_calculate(uint16_t *calTable, calTableType t_calTable, uint32_t *crc)
{
    if ( t_calTable == TABLETYPE_M12 ) {
        /* See the next value in Table_t structure */
        const uint8_t calTable_lenght = 88;

        *crc = HAL_CRC_Calculate(&hcrc, (uint32_t*)calTable, calTable_lenght);
        return HAL_OK;
    }
    else if ( t_calTable == TABLETYPE_M27 ) {
        /* See the next value in Table_t structure */
        const uint8_t calTable_lenght = 163;

        *crc = HAL_CRC_Calculate(&hcrc, (uint32_t*)calTable, calTable_lenght);
        return HAL_OK;
    }
    else {
        return HAL_ERROR;
    }
}
