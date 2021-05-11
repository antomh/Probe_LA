//---------------------------------------------------------------------------

#pragma hdrstop

#include "USignals.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//===========================================================================
USignal::USignal(USignals* Owner, String Name){

	fName		= Name;
	fOwner		= Owner;
	fSlots.Initialize();
};

//-------------------------------------------
USignal::~USignal(){

	DisconnectAll();
};

//-------------------------------------------
void __fastcall USignal::Execute(String data){

	USlot*	slot	= NULL;

	for(int i = 0; i < fSlots->Count; i++){
		fSlots->Get(i);

		try{
			slot	= fSlots->Key;
			if(slot->OnHandler)	slot->OnHandler(data);
		}catch(...){
			 Disconnect(slot);
		}

	}
};

//-------------------------------------------
void __fastcall	USignal::Message(String data){

	USlot*	slot	= NULL;

	for(int i = 0; i < fSlots->Count; i++){
		fSlots->Get(i);

		try{
			slot	= fSlots->Key;
			slot->Push(data);
			slot->Dispatch(slot->ObjectMsg);
		}catch(...){

		}

	}
};

//-------------------------------------------
bool __fastcall USignal::Connect(USlot* slot){

	if(fSlots->Find(slot))	return	false;
	fSlots->Add(slot,slot);
	return true;
};

//-------------------------------------------
void __fastcall USignal::Disconnect(USlot* slot){

	if(fSlots->Find(slot)){

		try{
			slot->ClearQueue();

		}__finally{
			fSlots->Delete(slot);
		}
	}
};

//-------------------------------------------
void __fastcall USignal::DisconnectAll(){

	for(int i = 0; i < fSlots->Count; i++){
		fSlots->Get(i);

		try{
			USlot*	slot	= fSlots->Key;
			slot->ClearQueue();
		}catch(...){
		}
	}
	fSlots->Clear();
};

//-------------------------------------------
String __fastcall	USignal::GetName(){

	return fName;
};

//-------------------------------------------
USignals*	__fastcall 	USignal::GetOwner(){

	return fOwner;
};

//-------------------------------------------
int			__fastcall	USignal::GetCount(){

	return	fSlots->Count;
};

//===========================================================================
USignals::USignals(){

	fNullSignal	= new USignal(this, "Пустышка");
	fSignals.Initialize();
};

//-------------------------------------------
USignals::~USignals(){

    Clear();
	delete fNullSignal;
};

//-------------------------------------------
USignal*	USignals::operator[](String name){

	if(fSignals->Find(name))	return fSignals[name];
	else						return fNullSignal;
};

//-------------------------------------------
USignal*	__fastcall USignals::Create(String name){

	if(name == "")				return fNullSignal;
	if(fSignals->Find(name))	return fSignals[name];
	else{
		USignal*	signal	= new USignal(this, name);
		fSignals->Add(name,signal);
		return signal;
    }
};

//-------------------------------------------
void		__fastcall USignals::Close(String name){

	if(fSignals->Find(name)){
		USignal* signal	 = fSignals[name];
		fSignals->Delete(name);
		delete signal;
	}
};

//-------------------------------------------
void 		__fastcall USignals::Clear(){

	for(int i = 0; i < fSignals->Count; i++){
		fSignals->Get(i);
		USignal* signal	 = fSignals->Value;
		delete signal;
	}
	fSignals->Clear();
};

//-------------------------------------------
bool 		__fastcall USignals::Find(String name){

	return fSignals->Find(name);
};

//===========================================================================
USlot::USlot(USlots* Owner, String Name){

	fName 	= Name;
	fOwner  = Owner;
	fQueue.Initialize();
};

//-------------------------------------------
__fastcall	USlot::~USlot(){

	//if(fSignal)	fSignal->Disconnect(this);
};

//-------------------------------------------
void	__fastcall		USlot::Push(String message){

	fQueue->Add(message);
};

//-------------------------------------------
String	__fastcall		USlot::Pop(){

	if(!fQueue->Count)	return EmptyStr;
	String message	= fQueue[0];
	fQueue->Delete(0);
	return message;
};

//-------------------------------------------
void	__fastcall		USlot::ClearQueue(){

	fQueue->Clear();
};

//-------------------------------------------
bool __fastcall USlot::Connect(USignal* signal){

	if(signal == fSignal)	return false;
	if(signal->Connect(this)){
		fName	= signal->Name;
		fQueue->Clear();
		return true;
	}else return false;
};

//-------------------------------------------
void __fastcall USlot::Disconnect(){

	Owner->Disconnect(this);
};

//-------------------------------------------
String	__fastcall 	USlot::GetName(){

	return fName;
};

//-------------------------------------------
THandler __fastcall USlot::GetOnHandler(){

	return fHandler;
};

//-------------------------------------------
USlots*		__fastcall 	USlot::GetOwner(){

	return fOwner;
};

//-------------------------------------------
USignal*	__fastcall  USlot::GetSignal(){

	return fSignal;
};

//-------------------------------------------
TObjectMsg*	__fastcall	USlot::GetObjectMsg(){

	return &fObjectMsg;
};
/*
//-------------------------------------------
void		__fastcall  USlot::SetMessage(String message){

	fObjectMsg.Data	= message;
};
*/
//-------------------------------------------
void __fastcall USlot::SetOnHandler(THandler handler){

	fHandler = handler;
};

//-------------------------------------------
void		__fastcall	USlot::MessageHandler(TObjectMsg* msg){

	String message	= Pop();
	if(OnHandler)	OnHandler(message);
};

//===========================================================================
USlots::USlots(USignals* signals){

	fSignals	= signals;
	fSlots.Initialize();
};

//-------------------------------------------
USlots::~USlots(){

	DisconnectAll();
};

//-------------------------------------------
USlot*	USlots::operator[](String name){

	if(fSlots->Find(name))	return fSlots[name];
	return NULL;
};

//-------------------------------------------
USlot*	__fastcall 	USlots::Connect(String name){

	if(fSlots->Find(name))	return fSlots[name];
	if(fSignals->Find(name)){
		USignal*	signal	= fSignals[0][name];
		USlot*	slot	= new USlot(this, name);
		if(slot->Connect(signal)){
			fSlots->Add(slot->Name, slot);
			return slot;
		}else delete slot;
	}
	return NULL;
};

//-------------------------------------------
void	__fastcall 	USlots::Disconnect(String name){

	if(fSignals->Find(name)){
		if(fSlots->Find(name)){
			USlot* slot	= fSlots[name];
			fSignals[0][name]->Disconnect(slot);
		}
	}
};

//-------------------------------------------
void	__fastcall 	USlots::DisconnectAll(){

	for(int i = fSlots->Count - 1; i >= 0 ; i--){
		fSlots->Get(i);
		USlot* slot	= fSlots->Value;
		fSignals[0][slot->Name]->Disconnect(slot);
	}
};

//-------------------------------------------
void	__fastcall 	USlots::Disconnect(USlot* slot){

	if(!slot)	return;
	if(fSlots->Find(slot->Name)){
		fSlots->Delete(slot->Name);
		delete slot;
	}
};

//-------------------------------------------
USignals* __fastcall		USlots::GetSignals(){

	return fSignals;
};



