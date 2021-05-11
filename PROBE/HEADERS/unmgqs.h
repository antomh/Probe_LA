#ifndef __UNMGQS_HEADER
#define __UNMGQS_HEADER

//#include <vpptype.h> 
#include <visa.h>
#include "unmgqs_math.h"


#if defined(__cplusplus) || defined(__cplusplus__)
extern "C" {
#endif
/*----------------------------------------------------------------------*/
/*  �����������                                                         */
/*----------------------------------------------------------------------*/

#define UNMGQS_MODEL_CODE				((ViUInt16) 0x42)
//#define UNMGQS_MODEL_CODE				((ViUInt16) 0x2E)	//TMP!!!
	
#define UNMGQS_NCHANS					2

#define UNMGQS_CHAN_1					0	//����� 1
#define UNMGQS_CHAN_2					1	//����� 2
//#define UNMGQS_CHANS_ALL				2	//��� ������
	
#define UNMGQS_STATE_FREE				0x0	//���� � ������ �������� (��������)
#define UNMGQS_STATE_AWAITS_START_EVENT	0x1	//����������� ���� ��� ����������, ��������� ������ ������������ ������� (���� ���������� ������ �� �������)
#define UNMGQS_STATE_STARTED			0x2	//������ ��� ����������, ���� ������ �������� ������ ��������� (���� ���� ����������� �������� �������)
#define UNMGQS_STATE_GENERATING			0x3	//���� ��������� �������
	
#define UNMGQS_RANGE_1V					0	//�������� 1 �
#define UNMGQS_RANGE_10V				1	//�������� 10 �
	
#define UNMGQS_OUT_CTRL					0	//�� ����� ���� "��������"
#define UNMGQS_OUT_MEZ					1	//�� ������ ��������, default
	
#define UNMGQS_BIAS_MIN					-10	//���������� �������� - �������
#define UNMGQS_BIAS_MAX					10	//���������� �������� - ��������
	
#define UNMGQS_R_LOAD_MIN				50	//������������� �������� default (min = 25.0)
#define UNMGQS_R_LOAD_MAX				100e9	//������������� �������� - ��������	
	
#define UNMGQS_SAMPLE_F_75				0	//������� ������������� ��� 75 ���
#define UNMGQS_SAMPLE_F_150				1	//������� ������������� ��� 150 ���
#define UNMGQS_SAMPLE_F_300				2	//������� ������������� ��� 300 ���
#define UNMGQS_SAMPLE_F_600				3	//������� ������������� ��� 600 ���, default
#define UNMGQS_SAMPLE_F_1200			4	//������� ������������� ��� 1200 ���
	
#define UNMGQS_DATA_SPEED_75			0	//�������� ������ ������ 75 ����/�
#define UNMGQS_DATA_SPEED_150			1	//�������� ������ ������ 150 ����/�
#define UNMGQS_DATA_SPEED_300			2	//�������� ������ ������ 300 ����/�, default
#define UNMGQS_DATA_SPEED_600			3	//�������� ������ ������ 600 ����/�
	
#define UNMGQS_SOURCE_F_IN				0	//�������� ��: ����������, default
#define UNMGQS_SOURCE_F_OUT				1	//�������� ��: �������
	
#define UNMGQS_SF_OUTPUT_OFF			0	//������ �� ������ - ����., default
#define UNMGQS_SF_OUTPUT_ON				1	//������ �� ������ - ���.

#define UNMGQS_SW_OFF					0	//����� ������ ���������
#define UNMGQS_SW_DIRECT				1	//����� ������ - ������ �����
#define UNMGQS_SW_INVERS				2	//����� ������ - ��������� �����
	
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
	
#define UNMGQS_MODE_AWG					0x0		//����� ���� (AWG)
#define UNMGQS_MODE_AFG					0x1		//����� ��������� ������� (AFG)
	
#define UNMGQS_START_SRC_PROG			0x0		//�������� �������: ���������
#define UNMGQS_START_SRC_CMD			0x1		//�������� �������: ������� ���������
#define UNMGQS_START_SRC_INPUT			0x2		//�������� �������: ���� "������"
#define UNMGQS_START_SRC_NM				0x3		//�������� �������: ������ �� ��������
#define UNMGQS_START_EVENT_FRONT		0x0		//������� ������� �� ����� "������": �����
#define UNMGQS_START_EVENT_CUT			0x1		//������� ������� �� ����� "������": ����
#define UNMGQS_START_DELAY_MIN			0		//�������� ������, ��� - �������
#define UNMGQS_START_DELAY_MAX			30		//�������� ������, ��� - ��������
	
#define UNMGQS_AWG_MODE_LOOP			0x0		//����� ������: �����������
#define UNMGQS_AWG_MODE_CONT			0x1		//����� ������: �����������
#define UNMGQS_AWG_MODE_SEQ				0x0		//����� ������� ����: �� ��� ������������������
#define UNMGQS_AWG_MODE_PACK			0x1		//����� ������� ����: �� ������ �����
	
#define UNMGQS_ADC_INPUT_I				0x0		// �������� ������ ������ 1
#define UNMGQS_ADC_INPUT_Q				0x1		// �������� ������ ������ 2
#define UNMGQS_ADC_INPUT_CTRL1_1		0x2		// �������� ����� �������� 1:1
#define UNMGQS_ADC_INPUT_CTRL1_5		0x3		// �������� ����� �������� 1:5
	
#define UNMGQS_RAM_TEST_RUNNING_0		0x0		// ���� ��� ������� ����
#define UNMGQS_RAM_TEST_RUNNING_1		0x1		// ���� ��� ������� �������
#define UNMGQS_RAM_TEST_ADDRESS_16		0x2		// ���� ��� �������� 16 ��������
#define UNMGQS_RAM_TEST_ADDRESS_32		0x3		// ���� ��� �������� 32 �������
	

#define UNMGQS_NUM_CYCLES_MIN			1
#define UNMGQS_NUM_CYCLES_MAX			(1<<16)
#define UNMGQS_NUM_PACKS_MIN			1
#define UNMGQS_NUM_PACKS_MAX			(1<<13)
#define UNMGQS_NUM_SAMPLES_MIN			8
#define UNMGQS_NUM_SAMPLES_MAX			(0x7FFFFFFF)
	
#define UNMGQS_AFG_AMPL_MIN				0   		//��������� ������� ��, ���
#define UNMGQS_AFG_AMPL_MAX				10			//��������� ������� ��, ����
#define UNMGQS_AFG_FREQ_MIN				0.06	   	//������� ������� ��, ���
#define UNMGQS_AFG_FREQ_MAX				150 * 1e6	//������� ������� ��, ����
#define UNMGQS_AFG_PHASE_MIN			0   		//���� ������� ��, ���
#define UNMGQS_AFG_PHASE_MAX			360			//���� ������� ��, ����
	
#define UNMGQS_AFG_GEN_DFUSE			0x0			//����� ��������� ��, �������� ������
#define UNMGQS_AFG_GEN_MEM				0x1			//����� ��������� ��, ��������������� �� ������

//���� ��������� ��
#define UNMGQS_NO_MODUL					0x0			//��� ���������
#define UNMGQS_MODUL_LCM				0x1			//�������-��������� ���������
#define UNMGQS_MODUL_AM					0x2			//����������� ���������
#define UNMGQS_MODUL_CM					0x3			//��������� ���������
#define UNMGQS_MODUL_FM					0x4			//������� ���������
	
#define UNMGQS_MODUL_F_MIN				0.0			//������������ �������, ���, ��
#define UNMGQS_MODUL_F_MAX				2e6			//������������ �������, ����, ��	
#define UNMGQS_MODUL_INDEX_MIN			0			//������ ��������� (��), ���, %
#define UNMGQS_MODUL_INDEX_MAX			100			//������ ��������� (��), ����, %
#define UNMGQS_MODUL_F_DEV_MIN			0			//�������� ������� (��, ���), ���, ��
#define UNMGQS_MODUL_F_DEV_MAX			75e6		//�������� ������� (��, ���), ����, ��
#define UNMGQS_MODUL_P_DEV_MIN			0			//�������� ���� (��), ���,�
#define UNMGQS_MODUL_P_DEV_MAX			360			//�������� ���� (��), ����,�
	
#define UNMGQS_SQL_AMPL_H_MIN			-10			//��������� H, ���, �
#define UNMGQS_SQL_AMPL_H_MAX			10			//��������� H, ����, �
#define UNMGQS_SQL_AMPL_L_MIN			-10			//��������� L, ���, �
#define UNMGQS_SQL_AMPL_L_MAX			10			//��������� L, ����, �
#define UNMGQS_SQL_SHIFT_MIN			-10			//�������� �������, ���, �
#define UNMGQS_SQL_SHIFT_MAX			10			//�������� �������, ����, �
	
#define UNMGQS_NSAMPLE_MIN				1			// ���������� �������, ���
#define UNMGQS_NSAMPLE_MAX				1024		// ���������� �������, ����
#define UNMGQS_TSAMPLE_MIN				0			// ������ �������������, ���
#define UNMGQS_TSAMPLE_MAX				0.2e-3		// ������ �������������, ����
	
#define UNMGQS_ADDR_MIN					0				// ����������� �������� ������ FIFO
#define UNMGQS_ADDR_MAX					(0x3FFFFFFF)	// ������������ �������� ������ FIFO

	
// ������ ����
#define   UNMGQS_ATTR_FLASH_STRUCT     1
#define   UNMGQS_ATTR_FLASH_SAVE_DEF   2

// ��������� � unmgqs_math
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
	
	// � ������� HH:MM:SS MM-DD-YYYY
	ViChar dateEE[32];		//���� ������ ����������
	
} UNMGQS_DRAM, *UNMGQS_DRAM_SP;
#pragma pack(pop)
*/

/*----------------------------------------------------------------------*/
/*  ������ ������/��������������                                        */
/*----------------------------------------------------------------------*/

#define UNMGQS_ERROR_OFFSET            	(_VI_ERROR + 0x3FFC0C00L)
#define UNMGQS_WARN_OFFSET             	(0x3FFC0C00L)

#define UNMGQS_ERROR_SELFTEST			(UNMGQS_ERROR_OFFSET + 0)
#define UNMGQS_ERROR_BUSY				(UNMGQS_ERROR_OFFSET + 1)
#define UNMGQS_INSTRUMENT_ERROR			(UNMGQS_ERROR_OFFSET + 2)
#define UNMGQS_EEPROM_ERROR				(UNMGQS_ERROR_OFFSET + 3)
#define UNMGQS_ERROR_NSUP_REFSRC		(UNMGQS_ERROR_OFFSET + 4)
#define UNMGQS_CONFIG_PLIS_ERROR		(UNMGQS_ERROR_OFFSET + 5)	// ������ ������������ ����
#define UNMGQS_CONFIG_PLIS_T_ERROR		(UNMGQS_ERROR_OFFSET + 6)	// ���������� ������� ������������ ����
#define UNMGQS_ERROR_PWR				(UNMGQS_ERROR_OFFSET + 7)	// ������������� ���� ������� ��������. ������ � ������������ ����������
#define UNMGQS_ERROR_CONFIG_PARAMS		(UNMGQS_ERROR_OFFSET + 8)	// ������ ������������. ������������ ��������� ����������
#define UNMGQS_ERROR_PLL_CALIBR			(UNMGQS_ERROR_OFFSET + 9)	// ���������� PLL �� ���������
#define UNMGQS_ERROR_PLL_CONFIG			(UNMGQS_ERROR_OFFSET + 10)	// ������ ������������ PLL
#define UNMGQS_ERROR_CALL_CONFIGCHAN	(UNMGQS_ERROR_OFFSET + 11)	// ������: ������� ����� ������� ������� unmgqs_config_chan
#define UNMGQS_ERROR_CALL_CONFIGSAMPL_F	(UNMGQS_ERROR_OFFSET + 12)	// ������: ������� ����� ������� ������� unmgqs_config_sample_freq
#define UNMGQS_ERROR_KOUT_DIFFERS		(UNMGQS_ERROR_OFFSET + 13)	// ������: ��� ���������� ������� ���������� ���������� �������� ��������� � ������������� �������� �� ������ ������
#define UNMGQS_ERROR_FREQ_NCO_DATASPEED	(UNMGQS_ERROR_OFFSET + 14)	// ������: �������� ������� NCO ��������� ���������� ��� ������������� �������� ������ ������
//AWG
#define UNMGQS_ERROR_CALL_CONFIG_AWG	(UNMGQS_ERROR_OFFSET + 15)	// ������: ������� ����� ������� ������� unmgqs_config_awg  
#define UNMGQS_ERROR_READ_FIFO			(UNMGQS_ERROR_OFFSET + 16)	// ������: ������ ������ ������ FIFO
#define UNMGQS_ERROR_WRITE_FIFO			(UNMGQS_ERROR_OFFSET + 17)	// ������: ������ ������ ������ FIFO
#define UNMGQS_ERROR_AWG_DIVIS			(UNMGQS_ERROR_OFFSET + 18)	// ������: ������� ������ ��� ������ ���� �� ������ 8

// ������ ����������
#define UNMGQS_ERROR_CALIBR_HP3458A		(UNMGQS_ERROR_OFFSET + 19)	// ������ ����������: �� ������ ���������� Agilent 3458A. ���������� �� ��������
	
#define UNMGQS_ERROR_CALIBR_NULL(chan, range)	(UNMGQS_ERROR_OFFSET + 20 + ((chan) + ((range) + 2) * 2))	// ������ ����������: ���������� �������� ���� ������ chan ��������� range ��������� � �������
#define UNMGQS_ERROR_CALIBR_GAIN(chan, range)	(UNMGQS_ERROR_OFFSET + 30 + ((chan) + ((range) + 2) * 2))	// ������ ����������: ���������� ������������ �������� ������ chan ��������� range ��������� � �������
#define UNMGQS_ERROR_CALIBR_N_K_OFFSET(chan)	(UNMGQS_ERROR_OFFSET + 40 + (chan))	// ������ ����������: ���������� �������� ��������� ���������� �������� ������ chan ��������� 10� ��������� � �������
#define UNMGQS_ERROR_CALIBR_N_ADC(input)	(UNMGQS_ERROR_OFFSET + 50 + (input))	// ������ ���������� ���: ���������� �������� ��� ��� ����� input ������ � �������
#define UNMGQS_ERROR_CALIBR_K_ADC(input)	(UNMGQS_ERROR_OFFSET + 60 + (input))	// ������ ���������� ���: ���������� ��������� ��� ��� ����� input ������ � �������
#define UNMGQS_ERROR_CALIBR_LOAD_ERROR	(UNMGQS_ERROR_OFFSET + 70)	// ������ �������� ������������� ������: ����������� ����� �� ���������
#define UNMGQS_ERROR_CALIBR_STOPPED		(UNMGQS_ERROR_OFFSET + 71)	// ���������� ���� ����������� �� ���������� ���������

#define UNMGQS_ERROR_SELFTEST_MEMORY	(UNMGQS_ERROR_OFFSET + 72)	// ������ ������������: �� ������� ������ ��� ���������� ������
#define UNMGQS_ERROR_MEMORY				(UNMGQS_ERROR_OFFSET + 73)	// ������: ������������ ������ ��� ���������� ��������
#define UNMGQS_ERROR_RAM_TEST			(UNMGQS_ERROR_OFFSET + 74)	// ������ ����� ���: �����������/���������� ������ �� ���������
#define UNMGQS_ERROR_OK_OFF_1			(UNMGQS_ERROR_OFFSET + 75)	// ������ ����� �� �������� 1: �����������/���������� ������ �� ���������



#define UNMGQS_ERROR_RG(i)				(UNMGQS_ERROR_OFFSET + 0x100 + (i))
					
#define UNMGQS_WARN_INIT_BAD         	(UNMGQS_WARN_OFFSET + 0)
#define UNMGQS_WARN_RAM_SFT				(UNMGQS_WARN_OFFSET + 1)	// ������ ������������ ��� �����������

/*----------------------------------------------------------------------*/
/*  ����������� �������                                                 */
/*----------------------------------------------------------------------*/
ViStatus _VI_FUNC unmgqs_init (ViRsrc rsrcName, ViBoolean IDquery, ViBoolean doReset, ViSession *mezvi);

ViStatus _VI_FUNC unmgqs_connect (ViSession mvi, ViSession vi, ViUInt16 m_num, ViBoolean IDquery, ViBoolean doReset);

ViStatus _VI_FUNC unmgqs_reset (ViSession mvi);

ViStatus _VI_FUNC unmgqs_self_test (ViSession mvi, ViPInt16 p_result, ViChar message[]);

//�������� ������� ���������� � ������������
ViStatus _VI_FUNC unmgqs_test_AFG (ViSession mvi, ViSession viHP3458, ViUInt16 chan, ViPInt16 p_result, ViChar message[]);

//���� ���
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
/*  ���������� �������                                                  */
/*----------------------------------------------------------------------*/
//--------------------������� ����������/���������------------------------
ViStatus _VI_FUNC unmgqs_start (ViSession mvi);

ViStatus _VI_FUNC unmgqs_prog_start (ViSession mvi);

ViStatus _VI_FUNC unmgqs_stop (ViSession mvi);

ViStatus _VI_FUNC unmgqs_state (ViSession mvi, ViPUInt16 state, ViPInt32 error);



//-------------------------������������ ����------------------------------
//��������� ���������� �������
ViStatus _VI_FUNC unmgqs_config_chan (ViSession mvi, ViUInt16 chan_output, ViUInt16 chan, ViBoolean state, ViUInt16 range, ViReal64 Rn, ViReal64 Us);
//������ ���������� �������
ViStatus _VI_FUNC unmgqs_config_chan_q (ViSession mvi, ViPUInt16 chan_output, ViUInt16 chan, ViPBoolean state, ViPUInt16 range, ViPReal64 Rn, ViPReal64 Us);

//��������� ������� �������������
ViStatus _VI_FUNC unmgqs_config_sample_freq (ViSession mvi, ViUInt16 sampleFreq, ViUInt16 dataSpeed);
//������ ������� �������������
ViStatus _VI_FUNC unmgqs_config_sample_freq_q (ViSession mvi, ViPUInt16 sampleFreq, ViPUInt16 dataSpeed);

//��������� ��������� ������� ������� � ��������� ������ �� ������
ViStatus _VI_FUNC unmgqs_config_source_freq (ViSession mvi, ViUInt16 sourceFreq, ViUInt16 outputSourceFreq);
//������ ��������� ������� �������, ��������� ������ �� ������, ������� �� � ��������� LockDetect
ViStatus _VI_FUNC unmgqs_config_source_freq_q (ViSession mvi, ViPUInt16 sourceFreq, ViPUInt16 outputSourceFreq, ViPBoolean SFstate, ViPBoolean LockDetect);


//��������� ������ ������ ����
ViStatus _VI_FUNC unmgqs_config_mode (ViSession mvi, ViUInt16 mode);
//������ ������ ������ ����
ViStatus _VI_FUNC unmgqs_config_mode_q (ViSession mvi, ViPUInt16 mode);

//���������� �������
ViStatus _VI_FUNC unmgqs_adjust_chans (ViSession mvi, ViBoolean adjustIQ, ViReal64 Uoff_I, ViReal64 Uoff_Q, ViReal64 dF);
//������ ������������ ������������� �������
ViStatus _VI_FUNC unmgqs_adjust_chans_q (ViSession mvi, ViPBoolean adjustIQ, ViPReal64 Uoff_I, ViPReal64 Uoff_Q, ViPReal64 dF);

//��������� ���������� �������
ViStatus _VI_FUNC unmgqs_config_start (ViSession mvi, ViUInt16 startSource, ViUInt16 startEventForm, ViReal64 startDelay);
//������ ���������� �������
ViStatus _VI_FUNC unmgqs_config_start_q (ViSession mvi, ViPUInt16 startSource, ViPUInt16 startEventForm, ViPReal64 startDelay);

//��������� ���������� ������������� �������
//1. ��������� ��������������� �������� HB1, HB2, HB3
ViStatus _VI_FUNC unmgqs_config_filters (ViSession mvi, ViUInt16 HB1, ViUInt16 HB2, ViUInt16 HB3);
//������ ���������� ������������� �������
//1. ������ ���������� ��������������� �������� HB1, HB2, HB3
ViStatus _VI_FUNC unmgqs_config_filters_q (ViSession mvi, ViPUInt16 HB1, ViPUInt16 HB2, ViPUInt16 HB3);

//2. ��������� ���������� ��������� NCO (��� ������ ����)
ViStatus _VI_FUNC unmgqs_config_NCO (ViSession mvi, ViBoolean modulNCO, ViBoolean attenuateNCO, ViReal64 freqNCO);
//2. ������ ���������� ��������� NCO (��� ������ ����)
ViStatus _VI_FUNC unmgqs_config_NCO_q (ViSession mvi, ViPBoolean modulNCO, ViPBoolean attenuateNCO, ViPReal64 freqNCO);

//3. ������������ ������������� �������
ViStatus _VI_FUNC unmgqs_config_QS (ViSession mvi, ViBoolean premodul, ViBoolean filterSinX, ViUInt16 sideBand, ViBoolean doubleIData);
//3. ������ ���������� ������������� �������
ViStatus _VI_FUNC unmgqs_config_QS_q (ViSession mvi, ViPBoolean premodul, ViPBoolean filterSinX, ViPUInt16 sideBand, ViPBoolean doubleIData);


//-------------------------������������ ����------------------------------

//��������� ���������� ������ ����
ViStatus _VI_FUNC unmgqs_config_awg (ViSession mvi, ViUInt16 awgMode, ViUInt16 awgStartMode, ViUInt16 numCycles, ViUInt16 numPacks, ViUInt32 numSamples);
//������ ���������� ������ ����
ViStatus _VI_FUNC unmgqs_config_awg_q (ViSession mvi, ViPUInt16 awgMode, ViPUInt16 awgStartMode, ViPUInt16 numCycles, ViPUInt16 numPacks, ViPUInt32 numSamples);

//�������� ������ ���������� � ���
ViStatus _VI_FUNC unmgqs_writeAWG (ViSession mvi, ViUInt32 adr, ViUInt32 n, ViReal64 data[]);
//�������� ������ ����� � ���
ViStatus _VI_FUNC unmgqs_writeCodeAWG (ViSession mvi, ViUInt32 adr, ViUInt32 n, ViUInt16 data[]);
//�������� ������ ���������� �� ���
ViStatus _VI_FUNC unmgqs_readAWG (ViSession mvi, ViUInt32 adr, ViUInt32 n, ViReal64 data[]);
//�������� ������ ����� �� ���
ViStatus _VI_FUNC unmgqs_readCodeAWG (ViSession mvi, ViUInt32 adr, ViUInt32 n, ViUInt16 data[]);

//�������� ������ ������
ViStatus _VI_FUNC unmgqs_awg_writePacket (ViSession mvi, ViUInt16 chan, ViUInt16 packetNumber, ViUInt16 packetsToWrite, ViPReal64 chan1Data, ViPReal64 chan2Data, ViUInt32 arraySize);

//�������� ������ ������ � ���� �����
ViStatus _VI_FUNC unmgqs_awg_writePacket_codes (ViSession mvi, ViUInt16 chan, ViUInt16 packetNumber, ViUInt16 packetsToWrite, ViPUInt16 chan1Data, ViPUInt16 chan2Data, ViUInt32 arraySize);

//�������� ������ ������
ViStatus _VI_FUNC unmgqs_awg_readPacket (ViSession mvi, ViUInt16 chan, ViUInt16 packetNumber, ViUInt16 packetsToRead, ViPReal64 chan1Data, ViPReal64 chan2Data, ViUInt32 arraySize);

//�������� ������ ������ � ���� �����
ViStatus _VI_FUNC unmgqs_awg_readPacket_codes (ViSession mvi, ViUInt16 chan, ViUInt16 packetNumber, ViUInt16 packetsToRead, ViPUInt16 chan1Data, ViPUInt16 chan2Data, ViUInt32 arraySize);


//-------------------------������������ ��--------------------------------
//��������� ���������� �������������� �������
ViStatus _VI_FUNC unmgqs_config_afg (ViSession mvi, ViUInt16 chan, ViReal64 ampl, ViReal64 freq, ViReal64 phase);
//������ ���������� �������������� �������
ViStatus _VI_FUNC unmgqs_config_afg_q (ViSession mvi, ViUInt16 chan, ViPReal64 ampl, ViPReal64 freq, ViPReal64 phase);

//������� ������ ��������� �������
ViStatus _VI_FUNC unmgqs_config_afg_gen (ViSession mvi, ViUInt16 chan, ViUInt16 genMode);
//������ ������ ��������� �������
ViStatus _VI_FUNC unmgqs_config_afg_gen_q (ViSession mvi, ViUInt16 chan, ViPUInt16 genMode);

//��������� ���������� ���������
ViStatus _VI_FUNC unmgqs_config_afg_modul (ViSession mvi, ViUInt16 chan, ViUInt16 modulType, ViReal64 modulFreq, ViReal64 modulIndex, ViReal64 freqDev, ViReal64 phaseDev);
//������ ���������� ���������
ViStatus _VI_FUNC unmgqs_config_afg_modul_q (ViSession mvi, ViUInt16 chan, ViPUInt16 modulType, ViPReal64 modulFreq, ViPReal64 modulIndex, ViPReal64 freqDev, ViPReal64 phaseDev);

//��������� ����������� ������ �������
ViStatus _VI_FUNC unmgqs_config_afg_signal (ViSession mvi, ViUInt16 chan, ViBoolean useLimits, ViReal64 ampl_h, ViReal64 ampl_l, ViReal64 shift);
//������ ����������� ������ �������
ViStatus _VI_FUNC unmgqs_config_afg_signal_q (ViSession mvi, ViUInt16 chan, ViPBoolean useLimits, ViPReal64 ampl_h, ViPReal64 ampl_l, ViPReal64 shift);

//��������� ���������� ������ ��������������� �� ������
ViStatus _VI_FUNC unmgqs_afg_setData (ViSession mvi, ViUInt16 chan, ViPReal64 data, ViUInt16 Ns, ViReal64 Ts);
//������ ���������� ������ ��������������� �� ������
ViStatus _VI_FUNC unmgqs_afg_getData (ViSession mvi, ViUInt16 chan, ViPReal64 data, ViPUInt16 Ns, ViPReal64 Ts);


#define UNMGQS_EVENT_RESET		1

//typedef  ViInt32(_VI_FUNCH * UNMGQS_HANDLER)(ViSession mvi, ViAddr *user_data, ViUInt32 reason); 

//ViStatus _VI_FUNC unmgqs_handler (ViSession mvi,  UNMGQS_HANDLER pfunc, ViAddr user_data);
/*----------------------------------------------------------------------*/
/*  ��������� �������                                                   */
/*----------------------------------------------------------------------*/
//������ �����������
ViStatus _VI_FUNC unmgqs_get_temperature (ViSession mvi, ViPReal64 tCont, ViPReal64 tCard);

//������� ������������ ����
ViStatus _VI_FUNC unmgqs_config_plis (ViSession mvi);

//����� ��� � ��������� �������� ����������
ViStatus _VI_FUNC unmgqs_ask_adc (ViSession mvi, ViUInt16 chan, ViPReal64 U);

//����� ��� � ��������� ����
ViStatus _VI_FUNC unmgqs_ask_adc_code (ViSession mvi, ViUInt16 chan, ViPInt32 COD_ADC);

//���������� ����
ViStatus _VI_FUNC unmgqs_calibrate (ViSession mvi, ViSession viHP3458, ViUInt16 chan);

//���������� ���������� ����
ViStatus _VI_FUNC unmgqs_stop_calibration (ViSession mvi);

//���������� �������� ����  � ������������ ��������  �������
ViStatus _VI_FUNC unmgqs_calibrate_null_ampl (ViSession mvi, ViSession viHP3458, ViUInt16 chan, ViUInt16 range);

//���������� �������� ��������� ���������� ��������
ViStatus _VI_FUNC unmgqs_calibrate_N_K_offset (ViSession mvi, ViSession viHP3458, ViUInt16 chan);

//���������� ���
ViStatus _VI_FUNC unmgqs_calibrate_ADC (ViSession mvi, ViChar message[]);

//�������� ������������� ������������� �� ������
ViStatus _VI_FUNC unmgqs_load_CalibrationData_FromFlash (ViSession mvi);
//������ ������������� ������������� �� ������
ViStatus _VI_FUNC unmgqs_save_CalibrationData_ToFlash (ViSession mvi);

//������� ��� ��������� �������� ������������� �������������
ViStatus _VI_FUNC unmgqs_get_AUX_DAC (ViSession mvi, ViUInt16 chan, ViUInt16 range, ViPUInt16 AUX_DAC);
ViStatus _VI_FUNC unmgqs_get_DACgain (ViSession mvi, ViUInt16 chan, ViUInt16 range, ViPUInt16 DACgain);
ViStatus _VI_FUNC unmgqs_get_N_OFFSET (ViSession mvi, ViUInt16 chan, ViPInt16 N_OFFSET);
ViStatus _VI_FUNC unmgqs_get_K_OFFSET (ViSession mvi, ViUInt16 chan, ViPReal64 K_OFFSET);
ViStatus _VI_FUNC unmgqs_get_N_ADC (ViSession mvi, ViUInt16 chan, ViPReal64 N_ADC);
ViStatus _VI_FUNC unmgqs_get_K_ADC (ViSession mvi, ViUInt16 chan, ViPReal64 K_ADC);
//�������� ������� ������������� ������������
ViStatus _VI_FUNC unmgqs_get_calibration_data (ViSession mvi, UNMGQS_DRAM *dram);
//�������� ���� ��������� ����������
ViStatus _VI_FUNC unmgqs_get_calibration_date (ViSession mvi, ViChar date[]);

/****************************************************************************          
		������� �������� ������������
*****************************************************************************/ 
ViStatus _VI_FUNC unmgqs_readyPLD (ViSession vi);	  //++
ViStatus _VI_FUNC unmgqs_loadPLD (ViSession vi);	 //__   ������
ViStatus _VI_FUNC unmgqs_prgPLD (ViSession vi);		//__	������
ViStatus _VI_FUNC unmgqs_vrfPLD (ViSession vi);	   //__	������  
ViStatus _VI_FUNC unmgqs_cmpVersions (ViSession vi);  //++
ViStatus _VI_FUNC unmgqs_readFlashVersion (ViSession vi, ViChar flash_rev[]);  //++
ViStatus _VI_FUNC unmgqs_readDataPLD (ViSession vi, void *data, ViUInt32 size);  //++
ViStatus _VI_FUNC unmgqs_writeDataPLD (ViSession vi, void *data, ViUInt32 size); //++ 


#if defined(__cplusplus) || defined(__cplusplus__)

}

#endif

#endif /* __UNMGQS_HEADER */
