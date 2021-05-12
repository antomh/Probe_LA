//---------------------------------------------------------------------------

#ifndef ULuaH
#define ULuaH

#include "lua.hpp"
#include "string"
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include "Templates.h"
#include "ULuaFunc.h"
//#include "UFName.h"

//---------------------------------------------------------------------------
//#define LUA_GLOBALSINDEX
//typedef int (*lua_CFunction) ( lua_State * );
//---------------------------------------------------------------------------

//==============================================================================
class ULua{

	public:
	//------------------------------------------
	ULua();
	~ULua();

	__property String 	Script 		= {read = GetScript, 	write = SetScript};
	__property int 		State		= {read = GetState, 	write = SetState};

	void __fastcall Execute(String script);
	void __fastcall Suspend();
	void __fastcall Resume();
	void __fastcall Stop();
	//-------------------------------------------



	protected:

	void		SetScript(String script);
	void		SetState(int);

	String		GetScript();
	int			GetState();

	lua_State*		FLua;
	lua_State*		Flua;

	int				FResult;
	String			FScript;
	int				FState;
};

#endif
