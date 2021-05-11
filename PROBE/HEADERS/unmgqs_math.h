#ifndef _UNMGQS_MATH_HEADER_
#define _UNMGQS_MATH_HEADER_

#include <vpptype.h>

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


//--------------------------------------------------------------------------------
ViInt16 _VI_FUNC get_DACCODE(ViSession mvi, ViReal64 Uout, ViReal64 Kout);

//--------------------------------------------------------------------------------
ViReal64 _VI_FUNC get_Uout(ViSession mvi, ViInt16 dacCODE, ViReal64 Kout);

#endif
