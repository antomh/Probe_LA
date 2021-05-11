//---------------------------------------------------------------------------
#ifndef ProbeH
#define ProbeH

#include "serial/Serial.h"
#include "serial/ASerial.h"
#include "Definition.h"

class Probe {
protected:
	ASerial aSerial;    // COM port �����������
	Serial serial;      // COM port ����������

	uint8_t buf[SERIAL_BUF_SIZE];	// ����� ������ �������
	uint32_t bufLen;                // ������ �������� ������ ������

	HANDLE threadGetButtonState;    // ����� ������ ��������� ������
	HANDLE mutexGetButtonState;     // �������������
	void (*callbackBtnState)(uint8_t Run, uint8_t Up, uint8_t Down);

public:
	Probe();
	~Probe();

	void reset();

	bool open(const std::string &name, DWORD baudRate);             // ������������ � ����������
	bool isOpened() const;                                          // ���� �� ����� � �����������

	bool getStatus(bool &Relay, uint16_t &DAC_A, uint16_t &DAC_B);  // ������ ������� ���������� (����, ��� ����� �, B)
	bool setRelay(bool Relay);                                      // ���������� ��������� ����
	bool setDAC_A(uint16_t DAC_A);                                  // ���������� ��� ����� �
	bool setDAC_B(uint16_t DAC_B);                                  // ���������� ��� ����� �
	bool setTableCount(u8 mode, i16 min, i16 max, u16 count);
	bool setTablePacket(u8 mode, u16 offset, u16 count, u16 code[]);
	bool getADC(uint16_t &ADC);                                     // ������ �������� ���
	bool getDeviceID(std::string &ID);                              // ������ ID ����������
	bool getHiTime(uint16_t& time);
	bool getLowTime(uint16_t& time);
    bool getButtonState(uint8_t &Run, uint8_t &Up, uint8_t &Down);  // ������ ��������� ������ (Run, Up, Down)

	std::string getLastError() const;   // ������ ��������� ������ COM �����

	// ������ ������ ������ ��������� ������.
    // ����� ���������� ������������� ������ � �������������
	// ����� �������� ��������� �� ������� �������, ������� ����� ���������� ��� ��������� ������ �� ����������
	void runAutoButtonStateCheck(uint16_t askPeriod = 200, void (*callbackBState)(uint8_t Run, uint8_t Up, uint8_t Down) = NULL);
	void stopAutoButtonStateCheck();    // ��������� ������ ������ ��������� ������
	void updateBtnState();				// ���������� ������ �� ������
};

//---------------------------------------------------------------------------
#endif
