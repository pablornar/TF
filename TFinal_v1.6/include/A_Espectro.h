/*
 * Funciones para el funcinamiento de la FFT
 */
#ifndef FFT_H_
#define FFT_H_

void dBmfun(int);
void displaymenuf(void);
void displaymenufft(void);
void calFFT(void); //funcio para calcular la FFT
void ParaFFT(void);
void Muestras(void);
void Frecuencia(void);
void Persistencia(void);
void Promedio(void);
void displaymenuMuestras();
void displaymenuFrecuencia();
void displaymenuPersistencia();
void displaymenuPromedio();



void FFT(){
	displaymenuf();
  ban=2;
  while(ban==2)
  {
	  	  /*
          REG_DACC_MR = (REG_DACC_MR & 0b11111111111111001111111111111111) | 0b00000000000000000000000000000000; //dac user sel canal 0
          REG_DACC_CHER=0b0000000000000000000000000000001;
          while ((REG_DACC_ISR & 0b00000000000000000000000000000001)== 0); //espera que el registro este disponible para una conversion
          REG_DACC_CDR = (0);//escribe el DAC con el valor del registro pwm
		*/

    if (dataAvailable() == true)
    {
      HAL_Delay(200);
      pressed_button = checkButtons();

      if (pressed_button==but2){
        clrScr(); //borra pantalla
        calFFT();
        clrScr(); //borra pantalla
        displaymenuf();
    }
      else if (pressed_button==but3){
        clrScr(); //borra pantalla
        ParaFFT();
        clrScr(); //borra pantalla
        displaymenuf();
    }
    else if (pressed_button==but4){
        deleteAllButtons();
        clrScr(); //borra pantalla
        ban=1;
    }
       else if (pressed_button==-1){
        //print("None    ", 110, 220);
       }
    }
  }
}

//++++++++++++++++++++++Funcion para colocar valores en los parametros
void ParaFFT(){
  displaymenufft();
  bana=2;
  while(bana==2){
    if (dataAvailable() == true){
    	HAL_Delay(200);
    	pressed_button = checkButtons();
      if (pressed_button==but3){
        //print("Button 3", 110, 220);
        clrScr(); //borra pantalla
        Muestras();
        clrScr(); //borra pantalla
        displaymenufft();
        //bana=1;
    }
      else if (pressed_button==but4){
        //print("Button 4", 110, 220);
        clrScr(); //borra pantalla
        Frecuencia();
        clrScr(); //borra pantalla
        displaymenufft();
        //bana=1;
    }
     else if (pressed_button==but5){
        //print("Button 5", 110, 220);
        clrScr(); //borra pantalla
        Persistencia();
        clrScr(); //borra pantalla
        displaymenufft();
        //bana=1;
    }
     else if (pressed_button==but6){
        //print("Button 6", 110, 220);
        clrScr(); //borra pantalla
        Promedio();
        clrScr(); //borra pantalla
        displaymenufft();
        //bana=1;
    }
    else if (pressed_button==but7){
        //print("Button 7", 110, 220);
        deleteAllButtons();
        clrScr(); //borra pantalla
        bana=1;
    }
       else if (pressed_button==-1){
        //print("None    ", 110, 220);
       }
    }
  }
}

//+++++++Funcion para ingresar la cantidad de muestras
void Muestras(){
  displaymenuMuestras();
  banaM=2;
  while(banaM==2)
  {
    if (dataAvailable() == true)
    {
    	HAL_Delay(200);
    	pressed_button = checkButtons();

      if (pressed_button==but1){
        //print("Button 1", 110, 220);
        clrScr(); //borra pantalla
        N=32;
        clrScr(); //borra pantalla
        banaM=1;
    }
      else if (pressed_button==but2){
        //print("Button 2", 110, 220);
        clrScr(); //borra pantalla
        N=64;
        clrScr(); //borra pantalla
        banaM=1;
    }
    else if (pressed_button==but3){
        //print("Button 3", 110, 220);
        clrScr(); //borra pantalla
         N=128;
        clrScr(); //borra pantalla
        banaM=1;
    }
    else if (pressed_button==but4){
        //print("Button 4", 110, 220);
        clrScr(); //borra pantalla
         N=256;
        clrScr(); //borra pantalla
        banaM=1;
    }
    else if (pressed_button==but5){
        //print("Button 5", 110, 220);
        clrScr(); //borra pantalla
         N=512;
        clrScr(); //borra pantalla
        banaM=1;
    }
    else if (pressed_button==but6){
        //print("Button 6", 110, 220);
        //myButtons.deleteAllButtons();
        clrScr(); //borra pantalla
        banaM=1;
    }

    else if (pressed_button==-1){
      print("None    ", 110, 220,0);
     }
   }
  }
}

//++++++++++++++++funcion para ingresar el rango de frecuencia para calcular la fft
void Frecuencia(){
   displaymenuFrecuencia();
  banaM=2;
  while(banaM==2)
  {
    if (dataAvailable() == true)
    {
    	HAL_Delay(200);
      pressed_button = checkButtons();

      if (pressed_button==but1){
        //print("Button 1", 110, 220);
        clrScr(); //borra pantalla
        Fs=100;
        clrScr(); //borra pantalla
        banaM=1;
    }
      else if (pressed_button==but2){
        //print("Button 2", 110, 220);
        clrScr(); //borra pantalla
        Fs=1000;
        clrScr(); //borra pantalla
        banaM=1;
    }
    else if (pressed_button==but3){
        //print("Button 3", 110, 220);
        clrScr(); //borra pantalla
         Fs=10000;
        clrScr(); //borra pantalla
        banaM=1;
    }
    else if (pressed_button==but4){
        //print("Button 4", 110, 220);
        clrScr(); //borra pantalla
         Fs=100000;
        clrScr(); //borra pantalla
        banaM=1;
    }
    else if (pressed_button==but5){
        //print("Button 5", 110, 220);
        clrScr(); //borra pantalla
        Fs=1000000;
        clrScr(); //borra pantalla
        banaM=1;
    }
    else if (pressed_button==but6){
        //print("Button 6", 110, 220);
        //myButtons.deleteAllButtons();
        clrScr(); //borra pantalla
        banaM=1;
    }
       else if (pressed_button==-1){
        //print("None    ", 110, 220);
       }
    }
  }
}

//+++++++++++++++++funcion para ingresar los datos de persistencia
void Persistencia(){
   displaymenuPersistencia();
  banaM=2;
  while(banaM==2)
  {
    if (dataAvailable() == true)
    {
    	HAL_Delay(200);
      pressed_button = checkButtons();

      if (pressed_button==but1){
        //print("Button 1", 110, 220);
        clrScr(); //borra pantalla
        Tpers=1;
        clrScr(); //borra pantalla
        banaM=1;
    }
      else if (pressed_button==but2){
        //print("Button 2", 110, 220);
        clrScr(); //borra pantalla
        Tpers=100;
        clrScr(); //borra pantalla
        banaM=1;
    }
    else if (pressed_button==but3){
        //print("Button 3", 110, 220);
        clrScr(); //borra pantalla
         Tpers=250;
        clrScr(); //borra pantalla
        banaM=1;
    }
    else if (pressed_button==but4){
        //print("Button 4", 110, 220);
        clrScr(); //borra pantalla
         Tpers=500;
        clrScr(); //borra pantalla
        banaM=1;
    }
    else if (pressed_button==but5){
        //print("Button 5", 110, 220);
        clrScr(); //borra pantalla
         Tpers=1000;
        clrScr(); //borra pantalla
        banaM=1;
    }
    else if (pressed_button==but6){
        //print("Button 6", 110, 220);
        //myButtons.deleteAllButtons();
        clrScr(); //borra pantalla
        banaM=1;
    }
       else if (pressed_button==-1){
        print("None    ", 110, 220,0);
       }
    }
  }
}

//++++++++++++++++funcion para ingresar el valor promedio
void Promedio(){
   displaymenuPromedio();
  banaM=2;
  while(banaM==2)
  {
    if (dataAvailable() == true)
    {
    	HAL_Delay(200);
      pressed_button = checkButtons();

      if (pressed_button==but1){
        //print("Button 1", 110, 220);
        clrScr(); //borra pantalla
        Tprom=10;
        clrScr(); //borra pantalla
        banaM=1;
    }
      else if (pressed_button==but2){
        //print("Button 2", 110, 220);
        clrScr(); //borra pantalla
        Tprom=200;
        clrScr(); //borra pantalla
        banaM=1;
    }
    else if (pressed_button==but3){
        //print("Button 3", 110, 220);
        clrScr(); //borra pantalla
         Tprom=500;
        clrScr(); //borra pantalla
        banaM=1;
    }
    else if (pressed_button==but4){
        //print("Button 4", 110, 220);
        clrScr(); //borra pantalla
         Tprom=1000;
        clrScr(); //borra pantalla
        banaM=1;
    }
    else if (pressed_button==but5){
        //print("Button 5", 110, 220);
        clrScr(); //borra pantalla
         Tprom=2000;
        clrScr(); //borra pantalla
        banaM=1;
    }
    else if (pressed_button==but6){
        //print("Button 6", 110, 220);
        //myButtons.deleteAllButtons();
        clrScr(); //borra pantalla
        banaM=1;
    }
       else if (pressed_button==-1){
        //print("None    ", 110, 220);
       }
    }
  }
}

//++++++++++++++++++++Funcion para calcular los coeficientes K de la transformada de fourier
void calFFT(){
	bana=2;
//El retardo total entre conversion, calculo y dac es de 12,5useg, con lo cual el calculo es de 9,5useg aproximadamente
//y de 11,2useg en total con lo cual tengo un retardo de calculo de 9,3useg. para N=8, Nout=3 y Nsal=1
    deleteAllButtons();
    //myButtons.setButtonColors(VGA_YELLOW, VGA_RED, VGA_RED, VGA_GRAY, VGA_BLUE);
    clrScr(); //borra pantalla
    setColorRGB(255,0, 0); //establece el color r,g,b en el rectangulo
    drawfillRoundRect(0, 0, ResH-1, 15); //dibuja un rectangulo
    //setColorRGB(64, 64, 64);  //establece color
    setColorRGB(255, 255, 255); //establece color de fondo
    setBackColorRGB(255, 0, 0); //establece color de fondo
    print("RESPUESTA EN FRECUENCIA", CENTER,1, 0);//imprime texto en el centro
    setColorRGB(50,50,90);	//establece el color r,g,b en el rectangulo
    drawfillRoundRect(2, 17, 404, ResV-3); //dibuja un rectangulo
    setColorRGB(0, 0, 255);
    drawRoundRect(0, 15, ResH-1, ResV-1); //dibuja rectangulo de la pantalla
    drawRoundRect(1, 16, ResH-2, ResV-2); //dibuja rectangulo de la pantalla
    drawRoundRect(405, 15, ResH-1, ResV-1); //dibuja rectangulo de menu en pantalla
    drawRoundRect(405, 15, ResH-1,70); //dibuja rectangulo de menu en pantalla para f
    drawRoundRect(405, 70, ResH-1,130 ); //dibuja rectangulo de menu en pantalla para dbm

    setColor(VGA_YELLOW);
    setBackColorRGB(0, 0, 0); //establece color de fondo
    print("0 < F <", 426,30, 0);//imprime texto en el centro
    printNumI(Fs,486,30,7,' ');
    print("Df=", 580,30, 0);//imprime la resolucion espectral por coeficiente de frecuencia
    printNumF((Fs/N),1,604,30,'.',4,' ');
    print("Fs=", 700,30, 0);//imprime la resolucion espectral por coeficiente de frecuencia
    //printNumF(Fs,0,725,30,'.',4,' ');
    printNumI(Fs,725,30,7,' ');
    print("Gan=", 700,85, 0);//imprime la resolucion espectral por coeficiente de frecuencia
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
    printNumF(GanV,1,735,85,'.',4,' ');
    print("Dac=", 700,105, 0);//imprime la resolucion espectral por coeficiente de frecuencia
    printNumF(GanVdac,1,735,105,'.',4,' ');

    print("Xk_Abs=", 426,85, 0);//imprime texto en el centro
    printNumI(dBmA,484,85,4,' ');
    print("k=", 426,105, 0);
    printNumI(kaa,446,105,2,' ');
    print("Fmed=", 560,85, 0);
    printNumI(Fmed,600,85,7,' ');
    print("AB=", 560,105, 0);
    printNumI(ABmed,580,105,4,' ');
    setFont(BigFont);
    setColorRGB(0, 255, 255);
    setBackColorRGB(0, 0, 0);
    setButtonColors(VGA_YELLOW, VGA_RED, VGA_RED, VGA_LIME, VGA_BLUE);
    but10 = addButton( 416, 150, 95, 60, "Graf1",0);
    but11 = addButton( 517, 150, 95, 60, "Graf2",0);
    but3 = addButton( 517, 215, 196, 60, "|Xk|",0);
    but1 = addButton( 517, 280, 95,  60, "Xkr",0);
    but2 = addButton( 618, 280, 95,  60, "Xki",0);
    but5 = addButton( 517, 345, 95,  60, "-F",0);
    but4 = addButton( 618, 345, 95,  60, "+F",0);
    but6 = addButton( 517, 410, 196, 60, "SALIR",0);
    but7 = addButton( 416, 215, 95,  60, "G+",0);
    but8 = addButton( 416, 280, 95,  60, "G-",0);
    but9 = addButton( 416, 345, 95,  60, "Zoom-",0);
    but12 = addButton( 416, 410, 95,  60, "Zoom+",0);
    setFont(SmallFont);
    drawButtons();
    setColorRGB(0, 0, 0);

    /*
    REG_DACC_MR = (REG_DACC_MR & 0b11111111111111001111111111111111) | 0b00000000000000000000000000000000; //dac user sel canal 0
    REG_DACC_CHER=0b0000000000000000000000000000001;
    while ((REG_DACC_ISR & 0b00000000000000000000000000000001)== 0); //espera que el registro este disponible para una conversion
    REG_DACC_CDR = (GanVdac);//escribe el DAC con el valor del registro pwm
	*/

bandint=0;
while(bana==2){

  //************funcion para la adquision de los datos
    i=0;
    HAL_ADC_Start(&hadc1);		//enabled adc
    HAL_DAC_Start(&hdac, DAC_CHANNEL_1);

    timer_start();				//star counter
    while(bandint == 0){
    	//GPIOE->ODR ^= GPIO_PIN_0;
    }
    //GPIOE->ODR ^= GPIO_PIN_0;
    bandint=0;

   //*******Convierte los valores de 12bits en voltaje max 33volt
   i=0;
   while (i != N+1){
    xn[i]= ((xn[i]*33)/4095);
    i=i+1;
    }

   FFT_calculo();	//calcula la FFT

   if(prom==1){
	   Mayor_Xk(bandver);		//calcula el mayor del los coeficientes de la FFT

		setColor(VGA_YELLOW);
		setBackColorRGB(0, 0, 0); //establece color de fondo
		print("k=", 426,105, 0);
		print("Fmed=", 560,85, 0);

		if (bandver==0){
			print("Xkreal=", 426,85, 0);//imprime texto en el centro
			printNumI(dBmR,484,85,4,' ');
			printNumI(kar,446,105,2,' ');
			Fmed=kar*df;
			printNumI(Fmed,600,85,7,' ');
		}
		else if (bandver==1){
			print("Xkimag=", 426,85, 0);//imprime texto en el centro
			printNumI(dBmI,484,85,4,' ');
			printNumI(kai,446,105,2,' ');
			Fmed=kai*df;
			printNumI(Fmed,600,85,7,' ');
		}
		else if (bandver==2){
			print("Xk_Abs=", 426,85, 0);//imprime texto en el centro
			printNumI(dBmA,484,85,4,' ');
			printNumI(kaa,446,105,2,' ');
			Fmed=kaa*df;
			printNumI(Fmed,600,85,7,' ');
		}

		//dBmR = 10*log10((mayorr/0.001));
		//dBmI = 10*log10((mayori/0.001));
		//dBmA = 10*log10((mayorabs/0.001));
   } //de if (prom==1)

   else{
    while (k != Nout){
      if (bandver==0){
        Xkrp[k]= (((abs(Xkr[k]))+(Xkrp[k]))/2);
      }
      else if (bandver==1){
        Xkrp[k]= (((abs(Xki[k]))+(Xkrp[k]))/2);
      }
      else if (bandver==2){
        Xkrp[k]= (((sqrt((Xkr[k]*Xkr[k])+(Xki[k]*Xki[k])))+(Xkrp[k]))/2);
      }
      k=k+1;
    }
   }
    prom=prom+1;
    if (prom > (5)){   //ESTO LE DA LA SUAVIDAD EN LA CURVA DE SALIDA (SERIA EL FILTRO)
      prom=1;
    }

  //**********para graficar los Xk puntos
  k=0;
  kdi=4;
  kd=kdi;
  kds= 400/Nout;
  while (k < Nout){
    salXk[k]=(((Xkrp[k])));
    if (salXk[k] > 400){//222
      salXk[k]=400;  //222
    }
    else if(salXk[k]<17){
      salXk[k]=1;
    }

    if(menugraf == 0){
    	setColorRGB(50,50,90);  //para borrar los puntos
      if(k == Nout-1){
        drawLine(((kdi)), 470, ((kdi)), 17);
        drawLine(((kdi+1)), 470, ((kdi+1)),17);
        drawLine(((kdi+2)), 470, ((kdi+2)), 17);
        drawLine(((kdi+3)), 470, ((kdi+3)),17);
        drawLine(((kdi+4)), 470, ((kdi+4)), 17);
        drawLine(((kdi+5)), 470, ((kdi+5)),17);
       // drawLine(((kdi+6)), 470, ((kdi+6)), 17);
        //drawLine(((kdi+7)), 470, ((kdi+7)),17);
        //drawLine(((kdi+8)), 470, ((kdi+8)), 17);
        //drawLine(((kdi+9)), 470, ((kdi+9)),17);
        //drawLine(((kdi+10)), 470, ((kdi+10)), 17);
        //drawLine(((kdi+11)), 470, ((kdi+11)),17);
        //drawLine(((kdi+12)), 470, ((kdi+12)), 17);
      }
      else{
        drawLine(((kd)+kds), 470, ((kd)+kds), 17);
        drawLine(((kd+1)+kds), 470, ((kd+1)+kds),17);
        drawLine(((kd+2)+kds), 470, ((kd+2)+kds), 17);
        drawLine(((kd+3)+kds), 470, ((kd+3)+kds),17);
        drawLine(((kd+4)+kds), 470, ((kd+4)+kds), 17);
        drawLine(((kd+5)+kds), 470, ((kd+5)+kds),17);
        //drawLine(((kd+6)+kds), 470, ((kd+6)+kds), 17);
       // drawLine(((kd+7)+kds), 470, ((kd+7)+kds),17);
        //drawLine(((kd+8)+kds), 470, ((kd+8)+kds), 17);
        //drawLine(((kd+9)+kds), 470, ((kd+9)+kds),17);
        //drawLine(((kd+10)+kds), 470, ((kd+10)+kds), 17);
       //drawLine(((kd+11)+kds), 470, ((kd+11)+kds),17);
        //drawLine(((kd+12)+kds), 470, ((kd+12)+kds), 17);
      }

      //setColorRGB(0, 255, 255);
      setColor(VGA_AQUA);  //COLOT PARA GRAFICAR LOS PUNTOS
      drawLine((kd), 470, (kd), 470-salXk[k]);
      drawLine((kd+1),470, (kd+1), 470-salXk[k]);
      drawLine((kd+2),470, (kd+2), 470-salXk[k]);
      //delay_us(Tpers); 		//ESTE DELAY LE DA LA PERSISTENCIA
      k=k+1;
      kd=kd+kds;
    }
    else if(menugraf == 1){
    	setColorRGB(50,50,90);  //para borrar los puntos
      if(k == Nout-1){
        drawLine(((kdi)), 470, ((kdi)), 17);
        drawLine(((kdi+1)), 470, ((kdi+1)),17);
        drawLine(((kdi+2)), 470, ((kdi+2)), 17);
        drawLine(((kdi+3)), 470, ((kdi+3)),17);
        drawLine(((kdi+4)), 470, ((kdi+4)), 17);
        drawLine(((kdi+5)), 470, ((kdi+5)),17);
       // drawLine(((kdi+6)), 470, ((kdi+6)), 17);
       // drawLine(((kdi+7)), 470, ((kdi+7)),17);
        //drawLine(((kdi+8)), 470, ((kdi+8)), 17);
        //drawLine(((kdi+9)), 470, ((kdi+9)),17);
        //drawLine(((kdi+10)), 470, ((kdi+10)), 17);
        //drawLine(((kdi+11)), 470, ((kdi+11)),17);
        //drawLine(((kdi+12)), 470, ((kdi+12)), 17);
      }
      else{
        drawLine(((kd)+kds), 470, ((kd)+kds), 17);
        drawLine(((kd+1)+kds), 470, ((kd+1)+kds),17);
        drawLine(((kd+2)+kds), 470, ((kd+2)+kds), 17);
        drawLine(((kd+3)+kds), 470, ((kd+3)+kds),17);
        drawLine(((kd+4)+kds), 470, ((kd+4)+kds), 17);
        drawLine(((kd+5)+kds), 470, ((kd+5)+kds),17);
       // drawLine(((kd+6)+kds), 470, ((kd+6)+kds), 17);
       // drawLine(((kd+7)+kds), 470, ((kd+7)+kds),17);
       // drawLine(((kd+8)+kds), 470, ((kd+8)+kds), 17);
        //drawLine(((kd+9)+kds), 470, ((kd+9)+kds),17);
        //drawLine(((kd+10)+kds), 470, ((kd+10)+kds), 17);
        //drawLine(((kd+11)+kds), 470, ((kd+11)+kds),17);
        //drawLine(((kd+12)+kds), 470, ((kd+12)+kds), 17);
      }

      //setColorRGB(0, 255, 255);
      setColor(VGA_AQUA);  //COLOT PARA GRAFICAR LOS PUNTOS
      if (k==0){
        drawLine((kd), 470-salXk[k], (kd+2), 470-salXk[k]);
      }
      else{
        drawLine((kd-kds), 470-salXk[k-1], (kd+2), 470-salXk[k]);
      }
      //delay_us(Tpers); //ESTE DELAY LE DA LA PERSISTENCIA
      k=k+1;
      kd=kd+kds;
    }

    if (dataAvailable() == true){ //para preguntar si se presiono un boton
    	HAL_Delay(200);
    	pressed_button = checkButtons();
          setColor(VGA_YELLOW);
          setBackColorRGB(0, 0, 0); //establece color de fondo
      if (pressed_button==but1){  //Xkr
        bandver=0;
        print("Xkreal=", 426,85, 0);//imprime texto en el centro
              //dBmfun();
        printNumI(dBmR,484,85,4,' ');
       }
      else if (pressed_button==but2){ //Xki
        bandver=1;
        print("Xkimag=", 426,85, 0);//imprime texto en el centro
              //dBmfun();
        printNumI(dBmI,484,85,4,' ');
      }
      else if (pressed_button==but3){
        bandver=2;
        print("Xk_Abs=", 426,85, 0);
              //dBmfun();
        printNumI(dBmA,484,85,4,' ');
      }
      else if (pressed_button==but4){
          //masF();
    	  contFs=contFs-5;
		  if(contFs <= 2){
			  contFs=2;
			  Fs=2000000/(contFs);
		  }
		  else{
			  Fs=2000000/(contFs-1);
		  }

		  df= (Fs/N);
          printNumF(df,1,604,30,'.',4,' ');
          printNumI(Fs,725,30,7,' ');
          printNumI(((Nout-1)*df),486,30,7,' ');
       }
      else if (pressed_button==but5){
          //menosF();
          contFs=contFs+5;
		  if (contFs>20000){
			  contFs=20000;
		  }
		  Fs=2000000/(contFs-1);
		  df= (Fs/N);
          printNumF(df,1,604,30,'.',4,' ');
          printNumI(Fs,725,30,7,' ');
          printNumI(((Nout-1)*df),486,30,7,' ');
       }
      else if (pressed_button==but7){ //G-
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
          printNumF(GanV,1,735,85,'.',4,' ');
          printNumF(GanVdac,1,735,105,'.',4,' ');

          /*
          REG_DACC_MR = (REG_DACC_MR & 0b11111111111111001111111111111111) | 0b00000000000000000000000000000000; //dac user sel canal 0
          REG_DACC_CHER=0b0000000000000000000000000000001;
          while ((REG_DACC_ISR & 0b00000000000000000000000000000001)== 0); //espera que el registro este disponible para una conversion
          REG_DACC_CDR = (GanVdac);//escribe el DAC con el valor del registro pwm
       	   */
       }
      else if (pressed_button==but8){ //de G+
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
          printNumF(GanV,1,735,85,'.',4,' ');
          printNumF(GanVdac,1,735,105,'.',4,' ');
          /*
          REG_DACC_MR = (REG_DACC_MR & 0b11111111111111001111111111111111) | 0b00000000000000000000000000000000; //dac user sel canal 0
          REG_DACC_CHER=0b0000000000000000000000000000001;
          while ((REG_DACC_ISR & 0b00000000000000000000000000000001)== 0); //espera que el registro este disponible para una conversion
          REG_DACC_CDR = (GanVdac);//escribe el DAC con el valor del registro pwm
          */

       }
      else if (pressed_button==but9){ //Zoom-
    	  contFs=contFs-1;
    	  if(contFs <= 2){
			  contFs=2;
			  Fs=2000000/(contFs);
		  }
		  else{
			  Fs=2000000/(contFs-1);
		  }
		  df= (Fs/N);
          printNumF(df,1,604,30,'.',4,' ');
          printNumI(Fs,725,30,7,' ');
          printNumI(((Nout-1)*df),486,30,7,' ');
       }
      else if (pressed_button==but12){ //Zoom+
    	  contFs=contFs+1;
		  if(contFs>20000){
			  contFs=20000;
		  }
		  Fs=2000000/(contFs-1);
		  df= (Fs/N);
          printNumF(df,1,604,30,'.',4,' ');
          printNumI(Fs,725,30,7,' ');
          printNumI(((Nout-1)*df),486,30,7,' ');
       }
      else if (pressed_button==but10){ //Graf1
          menugraf=0;
       }
      else if (pressed_button==but11){ //Graf2
          menugraf=1;
       }
      else if (pressed_button==but6){ //salir
        bana=1;

        /*
        REG_DACC_MR = (REG_DACC_MR & 0b11111111111111001111111111111111) | 0b00000000000000000000000000000000; //dac user sel canal 0
        REG_DACC_CHER=0b0000000000000000000000000000001;
        while ((REG_DACC_ISR & 0b00000000000000000000000000000001)== 0); //espera que el registro este disponible para una conversion
        REG_DACC_CDR = (0);//escribe el DAC con el valor del registro pwm
       */

       }
     setColorRGB(0, 255, 255);
    }
  }
     /*
     setColorRGB(0, 0, 0);
     drawLine((kd), 399, (kd), 20);
     drawLine((kd+1),399, (kd+1), 20);
     drawLine((kd+2), 399, (kd+2), 20);
     //delayMicroseconds(900); //ESTE DELAY LE DA LA PERSISTENCIA
    */
 }
}


//funcion para mostrar el menu en Parametros en Muestras
void displaymenuPersistencia(){
	deleteAllButtons();
    //myButtons.setButtonColors(VGA_YELLOW, VGA_RED, VGA_RED, VGA_GRAY, VGA_BLUE);
    clrScr(); //borra pantalla
    setColorRGB(255,0, 0); //establece el color r,g,b en el rectangulo
    drawfillRoundRect(0, 0, ResH-1, 15); //dibuja un rectangulo
   // setColorRGB(64, 64, 64);  //establece color
    setColorRGB(255, 255, 255); //establece color de fondo
    setBackColorRGB(255, 0, 0); //establece color de fondo
    setFont(SmallFont);
    print("PERSISTENCIA VISUAL", CENTER,1, 0);//imprime texto en el centro
    setColorRGB(0, 0, 255);
    drawRectangulo(0, 15, ResH-1, ResV-1); //dibuja rectangulo de la pantalla
    setColorRGB(0, 255, 255);
    setBackColorRGB(0, 0, 0);

    setButtonColors(VGA_YELLOW, VGA_RED, VGA_RED, VGA_LIME, VGA_BLUE);
    but7 = addButton( 4,  155, 205,  60, "PERSISTENCIA",0);
    but1 = addButton( 215,  25, 200, 60, "1useg.",0);
    but2 = addButton( 215,  90, 200,  60, "100useg.",0);
    but3 = addButton( 215, 155, 200,  60, "250useg.",0);
    but4 = addButton( 215, 220, 200,  60, "500useg.",0);
    but5 = addButton( 215, 285, 200,  60, "1mseg.",0);
    but6 = addButton( 215, 350, 200,  60, "VOLVER",0);
    drawButtons();
}
//fucion para mostrar el menu en Parametros en Muestras
void displaymenuPromedio(){
    deleteAllButtons();
    //myButtons.setButtonColors(VGA_YELLOW, VGA_RED, VGA_RED, VGA_GRAY, VGA_BLUE);
    clrScr(); //borra pantalla
    setColorRGB(255,0, 0); //establece el color r,g,b en el rectangulo
    drawfillRoundRect(0, 0, ResH-1, 15); //dibuja un rectangulo
   // setColorRGB(64, 64, 64);  //establece color
    setColorRGB(255, 255, 255); //establece color de fondo
    setBackColorRGB(255, 0, 0); //establece color de fondo
    setFont(SmallFont);
    print("PROMEDIO DE SALIDA", CENTER,1, 0);//imprime texto en el centro
    setColorRGB(0, 0, 255);
    drawRectangulo(0, 15, ResH-1, ResV-1); //dibuja rectangulo de la pantalla
    setColorRGB(0, 255, 255);
    setBackColorRGB(0, 0, 0);

    setButtonColors(VGA_YELLOW, VGA_RED, VGA_RED, VGA_LIME, VGA_BLUE);
    but7 = addButton( 4,  155, 195,  60, "PROMEDIO",0);
    but1 = addButton( 205,  25, 200,  60, "10",0);
    but2 = addButton( 205,  90, 200,  60, "200",0);
    but3 = addButton( 205, 155, 200,  60, "500",0);
    but4 = addButton( 205, 220, 200,  60, "1000",0);
    but5 = addButton( 205, 285, 200,  60, "2000",0);
    but6 = addButton( 205, 350, 200,  60, "VOLVER",0);
    drawButtons();
}
//fucion para mostrar el menu en Parametros en Muestras
void displaymenuFrecuencia(){
   deleteAllButtons();
    //myButtons.setButtonColors(VGA_YELLOW, VGA_RED, VGA_RED, VGA_GRAY, VGA_BLUE);
    clrScr(); //borra pantalla
    setColorRGB(255,0, 0); //establece el color r,g,b en el rectangulo
    drawfillRoundRect(0, 0, ResH-1, 15); //dibuja un rectangulo
   // setColorRGB(64, 64, 64);  //establece color
    setColorRGB(255, 255, 255); //establece color de fondo
    setBackColorRGB(255, 0, 0); //establece color de fondo
    setFont(SmallFont);
    print("RANGO DE FRECUENCIA", CENTER,1, 0);//imprime texto en el centro
    setColorRGB(0, 0, 255);
    drawRectangulo(0, 15, ResH-1, ResV-1); //dibuja rectangulo de la pantalla
    setColorRGB(0, 255, 255);
    setBackColorRGB(0, 0, 0);

    setButtonColors(VGA_YELLOW, VGA_RED, VGA_RED, VGA_LIME, VGA_BLUE);
    but7 = addButton( 4,  155, 195,  60, "FRECUENCIA",0);
    but1 = addButton( 205,  25, 200,  60, "0<F<100hz",0);
    but2 = addButton( 205,  90, 200,  60, "0<F<1Khz",0);
    but3 = addButton( 205, 155, 200,  60, "0<F<10Khz",0);
    but4 = addButton( 205, 220, 200,  60, "0<F<10Khz",0);
    but5 = addButton( 205, 285, 200,  60, "0<F<1Mhz",0);
    but6 = addButton( 205, 350, 200,  60, "VOLVER",0);
    drawButtons();
}
//fucion para mostrar el menu en Parametros en Muestras
void displaymenuMuestras(){
    deleteAllButtons();
    //myButtons.setButtonColors(VGA_YELLOW, VGA_RED, VGA_RED, VGA_GRAY, VGA_BLUE);
    clrScr(); //borra pantalla
    setColorRGB(255,0, 0); //establece el color r,g,b en el rectangulo
    drawfillRoundRect(0, 0, ResH-1, 15); //dibuja un rectangulo
    //setColorRGB(64, 64, 64);  //establece color
    setColorRGB(255, 255, 255); //establece color de fondo
    setBackColorRGB(255, 0, 0); //establece color de fondo
     setFont(SmallFont);
    print("NUMERO DE MUESTRAS", CENTER,1, 0);//imprime texto en el centro
    setColorRGB(0, 0, 255);
    drawRectangulo(0, 15, ResH-1, ResV-1); //dibuja rectangulo de la pantalla
    setColorRGB(0, 255, 255);
    setBackColorRGB(0, 0, 0);

    setButtonColors(VGA_YELLOW, VGA_RED, VGA_RED, VGA_LIME, VGA_BLUE);
    but7 = addButton( 4,  25, 200,  60, "MUESTRAS",0);
    but1 = addButton( 205,  25, 200,  60, "N = 32",0);
    but2 = addButton( 205, 90, 200,  60, "N = 64",0);
    but3 = addButton( 205, 155, 200,  60, "N = 128",0);
    but4 = addButton( 205, 220, 200,  60, "N = 256",0);
    but5 = addButton( 205, 285, 200,  60, "N = 512",0);
    but6 = addButton( 205, 350, 200,  60, "VOLVER",0);
    drawButtons();
}

//fucion para mostrar el menu en Parametros
void displaymenufft(){
   deleteAllButtons();
    //myButtons.setButtonColors(VGA_YELLOW, VGA_RED, VGA_RED, VGA_GRAY, VGA_BLUE);
    clrScr(); //borra pantalla
    setColorRGB(255,0, 0); //establece el color r,g,b en el rectangulo
    drawfillRoundRect(0, 0, ResH-1, 15); //dibuja un rectangulo
  // setColorRGB(64, 64, 64);  //establece color
    setColorRGB(255, 255, 255); //establece color de fondo
    setBackColorRGB(255, 0, 0); //establece color de fondo
    setFont(SmallFont);
    print("PARAMETROS", CENTER,1, 0);//imprime texto en el centro
    setColorRGB(0, 0, 255);
    drawRectangulo(0, 15, ResH-1, ResV-1); //dibuja rectangulo de la pantalla
    setColorRGB(0, 255, 255);
    setBackColorRGB(0, 0, 0);

    setButtonColors(VGA_YELLOW, VGA_RED, VGA_RED, VGA_LIME, VGA_BLUE);
    but1 = addButton( 4,  25, 200,  60, "FFT",0);
    but2 = addButton( 210,  90, 215,  60, "CONFIGURACION",0);
    but3 = addButton( 435,  90, 200,  60, "MUESTRAS",0);
    but4 = addButton( 435,  155, 200,  60, "FRECUENCIA",0);
    but5 = addButton( 435,  220, 200,  60, "PERSISTENCIA",0);
    but6 = addButton( 435,  285, 200, 60, "PROMEDIO",0);
    but7 = addButton( 435, 350, 200,  60, "VOLVER",0);
    drawButtons();
}

//funcion para mostrar el menu en FFT
void displaymenuf(){
 deleteAllButtons();
 clrScr(); //borra pantalla
 setColorRGB(255,0, 0); //establece el color r,g,b en el rectangulo
 drawfillRoundRect(0, 0, ResH-1, 15); //dibuja un rectangulo
 //setColorRGB(64, 64, 64);  //establece color
 setColorRGB(255, 255, 255); //establece color de fondo
 setBackColorRGB(255, 0, 0); //establece color de fondo
 setFont(SmallFont);
 print("TRANSFORMADA RAPIDA DE FOURIER", CENTER,1, 0);//imprime texto en el centro
 setColorRGB(0, 0, 255);
 drawRectangulo(0, 15, ResH-1, ResV-1); //dibuja rectangulo de la pantalla

  setButtonColors(VGA_YELLOW, VGA_RED, VGA_RED, VGA_LIME, VGA_BLUE);
  but1 = addButton( 4,  25, 200,  60, "FFT",0);
  but2 = addButton( 210,  25, 200,  60, "MODO",0);
  but3 = addButton( 210,  95, 200,  60, "CONFIG.",0);
  but4 = addButton( 210, 165, 200,  60, "VOLVER",0);
  drawButtons();
}



#endif /* FFT_H_ */
