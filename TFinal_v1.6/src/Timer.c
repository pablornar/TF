/*
 *
 */

#include "Timer.h"
#include "cortexm/ExceptionHandlers.h"

// ----------------------------------------------------------------------------
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim6;
extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc1;
extern DAC_HandleTypeDef hdac;
extern uint16_t datostx;
extern uint16_t ADCread;
extern long bandelayus;

#if defined(USE_HAL_DRIVER)
//void HAL_IncTick(void);
#endif

// Forward declarations.

void timer_tick (void);

// ----------------------------------------------------------------------------

volatile timer_ticks_t timer_delayCount;

// ----------------------------------------------------------------------------

void timer_start (void)
{
  // Use SysTick as reference for the delay loops.
	//Valor de recarga = SysTick Counter Clock (Hz) x Temporización deseada (s)
	//timeint=N * clock;
	//168 * (1/168Mhz)=1us
  SysTick_Config (SystemCoreClock / TIMER_FREQUENCY_HZ);
}

void timer_sleep (timer_ticks_t ticks)
{
  timer_delayCount = ticks;

  // Busy wait until the SysTick decrements the counter to zero.
  while (timer_delayCount != 0u);
}

void timer_tick (void)
{
  // Decrement to zero the counter used by the delay routine.
  if (timer_delayCount != 0u)
    {
      --timer_delayCount;
    }
}


// ----- SysTick_Handler() ----------------------------------------------------

void
SysTick_Handler (void)
{

#if defined(USE_HAL_DRIVER)
  HAL_IncTick();
#endif
  //timer_tick ();
  if (bandelayus == 0){
	  muestreo();
  }
  else if(bandelayus == 1){
	  cont_delay_us();
  }

}


//************************Handler del timer 1
void TIM1_UP_TIM10_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */
	//HAL_GPIO_TogglePin(GPIOE,  GPIO_PIN_0);

	//HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
	HAL_ADC_Start(&hadc1);
	GPIOE->ODR ^= GPIO_PIN_0;
	while (HAL_ADC_PollForConversion(&hadc1, 100) != HAL_OK); //check if conversion is completed
	GPIOE->ODR ^= GPIO_PIN_0;
	ADCread=HAL_ADC_GetValue(&hadc1);

	//tiempo de conversion es:
	// ( adcresolution + adcsampletime +2.5)/(pcclok2/prescaleradc)
	//   (15 + 3 + 2,5)/(84mzh / 4)=0.9761us fm=1.02mhz  llega a 1.2useg
	//en continue mode = enable si llega a 0.976useg.
	//	(15 + 3 + 2,5)/(84mzh / 2)=0.4880us fm=2.04mhz  no se cumple llega a 0.9useg
	 trace_printf("ADC: %d \n", ADCread);
	//HAL_ADC_GetValue(&hadc1);
	HAL_UART_Transmit(&huart1, (uint8_t *)&ADCread,2, 0xFFFF);
	//HAL_GPIO_WritePin(GPIOE,  GPIO_PIN_0, 0);


	HAL_TIM_IRQHandler(&htim1);

	//HAL_GPIO_WritePin(GPIOE,  GPIO_PIN_0, 1);
	//__HAL_TIM_CLEAR_FLAG (& htim2, TIM_FLAG_UPDATE);

	//__HAL_TIM_GET_COUNTER(&htim2);  // wait for the counter to reach the us input in the parameter

	// __HAL_TIM_SET_COUNTER(&htim2,0);  // set the counter value a 0
	// __HAL_TIM_GET_COUNTER(&htim2);  // wait for the counter to reach the us input in the parameter
	//__HAL_TIM_SET_COUNTER(&htim2,0);
  /* USER CODE END TIM2_IRQn 0 */
  //HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles TIM6 global interrupt, DAC1 and DAC2 underrun error interrupts.
  */
//void TIM6_DAC_IRQHandler(void)
//{
  /* USER CODE BEGIN TIM6_DAC_IRQn 0 */

  /* USER CODE END TIM6_DAC_IRQn 0 */
	//HAL_DAC_IRQHandler(&hdac);
   // HAL_TIM_IRQHandler(&htim6);
  /* USER CODE BEGIN TIM6_DAC_IRQn 1 */
 // HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_0);
  /* USER CODE END TIM6_DAC_IRQn 1 */
//}

// ----------------------------------------------------------------------------
