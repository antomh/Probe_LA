#ifndef InterfacesH
#define InterfacesH
//------------------------------------------------------------------------------
#include "Templates.h"
#include "UData.h"
#include "Observer.h"
#include <System.Classes.hpp>
#include <Vcl.Forms.hpp>
//------------------------------------------------------------------------------
#define T_MODULES 		0
#define T_MODULE 		1
#define T_OBJECT 		2
#define T_COMMANDS		3
#define T_COMMAND		4
#define T_AUTHORITY		5
#define T_AUTORITIES	6
#define T_HANDLER		7
#define T_HANDLERS		8
#define T_FORM			9
#define T_FORMS			10

//------------------------------------------------------------------------------
class IAuthorities;
class IHandlers;
class ICommands;
class IForms;
//==============================================================================
class IModBase{

	public:

	virtual ~IModBase(){};

	//---------- Свойства ---------------------------

	__property int Type	= {read = GetType};

	//---------- Функции ----------------------------

	virtual int 	GetType()			= 0;
	virtual void 	SetData(HData data)	= 0;
	virtual	HData	GetData()			= 0;
};

class IObject;
//==============================================================================
class ICommand: public IModBase{

	public:

	virtual ~ICommand(){};

	//---------- Свойства ---------------------------

	__property String 	Name	= {read = GetName};
	__property String 	Info  	= {read = GetInfo};
	__property String	Caption	= {read = GetCaption};
	__property IObject*	Parent	= {read = GetParent, write = SetParent};

	//---------- Операторы преобразования  ----------

	virtual operator UnicodeString()			= 0;
	virtual void operator=(UnicodeString)		= 0;

	//---------- Функции ----------------------------

	virtual	bool 	Execute()		   	= 0;
	virtual void 	Tool()			   	= 0;

	protected:

	//---------- Закрытые функции --------------------

	virtual		String	GetName()			= 0;
	virtual		String	GetInfo()			= 0;
	virtual		String	GetCaption()		= 0;

	virtual void		SetParent(IObject*)	= 0;
	virtual IObject*	GetParent()			= 0;

};

//==============================================================================
class ICommands: public IModBase{

	public:

	virtual ~ICommands(){};

	//---------- Свойства ---------------------------

//	__property String 		Name	= {read = GetName};
	__property unsigned 	Count	= {read = GetCount};
	__property bool			Bof		= {read = GetBof};
	__property bool			Eof		= {read = GetEof};
	__property ICommand*	Value	= {read = GetValue};
	__property String		Key		= {read = GetKey};
	__property IObject*		Parent	= {read = GetParent, write = SetParent};

	//---------- Операторы --------------------------

	virtual operator UnicodeString()			= 0;
	virtual void operator=(UnicodeString)		= 0;
	virtual ICommand*	operator[](String key)	= 0;

	//---------- Функции ----------------------------

	virtual void		First()				= 0;
	virtual void		End()				= 0;
	virtual void		Next()				= 0;
	virtual void		Previous()			= 0;
	virtual ICommand*	Get(int)			= 0;

	protected:

	//---------- Закрытые функции --------------------

//	virtual	 String 	GetName()	  		= 0;
	virtual unsigned	GetCount(void)		= 0;
	virtual bool		GetBof(void)		= 0;
	virtual bool		GetEof(void)		= 0;
	virtual ICommand*	GetValue(void)		= 0;
	virtual String		GetKey(void)		= 0;

	virtual void		SetParent(IObject*)	= 0;
	virtual IObject*	GetParent()			= 0;
};

class IModule;
//==============================================================================
class IObject: public IModBase{

	public:

	virtual ~IObject(){};

	//---------- Свойства ---------------------------

	__property String 			Name 	 	= {read = GetName, write = SetName};
	__property String			Caption		= {read = GetCaption};
	__property int				Num			= {read = GetNum, write	= SetNum};
	__property IModule*			Parent		= {read = GetParent, write = SetParent};
	__property ICommands*   	Commands 	= {read = GetCommands};
//	__property IAuthorities* 	Authorities = {read = GetAuthorities};
//	__property IHandlers*		Handler		= {read = GetHandlers};
	__property IForms*          Forms		= {read = GetForms};

	//---------- Операторы преобразования  ----------

	virtual					operator UnicodeString() = 0;
	virtual void   			operator=(UnicodeString) = 0;

	//---------- Функции ----------------------------

	protected:

	//---------- Закрытые функции --------------------
	virtual void			SetParent(IModule*)	= 0;
	virtual void 			SetName(String)		= 0;
	virtual void			SetNum(int num)		= 0;

	virtual String 			GetName()			= 0;
	virtual String			GetCaption()		= 0;
	virtual int				GetNum()			= 0;

	virtual ICommands* 		GetCommands()		= 0;
//	virtual IAuthorities* 	GetAuthorities()	= 0;
//	virtual IHandlers*		GetHandlers()		= 0;
	virtual IForms*			GetForms()			= 0;
	virtual IModule*		GetParent()			= 0;

};

class IModules;
//==============================================================================
class IModule: public IModBase{

	public:

	virtual ~IModule(){};

	//---------- Свойства ---------------------------

	__property String 			Name  = {read = GetName};
	__property String 			Info  = {read = GetInfo/*, write = SetInfo*/};
	__property String			Caption	= {read = GetCaption, write = SetCaption};
	__property unsigned 		Count = {read = GetCount};
	__property bool				Bof	  = {read = GetBof};
	__property bool				Eof	  = {read = GetEof};
	__property String			Key   = {read = GetKey};
	__property IObject*			Value = {read = GetValue};

	__property IModules* 		Parent = {read = GetModules};
	__property IAuthorities* 	Authorities = {read = GetAuthorities};
	__property IHandlers*		Handlers		= {read = GetHandlers};

	//---------- Операторы преобразования  ----------

	virtual IObject* 		operator[](String)		 = 0;
	virtual					operator UnicodeString() = 0;
	virtual void   			operator=(UnicodeString) = 0;

	//---------- Функции ----------------------------

	virtual void		__fastcall Clear()					= 0;
	virtual IObject*	__fastcall Create(String name = "")	= 0;
	virtual void		__fastcall Delete(String )			= 0;
	virtual bool		__fastcall	Find(String)			= 0;
	virtual bool		__fastcall	Set(String)				= 0;

	virtual void		First()  				= 0;
	virtual void		End()	 				= 0;
	virtual void		Next()	 				= 0;
	virtual void		Previous()				= 0;
	virtual IObject*	Get(int)				= 0;

	protected:

	//---------- Закрытые функции --------------------

//	virtual void		SetInfo(String) = 0;
	virtual int				GetCount(void)	= 0;
	virtual bool			GetBof(void)	= 0;
	virtual bool			GetEof(void)	= 0;
	virtual IObject*		GetValue(void)	= 0;
	virtual String			GetKey(void)	= 0;
	virtual String			GetName()		= 0;
	virtual	String			GetInfo()		= 0;
	virtual IModules*		GetModules()	= 0;
	virtual IAuthorities* 	GetAuthorities()= 0;
	virtual IHandlers*		GetHandlers()	= 0;
	virtual String			GetCaption()	= 0;
	virtual void			SetCaption(String)	= 0;
};

//==============================================================================
class IModules: public IModBase{

	public:

	virtual ~IModules(){};

	//---------- Свойства ---------------------------

	__property unsigned Count = {read = GetCount};
	__property bool		Bof	  = {read = GetBof};
	__property bool		Eof	  = {read = GetEof};
	__property String	Key   = {read = GetKey};
	__property IModule*	Value = {read = GetValue};

	//---------- Операторы преобразования  ----------

	virtual IModule* 		operator[](String)		 = 0;
	virtual					operator UnicodeString() = 0;
	virtual void   			operator=(UnicodeString) = 0;

	//---------- Функции ----------------------------

	virtual void __fastcall Clear()					= 0;
	virtual void __fastcall Add(String,IModule*)	= 0;
	virtual void __fastcall Delete(String)			= 0;
	virtual bool __fastcall	Find(String)			= 0;
	virtual bool __fastcall	Set(String)				= 0;

//	virtual HData	GetRegister()		= 0;

	virtual void		First()  				= 0;
	virtual void		End()	 				= 0;
	virtual void		Next()	 				= 0;
	virtual void		Previous()				= 0;
	virtual IModule*	Get(int)				= 0;

	virtual void		Reg(IObserv*)   		= 0;
	virtual void		UnReg(IObserv*)			= 0;
	virtual void		Inform(HData)			= 0;

	protected:

	//---------- Закрытые функции --------------------

	virtual int			GetCount(void)	= 0;
	virtual bool		GetBof(void)	= 0;
	virtual bool		GetEof(void)	= 0;
	virtual IModule*	GetValue(void)	= 0;
	virtual String		GetKey(void)	= 0;

};

//==============================================================================
class IAuthority: public IModBase{

	public:

	virtual ~IAuthority(){};

	//---------- Свойства ---------------------------

	__property String 	Name	= {read = GetName};
	__property String 	Info  	= {read = GetInfo};
	__property bool	  	Access  = {read = GetAccess, write = SetAccess};
	__property IModule*	Parent	= {read = GetParent, write = SetParent};

	//---------- Операторы преобразования  ----------

	virtual operator UnicodeString()			= 0;
	virtual void operator=(UnicodeString)		= 0;

	//---------- Функции ----------------------------
	virtual void	Refresh()				= 0;

	protected:

	//---------- Закрытые функции --------------------
	virtual	 void	SetAccess(bool)		= 0;
	virtual	 String GetName()			= 0;
	virtual	 String GetInfo()			= 0;
	virtual	 bool	GetAccess()			= 0;

	virtual void		SetParent(IModule*)	= 0;
	virtual IModule*	GetParent()			= 0;
};

//==============================================================================
class IAuthorities: public IModBase{

	public:

	virtual ~IAuthorities(){};

	//---------- Свойства ---------------------------

//	__property String 		Name	= {read = GetName};
	__property unsigned 	Count	= {read = GetCount};
	__property bool			Bof		= {read = GetBof};
	__property bool			Eof		= {read = GetEof};
	__property IAuthority*	Value	= {read = GetValue};
	__property String		Key		= {read = GetKey};
	__property IModule*		Parent	= {read = GetParent, write = SetParent};

	//---------- Операторы --------------------------

	virtual operator UnicodeString()			= 0;
	virtual void operator=(UnicodeString)		= 0;
	virtual IAuthority*	operator[](String key)	= 0;

	//---------- Функции ----------------------------

	virtual void		First()				= 0;
	virtual void		End()				= 0;
	virtual void		Next()				= 0;
	virtual void		Previous()			= 0;
	virtual IAuthority* Get(int)			= 0;
	virtual void		Register()			= 0;
	virtual void		Unregister()		= 0;
	virtual void		Refresh()			= 0;

	protected:

	//---------- Закрытые функции --------------------

//	virtual	 String 	GetName()	  	= 0;
	virtual unsigned	GetCount(void)	= 0;
	virtual bool		GetBof(void)	= 0;
	virtual bool		GetEof(void)	= 0;
	virtual IAuthority*	GetValue(void)	= 0;
	virtual String		GetKey(void)	= 0;

	virtual void		SetParent(IModule*)	= 0;
	virtual IModule*	GetParent()			= 0;

};

//==============================================================================
class IHandler: public IModBase{

	public:

	virtual ~IHandler(){};

	//---------- Свойства ---------------------------

	__property String 	Name	= {read = GetName};
	__property String 	Info  	= {read = GetInfo};
	__property String 	Script  = {read = GetScript, write = SetScript};
	__property IModule*	Parent	= {read = GetParent, write = SetParent};

	//---------- Операторы преобразования  ----------

	virtual operator UnicodeString()			= 0;
	virtual void operator=(UnicodeString)		= 0;

	//---------- Функции ----------------------------

	protected:

	//---------- Закрытые функции --------------------

	virtual	 void	SetScript(String)	= 0;
	virtual	 String GetName()			= 0;
	virtual	 String GetInfo()			= 0;
	virtual	 String GetScript()			= 0;

	virtual void		SetParent(IModule*)	= 0;
	virtual IModule*	GetParent()			= 0;
};

//==============================================================================
class IHandlers: public IModBase{

	public:

	virtual ~IHandlers(){};

	//---------- Свойства ---------------------------

//	__property String 		Name	= {read = GetName};
	__property unsigned 	Count	= {read = GetCount};
	__property bool			Bof		= {read = GetBof};
	__property bool			Eof		= {read = GetEof};
	__property IHandler*	Value	= {read = GetValue};
	__property String		Key		= {read = GetKey};
	__property IModule*		Parent	= {read = GetParent, write = SetParent};

	//---------- Операторы --------------------------

	virtual operator UnicodeString()			= 0;
	virtual void operator=(UnicodeString)		= 0;
	virtual IHandler*	operator[](String key)	= 0;

	//---------- Функции ----------------------------

	virtual void		First()			= 0;
	virtual void		End()			= 0;
	virtual void		Next()			= 0;
	virtual void		Previous()		= 0;
	virtual IHandler*	Get(int)		= 0;

	protected:

	//---------- Закрытые функции --------------------

//	virtual	 String 	GetName()	  	= 0;
	virtual unsigned	GetCount(void)	= 0;
	virtual bool		GetBof(void)	= 0;
	virtual bool		GetEof(void)	= 0;
	virtual IHandler*	GetValue(void)	= 0;
	virtual String		GetKey(void)	= 0;

	virtual void		SetParent(IModule*)	= 0;
	virtual IModule*	GetParent()			= 0;

};

//==============================================================================
class IForm: public IModBase{

	friend class ICreator;
	public:

	virtual ~IForm(){};

	//---------- Свойства ---------------------------

	__property String 	Name		= {read = GetName, write = SetName};
	__property String 	Info  		= {read = GetInfo};
	__property String 	ClassName 	= {read = GetClassName, write = SetClassName};
	__property IObject*	Parent		= {read = GetParent, write = SetParent};

	//---------- Операторы преобразования  ----------

	virtual operator UnicodeString()		= 0;
	virtual void operator=(UnicodeString)	= 0;
	virtual operator TForm*()				= 0;
	virtual TForm*	operator->()			= 0;

	//---------- Функции ----------------------------


	protected:

	//---------- Закрытые функции --------------------
	virtual void SetName(String)		= 0;
	virtual void SetClassName(String)	= 0;

	virtual	 String GetName()			= 0;
	virtual	 String GetInfo()			= 0;
	virtual	 String GetClassName()		= 0;

	virtual void		SetParent(IObject*)	= 0;
	virtual IObject*	GetParent()			= 0;
};

//==============================================================================
class ICreator{

	public:

	~ICreator(){};
	virtual String GetInfo() = 0;
	virtual IForm* Create(String classname, String name = "")	= 0;

};

//==============================================================================
class IForms: public IModBase{

	public:

	virtual ~IForms(){};

		//---------- Свойства ---------------------------

//	__property String 	Name  = {read = GetName};
	__property String 	Info  = {read = GetInfo};
	__property unsigned Count = {read = GetCount};
	__property bool		Bof	  = {read = GetBof};
	__property bool		Eof	  = {read = GetEof};
	__property String	Key   = {read = GetKey};
	__property IForm*	Value = {read = GetValue};
	__property IObject*	Parent	= {read = GetParent, write = SetParent};

	//---------- Операторы преобразования  ----------

	virtual IForm*	 		operator[](String)		 = 0;
	virtual					operator UnicodeString() = 0;
	virtual void   			operator=(UnicodeString) = 0;

	//---------- Функции ----------------------------

	virtual void 	__fastcall Clear()					 					= 0;
	virtual IForm* 	__fastcall Create(String classname, String name = "")	= 0;
	virtual void 	__fastcall Delete(String )			 					= 0;
	virtual bool 	__fastcall	Find(String)			 					= 0;
	virtual bool 	__fastcall	Set(String)				 					= 0;

	virtual void	First()  	= 0;
	virtual void	End()	 	= 0;
	virtual void	Next()	 	= 0;
	virtual void	Previous()	= 0;
	virtual IForm*	Get(int)	= 0;

	protected:

	//---------- Закрытые функции --------------------

//	virtual void		SetInfo(String) = 0;
	virtual int			GetCount(void)	= 0;
	virtual bool		GetBof(void)	= 0;
	virtual bool		GetEof(void)	= 0;
	virtual IForm*		GetValue(void)	= 0;
	virtual String		GetKey(void)	= 0;
//	virtual String		GetName()		= 0;
	virtual	String		GetInfo()		= 0;

	virtual void		SetParent(IObject*)	= 0;
	virtual IObject*	GetParent()			= 0;
};
//------------------------------------------------------------------------------
#endif
