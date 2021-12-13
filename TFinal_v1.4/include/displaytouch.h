/*
 * IncFile1.h
 *
 * Created: 24/02/2021 16:54:21
 *  Author: Pablo
 */


#ifndef	DISPLAYTOUCH_H_
#define DISPLAYTOUCH_H_

#include "cmsis_device.h"
#include "ButtonsFonts.h"

//POR DEFECTO
/*#define CAL_X 0x00378F66UL
#define CAL_Y 0x03C34155UL
#define CAL_S 0x000EF13FUL */

/*
//dEL DISPLAY CHICO 3,2
#define CAL_X 0x0034CEB0UL
#define CAL_Y 0x00200EE5UL
#define CAL_S 0x000EF18FUL
*/

/*
//dEL DISPLAY CHICO 3,2 modelo ILI9341_16
#define CAL_X 0x03D0C0ACUL
#define CAL_Y 0x03D90179UL
#define CAL_S 0x000EF13FUL
*/

/*
//DEL DISPLAY MEDIANO 5
#define CAL_X 0x00194FBEUL
#define CAL_Y 0x03B14110UL
#define CAL_S 0x8031F1DFUL
*/


//DEL DISPLAY GRANDE 7
#define CAL_X 0x00100FB2UL
#define CAL_Y 0x00604F72UL
#define CAL_S 0x8031F1DFUL

/*
#define CAL_X 0x000FCFC0UL
#define CAL_Y 0x00628F62UL
#define CAL_S 0x8031F1DFUL

#define CAL_X 0x000DCFB7UL
#define CAL_Y 0x00574F5BUL
#define CAL_S 0x8031F1DFUL
*/


#define PORTRAIT			0
#define LANDSCAPE			1

#define PREC_LOW			1
#define PREC_MEDIUM			2
#define PREC_HI				3
#define PREC_EXTREME		4

//regtype *P_CLK, *P_CS, *P_DIN, *P_DOUT, *P_IRQ;
//regsize B_CLK, B_CS, B_DIN, B_DOUT, B_IRQ;
		//uint16_t	T_CLK, T_CS, T_DIN, T_DOUT, T_IRQ;
		int16_t	TP_X ,TP_Y;
		long	_default_orientation;
		//uint8_t	orient;					YA ESTA DEFINIDO EN LCD
		uint8_t	prec;
		//uint8_t	display_model; ya esta definido en displaygraf
		long	 default_orientation, disp_x_sizeT, disp_y_sizeT;
		long	touch_x_left, touch_x_right, touch_y_top, touch_y_bottom;

#endif /* DISPLAYTOUCH_H_ */
