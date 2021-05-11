//---------------------------------------------------------------------------
#pragma hdrstop

#include "Serial.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
void Serial::reset() {
//	COM_Port	= NULL;
	close();

	lastError	= "";
	bufReadLen	= 0;
	bufWriteLen	= 0;

	SERIAL_TIMEOUT	= 3000;
	SERIAL_BETWEEN_SYMBOL_TIMEOUT	= 50;
}

//---------------------------------------------------------------------------
// функция открытия и инициализации порта
bool Serial::open(std::string name, DWORD baudRate) {
	reset();

	DCB dcb;				// структура для общей инициализации порта DCB
	COMMTIMEOUTS timeouts;	// структура для установки таймаутов

	// открыть порт, для асинхронных операций обязательно нужно указать флаг FILE_FLAG_OVERLAPPED
	if (name.size() > 4)	name	= "\\\\.\\" + name;
	COM_Port	= CreateFileA(name.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS/*OPEN_EXISTING*/, FILE_ATTRIBUTE_NORMAL, NULL);
	// здесь:
	// - name.c_str() - имя порта в качестве имени файла
	// - GENERIC_READ | GENERIC_WRITE - доступ к порту на чтение/записть
	// - 0 - порт не может быть общедоступным (shared)
	// - NULL - дескриптор порта не наследуется, используется дескриптор безопасности по умолчанию
	// - OPEN_EXISTING - порт должен открываться как уже существующий файл
	// - FILE_FLAG_OVERLAPPED - этот флаг указывает на использование асинхронных операций
	// - NULL - указатель на файл шаблона не используется при работе с портами

	// если ошибка открытия порта
	if (COM_Port == NULL) {
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
	timeouts.ReadIntervalTimeout			= 0xFFFFFFFF;							// таймаут между двумя символами
	timeouts.ReadTotalTimeoutMultiplier		= 0;									// общий таймаут операции чтения
	//NOTICE: тут отдельное маленькое значение, так как процедура чтения сама контролирует количество попыток чтения и таймаут должен быть коротким
	timeouts.ReadTotalTimeoutConstant		= SERIAL_BETWEEN_SYMBOL_TIMEOUT * 0.8f;	// константа для общего таймаута операции чтения
	timeouts.WriteTotalTimeoutMultiplier	= 0;									// общий таймаут операции записи
	timeouts.WriteTotalTimeoutConstant		= SERIAL_TIMEOUT;						// константа для общего таймаута операции записи

	// записать структуру таймаутов в порт
	if (!SetCommTimeouts(COM_Port, &timeouts)) {
		close();
		lastError	= "Не удалось установить тайм-ауты";
		return false;
	}

	SetupComm(COM_Port, SERIAL_BUF_SIZE, SERIAL_BUF_SIZE);	// установить размеры очередей приёма и передачи
	PurgeComm(COM_Port, PURGE_RXCLEAR);						// очистить принимающий буфер порта

	return true;
}

//---------------------------------------------------------------------------
// функция закрытия порта
void Serial::close() {
	if (COM_Port != NULL) {
		CloseHandle(COM_Port);	// закрыть порт
		COM_Port	= NULL;		// обнулить переменную для дескриптора порта
	}
}

bool Serial::checkPortHandle() {
	lastError	= "";

	if (COM_Port == NULL) {
		lastError	= "Нужно открыть соединение с COM портом";
		return false;
	}

	return true;
}

//---------------------------------------------------------------------------
bool Serial::send(const uint8_t *buf, uint32_t len) {
	if (!checkPortHandle())	return false;

	memset(bufWrite, 0, SERIAL_BUF_SIZE);	// очистить программный передающий буфер, чтобы данные не накладывались друг на друга
	PurgeComm(COM_Port, PURGE_TXCLEAR);		// очистить передающий буфер порта

	bufWriteLen	= len;
	memcpy(bufWrite, buf, bufWriteLen);

	DWORD feedback;
	if (!WriteFile(COM_Port, bufWrite, bufWriteLen, &feedback, 0) || feedback != bufWriteLen) {
		CloseHandle(COM_Port);
		COM_Port	= NULL;
		lastError	= "Ошибка записи в порт. Соединение разорвано";

		return false;
 	}

 	// In some cases it's worth uncommenting
	FlushFileBuffers(COM_Port);

	return true;
}

//---------------------------------------------------------------------------
bool Serial::receive(uint8_t *buf, uint32_t &len) {
	if (!checkPortHandle())	return false;

	// установить маску на срабатывание по событию приёма байта в порт
	SetCommMask(COM_Port, EV_RXCHAR);

	// очистка буфера
	memset(bufRead, 0, SERIAL_BUF_SIZE);
	bufReadLen	= 0;

	DWORD dtS = 0, lastByte = 0, dt = 0, feedback = 0, begin = GetTickCount();
	bool wasFirstByte	= false;

	while ((!wasFirstByte && dt < (DWORD)SERIAL_TIMEOUT) || (wasFirstByte && dtS <= SERIAL_BETWEEN_SYMBOL_TIMEOUT)) {
		if (!ReadFile(COM_Port, bufRead + bufReadLen, 1, &feedback, NULL)) {
			CloseHandle(COM_Port);
			COM_Port	= NULL;
			lastError	= "Ошибка чтения порта. Соединение разорвано";

			return false;
		}

		dt	= GetTickCount() - begin;
		bufReadLen	+= feedback;

		if (feedback > 0) {
			if (!wasFirstByte)	wasFirstByte	= true;
			lastByte	= GetTickCount();
		}

		dtS	= GetTickCount() - lastByte;
	}

	if (bufReadLen > 0) {
		len	= bufReadLen;
		memset(buf, 0, SERIAL_BUF_SIZE);
		memcpy(buf, bufRead, bufReadLen);
		return true;
	}

	lastError	= "Нет данных";
	return false;
}

//---------------------------------------------------------------------------
bool Serial::sendAndReceive(uint8_t *buf, uint32_t &len, bool needWaitForAnswer) {
	if (!send(buf, len))	return false;

	// задержка если операция не требует чтения данных
	if (!needWaitForAnswer)	{}//Sleep(100);
	else {
		memset(buf, 0, SERIAL_BUF_SIZE);
		if (!receive(buf, len))	return false;
	}

	return true;
}
