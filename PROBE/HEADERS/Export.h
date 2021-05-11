#ifndef Unit2H
#define Unit2H
//----------------------------------------------
//#include "Interfaces.h"
#include "RModule.h"
#include "UGlobal.h"
//----------------------------------------------

extern "C" IModule* __declspec(dllexport) Create(HGlobal*	global);
extern "C" void __declspec(dllexport) Close(IModule*);


#endif
