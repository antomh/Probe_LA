//---------------------------------------------------------------------------

#ifndef AdminH
#define AdminH
#include "UData.h"
#include "Templates.h"
#include "UGlobal.h"
//---------------------------------------------------------------------------
class HGlobal;

class UUser;
class HUser;

class UAut;
class HAut;

class UGroupAuts;
class HGroupAuts;

class UAuts;
class HAuts;

//==============================================================================
class __declspec(dllexport) HUser{

	public:

	HUser();
	~HUser();

	__property HGlobal*	Parent 		= {read = GetParent, write = SetParent};
	__property String	Name		= {read = GetName, write = SetName};
	__property String	Dolzhn		= {read = GetDolzhn, write = SetDolzhn};
	__property String	Zvan		= {read = GetZvan, write = SetZvan};
	__property String	Category	= {read = GetCategory, write = SetCategory};
	__property int 		Rank		= {read = GetRank, write = SetRank};
	__property String	Authority	= {read = GetAuthority, write = SetAuthority};
	__property String	Login		= {read = GetLogin, write = SetLogin};
	__property String	Password	= {read = GetPassword, write = SetPassword};


	void	SetData(String data);
	String	GetData();

	private:

	void	SetParent(HGlobal*);
	void	SetName(String);
	void	SetDolzhn(String);
	void	SetZvan(String);
	void	SetCategory(String);
	void	SetRank(int);
	void	SetAuthority(String);
	void	SetLogin(String);
	void	SetPassword(String);

	HGlobal*	GetParent();
	String		GetName();
	String		GetDolzhn();
	String		GetZvan();
	String		GetCategory();
	int			GetRank();
	String		GetAuthority();
	String		GetLogin();
	String		GetPassword();

	HPtr<UUser>			FUser;
};

//==============================================================================
class __declspec(dllexport) HAut{

	friend class HGroupAuts;
	public:
	HAut();
	~HAut();

//	operator bool();
//	void operator=(bool);

	__property String 	Name 	= {read = GetName,write = SetName};
	__property String 	Path 	= {read = GetPath, write = SetPath};
	__property bool     Access	= {read = GetAccess, write = SetAccess};

	void	SetData(String);
	String 	GetData();

	private:

    void	SetName(String);
	void	SetPath(String);
	void	SetAccess(bool);

	bool	GetAccess();
	String 	GetName();
	String 	GetPath();

	HPtr<UAut>		FAut;
	HGroupAuts*		FParent;
};

//==============================================================================
class __declspec(dllexport) HGroupAuts{

	friend class HAuts;
	public:
	HGroupAuts();
	~HGroupAuts();

	HAut	operator[](String name);

	__property String 		Name 	= {read = GetName};
	__property int			Count	= {read = GetCount};
	__property bool			Bof		= {read = GetBof};
	__property bool			Eof		= {read = GetEof};
	__property String		Key		= {read = GetKey};
	__property HAut   		Value	= {read = GetValue};

	bool	Find(String name);
	void	First();
	void	End();
	void	Next();
	void 	Previous();

	void	SetData(String);
	String 	GetData();

	void	Set();
	void	Reset();
	void	SetAuthorities(String);
	void	Refresh(String name);

	private:

	String	GetName();
	int		GetCount();
	bool	GetEof();
	bool	GetBof();
	String	GetKey();
	HAut	GetValue();

	HPtr<UGroupAuts>		FGroup;
	HGlobal*				FParent;
};

//==============================================================================
class __declspec(dllexport) HAuts{

	public:
	HAuts();
	~HAuts();

	HGroupAuts	operator[](String name);

	__property int			Count	= {read = GetCount};
	__property bool			Bof		= {read = GetBof};
	__property bool			Eof		= {read = GetEof};
	__property String		Key		= {read = GetKey};
	__property bool			Access	= {read = GetAccess, write = SetAccess};
	__property HGroupAuts	Value	= {read = GetValue};
	__property HGlobal*		Parent 	= {read = GetParent, write = SetParent};

	void	Add(String name, String data);
	void	Delete(String name);
	bool	Find(String name);
	void	First();
	void	End();
	void	Next();
	void 	Previous();

	void	SetData(String);
	void	SetAuthorities(String);
	String 	GetData();

	void	Refresh(String name);

	private:

	void		SetParent(HGlobal*);
	void		SetAccess(bool);

	int			GetCount();
	bool		GetEof();
	bool		GetBof();
	String		GetKey();
	HGroupAuts	GetValue();
	HGlobal*	GetParent();
	bool		GetAccess();

	HPtr<UAuts>		FAuts;
	HGlobal*		FParent;
};






















#endif
