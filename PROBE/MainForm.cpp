//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
#include "Registry.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormTestSerial *FormTestSerial;
//---------------------------------------------------------------------------

// КолБэк состояния кнопок щупа
void callbackButtonState(uint8_t Run, uint8_t Up, uint8_t Down) {
    FormTestSerial->UpdateBtnState(Run, Up, Down);
}
//---------------------------------------------------------------------------

std::string TFormTestSerial::Double2String(const double &d) {
	std::ostringstream strm;
	strm << d;
	return strm.str();
}
//---------------------------------------------------------------------------

char easytolower(char in) {
	if (in <= 'Z' && in >= 'A')	return in - ('Z' - 'z');
	if (in <= 'Я' && in >= 'А')	return in - ('Я' - 'я');
	return in;
}
//---------------------------------------------------------------------------

double TFormTestSerial::strToDouble(const std::string &str) {
	std::string alph	= "-0123456789.";
	std::string tStr	= str;

	// Исправим разделитель дробной части
	size_t pos	= tStr.find(",");
	if (pos != std::string::npos)   tStr[pos]	= '.';

	// Удалим все лишнее
	for (int i = 0; i < tStr.size(); i++) {
		if (alph.find(tStr[i]) == std::string::npos) {
			tStr.erase(tStr.begin() + i);
			i--;
		}
	}

	// Минус может быть только в начале
	if (tStr.find("-") != std::string::npos) {
		for (int i = 1; i < tStr.size(); i++) {
			if (tStr[i] == '-') {
				tStr.erase(tStr.begin() + i);
				i--;
			}
		}
	}

	// Получаем число
	return atof(tStr.c_str());
}

std::string TFormTestSerial::doubleToStr(double val) {
	return Double2String(val);
}
//---------------------------------------------------------------------------

__fastcall TFormTestSerial::TFormTestSerial(TComponent* Owner) : TForm(Owner) {
	ComboBoxBaudRate->Clear();
	ComboBoxBaudRate->Items->Add("110");
	ComboBoxBaudRate->Items->Add("300");
	ComboBoxBaudRate->Items->Add("600");
	ComboBoxBaudRate->Items->Add("1200");
	ComboBoxBaudRate->Items->Add("2400");
	ComboBoxBaudRate->Items->Add("4800");
	ComboBoxBaudRate->Items->Add("9600");
	ComboBoxBaudRate->Items->Add("14400");
	ComboBoxBaudRate->Items->Add("19200");
	ComboBoxBaudRate->Items->Add("38400");
	ComboBoxBaudRate->Items->Add("56000");
	ComboBoxBaudRate->Items->Add("57600");
	ComboBoxBaudRate->Items->Add("115200");
	ComboBoxBaudRate->Items->Add("128000");
	ComboBoxBaudRate->Items->Add("256000");
	ComboBoxBaudRate->ItemIndex = 6;

	TimerAutoClearStatus->Enabled	= false;

//---------------------------------------------------------------------------

    CheckBoxRelay->Checked	= false;

	TrackBarDAC_A->Position	= 0;
	EditDAC_A->Text	= 0;

	TrackBarDAC_B->Position	= 0;
	EditDAC_B->Text	= 0;

	EditADC->Text		= "";
	EditDeviceID->Text	= "";

	PanelRunPress->Color		= clSilver;
	PanelRunLongPress->Color	= clSilver;
	PanelUpPress->Color			= clSilver;
	PanelUpLongPress->Color		= clSilver;
	PanelDownPress->Color		= clSilver;
	PanelDownLongPress->Color	= clSilver;

	CheckBoxAutoGetBtnState->Checked	= false;
	TrackBarAutoGetButtonStatePeriod->Position	= 200;
	TrackBarAutoGetButtonStatePeriod->Enabled   = true;
	TrackBarAutoGetButtonStatePeriod->Visible   = true;

	Block();
	UpdateSerialListClick(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TFormTestSerial::FormClose(TObject *Sender, TCloseAction &Action) {
	probe.reset();
	Block();
}
//---------------------------------------------------------------------------

void __fastcall TFormTestSerial::UpdateSerialListClick(TObject *Sender) {
    AnsiString KeyName	= "\\Hardware\\DeviceMap\\SerialComm";
	TStringList *SerialCommValues	= new TStringList();
	TRegistry *Registry	= new TRegistry;

	try {
		Registry->RootKey	= HKEY_LOCAL_MACHINE;
		Registry->OpenKeyReadOnly(KeyName);
		Registry->GetValueNames(SerialCommValues);

		ListBox_COM_Ports->Clear();
		for (int i = 0; i < SerialCommValues->Count; i++) {
			ListBox_COM_Ports->Items->Add(Registry->ReadString(SerialCommValues->Strings[i]));
		}

	} __finally {
		delete Registry;
		delete SerialCommValues;
		if (ListBox_COM_Ports->Items->Count > 0)	ListBox_COM_Ports->ItemIndex	= 0;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormTestSerial::BitBtnConnectClick(TObject *Sender) {
	if (ListBox_COM_Ports->ItemIndex < 0 || ListBox_COM_Ports->ItemIndex >= ListBox_COM_Ports->Items->Count)	return;

	if (!probe.isOpened()) {
		DWORD baudRate	= CBR_9600;
		if (ComboBoxBaudRate->ItemIndex == 0)   	baudRate	= CBR_110;
		else if (ComboBoxBaudRate->ItemIndex == 1)	baudRate	= CBR_300;
		else if (ComboBoxBaudRate->ItemIndex == 2)	baudRate	= CBR_600;
		else if (ComboBoxBaudRate->ItemIndex == 3)	baudRate	= CBR_1200;
		else if (ComboBoxBaudRate->ItemIndex == 4)	baudRate	= CBR_2400;
		else if (ComboBoxBaudRate->ItemIndex == 5)	baudRate	= CBR_4800;
		else if (ComboBoxBaudRate->ItemIndex == 6)	baudRate	= CBR_9600;
		else if (ComboBoxBaudRate->ItemIndex == 7)	baudRate	= CBR_14400;
		else if (ComboBoxBaudRate->ItemIndex == 8)	baudRate	= CBR_19200;
		else if (ComboBoxBaudRate->ItemIndex == 9)	baudRate	= CBR_38400;
		else if (ComboBoxBaudRate->ItemIndex == 10)	baudRate	= CBR_56000;
		else if (ComboBoxBaudRate->ItemIndex == 11)	baudRate	= CBR_57600;
		else if (ComboBoxBaudRate->ItemIndex == 12)	baudRate	= CBR_115200;
		else if (ComboBoxBaudRate->ItemIndex == 13)	baudRate	= CBR_128000;
		else if (ComboBoxBaudRate->ItemIndex == 14)	baudRate	= CBR_256000;

		if (!probe.open(AnsiString(ListBox_COM_Ports->Items->operator [](ListBox_COM_Ports->ItemIndex)).c_str(), baudRate)) {
			Block();
			Application->MessageBox(UnicodeString(("Ошибка подключения: " + probe.getLastError()).c_str()).c_str(), L"Ошибка", MB_OK | MB_ICONERROR);
			return;
		}

		UnBlock();
		BitBtnConnect->Caption	= "Отключиться";

	} else {
		probe.reset();
		Block();
		BitBtnConnect->Caption	= "Подключиться";
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormTestSerial::Block() {
	GroupBoxDevice->Visible	= false;
	GroupBoxDevice->Enabled	= false;

	CheckBoxAutoGetBtnState->Checked	= false;
	TrackBarAutoGetButtonStatePeriod->Enabled   = true;
	TrackBarAutoGetButtonStatePeriod->Visible   = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormTestSerial::UnBlock() {
	GroupBoxDevice->Visible	= true;
	GroupBoxDevice->Enabled	= true;
}
//---------------------------------------------------------------------------

void __fastcall TFormTestSerial::ShowStatusBar(const UnicodeString &msg) {
	StatusBar1->Panels->Items[0]->Text	= msg;
    TimerAutoClearStatus->Enabled	= true;
}
//---------------------------------------------------------------------------

void __fastcall TFormTestSerial::ButtonGetStatusClick(TObject *Sender) {
	bool Relay;
	uint16_t DAC_A, DAC_B;

	if (!probe.getStatus(Relay, DAC_A, DAC_B))  ShowStatusBar("Статус устройства не верен");
	else {
		CheckBoxRelay->Checked	= Relay;
		TrackBarDAC_A->Position	= DAC_A;
		TrackBarDAC_B->Position	= DAC_B;

        ShowStatusBar("Статус устройства получен");
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormTestSerial::CheckBoxRelayClick(TObject *Sender) {
	ShowStatusBar(probe.setRelay(CheckBoxRelay->Checked) ? UnicodeString(L"Установка Реле: Успешно") : UnicodeString(L"Установка Реле: Ошибка"));
}
//---------------------------------------------------------------------------

void __fastcall TFormTestSerial::ButtonSetDAC_AClick(TObject *Sender) {
	ShowStatusBar(probe.setDAC_A(TrackBarDAC_A->Position) ? UnicodeString(L"Установка ЦАП канал А: Успешно") : UnicodeString(L"Установка ЦАП канал А: Ошибка"));
}
//---------------------------------------------------------------------------

void __fastcall TFormTestSerial::ButtonSetDAC_BClick(TObject *Sender) {
	ShowStatusBar(probe.setDAC_B(TrackBarDAC_B->Position) ? UnicodeString(L"Установка ЦАП канал B: Успешно") : UnicodeString(L"Установка ЦАП канал B: Ошибка"));
}
//---------------------------------------------------------------------------

void __fastcall TFormTestSerial::EditDAC_AChange(TObject *Sender) {
	uint16_t val	= 0;

	if (EditDAC_A->Text.Length() > 0) {
		val	= EditDAC_A->Text.ToInt();
		if (val > 0x0FFF) {
			val	= 0x0FFF;
			EditDAC_A->Text	= val;
		}
	}

	TrackBarDAC_A->Position	= val;
}
//---------------------------------------------------------------------------

void __fastcall TFormTestSerial::TrackBarDAC_AChange(TObject *Sender) {
	uint16_t val	= TrackBarDAC_A->Position;
	EditDAC_A->Text	= val;
}
//---------------------------------------------------------------------------

void __fastcall TFormTestSerial::EditDAC_AKeyDown(TObject *Sender, WORD &Key, TShiftState Shift) {
	if (Key != 13)  return;

	ButtonSetDAC_AClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFormTestSerial::EditDAC_BChange(TObject *Sender) {
	uint16_t val	= 0;

	if (EditDAC_B->Text.Length() > 0) {
		val	= EditDAC_B->Text.ToInt();
		if (val > 0x0FFF) {
			val	= 0x0FFF;
			EditDAC_B->Text	= val;
		}
	}

	TrackBarDAC_B->Position	= val;
}
//---------------------------------------------------------------------------

void __fastcall TFormTestSerial::TrackBarDAC_BChange(TObject *Sender) {
	uint16_t val	= TrackBarDAC_B->Position;
	EditDAC_B->Text	= val;
}
//---------------------------------------------------------------------------

void __fastcall TFormTestSerial::EditDAC_BKeyDown(TObject *Sender, WORD &Key, TShiftState Shift) {
	if (Key != 13)  return;

	ButtonSetDAC_AClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFormTestSerial::ButtonGetADCClick(TObject *Sender) {
	uint16_t ADC;

	if (!probe.getADC(ADC)) ShowStatusBar("Значение АЦП: ошибка");
	else {
		EditADC->Text	= String(ADC);
		ShowStatusBar("Значение АЦП получено");
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormTestSerial::ButtonGetDeviceIDClick(TObject *Sender) {
	std::string ID;

	if (!probe.getDeviceID(ID))    ShowStatusBar("ID устройства: ошибка");
    else {
		EditDeviceID->Text	= String(ID.c_str());
		ShowStatusBar("ID устройства получено");
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormTestSerial::UpdateBtnState(uint8_t Run, uint8_t Up, uint8_t Down) {
	// RUN
	if (Run == 1) {
		PanelRunPress->Color		= clLime;
		PanelRunLongPress->Color	= clSilver;

	} else if (Run == 2) {
		PanelRunPress->Color		= clSilver;
		PanelRunLongPress->Color	= clLime;

	} else {
		PanelRunPress->Color		= clSilver;
		PanelRunLongPress->Color	= clSilver;
	}

	// UP
	if (Up == 1) {
		PanelUpPress->Color		= clLime;
		PanelUpLongPress->Color	= clSilver;

	} else if (Up == 2) {
		PanelUpPress->Color		= clSilver;
		PanelUpLongPress->Color	= clLime;

	} else {
		PanelUpPress->Color		= clSilver;
		PanelUpLongPress->Color	= clSilver;
	}

	// DOWN
	if (Down == 1) {
		PanelDownPress->Color		= clLime;
		PanelDownLongPress->Color	= clSilver;

	} else if (Down == 2) {
		PanelDownPress->Color		= clSilver;
		PanelDownLongPress->Color	= clLime;

	} else {
		PanelDownPress->Color		= clSilver;
		PanelDownLongPress->Color	= clSilver;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormTestSerial::ButtonGetBtnStateClick(TObject *Sender) {
	uint8_t Run, Up, Down;

	if (!probe.getButtonState(Run, Up, Down))	ShowStatusBar("Состояние кнопок: ошибка");
	else {
		UpdateBtnState(Run, Up, Down);
		ShowStatusBar("Состояние кнопок получено");
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormTestSerial::CheckBoxAutoGetBtnStateClick(TObject *Sender) {
	if (CheckBoxAutoGetBtnState->Checked) {
		probe.runAutoButtonStateCheck(TrackBarAutoGetButtonStatePeriod->Position, callbackButtonState);
		TrackBarAutoGetButtonStatePeriod->Enabled	= false;
		TrackBarAutoGetButtonStatePeriod->Visible	= false;

	} else {
		probe.stopAutoButtonStateCheck();
		TrackBarAutoGetButtonStatePeriod->Enabled	= true;
		TrackBarAutoGetButtonStatePeriod->Visible	= true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormTestSerial::TimerAutoClearStatusTimer(TObject *Sender) {
	TimerAutoClearStatus->Enabled	= false;
	StatusBar1->Panels->Items[0]->Text	= "";
}
//---------------------------------------------------------------------------

