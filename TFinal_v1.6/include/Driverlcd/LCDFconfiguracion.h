/*
 * LCDFconfiguracion.h
 *
 * Created: 27/02/2021 8:20:08
 *  Author: Pablo
 */

#ifndef LCDFCONFIGURACION_H_
#define LCDFCONFIGURACION_H_
//para este modelo tenemos
//db0-C5 db1-C4 db2-C3 db3-C2 db4-C1 db5-D10 db6-A7 db7-D9 db8-B26 db9-A14 db10-A15 db11-D0 db12-D1 db13-D2 db14-D3 db15-D6
//rs-c6 wr-c7 cs-c8 rst-c9
//con esta funcion se obtiene la resolucion en x, y y la forma de transferencia.
void Conflcd(int model, int RS, int WR, int CS, int REST) {
	int dsx[] = { 239, 239, 239, 239, 239, 239, 175, 175, 239, 127,     // 00-09
			127, 239, 271, 479, 239, 239, 239, 239, 239, 239,           // 10-19
			479, 319, 239, 175, 0, 239, 239, 319, 319, 799,            // 20-29
			127 };                                  // 30-
	int dsy[] = { 319, 399, 319, 319, 319, 319, 219, 219, 399, 159,     // 00-09
			127, 319, 479, 799, 319, 319, 319, 319, 319, 319,           // 10-19
			799, 479, 319, 219, 0, 319, 319, 479, 479, 479,            // 20-29
			159 };                                  // 30-
	int dtm[] = { 16, 16, 16, 8, 8, 16, 8, SERIAL_4PIN, 16, SERIAL_5PIN, // 00-09
			SERIAL_5PIN, 16, 16, 16, 8, 16, LATCHED_16, 16, 8, 8,       // 10-19
			16, 16, 16, 8, 0, SERIAL_5PIN, SERIAL_4PIN, 16, 16, 16,     // 20-29
			SERIAL_5PIN };                              // 30-

	disp_x_size = dsx[model];
	disp_y_size = dsy[model];
	display_transfer_mode = dtm[model];       //para arm es 16
	display_model = model;

	if (display_transfer_mode != 1) {
		_set_direction_registers (display_transfer_mode); //habilita los pines del micro

	}

/*

			HAL_GPIO_WritePin(D0.puerto, D0.pin, ON);

			HAL_GPIO_WritePin(D1.puerto, D1.pin, ON);

			HAL_GPIO_WritePin(D2.puerto, D2.pin, ON);

			HAL_GPIO_WritePin(D3.puerto, D3.pin, ON);

			HAL_GPIO_WritePin(D4.puerto, D4.pin, ON);

			HAL_GPIO_WritePin(D5.puerto, D5.pin, ON);

			HAL_GPIO_WritePin(D6.puerto, D6.pin, ON);

			HAL_GPIO_WritePin(D7.puerto, D7.pin, ON);

			HAL_GPIO_WritePin(D8.puerto, D8.pin, ON);

			HAL_GPIO_WritePin(D9.puerto, D9.pin, ON);

			HAL_GPIO_WritePin(D10.puerto, D10.pin, ON);

			HAL_GPIO_WritePin(D11.puerto, D11.pin, ON);

			HAL_GPIO_WritePin(D12.puerto, D12.pin, ON);

			HAL_GPIO_WritePin(D13.puerto, D13.pin, ON);

			HAL_GPIO_WritePin(D14.puerto, D14.pin, ON);

			HAL_GPIO_WritePin(D15.puerto, D15.pin, ON);



		HAL_GPIO_WritePin(D0.puerto, D0.pin, OFF);

		HAL_GPIO_WritePin(D1.puerto, D1.pin, OFF);

		HAL_GPIO_WritePin(D2.puerto, D2.pin, OFF);

		HAL_GPIO_WritePin(D3.puerto, D3.pin, OFF);

		HAL_GPIO_WritePin(D4.puerto, D4.pin, OFF);

		HAL_GPIO_WritePin(D5.puerto, D5.pin, OFF);

		HAL_GPIO_WritePin(D6.puerto, D6.pin, OFF);

		HAL_GPIO_WritePin(D7.puerto, D7.pin, OFF);

		HAL_GPIO_WritePin(D8.puerto, D8.pin, OFF);

		HAL_GPIO_WritePin(D9.puerto, D9.pin, OFF);

		HAL_GPIO_WritePin(D10.puerto, D10.pin, OFF);

		HAL_GPIO_WritePin(D11.puerto, D11.pin, OFF);

		HAL_GPIO_WritePin(D12.puerto, D12.pin, OFF);

		HAL_GPIO_WritePin(D13.puerto, D13.pin, OFF);

		HAL_GPIO_WritePin(D14.puerto, D14.pin, OFF);

		HAL_GPIO_WritePin(D15.puerto, D15.pin, OFF);
		*/
}

void _set_direction_registers(uint8_t mode) {  //no lo uso es para el micro arm cortex m3
	if (mode == 16) {
		/*
		 REG_PIOA_WPMR=(REG_PIOA_WPMR & 0b11111111111111111111111111111110) | 0b00000000000000000000000000000001; //habilito la escritura de los pio
		 REG_PIOB_WPMR=(REG_PIOB_WPMR & 0b11111111111111111111111111111110) | 0b00000000000000000000000000000001; //habilito la escritura de los pio
		 REG_PIOC_WPMR=(REG_PIOC_WPMR & 0b11111111111111111111111111111110) | 0b00000000000000000000000000000001; //habilito la escritura de los pio
		 REG_PIOD_WPMR=(REG_PIOD_WPMR & 0b11111111111111111111111111111110) | 0b00000000000000000000000000000001; //habilito la escritura de los pio
		 REG_PIOA_OER=(REG_PIOA_OER & 0b11111111111111110011111101111111) | 0b00000000000000001100000010000000; //PA7, PA14,PA15 enable
		 REG_PIOB_OER=(REG_PIOB_OER & 0b11111011111111111111111111111111) | 0b00000100000000000000000000000000; //PB26 enable
		 REG_PIOC_OER=(REG_PIOC_OER & 0b11111111111111111111111111000001) | 0b00000000000000000000000000111110; //PC1 - PC5 enable
		 REG_PIOD_OER=(REG_PIOD_OER & 0b11111111111111111111100110110000) | 0b00000000000000000000011001001111; //PD0-3,PD6,PD9-10 enable

		 REG_PIOC_OER=(REG_PIOC_OER & 0b11111111111111111111110000111111) | 0b00000000000000000000001111000000; //PC6 - PC9 enable
		 */
	}
}

void LCD_Writ_Bus(char VH, char VL, uint8_t mode) {

	HAL_GPIO_WritePin(D6.puerto, D6.pin, OFF);
	//gpioWrite(D9, OFF);
	HAL_GPIO_WritePin(D9.puerto, D9.pin, OFF);
	//gpioWrite(D10, OFF);
	HAL_GPIO_WritePin(D10.puerto, D10.pin, OFF);
	//REG_PIOB_CODR=0x4000000;
	//gpioWrite(D8, OFF);
	HAL_GPIO_WritePin(D8.puerto, D8.pin, OFF);
	//REG_PIOC_CODR=0x0000003E;
	//gpioWrite(D0, OFF);
	HAL_GPIO_WritePin(D0.puerto, D0.pin, OFF);
	//gpioWrite(D1, OFF);
	HAL_GPIO_WritePin(D1.puerto, D1.pin, OFF);
	//gpioWrite(D2, OFF);
	HAL_GPIO_WritePin(D2.puerto, D2.pin, OFF);
	//gpioWrite(D3, OFF);
	HAL_GPIO_WritePin(D3.puerto, D3.pin, OFF);
	//gpioWrite(D4, OFF);
	HAL_GPIO_WritePin(D4.puerto, D4.pin, OFF);
	//REG_PIOD_CODR=0x0000064F;
	//gpioWrite(D5, OFF);
	HAL_GPIO_WritePin(D5.puerto, D5.pin, OFF);
	//gpioWrite(D7, OFF);
	HAL_GPIO_WritePin(D7.puerto, D7.pin, OFF);
	//gpioWrite(D11, OFF);
	HAL_GPIO_WritePin(D11.puerto, D11.pin, OFF);
	//gpioWrite(D12, OFF);
	HAL_GPIO_WritePin(D12.puerto, D12.pin, OFF);
	//gpioWrite(D13, OFF);
	HAL_GPIO_WritePin(D13.puerto, D13.pin, OFF);
	//gpioWrite(D14, OFF);
	HAL_GPIO_WritePin(D14.puerto, D14.pin, OFF);
	//gpioWrite(D15, OFF);
	HAL_GPIO_WritePin(D15.puerto, D15.pin, OFF);

	//REG_PIOA_SODR=((VH & 0x06)<<13) | ((VL & 0x40)<<1);   //pone en 1 los bits seleccionados por puerto
	if ((VL & 0x040)) {
		//gpioWrite(D6, ON);
		HAL_GPIO_WritePin(D6.puerto, D6.pin, ON);
	}
	if ((VH & 0x02)) {
		//gpioWrite(D9, ON);
		HAL_GPIO_WritePin(D9.puerto, D9.pin, ON);
	}
	if ((VH & 0x04)) {
		//gpioWrite(D10, ON);
		HAL_GPIO_WritePin(D10.puerto, D10.pin, ON);
	}
	//(VH & 0x01) ? REG_PIOB_SODR = 0x4000000 : REG_PIOB_CODR = 0x4000000;
	if ((VH & 0x01)) {
		//gpioWrite(D8, ON);
		HAL_GPIO_WritePin(D8.puerto, D8.pin, ON);
	}

	//REG_PIOC_SODR=((VL & 0x01)<<5) | ((VL & 0x02)<<3) | ((VL & 0x04)<<1) | ((VL & 0x08)>>1) | ((VL & 0x10)>>3);
	if ((VL & 0x01)) {
		//gpioWrite(D0, ON);
		HAL_GPIO_WritePin(D0.puerto, D0.pin, ON);
	}
	if ((VL & 0x02)) {
		//gpioWrite(D1, ON);
		HAL_GPIO_WritePin(D1.puerto, D1.pin, ON);
	}
	if ((VL & 0x04)) {
		//gpioWrite(D2, ON);
		HAL_GPIO_WritePin(D2.puerto, D2.pin, ON);
	}
	if ((VL & 0x08)) {
		//gpioWrite(D3, ON);
		HAL_GPIO_WritePin(D3.puerto, D3.pin, ON);
	}
	if ((VL & 0x010)) {
		//gpioWrite(D4, ON);
		HAL_GPIO_WritePin(D4.puerto, D4.pin, ON);
	}
	//REG_PIOD_SODR=((VH & 0x78)>>3) | ((VH & 0x80)>>1) | ((VL & 0x20)<<5) | ((VL & 0x80)<<2);
	if ((VL & 0x020)) {
		//gpioWrite(D5, ON);
		HAL_GPIO_WritePin(D5.puerto, D5.pin, ON);
	}
	if ((VL & 0x080)) {
		//gpioWrite(D7, ON);
		HAL_GPIO_WritePin(D7.puerto, D7.pin, ON);
	}
	if ((VH & 0x08)) {
		//gpioWrite(D11, ON);
		HAL_GPIO_WritePin(D11.puerto, D11.pin, ON);
	}
	if ((VH & 0x010)) {
		//gpioWrite(D12, ON);
		HAL_GPIO_WritePin(D12.puerto, D12.pin, ON);
	}
	if ((VH & 0x020)) {
		//gpioWrite(D13, ON);
		HAL_GPIO_WritePin(D13.puerto, D13.pin, ON);
	}
	if ((VH & 0x04)) {
		//gpioWrite(D14, ON);
		HAL_GPIO_WritePin(D14.puerto, D14.pin, ON);
	}
	if ((VH & 0x08)) {
		//gpioWrite(D15, ON);
		HAL_GPIO_WritePin(D15.puerto, D15.pin, ON);
	}
	//pulse_low(P_WR, B_WR); hace un pulso en bajo de wr
	//REG_PIOC_CODR=(REG_PIOC_CODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
	//gpioWrite(WR, ON);
	HAL_GPIO_WritePin(WR.puerto, WR.pin, ON);
	//HAL_Delay(1);
	//delayMicroseconds(1); //retardo minimo de 12nseg
	//REG_PIOC_SODR=(REG_PIOC_SODR & 0b11111111111111111111111101111111) | 0b00000000000000000000000010000000; //PC7-WR
	//gpioWrite(WR, OFF);
	HAL_GPIO_WritePin(WR.puerto, WR.pin, OFF);
}

void LCD_Write_DATA(char VL) {		//no lo uso es para otro modelo de display de 8bits
	//sbi(P_RS, B_RS); pone en 1 RS
	//gpioWrite(RS, ON);
	HAL_GPIO_WritePin(RS.puerto, RS.pin, ON);
	//HAL_Delay(1);
	//REG_PIOC_SODR=(REG_PIOC_SODR & 0b11111111111111111111111110111111) | 0b00000000000000000000000001000000; //PC6-RS
	LCD_Writ_Bus(0x00, VL, display_transfer_mode);
}

void LCD_Write_COM(char VL) {
	//cbi(P_RS, B_RS); para poner a cero el pin RS
	//gpioWrite(RS, OFF);
	HAL_GPIO_WritePin(RS.puerto, RS.pin, OFF);
	//HAL_Delay(1);
	//REG_PIOC_CODR=(REG_PIOC_CODR & 0b11111111111111111111111110111111) | 0b00000000000000000000000001000000; //PC6-RS
	LCD_Writ_Bus(0x00, VL, display_transfer_mode);
}

void LCD_Write_DATAb(char VH, char VL) {
	//sbi(P_RS, B_RS);
	//gpioWrite(RS, ON);
	HAL_GPIO_WritePin(RS.puerto, RS.pin, ON);
	//HAL_Delay(1);
	//REG_PIOC_SODR=(REG_PIOC_SODR & 0b11111111111111111111111110111111) | 0b00000000000000000000000001000000; //PC6-RS
	LCD_Writ_Bus(VH, VL, display_transfer_mode);
}

#endif /* LCDFCONFIGURACION_H_ */
