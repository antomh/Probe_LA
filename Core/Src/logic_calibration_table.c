/*******************************************************************************
 * @File: logic_calibration_table.c
 * @Author: Kozlov-dev, A.
 * @Project: Probe_LA.c * @Microcontroller: STM32F103C8T
 * @Device: Probe_LA
 * @Date: 07.04.2021
 * @Purpose: Calibration table volt2dac
 *******************************************************************************/
#include "main.h"
#include "logic_calibration_table.h"
#include "flash.h"

#include <stdlib.h>
#include <math.h>

/*---------------------------------------------------------------------------*/

extern union NVRAM DevNVRAM;

/*---------------------------------------------------------------------------*/

void calib_table_create_default(Table_t *ct)
{
    ct->dacValA_m12[0]  = 0x159;
    ct->dacValA_m12[1]  = 0x182;
    ct->dacValA_m12[2]  = 0x225;
    ct->dacValA_m12[3]  = 0x309;
    ct->dacValA_m12[4]  = 0x3eb;
    ct->dacValA_m12[5]  = 0x4cd;
    ct->dacValA_m12[6]  = 0x5b0;
    ct->dacValA_m12[7]  = 0x693;
    ct->dacValA_m12[8]  = 0x777;
    ct->dacValA_m12[9]  = 0x861;
    ct->dacValA_m12[10] = 0x93c;
    ct->dacValA_m12[11] = 0xa20;
    ct->dacValA_m12[12] = 0xb04;
    ct->dacValA_m12[13] = 0xbe5;
    ct->dacValA_m12[14] = 0xcc7;
    ct->dacValA_m12[15] = 0xda9;
    ct->dacValA_m12[16] = 0xe62;
    ct->dacValA_m12[17] = 0xe96;
    ct->dacValA_m12[18] = 0xeac;

    ct->dacValB_m12[0]  = 0x145;
    ct->dacValB_m12[1]  = 0x16e;
    ct->dacValB_m12[2]  = 0x212;
    ct->dacValB_m12[3]  = 0x2f0;
    ct->dacValB_m12[4]  = 0x3d2;
    ct->dacValB_m12[5]  = 0x4b4;
    ct->dacValB_m12[6]  = 0x597;
    ct->dacValB_m12[7]  = 0x67a;
    ct->dacValB_m12[8]  = 0x75e;
    ct->dacValB_m12[9]  = 0x84a;
    ct->dacValB_m12[10] = 0x923;
    ct->dacValB_m12[11] = 0xa07;
    ct->dacValB_m12[12] = 0xae8;
    ct->dacValB_m12[13] = 0xbcc;
    ct->dacValB_m12[14] = 0xcae;
    ct->dacValB_m12[15] = 0xd90;
    ct->dacValB_m12[16] = 0xe49;
    ct->dacValB_m12[17] = 0xe7b;
    ct->dacValB_m12[18] = 0xe92;

    ct->dacValA_m27[0]  = 0x0;
    /* TODO: Добавить код заполнения таблицы для 27 В значениями
     * по умолчанию */
    ct->dacValA_m27[1]  = 0x1000;

    ct->dacValB_m27[0]  = 0x0;
    ct->dacValB_m27[1]  = 0x1000;
}

/*---------------------------------------------------------------------------*/

/*
 * @brief   Fill some fields in @Table_t structure and read calibrate values
 *          from flash.
 */
void calib_table_init(Table_t *ct)
{
    if ( flash_is_calibTable_null() == 0x00 ) {
        ct->Firmware = FIRMWARE_NUMBER;
        ct->Hardwire = HARDWIRE_NUMBER;
        ct->MagicNum = MAGIC_KEY;
        ct->SN       = SERIAL_NUMBER;

        ct->calibration_step = 1040;
        ct->volt_min_mode_12 = -9360;
        ct->volt_max_mode_12 = 9360;
        ct->volt_min_mode_27 = -27000;
        ct->volt_max_mode_27 = 27000;

        /* Заполнение калибровочной таблицы значениями по умолчанию */
        calib_table_create_default(ct);
        /* Запись дефолтных значений во флеш-память */
        flash_write_calibTable( &DevNVRAM );
    }
    else {
        /* Чтение таблицы из флеш-памяти в переменную DevNVRAM */
        flash_read_sector( &DevNVRAM );
    }
}

/*---------------------------------------------------------------------------*/

/*
 * @brief   Convert some voltage to ... do it later.
 * */
uint16_t volt2dgt(Table_t *ct, struct comparison_parameters *cp, enum DacChannel ch)
{
//    struct data_volt2dgt dConv = {
//            .count  = 0,
//            .yi     = 0,
//            .y      = 0,
//            .Ca0    = 0,
//            .Ca1    = 0,
//            .a0     = 0,
//            .a1     = 0,
//            .CodeX  = 0
//    };
//
//    switch (cp->relay_state)
//    {
//        case M12 :
//
//            if (ch == CH_A) {
//                /*Канал А*/
//                /* по значениям МАX и MIN и Шага калибровки вычисляем индекс соотвестующего значению таблицы равного или меньше VOLT  */
//                dConv.yi = floor(
//                        ((float) ((float) (((abs(ct->volt_min_mode_12)
//                                + abs(ct->volt_max_mode_12))
//                                / ct->calibration_step)
//                                * abs(ct->volt_min_mode_12))
//                                / (float) (abs(ct->volt_min_mode_12)
//                                        + abs(ct->volt_max_mode_12)))
//                                / (float) (abs(ct->volt_min_mode_12)))
//                                * cp->VDAC_A
//                                + ((float) (((abs(ct->volt_min_mode_12)
//                                        + abs(ct->volt_max_mode_12))
//                                        / ct->calibration_step)
//                                        * abs(ct->volt_min_mode_12))
//                                        / (float) (abs(ct->volt_min_mode_12)
//                                                + abs(ct->volt_max_mode_12))));
//            /* Значение цап для первой точки */
//            /* Потенциальное место ошибки!  обращаемся к индексу который вычеслили, добавить проверку  вхождения в область таблицы*/
//            if (dConv.yi <= MAX_VAL_M12) /* Проверка что индекс был в области памями таблицы */
//            {
//                dConv.Ca0 = (uint16_t*) ct->dacValA_m12[dConv.yi];
//                /* Значение цап для второй точки  */
//                /* Потенциальное место ошибки!  обращаемся к индексу который вычеслили, добавить проверку  выхождения за область таблицы*/
//                dConv.Ca1 = ct->dacValA_m12[dConv.yi + 1];
//                /* Значение цап для второй точки  */
//                dConv.y = ((float) ((float) (((abs(ct->volt_min_mode_12)
//                        + abs(ct->volt_max_mode_12)) / ct->calibration_step)
//                        * abs(ct->volt_min_mode_12))
//                        / (float) (abs(ct->volt_min_mode_12)
//                        + abs(ct->volt_max_mode_12)))
//                        / (float) (abs(ct->volt_min_mode_12)))
//                        * cp->VDAC_A
//                        + ((float) (((abs(ct->volt_min_mode_12)
//                        + abs(ct->volt_max_mode_12))
//                        / ct->calibration_step)
//                        * abs(ct->volt_min_mode_12))
//                        / (float) (abs(ct->volt_min_mode_12)
//                        + abs(ct->volt_max_mode_12)));
//
//                dConv.a0 = (dConv.yi * ct->calibration_step)
//                        - abs(ct->volt_min_mode_12);
//                dConv.a1 = ((dConv.yi + 1) * ct->calibration_step)
//                        - abs(ct->volt_min_mode_12);
//                dConv.CodeX = ((((float) (dConv.Ca1 - dConv.Ca0))
//                        / ((float) dConv.a1 - dConv.a0)))
//                        * (cp->VDAC_A - dConv.a0) + dConv.Ca0;
//
//                cp->status = SUCCESS;
//
//                return dConv.CodeX; //2400v -> 2662dgt
//            } else {
//                /*Возвращаем статус -> вышли за область памяти таблицы */
//                return cp->status = ERROR;
//                break;
//            }
//        } else {
//            /*Канал B*/
//            /* по значениям МАX и MIN и Шага калибровки вычисляем индекс соотвестующего значению таблицы равного или меньше VOLT  */
//            dConv.yi = floor(
//                    ((float) ((float) (((abs(ct->volt_min_mode_12)
//                            + abs(ct->volt_max_mode_12)) / ct->calibration_step)
//                            * abs(ct->volt_min_mode_12))
//                            / (float) (abs(ct->volt_min_mode_12)
//                                    + abs(ct->volt_max_mode_12)))
//                            / (float) (abs(ct->volt_min_mode_12)))
//                            * cp->VDAC_B
//                            + ((float) (((abs(ct->volt_min_mode_12)
//                                    + abs(ct->volt_max_mode_12))
//                                    / ct->calibration_step)
//                                    * abs(ct->volt_min_mode_12))
//                                    / (float) (abs(ct->volt_min_mode_12)
//                                            + abs(ct->volt_max_mode_12))));
//            /* Значение цап для первой точки  */
//            /* Потенциальное место ошибки!  обращаемся к индексу который вычеслили, добавить проверку  выхождения за область таблицы*/
//            if (dConv.yi <= MAX_VAL_M12) /* Проверка что индекс был в области памями таблицы */
//            {
//                dConv.Ca0 = (uint16_t*) ct->dacValA_m12[dConv.yi];
//                /* Значение цап для второй точки  */
//                /* Потенциальное место ошибки!  обращаемся к индексу который вычеслили, добавить проверку  выхождения за область таблицы*/
//                dConv.Ca1 = ct->dacValA_m12[dConv.yi + 1];
//                /* Значение цап для второй точки  */
//                dConv.y = ((float) ((float) (((abs(ct->volt_min_mode_12)
//                        + abs(ct->volt_max_mode_12)) / ct->calibration_step)
//                        * abs(ct->volt_min_mode_12))
//                        / (float) (abs(ct->volt_min_mode_12)
//                                + abs(ct->volt_max_mode_12)))
//                        / (float) (abs(ct->volt_min_mode_12)))
//                        * cp->VDAC_B
//                        + ((float) (((abs(ct->volt_min_mode_12)
//                                + abs(ct->volt_max_mode_12))
//                                / ct->calibration_step)
//                                * abs(ct->volt_min_mode_12))
//                                / (float) (abs(ct->volt_min_mode_12)
//                                        + abs(ct->volt_max_mode_12)));
//
//                dConv.a0 = (dConv.yi * ct->calibration_step)
//                        - abs(ct->volt_min_mode_12);
//                dConv.a1 = ((dConv.yi + 1) * ct->calibration_step)
//                        - abs(ct->volt_min_mode_12);
//                dConv.CodeX = ((((float) (dConv.Ca1 - dConv.Ca0))
//                        / ((float) dConv.a1 - dConv.a0)))
//                        * (cp->VDAC_B - dConv.a0) + dConv.Ca0;
//
//                cp->status = SUCCESS;
//
//                return dConv.CodeX; //2400 -> 2662
//            } else {
//                /*Возвращаем статус -> вышли за область памяти таблицы */
//                return cp->status = ERROR;
//                break;
//            }
//        }
//        break;
//
//    case m27:
//        if (ch == ChA) {
//            /*Канал А*/
//            /* по значениям МАX и MIN и Шага калибровки вычисляем индекс соотвестующего значению таблицы равного или меньше VOLT  */
//            dConv.yi = floor(
//                    ((float) ((float) (((abs(ct->volt_min_mode_27)
//                            + abs(ct->volt_max_mode_27)) / ct->calibration_step)
//                            * abs(ct->volt_min_mode_27))
//                            / (float) (abs(ct->volt_min_mode_27)
//                                    + abs(ct->volt_max_mode_27)))
//                            / (float) (abs(ct->volt_min_mode_27)))
//                            * cp->VDAC_A
//                            + ((float) (((abs(ct->volt_min_mode_27)
//                                    + abs(ct->volt_max_mode_27))
//                                    / ct->calibration_step)
//                                    * abs(ct->volt_min_mode_27))
//                                    / (float) (abs(ct->volt_min_mode_27)
//                                            + abs(ct->volt_max_mode_27))));
//            /* Значение цап для первой точки  */
//            /* Потенциальное место ошибки!  обращаемся к индексу который вычеслили, добавить проверку  выхождения за область таблицы*/
//            if (dConv.yi <= MAX_VAL_M27) /* Проверка что индекс был в области памями таблицы */
//            {
//                dConv.Ca0 = (uint16_t*) ct->dacValA_m27[dConv.yi];
//                /* Значение цап для второй точки  */
//                /* Потенциальное место ошибки!  обращаемся к индексу который вычеслили, добавить проверку  выхождения за область таблицы*/
//                dConv.Ca1 = ct->dacValA_m27[dConv.yi + 1];
//                /* Значение цап для второй точки  */
//                dConv.y = ((float) ((float) (((abs(ct->volt_min_mode_27)
//                        + abs(ct->volt_max_mode_27)) / ct->calibration_step)
//                        * abs(ct->volt_min_mode_27))
//                        / (float) (abs(ct->volt_min_mode_27)
//                                + abs(ct->volt_max_mode_27)))
//                        / (float) (abs(ct->volt_min_mode_27)))
//                        * cp->VDAC_A
//                        + ((float) (((abs(ct->volt_min_mode_27)
//                                + abs(ct->volt_max_mode_27))
//                                / ct->calibration_step)
//                                * abs(ct->volt_min_mode_27))
//                                / (float) (abs(ct->volt_min_mode_27)
//                                        + abs(ct->volt_max_mode_27)));
//
//                dConv.a0 = (dConv.yi * ct->calibration_step)
//                        - abs(ct->volt_min_mode_27);
//                dConv.a1 = ((dConv.yi + 1) * ct->calibration_step)
//                        - abs(ct->volt_min_mode_27);
//                dConv.CodeX = ((((float) (dConv.Ca1 - dConv.Ca0))
//                        / ((float) dConv.a1 - dConv.a0)))
//                        * (cp->VDAC_A - dConv.a0) + dConv.Ca0;
//                cp->status = SUCCESS;
//                return dConv.CodeX; //2400 -> 2662
//                break;
//            } else {
//                /*Возвращаем статус -> вышли за область памяти таблицы */
//                return cp->status = ERROR;
//                break;
//            }
//        } else {
//            /*Канал B*/
//            /* по значениям МАX и MIN и Шага калибровки вычисляем индекс соотвестующего значению таблицы равного или меньше VOLT  */
//            dConv.yi = floor(
//                    ((float) ((float) (((abs(ct->volt_min_mode_27)
//                            + abs(ct->volt_max_mode_27)) / ct->calibration_step)
//                            * abs(ct->volt_min_mode_27))
//                            / (float) (abs(ct->volt_min_mode_27)
//                                    + abs(ct->volt_max_mode_27)))
//                            / (float) (abs(ct->volt_min_mode_27)))
//                            * cp->VDAC_B
//                            + ((float) (((abs(ct->volt_min_mode_27)
//                                    + abs(ct->volt_max_mode_27))
//                                    / ct->calibration_step)
//                                    * abs(ct->volt_min_mode_27))
//                                    / (float) (abs(ct->volt_min_mode_27)
//                                            + abs(ct->volt_max_mode_27))));
//            /* Значение цап для первой точки  */
//            /* Потенциальное место ошибки!  обращаемся к индексу который вычеслили, добавить проверку  выхождения за область таблицы*/
//            if (dConv.yi <= MAX_VAL_M27) /* Проверка что индекс был в области памями таблицы */
//            {
//                dConv.Ca0 = (uint16_t*) ct->dacValA_m27[dConv.yi];
//                /* Значение цап для второй точки  */
//                /* Потенциальное место ошибки!  обращаемся к индексу который вычеслили, добавить проверку  выхождения за область таблицы*/
//                dConv.Ca1 = ct->dacValA_m27[dConv.yi + 1];
//                /* Значение цап для второй точки  */
//                dConv.y = ((float) ((float) (((abs(ct->volt_min_mode_27)
//                        + abs(ct->volt_max_mode_27)) / ct->calibration_step)
//                        * abs(ct->volt_min_mode_27))
//                        / (float) (abs(ct->volt_min_mode_27)
//                                + abs(ct->volt_max_mode_27)))
//                        / (float) (abs(ct->volt_min_mode_27)))
//                        * cp->VDAC_B
//                        + ((float) (((abs(ct->volt_min_mode_27)
//                                + abs(ct->volt_max_mode_27))
//                                / ct->calibration_step)
//                                * abs(ct->volt_min_mode_27))
//                                / (float) (abs(ct->volt_min_mode_27)
//                                        + abs(ct->volt_max_mode_27)));
//
//                dConv.a0 = (dConv.yi * ct->calibration_step)
//                        - abs(ct->volt_min_mode_27);
//                dConv.a1 = ((dConv.yi + 1) * ct->calibration_step)
//                        - abs(ct->volt_min_mode_12);
//                dConv.CodeX = ((((float) (dConv.Ca1 - dConv.Ca0))
//                        / ((float) dConv.a1 - dConv.a0)))
//                        * (cp->VDAC_B - dConv.a0) + dConv.Ca0;
//                cp->status = SUCCESS;
//                return dConv.CodeX; //2400 -> 2662
//                break;
//            } else {
//                /*Возвращаем статус -> вышли за область памяти таблицы */
//                return cp->status = ERROR;
//                break;
//            }
//        }
//    }
    return 0;
}
