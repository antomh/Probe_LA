//---------------------------------------------------------------------------

#ifndef UMgqsH
#define UMgqsH
//---------------------------------------------------------------------------

#include "Definition.h"
#include "Templates.h"
#include "ULog.h"
#include "UData.h"
#include "USignals.h"

typedef  bool 	(MGQS_CONNECT)(int, int, int);
typedef  void	(MGQS_DISCONNECT)();
typedef  bool	(MGQS_IS_CONNECT)();

typedef  void	(MGQS_ENABLE)(int);
typedef  void	(MGQS_DISABLE)(int);

typedef bool 	(MGQS_SET_AMPLITUDE)(int, double );
typedef bool 	(MGQS_SET_OFFSET)(int, double );

//---------------------------------------------------------------------------
class Mgqs{

public:
	Mgqs();
	~Mgqs();

	bool	__fastcall open_dll(String dllname);
	void	__fastcall close_dll();

	bool	__fastcall connect(int crate_number, int dev_number, int mez_number);
	bool	__fastcall disconnect();

	bool	__fastcall is_connected();

	bool	__fastcall enable(u8 channel);
	bool	__fastcall disable(u8 channel);

	bool	__fastcall set_amplitude(u8 channel, double value);
	bool	__fastcall set_offset(u8 channel, double value);


private:

	i32				_crate_number;
	i32				_dev_number;
	i32             _mez_number;

	HINSTANCE 		_H;

	MGQS_CONNECT*		_connect;
	MGQS_DISCONNECT*	_disconnect;
	MGQS_IS_CONNECT*	_is_connect;

	MGQS_ENABLE*		_enable;
	MGQS_DISABLE*		_disable;

	MGQS_SET_AMPLITUDE*	_set_amplitude;
	MGQS_SET_OFFSET* 	_set_offset;


};
#endif
