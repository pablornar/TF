/*
 * Programa para probar los timer, el systick, el uart y el conversor ad.
 * fecha: 06/12/2021
 */
// ----------------------------------------------------------------------------
#include "main.h"


// ----------------------------------------------------------------------------
//Variables
extern TIM_HandleTypeDef htim1;
extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc1;
uint32_t cont = 0;
uint32_t Fmuestreo = 1000000;
uint16_t datostx=101;
uint16_t ADCread=0;


// ----- main() ---------------------------------------------------------------
int main(int argc, char* argv[])
{
	  // Send a greeting to the trace device (skipped on Release).
	  trace_puts("Inico de programa");
	  // At this stage the system clock should have already been configured
	  // at high speed.
	  trace_printf("System clock: %u Hz\n", SystemCoreClock);


	 timer_start();

	  uint32_t seconds = 0;
	 //HAL_TIM_Base_Start_IT(&htim1);
	 //__HAL_TIM_SET_COUNTER(&htim1,0);  // set the counter value a 0
	  //HAL_ADC_Start(&hadc1);
  while (1)
    {
       // Add your code here.
    }
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
/*
 * Funciona para realizar el muestreo
 */
void muestreo(){
	cont++;
	if (cont >= (1000000/Fmuestreo)){
		cont=0;
		D1.puerto->ODR ^= D1.pin;
		HAL_ADC_Start(&hadc1);

		//GPIOE->ODR ^= GPIO_PIN_0;

		//HAL_GPIO_WritePin(D0.puerto, D0.pin, 1);
		while (HAL_ADC_PollForConversion(&hadc1, 255) != HAL_OK); //check if conversion is completed
		//while (HAL_ADC_PollForEvent(&hadc1, 1) != HAL_OK);
		//GPIOE->ODR ^= GPIO_PIN_0;
		D1.puerto->ODR ^= D1.pin;
		//HAL_GPIO_WritePin(D0.puerto,  D0.pin, 0);
		ADCread=HAL_ADC_GetValue(&hadc1);
		//trace_printf("ADC: %d \n", ADCread);
		//HAL_UART_Transmit(&huart1, (uint8_t *)&ADCread,2, 0xFFFF);

	}
}



