//---------------------------------------------------------------------------
#ifndef SerialH
#define SerialH

#include <windows.h>
#include <stdint.h>
#include <string>

// размер буфера
#ifndef SERIAL_BUF_SIZE
	#define SERIAL_BUF_SIZE	2048
#endif

/**
 *	Синхронная работа с COM портом
 *	Чтение работет так:
 *	Сначала ожидаем приема первого символа. Ожидаем первого символа не более SERIAL_TIMEOUT миллисекунд
 *	Если пришел значимый символ, то начинаем измерять время между символами, и читаем их пока это время меньше SERIAL_BETWEEN_SYMBOL_TIMEOUT
 */

class Serial {
	protected:
		HANDLE COM_Port;	// дескриптор порта

		uint8_t bufRead[SERIAL_BUF_SIZE], bufWrite[SERIAL_BUF_SIZE];	// приемный и передающий буферы
		uint32_t bufReadLen, bufWriteLen;	// дразмер буфера Read/Write
		
		std::string lastError;

		bool checkPortHandle();

	public:
		uint32_t SERIAL_TIMEOUT;				// таймаут
		uint32_t SERIAL_BETWEEN_SYMBOL_TIMEOUT;	// таймаут между символами во время чтения данных

		Serial()	{ reset(); }
		~Serial()	{ reset(); }

		void reset();

		// открыть/закрыть порт
		bool open(std::string name, DWORD baudRate);
		void close();

		// чтение/запись в порт
		bool send(const uint8_t *buf, uint32_t len);
		bool receive(uint8_t *buf, uint32_t &len);
		bool sendAndReceive(uint8_t *buf, uint32_t &len, bool needWaitForAnswer = false);

		inline void setDTR(bool mode) const	{ EscapeCommFunction(COM_Port, mode ? SETDTR : CLRDTR); }	// установить линию DTR
		inline void setRTS(bool mode) const	{ EscapeCommFunction(COM_Port, mode ? SETRTS : CLRRTS); }	// установить линию RTS

		inline uint32_t getBufReadLen() const	{ return bufReadLen; }
		inline std::string getLastError() const	{ return lastError; }

        inline bool isOpened() const    { return (COM_Port != NULL); }
};
//---------------------------------------------------------------------------
#endif
