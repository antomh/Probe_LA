//---------------------------------------------------------------------------
#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include "Probe.h"
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <sstream>
//---------------------------------------------------------------------------
class TFormTestSerial : public TForm
{
__published:	// IDE-managed Components
	TBitBtn *UpdateSerialList;
	TListBox *ListBox_COM_Ports;
	TLabel *Label1;
	TBitBtn *BitBtnConnect;
	TComboBox *ComboBoxBaudRate;
	TGroupBox *GroupBoxDevice;
	TButton *ButtonGetStatus;
	TStatusBar *StatusBar1;
	TCheckBox *CheckBoxRelay;
	TLabel *Label5;
	TLabel *Label6;
	TEdit *EditADC;
	TLabel *Label7;
	TButton *ButtonGetADC;
	TLabel *Label2;
	TEdit *EditDeviceID;
	TButton *ButtonGetDeviceID;
	TPanel *PanelRunPress;
	TPanel *PanelUpPress;
	TPanel *PanelDownPress;
	TPanel *PanelRunLongPress;
	TPanel *PanelUpLongPress;
	TPanel *PanelDownLongPress;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TButton *ButtonGetBtnState;
	TCheckBox *CheckBoxAutoGetBtnState;
	TTimer *TimerAutoClearStatus;
	TTrackBar *TrackBarDAC_A;
	TTrackBar *TrackBarDAC_B;
	TEdit *EditDAC_A;
	TEdit *EditDAC_B;
	TButton *ButtonSetDAC_A;
	TButton *ButtonSetDAC_B;
	TTrackBar *TrackBarAutoGetButtonStatePeriod;
	void __fastcall UpdateSerialListClick(TObject *Sender);
	void __fastcall BitBtnConnectClick(TObject *Sender);
	void __fastcall ButtonGetStatusClick(TObject *Sender);
	void __fastcall CheckBoxRelayClick(TObject *Sender);
	void __fastcall ButtonGetADCClick(TObject *Sender);
	void __fastcall ButtonGetDeviceIDClick(TObject *Sender);
	void __fastcall ButtonGetBtnStateClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall CheckBoxAutoGetBtnStateClick(TObject *Sender);
	void __fastcall TimerAutoClearStatusTimer(TObject *Sender);
	void __fastcall EditDAC_AChange(TObject *Sender);
	void __fastcall TrackBarDAC_AChange(TObject *Sender);
	void __fastcall EditDAC_BChange(TObject *Sender);
	void __fastcall TrackBarDAC_BChange(TObject *Sender);
	void __fastcall ButtonSetDAC_AClick(TObject *Sender);
	void __fastcall ButtonSetDAC_BClick(TObject *Sender);
	void __fastcall EditDAC_AKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EditDAC_BKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

private:	// User declarations
public:		// User declarations
	__fastcall TFormTestSerial(TComponent* Owner);

	Probe probe;

	void __fastcall Block();
	void __fastcall UnBlock();
	void __fastcall ShowStatusBar(const UnicodeString &msg);
	void __fastcall UpdateBtnState(uint8_t Run, uint8_t Up, uint8_t Down);

	std::string Double2String(const double &d);

	double strToDouble(const std::string &str);	// преобразует string в double
	std::string doubleToStr(double val);        // преобразуем double в string
};
//---------------------------------------------------------------------------
extern PACKAGE TFormTestSerial *FormTestSerial;
//---------------------------------------------------------------------------
#endif
