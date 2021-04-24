/*

uint32_t  timme = 0;
while(1)
{
        if((HAL_GetTick() - timme) > 1000) // интервал 1000мс = 1сек
        {
                // что-то делаем
                timme = HAL_GetTick();
        }
}
*/
//--------------------------------------------------------------------------
#define TEST_RELAY_BKP			0

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
#define TEST_DAC_WHILE 			0
#if  TEST_DAC_WHILE

	DAC_AD5322_Ch1(&hspi1, VDAC_A);
	DAC_AD5322_Ch2(&hspi1, VDAC_B);
	HAL_Delay(250);
#endif	/* TEST_DAC_WHILE */
//--------------------------------------------------------------------------
#define TEST_CALIBRATION_HL		0
#define TEST_CALIBRATION_LL		0

#if  TEST_CALIBRATION_HL

	// PB8 - inHL

	uint8_t flag_key1_press = 1;
	uint32_t time_key1_press= 0;

	uint8_t inLL_rd 		= 0;

	// PB9 - inLL

	uint8_t flag_key2_press = 1;
	uint32_t time_key2_press= 0;

	uint8_t inHL_rd 		= 0;
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
