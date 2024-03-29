/*
 * Programa Trabajo final de la Especialidad en Sistemas Embebidos
 * version: 1.6
 * fecha inicio: 06/12/2021
 * fecha presentacion: xx/xx/2022
 * Observaciones:
 * 1: Para una lectura mas precisa se agrego un retardo en redtouch para poder estabilizar la senal de
 * CS y que realice la lectura del touch correctamente.
 * 2: Falta agregar un temporizador para la lectura de frecuencia ya que con el systick estoy limitado a 500ns de paso
 */

//---------------------Librerias-------------------------------------------------------
#include "main.h"


// ----- main() ---------------------------------------------------------------
int main(int argc, char* argv[]){
	//*******************Inicializacion de variables

	// Send a greeting to the trace device (skipped on Release).
	trace_puts("Inico de programa");
	// At this stage the system clock should have already been configured
	trace_printf("System clock: %u Hz\n", SystemCoreClock);

	/*configura lcd y selecciona el modelo*/
	Conflcd(CTE70, 38, 39, 40, 41);	//configura RS, WR, CS y rest pero no se usan por ahora vienen por defecto
	Touch(43, 45, 47, 49, 51); 	//tclk, tcs, tdin, dout e irq
	inicioLCD(LANDSCAPE); 		//inicializa LCD
	InitTouch(LANDSCAPE);		//inicializa el touch
	setPrecision(PREC_MEDIUM);	// setea la precision del touch

	UTFT_Buttons();				//inicializa los botones
	setFont(BigFont); 			//configura letra pantalla
	setTextFont(SmallFont); 		//configura letra de botones
	setSymbolFont(Dingbats1_XL); //
	clrScr();  					//borra lcd
	deleteAllButtons();		//borra los botones que pudieren quedar
	HAL_Delay(1000);		//delay de 1seg para esperar la estabilizacion
	//timer_start();
	uint32_t seconds = 0;
	//HAL_TIM_Base_Start_IT(&htim1);
	//__HAL_TIM_SET_COUNTER(&htim1,0);  // set the counter value a 0
	//HAL_ADC_Start(&hadc1);


	 //__ADC1_CLK_ENABLE();

	while (1)
	{

		menu();

	}
}

#pragma GCC diagnostic pop


/*
 * Funciona para realizar el muestreo
 */
void muestreo(){
	ADC_HandleTypeDef* hadc;

	hadc = &hadc1;

	cont++;

	//HAL_DAC_Start(&hdac, DAC_CHANNEL_1 );

	//HAL_DAC_Init(&hdac);


	if (cont >= (1000000/Fs)){		//para establecer la cantidad de cuenta segun la Fs, periodo minimo de cuenta de 500ns
		cont=0;
		GPIOE->ODR ^= GPIO_PIN_0;
		//while (HAL_ADC_PollForConversion(&hadc1, 255) != HAL_OK); //check if conversion is completed
		while(!(__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_EOC)));
		if(ADC_IS_SOFTWARE_START_REGULAR(hadc) && (hadc->Init.ContinuousConvMode == DISABLE) && (HAL_IS_BIT_CLR(hadc->Instance->SQR1, ADC_SQR1_L) ||
			   HAL_IS_BIT_CLR(hadc->Instance->CR2, ADC_CR2_EOCS)  ) ){
			/* Set ADC state */
			CLEAR_BIT(hadc->State, HAL_ADC_STATE_REG_BUSY);
			if (HAL_IS_BIT_CLR(hadc->State, HAL_ADC_STATE_INJ_BUSY))
			{
				 SET_BIT(hadc->State, HAL_ADC_STATE_READY);
			}
		}

		xn[i] = hadc->Instance->DR;

		//HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1,  DAC_ALIGN_12B_R, xn[i]);

		GPIOE->ODR ^= GPIO_PIN_0;

		//******Trigger-----------------
	if(trigger == 1){
		if (i == 0){
					i=1;
		}
		else if (i == 1){
			 if (((xn[i-1] < leveltriger+5) && (xn[i-1] > leveltriger-5)) && (xn[i]>leveltriger)){
					   bandtriger=1;
			 }
			 else {
				 i=0;
			 }
	     }

		if(bandtriger == 1){  //cuenta si el tigger fue habilitado
			i=i+1;
		}
	}
	else{
		i=i+1;
	}

		if(i > N){					//para preguntar si llego a la contidad de muestras
			bandtriger=0;
			i=0;
			/* Process locked */
			 //__HAL_LOCK(hadc);

			bandint=1;

			SysTick->CTRL = 0;    //Disable Systick

			//__HAL_ADC_DISABLE(hadc);							//desabilito el convesor adc

			//__HAL_UNLOCK(hadc);									//proces unlocked

		}
	}
}

/*
 * Funcion para crear un delay de useg
 */
void cont_delay_us(){
	contdelayus++;
}

/*
 * Funcion para el delay de us bloqueante
 */
void delay_us(long contdelay){
	bandelayus=1;
	contdelayus=0;
	timer_start();				//star counter
	while((2*contdelay) < contdelayus);			//espero a que llegue la cuenta establecidad
	contdelayus=0;
	SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
								   SysTick_CTRL_TICKINT_Msk   |
								   SysTick_CTRL_ENABLE_Pos ;         /* Disable SysTick IRQ and SysTick Timer */
	bandelayus=0;
}

//D1.puerto->ODR ^= D1.pin;
//xn[i] = HAL_ADC_GetValue(&hadc1);
		//trace_printf("ADC: %d \n", ADCread);
		//HAL_UART_Transmit(&huart1, (uint8_t *)&ADCread,2, 0xFFFF);
		//D1.puerto->ODR ^= D1.pin;
				//HAL_GPIO_WritePin(D0.puerto,  D0.pin, 0);
//HAL_ADC_Start(&hadc1);
		//HAL_GPIO_WritePin(D0.puerto, D0.pin, 1);
		//while (HAL_ADC_PollForConversion(&hadc1, 255) != HAL_OK); //check if conversion is completed
		//while (HAL_ADC_PollForEvent(&hadc1, 1) != HAL_OK);
