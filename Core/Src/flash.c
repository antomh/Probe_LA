/*
 * flash.c
 *
 *  Created on: 17 июн. 2021 г.
 *      Author: Shein
 */

#include "stm32f1xx_hal.h"

#include "logic_calibration_table.h"
#include "flash.h"

#include "string.h"

/*---------------------------------------------------------------------------*/

extern union NVRAM DevNVRAM;
extern CRC_HandleTypeDef hcrc;

/*---------------------------------------------------------------------------*/
/*
 * @brief   Test function
 */
void flash_fill_calibTable(void)
{
    for (uint32_t i = 0; i < 254; ++i) {
        DevNVRAM.sector.data[i] = i;
    }
    DevNVRAM.sector.CheckSum = 0xAAAAAAAA;
    DevNVRAM.sector.NWrite = 0;
}

/*---------------------------------------------------------------------------*/
/*
 * @brief   Checks is there any calibration values in flash memory
 * @retval  Status (0x01) or (0x00) if there is table or no
 */
uint8_t flash_is_calibTable_null(void)
{
    Table_t t;
    volatile uint32_t addr = FLASH_TABLE_START_ADDR;

    /* Копируем значения из флеш-памяти во временную переменную для
     * того, чтобы проверить значение поля MagicNum. Копируем 50 байт
     * с запасом, вдруг если в структуре Table_t изменятся какие-либо
     * поля и адрес поля MagicNum в флеш-памяти будет другой. */
    memcpy( &t, (uint32_t*)addr, 50 );

    if ( t.MagicNum == MAGIC_KEY ) {
        return 0x01;
    }

    return 0x00;
}

/*---------------------------------------------------------------------------*/
/*
 * @brief   Write calibration table into flash memory
 * @retval  HAL Status
 */
HAL_StatusTypeDef flash_write_calibTable(union NVRAM *ram)
{
    /* Create some variables */
    volatile uint32_t   addr    = FLASH_TABLE_START_ADDR;
    uint32_t            err     = 0;
    uint32_t            index   = 0;
    uint8_t             status  = HAL_OK;

    /* Compare flash and ram content */
    while ( addr < FLASH_TABLE_STOP_ADDR ) {
        if ( ram->data32[index] != *(uint32_t *)addr ) {
            ++err;
        }
        index += 1;
        addr += 4;
    }

    /* If there are differencies -> write new data in flash */
    if (err > 0) {
        /* Unlock flash */
        if ( HAL_FLASH_Unlock() != HAL_OK ) {
            status = HAL_ERROR;
            return status;
        }

        /* Erase flash */
        FLASH_EraseInitTypeDef EraseInitStruct = {
                .TypeErase      = FLASH_TYPEERASE_PAGES,
                .PageAddress    = FLASH_TABLE_START_ADDR,
                .NbPages        = 1
        };
        if ( HAL_FLASHEx_Erase(&EraseInitStruct, &err) != HAL_OK ) {
            status = HAL_ERROR;
            return status;
        }
        if ( err != 0xFFFFFFFF ) {
            status = HAL_ERROR;
            return status;
        }

        /* Reset variables */
        addr    = FLASH_TABLE_START_ADDR;
        err     = 0;
        index   = 0;
        /* Increase number of rewritings */
        ram->sector.NWrite += 1;
        /* Calculate calibration table checksum */
        ram->sector.CheckSum = HAL_CRC_Calculate( &hcrc,
                                                  (uint32_t*)&(ram->calibration_table),
                                                  (sizeof(ram->calibration_table)/4) );
        /* Write flash */
        while (addr < FLASH_TABLE_STOP_ADDR) {
            if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr, ram->data32[index]) != HAL_OK) {
                err++;
            }
            index += 1;
            addr += 4;
            /* Wait until flash is busy */
            while ( (FLASH->SR & FLASH_SR_BSY) != 0 ) continue;
        }
        /* Lock flash */
        HAL_FLASH_Lock();
    }
    return status;
}

/*---------------------------------------------------------------------------*/
/*
 * @brief   Read calibration table from flash memory and write it to some Table_t variable
 */
void flash_read_calibTable(Table_t *ct)
{
    volatile uint32_t addr = FLASH_TABLE_START_ADDR;
    memcpy( ct, (uint32_t*)addr, sizeof(Table_t) );
}
