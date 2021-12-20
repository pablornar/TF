/*
 *
 */

#ifndef DRIVERTOUCHLCD_H_
#define DRIVERTOUCHLCD_H_

#include "DriverTouch/displaytouch.h"	//libreria Touch general del display
#define ON     1
#define OFF    0
// ----------------------------------------------------------------------------

//variables
/*
struct D{
	uint16_t pin;
	GPIO_TypeDef* puerto;
};
struct C{
	uint16_t pin;
	GPIO_TypeDef* puerto;
};
struct E{
	uint16_t pin;
	GPIO_TypeDef* puerto;
};
struct B{
	uint16_t pin;
	GPIO_TypeDef* puerto;
};
*/
struct E T_CLK={ GPIO_PIN_3, GPIOE};
struct E T_CS={ GPIO_PIN_2, GPIOE};
struct E T_DIN={ GPIO_PIN_5, GPIOE};
struct E T_DOUT={ GPIO_PIN_4, GPIOE};
struct E T_IRQ={ GPIO_PIN_6, GPIOE};



//Funciones
//*******funciones de Libreria Inicio
extern void InitTouch(uint8_t orientation);

//*******funciones de Libreria Comandos
extern void readtouch();  //para leer la presion sobre el display en x e y
extern int16_t getX();	//para obtener el valor de x  en pixeles en funcion del tamanio del lcd
extern int16_t getY();	//para obtener el valor de y  en pixeles en funcion del tamanio del lcd
extern bool dataAvailable(); //para saber si alguien presiono el display
//*******funciones de Libreria Configuracion
extern void Touch(uint16_t tclk, uint16_t tcs, uint16_t din, uint16_t dout, uint16_t irq);
extern void setPrecision(uint8_t precision); //para establecer la precision de presion del display
extern void calibrateRead(); //para calibrar el display
extern void touch_WriteData(uint8_t data);
extern uint32_t touch_ReadData();

//*******funciones de Libreria graficos
//extern void setColorb(uint8_t r, uint8_t g, uint8_t b);


#include <DriverTouch/TouchLCDconfiguracion.h>  //agrega la libreria de configuracion de lcd touch
// ----------------------------------------------------------------------------

#endif // DRIVERTOUCHLCD_H_
