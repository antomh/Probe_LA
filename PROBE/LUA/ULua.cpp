//---------------------------------------------------------------------------

#pragma hdrstop

#include "ULua.h"
#include "UFProbeTest.h"
extern bool			stop;
extern bool			wait;
extern int			debug;
extern int 			state;

bool	allow 	= true;
bool	allow1	= true;
bool	single	= true;

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------


//==============================================================================
ULua::ULua(){

	FLua = luaL_newstate();
	luaL_openlibs(FLua);

	lua_register(FLua,	"pause",		&Pause);
	lua_register(FLua,	"stop",			&Return);
	lua_register(FLua,	"message",		&Message);
	lua_register(FLua,	"sleep",		&USleep);
	lua_register(FLua,	"console",		&Console);

	lua_register(FLua,	"mode_27",		&relay_off);
	lua_register(FLua,	"mode_12",		&relay_on);
	lua_register(FLua,	"low",			&low);
	lua_register(FLua,	"hi",			&hi);
	lua_register(FLua,	"low_code",	   	&low_code);
	lua_register(FLua,	"hi_code",	   	&hi_code);
	lua_register(FLua,	"set_code",	   	&set_code);
	lua_register(FLua,	"time",			&get_event);

	lua_register(FLua,	"set_voltage",	&set_voltage);
	lua_register(FLua,	"set_current",	&set_current);
	lua_register(FLua,	"get_voltage",	&get_voltage);
	lua_register(FLua,	"get_current",	&get_current);
	lua_register(FLua,	"enable",		&enable);
	lua_register(FLua,	"disable",		&disable);

	lua_register(FLua,	"initialize",  	&create);
	lua_register(FLua,	"close",		&close);
	lua_register(FLua,	"add_12v",		&add_12v);
	lua_register(FLua,	"add_27v",		&add_27v);
	lua_register(FLua,	"to_code_12v",	&to_code_12v);
	lua_register(FLua,	"to_code_27v",	&to_code_27v);
	lua_register(FLua,	"save",			&save);

	lua_register(FLua,	"set_amplitude",&set_amplitude);
	lua_register(FLua,	"set_offset",	&set_offset);
	lua_register(FLua,	"mgqs_enable",	&mgqs_enable);
	lua_register(FLua,	"mgqs_disable",	&mgqs_disable);

	FState 	= 0;

};

//-------------------------------------------
ULua::~ULua(){

	Stop();
	lua_close(FLua);

};

//-------------------------------------------
void		ULua::SetScript(String script){

	FScript	= script;
};

//-------------------------------------------
void		ULua::SetState(int state){

	FState = state;    //???????????
};

//-------------------------------------------
String		ULua::GetScript(){

	return FScript;
};

//-------------------------------------------
int			ULua::GetState(){

	return FState;
};

//-------------------------------------------
void __fastcall ULua::Execute(String script){

	if(STOP != state)	Stop();
	if(script != "")	FScript = script;

	luaL_loadstring(FLua,AnsiString(FScript).c_str());
	lua_pcall(FLua,0,LUA_MULTRET,0);
	Flua	= lua_newthread(FLua);
	lua_getglobal(Flua,"Main");

	FState 	= 1;
	stop	= false;

//	state = PROCEED;

	FResult = lua_resume(Flua,0);
	if(FResult == LUA_YIELD){
		FState = 2;
//		state = PAUSED;
		return;
	}else
	if(FResult != 0)	ShowMessage("Ошибка выполнения скрипта!");

//	state = STOP;
	FState = 0;


};

//--------------------------------------------
void __fastcall ULua::Suspend(){

	stop = true;
	if(PROCEED == state){
//		state = PAUSED;
		FState = 2;
	}

};

//--------------------------------------------
void __fastcall ULua::Resume(){

	stop = false;
	if(PAUSED == state){
//		state = PROCEED;
		FResult = lua_resume(Flua,0);
		if(FResult == LUA_YIELD){
			FState = 2;
//			state = PAUSED;
			return;
		}else
		if(FResult != 0)	ShowMessage("Ошибка выполнения скрипта!");

//		state = STOP;
		FState = 0;
	}
};

//--------------------------------------------
void __fastcall ULua::Stop(){

	stop = true;
//	state = STOP;
	FState = 0;
};





