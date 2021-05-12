//---------------------------------------------------------------------------

#ifndef UPsuH
#define UPsuH

#include "Definition.h"
#include "Templates.h"
#include "ULog.h"
#include "UData.h"
#include "USignals.h"

typedef  bool 	(CONNECT)(const std::string&, int);
typedef  void	(DISCONNECT)();
typedef  bool	(IS_CONNECT)();

typedef  void	(ENABLE)(int);
typedef  void	(DISABLE)(int);

typedef bool 	(SET_VOLTAGE)(float, int );
typedef bool 	(SET_CURRENT)(float, int );

typedef float 	(GET_VOLTAGE)(int );
typedef float 	(GET_CURRENT)(int );

//---------------------------------------------------------------------------
class Psu{

public:
	Psu();
	~Psu();

	bool	__fastcall open_dll(String dllname);
	void	__fastcall close_dll();

	bool	__fastcall connect(String address, i32 port);
	bool	__fastcall disconnect();

	bool	__fastcall is_connected();

	bool	__fastcall set_voltage(u8 channel, double value);
	bool	__fastcall set_current(u8 channel, double value);

	bool	__fastcall get_current(u8 channel, double& value);
	bool	__fastcall get_voltage(u8 channel, double& value);

	bool	__fastcall enable(u8 channel);
	bool	__fastcall disable(u8 channel);

private:

	String			_address;
	i32				_port;
	HINSTANCE 		_H;

	CONNECT*		_connect;
	DISCONNECT*		_disconnect;
	IS_CONNECT*		_is_connect;

	ENABLE*			_enable;
	DISABLE*		_disable;

	SET_VOLTAGE*	_set_voltage;
	SET_CURRENT* 	_set_current;

	GET_VOLTAGE*	_get_voltage;
	GET_CURRENT*	_get_current;





};



































#endif
