#ifndef	TEMPLATES2_H
#define TEMPLATES2_H
#include <map>
#include <unordered_map>
#include <set>
#include <vector>
#include <System.Classes.hpp>

using std::pair;
using std::multimap;
using std::map;
using std::set;
using std::vector;

class NullType;
//==============================================================================
struct MyLess : std::binary_function <String, String, bool>{

	//--------------------------------
	void __fastcall Diff(String Src,String& name,String& count)const{

		name	= Src;
		count	= 0;
		int N	= Src.Length();
		int P	= 0;

		for(int i = N; i > 0; i--){
			if(isdigit(name[i])) P++;
			else break;
		}
		count	=	Src.SubString(N-P+1,P);
		name	=	Src.SubString(1,N-P);

	};

	//----------------------------------
	result_type operator() (first_argument_type arg1, second_argument_type arg2)const{

//		return arg2 < arg1; //сравниваем как хотим.
		String name1	= "";
		String name2	= "";
		String num1		= "";
		String num2		= "";
		Diff(arg1,name1,num1);
		Diff(arg2,name2,num2);
		if(name1 != name2)		return name1 < name2;
		else if(num1 == "")    return arg1 < arg2;
		else if(num2 == "")    return arg1 < arg2;
		else{
			try{
				return StrToInt(num1) < StrToInt(num2);
			}catch(...){};
		}
		return false;
	};

};

//==============================================================================
/*
	MPtr - ведущий указатель:
	1. Этот указатель не может быть пустым;
	2. При копировании создается копия объекта, а не указателя;
	3. Реализуется подсчет ссылок;

*/

template <typename T>
class MPtr{
	private:
		int Count;

	protected:
		T*	Ptr;

	public:
		MPtr();
		MPtr(const MPtr<T>&);
		MPtr(const T&);
		MPtr<T>&	operator=(const MPtr<T>&);
		T*	operator->();
		operator	T*();
		void	IncRef();
		void	DecRef();
		virtual	~MPtr();
		void	Set(MPtr<T>*);
		int		Get() const;

};

//---------------------------------------------------
template <typename T>
inline MPtr<T>::MPtr(){

	Ptr		= new T();
	Count	= 0;
};

//---------------------------------------------------
template <typename T>
inline MPtr<T>::MPtr(const MPtr<T>& source){

	if(source.Ptr == NULL) 	Ptr = new T;
	else 					Ptr = new T(*(source.Ptr));
	Count = 0;
};

//---------------------------------------------------
template <typename T>
inline MPtr<T>::MPtr(const T& source){

	Ptr		= new T(source);
	Count	= 0;
};

//---------------------------------------------------
template <typename T>
inline MPtr<T>::~MPtr(){

	delete Ptr;

};

//---------------------------------------------------
template <typename T>
MPtr<T>&	MPtr<T>::operator=(const MPtr<T>& source){

	if(source.Ptr == NULL)	return *this;
	if(this != &source){
		if(Ptr != NULL) delete Ptr;
		Ptr		= new T(*(source.Ptr));
		Count	= 0;
	}
	return *this;
};

//---------------------------------------------------
template <typename T>
T*	MPtr<T>::operator->(){

	return Ptr;
};

//---------------------------------------------------
template <typename T>
MPtr<T>::operator	T*(){

	return Ptr;
};

//---------------------------------------------------
template <typename T>
void	MPtr<T>::IncRef(){

	Count++;
};

//---------------------------------------------------
template <typename T>
void	MPtr<T>::DecRef(){

	Count--;
	if(!Count){
		delete	this;
	}
};

//---------------------------------------------------
template <typename T>
void	MPtr<T>::Set(MPtr<T>* ptr){

	if(!ptr)	return;
	if(Ptr){
		delete Ptr;
		Ptr = ptr->Ptr;
		ptr->IncRef();
	}else{
		Ptr = ptr->Ptr;
		IncRef();
	}
};

//---------------------------------------------------
template <typename T>
int	MPtr<T>::Get() const{

	return (int)Ptr;
};

//==============================================================================
template <typename T>
class HPtr{
	protected:
		mutable MPtr<T>*	Ptr;
	public:
		HPtr(bool init = false);
		HPtr(int){Initialize()};
		HPtr(const HPtr<T>&);
		HPtr<T>&	operator=(const HPtr<T>&);
		HPtr<T>&	operator=(T*);
		T*	operator->();
		operator	T*();
		virtual	~HPtr();
		void Initialize();
		void Initialize(const HPtr<T>&);
		void UnInitialize();
		void Set(HPtr<T>&);
		int	 Get() const;
};

//---------------------------------------------------
template <typename T>
inline HPtr<T>::HPtr(bool init){

	Ptr		= NULL;
	if(init)	Initialize();
};

//---------------------------------------------------
template <typename T>
inline HPtr<T>::HPtr(const HPtr<T>& source){

	Ptr		= source.Ptr;
	if(Ptr) Ptr->IncRef();

};

//---------------------------------------------------
template <typename T>
inline HPtr<T>::~HPtr(){

	UnInitialize();

};

//---------------------------------------------------
template <typename T>
HPtr<T>&	HPtr<T>::operator=(const HPtr<T>& source){

	if(&source == this) return *this;
	if(Ptr) Ptr->DecRef();
	Ptr = source.Ptr;
	if(Ptr) Ptr->IncRef();
	return *this;
};

//---------------------------------------------------
template <typename T>
HPtr<T>&	HPtr<T>::operator=(T*	source){

	if(Ptr) Ptr->DecRef();
	Ptr = new	MPtr<T>(*source);
	if(Ptr) Ptr->IncRef();
	return *this;

};
//---------------------------------------------------
template <typename T>
T*	HPtr<T>::operator->(){

	return (T*)*Ptr;
};

//---------------------------------------------------
template <typename T>
HPtr<T>::operator	T*(){

	if(Ptr) return *Ptr;
	else return NULL;
};

//---------------------------------------------------
template <typename T>
void HPtr<T>::Initialize(){

	if(Ptr) Ptr->DecRef();
	Ptr = new	MPtr<T>();
	if(Ptr) Ptr->IncRef();
};

//---------------------------------------------------
template <typename T>
void HPtr<T>::Initialize(const HPtr<T>& source){

	if(Ptr) Ptr->DecRef();
	Ptr = new	MPtr<T>(*(source.Ptr));
	if(Ptr) Ptr->IncRef();
};

//---------------------------------------------------
template <typename T>
void HPtr<T>::UnInitialize(){

	if(Ptr) Ptr->DecRef();
	Ptr = NULL;
};

//---------------------------------------------------

template <typename T>
void HPtr<T>::Set(HPtr<T>& source){

	if(Ptr){
		Ptr->Set(source.Ptr);
	}else{
		(*this)=source;
	}

};

//---------------------------------------------------
template <typename T>
int HPtr<T>::Get() const{

	if(Ptr){
		return Ptr->Get();
	}else{
		return 0;
	}

};

//==============================================================================
template<class TValue>
class UVector{
	public:
		typedef std::vector<TValue> TVect;
		typedef bool (*TCompare)(TValue arg1, TValue arg2);
//		typedef UScreen<TValue>	WScreen;

		template<class TValue>
		struct TTemp{
			TValue		State;
			int			Num;
			UVector*	Parent;
			inline TTemp	operator=(const TValue& x){
				Parent->Set(Num,x);
				return *this;
			};
			inline operator TValue(){return State;};
			inline operator TValue*(){return &State;};
			inline TValue& operator->(){return State;};
		};

//		typedef TTemp<TValue>	WScreen;

		UVector();
//		UVector(int);
//		UVector(int,UVector<TKey>&);
		UVector(UVector<TValue>& source);

		__property unsigned Count		= {read = GetCount};
		__property unsigned MaxCount	= {read = GetMaxCount};
		__property bool		Bof			= {read = GetBof};
		__property bool		Eof			= {read = GetEof};
		__property bool		Empty		= {read = GetEmpty};
		__property TValue	Value		= {read = GetValue};
		__property TCompare Compare		= {read = fCompare, write = fCompare};
		__property bool		Sorted		= {read = fSorted, write = SetSorted};

		void 	__fastcall 	Clear();
		void 	__fastcall 	Add(TValue);
		void	__fastcall	AddForward(TValue);
		void	__fastcall	Insert(int,TValue);
		void	__fastcall	Set(int,TValue);
		void 	__fastcall 	Delete(int);
		void	__fastcall	Resize(int,const TValue&);
		void	__fastcall	Resize(int);

		void operator=(UVector<TValue>&);
		TValue& operator[](int);
		void	Sort();

		void	First();
		void	End();
		void	Next();
		void	Previous();

	protected:
		TTemp	            fScreen;
		TVect				fVector;
		TValue				fValue;
		TVect::iterator		iterator;
		TVect::iterator		Iterator;
		bool				fBof;
		bool				fEof;
		TCompare			fCompare;
		bool				fSorted;

		int	   				GetCount(void);
		bool				GetBof(void);
		bool    			GetEof(void);
		TValue				GetValue(void);
		bool				GetEmpty(void);
		unsigned			GetMaxCount(void);

		static bool		DefaultCompare(TValue arg1, TValue arg2);
		void			Swap(unsigned arg1, unsigned arg2);
		void			SetSorted(bool sorted);
};

//---------------------------------------------------
template<class TValue>
UVector<TValue>::UVector(){

	fScreen.Parent=this;
	Clear();
};

//---------------------------------------------------
template<class TValue>
UVector<TValue>::UVector(UVector<TValue>& source){

	*this=source;
};

//---------------------------------------------------
template<class TValue>
void 	__fastcall 	UVector<TValue>::Clear(){

	fVector.clear();
};

//---------------------------------------------------
template<class TValue>
void 	__fastcall 	UVector<TValue>::Add(TValue value){

	fVector.push_back(value);

};

//---------------------------------------------------
template<class TValue>
void	__fastcall	UVector<TValue>::AddForward(TValue value){

	Insert(0,value);
};

//---------------------------------------------------
template<class TValue>
void	__fastcall	UVector<TValue>::Insert(int num,TValue value){

	if(num < 0)	return;
	if(num >= fVector.size())	Resize(num);
	fVector.insert(fVector.begin()+num,value);

};

//---------------------------------------------------
template<class TValue>
void	__fastcall	UVector<TValue>::Set(int num,TValue value){

	if(num < 0)	return;
	if(num >= fVector.size())	Resize(num+1);
	fVector[num]=value;
};


//---------------------------------------------------
template<class TValue>
void 	__fastcall 	UVector<TValue>::Delete(int num){

	if((num < 0) || (num >= fVector.size()))	return;
	fVector.erase(fVector.begin()+num);
};

//---------------------------------------------------
template<class TValue>
void	__fastcall	UVector<TValue>::Resize(int num,const TValue& value){

	if(num < 0)	return;
	fVector.resize(num,value);
};

//---------------------------------------------------
template<class TValue>
void	__fastcall	UVector<TValue>::Resize(int num){

	if(num < 0)	return;
	fVector.resize(num);
};

//---------------------------------------------------
template<class TValue>
void UVector<TValue>::operator=(UVector<TValue>& source){

	if(&source == this) return;
	fVector.clear();
	fVector = source.fVector;
};

//---------------------------------------------------
template<class TValue>
TValue&  UVector<TValue>:: operator[](int index){

	if((index<0)||(index>=fVector.size()))	return fValue;
	TValue a = fVector[index];
	return fVector[index];

};

//--------------------------------------
template<class TValue>
void	UVector<TValue>::Sort(){

	TCompare		compare = NULL;
	if(fCompare)	compare = fCompare;
	else			compare	= DefaultCompare;

	unsigned count	= Vector.size();
	unsigned jump	= count;
	bool	swapped	= true;

	while((jump > 1)|| swapped){
		try{

			if(jump > 1)	jump	/= 1.24733;
			swapped	= false;
			for(unsigned i = 0; i + jump <count; i++)
				if(compare(Vector[i].Key, Vector[i+jump].Key)){
					Swap(i, i + jump);
					swapped = true;
				};
		}__finally{
		}
	}
};

//---------------------------------------------------
template<class TValue>
void	UVector<TValue>::First(){

	Iterator = fVector.begin();
	fBof = true;

	if(Iterator != fVector.end()){
		fValue = *Iterator;
		fEof = false;
	}else{
		fEof = true;
	}
};

//---------------------------------------------------
template<class TValue>
void	UVector<TValue>::End(){

	Iterator = fVector.end();
	Iterator--;

	if(Iterator != fVector.begin()) fBof = false;
	else	fBof = true;

	if(Iterator != fVector.end()){
		fEof = false;
		fValue = *Iterator;
	}else{
		fEof = true;
	}
};

//---------------------------------------------------
template<class TValue>
void	UVector<TValue>::Next(){

	if(Iterator != fVector.end()) Iterator++;

	if(Iterator != fVector.begin()) fBof = false;
	else	fBof = true;

	if(Iterator != fVector.end()){
		fValue = *Iterator;
		fEof = false;
	}else{
		fEof = true;
	}
};

//---------------------------------------------------
template<class TValue>
void	UVector<TValue>::Previous(){

	if(Iterator != fVector.begin()) Iterator--;

	if(Iterator != fVector.begin()) fBof=false;
	else	fBof = true;

	if(Iterator != fVector.end()){
		fValue = *Iterator;
		fEof = false;
	}else{
		fEof = true;
	}
};

//---------------------------------------------------
template<class TValue>
int		UVector<TValue>::GetCount(void){

	return	fVector.size();
};

//---------------------------------------------------
template<class TValue>
bool	UVector<TValue>::GetBof(void){

	return	fBof;
};

//---------------------------------------------------
template<class TValue>
bool	UVector<TValue>::GetEof(void){

	return	fEof;
};

//---------------------------------------------------
template<class TValue>
TValue	UVector<TValue>::GetValue(void){

	return fValue;
};

//---------------------------------------------------
template<class TValue>
bool				UVector<TValue>::GetEmpty(void){

	return fVector.empty();
};

//---------------------------------------------------
template<class TValue>
unsigned			UVector<TValue>::GetMaxCount(void){

//	return fVector.maxsize();
};

//------------------------------------------
template<class TValue>
bool		UVector<TValue>::DefaultCompare(TValue arg1, TValue arg2){

	return arg1 > arg2;
};

//------------------------------------------
template<class TValue>
void UVector<TValue>::Swap(unsigned arg1, unsigned arg2){

	int count	= fVector.size();
	if(arg1 >= count)	return;
	if(arg2 >= count)	return;

	TValue	item	= fVector[arg1];

	fVector[arg1]	= fVector[arg2];
	fVector[arg2]	= item;

//	Update();
};

//------------------------------------------
template<class TValue>
void 	UVector<TValue>::SetSorted(bool sorted){

	if(fSorted == sorted)	return;

	fSorted = sorted;
	if(fSorted){
		Sort();
	}
};
//==============================================================================
template<class TValue>
class HVector:public HPtr<UVector<TValue> >{
	public:
	HVector(bool init=false){if(init) Initialize();};
	HVector(int);
	HVector(int,const TValue&);
	void Initialize();
	void Initialize(int);
	void Initialize(int,const TValue&);


	/*UVector<TValue>::TTemp*/TValue& HVector::operator[](int);
};

//-------------------------------------------
template<class TValue>
HVector<TValue>::HVector(int count){

	Initialize();
	(*Ptr)->Resize(count);
}

//-------------------------------------------
template<class TValue>
HVector<TValue>::HVector(int count,const TValue& source){

	Initialize();
	(*Ptr)->Resize(count,source);
}

//-------------------------------------------
template<class TValue>
void HVector<TValue>::Initialize(){

	HPtr<UVector<TValue> >::Initialize();

}

//-------------------------------------------
template<class TValue>
void HVector<TValue>::Initialize(int count){

	Initialize();
	(*Ptr)->Resize(count);
}

//-------------------------------------------
template<class TValue>
void HVector<TValue>::Initialize(int count,const TValue& source){

	Initialize();
	(*Ptr)->Resize(count,source);
}
//-------------------------------------------
template<class TValue>
/*UVector<TValue>::TTemp*/TValue&	HVector<TValue>::operator[](int index){

	return (*Ptr)->operator[](index);

};

//==============================================================================
template<class TKey,class TValue>
struct SItem{
	TKey		Key;
	TValue 		Value;
	void operator=(SItem<TKey,TValue>);
};

//--------------------------------------
template<class TKey,class TValue>
void SItem<TKey, TValue>::operator=(SItem<TKey,TValue> item){

	Key		= item.Key;
	Value	= item.Value;
};
//==============================================================================
template<class T>
bool compare_function(T arg1, T arg2){

};
typedef HPtr<TStringList>	HList;
typedef HPtr<TMemoryStream>	HStream;
//==============================================================================
template<class TKey,class TValue>
class UMap{
		public:

		typedef map<TKey,unsigned> 	TMap;
		typedef SItem<TKey,TValue>  	TItem;
		typedef bool (*TCompare)(TKey arg1, TKey arg2);
		UMap();
		UMap(UMap& map);
		virtual ~UMap();

		__property unsigned Count	= {read = GetCount};
		__property bool		Bof		= {read = GetBof};
		__property bool		Eof		= {read = GetEof};
		__property TValue	Value	= {read = GetValue};
		__property TKey		Key		= {read = GetKey};
		__property TCompare Compare	= {read = fCompare, write = fCompare};
		__property bool		Sorted	= {read = fSorted, write = SetSorted};

		void 	__fastcall 	Clear();
		void 	__fastcall 	Add(TKey,TValue);
		void 	__fastcall 	Delete(TKey);
		void	__fastcall	Delete(HVector<TKey>);
		void	__fastcall	Delete(HList list);
		bool 	__fastcall	Find(TKey);
		void 	__fastcall 	Move(int pos, TKey key);
		void 	__fastcall 	Move(int pos, HVector<TKey>);
		void 	__fastcall 	Insert(int pos, String, TValue);
		int 	__fastcall	IndexOf(TKey key);
		void	__fastcall	Sort();
		void	__fastcall	BeginUpdate();
		void	__fastcall	EndUpdate();
		void	__fastcall	Update();

		TItem*  __fastcall  Get(unsigned index);

		const TValue 	operator[](TKey);
		void 			operator=(UMap&);

		TItem*			First();
		TItem*			End();
		TItem*			Next();
		TItem*			Previous();

	protected:
		TMap		   	Map;
		TItem			Item;
		vector<TItem>	Vector;

		vector<TItem>::iterator	iterator;
		vector<TItem>::iterator	Iterator;

		bool			fBof;
		bool			fEof;
		TCompare		fCompare;
		bool			fSorted;
		int				fUpdate;

		static bool		DefaultCompare(TKey arg1, TKey arg2);
		void			Swap(unsigned arg1, unsigned arg2);
		void			SetSorted(bool sorted);

		int	   			GetCount(void);
		bool			GetBof(void);
		bool    		GetEof(void);
		TValue  		GetValue(void);
		TKey    		GetKey(void);

	};
//--------------------------------------
template<class TKey,class TValue>
UMap<TKey,TValue>::UMap(){

	Clear();
	fCompare 	= NULL;
	fUpdate		= 0;
	fSorted		= false;
};

//--------------------------------------
template<class TKey,class TValue>
UMap<TKey,TValue>::UMap(UMap& source){

	*this=source;
};

//--------------------------------------
template<class TKey,class TValue>
UMap<TKey,TValue>::~UMap(){

	Clear();

};

//--------------------------------------
template<class TKey,class TValue>
void __fastcall UMap<TKey,TValue>::Clear(){

	Map.clear();
	Vector.clear();
};

//--------------------------------------
template<class TKey,class TValue>
void __fastcall UMap<TKey,TValue>::Add(TKey key,TValue val){

	if(Map.find(key) != Map.end()){

		Vector[Map[key]].Value	= val;
	}else{
		TItem item;
		item.Key	= key;
		item.Value	= val;
		int index	= 0;

		if(fSorted){

			if(fCompare){
				for(int i = 0; i < Vector.size(); i++){
					if(fCompare(Vector[i].Key, key)){
						index++;
						continue;
					}else	break;
				}
			}else{
				for(int i = 0; i < Vector.size(); i++){
					index = i;
					if(Vector[i].Key < key){
						index++;
						continue;
					}
					else	break;
				}
			}
			Vector.insert(Vector.begin() + index, item);
		}else{
			Vector.push_back(item);
			index = Vector.size() - 1;
        }

		Update();
	}


};

//--------------------------------------
template<class TKey,class TValue>
void __fastcall UMap<TKey,TValue>::Delete(TKey key){

	map<TKey, unsigned>::iterator it	= Map.find(key);
	if(it == Map.end()) return;

	unsigned index 	= Map[key];
	iterator 		= Vector.begin() + index;
	Vector.erase(iterator);
	Update();
};

//--------------------------------------
template<class TKey,class TValue>
void	__fastcall	UMap<TKey,TValue>::Delete(HVector<TKey> vec){

	HSet<unsigned> A(true);
	for(int i = 0; i < vec->Count; i++){
		A->Add(Map[vec[i]]);
	}
	vector<TItem>	buf;
	for(int i = Vector.size() - 1; i >= 0; i--){
		if(!A->Find(i)){
			buf.push_back(Vector[i]);
		}
	}
	Vector = buf;
	Update();

};

//--------------------------------------
template<class TKey,class TValue>
void	__fastcall	UMap<TKey,TValue>::Delete(HList list){

	HSet<unsigned> A(true);
	for(int i = 0; i < list->Count; i++){
		A->Add(Map[list->Strings[i]]);
	}
	vector<TItem>	buf;
	for(int i = Vector.size() - 1; i >= 0; i--){
		if(!A->Find(i)){
			buf.push_back(Vector[i]);
		}
	}
	Vector = buf;
	Update();

};

//--------------------------------------
template<class TKey,class TValue>
void	__fastcall	UMap<TKey,TValue>::Sort(){

	TCompare		compare = NULL;
	if(fCompare)	compare = fCompare;
	else			compare	= DefaultCompare;

	unsigned count	= Vector.size();
	unsigned jump	= count;
	bool	swapped	= true;

	BeginUpdate();
	while((jump > 1)|| swapped){
		try{

			if(jump > 1)	jump	/= 1.24733;
			swapped	= false;
			for(unsigned i = 0; i + jump <count; i++)
				if(compare(Vector[i].Key, Vector[i+jump].Key)){
					Swap(i, i + jump);
					swapped = true;
				};
		}__finally{
		}
	}
	EndUpdate();
};

//--------------------------------------
template<class TKey,class TValue>
void	__fastcall	UMap<TKey,TValue>::BeginUpdate(){

	fUpdate++;
};

//--------------------------------------
template<class TKey,class TValue>
void	__fastcall	UMap<TKey,TValue>::EndUpdate(){

	fUpdate--;
	if(fUpdate < 0)	fUpdate = 0;
	Update();
};

//--------------------------------------
template<class TKey,class TValue>
void	__fastcall	UMap<TKey,TValue>::Update(){

	if(fUpdate)	return;
	Map.clear();
	for(int i = 0; i < Vector.size(); i++){

		pair<TKey,unsigned> index(Vector[i].Key,i);
		Map.insert(index);
	}
};

//--------------------------------------
template<class TKey,class TValue>
const TValue UMap<TKey,TValue>::operator[](TKey key){

	map<TKey, unsigned>::iterator it = Map.find(key);

	if(it != Map.end()){
		return Vector[it->second].Value;
	}else
	return TValue();

};

//--------------------------------------
template<class TKey,class TValue>
void UMap<TKey,TValue>::operator=(UMap& source){

	if(&source == this) return;
	Map.clear();
	Vector.clear();

	Vector = source.Vector;
	Update();

};

//---------------------------------------
template<class TKey,class TValue>
SItem<TKey,TValue>*	UMap<TKey,TValue>::First(){

	Iterator = Vector.begin();
	fBof	= true;
	if(Iterator != Vector.end()){
		Item   = *Iterator;
		fEof	= false;
	}else{
		fEof	= true;
		return	NULL;
	}

	return &Item;

};

//----------------------------------------
template<class TKey,class TValue>
SItem<TKey,TValue>*	UMap<TKey,TValue>::End(){

	Iterator	= Vector.end();
	Iterator--;

	if(Iterator != Vector.begin()) fBof = false;
	else	fBof = true;

	if(Iterator != Vector.end()){
		Item = *Iterator;
		fEof = false;
	}else{
		fEof = true;
		return	NULL;
	}

	return &Item;

};

//----------------------------------------
template<class TKey,class TValue>
SItem<TKey,TValue>*	UMap<TKey,TValue>::Next(){

	if(Iterator != Vector.end()) Iterator++;

	if(Iterator != Vector.begin()) fBof	= false;
	else	fBof = true;

	if(Iterator != Vector.end()){
		Item = *Iterator;
		fEof = false;
	}else{
		fEof = true;
		return	NULL;
	}
	return &Item;

};

//-----------------------------------------
template<class TKey,class TValue>
SItem<TKey,TValue>*	UMap<TKey,TValue>::Previous(){

	if(Iterator != Vector.begin()) Iterator--;

	if(Iterator != Vector.begin()) fBof = false;
	else	fBof = true;

	if(Iterator != Vector.end()){
		Item = *Iterator;
		fEof = false;
	}else{
		fEof = true;
		return NULL;
	}

	return &Item;

};

//------------------------------------------
template<class TKey,class TValue>
bool __fastcall	UMap<TKey,TValue>::Find(TKey key){

	map<TKey, unsigned>::iterator it = Map.find(key);
	if(it != Map.end()) return true;
	else return false;

};

//------------------------------------------
template<class TKey,class TValue>
void 	__fastcall 	UMap<TKey,TValue>::Move(int pos, TKey key){

	if(fSorted)	return;

	map<TKey, unsigned>::iterator it = Map.find(key);
	if(it == Map.end())	return;

	vector<TItem>::iterator it1	= Vector.begin() + it->second;
	vector<TItem>::iterator it2	= Vector.begin() + pos;

	Vector.insert(it2, it1+1, it1+2);
	Vector.erase(it1+1);

	Update();

};

//------------------------------------------
template<class TKey,class TValue>
void 	__fastcall 	UMap<TKey,TValue>::Move(int pos, HVector<TKey> vec){

	if(fSorted)	return;
	if(pos >= Vector.size())	return;

	vector<TItem> buf;
	for(int i = 0; i < pos; i++)
		buf.push_back(vec[i]);

	HVector<unsigned> 	A(true);
	for(int i = 0; i < vec->Count; i++){
		A->Add(Map[vec[i]]);
	}

	HSet<unsigned>		B(true);
	for(int i = 0; i < A->Count; i++){
		unsigned t = A[i];
		if(!B->Find(t))	buf.push_back(vec[t]);
		B->Add(t);
	}

	for(int i = pos; i < Vector.size(); i++){
		if(!B->Find(i))	buf.push_back(vec[i]);
	}

};

//------------------------------------------
template<class TKey,class TValue>
void 	__fastcall 	UMap<TKey,TValue>::Insert(int pos, String key, TValue val){

	if(fSorted)	return;

	map<TKey, unsigned>::iterator it = Map.find(key);
	if(it != Map.end())	return;

	vector<TItem>::iterator it1	= Vector.begin() + pos;
	TItem item;
	item.Key	= key;
	item.Value	= val;

	Vector.insert(it1, item);

	Update();

};

//------------------------------------------
template<class TKey,class TValue>
int 	__fastcall	UMap<TKey,TValue>::IndexOf(TKey key){

	int result	= -1;

	map<TKey, unsigned>::iterator it = Map.find(key);
	if(it != Map.end())	return	-1;
	else				return Map[key];
};

//------------------------------------------
template<class TKey,class TValue>
UMap<TKey,TValue>::TItem* __fastcall	UMap<TKey,TValue>::Get(unsigned index){

	if(index < Vector.size()){
		Item = Vector[index];
		return &Item;
	}else return NULL;

};

//------------------------------------------
template<class TKey,class TValue>
bool		UMap<TKey,TValue>::DefaultCompare(TKey arg1, TKey arg2){

	return arg1 > arg2;
};

//------------------------------------------
template<class TKey,class TValue>
void UMap<TKey,TValue>::Swap(unsigned arg1, unsigned arg2){

	int count	= Vector.size();
	if(arg1 >= count)	return;
	if(arg2 >= count)	return;

	TItem	item	= Vector[arg1];

	Vector[arg1]	= Vector[arg2];
	Vector[arg2]	= item;

	Update();
};

//------------------------------------------
template<class TKey,class TValue>
void 	UMap<TKey,TValue>::SetSorted(bool sorted){

	if(fSorted == sorted)	return;

	fSorted = sorted;
	if(fSorted){
		Sort();
	}
};

//-------------------------------------------
template<class TKey,class TValue>
int	   	UMap<TKey,TValue>::GetCount(void){

	return	Map.size();
};

//-------------------------------------------
template<class TKey,class TValue>
bool	UMap<TKey,TValue>::GetBof(void){

	return	fBof;
};

//-------------------------------------------
template<class TKey,class TValue>
bool    UMap<TKey,TValue>::GetEof(void){

	return	fEof;
};

//-------------------------------------------
template<class TKey,class TValue>
TValue 	UMap<TKey,TValue>::GetValue(void){

	return Item.Value;
};

//-------------------------------------------
template<class TKey,class TValue>
TKey	UMap<TKey,TValue>::GetKey(void){

	return Item.Key;
};

//==============================================================================
template<class TKey,class TValue>
class HMap:public HPtr<UMap<TKey,TValue> >{
	public:
	HMap(bool init = false){if(init)	Initialize();};
	~HMap(){};
	TValue HMap::operator[](TKey	key);
};

//-------------------------------------------
template<class TKey,class TValue>
TValue	HMap<TKey,TValue>::operator[](TKey key){

	return (*Ptr)->operator[](key);

};

//===========================================================================
template<class TKey>
class USet{
	public:
		typedef set<TKey> TSet;

		USet(){};
		USet(USet& source);

		__property unsigned Count	= {read	= GetCount};
		__property bool		Bof		= {read	= GetBof};
		__property bool		Eof		= {read	= GetEof};
		__property TKey		Key		= {read	= GetKey};


		void 	__fastcall 	Clear();
		void 	__fastcall 	Add(TKey);
		void 	__fastcall 	Delete(TKey);
		bool 	__fastcall	Find(TKey);
		bool 	__fastcall	Set(TKey);


		void operator=(USet<TKey>&);
		TKey	GetNext(bool first);

		void	First();
		void	End();
		void	Next();
		void	Previous();

	protected:
		TSet				fSet;
		TKey				fKey;
		TSet::iterator		iterator;
		TSet::iterator		Iterator;
		bool				fBof;
		bool				fEof;
		int	   				GetCount(void);
		bool				GetBof(void);
		bool    			GetEof(void);
		TKey				GetKey(void);
	};

//-----------------------------------------
template<class TKey>
USet<TKey>::USet(USet& source){

	*this=source;
};
//-----------------------------------------
template<class TKey>
void __fastcall USet<TKey>::Clear(){

	fSet.clear();

};

//-----------------------------------------
template<class TKey>
void __fastcall USet<TKey>::Add(TKey key){

	fSet.insert(key);

};

//-----------------------------------------
template<class TKey>
void __fastcall USet<TKey>::Delete(TKey key){

	iterator = fSet.find(key);
	if(iterator != fSet.end()) fSet.erase(iterator);

};

//-----------------------------------------
template<class TKey>
bool __fastcall	USet<TKey>::Find(TKey key){

	iterator = fSet.find(key);
	if(iterator != fSet.end()) return true;
	else return false;

};

//-----------------------------------------
template<class TKey>
bool __fastcall	USet<TKey>::Set(TKey key){

	iterator = fSet.find(key);
	if(iterator != fSet.end()){
		Iterator=iterator;
		return true;
	}else return false;

};


//-----------------------------------------
template<class TKey>
void USet<TKey>::operator=(USet<TKey>& source){

	if(&source == this) return;
	fSet.clear();
	fSet = source.fSet;

};

//-----------------------------------------
template<class TKey>
TKey	USet<TKey>::GetNext(bool first){

	if(first) First();
	else	  Next();
	return Key;

};

//-----------------------------------------
template<class TKey>
void	USet<TKey>::First(){

	Iterator = fSet.begin();
	fBof = true;

	if(Iterator != fSet.end()){
		fKey = *Iterator;
		fEof = false;
	}else{
		fEof = true;
	}
};

//-----------------------------------------
template<class TKey>
void	USet<TKey>::End(){

	Iterator = fSet.end();
	Iterator--;

	if(Iterator != fSet.begin()) fBof = false;
	else	fBof = true;

	if(Iterator != fSet.end()){
		fKey = *Iterator;
		fEof = false;
	}else{
		fEof = true;
	}

};

//-----------------------------------------
template<class TKey>
void	USet<TKey>::Next(){

	if(Iterator != fSet.end()) Iterator++;

	if(Iterator != fSet.begin()) fBof = false;
	else	fBof = true;

	if(Iterator != fSet.end()){
		fKey = *Iterator;
		fEof = false;
	}else{
		fEof = true;
	}

};

//-----------------------------------------
template<class TKey>
void	USet<TKey>::Previous(){


	if(Iterator != fSet.begin()) Iterator--;

	if(Iterator != fSet.begin()) fBof=false;
	else	fBof = true;

	if(Iterator != fSet.end()){
		fKey = *Iterator;
		fEof = false;
	}else{
		fEof = true;
	}

};

//-----------------------------------------
template<class TKey>
int	   	USet<TKey>::GetCount(void){

	return	fSet.size();

};

//-----------------------------------------
template<class TKey>
bool	USet<TKey>::GetBof(void){

	return	fBof;

};

//-----------------------------------------
template<class TKey>
bool    USet<TKey>::GetEof(void){

	return	fEof;

};

//-----------------------------------------
template<class TKey>
TKey	USet<TKey>::GetKey(void){

	return	fKey;
};
/*
//===========================================================================
template<>
class USet<String>{
	public:
		typedef set<String,MyLess> TSet;

		USet(){};
		USet(USet& source);

		__property unsigned Count	= {read = GetCount};
		__property bool		Bof		= {read = GetBof};
		__property bool		Eof		= {read = GetEof};
		__property String	Key		= {read = GetKey};


		void 	__fastcall 	Clear();
		void 	__fastcall 	Add(String);
		void 	__fastcall 	Delete(String);
		bool 	__fastcall	Find(String);
		bool 	__fastcall	Set(String);


		void operator=(USet<String>&);
		String	Get(unsigned int index);

		void	First();
		void	End();
		void	Next();
		void	Previous();

	protected:
		TSet				fSet;
		String				fKey;
		TSet::iterator		iterator;
		TSet::iterator		Iterator;
		bool				fBof;
		bool				fEof;
		int	   				GetCount(void);
		bool				GetBof(void);
		bool    			GetEof(void);
		String				GetKey(void);
	};

//-----------------------------------------
USet<String>::USet(USet& source){

	*this=source;
};
//-----------------------------------------
void __fastcall USet<String>::Clear(){

	fSet.clear();

};

//-----------------------------------------
void __fastcall USet<String>::Add(String key){

	fSet.insert(key);

};

//-----------------------------------------
void __fastcall USet<String>::Delete(String key){

	iterator = fSet.find(key);
	if(iterator != fSet.end()) fSet.erase(iterator);

};

//-----------------------------------------
bool __fastcall	USet<String>::Find(String key){

	iterator = fSet.find(key);
	if(iterator != fSet.end()) return true;
	else return false;

};

//-----------------------------------------
bool __fastcall	USet<String>::Set(String key){

	iterator = fSet.find(key);
	if(iterator != fSet.end()){
		Iterator=iterator;
		return true;
	}else return false;

};


//-----------------------------------------
void USet<String>::operator=(USet<String>& source){

	if(&source == this) return;
	fSet.clear();
	fSet = source.fSet;

};

//-----------------------------------------
String	USet<String>::Get(unsigned int index){

	if(!index) fBof = true;

	Iterator = fSet.begin() + index;
	if(Iterator != fSet.end()){
		fKey = *Iterator;
		fEof = false;
	}else{
		fEof = true;
	}
};

//-----------------------------------------
void	USet<String>::First(){

	Iterator = fSet.begin();
	fBof = true;

	if(Iterator != fSet.end()){
		fKey = *Iterator;
		fEof = false;
	}else{
		fEof = true;
	}
};

//-----------------------------------------
void	USet<String>::End(){

	Iterator = fSet.end();
	Iterator--;

	if(Iterator != fSet.begin()) fBof = false;
	else	fBof = true;

	if(Iterator != fSet.end()){
		fKey = *Iterator;
		fEof = false;
	}else{
		fEof = true;
	}

};

//-----------------------------------------
void	USet<String>::Next(){

	if(Iterator != fSet.end()) Iterator++;

	if(Iterator != fSet.begin()) fBof = false;
	else	fBof = true;

	if(Iterator != fSet.end()){
		fKey = *Iterator;
		fEof = false;
	}else{
		fEof = true;
	}

};

//-----------------------------------------
void	USet<String>::Previous(){


	if(Iterator != fSet.begin()) Iterator--;

	if(Iterator != fSet.begin()) fBof=false;
	else	fBof = true;

	if(Iterator != fSet.end()){
		fKey = *Iterator;
		fEof = false;
	}else{
		fEof = true;
	}

};

//-----------------------------------------
int	   	USet<String>::GetCount(void){

	return	fSet.size();

};

//-----------------------------------------
bool	USet<String>::GetBof(void){

	return	fBof;

};

//-----------------------------------------
bool    USet<String>::GetEof(void){

	return	fEof;

};

//-----------------------------------------
String	USet<String>::GetKey(void){

	return	fKey;
};     */
//==============================================================================
template<class TKey>
class HSet:public HPtr<USet<TKey> >{

	public:
		HSet(bool init = false){if(init)	Initialize();};
		HSet(const HSet<TKey>& key):HPtr<USet<TKey> >(key){		};


};
//==============================================================================
template <class TKey,class TValue, class TParent>
class UScreen{
	private:
		TValue		State;
		TKey		Index;
		TParent		Parent;
		UScreen&	operator=(const TValue&	x);
		operator	TValue();
		TValue&		operator->();
};

//-----------------------------------------------
template <class TKey,class TValue, class TParent>
UScreen<TKey,TValue,TParent>&	UScreen<TKey,TValue,TParent>::operator=(const TValue&	value){

	Parent->Set(Index,value);
	return *this;
};

//-----------------------------------------------
template <class TKey,class TValue, class TParent>
UScreen<TKey,TValue,TParent>::operator	TValue(){

	return State;
};

//-----------------------------------------------
template <class TKey,class TValue, class TParent>
TValue&		UScreen<TKey,TValue,TParent>::operator->(){

	return State;
};

//==============================================================================
template<class TKey,class TValue>
class UMultiMap{
		public:

		typedef HSet<TValue>			TSet;
		typedef map<TKey,TSet> 		  	TMap;

		__property unsigned Count = {read=GetCount};
		__property bool		Bof   = {read=GetBof};
		__property bool		Eof   = {read=GetEof};
		__property TKey		Key   = {read=GetKey};
		__property TSet&	Value = {read=GetValue};

		UMultiMap();
		UMultiMap(UMultiMap&);
		~UMultiMap();

		void 	__fastcall 	Clear();
		void 	__fastcall 	Clear(TKey);
		void 	__fastcall 	Add(TKey);
		void 	__fastcall 	Add(TKey,TValue);
		void 	__fastcall 	Delete(TKey);
		void 	__fastcall 	Delete(TKey,TValue);

		bool __fastcall		Find(TKey);
		bool __fastcall 	Find(TKey,TValue);

		TSet& 	operator[](TKey);
		void 	operator=(UMultiMap&);


		TSet&			First();
		TSet&			End();
		TSet&			Next();
		TSet&			Previuos();
		int 			ValuesCount(TKey key);

	protected:
		TMap			Map;
		TKey			fKey;
		TSet			fSet;
		TMap::iterator	iterator;
		TMap::iterator	Iterator;
		bool			fBof;
		bool			fEof;
		int	   			GetCount(void);
		bool			GetBof(void);
		bool    		GetEof(void);
		TKey			GetKey(void);
		TSet&			GetValue(void);

	};

//------------------------------------------
template<class TKey,class TValue>
UMultiMap<TKey,TValue>::UMultiMap(){


};

//------------------------------------------
template<class TKey,class TValue>
UMultiMap<TKey,TValue>::UMultiMap(UMultiMap& map){

	*this=map;
};

//------------------------------------------
template<class TKey,class TValue>
UMultiMap<TKey,TValue>::~UMultiMap(){

	Clear();
};

//------------------------------------------
template<class TKey,class TValue>
void __fastcall UMultiMap<TKey,TValue>::Clear(){

//	First();
//	while(!Eof){
//		delete Value;
//		Next();
//	}
	Map.clear();

};

//------------------------------------------
template<class TKey,class TValue>
void __fastcall UMultiMap<TKey,TValue>::Clear(TKey key){

	if(Find(key))	(*this)[key]->Clear();
};

//------------------------------------------
template<class TKey,class TValue>
void __fastcall UMultiMap<TKey,TValue>::Add(TKey key){

	if(Find(key))  return;
	else{
		TSet s;
		s.Initialize();
		std::pair<TKey,TSet> item(key,s);
		Map.insert(item);
	}
};

//-----------------------------------------
template<class TKey,class TValue>
void __fastcall UMultiMap<TKey,TValue>::Add(TKey key,TValue value){

	if(Find(key))  (*this)[key]->Add(value);
	else{
		TSet s;
		s.Initialize();
		s->Add(value);
		std::pair<TKey,TSet> item(key,s);
		Map.insert(item);
	}
};

//-----------------------------------------
template<class TKey,class TValue>
void __fastcall UMultiMap<TKey,TValue>::Delete(TKey key){

	iterator = Map.find(key);

	if(iterator != Map.end()) {
	   Map.erase(iterator);
	}
};

//-----------------------------------------
template<class TKey,class TValue>
void __fastcall UMultiMap<TKey,TValue>::Delete(TKey key ,TValue value){

	iterator = Map.find(key);
	if(iterator != Map.end()) {
	   TSet s = (*this)[key];
	   if(s->Find(value))	s->Delete(value);
	}

};

//-----------------------------------------
template<class TKey,class TValue>
bool __fastcall	UMultiMap<TKey,TValue>::Find(TKey key){

	iterator = Map.find(key);

	if(iterator != Map.end()) return true;
	else return false;

};

//-----------------------------------------
template<class TKey,class TValue>
bool __fastcall UMultiMap<TKey,TValue>::Find(TKey key,TValue value){

	if(Find(key))
		if((*this)[key]->Find(value)) return true;
	return false;
};

//-----------------------------------------
template<class TKey,class TValue>
UMultiMap<TKey,TValue>::TSet& UMultiMap<TKey,TValue>::operator[](TKey key){

	iterator = Map.find(key);
	if(iterator != Map.end()){
		fSet = iterator->second;
	};
	return iterator->second;
};

//-----------------------------------------
template<class TKey,class TValue>
void UMultiMap<TKey,TValue>::operator=(UMultiMap& map){

	if(&map == this) return;
	Clear();

	for(iterator = map.Map.begin(); iterator != map.Map.end(); iterator++){
		TSet	s;
		s.Initialize(iterator->second);
		pair<TKey,TSet> item(iterator->first,s);
		Map.insert(item);
	}
};

//-----------------------------------------
template<class TKey,class TValue>
UMultiMap<TKey,TValue>::TSet&	UMultiMap<TKey,TValue>::First(){

	Iterator = Map.begin();
	fBof=true;

	if(Iterator != Map.end()){
		fKey = Iterator->first;
		fSet = Iterator->second;
		fEof = false;
	}else{
		fEof = true;
		return Iterator->second;
	}

	return fSet;
};

//-------------------------------------------
template<class TKey,class TValue>
UMultiMap<TKey,TValue>::TSet&	UMultiMap<TKey,TValue>::End(){

	Iterator = Map.end();
	Iterator--;

	if(Iterator != Map.begin()) fBof = false;
	else	fBof=true;

	if(Iterator != Map.end()){
		fKey = Iterator->first;
		fSet = Iterator->second;
		fEof = false;
	}else{
		fEof = true;
		return	Iterator->second;
	}

	return fSet;
};

//-------------------------------------------
template<class TKey,class TValue>
UMultiMap<TKey,TValue>::TSet&	UMultiMap<TKey,TValue>::Next(){

	if(Iterator != Map.end()) Iterator++;

	if(Iterator != Map.begin()) fBof = false;
	else	fBof = true;

	if(Iterator != Map.end()){
		fKey = Iterator->first;
		fSet = Iterator->second;
		fEof = false;
	}else{
		fEof = true;
		return	Iterator->second;
	}
	return fSet;
};

//--------------------------------------------
template<class TKey,class TValue>
UMultiMap<TKey,TValue>::TSet&	UMultiMap<TKey,TValue>::Previuos(){

	if(Iterator != Map.begin()) Iterator--;

	if(Iterator != Map.begin()) fBof = false;
	else	fBof = true;

	if(Iterator != Map.end()){
		fKey = Iterator->first;
		fSet = Iterator->second;
		fEof = false;
	}else{
		fEof = true;
		return Iterator->second;
	}

	return fSet;
};

//-------------------------------------------
template<class TKey,class TValue>
int	   	UMultiMap<TKey,TValue>::ValuesCount(TKey key){

	if(Find(key)) return (*this)[key]->Count;
	return 0;
};

//-------------------------------------------
template<class TKey,class TValue>
int	   	UMultiMap<TKey,TValue>::GetCount(void){

	return	Map.size();
};

//-------------------------------------------
template<class TKey,class TValue>
bool	UMultiMap<TKey,TValue>::GetBof(void){

	return fBof;
};

//-------------------------------------------
template<class TKey,class TValue>
bool    UMultiMap<TKey,TValue>::GetEof(void){

	return fEof;
}

//-------------------------------------------
template<class TKey,class TValue>
TKey	UMultiMap<TKey,TValue>::GetKey(void){

	return fKey;

};

//-------------------------------------------
template<class TKey,class TValue>
UMultiMap<TKey,TValue>::TSet&	UMultiMap<TKey,TValue>::GetValue(void){

	return fSet;

};

//==============================================================================
template<class TValue>
class UMultiMap<String, TValue>{
		public:

		typedef HSet<TValue>			TSet;
		typedef map<String,TSet,MyLess> 	TMap;

		__property unsigned Count = {read=GetCount};
		__property bool		Bof   = {read=GetBof};
		__property bool		Eof   = {read=GetEof};
		__property String	Key   = {read=GetKey};
		__property TSet&	Value = {read=GetValue};

		UMultiMap();
		UMultiMap(UMultiMap&);
		~UMultiMap();

		void 	__fastcall 	Clear();
		void 	__fastcall 	Clear(String);
		void 	__fastcall 	Add(String);
		void 	__fastcall 	Add(String,TValue);
		void 	__fastcall 	Delete(String);
		void 	__fastcall 	Delete(String,TValue);

		bool __fastcall		Find(String);
		bool __fastcall 	Find(String,TValue);

		TSet& 	operator[](String);
		void 	operator=(UMultiMap&);


		TSet&			First();
		TSet&			End();
		TSet&			Next();
		TSet&			Previuos();
		int 			ValuesCount(String key);

	protected:
		TMap			Map;
		String			fKey;
		TSet			fSet;
		TMap::iterator	iterator;
		TMap::iterator	Iterator;
		bool			fBof;
		bool			fEof;
		int	   			GetCount(void);
		bool			GetBof(void);
		bool    		GetEof(void);
		String			GetKey(void);
		TSet&			GetValue(void);

	};

//------------------------------------------
template<class TValue>
UMultiMap<String,TValue>::UMultiMap(){


};

//------------------------------------------
template<class TValue>
UMultiMap<String,TValue>::UMultiMap(UMultiMap& map){

	*this=map;
};

//------------------------------------------
template<class TValue>
UMultiMap<String,TValue>::~UMultiMap(){

	Clear();
};

//------------------------------------------
template<class TValue>
void __fastcall UMultiMap<String,TValue>::Clear(){

//	First();
//	while(!Eof){
//		delete Value;
//		Next();
//	}
	Map.clear();

};

//------------------------------------------
template<class TValue>
void __fastcall UMultiMap<String,TValue>::Clear(String key){

	if(Find(key))	(*this)[key]->Clear();
};

//------------------------------------------
template<class TValue>
void __fastcall UMultiMap<String,TValue>::Add(String key){

	if(Find(key))  return;
	else{
		TSet s;
		s.Initialize();
		std::pair<String,TSet> item(key,s);
		Map.insert(item);
	}
};

//-----------------------------------------
template<class TValue>
void __fastcall UMultiMap<String,TValue>::Add(String key,TValue value){

	if(Find(key))  (*this)[key]->Add(value);
	else{
		TSet s;
		s.Initialize();
		s->Add(value);
		std::pair<String,TSet> item(key,s);
		Map.insert(item);
	}
};

//-----------------------------------------
template<class TValue>
void __fastcall UMultiMap<String,TValue>::Delete(String key){

	iterator = Map.find(key);

	if(iterator != Map.end()) {
	   Map.erase(iterator);
	}
};

//-----------------------------------------
template<class TValue>
void __fastcall UMultiMap<String,TValue>::Delete(String key ,TValue value){

	iterator = Map.find(key);
	if(iterator != Map.end()) {
	   TSet s = (*this)[key];
	   if(s->Find(value))	s->Delete(value);
	}

};

//-----------------------------------------
template<class TValue>
bool __fastcall	UMultiMap<String,TValue>::Find(String key){

	iterator = Map.find(key);

	if(iterator != Map.end()) return true;
	else return false;

};

//-----------------------------------------
template<class TValue>
bool __fastcall UMultiMap<String,TValue>::Find(String key,TValue value){

	if(Find(key))
		if((*this)[key]->Find(value)) return true;
	return false;
};

//-----------------------------------------
template<class TValue>
UMultiMap<String,TValue>::TSet& UMultiMap<String,TValue>::operator[](String key){

	iterator = Map.find(key);
	if(iterator != Map.end()){
		fSet = iterator->second;
	};
	return iterator->second;
};

//-----------------------------------------
template<class TValue>
void UMultiMap<String,TValue>::operator=(UMultiMap& map){

	if(&map == this) return;
	Clear();

	for(iterator = map.Map.begin(); iterator != map.Map.end(); iterator++){
		TSet	s;
		s.Initialize(iterator->second);
		pair<String,TSet> item(iterator->first,s);
		Map.insert(item);
	}
};

//-----------------------------------------
template<class TValue>
UMultiMap<String,TValue>::TSet&	UMultiMap<String,TValue>::First(){

	Iterator = Map.begin();
	fBof=true;

	if(Iterator != Map.end()){
		fKey = Iterator->first;
		fSet = Iterator->second;
		fEof = false;
	}else{
		fEof = true;
		return Iterator->second;
	}

	return fSet;
};

//-------------------------------------------
template<class TValue>
UMultiMap<String,TValue>::TSet&	UMultiMap<String,TValue>::End(){

	Iterator = Map.end();
	Iterator--;

	if(Iterator != Map.begin()) fBof = false;
	else	fBof=true;

	if(Iterator != Map.end()){
		fKey = Iterator->first;
		fSet = Iterator->second;
		fEof = false;
	}else{
		fEof = true;
		return	Iterator->second;
	}

	return fSet;
};

//-------------------------------------------
template<class TValue>
UMultiMap<String,TValue>::TSet&	UMultiMap<String,TValue>::Next(){

	if(Iterator != Map.end()) Iterator++;

	if(Iterator != Map.begin()) fBof = false;
	else	fBof = true;

	if(Iterator != Map.end()){
		fKey = Iterator->first;
		fSet = Iterator->second;
		fEof = false;
	}else{
		fEof = true;
		return	Iterator->second;
	}
	return fSet;
};

//--------------------------------------------
template<class TValue>
UMultiMap<String,TValue>::TSet&	UMultiMap<String,TValue>::Previuos(){

	if(Iterator != Map.begin()) Iterator--;

	if(Iterator != Map.begin()) fBof = false;
	else	fBof = true;

	if(Iterator != Map.end()){
		fKey = Iterator->first;
		fSet = Iterator->second;
		fEof = false;
	}else{
		fEof = true;
		return Iterator->second;
	}

	return fSet;
};

//-------------------------------------------
template<class TValue>
int	   	UMultiMap<String,TValue>::ValuesCount(String key){

	if(Find(key)) return (*this)[key]->Count;
	return 0;
};

//-------------------------------------------
template<class TValue>
int	   	UMultiMap<String,TValue>::GetCount(void){

	return	Map.size();
};

//-------------------------------------------
template<class TValue>
bool	UMultiMap<String,TValue>::GetBof(void){

	return fBof;
};

//-------------------------------------------
template<class TValue>
bool    UMultiMap<String,TValue>::GetEof(void){

	return fEof;
}

//-------------------------------------------
template<class TValue>
String	UMultiMap<String,TValue>::GetKey(void){

	return fKey;

};

//-------------------------------------------
template<class TValue>
UMultiMap<String,TValue>::TSet&	UMultiMap<String,TValue>::GetValue(void){

	return fSet;

};

//==============================================================================
template<class TKey,class TValue>
class HMultiMap:public HPtr<UMultiMap<TKey,TValue> >{
	public:
	HMultiMap(bool init = false){if(init)	Initialize();};
	HSet<TValue>& operator[](TKey	key);
};

//-------------------------------------------
template<class TKey,class TValue>
HSet<TValue>&	HMultiMap<TKey,TValue>::operator[](TKey key){

	return (*Ptr)->operator[](key);

};

//==============================================================================
template<class TKey1,class TKey2 ,class TValue>
class UMapX2{
		public:

		typedef HMap<TKey1, TValue>				TSet;
		typedef map<TKey1,HMap<TKey2,TValue> > 	TMap;

		__property unsigned Count = {read=GetCount};
		__property bool		Bof   = {read=GetBof};
		__property bool		Eof   = {read=GetEof};
		__property TKey1	Key   = {read=GetKey};
		__property TSet&	Value = {read=GetValue};

		UMapX2();
		UMapX2(UMapX2&);
		~UMapX2();

		void 	__fastcall 	Clear();
		void 	__fastcall 	Clear(TKey1);
		void 	__fastcall 	Add(TKey1);
		void 	__fastcall 	Add(TKey1,TKey2,TValue);
		void 	__fastcall 	Delete(TKey1);
		void	__fastcall	Delete(TKey1,TKey2);

		bool __fastcall		Find(TKey1);
		bool __fastcall		Find(TKey1,TKey2);

		TSet& 	operator[](TKey1);
		void 	operator=(UMapX2&);


		TSet&			First();
		TSet&			End();
		TSet&			Next();
		TSet&			Previous();
		int 			ValuesCount(TKey1 key);

	protected:
		TMap			Map;
		TKey1			fKey;
		TSet			fSet;
		TMap::iterator	iterator;
		TMap::iterator	Iterator;
		bool			fBof;
		bool			fEof;
		int	   			GetCount(void);
		bool			GetBof(void);
		bool    		GetEof(void);
		TKey1			GetKey(void);
		TSet&			GetValue(void);

	};

//------------------------------------------
template<class TKey1,class TKey2 ,class TValue>
UMapX2<TKey1,TKey2,TValue>::UMapX2(){


};

//------------------------------------------
template<class TKey1,class TKey2 ,class TValue>
UMapX2<TKey1,TKey2,TValue>::UMapX2(UMapX2& map){

	*this=map;
};

//------------------------------------------
template<class TKey1,class TKey2 ,class TValue>
UMapX2<TKey1,TKey2,TValue>::~UMapX2(){

	Clear();
};

//------------------------------------------
template<class TKey1,class TKey2 ,class TValue>
void __fastcall UMapX2<TKey1,TKey2,TValue>::Clear(){

	Map.clear();

};

//------------------------------------------
template<class TKey1,class TKey2 ,class TValue>
void __fastcall UMapX2<TKey1,TKey2,TValue>::Clear(TKey1 key){

	if(Find(key))	(*this)[key]->Clear();
};

//------------------------------------------
template<class TKey1,class TKey2 ,class TValue>
void __fastcall UMapX2<TKey1,TKey2,TValue>::Add(TKey1 key){

	if(Find(key))  return;
	else{
		TSet s;
		s.Initialize();
		std::pair<TKey1,TSet> item(key,s);
		Map.insert(item);
	}
};

//-----------------------------------------
template<class TKey1,class TKey2 ,class TValue>
void __fastcall UMapX2<TKey1,TKey2,TValue>::Add(TKey1 key1,TKey2 key2,TValue value){

	if(Find(key1)){
		 (*this)[key1]->Add(key2,value);
	}
	else{
		TSet s;
		s.Initialize();
		s->Add(key2,value);
		std::pair<TKey1,TSet> item(key,s);
		Map.insert(item);
	}
};

//-----------------------------------------
template<class TKey1,class TKey2 ,class TValue>
void __fastcall UMapX2<TKey1,TKey2,TValue>::Delete(TKey1 key){

	iterator = Map.find(key);

	if(iterator != Map.end()) {
	   Map.erase(iterator);
	}
};

//-----------------------------------------
template<class TKey1,class TKey2 ,class TValue>
void __fastcall UMapX2<TKey1,TKey2,TValue>::Delete(TKey1 key1 ,TKey2 key2){

	iterator = Map.find(key1);

	if(iterator != Map.end()) {
	   TSet s = (*this)[key1];
	   if(s->Find(key2))	s->Delete(key2);
	}

};

//-----------------------------------------
template<class TKey1,class TKey2 ,class TValue>
bool __fastcall	UMapX2<TKey1,TKey2,TValue>::Find(TKey1 key){

	iterator = Map.find(key);

	if(iterator != Map.end()) return true;
	else return false;

};

//-----------------------------------------
template<class TKey1,class TKey2 ,class TValue>
bool __fastcall UMapX2<TKey1,TKey2,TValue>::Find(TKey1 key1,TKey2 key2){

	if(Find(key1))
		if((*this)[key1]->Find(key2)) return true;
	return false;
};

//-----------------------------------------
template<class TKey1,class TKey2 ,class TValue>
UMapX2<TKey1,TKey2,TValue>::TSet& UMapX2<TKey1,TKey2,TValue>::operator[](TKey1 key){

	iterator = Map.find(key);
	if(iterator != Map.end()){
		fSet = iterator->second;
	};
	return iterator->second;
};

//-----------------------------------------
template<class TKey1,class TKey2 ,class TValue>
void UMapX2<TKey1,TKey2,TValue>::operator=(UMapX2& map){

	if(&map == this) return;
	Clear();

	for(iterator = map.Map.begin(); iterator != map.Map.end(); iterator++){
		TSet	s;
		s.Initialize(iterator->second);
		pair<TKey,TSet> item(iterator->first,s);
		Map.insert(item);
	}
};

//-----------------------------------------
template<class TKey1,class TKey2 ,class TValue>
UMapX2<TKey1,TKey2,TValue>::TSet&	UMapX2<TKey1,TKey2,TValue>::First(){

	Iterator = Map.begin();
	fBof=true;

	if(Iterator != Map.end()){
		fKey = Iterator->first;
		fSet = Iterator->second;
		fEof = false;
	}else{
		fEof = true;
		return Iterator->second;
	}

	return fSet;
};

//-------------------------------------------
template<class TKey1,class TKey2 ,class TValue>
UMapX2<TKey1,TKey2,TValue>::TSet&	UMapX2<TKey1,TKey2,TValue>::End(){

	Iterator = Map.end();
	Iterator--;

	if(Iterator != Map.begin()) fBof = false;
	else	fBof=true;

	if(Iterator != Map.end()){
		fKey = Iterator->first;
		fSet = Iterator->second;
		fEof = false;
	}else{
		fEof = true;
		return	Iterator->second;
	}

	return fSet;
};

//-------------------------------------------
template<class TKey1,class TKey2 ,class TValue>
UMapX2<TKey1,TKey2,TValue>::TSet&	UMapX2<TKey1,TKey2,TValue>::Next(){

	if(Iterator != Map.end()) Iterator++;

	if(Iterator != Map.begin()) fBof = false;
	else	fBof = true;

	if(Iterator != Map.end()){
		fKey = Iterator->first;
		fSet = Iterator->second;
		fEof = false;
	}else{
		fEof = true;
		return	Iterator->second;
	}
	return fSet;
};

//--------------------------------------------
template<class TKey1,class TKey2 ,class TValue>
UMapX2<TKey1,TKey2,TValue>::TSet&	UMapX2<TKey1,TKey2,TValue>::Previous(){

	if(Iterator != Map.begin()) Iterator--;

	if(Iterator != Map.begin()) fBof = false;
	else	fBof = true;

	if(Iterator != Map.end()){
		fKey = Iterator->first;
		fSet = Iterator->second;
		fEof = false;
	}else{
		fEof = true;
		return Iterator->second;
	}

	return fSet;
};

//-------------------------------------------
template<class TKey1,class TKey2 ,class TValue>
int	   	UMapX2<TKey1,TKey2,TValue>::ValuesCount(TKey1 key){

	if(Find(key)) return (*this)[key]->Count;
	return 0;
};

//-------------------------------------------
template<class TKey1,class TKey2 ,class TValue>
int	   	UMapX2<TKey1,TKey2,TValue>::GetCount(void){

	return	Map.size();
};

//-------------------------------------------
template<class TKey1,class TKey2 ,class TValue>
bool	UMapX2<TKey1,TKey2,TValue>::GetBof(void){

	return fBof;
};

//-------------------------------------------
template<class TKey1,class TKey2 ,class TValue>
bool    UMapX2<TKey1,TKey2,TValue>::GetEof(void){

	return fEof;
}

//-------------------------------------------
template<class TKey1,class TKey2 ,class TValue>
TKey1	UMapX2<TKey1,TKey2,TValue>::GetKey(void){

	return fKey;

};

//-------------------------------------------
template<class TKey1,class TKey2 ,class TValue>
UMapX2<TKey1,TKey2,TValue>::TSet&	UMapX2<TKey1,TKey2,TValue>::GetValue(void){

	return fSet;

};

//==============================================================================
/*
template<class TKey1,class TKey2 ,class TValue>
class HMultiMap:public HPtr<UMultiMap<TKey,TValue> >{
	public:
	HSet<TValue>& operator[](TKey	key);
};

//-------------------------------------------
template<class TKey1,class TKey2 ,class TValue>
HSet<TValue>&	HMultiMap<TKey,TValue>::operator[](TKey key){

	return (**Ptr)[key];

};
*/
/*
//==============================================================================
template<>
class HPtr<UMap<class TKey,class TValue> >{

	public:
	TValue HPtr<UMap<TKey,TValue> >::operator[](TKey);
};

//-------------------------------------------
template<>
TValue HPtr<UMap<class TKey,class TValue> >::operator[](UMap::TKey key){

	return UMap[key];
};
*/
//==============================================================================
template <typename T>
class Builder{
	public:
	virtual  T Create(void){};
	virtual void Close(T){};

};

//==============================================================================

template <typename T>
class BuildPtr{
	private:
		int Count;

	protected:
		T	Ptr;
		Builder<T>*	Build;
	public:
		BuildPtr(Builder<T>* build);
		BuildPtr(const BuildPtr<T>&);
		BuildPtr(const T&);
		BuildPtr<T>&	operator=(const BuildPtr<T>&);
		T	operator->();
		operator	T();
		void	Set(BuildPtr<T>*);
		void	IncRef();
		void	DecRef();
		int		GetCount();
		virtual	~BuildPtr();

};

//---------------------------------------------------
template <typename T>
inline BuildPtr<T>::BuildPtr(Builder<T>* build){

	Build = NULL;
	if(!build) return;
	Build = build;
	try{
		Ptr=Build->Create();
	}catch(...){
		Build = NULL;
	}
	Count=0;
};


//---------------------------------------------------
template <typename T>
inline BuildPtr<T>::BuildPtr(const BuildPtr<T>& source){

	if(source.Ptr == NULL)
		if(!Build){
			try{
				Ptr = Build->Create();
			}catch(...){
				Build = NULL;
			}

		}
	else
		if(!source.Build){
			try{
				Ptr = source.Build->Create();
			}catch(...){

			}
		}
	Count=0;
};

//---------------------------------------------------
template <typename T>
inline BuildPtr<T>::~BuildPtr(){

	try{
		Build->Close(Ptr);
		Build = NULL;
	}catch(...){
	}

};

//---------------------------------------------------
template <typename T>
T	BuildPtr<T>::operator->(){

	return Ptr;
};

//---------------------------------------------------
template <typename T>
BuildPtr<T>::operator	T(){

	return Ptr;
};

//---------------------------------------------------
template <typename T>
void	BuildPtr<T>::IncRef(){

	Count++;
};

//---------------------------------------------------
template <typename T>
void	BuildPtr<T>::DecRef(){

	Count--;
	if(!Count){
		delete	this;
	}
};

//---------------------------------------------------
template <typename T>
int	BuildPtr<T>::GetCount(){

	return Count;
};
//---------------------------------------------------
template <typename T>
void	BuildPtr<T>::Set(BuildPtr<T>* ptr){

	if(!ptr)	return;
	if(Ptr){
		if(Build) Build->Close(Ptr);
		else delete Ptr;
		Ptr = ptr->Ptr;
		Build = ptr->Build;
		ptr->Ptr = NULL;
//		Count += ptr->Count;
//		ptr->IncRef();
	}else{
		Ptr = ptr->Ptr;
		Build = ptr->Build;
		ptr->Ptr = NULL;
//		Count += ptr->Count;
//		IncRef();
	}
};


/**/

//==============================================================================
template <typename T>
class NPtr{
	protected:
		mutable BuildPtr<T>*	Ptr;
		Builder<T>*				Build;
		bool					Strong;
	public:
		NPtr(bool weaked = true);
		NPtr(Builder<T>* build);
//		NPtr(int){Initialize()};
		NPtr(const NPtr<T>&);
		NPtr<T>&	operator=(const NPtr<T>& );
		bool operator==(NPtr<T>& source);

		T	operator->();
		operator	T();
		virtual	~NPtr();
		void Initialize();
		void Initialize(Builder<T>* build);
		void UnInitialize();
		void Set(NPtr<T>&);
		void SetStrong(bool strong);
		int  GetStrong();
		int GetCount();
};

//---------------------------------------------------
template <typename T>
inline NPtr<T>::NPtr(bool strong){

	Ptr 	= NULL;
	Build 	= NULL;
	Strong 	= strong;
};

//---------------------------------------------------
template <typename T>
inline NPtr<T>::NPtr(Builder<T>* build){

	Ptr 	= NULL;
	Build 	= build;
	Strong 	= true;
};

//---------------------------------------------------
template <typename T>
inline NPtr<T>::NPtr(const NPtr<T>& source){

	Ptr 	= source.Ptr;
	Build 	= source.Build;
	Strong = true;
	if(Ptr)	Ptr->IncRef();

};

//---------------------------------------------------
template <typename T>
inline NPtr<T>::~NPtr(){

	UnInitialize();

};

//---------------------------------------------------
template <typename T>
NPtr<T>&	NPtr<T>::operator=(const NPtr<T>& source){

	if(&source == this) return *this;
	if(Ptr)
		if(Strong)
			Ptr->DecRef();
	Ptr = source.Ptr;
	Build = source.Build;
	if(Ptr)
		if(Strong)
			Ptr->IncRef();

	return *this;
};

//---------------------------------------------------
template <typename T>
bool NPtr<T>::operator==(NPtr<T>& source){

	if(this->Ptr == source.Ptr)	return true;
	else return false;
};

//---------------------------------------------------
template <typename T>
T	NPtr<T>::operator->(){

	return (T)*Ptr;
};

//---------------------------------------------------
template <typename T>
NPtr<T>::operator	T(){

	if(Ptr)	return *Ptr;
	else return NULL;
};

//---------------------------------------------------
template <typename T>
void NPtr<T>::Initialize(){

	if(Strong){
		if(Ptr) Ptr->DecRef();
		Ptr = NULL;
		if(Build){
			Ptr = new	BuildPtr<T>(Build);
			if(Ptr) Ptr->IncRef();
		}
	}
};

//---------------------------------------------------
template <typename T>
void NPtr<T>::Initialize(Builder<T>* build){

	if(build) Build = build;
	if(Strong){
		if(Ptr) Ptr->DecRef();
		Ptr = NULL;
		if(build){
			Build = build;
			Ptr = new	BuildPtr<T>(Build);
			if(Ptr) Ptr->IncRef();
		}
	}
};

//---------------------------------------------------
template <typename T>
void NPtr<T>::UnInitialize(){

	if(Ptr)
		if(Strong)
			Ptr->DecRef();
	Ptr = NULL;
};

//---------------------------------------------------
template <typename T>
int NPtr<T>::GetCount(){

	return Ptr->GetCount();
};

//---------------------------------------------------
 template <typename T>
void NPtr<T>::Set(NPtr<T>& source){

	if(Ptr){
		Ptr->Set(source.Ptr);
	}else{
		(*this)=source;
	}

};

//---------------------------------------------------
 template <typename T>
void NPtr<T>::SetStrong(bool strong){

	if(strong){
		if(!Strong){
			Strong = strong;
			if(Ptr) Ptr->IncRef();
		}
	}else{
		if(Strong){
			Strong = strong;
			if(Ptr) Ptr->DecRef();
		}
	}

};

//---------------------------------------------------
 template <typename T>
int  NPtr<T>::GetStrong(){

	return Strong;
};

#endif
