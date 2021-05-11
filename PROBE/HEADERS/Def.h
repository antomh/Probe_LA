//---------------------------------------------------------------------------
#ifndef ClassesH
#define ClassesH

//==============================================================================
namespace	OLS{

enum EOLSMode{AUTO,SLAVE};

const int	OLS_CODE=0x0168;

const int OFF=0;
const int ON=1;

const int iREG=0;
const int iGEN=1;

const int REG=1;
const int GEN=2;
const int ALL=3;

const int MODE_SYNC=1;
const int MODE_ASYNC=0;

const int EXT_GEN=1;
const int INT_GEN=0;

const int SREZ=0;
const int FRONT=1;

const int DI_1=0;
const int DI_2=1;
const int DI_AUTO=2;

const double T1_MIN=29.0E-9;
const double T1_MAX=327.68E-6;
const double T1_STEP=5.0E-9;

const double T2_MIN=7.68E-6;
const double T2_MAX=83.88608E-3;
const double T2_STEP=1.28E-6;

const int TRIG_SOUR_IMM=0;
const int TRIG_SOUR_CODE=1;
const int TRIG_SOUR_EXT=2;

const int STOP_SOUR_END=0;
const int STOP_SOUR_CODE=1;

const int PACK_MODE=0;
const int SINGL_MODE=1;

const int REG_EVENT_ONE_PACK=1;
const int REG_EVENT_SET_PACK=2;
const int REG_EVENT_BEGIN=4;
const int REG_EVENT_END=8;
const int REG_EVENT_RAM_FULL=10;

const int GEN_EVENT_ONE_PACK=1;
const int GEN_EVENT_SET_PACK=2;
const int GEN_EVENT_BEGIN=4;
const int GEN_EVENT_END=8;

const int ERR_EVENT_18=1;
const int ERR_EVENT_33=2;

const int STATE_STOP=1;
const int STATE_WAIT=2;
const int STATE_RUN=4;
//---------------------------------------------------------------------------
//const ViUInt32 	maskFF[2]={0xFFFFFFFF,0xFFFFFFFF};
//const ViUInt32 	mask00[2]={0,0};
const double	OLS_Uout[4]={5.0,5.0,5.0,5.0};
//---------------------------------------------------------------------------
const int	in=0;
const int	out=1;

//--------------------------------------
const unsigned long 	maskFF[2]={0xFFFFFFFF,0xFFFFFFFF};
const unsigned long 	mask00[2]={0,0};
const unsigned __int64  FULL=0xFFFFFFFFFFFFFFFF;
const unsigned __int64 NEG=0x0000000000000000;
const unsigned __int64 BIT[64]={0x0000000000000001,
					   0x0000000000000002,
					   0x0000000000000004,
					   0x0000000000000008,
					   0x0000000000000010,
					   0x0000000000000020,
					   0x0000000000000040,
					   0x0000000000000080,
					   0x0000000000000100,
					   0x0000000000000200,
					   0x0000000000000400,
					   0x0000000000000800,
					   0x0000000000001000,
					   0x0000000000002000,
					   0x0000000000004000,
					   0x0000000000008000,
					   0x0000000000010000,
					   0x0000000000020000,
					   0x0000000000040000,
					   0x0000000000080000,
					   0x0000000000100000,
					   0x0000000000200000,
					   0x0000000000400000,
					   0x0000000000800000,
					   0x0000000001000000,
					   0x0000000002000000,
					   0x0000000004000000,
					   0x0000000008000000,
					   0x0000000010000000,
					   0x0000000020000000,
					   0x0000000040000000,
					   0x0000000080000000,
					   0x0000000100000000,
					   0x0000000200000000,
					   0x0000000400000000,
					   0x0000000800000000,
					   0x0000001000000000,
					   0x0000002000000000,
					   0x0000004000000000,
					   0x0000008000000000,
					   0x0000010000000000,
					   0x0000020000000000,
					   0x0000040000000000,
					   0x0000080000000000,
					   0x0000100000000000,
					   0x0000200000000000,
					   0x0000400000000000,
					   0x0000800000000000,
					   0x0001000000000000,
					   0x0002000000000000,
					   0x0004000000000000,
					   0x0008000000000000,
					   0x0010000000000000,
					   0x0020000000000000,
					   0x0040000000000000,
					   0x0080000000000000,
					   0x0100000000000000,
					   0x0200000000000000,
					   0x0400000000000000,
					   0x0800000000000000,
					   0x1000000000000000,
					   0x2000000000000000,
					   0x4000000000000000,
					   0x8000000000000000};

};


#endif
