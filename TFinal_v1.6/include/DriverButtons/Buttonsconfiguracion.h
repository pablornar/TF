/*
 *
 */

#ifndef BUTTONSCONFIGURACION_H_
#define BUTTONSCONFIGURACION_H_

#include "Driverlcd/Driverlcd.h"
/*
 * Funcion para configurar los botnes
 */
//UTFT_Buttons(UTFT *ptrUTFT, URTouch *ptrURTouch)
void UTFT_Buttons()
{
	//_UTFT = ptrUTFT;
	//_URTouch = ptrURTouch;
	deleteAllButtons();
	_color_text				= VGA_WHITE;
	_color_text_inactive	= VGA_GRAY;
	_color_background		= VGA_BLUE;
	_color_border			= VGA_WHITE;
	_color_hilite			= VGA_RED;
	_font_text				= NULL;
	_font_symbol			= NULL;
}


/*
 * Funcion para agregar botones flags en 0 es boton habilitado, en 1 es desabilitado
 */
int addButton(uint16_t x, uint16_t y, uint16_t width, uint16_t height, char *label, uint16_t flags)
{
	int btcnt = 0;

	while (((buttons[btcnt].flags & BUTTON_UNUSED) == 0) && (btcnt<MAX_BUTTONS))
		btcnt++;

	if (btcnt == MAX_BUTTONS)
		return -1;
	else
	{
		buttons[btcnt].pos_x  = x;
		buttons[btcnt].pos_y  = y;
		buttons[btcnt].width  = width;
		buttons[btcnt].height = height;
		buttons[btcnt].flags  = flags;
		buttons[btcnt].label  = label;
		buttons[btcnt].data   = NULL;
		return btcnt;
	}
}

/*
 * Funcion para agregar botones con bitmaps
 */
int addButton_bitmap(uint16_t x, uint16_t y, uint16_t width, uint16_t height, bitmapdatatype data, uint16_t flags)
{
	int btcnt = 0;

	while (((buttons[btcnt].flags & BUTTON_UNUSED) == 0) && (btcnt<MAX_BUTTONS))
		btcnt++;

	if (btcnt == MAX_BUTTONS)
		return -1;
	else
	{
		buttons[btcnt].pos_x  = x;
		buttons[btcnt].pos_y  = y;
		buttons[btcnt].width  = width;
		buttons[btcnt].height = height;
		buttons[btcnt].flags  = flags | BUTTON_BITMAP;
		buttons[btcnt].label  = NULL;
		buttons[btcnt].data   = data;
		return btcnt;
	}
}

/*
 * Funcion para dibujar los botones
 */
void drawButtons()
{
	for (int i=0;i<MAX_BUTTONS;i++)
	{
		if ((buttons[i].flags & BUTTON_UNUSED) == 0)
			drawButton(i);
	}
}

/*
 * Funcion para dibujar un boton en particular
 */
void drawButton(int buttonID)
{
	int		text_x, text_y;
	uint8_t	*_font_current = getFont();
	uint32_t _current_color = getColor();
	uint32_t _current_back  = getBackColor();

	if (buttons[buttonID].flags & BUTTON_BITMAP)
	{
		drawBitmap(buttons[buttonID].pos_x, buttons[buttonID].pos_y, buttons[buttonID].width, buttons[buttonID].height, buttons[buttonID].data,1);
		if (!(buttons[buttonID].flags & BUTTON_NO_BORDER))
		{
			if ((buttons[buttonID].flags & BUTTON_DISABLED)){
				setColor(_color_text_inactive);
			}
			else{
				setColor(_color_border);
				drawRectangulo(buttons[buttonID].pos_x, buttons[buttonID].pos_y, buttons[buttonID].pos_x+buttons[buttonID].width, buttons[buttonID].pos_y+buttons[buttonID].height);
			}
		}
	}
	else
	{
		//funciones del driver UTFT
		setColor(_color_background);
		drawfillRoundRect(buttons[buttonID].pos_x, buttons[buttonID].pos_y, buttons[buttonID].pos_x+buttons[buttonID].width, buttons[buttonID].pos_y+buttons[buttonID].height);
		setColor(_color_border);
		drawRoundRect(buttons[buttonID].pos_x, buttons[buttonID].pos_y, buttons[buttonID].pos_x+buttons[buttonID].width, buttons[buttonID].pos_y+buttons[buttonID].height);

		if (buttons[buttonID].flags & BUTTON_DISABLED)
			setColor(_color_text_inactive);
		else
			setColor(_color_text);
		if (buttons[buttonID].flags & BUTTON_SYMBOL)
		{
			setFont(_font_symbol);
			text_x = (buttons[buttonID].width/2) - (getFontXsize()/2) + buttons[buttonID].pos_x;
			text_y = (buttons[buttonID].height/2) - (getFontYsize()/2) + buttons[buttonID].pos_y;
		}
		else
		{
			setFont(_font_text);
			text_x = ((buttons[buttonID].width/2) - ((strlen(buttons[buttonID].label) * getFontXsize())/2)) + buttons[buttonID].pos_x;
			text_y = (buttons[buttonID].height/2) - (getFontYsize()/2) + buttons[buttonID].pos_y;
		}
		setBackColor(_color_background);
		setColor(_color_text);
		print(buttons[buttonID].label, text_x, text_y,0);
		if ((buttons[buttonID].flags & BUTTON_SYMBOL) && (buttons[buttonID].flags & BUTTON_SYMBOL_REP_3X))
		{
			print(buttons[buttonID].label, text_x-getFontXsize(), text_y,0);
			print(buttons[buttonID].label, text_x+getFontXsize(), text_y,0);
		}
	}
	setFont(_font_current);
	setColor(_current_color);
	setBackColor(_current_back);
}

/*
 * Funcion para habilitar los botones
 */
void enableButton(int buttonID, bool redraw)
{
	if (!(buttons[buttonID].flags & BUTTON_UNUSED))
	{
		buttons[buttonID].flags = buttons[buttonID].flags & ~BUTTON_DISABLED;
		if (redraw)
			drawButton(buttonID);
	}
}

/*
 * Funcion para desbilitar los botones
 */
void disableButton(int buttonID, bool redraw)
{
	if (!(buttons[buttonID].flags & BUTTON_UNUSED))
	{
		buttons[buttonID].flags = buttons[buttonID].flags | BUTTON_DISABLED;
		if (redraw)
			drawButton(buttonID);
	}
}

/*
 *
 */
void relabelButton(int buttonID, char *label, bool redraw)
{
	if (!(buttons[buttonID].flags & BUTTON_UNUSED))
	{
		buttons[buttonID].label = label;
		if (redraw)
			drawButton(buttonID);
	}
}

/*
 *
 */
bool buttonEnabled(int buttonID)
{
	return !(buttons[buttonID].flags & BUTTON_DISABLED);
}

/*
 *
 */
void deleteButton(int buttonID)
{
	if (!(buttons[buttonID].flags & BUTTON_UNUSED))
		buttons[buttonID].flags = BUTTON_UNUSED;
}

/*
 *
 */
void deleteAllButtons()
{
	for (int i=0;i<MAX_BUTTONS;i++)
	{
		buttons[i].pos_x=0;
		buttons[i].pos_y=0;
		buttons[i].width=0;
		buttons[i].height=0;
		buttons[i].flags=BUTTON_UNUSED;
		buttons[i].label="";
	}
}

/*
 *
 */
void setButtonColors(uint32_t atxt, uint32_t iatxt, uint32_t brd, uint32_t brdhi, uint32_t back)
{
	_color_text				= atxt;
	_color_text_inactive	= iatxt;
	_color_background		= back;
	_color_border			= brd;
	_color_hilite			= brdhi;
}

/*
 * Para establecer el font de los botones
 */
void setTextFont(uint8_t* font)
{
	_font_text = font;
}

/*
 * para establecer el simbolo
 */
void setSymbolFont(uint8_t* font)
{
	_font_symbol = font;
}

/*
 * funcion para devolver el boton que se presiono y cambiar el color del borde
 */
int checkButtons()
{
    if (dataAvailable() == true)
    {
		readtouch();
		int		result = -1;
		int		touch_x = getX();
		int		touch_y = getY();
		uint32_t	_current_color = getColor();

		for (int i=0;i<MAX_BUTTONS;i++)
		{
			if (((buttons[i].flags & BUTTON_UNUSED) == 0) && ((buttons[i].flags & BUTTON_DISABLED) == 0) && (result == -1))
			{
				if ((touch_x >= buttons[i].pos_x) && (touch_x <= (buttons[i].pos_x + buttons[i].width)) && (touch_y >= buttons[i].pos_y) && (touch_y <= (buttons[i].pos_y + buttons[i].height)))
					result = i;
			}
		}
		if (result != -1)
		{
			if (!(buttons[result].flags & BUTTON_NO_BORDER))
			{
				setColor(_color_hilite);
				if (buttons[result].flags & BUTTON_BITMAP)
					drawRectangulo(buttons[result].pos_x, buttons[result].pos_y, buttons[result].pos_x+buttons[result].width, buttons[result].pos_y+buttons[result].height);
				else
					drawRoundRect(buttons[result].pos_x, buttons[result].pos_y, buttons[result].pos_x+buttons[result].width, buttons[result].pos_y+buttons[result].height);
			}
		}

		while (dataAvailable() == true) {};

		if (result != -1)
		{
			if (!(buttons[result].flags & BUTTON_NO_BORDER))
			{
				setColor(_color_border);
				if (buttons[result].flags & BUTTON_BITMAP)
					drawRectangulo(buttons[result].pos_x, buttons[result].pos_y, buttons[result].pos_x+buttons[result].width, buttons[result].pos_y+buttons[result].height);
				else
					drawRoundRect(buttons[result].pos_x, buttons[result].pos_y, buttons[result].pos_x+buttons[result].width, buttons[result].pos_y+buttons[result].height);
			}
		}

		setColor(_current_color);
		return result;
	}
	else
		return -1;
}



#endif // BUTTONSCONFIGURACION_H_
