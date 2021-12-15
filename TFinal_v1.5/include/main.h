/*
 *
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "cmsis_device.h"

#define bitmapdatatype unsigned short*
/*
struct _current_font {
	uint8_t* font;
	uint8_t x_size;
	uint8_t y_size;
	uint8_t offset;
	uint8_t numchars;
};

struct _current_font cfont;

#define MAX_BUTTONS	20	// Maximum number of buttons available at one time

// Define presets for button status
#define BUTTON_DISABLED			0x0001
#define BUTTON_SYMBOL			0x0002
#define BUTTON_SYMBOL_REP_3X	0x0004
#define BUTTON_BITMAP			0x0008
#define BUTTON_NO_BORDER		0x0010
#define BUTTON_UNUSED			0x8000

typedef struct
{
  uint16_t			pos_x, pos_y, width, height;
  uint16_t			flags;
  char				*label;
  bitmapdatatype	data;
} button_type;
button_type	buttons[MAX_BUTTONS];
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "cmsis_device.h"
#include "diag/Trace.h"
#include "cmsis_device.h"
#include "Driverlcd/Driverlcd.h"
#include "DriverTouch/DriverTouchlcd.h"
#include "DriverButtons/Driverbuttons.h"
#include "Timer.h"
#include "FuncionesMath.h"
#include "Funciones_Variables.h"
#include "Menu.h"
#include "Osc.h"
#include "FFT.h"
#include "Filtros.h"

// ----------------------------------------------------------------------------

//variables

//Funciones
void muestreo(void);

// ----------------------------------------------------------------------------

#endif // MAIN_H_
