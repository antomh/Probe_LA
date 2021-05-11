/************************************/
/* Copyright (C) 1997				*/
/* Informtest ltd.					*/
/* 									*/
/* All rights reserved.				*/
/************************************/

#ifndef __UNOLS_HEADER
#define __UNOLS_HEADER

#include "vpptype.h"

#if defined(__cplusplus) || defined(__cplusplus__)
extern "C" {
#endif
#ifndef UN_MANUFACTURER_ID
#define UN_MANUFACTURER_ID			((ViUInt16) 0x0E76)
#endif
#define UNOLS_MODEL_CODE			((ViUInt16) 0x0168)  	//((ViUInt16) 0x010F)

#define UNOLS_ERROR_OFFSET    		(_VI_ERROR + 0x3FFC0800L)
#define UNOLS_WARN_OFFSET     		(0x3FFC0800L)

//Коды ошибок и предупреждений
#define UNOLS_ERROR_VI		  		(UNOLS_ERROR_OFFSET + 0x0L)  // Ошибка номера сеанса связи  
#define UNOLS_ERROR_READY	  		(UNOLS_ERROR_OFFSET + 0x1L)  // Ошибка контроллеров  
#define UNOLS_ERROR_RPZU 			(UNOLS_ERROR_OFFSET + 0x2L)  // Ошибка РПЗУ  
#define UNOLS_ERROR_SELFTEST   	 	(UNOLS_ERROR_OFFSET + 0x3L) 
#define UNOLS_ERROR_TEST1 	  	 	(UNOLS_ERROR_OFFSET + 0x4L) 
#define UNOLS_ERROR_TEST2			(UNOLS_ERROR_OFFSET + 0x5L)   
			
#define UNOLS_ERROR_CNFG_KF		    (UNOLS_ERROR_OFFSET + 0x10L)    //0x6L)    
#define UNOLS_ERROR_CNFG_KR		    (UNOLS_ERROR_OFFSET + 0x11L)    //0x7L)   
//#define UNOLS_ERROR_BUSY 	  	 	(UNOLS_ERROR_OFFSET + 0x5L)
#define UNOLS_ERROR_BUSY_KF		    (UNOLS_ERROR_OFFSET + 0x12L)    //0x8L) 
#define UNOLS_ERROR_BUSY_KR		    (UNOLS_ERROR_OFFSET + 0x13L)    //0x9L) 	

	// Короткое замыкание	
#define UNOLS_ERROR_U               (UNOLS_ERROR_OFFSET + 0x14L)	//0x10L)  
#define UNOLS_ERROR_START_IMM_KR	(UNOLS_ERROR_OFFSET + 0x15L)    //0x11L)
#define UNOLS_ERROR_START_IMM_KF	(UNOLS_ERROR_OFFSET + 0x16L)    //0x12L)     	

#define UNOLS_ERROR_START_KR		(UNOLS_ERROR_OFFSET + 0x17L)    //0x13L)
#define UNOLS_ERROR_START_KF		(UNOLS_ERROR_OFFSET + 0x18L)    //0x14L)
#define UNOLS_ERROR_START_IMM1_KR	(UNOLS_ERROR_OFFSET + 0x19L)    //0x15L) 
#define UNOLS_ERROR_START_IMM1_KF	(UNOLS_ERROR_OFFSET + 0x20L)    //0x16L)
#define UNOLS_ERROR_CALLOC_KR	    (UNOLS_ERROR_OFFSET + 0x21L)    //0x17L)    	
#define UNOLS_ERROR_CALLOC_KF	    (UNOLS_ERROR_OFFSET + 0x22L)    //0x18L) 	
#define UNOLS_ERROR_MAX_PAR4        (UNOLS_ERROR_OFFSET + 0x23L)  	//0x19L)
#define UNOLS_ERROR_ARRAY_PAR4      (UNOLS_ERROR_OFFSET + 0x24L)	//0x20L)
#define UNOLS_ERROR_PTR_DATA        (UNOLS_ERROR_OFFSET + 0x25L)	//0x20L)    	

#define UNOLS_WARN_NO_READY		  	(UNOLS_WARN_OFFSET  + 0x1L) 
//#define UNOLS_WARN_NO_RPZU		  	(UNOLS_WARN_OFFSET  + 0x2L) 
#define UNOLS_WARN_NO_VRS		  	(UNOLS_WARN_OFFSET  + 0x3L) 
#define UNOLS_WARN_PACKET_ONE_KR	(UNOLS_WARN_OFFSET  + 0x4L) 
#define UNOLS_WARN_PACKET_ONE_KF	(UNOLS_WARN_OFFSET  + 0x5L) 
#define UNOLS_WARN_DDR_KF			(UNOLS_WARN_OFFSET  + 0x6L) 
#define UNOLS_WARN_DDR_KR			(UNOLS_WARN_OFFSET  + 0x7L)  

//Маски состояния инструмента, возвращаемые ф-ей запроса стуса инструмента
#define UNOLS_STOP	  		  0x1      /* ОСТАНОВ (после сброса или останова);*/
#define UNOLS_WAIT    		  0x2      /* ОЖИДАНИЕ (ожидание события запуска) */ 
#define UNOLS_WORK   		  0x4      /* РАБОТА (было событие запуска, идет регистрация /формирование)*/  	
//#define UNOLS_RPZU    	  0x8      /* 0-нет данных РПЗУ/1-есть данные РПЗУ*/ 
	
#define UNOLS_VRS     		  0x100    /* 0-версии ПЛМ и драйвера не совместимы/1-версии совместимы */ 
#define UNOLS_READY			  0x200	   // 0-не готов/1-готов 
#define UNOLS_MASK_DRAM_KR    0x10     /* 1 -  неисправно динамическое ОЗУ КР */ 
#define UNOLS_MASK_DRAM_KF    0x20     /* 1 -  неисправно динамическое ОЗУ КФ  */ 
//  (D0|D1) - исправность питания
	
// Текущеее состояние инструмента, ф-я   Запрос стуса инструмента
#define UNOLS_SERIES_PACK     0х1      /*  Завершение очередного цикла пакетов  */
#define UNOLS_ALL_PACK        0х2      /*  Завершение всех циклов всех пакетов  */ 
	
#define UNOLS_ERR_DRAM_KR     0x100     /* 1 -  неисправно динамическое ОЗУ КР */ 
#define UNOLS_ERR_DRAM_KF     0x200     /* 1 -  неисправно динамическое ОЗУ КФ  */ 

#define   UNOLS_MODE_ASYNCH		0
#define   UNOLS_MODE_SYNCH		1
	
#define   UNOLS_DEVICE_REG		1
#define   UNOLS_DEVICE_GEN  	2
#define   UNOLS_DEVICE_ALL	  	3
	
#define   UNOLS_EXT_GEN   1
#define   UNOLS_INT_GEN   0

#define   UNOLS_DI_1	 0
#define   UNOLS_DI_2	 1
#define   UNOLS_DI_AUTO  2 

#define   UNOLS_T1_MIN   29.e-9  //30.e-9  
#define   UNOLS_T1_MAX   327.68e-6   
#define   UNOLS_T1_STEP  5.e-9   

#define   UNOLS_T2_MIN  7.68e-6   
#define   UNOLS_T2_MAX   83.886080e-3   
#define   UNOLS_T2_STEP  1.28e-6   
	
#define   UNOLS_SREZ	 0
#define   UNOLS_FRONT	 1     		

//  Параметры запуска на формирование
#define UNOLS_TRIG_SOUR_IMM 	0
#define UNOLS_TRIG_SOUR_EVENT   1
#define UNOLS_TRIG_SOUR_EXT		2
#define UNOLS_TRIG_SOUR_EVENT_1 3

#define UNOLS_REGIME_SINGL  	1
#define UNOLS_REGIME_PACET  	2
#define UNOLS_REGIME_STEP   	3
	
#define UNOLS_PACKS_MIN	 		 1
#define UNOLS_PACKS_MAX	  		 1024

#define UNOLS_GEN_PERIOD_MIN	 1  
#define UNOLS_REG_PERIOD_MIN	 0 
#define UNOLS_PERIOD_MAX	 	 4194304

#define UNOLS_SERIES_MIN	 	 1
#define UNOLS_SERIES_MAX	 	 65536
#define UNOLS_SIZE_PAKET	     0x401	  // размер полей периода, циклов повтореий, НА пакета      
	
//  МАски для разрешения событий	
#define UNOLS_EVENT_REG_PACKET_MASK 	0x01     
#define UNOLS_EVENT_REG_PACKET_ALL_MASK 0x02     
#define UNOLS_EVENT_REG_START_MASK      0x04     
#define UNOLS_EVENT_REG_STOP_MASK       0x08     
#define UNOLS_EVENT_REG_OVER_FIFO       0x10      
#define UNOLS_EVENT_REG_MASK            0x1F 


#define UNOLS_EVENT_GEN_PACKET_MASK 	0x01     
#define UNOLS_EVENT_GEN_PACKET_ALL_MASK 0x02     
#define UNOLS_EVENT_GEN_START_MASK      0x04     
#define UNOLS_EVENT_GEN_STOP_MASK       0x08     
#define UNOLS_EVENT_GEN_MASK            0x0F 


#define UNOLS_EVENT_ERR_MASK_SHORT_1    0x01 
#define UNOLS_EVENT_ERR_MASK_SHORT_2    0x02  
#define UNOLS_EVENT_ERR_MASK            0x03        

	
#define UNOLS_ERR_SHORT_1   	0x1   /*  неисправность канала питания контроллеров 1,8 В */
#define UNOLS_ERR_SHORT_2   	0x2   /*  неисправность канала питания контроллеров 3,3 В */
#define UNOLS_ERR_MASK      	0x3   								  
	
	
typedef void (_VI_FUNCH _VI_PTR unols_userCallback)
			 (ViSession vi, ViUInt16 eventREG, ViUInt16 eventGEN, ViUInt16 errorEvent);
/****************************************************************************
		Функция инициализация сеанса с инструментом
*****************************************************************************/
ViStatus _VI_FUNC unols_init (	ViRsrc 		rsrcName, 
								ViBoolean 	id_query,
								ViBoolean 	reset, 
								ViPSession 	vi);
/****************************************************************************
		Функции конфигурации
*****************************************************************************/
ViStatus _VI_FUNC unols_set_synhro_mode (ViSession vi, ViInt16 mode); 

ViStatus _VI_FUNC unols_synhro_gener (ViSession vi, ViInt16 devise,  ViUInt16 sourse,
                                      ViBoolean front, ViUInt16 diT, ViReal64 T);

ViStatus _VI_FUNC unols_synhro_trigger (ViSession vi, ViInt16 devise, ViUInt16 sourse);

ViStatus _VI_FUNC unols_synhro_stop (ViSession vi, ViInt16 devise, ViUInt16 sourse);

ViStatus _VI_FUNC unols_config_trigger (ViSession vi, ViInt16 devise, 
                                        ViUInt32 _VI_FAR event[],
                                        ViUInt32 _VI_FAR chanEvent[]);

ViStatus _VI_FUNC unols_config_stop (ViSession vi, ViInt16 devise, 
                                     ViUInt32 _VI_FAR event[],
                                     ViUInt32 _VI_FAR chanEvent[]);

ViStatus _VI_FUNC unols_set_mode (ViSession vi, ViInt16 devise, ViInt16 mode, ViBoolean endless, ViBoolean stepMode);

ViStatus _VI_FUNC unols_config_mode (ViSession vi, ViUInt16 devise,  
                                     ViUInt16 packs, ViUInt32 _VI_FAR periodPack[], 
                                     ViUInt32 _VI_FAR seriesPack[]);
ViStatus _VI_FUNC unols_config_preTrig (ViSession vi, ViUInt16 statePreTrig);

ViStatus _VI_FUNC unols_config_channel (ViSession vi, ViInt16 devise,
                                        ViUInt32 _VI_FAR stateChans[],
                                        ViUInt32 _VI_FAR chans[],
										ViUInt16 defState);

ViStatus _VI_FUNC unols_config_Uout (ViSession vi, ViReal64 _VI_FAR U[]); 

ViStatus _VI_FUNC unols_config_inpExt (ViSession vi, ViInt16 sourse,  ViInt16 st);  

ViStatus _VI_FUNC unols_config_handler (ViSession vi,  ViAddr userCallback, ViUInt16 regEvent,
                                        ViUInt16 genEvent, ViUInt16 errorEvent);

ViStatus _VI_FUNC unols_set_synhro_mode_Q (ViSession vi, ViPInt16 mode);

ViStatus _VI_FUNC unols_synhro_gener_Q (ViSession vi, ViInt16 devise, ViPUInt16 sourse,
                                        ViPBoolean front, ViPUInt16 diT, ViPReal64 T);


ViStatus _VI_FUNC unols_synhro_trigger_Q (ViSession vi, ViInt16 devise, ViPUInt16 sourse);

ViStatus _VI_FUNC unols_synhro_stop_Q (ViSession vi, ViInt16 devise, ViPUInt16 sourse);

ViStatus _VI_FUNC unols_config_trigger_Q (ViSession vi, ViInt16 devise,
                                       	  ViUInt32 _VI_FAR event[],
                                          ViUInt32 _VI_FAR chanEvent[]);

ViStatus _VI_FUNC unols_config_stop_Q (ViSession vi, ViInt16 devise,
                                       	  ViUInt32 _VI_FAR event[],
                                          ViUInt32 _VI_FAR chanEvent[]);

ViStatus _VI_FUNC unols_set_mode_Q (ViSession vi, ViInt16 devise, ViPInt16 mode, ViPBoolean endless, ViPBoolean stepMode);

ViStatus _VI_FUNC unols_config_handler_Q (ViSession vi,  ViPAddr userCallback, ViPUInt16 regEvent,
                                        ViPUInt16 genEvent, ViPUInt16 errorEvent);
ViStatus _VI_FUNC unols_config_channel_Q (ViSession vi, ViInt16 devise,
                                        ViUInt32 _VI_FAR stateChans[],
										ViPUInt16 defState);
ViStatus _VI_FUNC unols_config_Uout_Q (ViSession vi, ViReal64 _VI_FAR U[]);
ViStatus _VI_FUNC unols_config_mode_Q (ViSession vi, ViUInt16 devise, ViPUInt16 packs,
                                       ViUInt32 _VI_FAR periodPacks[], 
									   ViUInt32 _VI_FAR seriesPacks[]);
ViStatus _VI_FUNC unols_config_preTrig_Q (ViSession vi, ViPUInt16 statePreTrig);   
ViStatus _VI_FUNC unols_config_inpExt_Q (ViSession vi,  ViPInt16 st);     


/****************************************************************************
		Функции управления/состояния
*****************************************************************************/
ViStatus _VI_FUNC unols_trigger (ViSession vi, ViInt16 devise);  
ViStatus _VI_FUNC unols_trigger_imm (ViSession vi, ViInt16 devise);     
ViStatus _VI_FUNC unols_stop (ViSession vi, ViInt16 devise);   
ViStatus _VI_FUNC unols_reset_status (ViSession vi, ViInt16 devise, ViUInt16 maskEvent, ViUInt16 errorEvent); 
ViStatus _VI_FUNC unols_reset_DRAM (ViSession vi, ViInt16 devise, ViUInt32 period, ViUInt32 offsetData);
ViStatus _VI_FUNC unols_status_Q (ViSession vi, ViInt16 devise,  
                                  ViPUInt16  stateDev, ViPUInt16 eventDev, ViPUInt16 errDev);
/****************************************************************************
		 Данные
*****************************************************************************/
ViStatus _VI_FUNC unols_countData (ViSession vi, ViInt16 devise, ViPUInt32 count);  

ViStatus _VI_FUNC unols_write_allData (ViSession vi, ViInt16 devise, ViUInt32 period,
                                       ViUInt32 offsetData, void* data);   
ViStatus _VI_FUNC unols_read_allData (ViSession vi, ViInt16 devise, ViUInt32 period,
                                    ViUInt32 offsetData, void* data);	 
ViStatus _VI_FUNC unols_read_dataKF (ViSession vi, ViUInt32 period,    
                                    ViUInt32 offsetData, void* data, void* maska);									
ViStatus _VI_FUNC unols_write_dataKF (ViSession vi, ViUInt32 period,   
                                    ViUInt32 offsetData, void* data, void* maska);
ViStatus _VI_FUNC unols_write_DataOZU (ViSession vi, ViInt16 devise, ViUInt32 period,
                                       ViUInt32 offsetData, void* data);   
ViStatus _VI_FUNC unols_read_DataOZU (ViSession vi, ViInt16 devise, ViUInt32 period,
                                    ViUInt32 offsetData, void* data);	 
/****************************************************************************
		Сервисные функции 
*****************************************************************************/
ViStatus _VI_FUNC unols_reset (ViSession vi);
ViStatus _VI_FUNC unols_self_test (ViSession 	vi, 
									ViPInt16 	test_result, 
									ViChar 		_VI_FAR test_message[]);
ViStatus _VI_FUNC unols_testOK_off_1 (ViSession 	vi, 
									ViPInt16 	test_result, 
									ViChar 		_VI_FAR test_message[]);
ViStatus _VI_FUNC unols_testOK_off_2 (ViSession 	vi, 
									ViPInt16 	test_result, 
									ViChar 		_VI_FAR test_message[]);
ViStatus _VI_FUNC unols_error_query(ViSession vi, 
									 ViPInt32 error, 
									 ViChar _VI_FAR error_message[]);
ViStatus _VI_FUNC unols_error_message (ViSession vi, 
										ViStatus error, 
										ViChar _VI_FAR message[]);
ViStatus _VI_FUNC unols_revision_query (ViSession vi,
										ViChar _VI_FAR driver_revision[],
										ViChar _VI_FAR instrument_revision[]);
/****************************************************************************
		Функция закрытия сеанса с инструментом
*****************************************************************************/
ViStatus _VI_FUNC unols_close (ViSession vi);

/****************************************************************************          
		Функции загрузки контроллеров
*****************************************************************************/ 
ViStatus _VI_FUNC unols_readyPLD (ViSession vi);
ViStatus _VI_FUNC unols_loadPLD (ViSession vi);
ViStatus _VI_FUNC unols_prgPLD (ViSession vi);
ViStatus _VI_FUNC unols_vrfPLD (ViSession vi);
ViStatus _VI_FUNC unols_cmpVersions (ViSession vi);
ViStatus _VI_FUNC unols_readFlashVersion (ViSession vi, ViChar _VI_FAR flash_rev[]);

/****************************************************************************

	Технологические функции 

*****************************************************************************/   
ViStatus _VI_FUNC unols_synhro_gener_ext (ViSession vi, ViInt16 state, ViUInt16 diT, ViReal64 T);      
ViStatus _VI_FUNC unols_synhro_gener_ext_Q (ViSession vi, ViPInt16 state,ViPUInt16 diT, ViPReal64 T);
ViStatus _VI_FUNC unols_trigger_ext (ViSession vi);   




#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif

#endif /* __UNOLS_HEADER */
