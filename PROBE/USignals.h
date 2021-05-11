//---------------------------------------------------------------------------

#ifndef USignalsH
#define USignalsH
#include "Templates.h"
//#include <boost/signals.hpp>
//#include <boost/bind.hpp>
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class USignals;
class USlot;

typedef void __fastcall (__closure *THandler)(String data);

const int	STRING_MESSAGE		= 0;
//===========================================================================
struct TObjectMsg{
	TObjectMsg(){Msg = 0; Data	= EmptyStr; Tag = 0;};
	TObjectMsg(unsigned msg, String data){Msg = msg; Data	= data; Tag = 0;};
	unsigned	Msg;
	int			Tag;
	String		Data;
};

//===========================================================================
class USignal{

friend class USignals;
public:

	virtual ~USignal();

	__property String		Name	= {read = GetName};
	__property USignals* 	Owner 	= {read = GetOwner};
	__property int			Count	= {read = GetCount};

	void __fastcall Execute(String data = "");
	void __fastcall	Message(String data = "");
	bool __fastcall Connect(USlot*);
	void __fastcall Disconnect(USlot*);
	void __fastcall DisconnectAll();

protected:
	USignal(USignals* Owner, String Name);

private:
	String		__fastcall	GetName();
	USignals*	__fastcall 	GetOwner();
	int			__fastcall	GetCount();

	String					fName;
	USignals*				fOwner;
	HMap<USlot*, USlot*>	fSlots;
};

//===========================================================================
class USignals{

public:
	USignals();
	virtual ~USignals();

	USignal*	operator[](String);

	USignal*	__fastcall Create(String);
	void		__fastcall Close(String);
	void 		__fastcall Clear();
	bool 		__fastcall Find(String);

private:
	HMap<String, USignal*>		fSignals;
	USignal*					fNullSignal;
};

//===========================================================================
class USlot:  public	TObject{

friend class USlots;
friend class USignal;
public:

	__fastcall ~USlot();

	__property String		Name		= {read = GetName};
	__property THandler		OnHandler	= {read = GetOnHandler, write = SetOnHandler};
	__property USlots*		Owner       = {read = GetOwner};
	__property USignal*		Signal		= {read = GetSignal};
//	__property String		Message		= {read = fObjectMsg.Data, write = SetMessage};
	__property TObjectMsg*  ObjectMsg	= {read = GetObjectMsg};

	void	__fastcall		Push(String message);
	String	__fastcall		Pop();
	void	__fastcall		ClearQueue();

    BEGIN_MESSAGE_MAP
		MESSAGE_HANDLER(STRING_MESSAGE, TObjectMsg*, MessageHandler)
	END_MESSAGE_MAP(TObject)

protected:
	USlot(USlots* Owner, String Name);
	bool __fastcall Connect(USignal* signal);
	void __fastcall Disconnect();

private:
	String		__fastcall	GetName();
	THandler	__fastcall	GetOnHandler();
	USlots*		__fastcall 	GetOwner();
	USignal*	__fastcall  GetSignal();
	TObjectMsg*	__fastcall	GetObjectMsg();

//	void		__fastcall	SetName(String);
//	void		__fastcall  SetMessage(String message);
	void		__fastcall	SetOnHandler(THandler);
	void		__fastcall	MessageHandler(TObjectMsg* msg);

	String				fName;
	THandler   			fHandler;
	USlots*				fOwner;
	USignal*			fSignal;
	TObjectMsg			fObjectMsg;
	HVector<String>		fQueue;
};

//===========================================================================
class USlots{

friend class USlot;
public:
	USlots(USignals*);
	virtual ~USlots();
	USlot*	operator[](String);

	__property USignals*	Signals	= {read = GetSignals};

	USlot*		__fastcall	Connect(String);
	void		__fastcall	Disconnect(String);
	void		__fastcall	DisconnectAll();

private:
	void		__fastcall  Disconnect(USlot* slot);
	USignals*	__fastcall	GetSignals();

	HMap<String, USlot*>		fSlots;
	USignals*					fSignals;
};




#endif
