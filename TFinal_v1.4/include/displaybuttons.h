/*
 *
 */

#ifndef	DISPLAYBUTTONS_H_
#define DISPLAYBUTTONS_H_

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

	uint32_t		_color_text, _color_text_inactive, _color_background, _color_border, _color_hilite;
	uint8_t		*_font_text, *_font_symbol;


#endif /* DISPLAYBUTTONS_H_ */
