#ifndef __UNMGQS_HEADER
#define __UNMGQS_HEADER

//#include <vpptype.h> 
#include <visa.h>
#include "unmgqs_math.h"


#if defined(__cplusplus) || defined(__cplusplus__)
extern "C" {
#endif
/*----------------------------------------------------------------------*/
/*  Определения                                                         */
/*----------------------------------------------------------------------*/

#define UNMGQS_MODEL_CODE				((ViUInt16) 0x42)
//#define UNMGQS_MODEL_CODE				((ViUInt16) 0x2E)	//TMP!!!
	
#define UNMGQS_NCHANS					2

#define UNMGQS_CHAN_1					0	//канал 1
#define UNMGQS_CHAN_2					1	//канал 2
//#define UNMGQS_CHANS_ALL				2	//все каналы
	
#define UNMGQS_STATE_FREE				0x0	//МГКС в режиме ожидания (свободен)
#define UNMGQS_STATE_AWAITS_START_EVENT	0x1	//Программный пуск был произведен, ожидается приход запускающего события (если установлен запуск по событию)
#define UNMGQS_STATE_STARTED			0x2	//Запуск был произведен, идет отсчет задержки начала генерации (если была установлена задержка запуска)
#define UNMGQS_STATE_GENERATING			0x3	//Идет генерация сигнала
	
#define UNMGQS_RANGE_1V					0	//Диапазон 1 В
#define UNMGQS_RANGE_10V				1	//Диапазон 10 В
	
#define UNMGQS_OUT_CTRL					0	//На входы узла "Контроль"
#define UNMGQS_OUT_MEZ					1	//На выходы мезонина, default
	
#define UNMGQS_BIAS_MIN					-10	//Напряжение смещения - минимум
#define UNMGQS_BIAS_MAX					10	//Напряжение смещения - максимум
	
#define UNMGQS_R_LOAD_MIN				50	//Сопротивление нагрузки default (min = 25.0)
#define UNMGQS_R_LOAD_MAX				100e9	//Сопротивление нагрузки - максимум	
	
#define UNMGQS_SAMPLE_F_75				0	//Частота дискретизации ЦАП 75 МГц
#define UNMGQS_SAMPLE_F_150				1	//Частота дискретизации ЦАП 150 МГц
#define UNMGQS_SAMPLE_F_300				2	//Частота дискретизации ЦАП 300 МГц
#define UNMGQS_SAMPLE_F_600				3	//Частота дискретизации ЦАП 600 МГц, default
#define UNMGQS_SAMPLE_F_1200			4	//Частота дискретизации ЦАП 1200 МГц
	
#define UNMGQS_DATA_SPEED_75			0	//Скорость выдачи данных 75 МОтч/с
#define UNMGQS_DATA_SPEED_150			1	//Скорость выдачи данных 150 МОтч/с
#define UNMGQS_DATA_SPEED_300			2	//Скорость выдачи данных 300 МОтч/с, default
#define UNMGQS_DATA_SPEED_600			3	//Скорость выдачи данных 600 МОтч/с
	
#define UNMGQS_SOURCE_F_IN				0	//Источник ОЧ: внутренний, default
#define UNMGQS_SOURCE_F_OUT				1	//Источник ОЧ: внешний
	
#define UNMGQS_SF_OUTPUT_OFF			0	//Выдача ОЧ наружу - выкл., default
#define UNMGQS_SF_OUTPUT_ON				1	//Выдача ОЧ наружу - вкл.

#define UNMGQS_SW_OFF					0	//линия канала отключена
#define UNMGQS_SW_DIRECT				1	//линия канала - прямой выход
#define UNMGQS_SW_INVERS				2	//линия канала - инверсный выход
	
#define UNMGQS_QM_HB1_OFF				0x0
#define UNMGQS_QM_HB1_1					0x1
#define UNMGQS_QM_HB1_2					0x2
#define UNMGQS_QM_HB1_3					0x3
#define UNMGQS_QM_HB1_4					0x4
	
#define UNMGQS_QM_HB2_OFF				0x0
#define UNMGQS_QM_HB2_1					0x1
#define UNMGQS_QM_HB2_2					0x2
#define UNMGQS_QM_HB2_3					0x3
#define UNMGQS_QM_HB2_4					0x4
#define UNMGQS_QM_HB2_5					0x5
#define UNMGQS_QM_HB2_6					0x6
#define UNMGQS_QM_HB2_7					0x7
#define UNMGQS_QM_HB2_8					0x8	
	
#define UNMGQS_QM_HB3_OFF				0x0
#define UNMGQS_QM_HB3_1					0x1
#define UNMGQS_QM_HB3_2					0x2
#define UNMGQS_QM_HB3_3					0x3
#define UNMGQS_QM_HB3_4					0x4
#define UNMGQS_QM_HB3_5					0x5
#define UNMGQS_QM_HB3_6					0x6
#define UNMGQS_QM_HB3_7					0x7
#define UNMGQS_QM_HB3_8					0x8
	
#define UNMGQS_QM_FREQ_NCO_MIN			0
#define UNMGQS_QM_FREQ_NCO_MAX			600e6
	
#define UNMGQS_QM_SIDEBAND_STRAIGHT		0
#define UNMGQS_QM_SIDEBAND_INVERSE		1	
	
#define UNMGQS_MODE_AWG					0x0		//Режим ГСПФ (AWG)
#define UNMGQS_MODE_AFG					0x1		//Режим Генератор функций (AFG)
	
#define UNMGQS_START_SRC_PROG			0x0		//Источник запуска: программа
#define UNMGQS_START_SRC_CMD			0x1		//Источник запуска: команда программы
#define UNMGQS_START_SRC_INPUT			0x2		//Источник запуска: вход "Запуск"
#define UNMGQS_START_SRC_NM				0x3		//Источник запуска: запуск от носителя
#define UNMGQS_START_EVENT_FRONT		0x0		//Событие запуска по входу "Запуск": фронт
#define UNMGQS_START_EVENT_CUT			0x1		//Событие запуска по входу "Запуск": срез
#define UNMGQS_START_DELAY_MIN			0		//Задержка старта, сек - минимум
#define UNMGQS_START_DELAY_MAX			30		//Задержка старта, сек - максимум
	
#define UNMGQS_AWG_MODE_LOOP			0x0		//Режим выдачи: циклический
#define UNMGQS_AWG_MODE_CONT			0x1		//Режим выдачи: непрерывный
#define UNMGQS_AWG_MODE_SEQ				0x0		//Режим запуска ГСПФ: на всю последовательность
#define UNMGQS_AWG_MODE_PACK			0x1		//Режим запуска ГСПФ: на каждый пакет
	
#define UNMGQS_ADC_INPUT_I				0x0		// проверка выхода канала 1
#define UNMGQS_ADC_INPUT_Q				0x1		// проверка выхода канала 2
#define UNMGQS_ADC_INPUT_CTRL1_1		0x2		// проверка входа Контроль 1:1
#define UNMGQS_ADC_INPUT_CTRL1_5		0x3		// проверка входа Контроль 1:5
	
#define UNMGQS_RAM_TEST_RUNNING_0		0x0		// Тест ОЗУ Бегущий ноль
#define UNMGQS_RAM_TEST_RUNNING_1		0x1		// Тест ОЗУ Бегущая единица
#define UNMGQS_RAM_TEST_ADDRESS_16		0x2		// Тест ОЗУ Адресный 16 разрядов
#define UNMGQS_RAM_TEST_ADDRESS_32		0x3		// Тест ОЗУ Адресный 32 разряда
	

#define UNMGQS_NUM_CYCLES_MIN			1
#define UNMGQS_NUM_CYCLES_MAX			(1<<16)
#define UNMGQS_NUM_PACKS_MIN			1
#define UNMGQS_NUM_PACKS_MAX			(1<<13)
#define UNMGQS_NUM_SAMPLES_MIN			8
#define UNMGQS_NUM_SAMPLES_MAX			(0x7FFFFFFF)
	
#define UNMGQS_AFG_AMPL_MIN				0   		//Амплитуда сигнала ГФ, мин
#define UNMGQS_AFG_AMPL_MAX				10			//Амплитуда сигнала ГФ, макс
#define UNMGQS_AFG_FREQ_MIN				0.06	   	//Частота сигнала ГФ, мин
#define UNMGQS_AFG_FREQ_MAX				150 * 1e6	//Частота сигнала ГФ, макс
#define UNMGQS_AFG_PHASE_MIN			0   		//Фаза сигнала ГФ, мин
#define UNMGQS_AFG_PHASE_MAX			360			//Фаза сигнала ГФ, макс
	
#define UNMGQS_AFG_GEN_DFUSE			0x0			//Режим генерации ГФ, Цифровой синтез
#define UNMGQS_AFG_GEN_MEM				0x1			//Режим генерации ГФ, Воспроизведение из памяти

//Типы модуляции ГФ
#define UNMGQS_NO_MODUL					0x0			//Без модуляции
#define UNMGQS_MODUL_LCM				0x1			//Линейно-частотная модуляция
#define UNMGQS_MODUL_AM					0x2			//Амплитудная модуляция
#define UNMGQS_MODUL_CM					0x3			//Частотная модуляция
#define UNMGQS_MODUL_FM					0x4			//Фазовая модуляция
	
#define UNMGQS_MODUL_F_MIN				0.0			//Модулирующая частота, мин, Гц
#define UNMGQS_MODUL_F_MAX				2e6			//Модулирующая частота, макс, Гц	
#define UNMGQS_MODUL_INDEX_MIN			0			//Индекс модуляции (АМ), мин, %
#define UNMGQS_MODUL_INDEX_MAX			100			//Индекс модуляции (АМ), макс, %
#define UNMGQS_MODUL_F_DEV_MIN			0			//Девиация частоты (ЧМ, ЛЧМ), мин, Гц
#define UNMGQS_MODUL_F_DEV_MAX			75e6		//Девиация частоты (ЧМ, ЛЧМ), макс, Гц
#define UNMGQS_MODUL_P_DEV_MIN			0			//Девиация фазы (ФМ), мин,°
#define UNMGQS_MODUL_P_DEV_MAX			360			//Девиация фазы (ФМ), макс,°
	
#define UNMGQS_SQL_AMPL_H_MIN			-10			//Амплитуда H, мин, В
#define UNMGQS_SQL_AMPL_H_MAX			10			//Амплитуда H, макс, В
#define UNMGQS_SQL_AMPL_L_MIN			-10			//Амплитуда L, мин, В
#define UNMGQS_SQL_AMPL_L_MAX			10			//Амплитуда L, макс, В
#define UNMGQS_SQL_SHIFT_MIN			-10			//Смещение сигнала, мин, В
#define UNMGQS_SQL_SHIFT_MAX			10			//Смещение сигнала, макс, В
	
#define UNMGQS_NSAMPLE_MIN				1			// Количество сэмплов, мин
#define UNMGQS_NSAMPLE_MAX				1024		// Количество сэмплов, макс
#define UNMGQS_TSAMPLE_MIN				0			// Период дискретизации, мин
#define UNMGQS_TSAMPLE_MAX				0.2e-3		// Период дискретизации, макс
	
#define UNMGQS_ADDR_MIN					0				// минимальное значение адреса FIFO
#define UNMGQS_ADDR_MAX					(0x3FFFFFFF)	// максимальное значение адреса FIFO

	
// Данные РПЗУ
#define   UNMGQS_ATTR_FLASH_STRUCT     1
#define   UNMGQS_ATTR_FLASH_SAVE_DEF   2

// перенесли в unmgqs_math
/*
#pragma pack(push, 4)
typedef struct _UNMGQS_DRAM
{
	//CRC32
	unsigned int crc32;
	
	// AUX_DAC[chan][range]
	ViUInt16 AUX_DAC[2][2];
	// DACgain[chan][range]
	ViUInt16 DACgain[2][2];
	// N_OFFSET[chan]
	ViInt16 N_OFFSET[2];
	// K_OFFSET[chan]
	ViReal64 K_OFFSET[2];
	// N_ADC[inputADC]
	ViReal64 N_ADC[4];
	// K_ADC[inputADC]
	ViReal64 K_ADC[4];
	
	// в формате HH:MM:SS MM-DD-YYYY
	ViChar dateEE[32];		//дата данных калибровки
	
} UNMGQS_DRAM, *UNMGQS_DRAM_SP;
#pragma pack(pop)
*/

/*----------------------------------------------------------------------*/
/*  Номера Ошибок/Предупреждений                                        */
/*----------------------------------------------------------------------*/

#define UNMGQS_ERROR_OFFSET            	(_VI_ERROR + 0x3FFC0C00L)
#define UNMGQS_WARN_OFFSET             	(0x3FFC0C00L)

#define UNMGQS_ERROR_SELFTEST			(UNMGQS_ERROR_OFFSET + 0)
#define UNMGQS_ERROR_BUSY				(UNMGQS_ERROR_OFFSET + 1)
#define UNMGQS_INSTRUMENT_ERROR			(UNMGQS_ERROR_OFFSET + 2)
#define UNMGQS_EEPROM_ERROR				(UNMGQS_ERROR_OFFSET + 3)
#define UNMGQS_ERROR_NSUP_REFSRC		(UNMGQS_ERROR_OFFSET + 4)
#define UNMGQS_CONFIG_PLIS_ERROR		(UNMGQS_ERROR_OFFSET + 5)	// Ошибка конфигурации ПЛИС
#define UNMGQS_CONFIG_PLIS_T_ERROR		(UNMGQS_ERROR_OFFSET + 6)	// Превышение времени конфигурации ПЛИС
#define UNMGQS_ERROR_PWR				(UNMGQS_ERROR_OFFSET + 7)	// Неисправность узла питания мезонина. Работа с инструментом невозможна
#define UNMGQS_ERROR_CONFIG_PARAMS		(UNMGQS_ERROR_OFFSET + 8)	// Ошибка конфигурации. Недопустимое сочетание параметров
#define UNMGQS_ERROR_PLL_CALIBR			(UNMGQS_ERROR_OFFSET + 9)	// Калибровка PLL не завершена
#define UNMGQS_ERROR_PLL_CONFIG			(UNMGQS_ERROR_OFFSET + 10)	// Ошибка конфигурации PLL
#define UNMGQS_ERROR_CALL_CONFIGCHAN	(UNMGQS_ERROR_OFFSET + 11)	// Ошибка: сначала нужно вызвать функцию unmgqs_config_chan
#define UNMGQS_ERROR_CALL_CONFIGSAMPL_F	(UNMGQS_ERROR_OFFSET + 12)	// Ошибка: сначала нужно вызвать функцию unmgqs_config_sample_freq
#define UNMGQS_ERROR_KOUT_DIFFERS		(UNMGQS_ERROR_OFFSET + 13)	// Ошибка: для подстройки каналов необходимы одинаковые значения диапазона и сопротивления нагрузки на каждом канале
#define UNMGQS_ERROR_FREQ_NCO_DATASPEED	(UNMGQS_ERROR_OFFSET + 14)	// Ошибка: значение частоты NCO превышает допустимое для установленной скорости выдачи данных
//AWG
#define UNMGQS_ERROR_CALL_CONFIG_AWG	(UNMGQS_ERROR_OFFSET + 15)	// Ошибка: сначала нужно вызвать функцию unmgqs_config_awg  
#define UNMGQS_ERROR_READ_FIFO			(UNMGQS_ERROR_OFFSET + 16)	// Ошибка: ошибка чтения данных FIFO
#define UNMGQS_ERROR_WRITE_FIFO			(UNMGQS_ERROR_OFFSET + 17)	// Ошибка: ошибка записи данных FIFO
#define UNMGQS_ERROR_AWG_DIVIS			(UNMGQS_ERROR_OFFSET + 18)	// Ошибка: область памяти для канала ГСПФ не кратна 8

// Ошибки калибровки
#define UNMGQS_ERROR_CALIBR_HP3458A		(UNMGQS_ERROR_OFFSET + 19)	// Ошибка калибровки: не найден мультиметр Agilent 3458A. Калибровка не возможна
	
#define UNMGQS_ERROR_CALIBR_NULL(chan, range)	(UNMGQS_ERROR_OFFSET + 20 + ((chan) + ((range) + 2) * 2))	// Ошибка калибровки: калибровка смещения нуля канала chan диапазона range завершена с ошибкой
#define UNMGQS_ERROR_CALIBR_GAIN(chan, range)	(UNMGQS_ERROR_OFFSET + 30 + ((chan) + ((range) + 2) * 2))	// Ошибка калибровки: калибровка коэффициента усиления канала chan диапазона range завершена с ошибкой
#define UNMGQS_ERROR_CALIBR_N_K_OFFSET(chan)	(UNMGQS_ERROR_OFFSET + 40 + (chan))	// Ошибка калибровки: калибровка точности установки напряжения смещения канала chan диапазона 10В завершена с ошибкой
#define UNMGQS_ERROR_CALIBR_N_ADC(input)	(UNMGQS_ERROR_OFFSET + 50 + (input))	// Ошибка калибровки АЦП: калибровка смещения АЦП для входа input прошла с ошибкой
#define UNMGQS_ERROR_CALIBR_K_ADC(input)	(UNMGQS_ERROR_OFFSET + 60 + (input))	// Ошибка калибровки АЦП: калибровка диапазона АЦП для входа input прошла с ошибкой
#define UNMGQS_ERROR_CALIBR_LOAD_ERROR	(UNMGQS_ERROR_OFFSET + 70)	// Ошибка загрузки калибровочных данных: контрольные суммы не совпадают
#define UNMGQS_ERROR_CALIBR_STOPPED		(UNMGQS_ERROR_OFFSET + 71)	// Калибровка была остановлена по требованию оператора

#define UNMGQS_ERROR_SELFTEST_MEMORY	(UNMGQS_ERROR_OFFSET + 72)	// Ошибка самоконтроля: не хватает памяти для проведения тестов
#define UNMGQS_ERROR_MEMORY				(UNMGQS_ERROR_OFFSET + 73)	// Ошибка: недостаточно памяти для выполнения операции
#define UNMGQS_ERROR_RAM_TEST			(UNMGQS_ERROR_OFFSET + 74)	// Ошибка теста ОЗУ: прочитанные/записанные данные не совпадают
#define UNMGQS_ERROR_OK_OFF_1			(UNMGQS_ERROR_OFFSET + 75)	// Ошибка теста ОК Отключен 1: прочитанные/записанные данные не совпадают



#define UNMGQS_ERROR_RG(i)				(UNMGQS_ERROR_OFFSET + 0x100 + (i))
					
#define UNMGQS_WARN_INIT_BAD         	(UNMGQS_WARN_OFFSET + 0)
#define UNMGQS_WARN_RAM_SFT				(UNMGQS_WARN_OFFSET + 1)	// Ошибка самоконтроля ОЗУ инструмента

/*----------------------------------------------------------------------*/
/*  Стандартные Функции                                                 */
/*----------------------------------------------------------------------*/
ViStatus _VI_FUNC unmgqs_init (ViRsrc rsrcName, ViBoolean IDquery, ViBoolean doReset, ViSession *mezvi);

ViStatus _VI_FUNC unmgqs_connect (ViSession mvi, ViSession vi, ViUInt16 m_num, ViBoolean IDquery, ViBoolean doReset);

ViStatus _VI_FUNC unmgqs_reset (ViSession mvi);

ViStatus _VI_FUNC unmgqs_self_test (ViSession mvi, ViPInt16 p_result, ViChar message[]);

//Проверка уровней напряжения с мультиметром
ViStatus _VI_FUNC unmgqs_test_AFG (ViSession mvi, ViSession viHP3458, ViUInt16 chan, ViPInt16 p_result, ViChar message[]);

//Тест ОЗУ
ViStatus _VI_FUNC unmgqs_test_RAM (ViSession mvi, ViUInt32 initialAddress, ViUInt16 numKiloSamples, ViUInt16 ramTestType, ViBoolean readOnly, ViPInt16 p_result, ViChar message[]);


ViStatus _VI_FUNC unmgqs_test_OK_Off1 (ViSession mvi, ViInt16 *p_result, ViChar message[]);
/*

ViStatus _VI_FUNC unmgqs_test_ok2 (ViSession mvi, 
									ViInt32 chan, 
									ViInt32 line,
									ViInt16 *result,
									ViChar testMessage[]);
*/

//typedef  ViInt16 (_VI_FUNCH * UNMEZONIN_SFT_INTERFACE)(ViSession mvi,ViUInt16 chan,
//				ViInt16 result, ViString message, void* userData); 

//ViStatus _VI_FUNC unmgqs_sft_interface (ViSession mvi,  UNMEZONIN_SFT_INTERFACE sftInterface, void *userData);

ViStatus _VI_FUNC unmgqs_error_query (ViSession mvi, ViPInt32 p_error, ViChar message[]);

ViStatus _VI_FUNC unmgqs_error_message (ViSession mvi, ViStatus status, ViChar message[]);

ViStatus _VI_FUNC unmgqs_revision_query (ViSession mvi, ViChar soft_rev[], ViChar instr_rev[]);

ViStatus _VI_FUNC unmgqs_close (ViSession mvi);


/*----------------------------------------------------------------------*/
/*  Прикладные Функции                                                  */
/*----------------------------------------------------------------------*/
//--------------------Функции управления/состояния------------------------
ViStatus _VI_FUNC unmgqs_start (ViSession mvi);

ViStatus _VI_FUNC unmgqs_prog_start (ViSession mvi);

ViStatus _VI_FUNC unmgqs_stop (ViSession mvi);

ViStatus _VI_FUNC unmgqs_state (ViSession mvi, ViPUInt16 state, ViPInt32 error);



//-------------------------Конфигурация МГКС------------------------------
//Установка параметров каналов
ViStatus _VI_FUNC unmgqs_config_chan (ViSession mvi, ViUInt16 chan_output, ViUInt16 chan, ViBoolean state, ViUInt16 range, ViReal64 Rn, ViReal64 Us);
//Запрос параметров каналов
ViStatus _VI_FUNC unmgqs_config_chan_q (ViSession mvi, ViPUInt16 chan_output, ViUInt16 chan, ViPBoolean state, ViPUInt16 range, ViPReal64 Rn, ViPReal64 Us);

//Установка частоты дискретизации
ViStatus _VI_FUNC unmgqs_config_sample_freq (ViSession mvi, ViUInt16 sampleFreq, ViUInt16 dataSpeed);
//Запрос частоты дискретизации
ViStatus _VI_FUNC unmgqs_config_sample_freq_q (ViSession mvi, ViPUInt16 sampleFreq, ViPUInt16 dataSpeed);

//Установка источника опорной частоты и параметра выдачи ОЧ наружу
ViStatus _VI_FUNC unmgqs_config_source_freq (ViSession mvi, ViUInt16 sourceFreq, ViUInt16 outputSourceFreq);
//Запрос источника опорной частоты, параметра выдачи ОЧ наружу, наличие ОЧ и состояние LockDetect
ViStatus _VI_FUNC unmgqs_config_source_freq_q (ViSession mvi, ViPUInt16 sourceFreq, ViPUInt16 outputSourceFreq, ViPBoolean SFstate, ViPBoolean LockDetect);


//Установка режима работы МГКС
ViStatus _VI_FUNC unmgqs_config_mode (ViSession mvi, ViUInt16 mode);
//Запрос режима работы МГКС
ViStatus _VI_FUNC unmgqs_config_mode_q (ViSession mvi, ViPUInt16 mode);

//Подстройка каналов
ViStatus _VI_FUNC unmgqs_adjust_chans (ViSession mvi, ViBoolean adjustIQ, ViReal64 Uoff_I, ViReal64 Uoff_Q, ViReal64 dF);
//Запрос подстроечных коэффициентов каналов
ViStatus _VI_FUNC unmgqs_adjust_chans_q (ViSession mvi, ViPBoolean adjustIQ, ViPReal64 Uoff_I, ViPReal64 Uoff_Q, ViPReal64 dF);

//Установка параметров запуска
ViStatus _VI_FUNC unmgqs_config_start (ViSession mvi, ViUInt16 startSource, ViUInt16 startEventForm, ViReal64 startDelay);
//Запрос параметров запуска
ViStatus _VI_FUNC unmgqs_config_start_q (ViSession mvi, ViPUInt16 startSource, ViPUInt16 startEventForm, ViPReal64 startDelay);

//Установка параметров квадратурного сигнала
//1. Установка интерполирующих фильтров HB1, HB2, HB3
ViStatus _VI_FUNC unmgqs_config_filters (ViSession mvi, ViUInt16 HB1, ViUInt16 HB2, ViUInt16 HB3);
//Запрос параметров квадратурного сигнала
//1. Запрос параметров интерполирующих фильтров HB1, HB2, HB3
ViStatus _VI_FUNC unmgqs_config_filters_q (ViSession mvi, ViPUInt16 HB1, ViPUInt16 HB2, ViPUInt16 HB3);

//2. Установка параметров модуляции NCO (для режима ГСПФ)
ViStatus _VI_FUNC unmgqs_config_NCO (ViSession mvi, ViBoolean modulNCO, ViBoolean attenuateNCO, ViReal64 freqNCO);
//2. Запрос параметров модуляции NCO (для режима ГСПФ)
ViStatus _VI_FUNC unmgqs_config_NCO_q (ViSession mvi, ViPBoolean modulNCO, ViPBoolean attenuateNCO, ViPReal64 freqNCO);

//3. Конфигурация квадратурного сигнала
ViStatus _VI_FUNC unmgqs_config_QS (ViSession mvi, ViBoolean premodul, ViBoolean filterSinX, ViUInt16 sideBand, ViBoolean doubleIData);
//3. Запрос параметров квадратурного сигнала
ViStatus _VI_FUNC unmgqs_config_QS_q (ViSession mvi, ViPBoolean premodul, ViPBoolean filterSinX, ViPUInt16 sideBand, ViPBoolean doubleIData);


//-------------------------Конфигурация ГСПФ------------------------------

//Установка параметров выдачи ГСПФ
ViStatus _VI_FUNC unmgqs_config_awg (ViSession mvi, ViUInt16 awgMode, ViUInt16 awgStartMode, ViUInt16 numCycles, ViUInt16 numPacks, ViUInt32 numSamples);
//Запрос параметров выдачи ГСПФ
ViStatus _VI_FUNC unmgqs_config_awg_q (ViSession mvi, ViPUInt16 awgMode, ViPUInt16 awgStartMode, ViPUInt16 numCycles, ViPUInt16 numPacks, ViPUInt32 numSamples);

//Адресная запись напряжений в ОЗУ
ViStatus _VI_FUNC unmgqs_writeAWG (ViSession mvi, ViUInt32 adr, ViUInt32 n, ViReal64 data[]);
//Адресная запись кодов в ОЗУ
ViStatus _VI_FUNC unmgqs_writeCodeAWG (ViSession mvi, ViUInt32 adr, ViUInt32 n, ViUInt16 data[]);
//Адресное чтение напряжений из ОЗУ
ViStatus _VI_FUNC unmgqs_readAWG (ViSession mvi, ViUInt32 adr, ViUInt32 n, ViReal64 data[]);
//Адресное чтение кодов из ОЗУ
ViStatus _VI_FUNC unmgqs_readCodeAWG (ViSession mvi, ViUInt32 adr, ViUInt32 n, ViUInt16 data[]);

//Пакетная запись данных
ViStatus _VI_FUNC unmgqs_awg_writePacket (ViSession mvi, ViUInt16 chan, ViUInt16 packetNumber, ViUInt16 packetsToWrite, ViPReal64 chan1Data, ViPReal64 chan2Data, ViUInt32 arraySize);

//Пакетная запись данных в виде кодов
ViStatus _VI_FUNC unmgqs_awg_writePacket_codes (ViSession mvi, ViUInt16 chan, ViUInt16 packetNumber, ViUInt16 packetsToWrite, ViPUInt16 chan1Data, ViPUInt16 chan2Data, ViUInt32 arraySize);

//Пакетное чтение данных
ViStatus _VI_FUNC unmgqs_awg_readPacket (ViSession mvi, ViUInt16 chan, ViUInt16 packetNumber, ViUInt16 packetsToRead, ViPReal64 chan1Data, ViPReal64 chan2Data, ViUInt32 arraySize);

//Пакетное чтение данных в виде кодов
ViStatus _VI_FUNC unmgqs_awg_readPacket_codes (ViSession mvi, ViUInt16 chan, ViUInt16 packetNumber, ViUInt16 packetsToRead, ViPUInt16 chan1Data, ViPUInt16 chan2Data, ViUInt32 arraySize);


//-------------------------Конфигурация ГФ--------------------------------
//Установка параметров гармонического сигнала
ViStatus _VI_FUNC unmgqs_config_afg (ViSession mvi, ViUInt16 chan, ViReal64 ampl, ViReal64 freq, ViReal64 phase);
//Запрос параметров гармонического сигнала
ViStatus _VI_FUNC unmgqs_config_afg_q (ViSession mvi, ViUInt16 chan, ViPReal64 ampl, ViPReal64 freq, ViPReal64 phase);

//Задание режима генерации функций
ViStatus _VI_FUNC unmgqs_config_afg_gen (ViSession mvi, ViUInt16 chan, ViUInt16 genMode);
//Запрос режима генерации функций
ViStatus _VI_FUNC unmgqs_config_afg_gen_q (ViSession mvi, ViUInt16 chan, ViPUInt16 genMode);

//Установка параметров модуляции
ViStatus _VI_FUNC unmgqs_config_afg_modul (ViSession mvi, ViUInt16 chan, ViUInt16 modulType, ViReal64 modulFreq, ViReal64 modulIndex, ViReal64 freqDev, ViReal64 phaseDev);
//Запрос параметров модуляции
ViStatus _VI_FUNC unmgqs_config_afg_modul_q (ViSession mvi, ViUInt16 chan, ViPUInt16 modulType, ViPReal64 modulFreq, ViPReal64 modulIndex, ViPReal64 freqDev, ViPReal64 phaseDev);

//Установка ограничений уровня сигнала
ViStatus _VI_FUNC unmgqs_config_afg_signal (ViSession mvi, ViUInt16 chan, ViBoolean useLimits, ViReal64 ampl_h, ViReal64 ampl_l, ViReal64 shift);
//Запрос ограничений уровня сигнала
ViStatus _VI_FUNC unmgqs_config_afg_signal_q (ViSession mvi, ViUInt16 chan, ViPBoolean useLimits, ViPReal64 ampl_h, ViPReal64 ampl_l, ViPReal64 shift);

//Установка параметров режима воспроизведения из памяти
ViStatus _VI_FUNC unmgqs_afg_setData (ViSession mvi, ViUInt16 chan, ViPReal64 data, ViUInt16 Ns, ViReal64 Ts);
//Запрос параметров режима воспроизведения из памяти
ViStatus _VI_FUNC unmgqs_afg_getData (ViSession mvi, ViUInt16 chan, ViPReal64 data, ViPUInt16 Ns, ViPReal64 Ts);


#define UNMGQS_EVENT_RESET		1

//typedef  ViInt32(_VI_FUNCH * UNMGQS_HANDLER)(ViSession mvi, ViAddr *user_data, ViUInt32 reason); 

//ViStatus _VI_FUNC unmgqs_handler (ViSession mvi,  UNMGQS_HANDLER pfunc, ViAddr user_data);
/*----------------------------------------------------------------------*/
/*  Служебные Функции                                                   */
/*----------------------------------------------------------------------*/
//Запрос температуры
ViStatus _VI_FUNC unmgqs_get_temperature (ViSession mvi, ViPReal64 tCont, ViPReal64 tCard);

//Функция конфигурации ПЛИС
ViStatus _VI_FUNC unmgqs_config_plis (ViSession mvi);

//Опрос АЦП с возвратом значения напряжения
ViStatus _VI_FUNC unmgqs_ask_adc (ViSession mvi, ViUInt16 chan, ViPReal64 U);

//Опрос АЦП с возвратом кода
ViStatus _VI_FUNC unmgqs_ask_adc_code (ViSession mvi, ViUInt16 chan, ViPInt32 COD_ADC);

//Калибровка МГКС
ViStatus _VI_FUNC unmgqs_calibrate (ViSession mvi, ViSession viHP3458, ViUInt16 chan);

//Остановить калибровку МГКС
ViStatus _VI_FUNC unmgqs_stop_calibration (ViSession mvi);

//Калибровка смещение нуля  и коэффициента усиления  каналов
ViStatus _VI_FUNC unmgqs_calibrate_null_ampl (ViSession mvi, ViSession viHP3458, ViUInt16 chan, ViUInt16 range);

//Калибровка точности установки напряжения смещения
ViStatus _VI_FUNC unmgqs_calibrate_N_K_offset (ViSession mvi, ViSession viHP3458, ViUInt16 chan);

//Калибровка АЦП
ViStatus _VI_FUNC unmgqs_calibrate_ADC (ViSession mvi, ViChar message[]);

//Загрузка калибровочных коэффициентов из флешки
ViStatus _VI_FUNC unmgqs_load_CalibrationData_FromFlash (ViSession mvi);
//Запись калибровочных коэффициентов во флешку
ViStatus _VI_FUNC unmgqs_save_CalibrationData_ToFlash (ViSession mvi);

//Функции для получения значений калибровочных коэффициентов
ViStatus _VI_FUNC unmgqs_get_AUX_DAC (ViSession mvi, ViUInt16 chan, ViUInt16 range, ViPUInt16 AUX_DAC);
ViStatus _VI_FUNC unmgqs_get_DACgain (ViSession mvi, ViUInt16 chan, ViUInt16 range, ViPUInt16 DACgain);
ViStatus _VI_FUNC unmgqs_get_N_OFFSET (ViSession mvi, ViUInt16 chan, ViPInt16 N_OFFSET);
ViStatus _VI_FUNC unmgqs_get_K_OFFSET (ViSession mvi, ViUInt16 chan, ViPReal64 K_OFFSET);
ViStatus _VI_FUNC unmgqs_get_N_ADC (ViSession mvi, ViUInt16 chan, ViPReal64 N_ADC);
ViStatus _VI_FUNC unmgqs_get_K_ADC (ViSession mvi, ViUInt16 chan, ViPReal64 K_ADC);
//Получить текущие калибровочные коэффициенты
ViStatus _VI_FUNC unmgqs_get_calibration_data (ViSession mvi, UNMGQS_DRAM *dram);
//Получить дату последней калибровки
ViStatus _VI_FUNC unmgqs_get_calibration_date (ViSession mvi, ViChar date[]);

/****************************************************************************          
		Функции загрузки контроллеров
*****************************************************************************/ 
ViStatus _VI_FUNC unmgqs_readyPLD (ViSession vi);	  //++
ViStatus _VI_FUNC unmgqs_loadPLD (ViSession vi);	 //__   ПАНЕЛЬ
ViStatus _VI_FUNC unmgqs_prgPLD (ViSession vi);		//__	ПАНЕЛЬ
ViStatus _VI_FUNC unmgqs_vrfPLD (ViSession vi);	   //__	ПАНЕЛЬ  
ViStatus _VI_FUNC unmgqs_cmpVersions (ViSession vi);  //++
ViStatus _VI_FUNC unmgqs_readFlashVersion (ViSession vi, ViChar flash_rev[]);  //++
ViStatus _VI_FUNC unmgqs_readDataPLD (ViSession vi, void *data, ViUInt32 size);  //++
ViStatus _VI_FUNC unmgqs_writeDataPLD (ViSession vi, void *data, ViUInt32 size); //++ 


#if defined(__cplusplus) || defined(__cplusplus__)

}

#endif

#endif /* __UNMGQS_HEADER */
