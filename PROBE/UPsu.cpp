//---------------------------------------------------------------------------

#pragma hdrstop

#include "UPsu.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

extern Log			console;
//===========================================================================
Psu::Psu(){

	_address		= "";
	_port			= 5024;
	_H				= NULL;

	_connect		= NULL;
	_disconnect		= NULL;
	_is_connect		= NULL;

	_enable			= NULL;
	_disable		= NULL;

	_set_voltage	= NULL;
	_set_current	= NULL;

	_get_voltage	= NULL;
	_get_current	= NULL;
};

//----------------------------------
Psu::~Psu(){


};

//----------------------------------
bool	__fastcall Psu::open_dll(String dllname){

	_H = LoadLibrary(dllname.c_str());
    int t = GetLastError();
	if(!_H){
		console<<"Указанный файл не является динамической библиотекой!"<<endl;
		return false;
	}

	_connect		= (CONNECT*)GetProcAddress(_H,"_Connect");
	_disconnect		= (DISCONNECT*)GetProcAddress(_H,"_Disconnect");
	_is_connect		= (IS_CONNECT*)GetProcAddress(_H,"_isConnect");;

	_enable			= (ENABLE*)GetProcAddress(_H,"_Enable");
	_disable		= (DISABLE*)GetProcAddress(_H,"_Disable");

	_set_voltage	= (SET_VOLTAGE*)GetProcAddress(_H,"_SetVoltage");
	_set_current	= (SET_CURRENT*)GetProcAddress(_H,"_SetCurrent");

	_get_voltage	= (GET_VOLTAGE*)GetProcAddress(_H,"_GetVoltage");
	_get_current	= (GET_CURRENT*)GetProcAddress(_H,"_GetCurrent");
};

//----------------------------------
void	__fastcall Psu::close_dll(){

	if(_H)	FreeLibrary(_H);
};

//----------------------------------
bool	__fastcall Psu::connect(String address, i32 port){

	if(!_H || !_is_connect || !_connect)	return false;

	return _connect(AnsiString(address).c_str(), port);
};

//----------------------------------
bool	__fastcall Psu::disconnect(){

	if(!_H || !_is_connect || !_disconnect)	return false;

	_disconnect();
	return true;
};

//----------------------------------
bool	__fastcall Psu::is_connected(){

	if(!_H || !_is_connect)	return false;

	return _is_connect();
};

//----------------------------------
bool	__fastcall Psu::set_voltage(u8 channel, double value){

	if(!_H || !_is_connect || !_set_voltage)	return false;

	_set_voltage(value, channel);
	return true;
};

//----------------------------------
bool	__fastcall Psu::set_current(u8 channel, double value){

	if(!_H || !_is_connect || !_set_voltage)	return false;

	_set_current(value, channel);
	return true;
};

//----------------------------------
bool	__fastcall Psu::get_current(u8 channel, double& value){

	if(!_H || !_is_connect || !_get_current)	return false;

	float buf = 0;
	buf = _get_current(channel);
	value = (int(100*buf))/100.0;
	return true;
};

//----------------------------------
bool	__fastcall Psu::get_voltage(u8 channel, double& value){

	if(!_H || !_is_connect || !_get_voltage)	return false;

	float buf = 0;
	buf	= _get_voltage(channel);
	value = (int(100*buf))/100.0;
	return true;
};

//----------------------------------
bool	__fastcall Psu::enable(u8 channel){

	if(!_H || !_is_connect || !_enable)	return false;

	_enable(channel);
	return true;
};

//----------------------------------
bool	__fastcall Psu::disable(u8 channel){

	if(!_H || !_is_connect || !_enable)	return false;

	_disable(channel);
	return true;
};


