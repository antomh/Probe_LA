//---------------------------------------------------------------------------
#ifndef UDataH
#define UDataH
//------------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.hpp>
#include "Templates.h"


//------------------------------------------------------------------------------
#define TYPE_NULL	0
#define TYPE_ARRAY	1
#define TYPE_OBJECT	2
#define TYPE_STRING	3
#define TYPE_INT	4
#define TYPE_LONG	5
#define TYPE_FLOAT	6
#define TYPE_BOOL	7
//------------------------------------------------------------------------------
class IData;
class UKeyHost;
class UObserv;
typedef bool (*TCompare)(String arg1, String arg2);
//==============================================================================
class  __declspec(dllimport) HData{

	friend class USimple;
	friend class HReg;


	public:
	//-----------   конструкторы и   ---------

	HData(bool temp);
	HData(int type = TYPE_OBJECT);
	HData(const NPtr<IData*>& data);
	HData(const HData& data);
	HData(::String json);
	~HData();
	void operator=(const NPtr<IData*> data);
	void operator=(const HData& data);
	//----------   операторы селекторы -------------------

	HData operator[](UnicodeString key);
	HData operator[](__int64 key);

	//----------  операторы преобразования ---------------
	void operator=(UnicodeString json);
	void operator=(const char* json);
	void operator=(std::string json);

	operator NPtr<IData*>();
	operator UnicodeString();
	operator char();
	operator unsigned char();
	operator short();
	operator unsigned short();
	operator int();
	operator unsigned int();
	operator long();
	operator unsigned long();
	operator __int64();
	operator unsigned __int64();
	operator bool();
	operator float();
	operator double();
	operator std::string();

	//----------- оператор сравнения ----------------------

	bool operator==(HData& source);

	//----------- свойства --------------------------------
	__property UnicodeString	ClassName = {read = GetClassName};
	__property UnicodeString	Name	  = {read = GetName, write = SetName};
	__property int				Type	  = {read = GetType};
	__property HData			Parent	  = {read = GetParent, write = SetParent};
	__property UnicodeString	Path	  = {read = GetPath};

	__property UnicodeString	String	  = {read = GetString,write = SetString};
	__property bool				Bool	  = {write = SetBool};
	__property int				Int		  = {write = SetInt};
	__property __int64			Int64	  = {write = SetInt64};
	__property double			Float	  = {write = SetFloat};


	__property unsigned 		Count	  = {read = GetCount};
	__property bool				Bof		  = {read = GetBof};
	__property bool				Eof		  = {read = GetEof};
	__property HData			Value	  = {read = GetValue};
	__property UnicodeString	Key		  = {read = GetKey};
	__property int				Index	  = {read = GetIndex};
	__property TCompare 		Compare		= {read = GetCompare, write = SetCompare};
	__property bool				Sorted		= {read = GetSorted, write = SetSorted};

	__property bool				Observer  = {read = FObserver, write = FObserver};
//	__property UHost*			Host	  = {read = GetHost};

	//------------- функции ---------------------------------

	void	__fastcall	Clear();
	HData	__fastcall	Add(int type, UnicodeString name = "");
	HData	__fastcall	AddBool(UnicodeString name = "");
	HData	__fastcall 	AddInt(UnicodeString name = "");
	HData	__fastcall	AddInt64(UnicodeString name = "");
	HData	__fastcall	AddFloat(UnicodeString name = "");
	HData	__fastcall	AddArray(UnicodeString name = "");
	HData	__fastcall	AddObject(UnicodeString name = "");
	HData	__fastcall	AddString(UnicodeString name = "");
	HData	__fastcall	AddData(NPtr<IData*>& data, UnicodeString name = "");

	bool	__fastcall	isNULL();
	bool	__fastcall	isArray();
	bool	__fastcall	isObject();
	bool	__fastcall	isString();
	bool	__fastcall	isInt();
	bool	__fastcall	isLong();
	bool	__fastcall	isBool();
	bool	__fastcall	isFloat();


	void	__fastcall	Delete(UnicodeString name);
	void	__fastcall	Delete(unsigned index);
	void	__fastcall	Rename(UnicodeString oldname, UnicodeString newname);
	void 	__fastcall 	Move(unsigned pos, UnicodeString key);
	void 	__fastcall 	Insert(unsigned pos, UnicodeString key, HData data);
	unsigned 	__fastcall	IndexOf(UnicodeString key);
	void	__fastcall	Sort(TCompare	compare = NULL);
	void	__fastcall	BeginUpdate();
	void	__fastcall	EndUpdate();
	void	__fastcall	Update();

	HData  	__fastcall  Get(unsigned index);
	HData	__fastcall	Get(UnicodeString);

	bool	__fastcall	Find(UnicodeString);

	void	__fastcall	First();
	void	__fastcall	End();
	void	__fastcall	Next();
	void	__fastcall	Previous();

	//-------------- функции хоста ------------------------
//	void Reg(UObserver*);
//	void UnReg(UObserver*);
//	void Informate();
	void Reg(UnicodeString key, UObserv*);
	void UnReg(UnicodeString key, UObserv*);
	void Informate(UnicodeString key);

	protected:

	//-------------- Скрытые функции ---------------------

	UnicodeString 	GetClassName();
	UnicodeString 	GetName();
	int				GetType();
	int				GetInt();
	__int64			GetInt64();
	double			GetFloat();
	bool			GetBool();
	int	   			GetCount(void);
	bool			GetBof(void);
	bool    		GetEof(void);
	HData			GetValue(void);
	UnicodeString 	GetKey(void);
	int				GetIndex(void);
	UnicodeString	GetString();
	HData			GetParent();
	UnicodeString	GetPath();
	TCompare		GetCompare();
	bool			GetSorted();

	void			SetCompare(TCompare compare);
	void			SetSorted(bool	sorted);
	void 			SetString(UnicodeString str);
	void 			SetName(UnicodeString);
	void			SetParent(NPtr<IData*> data);
	void			SetInt(int);
	void			SetInt64(__int64);
	void			SetFloat(double);
	void			SetBool(bool);
//	void			SetParent(HData data);
	void 			Wrap(::String source, TStrings* receiver, ::String delimiters);
	//-------------- Скрытые члены -----------------------

	mutable NPtr<IData*>		FPointer;
	bool						FObserver;
};


//==============================================================================
class __declspec(dllexport) HReg: public HData{

	public:
	HReg();
	~HReg();

	//----------  операторы преобразования ---------------
	void operator=(UnicodeString json);
	void operator=(const char* json);
	void operator=(std::string json);


	HReg operator[](UnicodeString key);
	bool Find(UnicodeString key);
	void Reg(UnicodeString key, UObserv*);
	void UnReg(UnicodeString key, UObserv*);
	void Informate(UnicodeString key);
	void	SetString(UnicodeString str);
	void	SetInt(int);
	void	SetInt64(__int64);
	void	SetFloat(double);
	void	SetBool(bool);

	protected:
	static UnicodeString 		FPath;
	bool						FFlag;


//	protected:
//	static UKeyHost		FHost;
};

UnicodeString HReg::FPath = NULL;
//UKeyHost HReg::FHost;

#endif
