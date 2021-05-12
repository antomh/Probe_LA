//---------------------------------------------------------------------------

#pragma hdrstop

#include "UMgqs.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
extern Log			console;
//==============================================================================
Mgqs::Mgqs(){

	_crate_number	= 0;
	_dev_number		= 1;
	_mez_number		= 1;
	_H				= NULL;

	_connect		= NULL;
	_disconnect		= NULL;
	_is_connect		= NULL;

	_enable			= NULL;
	_disable		= NULL;

	_set_amplitude	= NULL;
	_set_offset		= NULL;

};

//----------------------------------
Mgqs::~Mgqs(){


};

//----------------------------------
bool	__fastcall Mgqs::open_dll(String dllname){

	_H = LoadLibrary(dllname.c_str());
	int t = GetLastError();
	if(!_H){
		console<<"Указанный файл не является динамической библиотекой!"<<endl;
		return false;
	}

	_connect		= (MGQS_CONNECT*)GetProcAddress(_H,"_Connect");
	_disconnect		= (MGQS_DISCONNECT*)GetProcAddress(_H,"_Disconnect");
	_is_connect		= (MGQS_IS_CONNECT*)GetProcAddress(_H,"_isConnect");;

	_enable			= (MGQS_ENABLE*)GetProcAddress(_H,"_Enable");
	_disable		= (MGQS_DISABLE*)GetProcAddress(_H,"_Disable");

	_set_amplitude	= (MGQS_SET_AMPLITUDE*)GetProcAddress(_H,"_Amplitude");
	_set_offset		= (MGQS_SET_OFFSET*)GetProcAddress(_H,"_Offset");

};

//----------------------------------
void	__fastcall Mgqs::close_dll(){

	if(_H)	FreeLibrary(_H);
};

//----------------------------------
bool	__fastcall Mgqs::connect(int crate_number, int dev_number, int mez_number){

	if(!_H || !_is_connect || !_connect)	return false;

	return _connect(crate_number, dev_number, mez_number);
};

//----------------------------------
bool	__fastcall Mgqs::disconnect(){

	if(!_H || !_is_connect || !_disconnect)	return false;

	_disconnect();
	return true;
};

//----------------------------------
bool	__fastcall Mgqs::is_connected(){

	if(!_H || !_is_connect)	return false;

	return _is_connect();
};

//----------------------------------
bool	__fastcall Mgqs::enable(u8 channel){

	if(!_H || !_is_connect || !_enable)	return false;

	_enable(channel);
	return true;
};

//----------------------------------
bool	__fastcall Mgqs::disable(u8 channel){

	if(!_H || !_is_connect || !_disable)	return false;

	_disable(channel);
	return true;
};

//----------------------------------
bool	__fastcall Mgqs::set_amplitude(u8 channel, double value){

	if(!_H || !_is_connect || !_set_amplitude)	return false;

	_set_amplitude(channel, value);
	return true;
};

//----------------------------------
bool	__fastcall Mgqs::set_offset(u8 channel, double value){

	if(!_H || !_is_connect || !_set_offset)	return false;

	_set_offset(channel, value);
	return true;
};

//----------------------------------
