//---------------------------------------------------------------------------
#ifndef ASerialH
#define ASerialH

#include <windows.h>
#include <stdint.h>
#include <string>

#define A_SERIAL_BUF_SIZE	2048	// размер буфера
#define A_SERIAL_TIMEOUT	5000	// таймаут

DWORD WINAPI ReadThread(void* param);
DWORD WINAPI WriteThread(void* param);

class ASerial {
	protected:
		HANDLE COM_Port;		// дескриптор порта
		HANDLE reader, writer;	// дескриптор потока чтения/записи

		// структура OVERLAPPED необходима для асинхронных операций, при этом для операции чтения и записи нужно объявить разные структуры
		OVERLAPPED overlappedRead, overlappedWrite;	// для операций чтения/записи

		uint8_t bufRead[A_SERIAL_BUF_SIZE], bufWrite[A_SERIAL_BUF_SIZE];	// приемный и передающий буферы
		uint32_t bufReadLen, bufWriteLen;	// длина последней операции Read/Write
		uint32_t totalBytesRead;			// счетчик принятых байтов, обнуляется при каждом открытии порта
		
		std::string lastError;

	public:
		// callback
		void *parentObj;
		void (*pCallback)(const uint8_t*, uint32_t, void*);

		ASerial()	{ reset(); }
		~ASerial()	{ reset(); }

		void reset();

		bool open(std::string name, DWORD baudRate);	// открыть порт
		void close();									// закрыть порт

		void send(const uint8_t *buf, uint32_t len);

		void beforeRead();
		bool read();

		void beforeWrite();
		bool write();
		void suspendWrite();
		
		inline void setDTR(bool mode) const	{ EscapeCommFunction(COM_Port, mode ? SETDTR : CLRDTR); }	// установить линию DTR
		inline void setRTS(bool mode) const	{ EscapeCommFunction(COM_Port, mode ? SETRTS : CLRRTS); }	// установить линию RTS
		
		inline void resetCounter()	{ totalBytesRead = 0; }

		inline uint32_t getBufReadLen() const	{ return bufReadLen; }
		inline std::string getLastError() const	{ return lastError; }
};

//---------------------------------------------------------------------------
#endif
