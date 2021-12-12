/*
 *
 */


#ifndef	DRIVERBUTTONS_H_
#define DRIVERBUTTONS_H_

#include "displaybuttons.h"	//libreria de botones

//Funciones
//*******funciones de Libreria Inicio
//extern void InitTouch(uint8_t orientation);

//*******funciones de Libreria Comandos
extern int addButton(uint16_t x, uint16_t y, uint16_t width, uint16_t height, char *label, uint16_t flags);
extern int addButton_bitmap(uint16_t x, uint16_t y, uint16_t width, uint16_t height, bitmapdatatype data, uint16_t flags);
extern void drawButtons();
extern void drawButton(int buttonID);
extern void enableButton(int buttonID, bool redraw);
extern void disableButton(int buttonID, bool redraw);
extern void relabelButton(int buttonID, char *label, bool redraw);
extern bool buttonEnabled(int buttonID);
extern void deleteButton(int buttonID);
extern void deleteAllButtons();

//*******funciones de Libreria Configuracion
extern void UTFT_Buttons();
extern void setTextFont(uint8_t* font);
extern void setSymbolFont(uint8_t* font);
extern void setButtonColors(uint32_t atxt, uint32_t iatxt, uint32_t brd, uint32_t brdhi, uint32_t back);
extern int checkButtons();

//*******funciones de Libreria graficos
//extern void setColorb(uint8_t r, uint8_t g, uint8_t b);

#include <Buttonsconfiguracion.h>  //agrega la libreria de configuracion de lcd touch

#endif // DRIVERBUTTONS_H_
