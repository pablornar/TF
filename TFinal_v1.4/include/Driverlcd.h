/*
 *
 */

#ifndef DRIVERLCD_H_
#define DRIVERLCD_H_

#define ON     1
#define OFF    0
// ----------------------------------------------------------------------------
#include "displaygraf.h"	//libreria general del display
//variables
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
struct C D0={ GPIO_PIN_7, GPIOC};
struct C D1={ GPIO_PIN_8, GPIOC};
struct D D2={ GPIO_PIN_15, GPIOD};
struct C D3={ GPIO_PIN_6, GPIOC};
struct D D4={ GPIO_PIN_13, GPIOD};
struct D D5={ GPIO_PIN_14, GPIOD};
struct D D6={ GPIO_PIN_11, GPIOD};
struct D D7={ GPIO_PIN_12, GPIOD};
struct D D8={ GPIO_PIN_9, GPIOD};
struct D D9={ GPIO_PIN_10, GPIOD};
struct B D10={ GPIO_PIN_15, GPIOB};
struct D D11={ GPIO_PIN_8, GPIOD};
struct B D12={ GPIO_PIN_13, GPIOB};
struct B D13={ GPIO_PIN_14, GPIOB};
struct B D14={ GPIO_PIN_12, GPIOB};
struct B D15={ GPIO_PIN_11, GPIOB};
struct B RS={ GPIO_PIN_10, GPIOB};
struct E WR={ GPIO_PIN_15, GPIOE};
struct E CS={ GPIO_PIN_14, GPIOE};
struct E REST={ GPIO_PIN_13, GPIOE};

//Funciones
//*******funciones de Libreria Inicio
extern void inicioLCD(uint8_t orientation);
extern void  initlcd(void);

//*******funciones de Libreria Comandos
extern void clrScr(void);
extern void clrXY(void);
extern void _fast_fill_16(int ch, int cl, long pix);
extern void setXY(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);
extern void setXYa(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);
extern void setFont(uint8_t* font);

//*******funciones de Libreria Configuracion
extern void Conflcd(int model, int RS, int WR, int CS, int RST);
extern void _set_direction_registers(uint8_t mode);
extern void LCD_Writ_Bus(char VH, char VL, uint8_t mode);
extern void LCD_Write_DATA(char VL);
extern void LCD_Write_DATAb(char VH, char VL);
extern void LCD_Write_COM(char VL);

//*******funciones de Libreria graficos
extern void setColorb(uint8_t r, uint8_t g, uint8_t b);
extern void setColor(int color);
extern void setBackColorb(uint8_t r, uint8_t g, uint8_t b);
extern void setBackColor(uint32_t color);
extern void drawHLine(int x, int y, int l);
extern void drawVLine(int x, int y, int l);
extern void drawLine(int x1, int y1, int x2, int y2);
extern void setPixel(int color);
extern void drawPixel(int x, int y);
extern void printCharAscii(uint8_t c, int x, int y);
extern void rotateChar(uint8_t c, int x, int y, int pos, int deg);
extern void print(char *st, int x, int y, int deg);
extern void printNumI(long num, int x, int y, int length, char filler);
extern void printNumF(double num, uint8_t dec, int x, int y, char divider, int length, char filler);
extern void _convert_float(char *buf, double num, int width, uint8_t prec);

extern void drawRectangulo(int x1, int y1, int x2, int y2);
extern void drawRoundRect(int x1, int y1, int x2, int y2);
extern void drawfillRect(int x1, int y1, int x2, int y2);
extern void drawCircle(int x, int y, int radius);
extern void drawfillCircle(int x, int y, int radius);
extern void drawfillRoundRect(int x1, int y1, int x2, int y2);
extern void drawBitmap(int x, int y, int sx, int sy, bitmapdatatype data, int scale);
extern uint32_t getColor();
extern uint32_t getBackColor();
extern uint8_t* getFont();
extern uint8_t getFontXsize();
extern uint8_t getFontYsize();


#include <LCDFconfiguracion.h>  //agrega la libreria de configuracion de lcd
#include <LCDFcomandos.h>  //agrega la libreria de comandos.
#include <LCDFinicio.h>  //agrega la libreria de inicializacion de lcd
#include <LCDFgraficos.h>  //agrega la libreria de graficos

// ----------------------------------------------------------------------------

#endif // DRIVERLCD_H_
