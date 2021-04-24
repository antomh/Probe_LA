/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "DAC_AD5322.h"
#include "logic_calibration_table.h"

#include "usbd_cdc_if.h"
#include "string.h" // для функции strlen()

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

//--------------------------------------------------------------------------
// Тестовые сборки
#define DEBUG_SWO				1
#define USE_FULL_ASSERT			1
#define TEST_UID				1


#define TEST_DAC 				1
#define TEST_READ_BTN			1 //TODO: данная реализация плохо отрабатывает!
#define TEST_TIM_CAPTURE		1
#define TEST_ADC 				1
#define USB_RESET				0
#define DWT_INIT				1

#define TEST_FLASH_TABLE		1

//--------------------------------------------------------------------------
//DONE: В цикле не прерывно идет установка цапов! Формируя цифровой шум DONE: убарно из цикла
//DONE: Ошибка в работе цап. При переключение в m27 цап принимает значения, но не устанавливет их! DONE: добавлена в библеотеку цап двоойна отправка команды, проблема устранена
//DONE: set 4v-> set 5v -> M27 -> set 4v -> M12 -> set 6v (err:DAC не установил значения, но в ядре значения имеются!!!) DONE: изза ошибки 3. = добалена функция отправки значений при устанвоке реле
//DONE: Доработать алгоритм установки реле! м.б. добавить в функции реле установку ЦАП по обоим каналам?
//DONE: Перенос проекта с сохранением во флеш в этот проект.
//DONE: Добавить серийный номер в щуп
//==>
//TODO: Добавить калибровочную таблицу в проект через t.py формируется - необходимо заполнять значениями в logic_calibration_table.с

//TODO: Работа с калибровочной таблицей
//TODO: получить значение V , Поиск по значению напряжения V значение в калибровочной таблице VDAC
//TODO: При остутсвтие значения в таблице произвести интерполяцию

//TODO: По команде с VCP перезаписать таблицу
//--------------------------------------------------------------------------

//TODO: по какой то причине в этом проекте не работает CRC!!!
//TODO: Реализовать процедуру изменения калибровочной таблицы через VCP!
//TODO: Сформировать калиброчную таблицу через функцию
//TODO: роверить первое состоянеи первоначальное состояние реле 27V
//--------------------------------------------------------------------------
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */


/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

CRC_HandleTypeDef hcrc;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

/* USER CODE BEGIN PV */
//--------------------------------------------------------------------------
#if USB_RESET
void USB_Reset(); не работает без использвоания транзистора на D+
#endif	/* USB_RESET */
//--------------------------------------------------------------------------
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM4_Init(void);
static void MX_CRC_Init(void);
/* USER CODE BEGIN PFP */
//**************************************************************************
#if DEBUG_SWO
int _write(int32_t file, uint8_t *ptr, int32_t len) {
	for (int i = 0; i < len; i++) {
		ITM_SendChar(*ptr++);
	}
	return len;
}

#endif	/* DEBUG_SWO */
//**************************************************************************
#if  TEST_UID
// Чтение UID контроллера
//#define UID_BASE 0x1FFFF7E8
uint16_t *idBase0 = (uint16_t*) (UID_BASE);
uint16_t *idBase1 = (uint16_t*) (UID_BASE + 0x02);
uint32_t *idBase2 = (uint32_t*) (UID_BASE + 0x04);
uint32_t *idBase3 = (uint32_t*) (UID_BASE + 0x08);
char buffer[64] = { 0, };
#endif	/* TEST_UID */
//**************************************************************************
#if  TEST_DAC

uint16_t VDAC_A = 2154;
uint16_t VDAC_B = 2154;

void SetDacA(uint16_t da) {
	VDAC_A = da;
	DAC_AD5322_Ch1(&hspi1, VDAC_A);
}
void SetDacB(uint16_t db) {
	VDAC_B = db;
	DAC_AD5322_Ch2(&hspi1, VDAC_B);
}
void SetAllDAC() {
	DAC_AD5322_Ch1Ch2(&hspi1,VDAC_A,VDAC_B);
}
uint16_t GetDacA() {
	return VDAC_A;
}
uint16_t GetDacB() {
	return VDAC_B;
}
#endif	/* TEST_DAC */
//**************************************************************************
#if  TEST_READ_BTN
#define KEY_LONG_DELAY	1000
//PB12
uint8_t short_state1 = 0;
uint8_t long_state1 = 0;
uint32_t time_key1 = 0;

uint8_t btn1_long_rd = 0;
uint8_t btn1_short_rd = 0;

//PB13
uint8_t short_state2 = 0;
uint8_t long_state2 = 0;
uint32_t time_key2 = 0;

uint8_t btn2_long_rd = 0;
uint8_t btn2_short_rd = 0;

//PB14
uint8_t short_state3 = 0;
uint8_t long_state3 = 0;
uint32_t time_key3 = 0;

uint8_t btn3_long_rd = 0;
uint8_t btn3_short_rd = 0;
//--------------------------------------------------------------------------
uint8_t GetBtnRunState() {
	// 0x00 - не нажата; 0x01 - короткое нажатие; 0x02 - длительное нажатие
	if (btn1_short_rd == 0x00 && btn1_long_rd == 0x00) {
		btn1_long_rd	 = 0;
		btn1_short_rd	 = 0;
		return 0x00;
	}
	if (btn1_short_rd == 0x01 && btn1_long_rd == 0x00) {
		btn1_long_rd 	= 0;
		btn1_short_rd 	= 0;
		return 0x01;
	}
	if (btn1_short_rd == 0x00 && btn1_long_rd == 0x01) {
		btn1_long_rd 	= 0;
		btn1_short_rd 	= 0;
		return 0x02;
	}

	btn1_long_rd 		= 0;
	btn1_short_rd	 	= 0;

//	if (short_state1 == 0x00 && long_state1 == 0x00)	return 0x00;
//	if (short_state1 == 0x01 && long_state1 == 0x00)	return 0x01;
//	if (short_state1 == 0x00 && long_state1 == 0x01)	return 0x02;
	return 0x00;
}
//--------------------------------------------------------------------------
uint8_t GetBtnUpState() {
	// 0x00 - не нажата; 0x01 - короткое нажатие; 0x02 - длительное нажатие
	if (btn2_short_rd == 0x00 && btn2_long_rd == 0x00) {
		btn2_long_rd	 = 0;
		btn2_short_rd	 = 0;
		return 0x00;
	}
	if (btn2_short_rd == 0x01 && btn2_long_rd == 0x00) {
		btn2_long_rd 	= 0;
		btn2_short_rd 	= 0;
		return 0x01;
	}
	if (btn2_short_rd == 0x00 && btn2_long_rd == 0x01) {
		btn2_long_rd 	= 0;
		btn2_short_rd 	= 0;
		return 0x02;
	}

	btn2_long_rd 		= 0;
	btn2_short_rd	 	= 0;
//	// 0x00 - не нажата; 0x01 - короткое нажатие; 0x02 - длительное нажатие
//	if (short_state2 == 0x00 && long_state2 == 0x00)	return 0x00;
//	if (short_state2 == 0x01 && long_state2 == 0x00)	return 0x01;
//	if (short_state2 == 0x00 && long_state2 == 0x01)	return 0x02;
	return 0x00;
}
//--------------------------------------------------------------------------
uint8_t GetBtnDownState() {
	// 0x00 - не нажата; 0x01 - короткое нажатие; 0x02 - длительное нажатие
	if (btn3_short_rd == 0x00 && btn3_long_rd == 0x00) {
		btn3_long_rd	 = 0;
		btn3_short_rd	 = 0;
		return 0x00;
	}
	if (btn3_short_rd == 0x01 && btn3_long_rd == 0x00) {
		btn3_long_rd 	= 0;
		btn3_short_rd 	= 0;
		return 0x01;
	}
	if (btn3_short_rd == 0x00 && btn3_long_rd == 0x01) {
		btn3_long_rd 	= 0;
		btn3_short_rd 	= 0;
		return 0x02;
	}

	btn3_long_rd 		= 0;
	btn3_short_rd	 	= 0;
//	if (short_state3 == 0x00 && long_state3 == 0x00)	return 0x00;
//	if (short_state3 == 0x01 && long_state3 == 0x00)	return 0x01;
//	if (short_state3 == 0x00 && long_state3 == 0x01)	return 0x02;
	return 0x00;
}
//--------------------------------------------------------------------------

#endif	/* TEST_READ_BTN */
//**************************************************************************
#if  TEST_TIM_CAPTURE
volatile uint8_t timWork = 0;
volatile uint8_t count_overflowTIM3 = 0;
volatile uint8_t count_overflowTIM4 = 0;

volatile uint16_t g_vTIM3_PB4 = 0;
volatile uint16_t g_vTIM4_PB6 = 0;

char trans2_str[64] = {0,};
//--------------------------------------------------------------------------
void EnableTIM3_PB4(){
	 timWork = 1 ;
}
uint16_t GetTIM3(){
	return g_vTIM3_PB4;
}
void resValTIM3_PB4(){
	g_vTIM3_PB4 = 0;
}
//--------------------------------------------------------------------------
void EnableTIM4_PB6(){
	 timWork = 0 ;
}
uint16_t GetTIM4(){
	return g_vTIM4_PB6;
}
void resValTIM4_PB6(){
	g_vTIM4_PB6 = 0;
}
//--------------------------------------------------------------------------
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
	uint16_t periodTIM3, pulseWidthTIM3, periodTIM4, pulseWidthTIM4;

	if (timWork) {
		if (htim->Instance == TIM3) {
			if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
				periodTIM3 = HAL_TIM_ReadCapturedValue(&htim3, TIM_CHANNEL_1);
				pulseWidthTIM3 = HAL_TIM_ReadCapturedValue(&htim3,
						TIM_CHANNEL_2);

				TIM3->CNT = 0;

				int16_t deltaTIM3 = (int16_t) periodTIM3
						- (int16_t) pulseWidthTIM3;
				deltaTIM3 = (deltaTIM3 < 0) ? (-1 * deltaTIM3) : deltaTIM3;
				g_vTIM3_PB4 = deltaTIM3;

			}
		}
	} else {
		if (htim->Instance == TIM4) {
			if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
				periodTIM4 = HAL_TIM_ReadCapturedValue(&htim4, TIM_CHANNEL_1);
				pulseWidthTIM4 = HAL_TIM_ReadCapturedValue(&htim4,
						TIM_CHANNEL_2);

				TIM4->CNT = 0;

				int16_t deltaTIM4 = (int16_t) periodTIM4
						- (int16_t) pulseWidthTIM4;
				deltaTIM4 = (deltaTIM4 < 0) ? (-1 * deltaTIM4) : deltaTIM4;
				g_vTIM4_PB6 = deltaTIM4;

			}
		}
	}

}



#endif	/* TEST_TIM_CAPTURE */
//**************************************************************************

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//**************************************************************************
#if TEST_ADC
volatile uint16_t g_VADC = 0;

uint16_t GetADC(){
	return g_VADC;
}
//--------------------------------------------------------------------------
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    if(hadc->Instance == ADC1) 				//check if the interrupt comes from ACD1
    {
    	g_VADC = HAL_ADC_GetValue(&hadc1); // глобальная переменна g_VADC вычитывается
    }
}
#endif	/* TEST_ADC */
//**************************************************************************
#if USB_RESET
void USB_RESET(void){

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // reset USB DP (D+)
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // инициализируем пин DP как выход
    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET); // прижимаем DP к "земле"
    for(uint16_t i = 0; i < 10000; i++) {}; // немного ждём

    // переинициализируем пин для работы с USB
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    for(uint16_t i = 0; i < 10000; i++) {}; // немного ждём

  }
#endif	/* USB_RESET */
//**************************************************************************
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
//--------------------------------------------------------------------------
#if DWT_INIT
	DWT_Init();
#endif	/* DWT_INIT */
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------


  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_USB_DEVICE_Init();
  MX_ADC1_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_CRC_Init();
  /* USER CODE BEGIN 2 */
  //**************************************************************************
#if  TEST_UID
	sprintf(buffer, "UID %x-%x-%lx-%lx\n", *idBase0, *idBase1, *idBase2, *idBase3);
	printf((uint8_t*)buffer);
#endif	/* TEST_UID */

	//**************************************************************************
#if	TEST_TIM_CAPTURE
	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_2);
	HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_2);
#endif	/* TEST_TIM_CAPTURE */
//--------------------------------------------------------------------------
#if	TEST_DAC
	SetAllDAC();
#endif	/* TEST_DAC */
	//**************************************************************************
#if	TEST_ADC
	HAL_ADCEx_Calibration_Start(&hadc1);
	HAL_ADC_Start_IT(&hadc1);

#endif	/* TEST_ADC */
//**************************************************************************
#if  TEST_FLASH_TABLE
//--------------------------------------------------------------------------
#define FLASH_TABLE_START_ADDR		ADDR_FLASH_PAGE_127
#define FLASH_TABLE_STOP_ADDR		FLASH_TABLE_START_ADDR+FLASH_PAGE_SIZE
//--------------------------------------------------------------------------
#define MAGIC_KEY_DEFINE			0x48151623
#define HARDWIRE_DEFINE 			0x06
#define FIRMWARE_DEFINE 			0x05
#define SN_DEFINE 					0x1121001
//--------------------------------------------------------------------------
#define MAX_VAL_M12 				88//	шаг 0,2В в диапозоне [-5:12:0,2] 85  TODO:найти что за 3 значения?!
#define MAX_VAL_M27 				163//	шаг 0,2В в диапозоне [-30:30:0,2] 163*0.2= 32,6
//--------------------------------------------------------------------------

	typedef struct // 							4+4+4+176+176+326+326 = 1016 байт
	{
		uint16_t Hardwire; //					2 байта
		uint16_t Firmware; //					2 байта
		uint32_t SN; //							4 байта

		uint32_t MagicNum; //0x4815162342		4 байта ==>4+4+2+2 = 12

		uint16_t dacValA_m12[MAX_VAL_M12]; //	88*2 = 176 байта
		uint16_t dacValB_m12[MAX_VAL_M12]; //	88*2 = 176 байта
		uint16_t dacValA_m27[MAX_VAL_M27]; //	163*2 = 326 байта
		uint16_t dacValB_m27[MAX_VAL_M27]; //	163*2 = 326 байта ==> 1004 + 12 = 1016

	} Table_t;

	struct FLASH_Sector {
		uint32_t data[256 - 2]; // 	254* 4 = 1016 байта (1016 байт)
		uint32_t NWrite; //			4 байта
		uint32_t CheckSum; //		4 байта ==>1016 + 4 + 4 = 1024
	};

	union NVRAM {
		Table_t calibration_table; //			1016 байт
		struct FLASH_Sector sector; //			1024 байт

		uint32_t data32[256]; // 			1024 байт
		uint8_t data16[256 * 2]; // 		1024 байт
		uint8_t data8[256 * 4]; // 			1024 байт
	};
	//										1024 байт

//--------------------------------------------------------------------------
	union NVRAM DevNVRAM;
//--------------------------------------------------------------------------
void crete_calibration_table(union NVRAM *DevNVRAM) {
    DevNVRAM->calibration_table.dacValA_m12[0] = 0x0;
    DevNVRAM->calibration_table.dacValA_m12[1] = 0x189;
    DevNVRAM->calibration_table.dacValA_m12[2] = 0x31d;
    DevNVRAM->calibration_table.dacValA_m12[3] = 0x223;
    DevNVRAM->calibration_table.dacValA_m12[4] = 0x21f;
    DevNVRAM->calibration_table.dacValA_m12[5] = 0x19d;
    DevNVRAM->calibration_table.dacValA_m12[6] = 0x27e;
    DevNVRAM->calibration_table.dacValA_m12[7] = 0x297;
    DevNVRAM->calibration_table.dacValA_m12[8] = 0x27e;
    DevNVRAM->calibration_table.dacValA_m12[9] = 0x297;
    DevNVRAM->calibration_table.dacValA_m12[10] = 0x1a1;
    DevNVRAM->calibration_table.dacValA_m12[11] = 0x223;
    DevNVRAM->calibration_table.dacValA_m12[12] = 0x21e;
    DevNVRAM->calibration_table.dacValA_m12[13] = 0x1b6;
    DevNVRAM->calibration_table.dacValA_m12[14] = 0x297;
    DevNVRAM->calibration_table.dacValA_m12[15] = 0x188;
    DevNVRAM->calibration_table.dacValA_m12[16] = 0x223;
    DevNVRAM->calibration_table.dacValA_m12[17] = 0x1a6;
    DevNVRAM->calibration_table.dacValA_m12[18] = 0x233;
    DevNVRAM->calibration_table.dacValA_m12[19] = 0x29b;
    DevNVRAM->calibration_table.dacValA_m12[20] = 0x21e;
    DevNVRAM->calibration_table.dacValA_m12[21] = 0x1b6;
    DevNVRAM->calibration_table.dacValA_m12[22] = 0x2e6;
    DevNVRAM->calibration_table.dacValA_m12[23] = 0x233;
    DevNVRAM->calibration_table.dacValA_m12[24] = 0x184;
    DevNVRAM->calibration_table.dacValA_m12[25] = 0x27e;
    DevNVRAM->calibration_table.dacValA_m12[26] = 0x855;
    DevNVRAM->calibration_table.dacValA_m12[27] = 0x877;
    DevNVRAM->calibration_table.dacValA_m12[28] = 0x8b1;
    DevNVRAM->calibration_table.dacValA_m12[29] = 0x8cb;
    DevNVRAM->calibration_table.dacValA_m12[30] = 0x8fc;
    DevNVRAM->calibration_table.dacValA_m12[31] = 0x960;
    DevNVRAM->calibration_table.dacValA_m12[32] = 0x953;
    DevNVRAM->calibration_table.dacValA_m12[33] = 0x992;
    DevNVRAM->calibration_table.dacValA_m12[34] = 0x9c4;
    DevNVRAM->calibration_table.dacValA_m12[35] = 0x9d6;
    DevNVRAM->calibration_table.dacValA_m12[36] = 0xa02;
    DevNVRAM->calibration_table.dacValA_m12[37] = 0xa2f;
    DevNVRAM->calibration_table.dacValA_m12[38] = 0x9dd;
    DevNVRAM->calibration_table.dacValA_m12[39] = 0xa89;
    DevNVRAM->calibration_table.dacValA_m12[40] = 0xab4;
    DevNVRAM->calibration_table.dacValA_m12[41] = 0xae1;
    DevNVRAM->calibration_table.dacValA_m12[42] = 0xb0b;
    DevNVRAM->calibration_table.dacValA_m12[43] = 0xb36;
    DevNVRAM->calibration_table.dacValA_m12[44] = 0xb8b;
    DevNVRAM->calibration_table.dacValA_m12[45] = 0xb8f;
    DevNVRAM->calibration_table.dacValA_m12[46] = 0xbd1;
    DevNVRAM->calibration_table.dacValA_m12[47] = 0xbe6;
    DevNVRAM->calibration_table.dacValA_m12[48] = 0xc12;
    DevNVRAM->calibration_table.dacValA_m12[49] = 0xc4e;
    DevNVRAM->calibration_table.dacValA_m12[50] = 0xc69;
    DevNVRAM->calibration_table.dacValA_m12[51] = 0xc96;
    DevNVRAM->calibration_table.dacValA_m12[52] = 0xcd5;
    DevNVRAM->calibration_table.dacValA_m12[53] = 0xcee;
    DevNVRAM->calibration_table.dacValA_m12[54] = 0xd19;
    DevNVRAM->calibration_table.dacValA_m12[55] = 0xc98;
    DevNVRAM->calibration_table.dacValA_m12[56] = 0xd70;
    DevNVRAM->calibration_table.dacValA_m12[57] = 0xd99;
    DevNVRAM->calibration_table.dacValA_m12[58] = 0xdb7;
    DevNVRAM->calibration_table.dacValA_m12[59] = 0xdca;
    DevNVRAM->calibration_table.dacValA_m12[60] = 0xdd8;
    DevNVRAM->calibration_table.dacValA_m12[61] = 0xddc;
    DevNVRAM->calibration_table.dacValA_m12[62] = 0xde9;
    DevNVRAM->calibration_table.dacValA_m12[63] = 0xded;
    DevNVRAM->calibration_table.dacValA_m12[64] = 0xdf4;
    DevNVRAM->calibration_table.dacValA_m12[65] = 0xdf9;
    DevNVRAM->calibration_table.dacValA_m12[66] = 0xdfc;
    DevNVRAM->calibration_table.dacValA_m12[67] = 0xdf7;
    DevNVRAM->calibration_table.dacValA_m12[68] = 0xdf8;
    DevNVRAM->calibration_table.dacValA_m12[69] = 0xdfa;
    DevNVRAM->calibration_table.dacValA_m12[70] = 0xdfc;
    DevNVRAM->calibration_table.dacValA_m12[71] = 0xdfe;
    DevNVRAM->calibration_table.dacValA_m12[72] = 0xe01;
    DevNVRAM->calibration_table.dacValA_m12[73] = 0xe01;
    DevNVRAM->calibration_table.dacValA_m12[74] = 0xe06;
    DevNVRAM->calibration_table.dacValA_m12[75] = 0xe06;
    DevNVRAM->calibration_table.dacValA_m12[76] = 0xe0a;
    DevNVRAM->calibration_table.dacValA_m12[77] = 0xe0e;
    DevNVRAM->calibration_table.dacValA_m12[78] = 0xe05;
    DevNVRAM->calibration_table.dacValA_m12[79] = 0xe01;
    DevNVRAM->calibration_table.dacValA_m12[80] = 0xe09;
    DevNVRAM->calibration_table.dacValA_m12[81] = 0x7d0;
    DevNVRAM->calibration_table.dacValA_m12[82] = 0xe06;
    DevNVRAM->calibration_table.dacValA_m12[83] = 0x7d0;
    DevNVRAM->calibration_table.dacValA_m12[84] = 0xe06;
    DevNVRAM->calibration_table.dacValA_m12[85] = 0xe00;
    DevNVRAM->calibration_table.dacValA_m12[86] = 0xdfe;
    DevNVRAM->calibration_table.dacValA_m12[87] = 0x1000;

    DevNVRAM->calibration_table.dacValB_m12[0] = 0x0;
    DevNVRAM->calibration_table.dacValB_m12[1] = 0x1bb;
    DevNVRAM->calibration_table.dacValB_m12[2] = 0x1ed;
    DevNVRAM->calibration_table.dacValB_m12[3] = 0x251;
    DevNVRAM->calibration_table.dacValB_m12[4] = 0x1bb;
    DevNVRAM->calibration_table.dacValB_m12[5] = 0x1ed;
    DevNVRAM->calibration_table.dacValB_m12[6] = 0x2ce;
    DevNVRAM->calibration_table.dacValB_m12[7] = 0x1d4;
    DevNVRAM->calibration_table.dacValB_m12[8] = 0x1f2;
    DevNVRAM->calibration_table.dacValB_m12[9] = 0x1d9;
    DevNVRAM->calibration_table.dacValB_m12[10] = 0x1bc;
    DevNVRAM->calibration_table.dacValB_m12[11] = 0x1bb;
    DevNVRAM->calibration_table.dacValB_m12[12] = 0x1f3;
    DevNVRAM->calibration_table.dacValB_m12[13] = 0x1d9;
    DevNVRAM->calibration_table.dacValB_m12[14] = 0x1ed;
    DevNVRAM->calibration_table.dacValB_m12[15] = 0x1f3;
    DevNVRAM->calibration_table.dacValB_m12[16] = 0x1c0;
    DevNVRAM->calibration_table.dacValB_m12[17] = 0x1c1;
    DevNVRAM->calibration_table.dacValB_m12[18] = 0x1c0;
    DevNVRAM->calibration_table.dacValB_m12[19] = 0x2ec;
    DevNVRAM->calibration_table.dacValB_m12[20] = 0x1d4;
    DevNVRAM->calibration_table.dacValB_m12[21] = 0x251;
    DevNVRAM->calibration_table.dacValB_m12[22] = 0x1d4;
    DevNVRAM->calibration_table.dacValB_m12[23] = 0x1d4;
    DevNVRAM->calibration_table.dacValB_m12[24] = 0x2ce;
    DevNVRAM->calibration_table.dacValB_m12[25] = 0x1cb;
    DevNVRAM->calibration_table.dacValB_m12[26] = 0x857;
    DevNVRAM->calibration_table.dacValB_m12[27] = 0x877;
    DevNVRAM->calibration_table.dacValB_m12[28] = 0x8a4;
    DevNVRAM->calibration_table.dacValB_m12[29] = 0x8cf;
    DevNVRAM->calibration_table.dacValB_m12[30] = 0x8fb;
    DevNVRAM->calibration_table.dacValB_m12[31] = 0x926;
    DevNVRAM->calibration_table.dacValB_m12[32] = 0x954;
    DevNVRAM->calibration_table.dacValB_m12[33] = 0x980;
    DevNVRAM->calibration_table.dacValB_m12[34] = 0x9ac;
    DevNVRAM->calibration_table.dacValB_m12[35] = 0x9d8;
    DevNVRAM->calibration_table.dacValB_m12[36] = 0xa04;
    DevNVRAM->calibration_table.dacValB_m12[37] = 0xa30;
    DevNVRAM->calibration_table.dacValB_m12[38] = 0xa5b;
    DevNVRAM->calibration_table.dacValB_m12[39] = 0xa86;
    DevNVRAM->calibration_table.dacValB_m12[40] = 0xab2;
    DevNVRAM->calibration_table.dacValB_m12[41] = 0xadf;
    DevNVRAM->calibration_table.dacValB_m12[42] = 0xb0b;
    DevNVRAM->calibration_table.dacValB_m12[43] = 0xb36;
    DevNVRAM->calibration_table.dacValB_m12[44] = 0xb63;
    DevNVRAM->calibration_table.dacValB_m12[45] = 0xb8e;
    DevNVRAM->calibration_table.dacValB_m12[46] = 0xbea;
    DevNVRAM->calibration_table.dacValB_m12[47] = 0xafd;
    DevNVRAM->calibration_table.dacValB_m12[48] = 0xb91;
    DevNVRAM->calibration_table.dacValB_m12[49] = 0xc3d;
    DevNVRAM->calibration_table.dacValB_m12[50] = 0xc69;
    DevNVRAM->calibration_table.dacValB_m12[51] = 0xbbe;
    DevNVRAM->calibration_table.dacValB_m12[52] = 0xcc2;
    DevNVRAM->calibration_table.dacValB_m12[53] = 0xd20;
    DevNVRAM->calibration_table.dacValB_m12[54] = 0xd19;
    DevNVRAM->calibration_table.dacValB_m12[55] = 0xd44;
    DevNVRAM->calibration_table.dacValB_m12[56] = 0xd6e;
    DevNVRAM->calibration_table.dacValB_m12[57] = 0xd92;
    DevNVRAM->calibration_table.dacValB_m12[58] = 0xd17;
    DevNVRAM->calibration_table.dacValB_m12[59] = 0xdc5;
    DevNVRAM->calibration_table.dacValB_m12[60] = 0xdc2;
    DevNVRAM->calibration_table.dacValB_m12[61] = 0xdcb;
    DevNVRAM->calibration_table.dacValB_m12[62] = 0xdd4;
    DevNVRAM->calibration_table.dacValB_m12[63] = 0xdd9;
    DevNVRAM->calibration_table.dacValB_m12[64] = 0xe09;
    DevNVRAM->calibration_table.dacValB_m12[65] = 0xc6a;
    DevNVRAM->calibration_table.dacValB_m12[66] = 0xbbc;
    DevNVRAM->calibration_table.dacValB_m12[67] = 0xc5d;
    DevNVRAM->calibration_table.dacValB_m12[68] = 0xc4f;
    DevNVRAM->calibration_table.dacValB_m12[69] = 0xcde;
    DevNVRAM->calibration_table.dacValB_m12[70] = 0xc52;
    DevNVRAM->calibration_table.dacValB_m12[71] = 0xdde;
    DevNVRAM->calibration_table.dacValB_m12[72] = 0xdff;
    DevNVRAM->calibration_table.dacValB_m12[73] = 0xe05;
    DevNVRAM->calibration_table.dacValB_m12[74] = 0xe0b;
    DevNVRAM->calibration_table.dacValB_m12[75] = 0xc80;
    DevNVRAM->calibration_table.dacValB_m12[76] = 0xc1f;
    DevNVRAM->calibration_table.dacValB_m12[77] = 0xe0d;
    DevNVRAM->calibration_table.dacValB_m12[78] = 0xc77;
    DevNVRAM->calibration_table.dacValB_m12[79] = 0xd49;
    DevNVRAM->calibration_table.dacValB_m12[80] = 0xd55;
    DevNVRAM->calibration_table.dacValB_m12[81] = 0xcf5;
    DevNVRAM->calibration_table.dacValB_m12[82] = 0xe14;
    DevNVRAM->calibration_table.dacValB_m12[83] = 0xd7f;
    DevNVRAM->calibration_table.dacValB_m12[84] = 0xd2a;
    DevNVRAM->calibration_table.dacValB_m12[85] = 0xd51;
    DevNVRAM->calibration_table.dacValB_m12[86] = 0xde0;
    DevNVRAM->calibration_table.dacValB_m12[87] = 0x1000;

    DevNVRAM->calibration_table.dacValA_m27[0] = 0x0;
    DevNVRAM->calibration_table.dacValA_m27[1] = 0x1f1;
    DevNVRAM->calibration_table.dacValA_m27[2] = 0x1a6;
    DevNVRAM->calibration_table.dacValA_m27[3] = 0x21e;
    DevNVRAM->calibration_table.dacValA_m27[4] = 0x233;
    DevNVRAM->calibration_table.dacValA_m27[5] = 0x27e;
    DevNVRAM->calibration_table.dacValA_m27[6] = 0x27e;
    DevNVRAM->calibration_table.dacValA_m27[7] = 0x1bb;
    DevNVRAM->calibration_table.dacValA_m27[8] = 0x1bb;
    DevNVRAM->calibration_table.dacValA_m27[9] = 0x1bb;
    DevNVRAM->calibration_table.dacValA_m27[10] = 0x477;
    DevNVRAM->calibration_table.dacValA_m27[11] = 0x5a3;
    DevNVRAM->calibration_table.dacValA_m27[12] = 0x1c4;
    DevNVRAM->calibration_table.dacValA_m27[13] = 0x1bb;
    DevNVRAM->calibration_table.dacValA_m27[14] = 0x1bb;
    DevNVRAM->calibration_table.dacValA_m27[15] = 0x29c;
    DevNVRAM->calibration_table.dacValA_m27[16] = 0x1bf;
    DevNVRAM->calibration_table.dacValA_m27[17] = 0x1bb;
    DevNVRAM->calibration_table.dacValA_m27[18] = 0x386;
    DevNVRAM->calibration_table.dacValA_m27[19] = 0x1bf;
    DevNVRAM->calibration_table.dacValA_m27[20] = 0x1bb;
    DevNVRAM->calibration_table.dacValA_m27[21] = 0x283;
    DevNVRAM->calibration_table.dacValA_m27[22] = 0x37d;
    DevNVRAM->calibration_table.dacValA_m27[23] = 0x283;
    DevNVRAM->calibration_table.dacValA_m27[24] = 0x37d;
    DevNVRAM->calibration_table.dacValA_m27[25] = 0x37d;
    DevNVRAM->calibration_table.dacValA_m27[26] = 0x843;
    DevNVRAM->calibration_table.dacValA_m27[27] = 0x843;
    DevNVRAM->calibration_table.dacValA_m27[28] = 0x83e;
    DevNVRAM->calibration_table.dacValA_m27[29] = 0x869;
    DevNVRAM->calibration_table.dacValA_m27[30] = 0x870;
    DevNVRAM->calibration_table.dacValA_m27[31] = 0x877;
    DevNVRAM->calibration_table.dacValA_m27[32] = 0x7d9;
    DevNVRAM->calibration_table.dacValA_m27[33] = 0x7e3;
    DevNVRAM->calibration_table.dacValA_m27[34] = 0x864;
    DevNVRAM->calibration_table.dacValA_m27[35] = 0x800;
    DevNVRAM->calibration_table.dacValA_m27[36] = 0x864;
    DevNVRAM->calibration_table.dacValA_m27[37] = 0x828;
    DevNVRAM->calibration_table.dacValA_m27[38] = 0x8cc;
    DevNVRAM->calibration_table.dacValA_m27[39] = 0x8d2;
    DevNVRAM->calibration_table.dacValA_m27[40] = 0x7fc;
    DevNVRAM->calibration_table.dacValA_m27[41] = 0x864;
    DevNVRAM->calibration_table.dacValA_m27[42] = 0x7fc;
    DevNVRAM->calibration_table.dacValA_m27[43] = 0x8ff;
    DevNVRAM->calibration_table.dacValA_m27[44] = 0x87e;
    DevNVRAM->calibration_table.dacValA_m27[45] = 0x834;
    DevNVRAM->calibration_table.dacValA_m27[46] = 0x828;
    DevNVRAM->calibration_table.dacValA_m27[47] = 0x847;
    DevNVRAM->calibration_table.dacValA_m27[48] = 0x800;
    DevNVRAM->calibration_table.dacValA_m27[49] = 0x87d;
    DevNVRAM->calibration_table.dacValA_m27[50] = 0x94a;
    DevNVRAM->calibration_table.dacValA_m27[51] = 0x977;
    DevNVRAM->calibration_table.dacValA_m27[52] = 0x7de;
    DevNVRAM->calibration_table.dacValA_m27[53] = 0x864;
    DevNVRAM->calibration_table.dacValA_m27[54] = 0x974;
    DevNVRAM->calibration_table.dacValA_m27[55] = 0x90f;
    DevNVRAM->calibration_table.dacValA_m27[56] = 0x8dd;
    DevNVRAM->calibration_table.dacValA_m27[57] = 0x874;
    DevNVRAM->calibration_table.dacValA_m27[58] = 0x7d4;
    DevNVRAM->calibration_table.dacValA_m27[59] = 0x7e3;
    DevNVRAM->calibration_table.dacValA_m27[60] = 0x7e8;
    DevNVRAM->calibration_table.dacValA_m27[61] = 0x914;
    DevNVRAM->calibration_table.dacValA_m27[62] = 0x9d3;
    DevNVRAM->calibration_table.dacValA_m27[63] = 0x919;
    DevNVRAM->calibration_table.dacValA_m27[64] = 0x8fb;
    DevNVRAM->calibration_table.dacValA_m27[65] = 0x7e4;
    DevNVRAM->calibration_table.dacValA_m27[66] = 0x86b;
    DevNVRAM->calibration_table.dacValA_m27[67] = 0x814;
    DevNVRAM->calibration_table.dacValA_m27[68] = 0x823;
    DevNVRAM->calibration_table.dacValA_m27[69] = 0x826;
    DevNVRAM->calibration_table.dacValA_m27[70] = 0x8af;
    DevNVRAM->calibration_table.dacValA_m27[71] = 0x804;
    DevNVRAM->calibration_table.dacValA_m27[72] = 0xa44;
    DevNVRAM->calibration_table.dacValA_m27[73] = 0x7ef;
    DevNVRAM->calibration_table.dacValA_m27[74] = 0x8f0;
    DevNVRAM->calibration_table.dacValA_m27[75] = 0x853;
    DevNVRAM->calibration_table.dacValA_m27[76] = 0x7d4;
    DevNVRAM->calibration_table.dacValA_m27[77] = 0x900;
    DevNVRAM->calibration_table.dacValA_m27[78] = 0x949;
    DevNVRAM->calibration_table.dacValA_m27[79] = 0x951;
    DevNVRAM->calibration_table.dacValA_m27[80] = 0xa80;
    DevNVRAM->calibration_table.dacValA_m27[81] = 0x832;
    DevNVRAM->calibration_table.dacValA_m27[82] = 0x899;
    DevNVRAM->calibration_table.dacValA_m27[83] = 0x879;
    DevNVRAM->calibration_table.dacValA_m27[84] = 0xac1;
    DevNVRAM->calibration_table.dacValA_m27[85] = 0x8b7;
    DevNVRAM->calibration_table.dacValA_m27[86] = 0x8dd;
    DevNVRAM->calibration_table.dacValA_m27[87] = 0x7d0;
    DevNVRAM->calibration_table.dacValA_m27[88] = 0x897;
    DevNVRAM->calibration_table.dacValA_m27[89] = 0x7d3;
    DevNVRAM->calibration_table.dacValA_m27[90] = 0x94b;
    DevNVRAM->calibration_table.dacValA_m27[91] = 0x8e9;
    DevNVRAM->calibration_table.dacValA_m27[92] = 0x8e9;
    DevNVRAM->calibration_table.dacValA_m27[93] = 0x7da;
    DevNVRAM->calibration_table.dacValA_m27[94] = 0x836;
    DevNVRAM->calibration_table.dacValA_m27[95] = 0x802;
    DevNVRAM->calibration_table.dacValA_m27[96] = 0x836;
    DevNVRAM->calibration_table.dacValA_m27[97] = 0x802;
    DevNVRAM->calibration_table.dacValA_m27[98] = 0x8cc;
    DevNVRAM->calibration_table.dacValA_m27[99] = 0x8e3;
    DevNVRAM->calibration_table.dacValA_m27[100] = 0x8cc;
    DevNVRAM->calibration_table.dacValA_m27[101] = 0x917;
    DevNVRAM->calibration_table.dacValA_m27[102] = 0x917;
    DevNVRAM->calibration_table.dacValA_m27[103] = 0x931;
    DevNVRAM->calibration_table.dacValA_m27[104] = 0x930;
    DevNVRAM->calibration_table.dacValA_m27[105] = 0xb95;
    DevNVRAM->calibration_table.dacValA_m27[106] = 0xb90;
    DevNVRAM->calibration_table.dacValA_m27[107] = 0xbc2;
    DevNVRAM->calibration_table.dacValA_m27[108] = 0x962;
    DevNVRAM->calibration_table.dacValA_m27[109] = 0x992;
    DevNVRAM->calibration_table.dacValA_m27[110] = 0x992;
    DevNVRAM->calibration_table.dacValA_m27[111] = 0x9ab;
    DevNVRAM->calibration_table.dacValA_m27[112] = 0x994;
    DevNVRAM->calibration_table.dacValA_m27[113] = 0xa9f;
    DevNVRAM->calibration_table.dacValA_m27[114] = 0xbd0;
    DevNVRAM->calibration_table.dacValA_m27[115] = 0xbea;
    DevNVRAM->calibration_table.dacValA_m27[116] = 0x9c6;
    DevNVRAM->calibration_table.dacValA_m27[117] = 0xb31;
    DevNVRAM->calibration_table.dacValA_m27[118] = 0xc1c;
    DevNVRAM->calibration_table.dacValA_m27[119] = 0x9ec;
    DevNVRAM->calibration_table.dacValA_m27[120] = 0x9f8;
    DevNVRAM->calibration_table.dacValA_m27[121] = 0xa0f;
    DevNVRAM->calibration_table.dacValA_m27[122] = 0x9fa;
    DevNVRAM->calibration_table.dacValA_m27[123] = 0xc46;
    DevNVRAM->calibration_table.dacValA_m27[124] = 0xc43;
    DevNVRAM->calibration_table.dacValA_m27[125] = 0xa1e;
    DevNVRAM->calibration_table.dacValA_m27[126] = 0xa32;
    DevNVRAM->calibration_table.dacValA_m27[127] = 0xa32;
    DevNVRAM->calibration_table.dacValA_m27[128] = 0xa39;
    DevNVRAM->calibration_table.dacValA_m27[129] = 0xa50;
    DevNVRAM->calibration_table.dacValA_m27[130] = 0xcb0;
    DevNVRAM->calibration_table.dacValA_m27[131] = 0xa5a;
    DevNVRAM->calibration_table.dacValA_m27[132] = 0xa64;
    DevNVRAM->calibration_table.dacValA_m27[133] = 0xcb0;
    DevNVRAM->calibration_table.dacValA_m27[134] = 0xa76;
    DevNVRAM->calibration_table.dacValA_m27[135] = 0xcbf;
    DevNVRAM->calibration_table.dacValA_m27[136] = 0xa8c;
    DevNVRAM->calibration_table.dacValA_m27[137] = 0xa95;
    DevNVRAM->calibration_table.dacValA_m27[138] = 0xcd9;
    DevNVRAM->calibration_table.dacValA_m27[139] = 0xaaa;
    DevNVRAM->calibration_table.dacValA_m27[140] = 0xbcb;
    DevNVRAM->calibration_table.dacValA_m27[141] = 0xbcf;
    DevNVRAM->calibration_table.dacValA_m27[142] = 0xacb;
    DevNVRAM->calibration_table.dacValA_m27[143] = 0xae1;
    DevNVRAM->calibration_table.dacValA_m27[144] = 0xaeb;
    DevNVRAM->calibration_table.dacValA_m27[145] = 0xaeb;
    DevNVRAM->calibration_table.dacValA_m27[146] = 0xaec;
    DevNVRAM->calibration_table.dacValA_m27[147] = 0xaf4;
    DevNVRAM->calibration_table.dacValA_m27[148] = 0xafc;
    DevNVRAM->calibration_table.dacValA_m27[149] = 0xc38;
    DevNVRAM->calibration_table.dacValA_m27[150] = 0xb18;
    DevNVRAM->calibration_table.dacValA_m27[151] = 0xb11;
    DevNVRAM->calibration_table.dacValA_m27[152] = 0xb27;
    DevNVRAM->calibration_table.dacValA_m27[153] = 0xb25;
    DevNVRAM->calibration_table.dacValA_m27[154] = 0xb2c;
    DevNVRAM->calibration_table.dacValA_m27[155] = 0xb31;
    DevNVRAM->calibration_table.dacValA_m27[156] = 0xb45;
    DevNVRAM->calibration_table.dacValA_m27[157] = 0xb56;
    DevNVRAM->calibration_table.dacValA_m27[158] = 0xb54;
    DevNVRAM->calibration_table.dacValA_m27[159] = 0xb56;
    DevNVRAM->calibration_table.dacValA_m27[160] = 0xb63;
    DevNVRAM->calibration_table.dacValA_m27[161] = 0xb62;
    DevNVRAM->calibration_table.dacValA_m27[162] = 0x1000;

    DevNVRAM->calibration_table.dacValB_m27[0] = 0x0;
    DevNVRAM->calibration_table.dacValB_m27[1] = 0x1c1;
    DevNVRAM->calibration_table.dacValB_m27[2] = 0x1d5;
    DevNVRAM->calibration_table.dacValB_m27[3] = 0x1d5;
    DevNVRAM->calibration_table.dacValB_m27[4] = 0x1d5;
    DevNVRAM->calibration_table.dacValB_m27[5] = 0x1d5;
    DevNVRAM->calibration_table.dacValB_m27[6] = 0x1d5;
    DevNVRAM->calibration_table.dacValB_m27[7] = 0x1d5;
    DevNVRAM->calibration_table.dacValB_m27[8] = 0x1d9;
    DevNVRAM->calibration_table.dacValB_m27[9] = 0x1f8;
    DevNVRAM->calibration_table.dacValB_m27[10] = 0x1bb;
    DevNVRAM->calibration_table.dacValB_m27[11] = 0x1bb;
    DevNVRAM->calibration_table.dacValB_m27[12] = 0x1bb;
    DevNVRAM->calibration_table.dacValB_m27[13] = 0x571;
    DevNVRAM->calibration_table.dacValB_m27[14] = 0x1bb;
    DevNVRAM->calibration_table.dacValB_m27[15] = 0x283;
    DevNVRAM->calibration_table.dacValB_m27[16] = 0x1cf;
    DevNVRAM->calibration_table.dacValB_m27[17] = 0x1c9;
    DevNVRAM->calibration_table.dacValB_m27[18] = 0x1bf;
    DevNVRAM->calibration_table.dacValB_m27[19] = 0x1bb;
    DevNVRAM->calibration_table.dacValB_m27[20] = 0x21f;
    DevNVRAM->calibration_table.dacValB_m27[21] = 0x1cf;
    DevNVRAM->calibration_table.dacValB_m27[22] = 0x1e8;
    DevNVRAM->calibration_table.dacValB_m27[23] = 0x1e8;
    DevNVRAM->calibration_table.dacValB_m27[24] = 0x1cf;
    DevNVRAM->calibration_table.dacValB_m27[25] = 0x1e8;
    DevNVRAM->calibration_table.dacValB_m27[26] = 0x7d3;
    DevNVRAM->calibration_table.dacValB_m27[27] = 0x80b;
    DevNVRAM->calibration_table.dacValB_m27[28] = 0x857;
    DevNVRAM->calibration_table.dacValB_m27[29] = 0x875;
    DevNVRAM->calibration_table.dacValB_m27[30] = 0x866;
    DevNVRAM->calibration_table.dacValB_m27[31] = 0x7d0;
    DevNVRAM->calibration_table.dacValB_m27[32] = 0x877;
    DevNVRAM->calibration_table.dacValB_m27[33] = 0x8a7;
    DevNVRAM->calibration_table.dacValB_m27[34] = 0x8a2;
    DevNVRAM->calibration_table.dacValB_m27[35] = 0x7f7;
    DevNVRAM->calibration_table.dacValB_m27[36] = 0x857;
    DevNVRAM->calibration_table.dacValB_m27[37] = 0x829;
    DevNVRAM->calibration_table.dacValB_m27[38] = 0x8f2;
    DevNVRAM->calibration_table.dacValB_m27[39] = 0x897;
    DevNVRAM->calibration_table.dacValB_m27[40] = 0x8cc;
    DevNVRAM->calibration_table.dacValB_m27[41] = 0x8ca;
    DevNVRAM->calibration_table.dacValB_m27[42] = 0x81f;
    DevNVRAM->calibration_table.dacValB_m27[43] = 0x7de;
    DevNVRAM->calibration_table.dacValB_m27[44] = 0x864;
    DevNVRAM->calibration_table.dacValB_m27[45] = 0x8ce;
    DevNVRAM->calibration_table.dacValB_m27[46] = 0x8d9;
    DevNVRAM->calibration_table.dacValB_m27[47] = 0x870;
    DevNVRAM->calibration_table.dacValB_m27[48] = 0x7de;
    DevNVRAM->calibration_table.dacValB_m27[49] = 0x80b;
    DevNVRAM->calibration_table.dacValB_m27[50] = 0x95b;
    DevNVRAM->calibration_table.dacValB_m27[51] = 0x89c;
    DevNVRAM->calibration_table.dacValB_m27[52] = 0x95b;
    DevNVRAM->calibration_table.dacValB_m27[53] = 0x7e2;
    DevNVRAM->calibration_table.dacValB_m27[54] = 0x8ce;
    DevNVRAM->calibration_table.dacValB_m27[55] = 0x974;
    DevNVRAM->calibration_table.dacValB_m27[56] = 0x7e7;
    DevNVRAM->calibration_table.dacValB_m27[57] = 0x801;
    DevNVRAM->calibration_table.dacValB_m27[58] = 0x864;
    DevNVRAM->calibration_table.dacValB_m27[59] = 0x8a1;
    DevNVRAM->calibration_table.dacValB_m27[60] = 0x988;
    DevNVRAM->calibration_table.dacValB_m27[61] = 0x7e3;
    DevNVRAM->calibration_table.dacValB_m27[62] = 0x864;
    DevNVRAM->calibration_table.dacValB_m27[63] = 0x92a;
    DevNVRAM->calibration_table.dacValB_m27[64] = 0x7fc;
    DevNVRAM->calibration_table.dacValB_m27[65] = 0x897;
    DevNVRAM->calibration_table.dacValB_m27[66] = 0x892;
    DevNVRAM->calibration_table.dacValB_m27[67] = 0x8af;
    DevNVRAM->calibration_table.dacValB_m27[68] = 0x83a;
    DevNVRAM->calibration_table.dacValB_m27[69] = 0x810;
    DevNVRAM->calibration_table.dacValB_m27[70] = 0x83a;
    DevNVRAM->calibration_table.dacValB_m27[71] = 0x7d4;
    DevNVRAM->calibration_table.dacValB_m27[72] = 0x914;
    DevNVRAM->calibration_table.dacValB_m27[73] = 0x7d6;
    DevNVRAM->calibration_table.dacValB_m27[74] = 0x8e8;
    DevNVRAM->calibration_table.dacValB_m27[75] = 0x7e8;
    DevNVRAM->calibration_table.dacValB_m27[76] = 0x8e7;
    DevNVRAM->calibration_table.dacValB_m27[77] = 0x8fa;
    DevNVRAM->calibration_table.dacValB_m27[78] = 0xa82;
    DevNVRAM->calibration_table.dacValB_m27[79] = 0x86c;
    DevNVRAM->calibration_table.dacValB_m27[80] = 0x906;
    DevNVRAM->calibration_table.dacValB_m27[81] = 0x8f8;
    DevNVRAM->calibration_table.dacValB_m27[82] = 0x885;
    DevNVRAM->calibration_table.dacValB_m27[83] = 0x884;
    DevNVRAM->calibration_table.dacValB_m27[84] = 0x930;
    DevNVRAM->calibration_table.dacValB_m27[85] = 0x865;
    DevNVRAM->calibration_table.dacValB_m27[86] = 0x8d0;
    DevNVRAM->calibration_table.dacValB_m27[87] = 0x7e7;
    DevNVRAM->calibration_table.dacValB_m27[88] = 0x8b9;
    DevNVRAM->calibration_table.dacValB_m27[89] = 0xab4;
    DevNVRAM->calibration_table.dacValB_m27[90] = 0x8c8;
    DevNVRAM->calibration_table.dacValB_m27[91] = 0x8e9;
    DevNVRAM->calibration_table.dacValB_m27[92] = 0xaff;
    DevNVRAM->calibration_table.dacValB_m27[93] = 0x7da;
    DevNVRAM->calibration_table.dacValB_m27[94] = 0x804;
    DevNVRAM->calibration_table.dacValB_m27[95] = 0x7da;
    DevNVRAM->calibration_table.dacValB_m27[96] = 0x804;
    DevNVRAM->calibration_table.dacValB_m27[97] = 0x7da;
    DevNVRAM->calibration_table.dacValB_m27[98] = 0x8ca;
    DevNVRAM->calibration_table.dacValB_m27[99] = 0x947;
    DevNVRAM->calibration_table.dacValB_m27[100] = 0x8fe;
    DevNVRAM->calibration_table.dacValB_m27[101] = 0x8fc;
    DevNVRAM->calibration_table.dacValB_m27[102] = 0x8ed;
    DevNVRAM->calibration_table.dacValB_m27[103] = 0x989;
    DevNVRAM->calibration_table.dacValB_m27[104] = 0x92e;
    DevNVRAM->calibration_table.dacValB_m27[105] = 0x930;
    DevNVRAM->calibration_table.dacValB_m27[106] = 0x9cf;
    DevNVRAM->calibration_table.dacValB_m27[107] = 0x979;
    DevNVRAM->calibration_table.dacValB_m27[108] = 0x9cf;
    DevNVRAM->calibration_table.dacValB_m27[109] = 0x979;
    DevNVRAM->calibration_table.dacValB_m27[110] = 0x9e6;
    DevNVRAM->calibration_table.dacValB_m27[111] = 0x9fc;
    DevNVRAM->calibration_table.dacValB_m27[112] = 0x992;
    DevNVRAM->calibration_table.dacValB_m27[113] = 0xaa9;
    DevNVRAM->calibration_table.dacValB_m27[114] = 0xbd0;
    DevNVRAM->calibration_table.dacValB_m27[115] = 0xc1c;
    DevNVRAM->calibration_table.dacValB_m27[116] = 0x9c6;
    DevNVRAM->calibration_table.dacValB_m27[117] = 0xb2b;
    DevNVRAM->calibration_table.dacValB_m27[118] = 0x9d8;
    DevNVRAM->calibration_table.dacValB_m27[119] = 0xc1f;
    DevNVRAM->calibration_table.dacValB_m27[120] = 0xb5d;
    DevNVRAM->calibration_table.dacValB_m27[121] = 0xc50;
    DevNVRAM->calibration_table.dacValB_m27[122] = 0xc4e;
    DevNVRAM->calibration_table.dacValB_m27[123] = 0xc4c;
    DevNVRAM->calibration_table.dacValB_m27[124] = 0xa0e;
    DevNVRAM->calibration_table.dacValB_m27[125] = 0xc76;
    DevNVRAM->calibration_table.dacValB_m27[126] = 0xbed;
    DevNVRAM->calibration_table.dacValB_m27[127] = 0xa2f;
    DevNVRAM->calibration_table.dacValB_m27[128] = 0xa36;
    DevNVRAM->calibration_table.dacValB_m27[129] = 0xc80;
    DevNVRAM->calibration_table.dacValB_m27[130] = 0xc71;
    DevNVRAM->calibration_table.dacValB_m27[131] = 0xa55;
    DevNVRAM->calibration_table.dacValB_m27[132] = 0xcac;
    DevNVRAM->calibration_table.dacValB_m27[133] = 0xa6b;
    DevNVRAM->calibration_table.dacValB_m27[134] = 0xcbb;
    DevNVRAM->calibration_table.dacValB_m27[135] = 0xa7d;
    DevNVRAM->calibration_table.dacValB_m27[136] = 0xb9a;
    DevNVRAM->calibration_table.dacValB_m27[137] = 0xba7;
    DevNVRAM->calibration_table.dacValB_m27[138] = 0xab4;
    DevNVRAM->calibration_table.dacValB_m27[139] = 0xbe4;
    DevNVRAM->calibration_table.dacValB_m27[140] = 0xab4;
    DevNVRAM->calibration_table.dacValB_m27[141] = 0xbbc;
    DevNVRAM->calibration_table.dacValB_m27[142] = 0xbba;
    DevNVRAM->calibration_table.dacValB_m27[143] = 0xd02;
    DevNVRAM->calibration_table.dacValB_m27[144] = 0xbf3;
    DevNVRAM->calibration_table.dacValB_m27[145] = 0xaf0;
    DevNVRAM->calibration_table.dacValB_m27[146] = 0xaed;
    DevNVRAM->calibration_table.dacValB_m27[147] = 0xaf8;
    DevNVRAM->calibration_table.dacValB_m27[148] = 0xcfc;
    DevNVRAM->calibration_table.dacValB_m27[149] = 0xc18;
    DevNVRAM->calibration_table.dacValB_m27[150] = 0xb0b;
    DevNVRAM->calibration_table.dacValB_m27[151] = 0xb18;
    DevNVRAM->calibration_table.dacValB_m27[152] = 0xb1b;
    DevNVRAM->calibration_table.dacValB_m27[153] = 0xc08;
    DevNVRAM->calibration_table.dacValB_m27[154] = 0xb2a;
    DevNVRAM->calibration_table.dacValB_m27[155] = 0xb2f;
    DevNVRAM->calibration_table.dacValB_m27[156] = 0xd09;
    DevNVRAM->calibration_table.dacValB_m27[157] = 0xc0a;
    DevNVRAM->calibration_table.dacValB_m27[158] = 0xb4f;
    DevNVRAM->calibration_table.dacValB_m27[159] = 0xb56;
    DevNVRAM->calibration_table.dacValB_m27[160] = 0xb6d;
    DevNVRAM->calibration_table.dacValB_m27[161] = 0xb44;
    DevNVRAM->calibration_table.dacValB_m27[162] = 0x1000;

}

	static FLASH_EraseInitTypeDef EraseInitStruct; // структура для очистки флеша

	EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES; // постраничная очистка, FLASH_TYPEERASE_MASSERASE - очистка всего флеша
	EraseInitStruct.PageAddress = FLASH_TABLE_START_ADDR; // адрес 127-ой страницы
	EraseInitStruct.NbPages = 0x01;               // кол-во страниц для стирания
	//EraseInitStruct.Banks = FLASH_BANK_1; // FLASH_BANK_2 - банк №2, FLASH_BANK_BOTH - оба банка
	//--------------------------------------------------------------------------
	uint32_t l_Address;
	uint32_t l_Error;
	uint32_t l_Index;
//--------------------------------------------------------------------------
// Чтение DevNVRAM
	l_Address = FLASH_TABLE_START_ADDR;
	l_Error = 0;
	l_Index = 0;
	while (l_Address < FLASH_TABLE_STOP_ADDR) {
		DevNVRAM.data32[l_Index] = *(__IO uint32_t*) l_Address;
		l_Index = l_Index + 1;
		l_Address = l_Address + 4;
	}

//--------------------------------------------------------------------------
// если после чтения майджик кей не найден, то это первый запуск

	if (DevNVRAM.calibration_table.MagicNum != MAGIC_KEY_DEFINE) {
		// Подготовка
		// Заносим типовые значения
		memset(DevNVRAM.data32, 0, sizeof(DevNVRAM.data32));

		// TODO: !!!!!Добавить математику расчета калибровочной таблицы!!!!!!!

		for (uint8_t i = 0; i < MAX_VAL_M12; i++) {
			DevNVRAM.calibration_table.dacValA_m12[i] = i;
		}
		for (uint8_t i = 0; i < MAX_VAL_M12; i++) {
			DevNVRAM.calibration_table.dacValB_m12[i] = i;
		}
		for (uint8_t i = 0; i < MAX_VAL_M27; i++) {
			DevNVRAM.calibration_table.dacValA_m27[i] = i;
		}
		for (uint8_t i = 0; i < MAX_VAL_M27; i++) {
			DevNVRAM.calibration_table.dacValB_m12[i] = i;
		}
		DevNVRAM.calibration_table.Hardwire = 0x06;
		DevNVRAM.calibration_table.Firmware = 0x05;
		DevNVRAM.calibration_table.SN 		= 0x1121001; //11 неделя + год + порядковый номер изготовления
		DevNVRAM.calibration_table.MagicNum = MAGIC_KEY_DEFINE;

		DevNVRAM.sector.NWrite = 0;
		DevNVRAM.sector.CheckSum = 0;//TODO: по какой то причине в этом проекте не работает CRC!!! у


//--------------------------------------------------------------------------
		//если после чтения майджик кей не найден, то это первый запуск записываем дефолтную таблицу
		l_Address = FLASH_TABLE_START_ADDR;
		l_Error = 0;
		l_Index = 0;

		while (l_Address < FLASH_TABLE_STOP_ADDR) {
			if (DevNVRAM.data32[l_Index] != *(__IO uint32_t*) l_Address) {
				l_Error++;
			}
			l_Index = l_Index + 1;
			l_Address = l_Address + 4;
		}

		if (l_Error > 0) { // конфигурация изменилась сохраняем
			// Готовим к записи в память
			HAL_FLASH_Unlock();
			// Очищаем страницу памяти
			HAL_FLASHEx_Erase(&EraseInitStruct, &l_Error);
			//Пишем данные в память
			l_Address = FLASH_TABLE_START_ADDR;
			l_Error = 0x00;
			l_Index = 0x00;

			while (l_Address < FLASH_TABLE_STOP_ADDR) {
				if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, l_Address,
						DevNVRAM.data32[l_Index]) != HAL_OK) {
					l_Error++;
				}

				l_Address = l_Address + 4;
				l_Index = l_Index + 1;
				HAL_Delay(10);
			}
			HAL_FLASH_Lock();
		}

	}//если после чтения майджик кей не найден, то это первый запуск записываем дефолтную таблицу
	// TODO: Надо по запросе какая версия калиброчной табцы высылать значения дефолтной таблице...
//--------------------------------------------------------------------------
// Запиcь калибровочной таблицы в память

	// TODO: !!!!!Добавить математику расчета калибровочной таблицы!!!!!!!


// Циклически проверяем соотвествует ли информация в памяти массиву настроек?

	l_Address = FLASH_TABLE_START_ADDR;
	l_Error = 0;
	l_Index = 0;
	//Читаем и сравниваем
	while (l_Address < FLASH_TABLE_STOP_ADDR) {
		if (DevNVRAM.data32[l_Index] != *(__IO uint32_t*) l_Address) {
			l_Error++;
		}
		l_Index = l_Index + 1;
		l_Address = l_Address + 4;
	}

	if (l_Error > 0) { // конфигурация изменилась сохраняем
		// Готовим к записи в память
		HAL_FLASH_Unlock();
		// Очищаем страницу памяти
		HAL_FLASHEx_Erase(&EraseInitStruct, &l_Error);
		//Пишем данные в память
		l_Address = FLASH_TABLE_START_ADDR;
		l_Error = 0x00;
		l_Index = 0x00;

		DevNVRAM.sector.NWrite = DevNVRAM.sector.NWrite + 1;
		DevNVRAM.sector.CheckSum = 0;

		while (l_Address < FLASH_TABLE_STOP_ADDR) {
			if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, l_Address,
					DevNVRAM.data32[l_Index]) != HAL_OK) {
				l_Error++;
			}

			l_Address = l_Address + 4;
			l_Index = l_Index + 1;
			HAL_Delay(10);
		}
		HAL_FLASH_Lock();
	}
	HAL_Delay(100);
//--------------------------------------------------------------------------
	crete_calibration_table(&DevNVRAM);


#endif	/* TEST_FLASH_TABLE */
//**************************************************************************
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {

//**************************************************************************
// Циклически проверяем соотвествует ли информация в памяти массиву настроек?

		l_Address = FLASH_TABLE_START_ADDR;
		l_Error = 0;
		l_Index = 0;
		//Читаем и сравниваем
		while (l_Address < FLASH_TABLE_STOP_ADDR) {
			if (DevNVRAM.data32[l_Index] != *(__IO uint32_t*) l_Address) {
				l_Error++;
			}
			l_Index = l_Index + 1;
			l_Address = l_Address + 4;
		}

		if (l_Error > 0) { // конфигурация изменилась сохраняем
			printf("Ошибка чтения таблицы :%i", l_Error);
			if (l_Error > 0) { // конфигурация изменилась сохраняем
					// Готовим к записи в память
					HAL_FLASH_Unlock();
					// Очищаем страницу памяти
					HAL_FLASHEx_Erase(&EraseInitStruct, &l_Error);
					//Пишем данные в память
					l_Address = FLASH_TABLE_START_ADDR;
					l_Error = 0x00;
					l_Index = 0x00;

					DevNVRAM.sector.NWrite = DevNVRAM.sector.NWrite + 1;
					DevNVRAM.sector.CheckSum = 0;

					while (l_Address < FLASH_TABLE_STOP_ADDR) {
						if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, l_Address,
								DevNVRAM.data32[l_Index]) != HAL_OK) {
							l_Error++;
						}

						l_Address = l_Address + 4;
						l_Index = l_Index + 1;
						HAL_Delay(10);
					}
					HAL_FLASH_Lock();
				}
				HAL_Delay(100);
		}

//**************************************************************************
#if  TEST_READ_BTN

		uint32_t ms = HAL_GetTick();
		uint8_t key1_state = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12); // подставить свой пин //TODO: Проверить работу BACK key!

		if (key1_state == 0 && !short_state1 && (ms - time_key1) > 50) {
			short_state1 = 1;
			long_state1 = 0;
			time_key1 = ms;
		} else if (key1_state
				== 0&& !long_state1 && (ms - time_key1) > KEY_LONG_DELAY) {
			long_state1 = 1;
			// действие на длинное нажатие
			btn1_long_rd = 1;

		} else if (key1_state == 1 && short_state1 && (ms - time_key1) > 50) {
			short_state1 = 0;
			time_key1 = ms;

			if (!long_state1) {
				// действие на короткое нажатие
				btn1_short_rd = 1;
			}
		}
		uint8_t key2_state = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13); // подставить свой пин

		if (key2_state == 0 && !short_state2 && (ms - time_key2) > 50) {
			short_state2 = 1;
			long_state2 = 0;
			time_key2 = ms;
		} else if (key2_state
				== 0&& !long_state2 && (ms - time_key2) > KEY_LONG_DELAY) {
			long_state2 = 1;

			// действие на длинное нажатие
			btn2_long_rd = 1;
		} else if (key2_state == 1 && short_state2 && (ms - time_key2) > 50) {
			short_state2 = 0;
			time_key2 = ms;

			if (!long_state2) {
				// действие на короткое нажатие
				btn2_short_rd = 1;
			}
		}

		uint8_t key3_state = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14); // подставить свой пин
		if (key3_state == 0 && !short_state3 && (ms - time_key3) > 50) {
			short_state3 = 1;
			long_state3 = 0;
			time_key3 = ms;
		} else if (key3_state
				== 0&& !long_state3 && (ms - time_key3) > KEY_LONG_DELAY) {
			long_state3 = 1;
			// действие на длинное нажатие
			btn3_long_rd = 1;
		} else if (key3_state == 1 && short_state3 && (ms - time_key3) > 50) {
			short_state3 = 0;
			time_key3 = ms;

			if (!long_state3) {
				// действие на короткое нажатие
				btn3_short_rd = 1;
			}
		}

#endif	/* TEST_READ_BTN */
//**************************************************************************

//--------------------------------------------------------------------------


		/* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC|RCC_PERIPHCLK_USB;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_13CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRC_Init(void)
{

  /* USER CODE BEGIN CRC_Init 0 */

  /* USER CODE END CRC_Init 0 */

  /* USER CODE BEGIN CRC_Init 1 */

  /* USER CODE END CRC_Init 1 */
  hcrc.Instance = CRC;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CRC_Init 2 */

  /* USER CODE END CRC_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_16BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 72-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65000-1;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_IC_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim3, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
  sConfigIC.ICSelection = TIM_ICSELECTION_INDIRECTTI;
  if (HAL_TIM_IC_ConfigChannel(&htim3, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 72-1;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 65000-1;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_IC_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim4, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
  sConfigIC.ICSelection = TIM_ICSELECTION_INDIRECTTI;
  if (HAL_TIM_IC_ConfigChannel(&htim4, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, AD5312_LDAC_Pin|AD5312_SYNC_Pin|GPIO_PIN_10, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Relay_GPIO_Port, Relay_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : AD5312_LDAC_Pin Relay_Pin AD5312_SYNC_Pin PA10 */
  GPIO_InitStruct.Pin = AD5312_LDAC_Pin|Relay_Pin|AD5312_SYNC_Pin|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB13 PB14 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

#if USB_RESET
// После перегенерации в Кубе добавить USB_Reset(); в функцию MX_GPIO_Init(void) (после ...CLK_ENABLE(); )
void USB_Reset()// не работает без транзистора(
{

	 GPIO_InitTypeDef GPIO_InitStruct = {0};

	 // инициализируем пин DP как выход
	 GPIO_InitStruct.Pin = GPIO_PIN_12;
	 GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	 GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	 HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET); // прижимаем DP к "земле"
	 for(uint16_t i = 0; i < 2000; i++) {}; // немного ждём

	 // переинициализируем пин для работы с USB
	 GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	 GPIO_InitStruct.Pull = GPIO_NOPULL;
	 HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	 for(uint16_t i = 0; i < 2000; i++) {}; // немного ждём
}
#endif	/* USB_RESET */
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	 printf("Wrong parameters value: file %s on line %d\r\n", file, line);
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
