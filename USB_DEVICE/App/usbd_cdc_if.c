/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : usbd_cdc_if.c
 * @version        : v2.0_Cube
 * @brief          : Usb device for Virtual Com Port.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "usbd_cdc_if.h"

/* USER CODE BEGIN INCLUDE */
#include "main.h"
#include "string.h"
#include "stdio.h"
#include "logic_calibration_table.h"

/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief Usb device library.
  * @{
  */

/** @addtogroup USBD_CDC_IF
  * @{
  */

/** @defgroup USBD_CDC_IF_Private_TypesDefinitions USBD_CDC_IF_Private_TypesDefinitions
  * @brief Private types.
  * @{
  */

/* USER CODE BEGIN PRIVATE_TYPES */

/* USER CODE END PRIVATE_TYPES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Private_Defines USBD_CDC_IF_Private_Defines
  * @brief Private defines.
  * @{
  */

/* USER CODE BEGIN PRIVATE_DEFINES */
/* Define size for the receive and transmit buffer over CDC */
/* It's up to user to redefine and/or remove those define */
#define APP_RX_DATA_SIZE 512
#define APP_TX_DATA_SIZE 512
/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Private_Macros USBD_CDC_IF_Private_Macros
  * @brief Private macros.
  * @{
  */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Private_Variables USBD_CDC_IF_Private_Variables
  * @brief Private variables.
  * @{
  */
/* Create buffer for reception and transmission           */
/* It's up to user to redefine and/or remove those define */
/** Received data over USB are stored in this buffer      */
uint8_t UserRxBufferFS[APP_RX_DATA_SIZE];

/** Data to send over USB CDC are stored in this buffer   */
uint8_t UserTxBufferFS[APP_TX_DATA_SIZE];

/* USER CODE BEGIN PRIVATE_VARIABLES */
uint8_t RelayState = 0x00; //TODO:ппроверить первое состоянеи первоначальное состояние реле 27V
//extern Table_t *calibTable;
/* USER CODE END PRIVATE_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Exported_Variables USBD_CDC_IF_Exported_Variables
  * @brief Public variables.
  * @{
  */

extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Private_FunctionPrototypes USBD_CDC_IF_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */

static int8_t CDC_Init_FS(void);
static int8_t CDC_DeInit_FS(void);
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t *pbuf, uint16_t length);
static int8_t CDC_Receive_FS(uint8_t *pbuf, uint32_t *Len);

/* USER CODE BEGIN PRIVATE_FUNCTIONS_DECLARATION */

/* USER CODE END PRIVATE_FUNCTIONS_DECLARATION */

/**
  * @}
  */

USBD_CDC_ItfTypeDef USBD_Interface_fops_FS =
	{
		CDC_Init_FS,
		CDC_DeInit_FS,
		CDC_Control_FS,
		CDC_Receive_FS};

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Initializes the CDC media low layer over the FS USB IP
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Init_FS(void)
{
	/* USER CODE BEGIN 3 */
	/* Set Application Buffers */
	USBD_CDC_SetTxBuffer(&hUsbDeviceFS, UserTxBufferFS, 0);
	USBD_CDC_SetRxBuffer(&hUsbDeviceFS, UserRxBufferFS);
	return (USBD_OK);
	/* USER CODE END 3 */
}

/**
  * @brief  DeInitializes the CDC media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_DeInit_FS(void)
{
	/* USER CODE BEGIN 4 */
	return (USBD_OK);
	/* USER CODE END 4 */
}

/**
  * @brief  Manage the CDC class requests
  * @param  cmd: Command code
  * @param  pbuf: Buffer containing command data (request parameters)
  * @param  length: Number of data to be sent (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t *pbuf, uint16_t length)
{
	/* USER CODE BEGIN 5 */
	switch (cmd)
	{
	case CDC_SEND_ENCAPSULATED_COMMAND:

		break;

	case CDC_GET_ENCAPSULATED_RESPONSE:

		break;

	case CDC_SET_COMM_FEATURE:

		break;

	case CDC_GET_COMM_FEATURE:

		break;

	case CDC_CLEAR_COMM_FEATURE:

		break;

		/*******************************************************************************/
		/* Line Coding Structure                                                       */
		/*-----------------------------------------------------------------------------*/
		/* Offset | Field       | Size | Value  | Description                          */
		/* 0      | dwDTERate   |   4  | Number |Data terminal rate, in bits per second*/
		/* 4      | bCharFormat |   1  | Number | Stop bits                            */
		/*                                        0 - 1 Stop bit                       */
		/*                                        1 - 1.5 Stop bits                    */
		/*                                        2 - 2 Stop bits                      */
		/* 5      | bParityType |  1   | Number | Parity                               */
		/*                                        0 - None                             */
		/*                                        1 - Odd                              */
		/*                                        2 - Even                             */
		/*                                        3 - Mark                             */
		/*                                        4 - Space                            */
		/* 6      | bDataBits  |   1   | Number Data bits (5, 6, 7, 8 or 16).          */
		/*******************************************************************************/
	case CDC_SET_LINE_CODING:

		break;

	case CDC_GET_LINE_CODING:

		break;

	case CDC_SET_CONTROL_LINE_STATE:

		break;

	case CDC_SEND_BREAK:

		break;

	default:
		break;
	}

	return (USBD_OK);
	/* USER CODE END 5 */
}

/**
  * @brief  Data received over USB OUT endpoint are sent over CDC interface
  *         through this function.
  *
  *         @note
  *         This function will issue a NAK packet on any OUT packet received on
  *         USB endpoint until exiting this function. If you exit this function
  *         before transfer is complete on CDC interface (ie. using DMA controller)
  *         it will result in receiving more data while previous ones are still
  *         not sent.
  *
  * @param  Buf: Buffer of data to be received
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Receive_FS(uint8_t *Buf, uint32_t *Len)
{
	/* USER CODE BEGIN 6 */
	USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &Buf[0]);
	USBD_CDC_ReceivePacket(&hUsbDeviceFS);

	if (*Len < 1)
		return (USBD_OK);

	//--------------------------------------------------------------------------

	uint16_t tVal16;
	uint8_t cmd = Buf[0];

	// command
	// 0x01 - включение рэле							data: 1B (0x00 - выключить; 0x01 - включить)	answer: 0x01 + 1B status
	// 0x02 - ЦАП канал А								data: 2B (значение)								answer: 0x02 + 1B status
	// 0x03 - ЦАП канал B								data: 2B (значение)								answer: 0x03 + 1B status
	// 0x04 - АЦП запрос значения						data: 0B										answer: 0x04 + 2B value
	// 0x05 - запрос состояния (Relay, DA, DB)			data: 0B										answer: 0x05 + 1B состиояние рэле + 2B значение ЦАП канал А + 2B значение ЦАП канал B
	// 0x06 - запрос состояния кнопок (Run, Up, Down)	data: 0B										answer: 0x06 + 1B состояние кнопки Run + 1B состояние кнопки Up + 1B состояние кнопки Down
	// 0x07 - запрос ID устройства
	// ("SN+WW+YY+NNN")									data: 0B										answer: 0x07 + 9B ID ("SN+WW+YY+NNN") SN1121001- 11 неделя-21год - 001 порядковый номер изготовления
	// 0х08 - запрос измеренной длительности			data: 0B (0x00 - сработал; 0x01 - не сработал)	answer: 0x08 + 1B status
	// 0х09 - запрос измеренной длительности			data: 0B (0x00 - сработал; 0x01 - не сработал)	answer: 0x08 + 1B status

	//--------------------------------------------------------------------------
	// 0х0C - запрос размера калибровочной таблицы		data: 0B ([длина калибровочной таблицы ]				0x00 - сработал; 0x01 - не сработал)	answer: 0x09 + 1B status
	// 0х0B - команда записи во флеш					data: 0B (0x00 - сработал; 0x01 - не сработал)	answer: 0x09 + 1B status
	// 0х0A - прием калибровочной таблицы				data: 0B (0x00 - сработал; 0x01 - не сработал)	answer: 0x09 + 1B status
	// 0х0D - запрос срабатывания компаратора inHH		data: 0B (0x00 - сработал; 0x01 - не сработал)	answer: 0x09 + 1B status

	// status
	// 0x00 - успешно
	// 0x01 - ошибка

	// Калибровка
	/* Одна итерация: на входе щупа устанавливается заданное напряжение.
	 * Начинаем менять входные коды ЦАП верхнего и нижнего уровня
	 * до того момента пока на выходах компараторов не появится 1.
	 * Т.е. каждый раз когда мы меняем входной код - мы запрашиваем контроллер щупа о состоянии выходов компаратора.
	 */

	//--------------------------------------------------------------------------

	// Relay:1 - 12V	[0x01 - 0x01]
	if (cmd == 0x01)
	{
		if (*Len >= 2 && (Buf[1] == 0x01 || Buf[1] == 0x00))
		{
			if (Buf[1] == 0x01)
			{
				HAL_GPIO_WritePin(Relay_GPIO_Port, Relay_Pin, GPIO_PIN_SET);
				RelayState = 0x01;
				printf("RelayState:12V - %d \n", RelayState);
				SetAllDAC();

				UserTxBufferFS[0] = cmd;
				UserTxBufferFS[1] = 0x00; // успешно
				CDC_Transmit_FS(UserTxBufferFS, 2);
				return (USBD_OK);
			}
			else if (Buf[1] == 0x00)
			{
				HAL_GPIO_WritePin(Relay_GPIO_Port, Relay_Pin, GPIO_PIN_RESET);
				RelayState = 0x00;
				printf("RelayState:27V - %d \n", RelayState);
				SetAllDAC();

				UserTxBufferFS[0] = cmd;
				UserTxBufferFS[1] = 0x00; // успешно
				CDC_Transmit_FS(UserTxBufferFS, 2);
				return (USBD_OK);
			}
		}

		UserTxBufferFS[0] = cmd;
		UserTxBufferFS[1] = 0x01; // ошибка
		CDC_Transmit_FS(UserTxBufferFS, 2);
		return (USBD_OK);

		//--------------------------------------------------------------------------
		// DA:4095
	}
	else if (cmd == 0x02)
	{
		if (*Len >= 3)
		{
			resValTIM3_PB4(); // обнуление переменной для проведения калиброки
			resValTIM4_PB6(); // обнуление переменной для проведения калиброки
			memcpy(&tVal16, Buf + 1, sizeof(tVal16));
			SetDacA(tVal16);
			//			SetDacA(tVal16);

			printf("DacA: %d\n", tVal16);
			UserTxBufferFS[0] = cmd;
			UserTxBufferFS[1] = 0x00; // успешно

			CDC_Transmit_FS(UserTxBufferFS, 2);
			return (USBD_OK);
		}

		UserTxBufferFS[0] = cmd;
		UserTxBufferFS[1] = 0x01; // ошибка
		CDC_Transmit_FS(UserTxBufferFS, 2);
		return (USBD_OK);
		//--------------------------------------------------------------------------
		// DB:4095
	}
	else if (cmd == 0x03)
	{
		if (*Len >= 3)
		{
			resValTIM3_PB4(); // обнуление переменной для проведения калиброки
			resValTIM4_PB6(); // обнуление переменной для проведения калиброки
			memcpy(&tVal16, Buf + 1, sizeof(tVal16));
			SetDacB(tVal16);

			UserTxBufferFS[0] = cmd;
			UserTxBufferFS[1] = 0x00; // успешно

			printf("DacB: %d \n", tVal16);

			CDC_Transmit_FS(UserTxBufferFS, 2);
			return (USBD_OK);
		}

		UserTxBufferFS[0] = cmd;
		UserTxBufferFS[1] = 0x01; // ошибка
		CDC_Transmit_FS(UserTxBufferFS, 2);
		return (USBD_OK);
		//--------------------------------------------------------------------------
		// ADC?
	}
	else if (cmd == 0x04)
	{
		tVal16 = GetADC();
		UserTxBufferFS[0] = cmd;
		memcpy(UserTxBufferFS + 1, &tVal16, sizeof(tVal16));
		CDC_Transmit_FS(UserTxBufferFS, 3);
		return (USBD_OK);
		//--------------------------------------------------------------------------
		// Relay?DA?DB?
	}
	else if (cmd == 0x05)
	{
		UserTxBufferFS[0] = cmd;
		UserTxBufferFS[1] = RelayState;

		tVal16 = GetDacA();
		memcpy(UserTxBufferFS + 2, &tVal16, sizeof(tVal16));

		tVal16 = GetDacB();
		memcpy(UserTxBufferFS + 4, &tVal16, sizeof(tVal16));

		CDC_Transmit_FS(UserTxBufferFS, 6);
		return (USBD_OK);
		//--------------------------------------------------------------------------
		// Btn?
	}
	else if (cmd == 0x06)
	{
		UserTxBufferFS[0] = cmd;
		UserTxBufferFS[1] = GetBtnRunState();
		UserTxBufferFS[2] = GetBtnUpState();
		UserTxBufferFS[3] = GetBtnDownState();
		CDC_Transmit_FS(UserTxBufferFS, 4);
		return (USBD_OK);
		//--------------------------------------------------------------------------
		// ID?
	}
	else if (cmd == 0x07)
	{
		char str[9] = {
			0,
		};
		memcpy(str, "SN", strlen("SN"));
		itoa(SN_DEFINE, str + 2, 16);

		UserTxBufferFS[0] = cmd;
		UserTxBufferFS[1] = strlen(str);
		memcpy(UserTxBufferFS + 2, str, strlen(str));
		CDC_Transmit_FS(UserTxBufferFS, strlen(str) + 2);
		return (USBD_OK);
		//--------------------------------------------------------------------------
		// Калибровка
		/* TODO: изменить описание калиброки относительно измерения длительности
	 * Одна итерация: на входе щупа устанавливается заданное напряжение.
	 * Начинаем менять входные коды ЦАП верхнего и нижнего уровня
	 * до того момента пока на выходах компараторов не появится 1.
	 * Т.е. каждый раз когда мы меняем входной код - мы запрашиваем контроллер щупа о состоянии выходов компаратора.
	 */

		//--------------------------------------------------------------------------
		// TIM inHL?
	}
	else if (cmd == 0x08)
	{
		EnableTIM3_PB4();
		uint16_t temp = GetTIM3();
		UserTxBufferFS[0] = cmd;
		memcpy(UserTxBufferFS + 1, &temp, sizeof(uint16_t));
		CDC_Transmit_FS(UserTxBufferFS, 1 + sizeof(uint16_t));
		return (USBD_OK);

		// TIM inLL?
		//--------------------------------------------------------------------------
	}
	else if (cmd == 0x09)
	{
		EnableTIM4_PB6();
		uint16_t temp = GetTIM4();
		UserTxBufferFS[0] = cmd;
		memcpy(UserTxBufferFS + 1, &temp, sizeof(uint16_t));
		CDC_Transmit_FS(UserTxBufferFS, 1 + sizeof(uint16_t));
		return (USBD_OK);
		//--------------------------------------------------------------------------
		// TODO:Прием калибровочной таблицы [0x0A][1-4][offset][count][data] 	answer:
	}
	else if (cmd == 0x0A)
	{
		if (*Len >= 2 && (Buf[1] == 0x01 || Buf[1] == 0x02 || Buf[1] == 0x03 || Buf[1] == 0x04))
		{
			if (Buf[1] == 0x01)
			{
				UserTxBufferFS[0] = cmd;
				UserTxBufferFS[1] = 0x01;
				// UserTxBufferFS[2] = getCRC_table_a_m12();
				printf("getCRC_table_a_m12 - %d \n", UserTxBufferFS[2]);

				//				UserTxBufferFS[1] = strlen(str);
				//				memcpy(UserTxBufferFS + 2, str, strlen(str));
				//				CDC_Transmit_FS(UserTxBufferFS, strlen(str) + 2);

				CDC_Transmit_FS(UserTxBufferFS, 2);
				return (USBD_OK);
			}
			else if (Buf[1] == 0x02)
			{
				HAL_GPIO_WritePin(Relay_GPIO_Port, Relay_Pin, GPIO_PIN_RESET);
				RelayState = 0x00;
				printf("RelayState:27V - %d \n", RelayState);
				SetAllDAC();

				UserTxBufferFS[0] = cmd;
				UserTxBufferFS[1] = 0x00; // успешно
				CDC_Transmit_FS(UserTxBufferFS, 2);
				return (USBD_OK);
			}
			else if (Buf[1] == 0x03)
			{
				HAL_GPIO_WritePin(Relay_GPIO_Port, Relay_Pin, GPIO_PIN_RESET);
				RelayState = 0x00;
				printf("RelayState:27V - %d \n", RelayState);
				SetAllDAC();

				UserTxBufferFS[0] = cmd;
				UserTxBufferFS[1] = 0x00; // успешно
				CDC_Transmit_FS(UserTxBufferFS, 2);
				return (USBD_OK);
			}
			else if (Buf[1] == 0x04)
			{
				HAL_GPIO_WritePin(Relay_GPIO_Port, Relay_Pin, GPIO_PIN_RESET);
				RelayState = 0x00;
				printf("RelayState:27V - %d \n", RelayState);
				SetAllDAC();

				UserTxBufferFS[0] = cmd;
				UserTxBufferFS[1] = 0x00; // успешно
				CDC_Transmit_FS(UserTxBufferFS, 2);
				return (USBD_OK);
			}
		}

		UserTxBufferFS[0] = cmd;
		UserTxBufferFS[1] = 0x00;

		tVal16 = GetDacA();
		memcpy(UserTxBufferFS + 2, &tVal16, sizeof(tVal16));
		tVal16 = GetDacB();
		memcpy(UserTxBufferFS + 4, &tVal16, sizeof(tVal16));

		CDC_Transmit_FS(UserTxBufferFS, 6);
		return (USBD_OK);
	}
		//--------------------------------------------------------------------------
	// TODO:Отправка CRC 1-4 таблицы [0x0B][1-4][CRC(1-4)]	answer:
	else if (cmd == 0x0B)
	{
		if (*Len >= 2 && (Buf[1] == 0x01 || Buf[1] == 0x02 || Buf[1] == 0x03 || Buf[1] == 0x04))
		{
			if (Buf[1] == 0x01)
			{
				UserTxBufferFS[0] = cmd;
				UserTxBufferFS[1] = 0x01;

				uint32_t crc_1 = getCRC_table_a_m12();//270814253
//				memcpy(UserTxBufferFS + 2, crc_1, sizeof(crc_1));
				
				printf("getCRC_table_a_m12 - %d \n", crc_1);

//				CDC_Transmit_FS(UserTxBufferFS, sizeof(crc_1) + 2);

				return (USBD_OK);
			}
			else if (Buf[1] == 0x02)
			{
				HAL_GPIO_WritePin(Relay_GPIO_Port, Relay_Pin, GPIO_PIN_RESET);
				RelayState = 0x00;
				printf("RelayState:27V - %d \n", RelayState);
				SetAllDAC();

				UserTxBufferFS[0] = cmd;
				UserTxBufferFS[1] = 0x00; // успешно
				CDC_Transmit_FS(UserTxBufferFS, 2);
				return (USBD_OK);
			}
			else if (Buf[1] == 0x03)
			{
				HAL_GPIO_WritePin(Relay_GPIO_Port, Relay_Pin, GPIO_PIN_RESET);
				RelayState = 0x00;
				printf("RelayState:27V - %d \n", RelayState);
				SetAllDAC();

				UserTxBufferFS[0] = cmd;
				UserTxBufferFS[1] = 0x00; // успешно
				CDC_Transmit_FS(UserTxBufferFS, 2);
				return (USBD_OK);
			}
			else if (Buf[1] == 0x04)
			{
				HAL_GPIO_WritePin(Relay_GPIO_Port, Relay_Pin, GPIO_PIN_RESET);
				RelayState = 0x00;
				printf("RelayState:27V - %d \n", RelayState);
				SetAllDAC();

				UserTxBufferFS[0] = cmd;
				UserTxBufferFS[1] = 0x00; // успешно
				CDC_Transmit_FS(UserTxBufferFS, 2);
				return (USBD_OK);
			}
		}

		UserTxBufferFS[0] = cmd;
		UserTxBufferFS[1] = 0x00;

		UserTxBufferFS[0] = cmd;

		UserTxBufferFS[1] = RelayState;
		tVal16 = GetDacA();
		memcpy(UserTxBufferFS + 2, &tVal16, sizeof(tVal16));
		tVal16 = GetDacB();
		memcpy(UserTxBufferFS + 4, &tVal16, sizeof(tVal16));

		CDC_Transmit_FS(UserTxBufferFS, 6);
		return (USBD_OK);

		//--------------------------------------------------------------------------
		// TODO:Прием калибровочной таблицы [0x0C][Длина][???]
	}
	else if (cmd == 0x0C)
	{
		UserTxBufferFS[0] = cmd;

		UserTxBufferFS[1] = RelayState;
		tVal16 = GetDacA();
		memcpy(UserTxBufferFS + 2, &tVal16, sizeof(tVal16));
		tVal16 = GetDacB();
		memcpy(UserTxBufferFS + 4, &tVal16, sizeof(tVal16));

		CDC_Transmit_FS(UserTxBufferFS, 6);
		return (USBD_OK);
		//--------------------------------------------------------------------------
		// TODO:Запись во флеш калибровочной таблицы [0x0D] data: 1B (0x00 - успешно; 0x01 - ошибка при записи)	answer: 0x0D + 1B status
	}
	else if (cmd == 0x0D)
	{
		UserTxBufferFS[0] = cmd;
		//		UserTxBufferFS[1] = flash_write();

		// Сделать функцию записи во флеш по флагу?! сравнивать CRC?

		UserTxBufferFS[1] = RelayState;
		tVal16 = GetDacA();
		memcpy(UserTxBufferFS + 2, &tVal16, sizeof(tVal16));
		tVal16 = GetDacB();
		memcpy(UserTxBufferFS + 4, &tVal16, sizeof(tVal16));

		CDC_Transmit_FS(UserTxBufferFS, 6);
		return (USBD_OK);
	}
	//--------------------------------------------------------------------------
	return (USBD_OK);
	/* USER CODE END 6 */
}

/**
  * @brief  CDC_Transmit_FS
  *         Data to send over USB IN endpoint are sent over CDC interface
  *         through this function.
  *         @note
  *
  *
  * @param  Buf: Buffer of data to be sent
  * @param  Len: Number of data to be sent (in bytes)
  * @retval USBD_OK if all operations are OK else USBD_FAIL or USBD_BUSY
  */
uint8_t CDC_Transmit_FS(uint8_t *Buf, uint16_t Len)
{
	uint8_t result = USBD_OK;
	/* USER CODE BEGIN 7 */
	USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef *)hUsbDeviceFS.pClassData;
	if (hcdc->TxState != 0)
	{
		return USBD_BUSY;
	}
	USBD_CDC_SetTxBuffer(&hUsbDeviceFS, Buf, Len);
	result = USBD_CDC_TransmitPacket(&hUsbDeviceFS);
	/* USER CODE END 7 */
	return result;
}

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */

/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
