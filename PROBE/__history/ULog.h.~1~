//---------------------------------------------------------------------------

#ifndef ULogH
#define ULogH
#include "USignals.h"

//---------------------------------------------------------------------------
namespace ACTION{

	enum{
		CREATE_LINE 	= 10,
		CREATE_DIVIDER 	= 11,
		CREATE_WIRE		= 12,
		CREATE_GRID		= 13,
		CREATE_MARKER	= 14,
		CREATE_PEG		= 15,
		CREATE_GROUP	= 16,
		CREATE_INTERVAL	= 17,

		CLOSE_LINE 		= 30,
		CLOSE_DIVIDER 	= 31,
		CLOSE_WIRE		= 32,
		CLOSE_GRID		= 33,
		CLOSE_MARKER	= 34,
		CLOSE_PEG		= 35,
		CLOSE_GROUP		= 36,
		CLOSE_INTERVAL	= 37,

		CHANGE_CLOCK_COUNT	= 50,
		CHANGE_LINE			= 51,
		CHANGE_LINE_POINTS	= 52,
		CHANGE_WIRE			= 53,
		CHANGE_GRID         = 54,
		CHANGE_MARKER		= 55,
		CHANGE_PEG			= 56,
		CHANGE_GROUP		= 57,
		CHANGE_INTERVAL		= 58,
		MOVED				= 59,
		ADD_TO_WIRE			= 60,
		REMOVE_FROM_WIRE	= 61

	};

};
class Endl{};
const Endl* endl	= NULL;
//==============================================================================
class Log{

public:
	Log();
	~Log();
	void	__fastcall init();
	void	__fastcall close();

	Log& operator<<(String message);
	Log& operator<<(const Endl* pointer);
private:

	bool	_init;
	String 	_data;
};
#endif
