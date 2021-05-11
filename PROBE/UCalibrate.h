//---------------------------------------------------------------------------

#ifndef UCalibrateH
#define UCalibrateH

#include "Definition.h"
#include "Templates.h"
#include "ULog.h"
#include "UData.h"
#include "USignals.h"
#include "UAnalizator.h"
//---------------------------------------------------------------------------
class Calibrate{

public:
	Calibrate();
	~Calibrate();

	void	__fastcall table_create();
	void	__fastcall table_close();

	void	__fastcall table_add_12v(u8 channel, i32 input_volt, i32 code);
	void	__fastcall table_add_27v(u8 channel, i32 input_volt, i32 code);
	i32		__fastcall volt_to_code_12v(i32 volt);             //1 - 10 mV
	i32		__fastcall volt_to_code_27v(i32 volt);             //1 - 10 mV

	void	__fastcall save_to_file(String filename);
	void	__fastcall load_from_file(String filename);

	vector<pair<i32, i32> > __fastcall get_vector(u8 mode);

private:

	std::map<i32, i32 >				_v12l;
	std::map<i32, i32 >				_v12h;

	std::map<i32, i32 >  			_v27l;
	std::map<i32, i32 >  			_v27h;

	std::map<i32, pair<i32, i32> >	_v12;
	std::map<i32, pair<i32, i32> >  _v27;

    void	__fastcall	initialize_tables();
	void	__fastcall	fill_12v();
	void	__fastcall	fill_27v();
	void	__fastcall message(String info);

};










#endif
