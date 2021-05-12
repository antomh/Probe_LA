#ifndef _UNMBASE_HEADER
#define _UNMBASE_HEADER

#include <visa.h>
#include <vpptype.h>

#if defined(__cplusplus) || defined(__cplusplus__)
extern "C" {
#endif

#ifndef _UNMBASE_API	//внутри unmbase.c определено как __declspec(dllexport), иначе импортируем
#define _UNMBASE_API	
#endif
	
#ifndef UN_MANUFACTURER_ID
#define UN_MANUFACTURER_ID              ((ViUInt16) 0x0E76)
#endif

#ifndef UN_USB_VENDOR_ID
#define UN_USB_VENDOR_ID                ((ViUInt16) 0x19BB)
#endif

#define UNMBASE_MODEL_CODE              ((ViUInt16) 0x010D)
#define UNMBASEU_MODEL_CODE             ((ViUInt16) 0x0155)
#define UNMBASE_MODEL_ARMVXI            ((ViUInt16) 0x0177)
	
#define UNMBASE_USB_MODEL_CODE          ((ViUInt16) 0x1004)

#define UNMBASE_MEZABOX_IDN          "INFORMTEST,UNMBASE"

#define UNMBASE_TYPE_U	0	//упрощенный
#define UNMBASE_TYPE_1	1	//верси€ 1
#define UNMBASE_TYPE_2	2	//верси€ 2
#define UNMBASE_TYPE_2A	3	//верси€ 2A
#define UNMBASE_TYPE_MB		0x10	//верси€ 2, Message Based
#define UNMBASE_TYPE_ARM	0x20	//верси€ 2, VXI на базе 2хј–ћ

#define UNMBASE_IOMODE_IN           0
#define UNMBASE_IOMODE_OUT          1
#define UNMBASE_IOMODE_BOTH         2

#define UNMBASE_MODE_SINGLE         0
#define UNMBASE_MODE_BLOCK          1
#define UNMBASE_MODE_LOOP           2

/******************************************/
/*         Mezzanine attributes           */
/******************************************/
#define UNMBASE_MATTR_BASE_VI       0x3FFF0801UL    //(RO)
#define UNMBASE_MATTR_NUM           0x3FFF0802UL    //(RO)  
#define UNMBASE_MATTR_TYPE          0x3FFF0803UL    //(RO)  
#define UNMBASE_MATTR_MEMBASE_IN    0x3FFF0804UL    //(RO)  
#define UNMBASE_MATTR_MEMSIZE_IN    0x3FFF0805UL    //(RO)
#define UNMBASE_MATTR_MEMBASE_OUT   0x3FFF0806UL    //(RO)  
#define UNMBASE_MATTR_MEMSIZE_OUT   0x3FFF0807UL    //(RO)
#define UNMBASE_MATTR_USER_DATA     0x3FFF0808UL    //(R/W)
#define UNMBASE_MATTR_DEV_TYPE     	0x3FFF0809UL    //(R/W)
#define UNMBASE_MATTR_BASE_TYPE    	0x3FFF080AUL    //(R/W)
#define UNMBASE_MATTR_ASYNC     	0x3FFF080BUL    //(R/W)
#define UNMBASE_MATTR_MEZ_EXTVI     0x3FFF080CUL    //(R/W)
#define UNMBASE_MATTR_MEZ_INTVI     0x3FFF080DUL    //(RO)

#define UNMBASE_MATTR_LOCK_LASTDATA 0x3FFF080EUL    //(R/W)

#define UNMBASE_MATTR_CHECK_OUT_ERR 0x3FFF080FUL    //(R/W)

#define UNMBASE_MATTR_BASE_ID_MSG   0x3FFF0880UL    //(RO)

/******************************************/
/*  Error and Complete codes definitions  */
/******************************************/
#define UNMBASE_ERROR_OFFSET            (_VI_ERROR + 0x3FFC0800L)
#define UNMBASE_WARN_OFFSET             (0x3FFC0800L)

#define UNMBASE_ERROR_SELFTEST          (UNMBASE_ERROR_OFFSET + 0x0BL)
#define UNMBASE_ERROR_FLEX              (UNMBASE_ERROR_OFFSET + 0x0CL) 
#define UNMBASE_ERROR_INSTR             (UNMBASE_ERROR_OFFSET + 0x0DL) 
#define UNMBASE_ERROR_SPD               (UNMBASE_ERROR_OFFSET + 0x0EL) 
#define UNMBASE_ERROR_BUSY              (UNMBASE_ERROR_OFFSET + 0x0FL) 
#define UNMBASE_ERROR_M_NUMBER          (UNMBASE_ERROR_OFFSET + 0x10L) 
#define UNMBASE_ERROR_NO_MEMORY         (UNMBASE_ERROR_OFFSET + 0x11L) 
#define UNMBASE_ERROR_NODATA            (UNMBASE_ERROR_OFFSET + 0x12L) 
#define UNMBASE_ERROR_READ              (UNMBASE_ERROR_OFFSET + 0x13L) 
#define UNMBASE_ERROR_WRITE             (UNMBASE_ERROR_OFFSET + 0x14L) 
#define UNMBASE_ERROR_MEZ_IO            (UNMBASE_ERROR_OFFSET + 0x15L) 
#define UNMBASE_ERROR_TOO_FAST          (UNMBASE_ERROR_OFFSET + 0x16L)
#define UNMBASE_ERROR_NO_CLOCKS         (UNMBASE_ERROR_OFFSET + 0x17L)
#define UNMBASE_ERROR_NO_FIRST_DELAY    (UNMBASE_ERROR_OFFSET + 0x18L)
#define UNMBASE_ERROR_NO_SAMPLE_LENGTH  (UNMBASE_ERROR_OFFSET + 0x19L)
#define UNMBASE_ERROR_NO_PACKET_SIZE    (UNMBASE_ERROR_OFFSET + 0x1AL)
#define UNMBASE_ERROR_NO_BLOCK_SIZE     (UNMBASE_ERROR_OFFSET + 0x1BL)
#define UNMBASE_ERROR_NO_ALLOC          (UNMBASE_ERROR_OFFSET + 0x1CL)
#define UNMBASE_ERROR_NULL_POINTER      (UNMBASE_ERROR_OFFSET + 0x1DL)
#define UNMBASE_ERROR_MEZ_IO2           (UNMBASE_ERROR_OFFSET + 0x1EL) 
#define UNMBASE_ERROR_NOT_SUPPORT       (UNMBASE_ERROR_OFFSET + 0x1FL) 
#define UNMBASE_ERROR_MEZ_IO12          (UNMBASE_ERROR_OFFSET + 0x20L) 

#define UNMBASE_WARN_INIT               (UNMBASE_WARN_OFFSET + 0x11L) 
#define UNMBASE_WARN_REREADED           (UNMBASE_WARN_OFFSET + 0x12L) 

typedef ViBoolean (_VI_FUNCH _VI_PTR unmbase_UserHandler)(ViSession mvi, ViInt32 reason);

#define UNMBASE_IRQ_MEZ_IRQ             0
#define UNMBASE_IRQ_TRANS_BLOCK         1
#define UNMBASE_IRQ_RECV_BLOCK          2
#define UNMBASE_IRQ_TRANS_PACKET        3
#define UNMBASE_IRQ_RECV_PACKET         4
#define UNMBASE_EVENT_RESET             10
#define UNMBASE_IRQ_ERR_1               -1
#define UNMBASE_IRQ_ERR_2               -2

/******************************************/
/*      Driver functions definitions      */
/******************************************/

_UNMBASE_API ViStatus _VI_FUNC unmbase_init (ViRsrc rsrcName,
							ViBoolean id_query,
							ViBoolean reset,
							ViSession *vi);
/*--------------------------------------------------------------------------*/
/* Init mezzanine session                                                   */
/*  On M-module number Num (if present); open session. Session number is     */
/* index in global array p_mvi + 1, where store session structure pointer   */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_init (ViSession vi,
								ViUInt16 Num,
								ViSession *mvi);
/*--------------------------------------------------------------------------*/
/* Close mezzanine session                                                  */
/*  Free session structure (->m_vi_idx=0); and session number (p_mvi[m_vi_idx] = 0);  */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_close (ViSession mvi);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_get_attribute (ViSession mvi,
								ViAttr Attribute_Name,
								void *Attribute_Value);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_set_attribute (ViSession mvi,
								ViAttr Attribute_Name,
								ViAttrState Attribute_Value);
/*--------------------------------------------------------------------------*/
/* Input D32 word from mezzanine memory                                     */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_in16 (ViSession mvi,
								ViUInt32 Addr,
								ViUInt16 *Data);
/*--------------------------------------------------------------------------*/
/* Output D32 word to mezzanine memory                                      */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_out16 (ViSession mvi,
								ViUInt32 Addr,
								ViUInt16 Data);
/*--------------------------------------------------------------------------*/
/* Input block of D16 words from mezzanine memory                           */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_movein16 (ViSession mvi,
								ViUInt32 Addr,
								ViUInt16 *Buff,
								ViInt32 Count,
								ViBoolean Increment);
/*--------------------------------------------------------------------------*/
/* Output block of D16 words to mezzanine memory                            */
/*--------------------------------------------------------------------------*/
//OK1
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_moveout16 (ViSession mvi,
								ViUInt32 Addr,
								ViUInt16 *Buff,
								ViInt32 Count,
								ViBoolean Increment);
/*--------------------------------------------------------------------------*/
/* Set sample width of mezzanine                                            */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_sample_width (ViSession mvi,
								ViUInt16 io,
								ViUInt32 Width);
/*--------------------------------------------------------------------------*/
/* Query sample width of mezzanine                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_sample_width_q (ViSession mvi,
								ViUInt16 io,
								ViUInt32 *Width);
/*--------------------------------------------------------------------------*/
/* Set delay of first mezzanine sample                                      */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_first_delay (ViSession mvi,
								ViUInt16 io,
								ViUInt32 FirstDelay);
/*--------------------------------------------------------------------------*/
/* Query delay of first mezzanine sample                                    */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_first_delay_q (ViSession mvi,
								ViUInt16 io,
								ViUInt32 *FirstDelay);
/*--------------------------------------------------------------------------*/
/* Allocate memory for mezzanine                                            */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_alloc (ViSession mvi,
								ViUInt16 io,
								ViUInt32 Size,
								ViUInt32 *Addr);
/*--------------------------------------------------------------------------*/
/* Query mezzanine allocated memory                                         */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_alloc_q (ViSession mvi,
								ViUInt16 io,
								ViUInt32 *Size,
								ViUInt32 *Addr);
/*--------------------------------------------------------------------------*/
/* Switch mezzanine mode:single, block or cycle                             */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_mode (ViSession mvi,
								ViUInt16 io,
								ViUInt16 Mode);
/*--------------------------------------------------------------------------*/
/* Query mezzanine mode:single, block or cycle                             */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_mode_q (ViSession mvi,
								ViUInt16 io,
								ViUInt16 *Mode);
/*--------------------------------------------------------------------------*/
/* Switch mezzanine START signal mode: pulse or level                       */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_trig_length (ViSession mvi,
								ViUInt16 Mode);
/*--------------------------------------------------------------------------*/
/* Query mezzanine START signal mode: pulse or level                        */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_trig_length_q (ViSession mvi,
								ViUInt16 *Mode);
/*--------------------------------------------------------------------------*/
/* Setup mezzanine trigger source                                           */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_config_trigger (ViSession mvi,
										ViUInt16 io,
										ViInt16 StartSource);
/*--------------------------------------------------------------------------*/
/* Return mezzanine trigger source                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_config_trigger_q (ViSession mvi,
										ViUInt16 io,
										ViInt16 *StartSource);
/*--------------------------------------------------------------------------*/
/* Set mezzanine sampling frequency                                         */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_clock (ViSession mvi,
								ViUInt16 io,
								ViUInt32 Divisor);
/*--------------------------------------------------------------------------*/
/* Query mezzanine sampling frequency                                       */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_clock_q (ViSession mvi,
								ViUInt16 io,
								ViUInt32 *Divisor);
/*--------------------------------------------------------------------------*/
/* Set mezzanine block size                                                 */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_block_size (ViSession mvi,
								ViUInt16 io,
								ViUInt32 Size);
/*--------------------------------------------------------------------------*/
/* Query mezzanine block size                                               */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_block_size_q (ViSession mvi,
								ViUInt16 io,
								ViUInt32 *Size);
/*--------------------------------------------------------------------------*/
/* Set mezzanine loop size                                                */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_loop_size (ViSession mvi,
								ViUInt16 io,
								ViUInt32 Size);
/*--------------------------------------------------------------------------*/
/* Query mezzanine loop size                                               */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_loop_size_q (ViSession mvi,
								ViUInt16 io,
								ViUInt32 *Size);
								
/*--------------------------------------------------------------------------*/
/* Set mezzanine loop segment config                                        */
/* (do not switch anything)                                                 */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_segment (ViSession mvi,
								ViUInt16 io,
								ViUInt32 Segment,
								ViUInt32 Offset,
								ViUInt32 Size);
/*--------------------------------------------------------------------------*/
/* Query mezzanine loop segment config                                      */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_segment_q (ViSession mvi,
								ViUInt16 io,
								ViUInt32 Segment,
								ViUInt32 *Offset,
								ViUInt32 *Size);
/*--------------------------------------------------------------------------*/
/* Switch mezzanine loop segment                                            */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_segment_switch (ViSession mvi,
								ViUInt16 io,
								ViUInt32 Segment,
								ViBoolean mode);
/*--------------------------------------------------------------------------*/
/* Query current mezzanine loop segment                                     */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_segment_cur_q (ViSession mvi,
								ViUInt16 io,
								ViUInt32 *Segment);
								
/*--------------------------------------------------------------------------*/
/* Set mezzanine packet size                                                */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_packet_size (ViSession mvi,
								ViUInt16 io,
								ViUInt32 Size);
/*--------------------------------------------------------------------------*/
/* Query mezzanine packet size                                              */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_packet_size_q (ViSession mvi,
								ViUInt16 io,
								ViUInt32 *Size);
/*--------------------------------------------------------------------------*/
/* Install user IRQ handler                                                 */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_handler (ViSession mvi,
								ViAddr Handler);
/*--------------------------------------------------------------------------*/
/* Enable/Disable Events                                                    */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_config_event (ViSession mvi,
								ViBoolean enable);
/*--------------------------------------------------------------------------*/
/* Query event enabled                                                      */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_config_event_q (ViSession mvi,
								ViBoolean *enable,
								ViBoolean *m_enable);
/*--------------------------------------------------------------------------*/
/* Read Last Sample                                                         */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_read_last (ViSession mvi,
									ViUInt32 Buff[],
									ViUInt32 *firstTime,
									ViUInt32 *thisTime);
/*--------------------------------------------------------------------------*/
/* Read Data Array                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_read_block (ViSession mvi,
									ViUInt32 Idx,
									ViUInt32 NSamples,
									ViUInt32 Buff[]);
/*--------------------------------------------------------------------------*/
/* Read next ready samples when cycle mode run                              */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_read_packet (ViSession mvi,
										ViUInt32 NSamples,
										ViUInt32 Buff[],
										ViUInt32 *ReadNSamples);
/*--------------------------------------------------------------------------*/
/* Read last samples when cycle mode run                                    */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_read_last_packet (ViSession mvi,
										ViUInt32 NSamples,
										ViUInt32 Buff[],
										ViUInt32 *ReadNSamples);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_write_block (ViSession mvi,
										ViUInt32 Idx,
										ViUInt32 NSamples,
										ViUInt32 Buff[]);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_write_packet (ViSession mvi,
										ViUInt32 NSamples,
										ViUInt32 Buff[],
										ViUInt32 *WriteNSamples);
/*--------------------------------------------------------------------------*/
/* Read Data Array from Segment                                             */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_read_segment (ViSession mvi,
										ViUInt16 io,
										ViUInt32 Segment,
										ViUInt32 Idx,
										ViUInt32 NSamples,
										ViUInt32 Buff[]);
/*--------------------------------------------------------------------------*/
/* Write Data Array to Segment                                              */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_write_segment (ViSession mvi,
										ViUInt16 io,
										ViUInt32 Segment,
										ViUInt32 Idx,
										ViUInt32 NSamples,
										ViUInt32 Buff[]);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_start (ViSession mvi,
								ViUInt16 io);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_stop (ViSession mvi,
								ViUInt16 io);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_async_stop (ViSession mvi,
								ViUInt16 io);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_state (ViSession mvi,
									ViUInt16 io,
									ViInt16 *State);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_reset (ViSession mvi,
									ViUInt16 io);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_type_q (ViSession vi,
									ViInt16 N,
									ViInt16 *Present,
									ViInt16 *Type);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_mem_q (ViSession vi,
								ViUInt32 *MemSize);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_time_q (ViSession vi,
								ViUInt32 *time);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_config_trigger (ViSession vi,
										ViInt16 StartSource,
										ViInt16 Master,
										ViInt16 TTLTRGline);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_config_trigger_q (ViSession vi,
										ViInt16 *StartSource,
										ViInt16 *Master,
										ViInt16 *TTLTRGline);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_config_ticks (ViSession vi,
										ViInt16 time);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_config_ticks_q (ViSession vi,
										ViInt16 *time);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_start (ViSession vi);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_stop (ViSession vi);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_state (ViSession vi,
								ViInt16 *State);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_time_sync (ViSession vi, ViBoolean dosync);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_m_howmuch_data_q (ViSession mvi,
									ViUInt16 io,
									ViUInt32 *howmuch);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_reset (ViSession vi);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_self_test (ViSession vi,
									ViInt16 *TestResult,
									ViChar _VI_FAR TestMessage[]);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_error_query (ViSession vi,
										ViInt32 *Error,
										ViChar _VI_FAR ErrorMessage[]);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_error_message (ViSession vi,
										ViStatus Status,
										ViChar _VI_FAR ErrorMessage[]);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_revision_query (ViSession vi,
										ViChar _VI_FAR HardRevision[],
										ViChar _VI_FAR SoftRevision[]);
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
_UNMBASE_API ViStatus _VI_FUNC unmbase_close (ViSession vi);

/*--------------------------------------------------------------------------*/
/* Utility functions for internal usage                                     */
/*--------------------------------------------------------------------------*/
ViStatus _VI_FUNCC unmbase_data_read(ViSession vi,
						  ViUInt32 A,   //global RAM address
						  ViUInt32 N,   //number of bytes
						  ViPUInt8 Buff);
ViStatus _VI_FUNCC unmbase_data_write(ViSession vi, 
						ViUInt32 A, //global RAM address
						ViUInt32 N, //number of bytes
						ViPUInt8 Buff);
//for old compatibility
ViStatus _VI_FUNCC unmbase_blk_read(ViSession vi,
						  ViUInt32 A,   //global RAM address
						  ViUInt32 N,   //number of bytes
						  ViPUInt8 Buff,
						  ViInt32 mez);	//дл€ отладки - кто блокирует...
ViStatus _VI_FUNCC unmbase_blk_write(ViSession vi, 
						ViUInt32 A, //global RAM address
						ViUInt32 N, //number of bytes
						ViPUInt8 Buff,
						ViInt32 mez);	//дл€ отладки - кто блокирует...

#if defined(__cplusplus) || defined(__cplusplus__)
		}       //extern "C" {
#endif

#endif  //_UNMBASE_HEADER
