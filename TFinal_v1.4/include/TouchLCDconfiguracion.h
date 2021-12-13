/*
 *
 */

#ifndef TOUCHLCDCONFIGURACION_H_
#define TOUCHLCDCONFIGURACION_H_

//**************Funcion para configuracion de pines no se utiliza aun
void Touch(uint16_t tclk, uint16_t tcs, uint16_t din, uint16_t dout, uint16_t irq)
{
	//T_CLK	= tclk;
	//T_CS	= tcs;
	//T_DIN	= din;
	//T_DOUT	= dout;
	//T_IRQ	= irq;
}

//*****************INICIALIZO EL TOUCH
void InitTouch(uint8_t orientation)
{
	orient					= orientation;
	_default_orientation	= CAL_S>>31;
	touch_x_left			= (CAL_X>>14) & 0x3FFF;
	touch_x_right			= CAL_X & 0x3FFF;
	touch_y_top				= (CAL_Y>>14) & 0x3FFF;
	touch_y_bottom			= CAL_Y & 0x3FFF;
	disp_x_sizeT				= (CAL_S>>12) & 0x0FFF;
	disp_y_sizeT				= CAL_S & 0x0FFF;
	prec					= 10;

	/*
	P_CLK	= portOutputRegister(digitalPinToPort(T_CLK));
	B_CLK	= digitalPinToBitMask(T_CLK);
	P_CS	= portOutputRegister(digitalPinToPort(T_CS));
	B_CS	= digitalPinToBitMask(T_CS);
	P_DIN	= portOutputRegister(digitalPinToPort(T_DIN));
	B_DIN	= digitalPinToBitMask(T_DIN);
	P_DOUT	= portInputRegister(digitalPinToPort(T_DOUT));
	B_DOUT	= digitalPinToBitMask(T_DOUT);
	P_IRQ	= portInputRegister(digitalPinToPort(T_IRQ));
	B_IRQ	= digitalPinToBitMask(T_IRQ);

	pinMode(T_CLK,  OUTPUT);
    pinMode(T_CS,   OUTPUT);
    pinMode(T_DIN,  OUTPUT);
    pinMode(T_DOUT, INPUT);
    pinMode(T_IRQ,  OUTPUT);
	*/

	//sbi(P_CS, B_CS);
	HAL_GPIO_WritePin(T_CS.puerto, T_CS.pin, ON);
	//sbi(P_CLK, B_CLK);
	HAL_GPIO_WritePin(T_CLK.puerto, T_CLK.pin, ON);
	//sbi(P_DIN, B_DIN);
	HAL_GPIO_WritePin(T_DIN.puerto, T_DIN.pin, ON);
	//sbi(P_IRQ, B_IRQ);
	//HAL_GPIO_WritePin(T_DIN.puerto, T_DIN.pin, ON);
}


/*
 * FUNCION para la lectura del touch
 */
void readtouch()
{
	unsigned long tx=0, temp_x=0;
	unsigned long ty=0, temp_y=0;
	unsigned long minx=99999, maxx=0;
	unsigned long miny=99999, maxy=0;
	int datacount=0;

	//cbi(P_CS, B_CS);
	HAL_GPIO_WritePin(T_CS.puerto, T_CS.pin, OFF);

	//pinMode(T_IRQ,  INPUT);
	for (int i=0; i<prec; i++)
	{
		//if (!rbi(P_IRQ, B_IRQ))
		if(!HAL_GPIO_ReadPin(T_IRQ.puerto, T_IRQ.pin))
		{
			touch_WriteData(0x90);
			//pulse_high(P_CLK, B_CLK);
			HAL_GPIO_WritePin(T_CLK.puerto, T_CLK.pin, ON);
			HAL_GPIO_WritePin(T_CLK.puerto, T_CLK.pin, OFF);
			temp_x=touch_ReadData();

			//if (!rbi(P_IRQ, B_IRQ))
			//if(!HAL_GPIO_ReadPin(T_IRQ.puerto, T_IRQ.pin))
			//{
				touch_WriteData(0xD0);
				//pulse_high(P_CLK, B_CLK);
				HAL_GPIO_WritePin(T_CLK.puerto, T_CLK.pin, ON);
				HAL_GPIO_WritePin(T_CLK.puerto, T_CLK.pin, OFF);
				temp_y=touch_ReadData();

				if ((temp_x>0) && (temp_x<4096) && (temp_y>0) && (temp_y<4096))
				{
					tx+=temp_x;
					ty+=temp_y;
					if (prec>5)
					{
						if (temp_x<minx)
							minx=temp_x;
						if (temp_x>maxx)
							maxx=temp_x;
						if (temp_y<miny)
							miny=temp_y;
						if (temp_y>maxy)
							maxy=temp_y;
					}
					datacount++;
				}
			//}
		}
	}
	//pinMode(T_IRQ,  OUTPUT); vv*****************ver si hace falta cambiar de input a output

	if (prec>5)
	{
		tx = tx-(minx+maxx);
		ty = ty-(miny+maxy);
		datacount -= 2;
	}

	//sbi(P_CS, B_CS);
	HAL_GPIO_WritePin(T_CS.puerto, T_CS.pin, ON);
	if ((datacount==(prec-2)) || (datacount==PREC_LOW))
	{
		if (orient == _default_orientation)
		{
			TP_X=ty/datacount;
			TP_Y=tx/datacount;
		}
		else
		{
			TP_X=tx/datacount;
			TP_Y=ty/datacount;
		}
	}
	else
	{
		TP_X=-1;
		TP_Y=-1;
	}
}


/*
 * funcion para saber si alguien presiono
 */
bool dataAvailable()
{
	bool avail;
	//pinMode(T_IRQ,  INPUT);
	avail = !(HAL_GPIO_ReadPin(T_IRQ.puerto, T_IRQ.pin));
	//pinMode(T_IRQ,  OUTPUT);
	return avail;
}


/*
 * funcion para leer el valor de x
 */
int16_t getX()
{
	long c;

	if ((TP_X==-1) || (TP_Y==-1)){
		return -1;
	}
	if (orient == _default_orientation)
	{
		//c = long(long(TP_X - touch_x_left) * (disp_x_size)) / long(touch_x_right - touch_x_left);
		c = ((TP_X - touch_x_left) * (disp_x_sizeT)) / (touch_x_right - touch_x_left);
		if (c<0){
			c = 0;
		}
		if (c>disp_x_sizeT){
			c = disp_x_sizeT;
		}
	}
	else
	{
		if (_default_orientation == PORTRAIT){
			c = ((TP_X - touch_y_top) * (-disp_y_sizeT)) / (touch_y_bottom - touch_y_top) + (disp_y_sizeT);
		}
			else
			{
			c = ((TP_X - touch_y_top) * (disp_y_sizeT)) / (touch_y_bottom - touch_y_top);
			}
			if (c<0){
			c = 0;
			}
		if (c>disp_y_sizeT){
			c = disp_y_sizeT;
		}
	}
	return c;
}

/*
 * Funcion para leer el valor de y del touch
 */
int16_t getY()
{
	int c;

	if ((TP_X==-1) || (TP_Y==-1)){
		return -1;
	}
	if (orient == _default_orientation)
	{
		c = ((TP_Y - touch_y_top) * (disp_y_sizeT)) / (touch_y_bottom - touch_y_top);
		if (c<0){
			c = 0;
		}
		if (c>disp_y_sizeT){
			c = disp_y_sizeT;
		}
	}
	else
	{
		if (_default_orientation == PORTRAIT){
			c = ((TP_Y - touch_x_left) * (disp_x_sizeT)) / (touch_x_right - touch_x_left);
		}
		else{
			c = ((TP_Y - touch_x_left) * (-disp_x_sizeT)) / (touch_x_right - touch_x_left) + (disp_x_sizeT);
		}
		if (c<0){
			c = 0;
		}
		if (c>disp_x_sizeT){
			c = disp_x_sizeT;
		}
	}
	return c;
}

/*
 * Funcion de calibracion del touch
 */
void setPrecision(uint8_t precision)
{
	switch (precision)
	{
		case PREC_LOW:
			prec=1;		// DO NOT CHANGE!
			break;
		case PREC_MEDIUM:
			prec=12;	// Iterations + 2
			break;
		case PREC_HI:
			prec=27;	// Iterations + 2
			break;
		case PREC_EXTREME:
			prec=102;	// Iterations + 2
			break;
		default:
			prec=12;	// Iterations + 2
			break;
	}
}

/*
 * Funcion para la lectura de calibracion
 */
void calibrateRead()
{
	unsigned long tx=0;
	unsigned long ty=0;

	//cbi(P_CS, B_CS);
	HAL_GPIO_WritePin(T_CS.puerto, T_CS.pin, OFF);

	touch_WriteData(0x90);
	//pulse_high(P_CLK, B_CLK);
	HAL_GPIO_WritePin(T_CLK.puerto, T_CLK.pin, ON);
	HAL_GPIO_WritePin(T_CLK.puerto, T_CLK.pin, OFF);
	tx=touch_ReadData();

	touch_WriteData(0xD0);
	//pulse_high(P_CLK, B_CLK);
	HAL_GPIO_WritePin(T_CLK.puerto, T_CLK.pin, ON);
	HAL_GPIO_WritePin(T_CLK.puerto, T_CLK.pin, OFF);
	ty=touch_ReadData();

	//sbi(P_CS, B_CS);
	HAL_GPIO_WritePin(T_CS.puerto, T_CS.pin, ON);

	TP_X=ty;
	TP_Y=tx;
}

/*
 * funcion write data
 */
void touch_WriteData(uint8_t data)
{
	uint8_t temp;

	temp=data;
	//cbi(P_CLK, B_CLK);
	HAL_GPIO_WritePin(T_CLK.puerto, T_CLK.pin, OFF);

	for(uint8_t count=0; count<8; count++)
	{
		if(temp & 0x80)
			//digitalWrite(T_DIN, HIGH);
			HAL_GPIO_WritePin(T_DIN.puerto, T_DIN.pin, ON);
		else
			//digitalWrite(T_DIN, LOW);
			HAL_GPIO_WritePin(T_DIN.puerto, T_DIN.pin, OFF);
		temp = temp << 1;
		//digitalWrite(T_CLK, LOW);
		HAL_GPIO_WritePin(T_CLK.puerto, T_CLK.pin, OFF);
		//digitalWrite(T_CLK, HIGH);
		HAL_GPIO_WritePin(T_CLK.puerto, T_CLK.pin, ON);
	}
}

/*
 * funcion read data
 */
uint32_t touch_ReadData()
{
	uint32_t data = 0;

	for(uint8_t count=0; count<12; count++)
	{
		data <<= 1;
		//digitalWrite(T_CLK, HIGH);
		HAL_GPIO_WritePin(T_CLK.puerto, T_CLK.pin, ON);
		//digitalWrite(T_CLK, LOW);
		HAL_GPIO_WritePin(T_CLK.puerto, T_CLK.pin, OFF);
		if (HAL_GPIO_ReadPin(T_DOUT.puerto, T_DOUT.pin))
			data++;
	}
	return(data);
}


#endif // TOUCHLCDCONFIGURACION_H_
