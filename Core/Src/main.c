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
#include "logic_calibration_table.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "DAC_AD5322.h"
#include "usbd_cdc_if.h"
#include "string.h" // это для функции strlen()
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
char UARTtrans_str[64] = {0,};
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

// Тестовые сборки
#define TEST_RELAY_BKP			0
#define TEST_DAC 				0
#define TEST_DAC_WHILE 			1
#define TEST_GPIO_WHILE			1
#define TEST_ADC 				1
#define TEST_CALIBRATION_WHILE	0
#define TEST_CALIBRATION_HL		0
#define TEST_CALIBRATION_LL		0
#define TEST_TIM_CAPTURE		1




//#define DWT_CONTROL *(volatile unsigned long *)0xE0001000
//#define SCB_DEMCR 	*(volatile unsigned long *)0xE000EDFC


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */
//--------------------------------------------------------------------------
uint16_t VDAC_A	= 2200;
uint16_t VDAC_B	= 2400;
//--------------------------------------------------------------------------
#if TEST_ADC
volatile uint16_t g_VADC = 0;
char trans_str[64] = { 0, };
#endif	/* TEST_ADC */
//--------------------------------------------------------------------------
#define KEY_LONG_DELAY	1000
//PB12
uint8_t short_state1 	= 0;
uint8_t long_state1	 	= 0;
uint32_t time_key1		= 0;

uint8_t btn1_long_rd 	= 0;
uint8_t btn1_short_rd	= 0;

//PB13
uint8_t short_state2 	= 0;
uint8_t long_state2	 	= 0;
uint32_t time_key2	 	= 0;

uint8_t btn2_long_rd 	= 0;
uint8_t btn2_short_rd 	= 0;

//PB14
uint8_t short_state3 	= 0;
uint8_t long_state3  	= 0;
uint32_t time_key3 	 	= 0;

uint8_t btn3_long_rd 	= 0;
uint8_t btn3_short_rd 	= 0;

// PB8 - inHL

uint8_t flag_key1_press = 1;
uint32_t time_key1_press= 0;

uint8_t inHL_rd 		= 0;

// PB9 - inLL

uint8_t flag_key2_press = 1;
uint32_t time_key2_press= 0;

uint8_t inLL_rd 		= 0;

#if TEST_TIM_CAPTURE

volatile uint8_t timWork = 0;

volatile uint8_t count_overflowTIM3 = 0;
volatile uint8_t count_overflowTIM4 = 0;

volatile uint16_t g_vTIM3_PB4 = 0;
volatile uint16_t g_vTIM4_PB6 = 0;


char trans2_str[64] = {0,};
#endif	/* TEST_TIM_CAPTURE */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM4_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */

void SetDacA(uint16_t da) {
	VDAC_A	= da;
	DAC_AD5322_Ch1(&hspi1, VDAC_A);
}

void SetDacB(uint16_t db) {
	VDAC_B	= db;
	DAC_AD5322_Ch2(&hspi1, VDAC_B);
}

uint16_t GetDacA() {
	return VDAC_A;
}

uint16_t GetDacB() {
	return VDAC_B;

}

//--------------------------------------------------------------------------

//struct s_Calibration_table{
//	uint16_t length = 570;
//	uint16_t Index = 0;
//
//	uint16_t volt_val[length];
//	uint16_t dac_val[length];
//};

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

/*	Калибровка:
 * Одна итерация: на входе щупа устанавливается заданное напряжение.
 * Начинаем менять входные коды ЦАП верхнего и нижнего уровня до того момента пока на выходах компараторов не появится 1.
 * Т.е. каждый раз когда мы меняем входной код - мы запрашиваем контроллер щупа о состоянии выходов компаратора.
 */
uint8_t GetInHL(){
	return  inHL_rd;
};

uint8_t GetInLL(){
	return  inLL_rd;
};

//--------------------------------------------------------------------------

void EnableTIM3_PB4(){
	 timWork = 1 ;
}
//--------------------------------------------------------------------------

void EnableTIM4_PB6(){
	 timWork = 0 ;
}
//--------------------------------------------------------------------------

uint16_t GetTIM3(){
	return g_vTIM3_PB4;
}
//--------------------------------------------------------------------------
void resValTIM3_PB4(){
	g_vTIM3_PB4 = 0;
}


//--------------------------------------------------------------------------
uint16_t GetTIM4(){
	return g_vTIM4_PB6;
}
//--------------------------------------------------------------------------
void resValTIM4_PB6(){
	g_vTIM4_PB6 = 0;
}
//--------------------------------------------------------------------------

uint16_t GetADC(){
	return g_VADC;
}
//--------------------------------------------------------------------------

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    if(hadc->Instance == ADC1) 				//check if the interrupt comes from ACD1
    {
    	g_VADC = HAL_ADC_GetValue(&hadc1); // глобальная переменна g_VADC вычитывается
    }
}
//--------------------------------------------------------------------------


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	uint16_t periodTIM3,pulseWidthTIM3,periodTIM4,pulseWidthTIM4;

	if (timWork){
		if (htim->Instance == TIM3)
		    {
		        if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
		        {
		        	periodTIM3 = HAL_TIM_ReadCapturedValue(&htim3, TIM_CHANNEL_1);
		        	pulseWidthTIM3 = HAL_TIM_ReadCapturedValue(&htim3, TIM_CHANNEL_2);

		            TIM3->CNT = 0;

		            int16_t deltaTIM3 = (int16_t)periodTIM3 - (int16_t)pulseWidthTIM3;
		            deltaTIM3	= (deltaTIM3 < 0) ? (-1 * deltaTIM3) : deltaTIM3;
		            g_vTIM3_PB4 = deltaTIM3;

		        }
		    }
	}else{
		 if (htim->Instance == TIM4)
		    {
		        if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
		        {
		        	periodTIM4 = HAL_TIM_ReadCapturedValue(&htim4, TIM_CHANNEL_1);
		        	pulseWidthTIM4 = HAL_TIM_ReadCapturedValue(&htim4, TIM_CHANNEL_2);

		            TIM4->CNT = 0;

		            int16_t deltaTIM4 = (int16_t)periodTIM4 - (int16_t)pulseWidthTIM4;
		            deltaTIM4	= (deltaTIM4 < 0) ? (-1 * deltaTIM4) : deltaTIM4;
		            g_vTIM4_PB6 = deltaTIM4;

		        }
		    }
	}



}


//--------------------------------------------------------------------------


//
//void DWT_Init(void)
//{
//    SCB_DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; // разрешаем использовать счётчик
//    DWT_CONTROL |= DWT_CTRL_CYCCNTENA_Msk;   // запускаем счётчик
//}
//
///////////////////////////////////// delay_ms /////////////////////////////////////
//void delay_ms(uint32_t ms)
//{
//    uint32_t ms_count_tic =  ms * (SystemCoreClock / 1000);
//    DWT->CYCCNT = 0U; // обнуляем счётчик
//    while(DWT->CYCCNT < ms_count_tic);
//}
//
///////////////////////////////// delay_us variant 1 ///////////////////////////////
//void delay_us(uint32_t us)
//{
//    uint32_t us_count_tic =  us * (SystemCoreClock / 1000000);
//    DWT->CYCCNT = 0U; // обнуляем счётчик
//    while(DWT->CYCCNT < us_count_tic);
//}

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
  DWT_Init();
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
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

//--------------------------------------------------------------------------

//  s_Calibration_table s_table;
//  s_table->

//--------------------------------------------------------------------------
#if TEST_ADC
//ADC
  HAL_ADCEx_Calibration_Start(&hadc1);
  HAL_ADC_Start_IT(&hadc1);
#endif	/* TEST_ADC */

  HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);
  HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_2);
  HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_1);
  HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_2);

//--------------------------------------------------------------------------
#if TEST_RELAY_BKP
  uint32_t volatile rdData = 0;
  uint16_t reload_counter = 0;

  HAL_PWR_EnableBkUpAccess(); // для хранения состояния в памяти

  reload_counter = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR2);//
  reload_counter = !reload_counter;
  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR2, (uint32_t) reload_counter);
	rdData = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR2);
	if (rdData == 0x01)
		{
			HAL_GPIO_WritePin(Reley_GPIO_Port, Reley_Pin, GPIO_PIN_SET);
//			 VDAC_A = 1500;
//			 VDAC_B = 1000;
		}
	if (rdData == 0x00)
		{
			HAL_GPIO_WritePin(Reley_GPIO_Port, Reley_Pin, GPIO_PIN_RESET);
//			 VDAC_A = 1000;
//			 VDAC_B = 1500;
		}
#endif	/* TEST_RELAY */
//--------------------------------------------------------------------------

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {

//--------------------------------------------------------------------------
#if  TEST_DAC_WHILE

	DAC_AD5322_Ch1(&hspi1, VDAC_A);
	DAC_AD5322_Ch2(&hspi1, VDAC_B);
	HAL_Delay(250);
#endif	/* TEST_DAC_WHILE */
//--------------------------------------------------------------------------
#if  TEST_GPIO_WHILE

		 uint32_t ms = HAL_GetTick();
			  uint8_t key1_state = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12); // подставить свой пин

			  if(key1_state == 0 && !short_state1 && (ms - time_key1) > 50)
			  {
			    short_state1 = 1;
			    long_state1 = 0;
			    time_key1 = ms;
			  }
			  else if(key1_state == 0 && !long_state1 && (ms - time_key1) > KEY_LONG_DELAY)
			  {
			    long_state1 = 1;
			    // действие на длинное нажатие
			    btn1_long_rd = 1;

			  }
			  else if(key1_state == 1 && short_state1 && (ms - time_key1) > 50)
			  {
			    short_state1 = 0;
			    time_key1 = ms;

			    if(!long_state1)
			    {
			      // действие на короткое нажатие
			    	btn1_short_rd = 1;
			    }
			  }
			  uint8_t key2_state = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13); // подставить свой пин

			  if(key2_state == 0 && !short_state2 && (ms - time_key2) > 50)
			  {
			    short_state2 = 1;
			    long_state2 = 0;
			    time_key2 = ms;
			  }
			  else if(key2_state == 0 && !long_state2 && (ms - time_key2) > KEY_LONG_DELAY)
			  {
			    long_state2 = 1;

			    // действие на длинное нажатие
			    btn2_long_rd = 1;
			  }
			  else if(key2_state == 1 && short_state2 && (ms - time_key2) > 50)
			  {
			    short_state2 = 0;
			    time_key2 = ms;

			    if(!long_state2)
			    {
			      // действие на короткое нажатие
			    	btn2_short_rd = 1;
			    }
			  }

			  uint8_t key3_state = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14); // подставить свой пин
			  if(key3_state == 0 && !short_state3 && (ms - time_key3) > 50)
			  {
			    short_state3 = 1;
			    long_state3 = 0;
			    time_key3 = ms;
			  }
			  else if(key3_state == 0 && !long_state3 && (ms - time_key3) > KEY_LONG_DELAY)
			  {
			    long_state3 = 1;
			    // действие на длинное нажатие
				 btn3_long_rd = 1;
			  }
			  else if(key3_state == 1 && short_state3 && (ms - time_key3) > 50)
			  {
			    short_state3 = 0;
			    time_key3 = ms;

			    if(!long_state3)
			    {
			      // действие на короткое нажатие
			    	btn3_short_rd = 1;
			    }
			  }


			  //--------------------------------------------------------------------------

			  #if  TEST_CALIBRATION_HL


			  // Чтение состояние компоратора inHL = 1
			  uint8_t ReadPinHL_S = HAL_GPIO_ReadPin(inHL_GPIO_Port, inHL_Pin) == GPIO_PIN_SET;

//			  if(HAL_GPIO_ReadPin(inHL_GPIO_Port, inHL_Pin) == GPIO_PIN_SET && flag_key1_press) // подставить свой пин
			  if(ReadPinHL_S && flag_key1_press) // подставить свой пин
			  {

			    flag_key1_press = 0;

			    // действие на нажатие
			    inHL_rd 		= 0x01;


			    time_key1_press = HAL_GetTick();
			  }

			  if(!flag_key1_press && (HAL_GetTick() - time_key1_press) > 150)
			  {
			    flag_key1_press = 1;
			  }

			  //--------------------------------------------------------------------------

			  // Чтение состояние компоратора inHL = 0
			  uint8_t ReadPinHL_R = HAL_GPIO_ReadPin(inHL_GPIO_Port, inHL_Pin) == GPIO_PIN_RESET;

//			  if(HAL_GPIO_ReadPin(inHL_GPIO_Port, inHL_Pin) == GPIO_PIN_RESET && flag_key1_press) // подставить свой пин
			  if(ReadPinHL_R && flag_key1_press) // подставить свой пин
			  {

			    flag_key1_press = 0;

			    // действие на нажатие
			    inHL_rd 		= 0x00;


			    time_key1_press = HAL_GetTick();
			  }

			  if(!flag_key1_press && (HAL_GetTick() - time_key1_press) > 150)
			  {
			    flag_key1_press = 1;
			  }
		#endif	/* TEST_CALIBRATION_HL */

		#if  TEST_CALIBRATION_LL
			  // Чтение состояние компоратора inLL = 1
			  uint8_t ReadPinLL_S = HAL_GPIO_ReadPin(inHL_GPIO_Port, inHL_Pin) == GPIO_PIN_SET;

//			  if(HAL_GPIO_ReadPin(inLL_GPIO_Port, inLL_Pin) == GPIO_PIN_SET && flag_key2_press) // подставить свой пин
			  if(ReadPinLL_S && flag_key2_press) // подставить свой пин
			  {
			    flag_key2_press = 0;

			    // действие на нажатие
			    inLL_rd 		= 0x01; //TODO: err read pin

			    time_key2_press = HAL_GetTick();
			    }


			  uint32_t dTime = (HAL_GetTick() - time_key2_press);

//			  if(!flag_key2_press && (HAL_GetTick() - time_key2_press) > 150)
			  if(!flag_key2_press && dTime > 150)
			  {
			    flag_key2_press = 1; //TODO: НЕ устанавливается флаш! изза dTime!
			  }
			  //--------------------------------------------------------------------------

			  // Чтение состояние компоратора inLL = 0
			  uint8_t ReadPinLL_R = HAL_GPIO_ReadPin(inHL_GPIO_Port, inHL_Pin) == GPIO_PIN_RESET;

//			  if(HAL_GPIO_ReadPin(inLL_GPIO_Port, inLL_Pin) == GPIO_PIN_RESET && flag_key2_press) // подставить свой пин
			  if(ReadPinLL_R && flag_key2_press) // подставить свой пин
			  {
			    flag_key2_press = 0;

			    // действие на нажатие
			    inLL_rd 		= 0x00;


			    time_key2_press = HAL_GetTick();
			    }



			  if(!flag_key2_press && dTime > 150)
			  {
			    flag_key2_press = 1; //TODO: НЕ устанавливается флаш! изза dTime!
			  }

#endif	/* TEST_CALIBRATION_LL */
			  //--------------------------------------------------------------------------

#endif	/* TEST_GPIO_WHILE */

//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
//	delay_us(500); // длина импульса
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
//	delay_us(500);
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

  /** Initializes the CPU, AHB and APB busses clocks 
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
  /** Initializes the CPU, AHB and APB busses clocks 
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
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 9600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

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
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
