//---------------------------------------------------------------------------
#pragma hdrstop

#include "ASerial.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
// главная функция потока, реализует приём байтов из COM-порта
DWORD WINAPI ReadThread(void* param) {
	ASerial* ptr	= (ASerial*)param;
	ptr->beforeRead();

	// пока поток не будет прерван, выполняем цикл
	while(true)	ptr->read();
}

//---------------------------------------------------------------------------
// главная функция потока, выполняет передачу байтов из буфера в COM-порт
DWORD WINAPI WriteThread(void* param) {
	ASerial* ptr	= (ASerial*)param;
	ptr->beforeWrite();

	while(true) {
		ptr->write();
		ptr->suspendWrite();
	}
}

//---------------------------------------------------------------------------
void ASerial::reset() {
	close();

	parentObj	= NULL;
	pCallback	= NULL;

	writer		= NULL;
	reader		= NULL;
	COM_Port	= NULL;
	
	lastError		= "";
	bufReadLen		= 0;
	bufWriteLen		= 0;
	totalBytesRead	= 0;
}

//---------------------------------------------------------------------------
// функция открытия и инициализации порта
bool ASerial::open(std::string name, DWORD baudRate) {
	reset();
	
	DCB dcb;				// структура для общей инициализации порта DCB
	COMMTIMEOUTS timeouts;	// структура для установки таймаутов

	// открыть порт, для асинхронных операций обязательно нужно указать флаг FILE_FLAG_OVERLAPPED
	if (name.size() > 4)	name	= "\\\\.\\" + name;
	COM_Port	= CreateFileA(name.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	// здесь:
	// - name.c_str() - имя порта в качестве имени файла
	// - GENERIC_READ | GENERIC_WRITE - доступ к порту на чтение/записть
	// - 0 - порт не может быть общедоступным (shared)
	// - NULL - дескриптор порта не наследуется, используется дескриптор безопасности по умолчанию
	// - OPEN_EXISTING - порт должен открываться как уже существующий файл
	// - FILE_FLAG_OVERLAPPED - этот флаг указывает на использование асинхронных операций
	// - NULL - указатель на файл шаблона не используется при работе с портами

	// если ошибка открытия порта
	if (COM_Port == INVALID_HANDLE_VALUE) {
		lastError	= "Не удалось открыть порт";
		return false;
	}

	// инициализация порта
	// в первое поле структуры DCB необходимо занести её длину, она будет использоваться функциями настройки порта для контроля корректности структуры
	dcb.DCBlength	= sizeof(DCB);

	// считать структуру DCB из порта, если не удалось - закрыть порт и вывести сообщение об ошибке
	if (!GetCommState(COM_Port, &dcb)) {
		close();
		lastError	= "Не удалось считать DCB";
		return false;
	}

	// инициализация структуры DCB
	dcb.BaudRate		= baudRate;				// задаём скорость передачи бод
	dcb.fBinary			= TRUE;					// включаем двоичный режим обмена
	dcb.fParity		 	= FALSE;				// режим контроля четности
	dcb.fOutxCtsFlow	= FALSE;				// выключаем режим слежения за сигналом CTS
	dcb.fOutxDsrFlow	= FALSE;				// выключаем режим слежения за сигналом DSR
	dcb.fDtrControl		= DTR_CONTROL_DISABLE;	// отключаем использование линии DTR
	dcb.fDsrSensitivity	= FALSE;				// отключаем восприимчивость драйвера к состоянию линии DSR
	dcb.fNull			= TRUE;					// запретить приём нулевых байтов
	dcb.fRtsControl		= RTS_CONTROL_DISABLE;	// отключаем использование линии RTS
	dcb.fAbortOnError	= FALSE;				// отключаем остановку всех операций чтения/записи при ошибке
	dcb.ByteSize		= 8;					// задаём 8 бит в байте
	dcb.Parity			= NOPARITY;				// отключаем проверку чётности
	dcb.StopBits		= ONESTOPBIT;			// задаём один стоп-бит

	// загрузить структуру DCB в порт
	if (!SetCommState(COM_Port, &dcb)) {
		close();
		lastError	= "Не удалось установить DCB";
		return false;
	}

	// установить таймауты
	timeouts.ReadIntervalTimeout			= 0xFFFFFFFF;		// таймаут между двумя символами
	timeouts.ReadTotalTimeoutMultiplier		= 0;				// общий таймаут операции чтения
	timeouts.ReadTotalTimeoutConstant		= A_SERIAL_TIMEOUT;	// константа для общего таймаута операции чтения
	timeouts.WriteTotalTimeoutMultiplier	= 0;				// общий таймаут операции записи
	timeouts.WriteTotalTimeoutConstant		= A_SERIAL_TIMEOUT;	// константа для общего таймаута операции записи

	// записать структуру таймаутов в порт
	if (!SetCommTimeouts(COM_Port, &timeouts)) {
		close();
		lastError	= "Не удалось установить тайм-ауты";
		return false;
	}

	SetupComm(COM_Port, A_SERIAL_BUF_SIZE, A_SERIAL_BUF_SIZE);	// установить размеры очередей приёма и передачи
	PurgeComm(COM_Port, PURGE_RXCLEAR);							// очистить принимающий буфер порта

	reader	= CreateThread(NULL, 0, ReadThread, (LPVOID)this, 0, NULL);					// создаём поток чтения, который сразу начнёт выполняться (предпоследний параметр = 0)
	writer	= CreateThread(NULL, 0, WriteThread, (LPVOID)this, CREATE_SUSPENDED, NULL);	// создаём поток записи в остановленном состоянии (предпоследний параметр = CREATE_SUSPENDED)

	// сбрасываем счётчик байтов
	totalBytesRead	= 0;

	return true;
}

//---------------------------------------------------------------------------
// функция закрытия порта
void ASerial::close() {
	//	Примечание: так как при прерывании потоков, созданных с помощью функций WinAPI, функцией TerminateThread - поток может быть прерван жёстко, в любом месте своего выполнения, то освобождать дескриптор сигнального объекта-события, находящегося в структуре типа OVERLAPPED, связанной с потоком, следует не внутри кода потока, а отдельно, после вызова функции TerminateThread.
	//	После чего нужно освободить и сам дескриптор потока.
	try {
		if (writer) {
			TerminateThread(writer, 0);
			CloseHandle(overlappedWrite.hEvent);
			CloseHandle(writer);
			writer	= NULL;
		}

		if (reader) {
			TerminateThread(reader, 0);
			CloseHandle(overlappedRead.hEvent);
			CloseHandle(reader);
			reader	= NULL;
		}

		CloseHandle(COM_Port);	// закрыть порт
		COM_Port	= NULL;		// обнулить переменную для дескриптора порта
		
	} catch (...) {

	}
}

//---------------------------------------------------------------------------
void ASerial::send(const uint8_t *buf, uint32_t len) {
	memset(bufWrite, 0, A_SERIAL_BUF_SIZE);	// очистить программный передающий буфер, чтобы данные не накладывались друг на друга
	PurgeComm(COM_Port, PURGE_TXCLEAR);		// очистить передающий буфер порта
	bufWriteLen	= len;
	memcpy(bufWrite, buf, bufWriteLen);
	ResumeThread(writer);	// активировать поток записи данных в порт
}

//---------------------------------------------------------------------------
void ASerial::beforeRead() {
	overlappedRead.hEvent	= CreateEvent(NULL, true, true, NULL);	// создать сигнальный объект-событие для асинхронных операций
	SetCommMask(COM_Port, EV_RXCHAR);								// установить маску на срабатывание по событию приёма байта в порт
}

//---------------------------------------------------------------------------
bool ASerial::read() {
	COMSTAT comstat;	// структура текущего состояния порта, в данной программе используется для определения количества принятых в порт байтов
	DWORD btr, temp, mask, signal;

	WaitCommEvent(COM_Port, &mask, &overlappedRead);						// ожидать события приёма байта (это и есть перекрываемая операция)
	signal	= WaitForSingleObject(overlappedRead.hEvent, A_SERIAL_TIMEOUT);	// приостановить поток до прихода байта
	if (signal == WAIT_TIMEOUT) {
		if (pCallback != NULL)	pCallback(NULL, 0, parentObj);
		return false;
	}

	memset(bufRead, 0, A_SERIAL_BUF_SIZE);	// очистить буфер (чтобы данные не накладывались друг на друга)

	// если событие прихода байта произошло, успешно ли завершилась перекрываемая операция WaitCommEvent, если произошло именно событие прихода байта
	if (signal == WAIT_OBJECT_0 && GetOverlappedResult(COM_Port, &overlappedRead, &temp, true) && (mask & EV_RXCHAR) != 0) {
		ClearCommError(COM_Port, &temp, &comstat);						// нужно заполнить структуру COMSTAT
		btr	= comstat.cbInQue;											// и получить из неё количество принятых байтов
		if (btr) {														// если действительно есть байты для чтения
			ReadFile(COM_Port, bufRead, btr, &temp, &overlappedRead);	// прочитать байты из порта в буфер программы
			totalBytesRead	+= btr;										// увеличиваем счётчик байтов
			bufReadLen		= btr;
			
			if (pCallback != NULL)	pCallback(bufRead, bufReadLen, parentObj);
			
			return true;
		}
	}

	return false;
}

//---------------------------------------------------------------------------
void ASerial::beforeWrite() {
 	overlappedWrite.hEvent	= CreateEvent(NULL, true, true, NULL);
}

//---------------------------------------------------------------------------
bool ASerial::write() {
	DWORD temp, signal;

	WriteFile(COM_Port, bufWrite, bufWriteLen, &temp, &overlappedWrite);		// записать байты в порт (перекрываемая операция!)
	signal	= WaitForSingleObject(overlappedWrite.hEvent, A_SERIAL_TIMEOUT);	// приостановить поток, пока не завершится перекрываемая операция WriteFile

	return (signal == WAIT_OBJECT_0 && GetOverlappedResult(COM_Port, &overlappedWrite, &temp, true));
}

//---------------------------------------------------------------------------
void ASerial::suspendWrite() {
	SuspendThread(writer);
}
