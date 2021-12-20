/*
 * Funciones para el funcinamiento del osciloscopio
 */
#ifndef OSC_H_
#define OSC_H_

void senal(void); //funcion para ver la entrada
void displaymenue(void);
void displayejes(void);
void menuentrada(void);
void menusenalTR(void);
void menusenal(void);
void submuestreo(void);


void entrada(){
  displaymenue();
  ban=2;
  menuentrada();
}

//+++++++++++++++++++++funcion para graficar la entrada
void senal(){
int c;
int f;
int amp;
int CC;
int sal;
int volt;
long cont;
long cont1;
int i;
short band;
short sallcd[801];
i=0;
band=0;
c=0;
f=0;
amp=0;
CC=2048;
sal=0;
cont=0;
cont1=0;

  menusenal();
  /*
  REG_DACC_MR = (REG_DACC_MR & 0b11111111111111001111111111111111) | 0b00000000000000000000000000000000; //dac user sel canal 0
  REG_DACC_CHER=0b0000000000000000000000000000001;
  while ((REG_DACC_ISR & 0b00000000000000000000000000000001)== 0); //espera que el registro este disponible para una conversion
  REG_DACC_CDR = (GanVdac);//escribe el DAC con el valor del registro pwm
  */
bana=2;
while(bana==2){
    menusenalTR();

    //************funcion para la adquision de los datos
    i=0;
    N=250;
    //N=250+(2*Nfir);
    HAL_ADC_Start(&hadc1);		//enabled adc
    HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
    timer_start();				//star counter
    while(bandint == 0){
      //GPIOE->ODR ^= GPIO_PIN_0;
    }
    //GPIOE->ODR ^= GPIO_PIN_0;
    bandint=0;


    //********para Calculo del maximo, minimo
    i=0;
        N=250;
        vpmas=2048;
        vpmenos=2048;
        periodo=0;
        bandf=0;
        while (i != (N+1)){  //N+1
          sallcd[i]=((xn[i]*460)/4095); //4095 a la senal x[n] le cambia la escala por el display
          if (xn[i] > vpmas){
        	  vpmas=xn[i];
          }

          if (xn[i] < vpmenos){
			  vpmenos=xn[i];
		  }

          if(i==0){
        	  bandf=1;
          }
          else if (((xn[i-1] < leveltriger) && (xn[i] > leveltriger)) && (bandf == 1) && (i > 1)){
        	  bandf=0;
          }
          else if (bandf==1){
        	  periodo=periodo+1;	//tiene un error ya que no se puede bajar mas de 500ns por muestra. y lo maximo
          }							//que se puede bajar es a 300ns que es tiempo de muestro.

          i=i+1;
        }

   //**********Para calcular la frecuencia
	   //*******Convierte los valores de 12bits en voltaje max 33volt
	   i=0;
	   while (i != N+1){
		xn[i]= ((xn[i]*33)/4095);
		i=i+1;
		}

	   FFT_calculo();	//calcula la FFT
	   Mayor_Xk(2);		//calcula el mayor del los coeficientes de la FFT

	   //********para graficar Vp+, Vp- y F
		vpmas = (vpmas*3.3)/4095;
		vpmenos = (vpmenos*3.3)/4095;
		if(periodo < 22){
			Fsenial = kaa *df;
		}
		else{
			Fsenial = (Fs/(periodo));
		}
		setColor(VGA_YELLOW);
		print("F=", 605,30, 0);
		printNumF(Fsenial,1,620,30,'.',4,' ');
		print("+VP=", 700,30, 0);
		printNumF(vpmas,1,732,30,'.',4,' ');
		print("-Vp=", 700,50, 0);
		printNumF(vpmenos,1,732,50,'.',4,' ');

	//***********Para dibujar la forma de onda
      i=1;
      iT=1;
      Tvisual = ((598/N)+1);
      iT=iT+Tvisual;
      while (iT < 598 ){
    	  menusenalTR();
        displayejes();
        setColorRGB(0, 0, 0);
        if ((iT >= (598-(Tvisual+1))) && (iT <= (598-Tvisual))){
          iTClear=1;
          while((iTClear) <=(Tvisual)){
            drawLine(iTClear, ResV-2, iTClear, 21);
            iTClear=iTClear+1;
          }
        }
        else if (iT <= (598-Tvisual)){
          iTClear=iT;
          while(iTClear <= (iT+Tvisual)){
            drawLine(iTClear, ResV-2, iTClear, 21);
            iTClear=iTClear+1;
          }
        }
        setColorRGB(0, 255, 255);
        drawLine(iT-Tvisual, ((465-sallcd[i-1])), iT, ((465-sallcd[i]))); // es 255 para sumar el desfasaje del rectangulo de arriba
        //setColorRGB(0, 255, 0);
       // drawLine(iT-Tvisual, (400-(Q[i-1]+200)), iT, (400-(Q[i]+200)));
       // setColorRGB(255, 255, 0);
       // drawLine(iT-Tvisual, (400-Xfam[i-1]), iT, (400-Xfam[i]));
        i=i+1;
        iT=iT+Tvisual;
     }
 }
}



//***********funcio para graficar ejes
void displayejes(){
  setColor(VGA_GRAY);
  drawLine(1, (((ResV-18)/2)+desplazamiento), 598, (((ResV-18)/2)+desplazamiento)); //eje x de la pantalla
  drawLine(299, 18, 299,(ResV-2)); //eje y de la pantalla

}

//++++++++++++++++++++menusenal para graficar la pantalla
void menusenal(){
    deleteAllButtons();
    clrScr(); //borra pantalla
    setColorRGB(255,0, 0); //establece el color r,g,b en el rectangulo
    drawfillRoundRect(0, 0, ResH-1, 17); //dibuja un rectangulo
    //myGLCD.setColor(64, 64, 64);  //establece color
    setColorRGB(255, 255, 255); //establece color de fondo
    setBackColorRGB(255, 0, 0); //establece color de fondo
    setFont(BigFont);
    print("Osciloscopio", LEFT,1, 0);//imprime texto en el centro
    setColorRGB(0, 0, 255);
    drawRoundRect(0, 19, ResH-1, ResV-1); //dibuja rectangulo de la pantalla
    drawRectangulo(600, 18, ResH-1, ResV-1); //dibuja rectangulo de menu en pantalla
    drawRectangulo(600, 18, ResH-1,70); //dibuja rectangulo de menu en pantalla para ganancia
    drawRectangulo(600, 18, ResH-1,130 ); //dibuja rectangulo de menu en pantalla para otros
    setFont(SmallFont);
    setColor(VGA_YELLOW);
    setBackColorRGB(0, 0, 0); //establece color de fondo
    print("Gan=", 605,85, 0);//imprime la resolucion espectral por coeficiente de frecuencia
    if(GanVdac<1100){
      //y = 0,0116x + 0,9225
      GanV=(29*GanVdac)/2500;
      GanV=GanV+0.9225;
    }
    else if ((GanVdac>1099) && (GanVdac<1211)){
      //y = 0,1229x - 119,94
      GanV=(1229*GanVdac)/10000;
      GanV=GanV-119.94;
    }
    else if ((GanVdac>1210) && (GanVdac<1301)){
      //y = 0,368x - 416,08
      GanV=(46*GanVdac)/125;
      GanV=GanV-416.0;
    }
    else if(GanVdac>1300){
      //y = 0,8384x - 1016,4
      GanV=(524*GanVdac)/625;
      GanV=GanV+1016.4;
    }
    printNumF(GanV,1,640,85,'.',4,' ');
    print("Dac=", 605,105, 0);//imprime la resolucion espectral por coeficiente de frecuencia
    printNumF(GanVdac,1,640,105,'.',4,' ');
    df= (Fs/N);
    print("df=", 705,85, 0);
    print("Fs=", 705,105, 0);
    printNumF(df,1,730,85,'.',4,' ');
    //printNumF(Fs,1,730,105,'.',4,' ');
    printNumI(Fs,730,105,2,' ');
    print("F=", 605,30, 0);
    printNumF(Fsenial,1,620,30,'.',4,' ');
    print("+VP=", 700,30, 0);
    printNumF(vpmas,1,732,30,'.',4,' ');
    print("-Vp=", 700,50, 0);
    printNumF(vpmenos,1,732,50,'.',4,' ');


    setButtonColors(VGA_GRAY, VGA_RED, VGA_RED, VGA_LIME, VGA_BLUE);
    but1 = addButton(605, 140, 90, 60, "GanV+",0);
    but2 = addButton(605, 205, 90, 60, "GanV-",0);
    but3 = addButton(705, 140, 90, 60, "F+",0);
    but4 = addButton(705, 205, 90, 60, "F-",0);
    but5 = addButton(605, 270, 90, 60, "Trig. OFF",0);
    //but7 = addButton(605, 335, 90, 60, "Desf-",0);
    but6 = addButton(605, 390, 190, 80, "Salir",0);
    drawButtons();
    _color_text=VGA_RED;
    relabelButton(but5, "Trig. OFF", true);

    setColorRGB(0, 255, 255);
    setBackColorRGB(0, 0, 0);
}

//++++++++++++++++++++menusenal en tiempo real
void menusenalTR(){
  if (dataAvailable() == true)  //para preguntar si se presiono un boton
     {
	  HAL_Delay(200);
      pressed_button = checkButtons();
      setColor(VGA_YELLOW);
      setBackColorRGB(0, 0, 0); //establece color de fondo

      if (pressed_button==but1){
        //delay(100);
        GanVdac=GanVdac+10;
        if(GanVdac<1100){
          //y = 0,0116x + 0,9225
          GanV=(29*GanVdac)/2500;
          GanV=GanV+0.9225;
        }
        else if ((GanVdac>1099) && (GanVdac<1211)){
          //y = 0,1229x - 119,94
          GanV=(1229*GanVdac)/10000;
          GanV=GanV-119.94;
        }
        else if ((GanVdac>1210) && (GanVdac<1301)){
          //y = 0,368x - 416,08
          GanV=(46*GanVdac)/125;
          GanV=GanV-416.0;
        }
        else if(GanVdac>1300){
          //y = 0,8384x - 1016,4
          GanV=(524*GanVdac)/625;
          GanV=GanV+1016.4;
        }
        printNumF(GanV,1,640,85,'.',4,' ');
        printNumF(GanVdac,1,640,105,'.',4,' ');
        /*
        REG_DACC_MR = (REG_DACC_MR & 0b11111111111111001111111111111111) | 0b00000000000000000000000000000000; //dac user sel canal 0
        REG_DACC_CHER=0b0000000000000000000000000000001;
        while ((REG_DACC_ISR & 0b00000000000000000000000000000001)== 0); //espera que el registro este disponible para una conversion
        REG_DACC_CDR = (GanVdac);//escribe el DAC con el valor del registro pwm
        */
        }
      else if (pressed_button==but2){
        //delay(100);
        GanVdac=GanVdac-10;
        if(GanVdac<1100){
          //y = 0,0116x + 0,9225
          GanV=(29*GanVdac)/2500;
          GanV=GanV+0.9225;
        }
        else if ((GanVdac>1099) && (GanVdac<1211)){
          //y = 0,1229x - 119,94
          GanV=(1229*GanVdac)/10000;
          GanV=GanV-119.94;
        }
        else if ((GanVdac>1210) && (GanVdac<1301)){
          //y = 0,368x - 416,08
          GanV=(46*GanVdac)/125;
          GanV=GanV-416.0;
        }
        else if(GanVdac>1300){
          //y = 0,8384x - 1016,4
          GanV=(524*GanVdac)/625;
          GanV=GanV+1016.4;
        }
        printNumF(GanV,1,640,85,'.',4,' ');
        printNumF(GanVdac,1,640,105,'.',4,' ');
        /*
        REG_DACC_MR = (REG_DACC_MR & 0b11111111111111001111111111111111) | 0b00000000000000000000000000000000; //dac user sel canal 0
        REG_DACC_CHER=0b0000000000000000000000000000001;
        while ((REG_DACC_ISR & 0b00000000000000000000000000000001)== 0); //espera que el registro este disponible para una conversion
        REG_DACC_CDR = (GanVdac);//escribe el DAC con el valor del registro pwm
        */
        }
       else if (pressed_button==but3){
    	  contFs=contFs-5;
		  if(contFs <= 2){
			  contFs=2;
			  Fs=2000000/(contFs);
		  }
		  else{
			  Fs=2000000/(contFs-1);
		  }

		  df= (Fs/N);
          printNumF(df,1,730,85,'.',4,' ');
          //printNumF(Fs,1,730,105,'.',4,' ');
          printNumI(Fs,730,105,2,' ');
        }
       else if (pressed_button==but4){
    	  contFs=contFs+5;
		  if (contFs>20000){
			  contFs=20000;
		  }
		  Fs=2000000/(contFs-1);
		  df= (Fs/N);
          printNumF(df,1,730,85,'.',4,' ');
          //printNumF(Fs,1,730,105,'.',4,' ');
          printNumI(Fs,730,105,2,' ');
        }
        else if (pressed_button==but5){
        	if(trigger==0){
        		trigger=1;
        		_color_text=VGA_YELLOW;
        		relabelButton(but5, "Trig. ON", true);
        	}
        	else{
        		trigger=0;
        		_color_text=VGA_RED;
        		relabelButton(but5, "Trig. OFF", true);
        	}

        }
        //else if (pressed_button==but6){

        //}
       else if (pressed_button==but6){
        bana=1;
        HAL_Delay(100);
        /*
        REG_DACC_MR = (REG_DACC_MR & 0b11111111111111001111111111111111) | 0b0000000000000000000000000000000;//dac user sel en canal 0
        REG_DACC_CHER=0b0000000000000000000000000000001;
        while ((REG_DACC_ISR & 0b00000000000000000000000000000001)== 0); //espera que el registro este disponible para una conversion
        REG_DACC_CDR = (000);//escribe el DAC con el valor del registro pwm
       	*/
       }
    }
}

//++++++++++++++++++menuentrada
void menuentrada(){
 while(ban==2)
  {
      //REG_DACC_CHDR=0x00000010;
      //REG_DACC_CHER=0x00000001;
      /*
	  REG_DACC_MR = (REG_DACC_MR & 0b11111111111111001111111111111111) | 0b0000000000000000000000000000000;//dac user sel en canal 0
      while ((REG_DACC_ISR & 0b00000000000000000000000000000001)== 0); //espera que el registro este disponible para una conversion
      REG_DACC_CDR = (000);//escribe el DAC con el valor del registro pwm
	  */

    if (dataAvailable() == true)
    {
    	HAL_Delay(200);
      pressed_button = checkButtons();

      if (pressed_button==but2){
       // myGLCD.print("Button 2", 220, 320);
        clrScr(); //borra pantalla
        HAL_Delay(100);
        senal();
        clrScr(); //borra pantalla
        displaymenue();
        //ban=1;
    }
      else if (pressed_button==but3){
        //myGLCD.print("Button 3", 220, 320);
        deleteAllButtons();
        clrScr(); //borra pantalla
        ban=1;

    }
       else if (pressed_button==-1){
       // myGLCD.print("None    ", 220, 320);
       // ban=1;
       }
    }
  }
}

//+++++++++++++++++++++++funcion para refrescar la pantalla
void displaymenue(){
 deleteAllButtons();
 clrScr(); //borra pantalla
 setColorRGB(255,0, 0); //establece el color r,g,b en el rectangulo
 drawfillRoundRect(0, 0, ResH-1, 15); //dibuja un rectangulo
 //myGLCD.setColor(64, 64, 64);  //establece color 1
 setColorRGB(255, 255, 255); //establece color de fondo
 setBackColorRGB(255, 0, 0); //establece color de fondo
 setFont(BigFont);
 print("ENTRADA", CENTER,1, 0);//imprime texto en el centro
 setColorRGB(0, 0, 255);
 drawRectangulo(0, 15, ResH-1, ResV-1); //dibuja rectangulo de la pantalla

  setButtonColors(VGA_YELLOW, VGA_RED, VGA_RED, VGA_LIME, VGA_BLUE);
  but1 = addButton( 4,  25, 200,  60, "Osc.",0);
  but2 = addButton( 210,  25, 200,  60, "ENTRADA",0);
  but3 = addButton( 210,  100, 200,  60, "VOLVER",0);
  //but3 = myButtons.addButton( 4, 99, 250,  30, "Modulacion PM");
  //but4 = myButtons.addButton( 4, 136, 250,  30, "VOLVER");
  drawButtons();
}


#endif /* OSC_H_ */
