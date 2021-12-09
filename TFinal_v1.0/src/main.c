/*
 * Programa para probar los timer, el systick, el uart y el conversor ad.
 * fecha: 06/12/2021
 */
// ----------------------------------------------------------------------------
#include "main.h"
#include "displaygraf.h"	//libreria general del display

// ----------------------------------------------------------------------------
//+++++++++++++++++++++variables de display
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];
extern uint8_t Dingbats1_XL[];
short ResH = 800;
short ResV = 480;
float valor;

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


	  /*configura lcd y selecciona el modelo*/
	  	Conflcd(CTE70, 38, 39, 40, 41);	//configura RS, WR, CS y rest pero no se usan por ahora vienen por defecto
	  	inicioLCD(LANDSCAPE); //inicializa LCD
	  	setFont(BigFont); //configura letra pantalla
	  	clrScr();  //borra lcd


	  	HAL_Delay(1000);
	  	valor=3.3/2;


	//timer_start();

	  uint32_t seconds = 0;
	 //HAL_TIM_Base_Start_IT(&htim1);
	 //__HAL_TIM_SET_COUNTER(&htim1,0);  // set the counter value a 0
	  //HAL_ADC_Start(&hadc1);
  while (1)
    {
	  	setColor(VGA_GREEN);
		drawPixel(380, 470);
		HAL_Delay(500);
		drawVLine(100, 100, 200);
		HAL_Delay(500);
		drawHLine(100, 100, 400);
		HAL_Delay(500);
		setColor(VGA_WHITE);
		drawLine(200, 200, 400, 200);
		HAL_Delay(500);
		setColor(VGA_RED);
		setFont(BigFont);
		printCharAscii(97, 300, 350);
		HAL_Delay(500);
		drawRectangulo(200,100,500,200);
		HAL_Delay(500);
		drawRoundRect(200,300,500,400);
		//delay(500);
		//setBackColor(VGA_BLUE);
		//drawfillRect(200,100,500,200);
		//delay(500);
		//drawCircle(300,300,50);
		//delay(500);
		//setColor(VGA_BLUE);
		//drawfillCircle(300,300,50);
		HAL_Delay(500);
		print("hola",300,400,90);
		HAL_Delay(500);
		printNumI(12,700,400,2,0);
		HAL_Delay(500);
		printNumF(valor,4,550,400,'.',4,' ');
		HAL_Delay(500);
		clrScr();
		HAL_Delay(500);
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
		//D1.puerto->ODR ^= D1.pin;
		HAL_ADC_Start(&hadc1);

		//GPIOE->ODR ^= GPIO_PIN_0;

		//HAL_GPIO_WritePin(D0.puerto, D0.pin, 1);
		while (HAL_ADC_PollForConversion(&hadc1, 255) != HAL_OK); //check if conversion is completed
		//while (HAL_ADC_PollForEvent(&hadc1, 1) != HAL_OK);
		//GPIOE->ODR ^= GPIO_PIN_0;
		//D1.puerto->ODR ^= D1.pin;
		//HAL_GPIO_WritePin(D0.puerto,  D0.pin, 0);
		ADCread=HAL_ADC_GetValue(&hadc1);
		//trace_printf("ADC: %d \n", ADCread);
		//HAL_UART_Transmit(&huart1, (uint8_t *)&ADCread,2, 0xFFFF);

	}
}



