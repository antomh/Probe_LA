/* USER CODE BEGIN Header */
/*
 * TODO: Протестировать обработку нажатия кнопок: длинное и одиночное нажатие ( в Callback )
 * TODO: Закончить перенос кода из проекта Саши
 * TODO: Протестировать команду приема параметров калибровки
 *
 * */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/*-USER FILES----------------------------------------------------------------*/
#include "DAC_AD5322.h"
#include "logic_calibration_table.h"
#include "flash.h"
#include "crc.h"
#include "usb_handler.h"
#include "btn.h"
#include "usbd_cdc_if.h"
#include "stm32f1xx_it.h"

/*-STANDART C FILES----------------------------------------------------------*/
#include "string.h"
#include "stdbool.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

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
/* Объединение для работы с калибровочной таблицей */
union NVRAM DevNVRAM;

/* Структура для организации приема пакетов по USB */
usb_rx_data_type usb_rx_data = {
        .is_handled     = true,
        .is_received    = false,
        .len            = 0,
        .buff           = {0,0,0,0,0,0,0,0,
                           0,0,0,0,0,0,0,0,
                           0,0,0,0,0,0,0,0,
                           0,0,0,0,0,0,0,0,
                           0,0,0,0,0,0,0,0,
                           0,0,0,0,0,0,0,0,
                           0,0,0,0,0,0,0,0,
                           0,0,0,0,0,0,0,0}
};

/* Заполнение структур для работы с кнопками */
struct btn btn_pin_12 = {
        .is_long_press      = 0,
        .was_short_pressed  = 0,
        .is_count_started   = 0,
        .counter            = 0
};
struct btn btn_pin_13 = {
        .is_long_press      = 0,
        .was_short_pressed  = 0,
        .is_count_started   = 0,
        .counter            = 0
};
struct btn btn_pin_14 = {
        .is_long_press      = 0,
        .was_short_pressed  = 0,
        .is_count_started   = 0,
        .counter            = 0
};

/* Заполнение структуры для ЦАП и реле */
struct comparison_parameters comparison_parameter = {
        .dac_A_dgt          = 0,
        .dac_A_volt         = 0,
        .dac_B_dgt          = 0,
        .dac_B_volt         = 0,
        .relay_state        = M12
};

/* Заполнение структуры для калибровки */
struct calibration_parameters calibration = {
        .is_tim_working         = 0,
        .tim3_overflow_counter  = 0,
        .tim4_overflow_counter  = 0,
        .g_tim3                 = 0,
        .g_tim4                 = 0,
        .v_polarity             = POSITIVE_POLARITY
};

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

/* Установка режима ЦАП А */
void SetDacA(void)
{
    switch (comparison_parameter.relay_state) {
        case M12:
            if ( comparison_parameter.dac_A_volt >= DevNVRAM.calibration_table.volt_min_mode_12 &&
                 comparison_parameter.dac_A_volt <= DevNVRAM.calibration_table.volt_max_mode_12)
            {
                comparison_parameter.dac_A_dgt = volt2dgt( &(DevNVRAM.calibration_table), &comparison_parameter, CH_A );
                DAC_AD5322_Ch1(&hspi1, comparison_parameter.dac_A_dgt);
                comparison_parameter.set_level_status = SUCCESS;
                break;
            }
            else {
                comparison_parameter.set_level_status = ERROR;
                break;
            }

        case M27:
            if ( comparison_parameter.dac_A_volt >= DevNVRAM.calibration_table.volt_min_mode_27 &&
                 comparison_parameter.dac_A_volt <= DevNVRAM.calibration_table.volt_max_mode_27)
            {
                comparison_parameter.dac_A_dgt = volt2dgt( &(DevNVRAM.calibration_table), &comparison_parameter, CH_A );
                DAC_AD5322_Ch1(&hspi1, comparison_parameter.dac_A_dgt);
                comparison_parameter.set_level_status = SUCCESS;
                break;
            }
            else {
                comparison_parameter.set_level_status = ERROR;
                break;
            }
        }
}

/* Установка режима ЦАП B */
void SetDacB(void)
{
    switch (comparison_parameter.relay_state) {
        case M12:
            if ( comparison_parameter.dac_B_volt >= DevNVRAM.calibration_table.volt_min_mode_12 &&
                 comparison_parameter.dac_B_volt <= DevNVRAM.calibration_table.volt_max_mode_12)
            {
                comparison_parameter.dac_B_dgt = volt2dgt( &(DevNVRAM.calibration_table), &comparison_parameter, CH_B);
                DAC_AD5322_Ch2(&hspi1, comparison_parameter.dac_B_dgt);
                comparison_parameter.set_level_status = SUCCESS;
                break;
            }
            else {
                comparison_parameter.set_level_status = ERROR;
                break;
            }

        case M27:
            if ( comparison_parameter.dac_B_volt >= DevNVRAM.calibration_table.volt_min_mode_27 &&
                 comparison_parameter.dac_B_volt <= DevNVRAM.calibration_table.volt_max_mode_27)
            {
                comparison_parameter.dac_B_dgt = volt2dgt( &(DevNVRAM.calibration_table), &comparison_parameter, CH_B);
                DAC_AD5322_Ch2(&hspi1, comparison_parameter.dac_B_dgt);
                comparison_parameter.set_level_status = SUCCESS;
                break;
            }
            else {
                comparison_parameter.set_level_status = ERROR;
                break;
            }
        }
}

/* Установка режимов */
void SetAllDAC(void)
{
    switch (comparison_parameter.relay_state) {
        case M12:
            if ( comparison_parameter.dac_A_volt >= DevNVRAM.calibration_table.volt_min_mode_12 &&
                 comparison_parameter.dac_A_volt <= DevNVRAM.calibration_table.volt_max_mode_12 &&
                 comparison_parameter.dac_B_volt >= DevNVRAM.calibration_table.volt_min_mode_12 &&
                 comparison_parameter.dac_B_volt <= DevNVRAM.calibration_table.volt_max_mode_12 )
            {
                comparison_parameter.dac_A_dgt = volt2dgt( &(DevNVRAM.calibration_table), &comparison_parameter, CH_A );
                comparison_parameter.dac_B_dgt = volt2dgt( &(DevNVRAM.calibration_table), &comparison_parameter, CH_B );
                DAC_AD5322_Ch1Ch2(&hspi1, comparison_parameter.dac_A_dgt, comparison_parameter.dac_B_dgt);
                comparison_parameter.set_level_status = SUCCESS;
                break;
            }
            else {
                comparison_parameter.set_level_status = ERROR;
                break;
            }
        case M27:
            if ( comparison_parameter.dac_A_volt >= DevNVRAM.calibration_table.volt_min_mode_27 &&
                 comparison_parameter.dac_A_volt <= DevNVRAM.calibration_table.volt_max_mode_27 &&
                 comparison_parameter.dac_B_volt >= DevNVRAM.calibration_table.volt_min_mode_27 &&
                 comparison_parameter.dac_B_volt <= DevNVRAM.calibration_table.volt_max_mode_27 )
            {
                comparison_parameter.dac_A_dgt = volt2dgt( &(DevNVRAM.calibration_table), &comparison_parameter, CH_A );
                comparison_parameter.dac_B_dgt = volt2dgt( &(DevNVRAM.calibration_table), &comparison_parameter, CH_B );
                DAC_AD5322_Ch1Ch2(&hspi1, comparison_parameter.dac_A_dgt, comparison_parameter.dac_B_dgt);
                comparison_parameter.set_level_status = SUCCESS;
                break;
            }
            else {
                comparison_parameter.set_level_status = ERROR;
                break;
            }
    }
}

uint32_t unit_test(void)
{
    uint32_t result = 0;

    /*проверка на вхождение в MIN m12*/
    comparison_parameter.relay_state = M12;
    comparison_parameter.dac_A_volt = DevNVRAM.calibration_table.volt_min_mode_12;
    comparison_parameter.dac_B_volt = DevNVRAM.calibration_table.volt_min_mode_12;
    SetDacA();
    if (comparison_parameter.set_level_status == ERROR)
    {
        result = (1 << 0);
    }
    SetDacB();
    if (comparison_parameter.set_level_status == ERROR)
    {
        result = (1 << 0);
    }

    /*проверка на выход из MIN m12*/
    comparison_parameter.dac_A_volt = DevNVRAM.calibration_table.volt_min_mode_12 - 1;
    comparison_parameter.dac_B_volt = DevNVRAM.calibration_table.volt_min_mode_12 - 1;
    SetDacA();
    if (comparison_parameter.set_level_status != ERROR)
    {
        result = (1 << 1);
    }
    SetDacB();
    if (comparison_parameter.set_level_status != ERROR)
    {
        result = (1 << 1);
    }

    /*проверка на выход из MAX m12*/
    comparison_parameter.dac_A_volt = DevNVRAM.calibration_table.volt_max_mode_12 + 1;
    comparison_parameter.dac_B_volt = DevNVRAM.calibration_table.volt_max_mode_12 + 1;
    SetDacA();
    if (comparison_parameter.set_level_status != ERROR)
    {
        result = (1 << 2);
    }
    SetDacB();
    if (comparison_parameter.set_level_status != ERROR)
    {
        result = (1 << 2);
    }

    /*проверка на выход из норм m12*/
    comparison_parameter.dac_A_volt = DevNVRAM.calibration_table.volt_max_mode_12;
    comparison_parameter.dac_B_volt = DevNVRAM.calibration_table.volt_max_mode_12;
    SetAllDAC();
    if (comparison_parameter.set_level_status == ERROR)
    {
        result = (1 << 3);
    }

    /*проверка на выход из мин m12*/
    comparison_parameter.dac_A_volt = DevNVRAM.calibration_table.volt_min_mode_12 - 1;
    comparison_parameter.dac_B_volt = DevNVRAM.calibration_table.volt_min_mode_12 - 1;
    SetAllDAC();
    if (comparison_parameter.set_level_status != ERROR)
    {
        result = (1 << 4);
    }

    /*проверка на выход из макс m12*/
    comparison_parameter.dac_A_volt = DevNVRAM.calibration_table.volt_max_mode_12 + 1;
    comparison_parameter.dac_B_volt = DevNVRAM.calibration_table.volt_max_mode_12 + 1;
    SetAllDAC();
    if (comparison_parameter.set_level_status != ERROR)
    {
        result = (1 << 5);
    }



    /*проверка на вхождение в MIN m27*/
    comparison_parameter.relay_state = M27;
    comparison_parameter.dac_A_volt = DevNVRAM.calibration_table.volt_min_mode_27;
    comparison_parameter.dac_B_volt = DevNVRAM.calibration_table.volt_min_mode_27;
    SetDacA();
    if (comparison_parameter.set_level_status == ERROR)
    {
        result = (1 << 6);
    }
    SetDacB();
    if (comparison_parameter.set_level_status == ERROR)
    {
        result = (1 << 6);
    }

    /*проверка на выход из MIN m27*/
    comparison_parameter.dac_A_volt = DevNVRAM.calibration_table.volt_min_mode_27 - 1;
    comparison_parameter.dac_B_volt = DevNVRAM.calibration_table.volt_min_mode_27 - 1;
    SetDacA();
    if (comparison_parameter.set_level_status != ERROR)
    {
        result = (1 << 7);
    }
    SetDacB();
    if (comparison_parameter.set_level_status != ERROR)
    {
        result = (1 << 7);
    }

    /*проверка на выход из MAX m27*/
    comparison_parameter.dac_A_volt = DevNVRAM.calibration_table.volt_max_mode_27 + 1;
    comparison_parameter.dac_B_volt = DevNVRAM.calibration_table.volt_max_mode_27 + 1;
    SetDacA();
    if (comparison_parameter.set_level_status != ERROR)
    {
        result = (1 << 8);
    }
    SetDacB();
    if (comparison_parameter.set_level_status != ERROR)
    {
        result = (1 << 8);
    }

    /*проверка на выход из норм m27 */
    comparison_parameter.dac_A_volt = DevNVRAM.calibration_table.volt_max_mode_27;
    comparison_parameter.dac_B_volt = DevNVRAM.calibration_table.volt_max_mode_27;
    SetAllDAC();
    if (comparison_parameter.set_level_status == ERROR)
    {
        result = (1 << 9);
    }

    /*проверка на выход из мин m27*/
    comparison_parameter.dac_A_volt = DevNVRAM.calibration_table.volt_min_mode_27 - 1;
    comparison_parameter.dac_B_volt = DevNVRAM.calibration_table.volt_min_mode_27 - 1;
    SetAllDAC();
    if (comparison_parameter.set_level_status != ERROR)
    {
        result = (1 << 10);
    }

    /*проверка на выход из макс m27*/
    comparison_parameter.dac_A_volt = DevNVRAM.calibration_table.volt_max_mode_27 + 1;
    comparison_parameter.dac_B_volt = DevNVRAM.calibration_table.volt_max_mode_27 + 1;
    SetAllDAC();
    if (comparison_parameter.set_level_status != ERROR)
    {
        result = (1 << 11);
    }

    /* Нужно сравнить таблицу загруженную во флеш и таблицу, которая должна быть там */
    /*  */

    return result;
}

/*---------------------------------------------------------------------------*/
inline void EnableTIM3(void)
{
	calibration.is_tim_working = 1;
}

inline uint16_t GetTIM3(void)
{
	return calibration.g_tim3;
}

inline void resValTIM3(void)
{
    calibration.g_tim4 = 0;
}

/*---------------------------------------------------------------------------*/
inline void EnableTIM4(void)
{
	calibration.is_tim_working = 0;
}

inline uint16_t GetTIM4(void)
{
	return calibration.g_tim4;
}

inline void resValTIM4(void)
{
	calibration.g_tim4 = 0;
}

/*---------------------------------------------------------------------------*/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	uint16_t periodTIM3, pulseWidthTIM3, periodTIM4, pulseWidthTIM4;

	if (calibration.is_tim_working == 1)
	{
		if (htim->Instance == TIM3)
		{
			if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
			{
				periodTIM3      = HAL_TIM_ReadCapturedValue(&htim3, TIM_CHANNEL_1);
				pulseWidthTIM3  = HAL_TIM_ReadCapturedValue(&htim3, TIM_CHANNEL_2);

				TIM3->CNT = 0;

				int16_t deltaTIM3   = (int16_t)periodTIM3 - (int16_t)pulseWidthTIM3;
				deltaTIM3           = (deltaTIM3 < 0) ? (-1 * deltaTIM3) : deltaTIM3;
				calibration.g_tim3  = deltaTIM3;
			}
		}
	}
	else
	{
		if (htim->Instance == TIM4)
		{
			if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
			{
				periodTIM4      = HAL_TIM_ReadCapturedValue(&htim4, TIM_CHANNEL_1);
				pulseWidthTIM4  = HAL_TIM_ReadCapturedValue(&htim4, TIM_CHANNEL_2);

				TIM4->CNT = 0;

				int16_t deltaTIM4   = (int16_t)periodTIM4 - (int16_t)pulseWidthTIM4;
				deltaTIM4           = (deltaTIM4 < 0) ? (-1 * deltaTIM4) : deltaTIM4;
				calibration.g_tim4  = deltaTIM4;
			}
		}
	}
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

volatile uint16_t volt_ADC = 0;

inline uint16_t GetADC(void)
{
	return volt_ADC;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    /* Check if the interrupt comes from ACD1 */
	if (hadc->Instance == ADC1) {
		volt_ADC = HAL_ADC_GetValue(&hadc1);
	}
}

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
  calib_table_init( &DevNVRAM.calibration_table );

  HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);
  HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_2);
  HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_1);
  HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_2);

  SetAllDAC();

  HAL_ADCEx_Calibration_Start(&hadc1);
  HAL_ADC_Start_IT(&hadc1);

//  if (unit_test() != 0) {
//      HardFault_Handler();
//  }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
	    if ( usb_rx_data.is_received == true ) {
	        usb_rx_handler(&usb_rx_data);
        }
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

  USB_Reset();

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

  /*Configure GPIO pins : PB12 PB13 PB14 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

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
	//	 printf("Wrong parameters value: file %s on line %d\r\n", file, line);
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
