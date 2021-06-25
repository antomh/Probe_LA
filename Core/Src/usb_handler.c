/*
 * usb_handler.c
 *
 *  Created on: Jun 21, 2021
 *      Author: Shein
 */

/*-USER FILES----------------------------------------------------------------*/
#include "main.h"
#include "logic_calibration_table.h"
#include "flash.h"

/*-STM LIBRARY FILES---------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "usbd_cdc_if.h"

/*-STANDART C FILES----------------------------------------------------------*/
#include "stdbool.h"
#include "stdlib.h"

/*-EXTERNAL VARIABLES--------------------------------------------------------*/

extern bool RelayState;
extern bool changeTableFlag;
extern union NVRAM DevNVRAM;

/*---------------------------------------------------------------------------*/

/*  Command system
    0x01 - включение реле                           data: 1B (0x00 - выключить; 0x01 - включить)    answer: 0x01 + 1B status
    0x02 - ЦАП канал А                              data: 2B (значение)                             answer: 0x02 + 1B status
    0x03 - ЦАП канал B                              data: 2B (значение)                             answer: 0x03 + 1B status
    0x04 - АЦП запрос значения                      data: 0B                                        answer: 0x04 + 2B value
    0x05 - запрос состояния (Relay, DA, DB)         data: 0B                                        answer: 0x05 + 1B состиояние рэле + 2B значение ЦАП канал А + 2B значение ЦАП канал B
    0x06 - запрос состояния кнопок (Run, Up, Down)  data: 0B                                        answer: 0x06 + 1B состояние кнопки Run + 1B состояние кнопки Up + 1B состояние кнопки Down
    0x07 - запрос ID устройства
    ("SN+WW+YY+NNN")                                    data: 0B                                        answer: 0x07 + 9B ID ("SN+WW+YY+NNN") SN1121001- 11 неделя-21год - 001 порядковый номер изготовления
    0х08 - запрос измеренной длительности           data: 0B (0x00 - сработал; 0x01 - не сработал)  answer: 0x08 + 1B status
    0х09 - запрос измеренной длительности           data: 0B (0x00 - сработал; 0x01 - не сработал)  answer: 0x08 + 1B status
    --------------------------------------------------------------------------
    0х0C - Прием длины калибровочной таблицы [0x0C][Длина][???]             0x00 - сработал; 0x01 - не сработал)    answer: 0x09 + 1B status
    0х0B - Отправка CRC 1-4 таблицы [0x0B][1-4][CRC(1-4)]   answer:
    0х0A - Прием калибровочной таблицы [0x0A][1-4][offset][count][data]     answer: [0x0A]+[1-4]+[offset]+[count]+[status] (0x00 - сработал; 0x01 - не сработал)
    0х0D - Запись во флеш калибровочной таблицы [0x0D] data: 1B (0x00 - успешно; 0x01 - ошибка при записи)  answer: 0x0D + 1B status
    --------------------------------------------------------------------------
    status
    0x00 - успешно
    0x01 - ошибка
    --------------------------------------------------------------------------
    Калибровка
    На вход щупа подается семетричная пила с частотой 1кГц с оффестом установленным на ип.
    после компарирования сигнала МК измеряет длительность импульса
    т.к. 1 кГц соотвествет длительности в 500 мс то это означает что мы попапали в полуку офсета. */
/*---------------------------------------------------------------------------*/

/*
 * @brief   USB package handler
 * @note    Len <= 64
 * @retval  HAL Status
 */
HAL_StatusTypeDef usb_rx_handler(uint8_t *Buf, uint32_t *Len)
{
    if (*Len < 1 || *Len > 64) {
        return HAL_ERROR;
    }

    uint8_t     UserTxBufferFS[APP_TX_DATA_SIZE];
    uint16_t    tVal16;
    uint8_t     cmd = Buf[0];

    switch (Buf[0]) {
        case 0x01 :
            if ( *Len >= 2 && (Buf[1] == 0x01 || Buf[1] == 0x00) ) {

                HAL_GPIO_WritePin(Relay_GPIO_Port, Relay_Pin, GPIO_PIN_SET);

                if ( Buf[1] == 0x01 ) {
                    RelayState = m12;
                    printf("RelayState:12V - %d \n", RelayState);
                }
                else if (Buf[1] == 0x00) {
                    RelayState = m27;
                    printf("RelayState:27V - %d \n", RelayState);
                }
                SetAllDAC();
                UserTxBufferFS[1] = 0x00; // успешно
            }
            else {
                UserTxBufferFS[1] = 0x01; // ошибка
            }

            UserTxBufferFS[0] = cmd;
            CDC_Transmit_FS(UserTxBufferFS, 2);
            break;

        case 0x02 :
            if (*Len >= 3) {
                resValTIM3_PB4(); // обнуление переменной для проведения калибровки
                resValTIM4_PB6(); // обнуление переменной для проведения калибровки
                memcpy(&tVal16, Buf + 1, sizeof(tVal16));
                SetDacA(tVal16);
                printf("DacA: %d\n", tVal16);

                UserTxBufferFS[1] = 0x00; // успешно
            }
            else {
                UserTxBufferFS[1] = 0x01; // ошибка
            }
            UserTxBufferFS[0] = cmd;
            CDC_Transmit_FS(UserTxBufferFS, 2);
            break;

        case 0x03 :
            if (*Len >= 3) {
                resValTIM3_PB4(); // обнуление переменной для проведения калиброки
                resValTIM4_PB6(); // обнуление переменной для проведения калиброки
                memcpy(&tVal16, Buf + 1, sizeof(tVal16));
                SetDacB(tVal16);
                printf("DacB: %d \n", tVal16);

                UserTxBufferFS[1] = 0x00; // успешно
            }
            else {
                UserTxBufferFS[1] = 0x01; // ошибка
            }
            UserTxBufferFS[0] = cmd;
            CDC_Transmit_FS(UserTxBufferFS, 2);
            break;

        case 0x04 :
            tVal16 = GetADC();
            UserTxBufferFS[0] = cmd;
            memcpy(UserTxBufferFS + 1, &tVal16, sizeof(tVal16));
            CDC_Transmit_FS(UserTxBufferFS, 3);
            break;

        case 0x05 :
            UserTxBufferFS[0] = cmd;
            UserTxBufferFS[1] = RelayState;

            tVal16 = GetDacA();
            memcpy(UserTxBufferFS + 2, &tVal16, sizeof(tVal16));

            tVal16 = GetDacB();
            memcpy(UserTxBufferFS + 4, &tVal16, sizeof(tVal16));

            CDC_Transmit_FS(UserTxBufferFS, 6);
            break;

        case 0x06 :
            UserTxBufferFS[0] = cmd;
            UserTxBufferFS[1] = GetBtnRunState();
            UserTxBufferFS[2] = GetBtnUpState();
            UserTxBufferFS[3] = GetBtnDownState();
            CDC_Transmit_FS(UserTxBufferFS, 4);
            break;

        case 0x07 :
        {
            char str[9] = {
                0,0,0,0,0,0,0,0,0
            };
            memcpy(str, "SN", strlen("SN"));
            itoa(SN_DEFINE, str + 2, 16);

            UserTxBufferFS[0] = cmd;
            UserTxBufferFS[1] = strlen(str);
            memcpy(UserTxBufferFS + 2, str, strlen(str));
            CDC_Transmit_FS(UserTxBufferFS, strlen(str) + 2);
            break;
        }

        case 0x08 :
        {
            EnableTIM3_PB4();
            uint16_t temp = GetTIM3();
            UserTxBufferFS[0] = cmd;
            memcpy(UserTxBufferFS + 1, &temp, sizeof(uint16_t));
            CDC_Transmit_FS(UserTxBufferFS, 1 + sizeof(uint16_t));
            break;
        }

        case 0x09 :
        {
            EnableTIM4_PB6();
            uint16_t temp = GetTIM4();
            UserTxBufferFS[0] = cmd;
            memcpy(UserTxBufferFS + 1, &temp, sizeof(uint16_t));
            CDC_Transmit_FS(UserTxBufferFS, 1 + sizeof(uint16_t));
            break;
        }

        case 0x0A :
        {
            /* TODO: Прием калибровочной таблицы [0x0A][1-4][offset][count][data]
             * answer: [0x0A]+[1-4]+[offset]+[count]+[status] (0x00 - сработал; 0x01 - не сработал)
             */
            /*
            u8 Buf[0] = 0x0A
            u8 Buf[1] = 0x00-0x03
            ---------------------
            u16 Buf[2] = offset u8
                Buf[3] = offset u8
            ----------------------
            u16 Buf[4] = count u8
                Buf[5] = count u8
            ----------------------
            u16 Buf[6] = data1 u8
                Buf[7] = data1 u8
            ----------------------
            ...
            u16 Buf[count] = data[n-1]  u8
                Buf[count] = data[n]    u8
            */

            UserTxBufferFS[1] = 0x01;           /* Значение для ответа на команду, 0х01 - успешное выполнение */

            uint16_t dataStartNumber, dataEndNumber;
            memcpy(&dataStartNumber, (Buf + 2), sizeof(uint16_t));
            memcpy(&dataEndNumber, (Buf + 2 + sizeof(uint16_t)), sizeof(uint16_t));
            CDC_Transmit_FS(Buf, (uint16_t)*Len);
            switch (Buf[1]) {
                case 0x00 :
                {
//                    CDC_Transmit_FS(Buf, *Len);
                    if (dataStartNumber >= MAX_VAL_M12 ||
                        dataEndNumber > MAX_VAL_M12) {
                        UserTxBufferFS[1] = 0x00;   /* Произошла ошибка - возвращаем 0х00 */
                        break;
                    }
//                    CDC_Transmit_FS(Buf, *Len);
                    for (uint16_t i = 0; i < (dataEndNumber - dataEndNumber); ++i) {
                        memcpy(&DevNVRAM.calibration_table.dacValA_m12[i + dataStartNumber],
                               (Buf + 2) + 2 * sizeof(uint16_t) + (i * 2),
                               sizeof(uint16_t));
                    }
//                    CDC_Transmit_FS(Buf, *Len);
                    break;
                }
                case 0x01 :
                {
                    if (dataStartNumber >= MAX_VAL_M12 ||
                        dataEndNumber > MAX_VAL_M12) {
                        UserTxBufferFS[1] = 0x00;   /* Произошла ошибка - возвращаем 0х00 */
                        break;
                    }
                    for (uint16_t i = 0; i < (dataEndNumber - dataEndNumber); ++i) {
                        memcpy(&DevNVRAM.calibration_table.dacValB_m12[i + dataStartNumber],
                               (Buf + 2) + 2 * sizeof(uint16_t) + (i * 2),
                               sizeof(uint16_t));
                    }
                    break;
                }
                case 0x02 :
                {
                    if (dataStartNumber >= MAX_VAL_M27 ||
                        dataEndNumber > MAX_VAL_M27) {
                        UserTxBufferFS[1] = 0x00;   /* Произошла ошибка - возвращаем 0х00 */
                        break;
                    }
                    for (uint16_t i = 0; i < (dataEndNumber - dataEndNumber); ++i) {
                        memcpy(&DevNVRAM.calibration_table.dacValA_m27[i + dataStartNumber],
                               (Buf + 2) + 2 * sizeof(uint16_t) + (i * 2),
                               sizeof(uint16_t));
                    }
                    break;
                }
                case 0x03 :
                {
                    if (dataStartNumber >= MAX_VAL_M27 ||
                        dataEndNumber > MAX_VAL_M27) {
                        UserTxBufferFS[1] = 0x00;   /* Произошла ошибка - возвращаем 0х00 */
                        break;
                    }
                    for (uint16_t i = 0; i < (dataEndNumber - dataEndNumber); ++i) {
                        memcpy(&DevNVRAM.calibration_table.dacValB_m27[i + dataStartNumber],
                               (Buf + 2) + 2 * sizeof(uint16_t) + (i * 2),
                               sizeof(uint16_t));
                    }
                    break;
                }
                default :
                    UserTxBufferFS[1] = 0x00;   /* Произошла ошибка - возвращаем 0х00 */
                    break;
            };
//            CDC_Transmit_FS(Buf, *Len);

            UserTxBufferFS[0] = cmd;                                                            //1         ->1
            memcpy(UserTxBufferFS + 2, &dataStartNumber, sizeof(uint16_t));                     //2+2       ->4
            memcpy(UserTxBufferFS + 2 + sizeof(uint16_t), &dataEndNumber, sizeof(uint16_t));    //2+2+2     ->6
            UserTxBufferFS[2 + 2 * sizeof(uint16_t) + 1] = 0x00;                                //2+2*2+1   ->7

//            CDC_Transmit_FS(Buf, *Len);
//            uint8_t size = sizeof(UserTxBufferFS[2 + 2 * sizeof(uint16_t) + 1]);
//            CDC_Transmit_FS(&size, 1);
//            CDC_Transmit_FS(UserTxBufferFS, sizeof(UserTxBufferFS[2 + 2 * sizeof(uint16_t) + 1]));
        }

            break;
        case 0x0B :
            /* TODO: Отправка CRC 1-4 таблицы [0x0B][1-4][CRC(1-4)] answer: */
            break;
        case 0x0C :
            /* TODO: Прием длины калибровочной таблицы [0x0C][Длина][???] */
            break;
        case 0x0D :
            /* TODO: Запись во флеш калибровочной таблицы [0x0D]
             * data: 1B (0x00 - успешно; 0x01 - ошибка при записи); answer: 0x0D + 1B status */
        {
            if (*Len >= 2 && (Buf[1] == 0x02))
            {
                changeTableFlag = true;
                if ( flash_write_calibTable() != HAL_OK ) {
                    break;
                }
                printf("changeTableFlag = true!");
                UserTxBufferFS[1] = 0x00; // успешно
            }
            else {
                UserTxBufferFS[1] = 0x01; // ошибка
            }
            UserTxBufferFS[0] = cmd;
            CDC_Transmit_FS(UserTxBufferFS, 2);
            break;
        }
    };
    return HAL_OK;


//    else if (cmd == 0x0A)
//    {
//        //Прием калибровочной таблицы [0x0A][1-4][offset][count][data]
//        //FIXME: За одну посылку можно получить максимум 64 byte. Нужно организовать пакетную передачу
//        uint16_t tOffset, tCount, tData;
//        if (*Len >= 2 && Buf[1] >= 0x00 && Buf[1] <= 0x03)
//        {
//            if      (Buf[1] == 0x00)    //А_m12
//            {
//                /*
//                u8 Buf[0] = 0x0A
//                u8 Buf[1] = 0x00-0x03
//                ---------------------
//                u16 Buf[2] = offset u8
//                    Buf[3] = offset u8
//                ----------------------
//                u16 Buf[4] = count u8
//                    Buf[5] = count u8
//                ----------------------
//                u16 Buf[6] = data1 u8
//                    Buf[7] = data1 u8
//                ----------------------
//                ...
//                u16 Buf[count] = data[n-1]  u8
//                    Buf[count] = data[n]    u8
//                */
//                memcpy(&tOffset, Buf + 2, sizeof(uint16_t));
//                memcpy(&tCount, Buf + 2 + sizeof(uint16_t), sizeof(uint16_t));
//
//                for (uint16_t i = 0; i < tCount; i++)
//                {
//                    memcpy(&tData, Buf + 2 + 2 * sizeof(uint16_t) + i * 2, sizeof(uint16_t));
//                    DevNVRAM.calibration_table.dacValA_m12[i + tOffset] = tData;
//                }
//
//                changeTableFlag = true;
//
//
//                //answer: [0x0A]+[1-4]+[offset]+[count]+[status] (0x00 - сработал; 0x01 - не сработал)
//                /*
//                u8  Buf[0] = 0x0A
//                u8  Buf[1] = 0x01-0x04  // Номер таблицы
//                ---------------------
//                u16 Buf[2] = offset u8
//                    Buf[3] = offset u8
//                ----------------------
//                u16 Buf[4] = count u8
//                    Buf[5] = count u8
//                ----------------------
//                u8  Buf[6] = status u8  (0x00 - сработал; 0x01 - не сработал)
//                ----------------------
//                */
//                UserTxBufferFS[0] = cmd;                                                  //1           ->1
//                UserTxBufferFS[1] = 0x01;                                                 //1           ->2
//                memcpy(UserTxBufferFS + 2, &tOffset, sizeof(uint16_t));                   //2+2         ->4
//                memcpy(UserTxBufferFS + 2 + sizeof(uint16_t), &tCount, sizeof(uint16_t)); //2+2+2       ->6
//                UserTxBufferFS[2 + 2 * sizeof(uint16_t) + 1] = 0x00;                      //2+2*2+1     ->7
//
//                CDC_Transmit_FS(UserTxBufferFS, sizeof(UserTxBufferFS[2 + 2 * sizeof(uint16_t) + 1]));
//                return;
//                //--------------------------------------------------------------------------
//            }
//            //--------------------------------------------------------------------------
//            else if (Buf[1] == 0x01)    //B_m12
//            {
//                /*
//                u8 Buf[0] = 0x0A
//                u8 Buf[1] = 0x01-0x04
//                ---------------------
//                u16 Buf[2] = offset u8
//                    Buf[3] = offset u8
//                ----------------------
//                u16 Buf[4] = count u8
//                    Buf[5] = count u8
//                ----------------------
//                u16 Buf[6] = data1 u8
//                    Buf[7] = data1 u8
//                ----------------------
//                ...
//                u16 Buf[count] = data[n-1]  u8
//                    Buf[count] = data[n]    u8
//                */
//                memcpy(&tOffset, Buf + 2, sizeof(uint16_t));
//                memcpy(&tCount, Buf + 2 + sizeof(uint16_t), sizeof(uint16_t));
//
//                for (uint16_t i = 0; i < tCount; i++)
//                {
//                    memcpy(&tData, Buf + 2 + 2 * sizeof(uint16_t) + i * 2, sizeof(uint16_t));
//                    DevNVRAM.calibration_table.dacValB_m12[i + tOffset] = tData;
//                }
//
//                //answer: [0x0A]+[1-4]+[offset]+[count]+[status] (0x00 - сработал; 0x01 - не сработал)
//                /*
//                u8  Buf[0] = 0x0A
//                u8  Buf[1] = 0x01-0x04  // Номер таблицы
//                ---------------------
//                u16 Buf[2] = offset u8
//                    Buf[3] = offset u8
//                ----------------------
//                u16 Buf[4] = count u8
//                    Buf[5] = count u8
//                ----------------------
//                u8  Buf[6] = status u8  (0x00 - сработал; 0x01 - не сработал)
//                ----------------------
//                */
//                UserTxBufferFS[0] = cmd;                                                  //1           ->1
//                UserTxBufferFS[1] = 0x01;                                                 //1           ->2
//                memcpy(UserTxBufferFS + 2, &tOffset, sizeof(uint16_t));                   //2+2     ->4
//                memcpy(UserTxBufferFS + 2 + sizeof(uint16_t), &tCount, sizeof(uint16_t)); //2+2+2       ->6
//                UserTxBufferFS[2 + 2 * sizeof(uint16_t) + 1] = 0x00;                      //2+2*2+1 ->7
//
//                CDC_Transmit_FS(UserTxBufferFS, sizeof(UserTxBufferFS[2 + 2 * sizeof(uint16_t) + 1]));
//                return;
//                //--------------------------------------------------------------------------
//            }
//            //--------------------------------------------------------------------------
//            else if (Buf[1] == 0x02)    //A_m27
//            {
//                /*
//                u8 Buf[0] = 0x0A
//                u8 Buf[1] = 0x01-0x04
//                ---------------------
//                u16 Buf[2] = offset u8
//                    Buf[3] = offset u8
//                ----------------------
//                u16 Buf[4] = count u8
//                    Buf[5] = count u8
//                ----------------------
//                u16 Buf[6] = data1 u8
//                    Buf[7] = data1 u8
//                ----------------------
//                ...
//                u16 Buf[count] = data[n-1]  u8
//                    Buf[count] = data[n]    u8
//                */
//                memcpy(&tOffset, Buf + 2, sizeof(uint16_t));
//                memcpy(&tCount, Buf + 2 + sizeof(uint16_t), sizeof(uint16_t));
//
//                for (uint16_t i = 0; i < tCount; i++)
//                {
//                    memcpy(&tData, Buf + 2 + 2 * sizeof(uint16_t) + i * 2, sizeof(uint16_t));
//                    DevNVRAM.calibration_table.dacValA_m27[i + tOffset] = tData;
//                }
//
//                //answer: [0x0A]+[1-4]+[offset]+[count]+[status] (0x00 - сработал; 0x01 - не сработал)
//                /*
//                u8  Buf[0] = 0x0A
//                u8  Buf[1] = 0x01-0x04  // Номер таблицы
//                ---------------------
//                u16 Buf[2] = offset u8
//                    Buf[3] = offset u8
//                ----------------------
//                u16 Buf[4] = count u8
//                    Buf[5] = count u8
//                ----------------------
//                u8  Buf[6] = status u8  (0x00 - сработал; 0x01 - не сработал)
//                ----------------------
//                */
//                UserTxBufferFS[0] = cmd;                                                  //1           ->1
//                UserTxBufferFS[1] = 0x01;                                                 //1           ->2
//                memcpy(UserTxBufferFS + 2, &tOffset, sizeof(uint16_t));                   //2+2     ->4
//                memcpy(UserTxBufferFS + 2 + sizeof(uint16_t), &tCount, sizeof(uint16_t)); //2+2+2       ->6
//                UserTxBufferFS[2 + 2 * sizeof(uint16_t) + 1] = 0x00;                      //2+2*2+1 ->7
//
//                CDC_Transmit_FS(UserTxBufferFS, sizeof(UserTxBufferFS[2 + 2 * sizeof(uint16_t) + 1]));
//                return;
//                //--------------------------------------------------------------------------
//            }
//            //--------------------------------------------------------------------------
//            else if (Buf[1] == 0x03)    //B_m27
//            {
//                /*
//                u8 Buf[0] = 0x0A
//                u8 Buf[1] = 0x01-0x04
//                ---------------------
//                u16 Buf[2] = offset u8
//                    Buf[3] = offset u8
//                ----------------------
//                u16 Buf[4] = count u8
//                    Buf[5] = count u8
//                ----------------------
//                u16 Buf[6] = data1 u8
//                    Buf[7] = data1 u8
//                ----------------------
//                ...
//                u16 Buf[count] = data[n-1]  u8
//                    Buf[count] = data[n]    u8
//                */
//                memcpy(&tOffset, Buf + 2, sizeof(uint16_t));
//                memcpy(&tCount, Buf + 2 + sizeof(uint16_t), sizeof(uint16_t));
//
//                for (uint16_t i = 0; i < tCount; i++)
//                {
//                    memcpy(&tData, Buf + 2 + 2 * sizeof(uint16_t) + i * 2, sizeof(uint16_t));
//                    DevNVRAM.calibration_table.dacValB_m27[i + tOffset] = tData;
//                }
//
//                //answer: [0x0A]+[1-4]+[offset]+[count]+[status] (0x00 - сработал; 0x01 - не сработал)
//                /*
//                u8  Buf[0] = 0x0A
//                u8  Buf[1] = 0x01-0x04  // Номер таблицы
//                ---------------------
//                u16 Buf[2] = offset u8
//                    Buf[3] = offset u8
//                ----------------------
//                u16 Buf[4] = count u8
//                    Buf[5] = count u8
//                ----------------------
//                u8  Buf[6] = status u8  (0x00 - сработал; 0x01 - не сработал)
//                ----------------------
//                */
//                UserTxBufferFS[0] = cmd;                                                  //1           ->1
//                UserTxBufferFS[1] = 0x01;                                                 //1           ->2
//                memcpy(UserTxBufferFS + 2, &tOffset, sizeof(uint16_t));                   //2+2     ->4
//                memcpy(UserTxBufferFS + 2 + sizeof(uint16_t), &tCount, sizeof(uint16_t)); //2+2+2       ->6
//                UserTxBufferFS[2 + 2 * sizeof(uint16_t) + 1] = 0x00;                      //2+2*2+1 ->7
//
//                CDC_Transmit_FS(UserTxBufferFS, sizeof(UserTxBufferFS[2 + 2 * sizeof(uint16_t) + 1]));
//                return;
//                //--------------------------------------------------------------------------
//            }
//            //--------------------------------------------------------------------------
//        }
//        UserTxBufferFS[0] = cmd;
//        UserTxBufferFS[1] = 0x01; // ошибка
//        CDC_Transmit_FS(UserTxBufferFS, 2);
}
