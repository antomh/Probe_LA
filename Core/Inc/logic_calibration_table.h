/*******************************************************************************
 * @File: logic_calibration_table.c
 * @Author: Kozlov-dev, A.
 * @Project: Probe_LA.c * @Microcontroller: STM32F103C8T
 * @Device: Probe_LA
 * @Date: 07.04.2021
 * @Purpose: Calibration table volt2dac
 *******************************************************************************/
#ifndef LOGIC_CALIBRATION_TABLE_H
#define LOGIC_CALIBRATION_TABLE_H

#include <main.h>
//--------------------------------------------------------------------------
#define FLASH_TABLE_START_ADDR		ADDR_FLASH_PAGE_127
#define FLASH_TABLE_STOP_ADDR		FLASH_TABLE_START_ADDR+FLASH_PAGE_SIZE
//--------------------------------------------------------------------------
#define MAGIC_KEY_DEFINE			0x48151623
#define HARDWIRE_DEFINE 			0x06
#define FIRMWARE_DEFINE 			0x05
#define SN_DEFINE 					0x1121001
//--------------------------------------------------------------------------
#define MAX_VAL_M12 				88//	шаг 0,2В в диапозоне [-5:12:0,2] 85  TODO:найти что за 3 значения?!
#define MAX_VAL_M27 				163//	шаг 0,2В в диапозоне [-30:30:0,2] 163*0.2= 32,6
//--------------------------------------------------------------------------
// Опорное напряжение ЦАП (в вольтах)
#define DAC_REF 4.096F

// Максимальное значение кода ЦАП
#define DAC_MAX 4096

// Макрос для перевода напряжения (в вольтах) в код ЦАП
//#define VLT_TO_DGT(V) (uint16_t)(((V) / DAC_REF) * DAC_MAX)
#define VLT_TO_DGT(V) (float)(((V) / DAC_REF) * DAC_MAX)


//--------------------------------------------------------------------------
typedef struct // 							4+4+4+176+176+326+326 = 1016 байт
{
	uint16_t Hardwire; //					2 байта
	uint16_t Firmware; //					2 байта
	uint32_t SN; //							4 байта

	uint32_t MagicNum; //0x4815162342		4 байта ==>4+4+2+2 = 12

	uint16_t dacValA_m12[MAX_VAL_M12]; //	88*2 = 176 байта
	uint16_t dacValB_m12[MAX_VAL_M12]; //	88*2 = 176 байта
	uint16_t dacValA_m27[MAX_VAL_M27]; //	163*2 = 326 байта
	uint16_t dacValB_m27[MAX_VAL_M27]; //	163*2 = 326 байта ==> 1004 + 12 = 1016

} Table_t;

struct FLASH_Sector {
	uint32_t 	data[256 - 2]; // 			254* 4 = 1016 байта (1016 байт)
	uint32_t 	NWrite; //					4 байта
	uint32_t 	CheckSum; //				4 байта ==>1016 + 4 + 4 = 1024
};

union NVRAM {
	Table_t 	calibration_table; //		1016 байт
	struct 		FLASH_Sector sector; //		1024 байт
	uint32_t	data32[256]; // 			1024 байт
	uint8_t		data16[256 * 2]; // 		1024 байт
	uint8_t		data8[256 * 4]; // 			1024 байт
};
//											1024 байт
//--------------------------------------------------------------------------
void crete_calibration_table(union NVRAM *DevNVRAM);
uint16_t find_value(union NVRAM *DevNVRAM, uint32_t Volt);


#endif /* LOGIC_CALIBRATION_TABLE_H */
