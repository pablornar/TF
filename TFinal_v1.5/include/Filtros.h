/*
 * Funciones para implementar un filtro fir pasa bajos, pasa altos, pasa banda y rechaza banda.
 */
#ifndef FILTRO_H_
#define FILTRO_H_

void menufiltro(void);
void coeficientesLPBP(void);
void verparametrosLPBP(void);
void filtroLP(void);
void filtroHP(void);
void filtroBP(void);
void filtroBR(void);
void coeficientesLP();
void verparametrosfiltro();
void coeficientesHP();
void coeficientesBP();
void coeficientesBR();

void Filtros(){
 menufiltro();
 bana=2;
 while(bana==2)
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
        filtroLP();
        clrScr(); //borra pantalla
        menufiltro();
    }
      else if (pressed_button==but3){
        clrScr(); //borra pantalla
        filtroHP();
        clrScr(); //borra pantalla
        menufiltro();
    }
    else if (pressed_button==but4){
        clrScr(); //borra pantalla
        filtroBP();
        clrScr(); //borra pantalla
        menufiltro();
    }
    else if (pressed_button==but5){
        clrScr(); //borra pantalla
        filtroBR();
        clrScr(); //borra pantalla
        menufiltro();
    }
    else if (pressed_button==but6){
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


//*************************funcion para filtro pasa bajos
void filtroLP(){
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
short ban=1;
int bana;
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

//calculo de los coeficiente del filtro LP y BP
  coeficientesLP();

  deleteAllButtons();
  clrScr(); //borra pantalla

  verparametrosfiltro();

  setColorRGB(255,0, 0); //establece el color r,g,b en el rectangulo
  drawfillRoundRect(0, 0, ResH-1, 15); //dibuja un rectangulo
  //setColorRGB(64, 64, 64);  //establece color
  setColorRGB(255, 255, 255); //establece color de fondo
  setBackColorRGB(255, 0, 0); //establece color de fondo
  setFont(BigFont);
  print("Filtro Pasa Bajos", LEFT,1, 0);//imprime texto en el centro
  setColorRGB(0, 0, 255);
  drawRectangulo(0, 15, ResH-1, ResV-1); //dibuja rectangulo de la pantalla
  drawRectangulo(600, 15, ResH-1, ResV-1); //dibuja rectangulo de menu en pantalla
  drawRectangulo(600, 15, ResH-1,70); //dibuja rectangulo de menu en pantalla para ganancia
  drawRectangulo(600, 70, ResH-1,130 ); //dibuja rectangulo de menu en pantalla para otros
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
    df= (N*Tret);
    df= (1000000/df);
    Fs= (1000000/Tret);
    print("df=", 705,85, 0);
    print("Fs=", 705,105, 0);
    printNumF(df,1,730,85,'.',4,' ');
    printNumF(Fs,1,730,105,'.',4,' ');
    print("Desf=", 605,50, 0);
    printNumF(Cmd,1,645,50,'.',4,' ');

    setButtonColors(VGA_YELLOW, VGA_RED, VGA_RED, VGA_LIME, VGA_BLUE);
    but1 = addButton(605, 140, 90, 60, "Gan+",0);
    but2 = addButton(605, 205, 90, 60, "Gan-",0);
    but3 = addButton(705, 140, 90, 60, "T+",0);
    but4 = addButton(705, 205, 90, 60, "T-",0);
    but5 = addButton(605, 270, 90, 60, "Desf+",0);
    but6 = addButton(605, 335, 90, 60, "Desf-",0);
    but7 = addButton(605, 410, 190, 60, "Salir",0);
    drawButtons();

    setColorRGB(0, 255, 255);
    setBackColorRGB(0, 0, 0);

    /*
    REG_DACC_MR = (REG_DACC_MR & 0b11111111111111001111111111111111) | 0b00000000000000000000000000000000; //dac user sel canal 0
    REG_DACC_CHER=0b0000000000000000000000000000001;
    while ((REG_DACC_ISR & 0b00000000000000000000000000000001)== 0); //espera que el registro este disponible para una conversion
    REG_DACC_CDR = (GanVdac);//escribe el DAC con el valor del registro pwm
	*/


  bana=2;
while(bana==2){

    //************funcion para la adquision de los datos
    i=0;
    N=250+(2*Nfir);
    //REG_TC0_CCR0=0b00000000000000000000000000000101;    // start counter
    timer_start();
    while(bandint == 0){
    	GPIOE->ODR ^= GPIO_PIN_0;
    }
    GPIOE->ODR ^= GPIO_PIN_0;
    bandint=0;

    //**************para poner xn con valores positivos y negativos
     i=0;
    while (i != N+1){
      xns[i]=((xn[i])-2048);
      i=i+1;
    }

      //+++++++++++calculo de la senal filtada pasabajos Xfam[]
      N=250;
      k=0;
      n=0;
      auxnf=0;
      while(n < N+1){
        while(k < (Nfir)){
          xnfd[n]=(hd[k])*(xns[((N+Nfir)-n)-k]);
          auxnf= ((xnfd[n])/100)+ auxnf;
          k=k+1;
        }
        xnf[n]=((auxnf)+2048)*1;  //5.2
        if ((xnf[n]) > 4095){    //800
          xnf[n]=4095;
        }
        auxnf=0;
        k=0;
        n=n+1;
      }

    i=0;
    while (i != N+1){
      sallcd[i]=((xn[i]*400)/4095);
      xnf[i]=((xnf[i]*400)/4095);
      I[i]=sallcd[i]-200;     //agrega la parte negativa de la senal
      Q[i]=sallcd[i]-200;     //agrega la parte negativa de la senal
      i=i+1;
    }

    //********para dibujar
      i=1;
      iT=1;
      Tvisual = ((598/N)+1);
      iT=iT+Tvisual;
      while (iT < 598 ){
        displayejes();
        setColorRGB(0, 0, 0);
        if ((iT >= (598-(Tvisual+1))) && (iT <= (598-Tvisual))){
          iTClear=1;
          while((iTClear) <=(Tvisual)){
            drawLine(iTClear, ResV-2, iTClear, 16);
            iTClear=iTClear+1;
          }
        }
        else if (iT <= (598-Tvisual)){
          iTClear=iT;
          while(iTClear <= (iT+Tvisual)){
            drawLine(iTClear, ResV-2, iTClear, 16);
            iTClear=iTClear+1;
          }
        }
        setColorRGB(0, 255, 255);
        drawLine(iT-Tvisual, (400-sallcd[i-1]), iT, (400-sallcd[i])); // es 255 para sumar el desfasaje del rectangulo de arriba
        setColorRGB(0, 255, 0);
        //drawLine(iT-Tvisual, (400-(Q[i-1]+200)), iT, (400-(Q[i]+200)));
        drawLine(iT-Tvisual, (400-xnf[i-1]), iT, (400-xnf[i]));

        i=i+1;
        iT=iT+Tvisual;
      }
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
        //delay(100);
        Tret=Tret+0.1;
          Tretint=((Fclock/2)*Tret);
          //REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          df= (N*Tret);
          df= (1000000/df);
          Fs= (1000000/Tret);
          printNumF(df,1,730,85,'.',4,' ');
          printNumF(Fs,1,730,105,'.',4,' ');
        }
       else if (pressed_button==but4){
        //delay(100);
          Tret=Tret-0.1;
          Tretint=((Fclock/2)*Tret);
          //REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          df= (N*Tret);
          df= (1000000/df);
          Fs= (1000000/Tret);
          printNumF(df,1,730,85,'.',4,' ');
          printNumF(Fs,1,730,105,'.',4,' ');
        }
        else if (pressed_button==but5){
        //delay(100);
          Cmd=Cmd+1;
          printNumF(Cmd,1,645,50,'.',4,' ');
        }
        else if (pressed_button==but6){
        //delay(100);
          Cmd=Cmd-1;
          printNumF(Cmd,1,645,50,'.',4,' ');
        }
       else if (pressed_button==but7){
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
}

//*************************funcion para filtro pasa altos
void filtroHP(){
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
short ban=1;
int bana;
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

//calculo de los coeficiente del filtro HP
  coeficientesHP();

  deleteAllButtons();
  clrScr(); //borra pantalla

  verparametrosfiltro();

  setColorRGB(255,0, 0); //establece el color r,g,b en el rectangulo
  drawfillRoundRect(0, 0, ResH-1, 15); //dibuja un rectangulo
  //setColorRGB(64, 64, 64);  //establece color
  setColorRGB(255, 255, 255); //establece color de fondo
  setBackColorRGB(255, 0, 0); //establece color de fondo
  setFont(BigFont);
  print("Filtro Pasa Altos", LEFT,1, 0);//imprime texto en el centro
  setColorRGB(0, 0, 255);
  drawRectangulo(0, 15, ResH-1, ResV-1); //dibuja rectangulo de la pantalla
  drawRectangulo(600, 15, ResH-1, ResV-1); //dibuja rectangulo de menu en pantalla
  drawRectangulo(600, 15, ResH-1,70); //dibuja rectangulo de menu en pantalla para ganancia
  drawRectangulo(600, 70, ResH-1,130 ); //dibuja rectangulo de menu en pantalla para otros
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
    df= (N*Tret);
    df= (1000000/df);
    Fs= (1000000/Tret);
    print("df=", 705,85, 0);
    print("Fs=", 705,105, 0);
    printNumF(df,1,730,85,'.',4,' ');
    printNumF(Fs,1,730,105,'.',4,' ');
    print("Desf=", 605,50, 0);
    printNumF(Cmd,1,645,50,'.',4,' ');

    setButtonColors(VGA_YELLOW, VGA_RED, VGA_RED, VGA_LIME, VGA_BLUE);
    but1 = addButton(605, 140, 90, 60, "Gan+",0);
    but2 = addButton(605, 205, 90, 60, "Gan-",0);
    but3 = addButton(705, 140, 90, 60, "T+",0);
    but4 = addButton(705, 205, 90, 60, "T-",0);
    but5 = addButton(605, 270, 90, 60, "Desf+",0);
    but6 = addButton(605, 335, 90, 60, "Desf-",0);
    but7 = addButton(605, 410, 190, 60, "Salir",0);
    drawButtons();

    setColorRGB(0, 255, 255);
    setBackColorRGB(0, 0, 0);

    /*
    REG_DACC_MR = (REG_DACC_MR & 0b11111111111111001111111111111111) | 0b00000000000000000000000000000000; //dac user sel canal 0
    REG_DACC_CHER=0b0000000000000000000000000000001;
    while ((REG_DACC_ISR & 0b00000000000000000000000000000001)== 0); //espera que el registro este disponible para una conversion
    REG_DACC_CDR = (GanVdac);//escribe el DAC con el valor del registro pwm
	*/


  bana=2;
while(bana==2){

    //************funcion para la adquision de los datos
    i=0;
    N=250+(2*Nfir);
   // REG_TC0_CCR0=0b00000000000000000000000000000101;    // start counter
    timer_start();
    while(bandint == 0){
    	GPIOE->ODR ^= GPIO_PIN_0;
    }
    GPIOE->ODR ^= GPIO_PIN_0;
    bandint=0;

    //**************para poner xn con valores positivos y negativos
     i=0;
    while (i != N+1){
      xns[i]=((xn[i])-2048);
      i=i+1;
    }

      //+++++++++++calculo de la senal filtada pasa altos xnf[]
      N=250;
      k=0;
      n=0;
      auxnf=0;
      auxnf1=0;
      while(n < N+1){
        while(k < (Nfir)){
          xnfd[n]=(hd[k])*(xns[((N+Nfir)-n)-k]);
          auxnf= ((xnfd[n])/100)+ auxnf;
          k=k+1;
        }

        //Serial.println(auxnf);
        xnf[n]=((auxnf)+2048)*1;  //5.2
        //xnf[n]=-(xnf[n]);
        if ((xnf[n]) > 4095){    //800
          xnf[n]=4095;
        }
         else if ((xnf[n]) < 1){    //800
          xnf[n]=1;
        }
        /*
        Serial.print(xnf[n]);
        Serial.print("--");
        Serial.print(n);
        Serial.println(" ");
        */
        auxnf=0;
        k=0;
        n=n+1;
      }

    i=0;
    while (i != N+1){
      sallcd[i]=((xn[i]*400)/4095);
      xnf[i]=((xnf[i]*400)/4095);
      I[i]=sallcd[i]-200;     //agrega la parte negativa de la senal
      Q[i]=sallcd[i]-200;     //agrega la parte negativa de la senal
      i=i+1;
    }

    //********para dibujar
      i=1;
      iT=1;
      Tvisual = ((598/N)+1);
      iT=iT+Tvisual;
      while (iT < 598 ){
        displayejes();
        setColorRGB(0, 0, 0);
        if ((iT >= (598-(Tvisual+1))) && (iT <= (598-Tvisual))){
          iTClear=1;
          while((iTClear) <=(Tvisual)){
            drawLine(iTClear, ResV-2, iTClear, 16);
            iTClear=iTClear+1;
          }
        }
        else if (iT <= (598-Tvisual)){
          iTClear=iT;
          while(iTClear <= (iT+Tvisual)){
            drawLine(iTClear, ResV-2, iTClear, 16);
            iTClear=iTClear+1;
          }
        }
        setColorRGB(0, 255, 255);
        drawLine(iT-Tvisual, (400-sallcd[i-1]), iT, (400-sallcd[i])); // es 255 para sumar el desfasaje del rectangulo de arriba
        setColorRGB(0, 255, 0);
        //drawLine(iT-Tvisual, (400-(Q[i-1]+200)), iT, (400-(Q[i]+200)));
        drawLine(iT-Tvisual, (400-xnf[i-1]), iT, (400-xnf[i]));

        i=i+1;
        iT=iT+Tvisual;
      }
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
        //delay(100);
        Tret=Tret+0.1;
          Tretint=((Fclock/2)*Tret);
         // REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          df= (N*Tret);
          df= (1000000/df);
          Fs= (1000000/Tret);
          printNumF(df,1,730,85,'.',4,' ');
          printNumF(Fs,1,730,105,'.',4,' ');
        }
       else if (pressed_button==but4){
        //delay(100);
          Tret=Tret-0.1;
          Tretint=((Fclock/2)*Tret);
          //REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          df= (N*Tret);
          df= (1000000/df);
          Fs= (1000000/Tret);
          printNumF(df,1,730,85,'.',4,' ');
          printNumF(Fs,1,730,105,'.',4,' ');
        }
        else if (pressed_button==but5){
        //delay(100);
          Cmd=Cmd+1;
          printNumF(Cmd,1,645,50,'.',4,' ');
        }
        else if (pressed_button==but6){
        //delay(100);
          Cmd=Cmd-1;
          printNumF(Cmd,1,645,50,'.',4,' ');
        }
       else if (pressed_button==but7){
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
}

//*************************funcion para filtro pasa banda
void filtroBP(){
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
short ban=1;
int bana;
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

//calculo de los coeficiente del filtro BP
  coeficientesBP();

  deleteAllButtons();
  clrScr(); //borra pantalla

  verparametrosfiltro();

  setColorRGB(255,0, 0); //establece el color r,g,b en el rectangulo
  drawfillRoundRect(0, 0, ResH-1, 15); //dibuja un rectangulo
  //setColorRGB(64, 64, 64);  //establece color
  setColorRGB(255, 255, 255); //establece color de fondo
  setBackColorRGB(255, 0, 0); //establece color de fondo
  setFont(BigFont);
  print("Filtro Pasa Banda", LEFT,1, 0);//imprime texto en el centro
  setColorRGB(0, 0, 255);
  drawRectangulo(0, 15, ResH-1, ResV-1); //dibuja rectangulo de la pantalla
  drawRectangulo(600, 15, ResH-1, ResV-1); //dibuja rectangulo de menu en pantalla
  drawRectangulo(600, 15, ResH-1,70); //dibuja rectangulo de menu en pantalla para ganancia
  drawRectangulo(600, 70, ResH-1,130 ); //dibuja rectangulo de menu en pantalla para otros
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
    df= (N*Tret);
    df= (1000000/df);
    Fs= (1000000/Tret);
    print("df=", 705,85, 0);
    print("Fs=", 705,105, 0);
    printNumF(df,1,730,85,'.',4,' ');
    printNumF(Fs,1,730,105,'.',4,' ');
    print("Desf=", 605,50, 0);
    printNumF(Cmd,1,645,50,'.',4,' ');

    setButtonColors(VGA_YELLOW, VGA_RED, VGA_RED, VGA_LIME, VGA_BLUE);
    but1 = addButton(605, 140, 90, 60, "Gan+",0);
    but2 = addButton(605, 205, 90, 60, "Gan-",0);
    but3 = addButton(705, 140, 90, 60, "T+",0);
    but4 = addButton(705, 205, 90, 60, "T-",0);
    but5 = addButton(605, 270, 90, 60, "Desf+",0);
    but6 = addButton(605, 335, 90, 60, "Desf-",0);
    but7 = addButton(605, 410, 190, 60, "Salir",0);
    drawButtons();

    setColorRGB(0, 255, 255);
    setBackColorRGB(0, 0, 0);

    /*
    REG_DACC_MR = (REG_DACC_MR & 0b11111111111111001111111111111111) | 0b00000000000000000000000000000000; //dac user sel canal 0
    REG_DACC_CHER=0b0000000000000000000000000000001;
    while ((REG_DACC_ISR & 0b00000000000000000000000000000001)== 0); //espera que el registro este disponible para una conversion
    REG_DACC_CDR = (GanVdac);//escribe el DAC con el valor del registro pwm
	*/


  bana=2;
while(bana==2){

    //************funcion para la adquision de los datos
    i=0;
    N=250+(2*Nfir);
    //REG_TC0_CCR0=0b00000000000000000000000000000101;    // start counter
    timer_start();
    while(bandint == 0){
    	GPIOE->ODR ^= GPIO_PIN_0;
    }
    GPIOE->ODR ^= GPIO_PIN_0;
    bandint=0;

    //**************para poner xn con valores positivos y negativos
     i=0;
    while (i != N+1){
      xns[i]=((xn[i])-2048);
      i=i+1;
    }

      //+++++++++++calculo de la senal filtada pasabanda xnf[]
      N=250;
      k=0;
      n=0;
      auxnf=0;
      auxnf1=0;
      while(n < N+1){
        while(k < (Nfir)){
          xnfd[n]=(hd[k])*(xns[((N+Nfir)-n)-k]);
          auxnf= ((xnfd[n])/100)+ auxnf;
          k=k+1;
        }

        xnf[n]=((auxnf)+2048)*1;  //5.2
        //xnf[n]=-(xnf[n]);
        if ((xnf[n]) > 4095){    //800
          xnf[n]=4095;
        }
        /*
        Serial.print(xnf[n]);
        Serial.print("--");
        Serial.print(n);
        Serial.println(" ");
        */
        auxnf=0;
        k=0;
        n=n+1;
      }

    i=0;
    while (i != N+1){
      sallcd[i]=((xn[i]*400)/4095);
      xnf[i]=((xnf[i]*400)/4095);
      I[i]=sallcd[i]-200;     //agrega la parte negativa de la senal
      Q[i]=sallcd[i]-200;     //agrega la parte negativa de la senal
      i=i+1;
    }

    //********para dibujar
      i=1;
      iT=1;
      Tvisual = ((598/N)+1);
      iT=iT+Tvisual;
      while (iT < 598 ){
        displayejes();
        setColorRGB(0, 0, 0);
        if ((iT >= (598-(Tvisual+1))) && (iT <= (598-Tvisual))){
          iTClear=1;
          while((iTClear) <=(Tvisual)){
            drawLine(iTClear, ResV-2, iTClear, 16);
            iTClear=iTClear+1;
          }
        }
        else if (iT <= (598-Tvisual)){
          iTClear=iT;
          while(iTClear <= (iT+Tvisual)){
            drawLine(iTClear, ResV-2, iTClear, 16);
            iTClear=iTClear+1;
          }
        }
        setColorRGB(0, 255, 255);
        drawLine(iT-Tvisual, (400-sallcd[i-1]), iT, (400-sallcd[i])); // es 255 para sumar el desfasaje del rectangulo de arriba
        setColorRGB(0, 255, 0);
        //drawLine(iT-Tvisual, (400-(Q[i-1]+200)), iT, (400-(Q[i]+200)));
        drawLine(iT-Tvisual, (400-xnf[i-1]), iT, (400-xnf[i]));

        i=i+1;
        iT=iT+Tvisual;
      }
  if (dataAvailable() == true)  //para preguntar si se presiono un boton
     {
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
        //delay(100);
        Tret=Tret+0.1;
          Tretint=((Fclock/2)*Tret);
         // REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          df= (N*Tret);
          df= (1000000/df);
          Fs= (1000000/Tret);
          printNumF(df,1,730,85,'.',4,' ');
          printNumF(Fs,1,730,105,'.',4,' ');
        }
       else if (pressed_button==but4){
        //delay(100);
          Tret=Tret-0.1;
          Tretint=((Fclock/2)*Tret);
         // REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          df= (N*Tret);
          df= (1000000/df);
          Fs= (1000000/Tret);
          printNumF(df,1,730,85,'.',4,' ');
          printNumF(Fs,1,730,105,'.',4,' ');
        }
        else if (pressed_button==but5){
        //delay(100);
          Cmd=Cmd+1;
          printNumF(Cmd,1,645,50,'.',4,' ');
        }
        else if (pressed_button==but6){
        //delay(100);
          Cmd=Cmd-1;
          printNumF(Cmd,1,645,50,'.',4,' ');
        }
       else if (pressed_button==but7){
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
}

//*************************funcion para filtro rechaza banda
void filtroBR(){
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
short ban=1;
int bana;
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

//calculo de los coeficiente del filtro BR
  coeficientesBR();

  deleteAllButtons();
  clrScr(); //borra pantalla

  verparametrosfiltro();

  setColorRGB(255,0, 0); //establece el color r,g,b en el rectangulo
  drawfillRoundRect(0, 0, ResH-1, 15); //dibuja un rectangulo
  //setColorRGB(64, 64, 64);  //establece color
  setColorRGB(255, 255, 255); //establece color de fondo
  setBackColorRGB(255, 0, 0); //establece color de fondo
  setFont(BigFont);
  print("Filtro Rechaza Banda", LEFT,1, 0);//imprime texto en el centro
  setColorRGB(0, 0, 255);
  drawRectangulo(0, 15, ResH-1, ResV-1); //dibuja rectangulo de la pantalla
  drawRectangulo(600, 15, ResH-1, ResV-1); //dibuja rectangulo de menu en pantalla
  drawRectangulo(600, 15, ResH-1,70); //dibuja rectangulo de menu en pantalla para ganancia
  drawRectangulo(600, 70, ResH-1,130 ); //dibuja rectangulo de menu en pantalla para otros
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
    df= (N*Tret);
    df= (1000000/df);
    Fs= (1000000/Tret);
    print("df=", 705,85, 0);
    print("Fs=", 705,105, 0);
    printNumF(df,1,730,85,'.',4,' ');
    printNumF(Fs,1,730,105,'.',4,' ');
    print("Desf=", 605,50, 0);
    printNumF(Cmd,1,645,50,'.',4,' ');

    setButtonColors(VGA_YELLOW, VGA_RED, VGA_RED, VGA_LIME, VGA_BLUE);
    but1 = addButton(605, 140, 90, 60, "Gan+",0);
    but2 = addButton(605, 205, 90, 60, "Gan-",0);
    but3 = addButton(705, 140, 90, 60, "T+",0);
    but4 = addButton(705, 205, 90, 60, "T-",0);
    but5 = addButton(605, 270, 90, 60, "Desf+",0);
    but6 = addButton(605, 335, 90, 60, "Desf-",0);
    but7 = addButton(605, 410, 190, 60, "Salir",0);
    drawButtons();

    setColorRGB(0, 255, 255);
    setBackColorRGB(0, 0, 0);

    /*
    REG_DACC_MR = (REG_DACC_MR & 0b11111111111111001111111111111111) | 0b00000000000000000000000000000000; //dac user sel canal 0
    REG_DACC_CHER=0b0000000000000000000000000000001;
    while ((REG_DACC_ISR & 0b00000000000000000000000000000001)== 0); //espera que el registro este disponible para una conversion
    REG_DACC_CDR = (GanVdac);//escribe el DAC con el valor del registro pwm
	*/


  bana=2;
while(bana==2){

    //************funcion para la adquision de los datos
    i=0;
    N=250+(2*Nfir);
    //REG_TC0_CCR0=0b00000000000000000000000000000101;    // start counter
    timer_start();
    while(bandint == 0){
    	GPIOE->ODR ^= GPIO_PIN_0;
    }
    GPIOE->ODR ^= GPIO_PIN_0;
    bandint=0;

    //**************para poner xn con valores positivos y negativos
     i=0;
    while (i != N+1){
      xns[i]=((xn[i])-2048);
      i=i+1;
    }

      //+++++++++++calculo de la senal filtada rechaza banda xnf[]
      N=250;
      k=0;
      n=0;
      auxnf=0;
      while(n < N+1){
        while(k < (Nfir)){
          xnfd[n]=(hd[k])*(xns[((N+Nfir)-n)-k]);
          auxnf= ((xnfd[n])/100)+ auxnf;
          k=k+1;
        }

        xnf[n]=((auxnf)+2048)*1;  //5.2
        //xnf[n]=-(xnf[n]);
        if ((xnf[n]) > 4095){    //800
          xnf[n]=4095;
        }
        else if ((xnf[n]) < 1){    //800
          xnf[n]=1;
        }
        /*
        Serial.print(xnf[n]);
        Serial.print("--");
        Serial.print(n);
        Serial.println(" ");
        */
        auxnf=0;
        k=0;
        n=n+1;
      }

    i=0;
    while (i != N+1){
      sallcd[i]=((xn[i]*400)/4095);
      xnf[i]=((xnf[i]*400)/4095);
      I[i]=sallcd[i]-200;     //agrega la parte negativa de la senal
      Q[i]=sallcd[i]-200;     //agrega la parte negativa de la senal
      i=i+1;
    }

    //********para dibujar
      i=1;
      iT=1;
      Tvisual = ((598/N)+1);
      iT=iT+Tvisual;
      while (iT < 598 ){
        displayejes();
        setColorRGB(0, 0, 0);
        if ((iT >= (598-(Tvisual+1))) && (iT <= (598-Tvisual))){
          iTClear=1;
          while((iTClear) <=(Tvisual)){
            drawLine(iTClear, ResV-2, iTClear, 16);
            iTClear=iTClear+1;
          }
        }
        else if (iT <= (598-Tvisual)){
          iTClear=iT;
          while(iTClear <= (iT+Tvisual)){
            drawLine(iTClear, ResV-2, iTClear, 16);
            iTClear=iTClear+1;
          }
        }
        setColorRGB(0, 255, 255);
        drawLine(iT-Tvisual, (400-sallcd[i-1]), iT, (400-sallcd[i])); // es 255 para sumar el desfasaje del rectangulo de arriba
        setColorRGB(0, 255, 0);
        //drawLine(iT-Tvisual, (400-(Q[i-1]+200)), iT, (400-(Q[i]+200)));
        drawLine(iT-Tvisual, (400-xnf[i-1]), iT, (400-xnf[i]));

        i=i+1;
        iT=iT+Tvisual;
      }
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
        //delay(100);
        Tret=Tret+0.1;
          Tretint=((Fclock/2)*Tret);
          //REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          df= (N*Tret);
          df= (1000000/df);
          Fs= (1000000/Tret);
          printNumF(df,1,730,85,'.',4,' ');
          printNumF(Fs,1,730,105,'.',4,' ');
        }
       else if (pressed_button==but4){
        //delay(100);
          Tret=Tret-0.1;
          Tretint=((Fclock/2)*Tret);
         // REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          df= (N*Tret);
          df= (1000000/df);
          Fs= (1000000/Tret);
          printNumF(df,1,730,85,'.',4,' ');
          printNumF(Fs,1,730,105,'.',4,' ');
        }
        else if (pressed_button==but5){
        //delay(100);
          Cmd=Cmd+1;
          printNumF(Cmd,1,645,50,'.',4,' ');
        }
        else if (pressed_button==but6){
        //delay(100);
          Cmd=Cmd-1;
          printNumF(Cmd,1,645,50,'.',4,' ');
        }
       else if (pressed_button==but7){
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
}

//*************funcion para ver los parametros del filtro
void verparametrosfiltro(){
  setFont(SmallFont);
    setColor(VGA_YELLOW);
    setBackColorRGB(0, 0, 0); //establece color de fondo
   print("df=", 705,85, 0);
    print("Fs=", 705,105, 0);
    printNumF(df,1,730,85,'.',4,' ');
    printNumF(Fs,1,730,105,'.',4,' ');
    print("Desf=", 605,50, 0);
    printNumF(Cmd,1,645,50,'.',4,' ');
    print("Fc=", 605,30, 0);
    printNumF(Fc,1,630,30,'.',4,' ');
    print("AB=", 705,30, 0);
    printNumF(AB,1,730,30,'.',4,' ');
    print("m=", 705,50, 0);
    printNumF(m,1,725,50,'.',4,' ');
    print("Nfir=", 705,270, 0);
    printNumF(Nfir,1,745,270,'.',4,' ');
    print("F2=", 705,300, 0);
    printNumF(F2,1,735,300,'.',4,' ');
    print("F1=", 705,320, 0);
    printNumF(F1,1,735,320,'.',4,' ');
    print("Fr=", 705,350, 0);
    printNumF(Fr,1,735,350,'.',4,' ');
}


//****************calculo de los coeficiente del filtro LP
void coeficientesLP(){
  //----------------calculo de m en funcion del armonico, Fc y AB
  aum=2*Fc;
  aum=aum-(AB);
  aum=(aum/Fc);
  aum=aum*Armonico;
  m=2*Fc;
  m=m+(AB);
  m=(m/Fc);
  m=m*Armonico;
  m=m-1;
  m=aum+m;
  m=(m/2);
  //----------------calculo de Fs en funcion del m calculado anteriormente
  auFs=2*Fc;
  auFs=auFs-(AB);
  auFs=(auFs/m);
  F2=auFs;
  Fs=2*Fc;
  Fs=Fs+(AB);
  Fs=(Fs/(m+1));
  F1=Fs;
  Fs=F2+F1;
  Fs=(Fs/2);
  //----------------calculo de T de muestro en funcion de Fs calculado anteriormente
  Tret=(1000000/Fs);
  df= (N*Tret);

  //--------------calculo de F2 en funcion de Fs para el filtro pasabajos
  F2=F2/Armonico;
  auF=360*F2;
  W2=auF/Fs;

  AWventana=8*180;    //de ventana de hamming
  AWventana=AWventana/Nfir; //calculo en ancho de la ventana del filtro en funcion de la cantidad de coeficientes
  AW=AWventana;  //calculo el ancho de la ventana de transicion
  Wr=AW+W2;
  Fr=Wr*Fs;
  Fr=Fr/360;
  Fr=Fr-F2;
  L=(Nfir/2);         //desplazamiento de h[n] respuesta del filtro
  //Serial.print(Nfir);


   //************implementa el filtro fir pasabajos
      k=0;
      while(k < (Nfir+1)){
        if (k > (Nfir/2)){
          fi2=k-L;
          fi2=(fi2*W2)/180;
          if (fi2 > 15){
            sinc2 =0;
          }
          else{
            angfi2=((fi2*180)/pi);
            sinc2 = tabsinc[angfi2];
          }

        }
        else if(k == (Nfir/2)){
          fi2=0;    //para que la division no de indefinida
          //fi2=(fi2*W2)/180;
          angfi2=((fi2*180)/pi);
          sinc2 = tabsinc[angfi2];
        }
        else if(k < (Nfir/2)){
          fi2=L-k;
          fi2=(fi2*W2)/180;
          if (fi2 > 15){
            sinc2 =0;
          }
          else{
            angfi2=((fi2*180)/pi);
            sinc2 = tabsinc[angfi2];
          }
        }

        fvent=360*k;
        fvent=fvent/(Nfir-1);
        angfvent=angulo360(fvent);
        coseno1 = tabcoseno[angfvent];
        auhd2= ((W2)*(sinc2*100)); // /1000
        //auhd2=auhd2;
        auhdpb=auhd2/180;     //para el filtro pasabajos
        hdd[k]=(auhd2)/180;
        auhd2=(coseno1*0.46)/1000;
        wn[k]=(0.54-auhd2)*(100);         // w[n]
        hd[k]=(hdd[k]*wn[k])/(100);      //4.6 h[n] del filtro pasabajos

        //Serial.print(hd[k]);
       /* Serial.print("--");
        Serial.print(k);
        Serial.print("--");
        Serial.print(fi1);
        Serial.print("--");
        Serial.print(angfi1);
        Serial.print("--");
        Serial.print(sinc1);
        */
        //Serial.println(" ");
        /*
        Serial.print("--");
        Serial.print(angfi1);
        Serial.print("--");
        Serial.print(seno1);
        Serial.print("--");
        Serial.print(auhd1);
        Serial.print("--");
        Serial.print(angfi2);
        Serial.print("--");
        Serial.print(seno2);
        Serial.print("--");
        Serial.print(auhd2);
        Serial.print("----");
        Serial.print(k);
        Serial.println(" ");
        */
        k=k+1;
      }
  Tretint=((Fclock/2)*Tret);
  //REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
}

//****************calculo de los coeficiente del filtro HP
void coeficientesHP(){
  //----------------calculo de m en funcion del armonico, Fc y AB
  aum=2*Fc;
  aum=aum-(AB);
  aum=(aum/Fc);
  aum=aum*Armonico;
  m=2*Fc;
  m=m+(AB);
  m=(m/Fc);
  m=m*Armonico;
  m=m-1;
  m=aum+m;
  m=(m/2);
  //----------------calculo de Fs en funcion del m calculado anteriormente
  auFs=2*Fc;
  auFs=auFs-(AB);
  auFs=(auFs/m);
  F2=auFs;
  Fs=2*Fc;
  Fs=Fs+(AB);
  Fs=(Fs/(m+1));
  F1=Fs;
  Fs=F2+F1;
  Fs=(Fs/2);
  //----------------calculo de T de muestro en funcion de Fs calculado anteriormente
  Tret=(1000000/Fs);
  df= (N*Tret);

  //--------------calculo de F1 en funcion de Fs para el filtro pasa alto
  F1=(F1/Armonico)+4000;
  auF=360*F1;
  W1=auF/Fs;

  AWventana=8*180;    //de ventana de hamming
  AWventana=AWventana/Nfir; //calculo en ancho de la ventana del filtro en funcion de la cantidad de coeficientes
  AW=AWventana;  //calculo el ancho de la ventana de transicion
  Wr=AW+W1;
  Fr=Wr*Fs;
  Fr=Fr/360;
  Fr=Fr-F1;
  L=(Nfir/2);         //desplazamiento de h[n] respuesta del filtro
  //Serial.print(Nfir);


   //************implementa el filtro fir pasa altos
      k=0;
      while(k < (Nfir+1)){
        if (k > (Nfir/2)){
          fi1=k-L;
          fi1=(fi1*W1)/180;
          if (fi1 > 15){      //para truncar la funcion sinc por arriba de 15 radianes a 0
            sinc1 =0;
          }
          else{
            angfi1=((fi1*180)/pi);
            sinc1 = tabsinc[angfi1];
          }
         fi2=k-L;
         //fi2=fi2;
         if (fi2 > 15){      //para truncar la funcion sinc por arriba de 15 radianes a 0
            sinc2 =0;
          }
          else{
            angfi2=((fi2*180)/pi);
            sinc2 = tabsinc[angfi2];
          }
        }
        else if(k == (Nfir/2)){
          fi1=0;
          //fi1=(fi1*W1)/180;
          angfi1=((fi1*180)/pi);
          sinc1 = tabsinc[angfi1];
          fi2=0;
          angfi2=((fi2*180)/pi);
          sinc2 = tabsinc[angfi2];
        }
        else if(k < (Nfir/2)){
          fi1=L-k;
          fi1=(fi1*W1)/180;
          if (fi1 > 15){
            sinc1 =0;
          }
          else{
            angfi1=((fi1*180)/pi);
            sinc1 = tabsinc[angfi1];
          }
          fi2=L-k;
          //fi2=fi2;
         if (fi2 > 15){      //para truncar la funcion sinc por arriba de 15 radianes a 0
            sinc2 =0;
          }
          else{
            angfi2=((fi2*180)/pi);
            sinc2 = tabsinc[angfi2];
          }
        }

        fvent=360*k;
        fvent=fvent/(Nfir-1);
        angfvent=angulo360(fvent);
        coseno1 = tabcoseno[angfvent];
        auhd1= ((W1)*(sinc1*100)); // /1000
        auhd1=auhd1/180;
        hdd[k]=((sinc2*100)-auhd1);
        auhd2=(coseno1*0.46)/1000;
        wn[k]=(0.54-auhd2)*(100);         // w[n]
        hd[k]=(hdd[k]*wn[k])/(100);      //4.6 h[n] del filtro pasaaltos

       // Serial.print(hd[k]);
       /* Serial.print("--");
        Serial.print(k);
        Serial.print("--");
        Serial.print(fi1);
        Serial.print("--");
        Serial.print(angfi1);
        Serial.print("--");
        Serial.print(sinc1);
        */
       // Serial.println(" ");
        /*
        Serial.print("--");
        Serial.print(angfi1);
        Serial.print("--");
        Serial.print(seno1);
        Serial.print("--");
        Serial.print(auhd1);
        Serial.print("--");
        Serial.print(angfi2);
        Serial.print("--");
        Serial.print(seno2);
        Serial.print("--");
        Serial.print(auhd2);
        Serial.print("----");
        Serial.print(k);
        Serial.println(" ");
        */
        k=k+1;
      }
  Tretint=((Fclock/2)*Tret);
 // REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
}

//****************calculo de los coeficiente del filtro pasa banda
void coeficientesBP(){
  //----------------calculo de m en funcion del armonico, Fc y AB
  aum=2*Fc;
  aum=aum-(AB);
  aum=(aum/Fc);
  aum=aum*Armonico;
  m=2*Fc;
  m=m+(AB);
  m=(m/Fc);
  m=m*Armonico;
  m=m-1;
  m=aum+m;
  m=(m/2);
  //----------------calculo de Fs en funcion del m calculado anteriormente
  auFs=2*Fc;
  auFs=auFs-(AB);
  auFs=(auFs/m);
  F2=auFs;
  Fs=2*Fc;
  Fs=Fs+(AB);
  Fs=(Fs/(m+1));
  F1=Fs;
  Fs=F2+F1;
  Fs=(Fs/2);
  //----------------calculo de T de muestro en funcion de Fs calculado anteriormente
  Tret=(1000000/Fs);
  df= (N*Tret);

  //--------------calculo de F1 y F2 en funcion de Fs para el filtro pasabanda
  F1=F1/Armonico;
  F2=F2/Armonico;
  auF=360*F1;
  W1=auF/Fs;
  auF=360*F2;
  W2=auF/Fs;

  AWventana=8*180;    //de ventana de hamming
  AWventana=AWventana/Nfir; //calculo en ancho de la ventana del filtro en funcion de la cantidad de coeficientes
  AW=AWventana;  //calculo el ancho de la ventana de transicion
  Wr=AW+W2;
  Fr=Wr*Fs;
  Fr=Fr/360;
  Fr=Fr-F2;
  L=(Nfir/2);         //desplazamiento de h[n] respuesta del filtro
  //Serial.print(Nfir);


   //************implementa el filtro fir pasabanda
      k=0;
      while(k < (Nfir+1)){
        if (k > (Nfir/2)){
          fi1=k-L;
          fi1=(fi1*W1)/180;
          if (fi1 > 15){      //para truncar la funcion sinc por arriba de 15 radianes a 0
            sinc1 =0;
          }
          else{
            angfi1=((fi1*180)/pi);
            sinc1 = tabsinc[angfi1];
          }
          fi2=k-L;
          fi2=(fi2*W2)/180;
          if (fi2 > 15){
            sinc2 =0;
          }
          else{
            angfi2=((fi2*180)/pi);
            sinc2 = tabsinc[angfi2];
          }

        }
        else if(k == (Nfir/2)){
          fi1=0;
          //fi1=(fi1*W1)/180;
          angfi1=((fi1*180)/pi);
          sinc1 = tabsinc[angfi1];
          fi2=0;    //para que la division no de indefinida
          //fi2=(fi2*W2)/180;
          angfi2=((fi2*180)/pi);
          sinc2 = tabsinc[angfi2];
        }
        else if(k < (Nfir/2)){
          fi1=L-k;
          fi1=(fi1*W1)/180;
          if (fi1 > 15){
            sinc1 =0;
          }
          else{
            angfi1=((fi1*180)/pi);
            sinc1 = tabsinc[angfi1];
          }
          fi2=L-k;
          fi2=(fi2*W2)/180;
          if (fi2 > 15){
            sinc2 =0;
          }
          else{
            angfi2=((fi2*180)/pi);
            sinc2 = tabsinc[angfi2];
          }
        }

        fvent=360*k;
        fvent=fvent/(Nfir-1);
        angfvent=angulo360(fvent);
        coseno1 = tabcoseno[angfvent];
        auhd1= ((W1)*(sinc1*100)); // /1000
        //auhd1=auhd1;
        auhd2= ((W2)*(sinc2*100)); // /1000
        //auhd2=auhd2;
        hdd[k]=(auhd2-auhd1)/180;
        auhd2=(coseno1*0.46)/1000;
        wn[k]=(0.54-auhd2)*(100);         // w[n]
        hd[k]=(hdd[k]*wn[k])/(100);      //4.6 h[n] del filtro pasabanda

       // Serial.print(hd[k]);
       /* Serial.print("--");
        Serial.print(k);
        Serial.print("--");
        Serial.print(fi1);
        Serial.print("--");
        Serial.print(angfi1);
        Serial.print("--");
        Serial.print(sinc1);
        */
        //Serial.println(" ");
        /*
        Serial.print("--");
        Serial.print(angfi1);
        Serial.print("--");
        Serial.print(seno1);
        Serial.print("--");
        Serial.print(auhd1);
        Serial.print("--");
        Serial.print(angfi2);
        Serial.print("--");
        Serial.print(seno2);
        Serial.print("--");
        Serial.print(auhd2);
        Serial.print("----");
        Serial.print(k);
        Serial.println(" ");
        */
        k=k+1;
      }
  Tretint=((Fclock/2)*Tret);
  //REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
}

//****************calculo de los coeficiente del filtro BR
void coeficientesBR(){
  //----------------calculo de m en funcion del armonico, Fc y AB
  aum=2*Fc;
  aum=aum-(AB);
  aum=(aum/Fc);
  aum=aum*Armonico;
  m=2*Fc;
  m=m+(AB);
  m=(m/Fc);
  m=m*Armonico;
  m=m-1;
  m=aum+m;
  m=(m/2);
  //----------------calculo de Fs en funcion del m calculado anteriormente
  auFs=2*Fc;
  auFs=auFs-(AB);
  auFs=(auFs/m);
  F2=auFs;
  Fs=2*Fc;
  Fs=Fs+(AB);
  Fs=(Fs/(m+1));
  F1=Fs;
  Fs=F2+F1;
  Fs=(Fs/2);
  //----------------calculo de T de muestro en funcion de Fs calculado anteriormente
  Tret=(1000000/Fs);
  df= (N*Tret);

  //--------------calculo de F1 y F2 en funcion de Fs para el filtro pasabanda
  F1=F1/Armonico;
  F2=F2/Armonico;
  auF=360*F1;
  W1=auF/Fs;
  auF=360*F2;
  W2=auF/Fs;

  AWventana=8*180;    //de ventana de hamming
  AWventana=AWventana/Nfir; //calculo en ancho de la ventana del filtro en funcion de la cantidad de coeficientes
  AW=AWventana;  //calculo el ancho de la ventana de transicion
  Wr=AW+W2;
  Fr=Wr*Fs;
  Fr=Fr/360;
  Fr=Fr-F2;
  L=(Nfir/2);         //desplazamiento de h[n] respuesta del filtro
  //Serial.print(Nfir);


   //************implementa el filtro fir rechaza banda
      k=0;
      while(k < (Nfir+1)){
        if (k > (Nfir/2)){
          fi1=k-L;
          fi1=(fi1*W1)/180; // /180
          if (fi1 > 15){      //para truncar la funcion sinc por arriba de 15 radianes a 0
            sinc1 =0;
          }
          else{
            angfi1=((fi1*180)/pi);
            sinc1 = tabsinc[angfi1];
          }
          fi2=k-L;
          fi2=(fi2*W2)/180;
          if (fi2 > 15){
            sinc2 =0;
          }
          else{
            angfi2=((fi2*180)/pi);
            sinc2 = tabsinc[angfi2];
          }
          fifs=k-L;
        // fifs=fifs;
         if (fifs > 15){      //para truncar la funcion sinc por arriba de 15 radianes a 0
            sincfs =0;
          }
          else{
            angfifs=((fifs*180)/pi);
            sincfs = tabsinc[angfifs];
          }
        }
        else if(k == (Nfir/2)){
          fi1=0;
          angfi1=((fi1*180)/pi);
          sinc1 = tabsinc[angfi1];
          fi2=0;    //para que la division no de indefinida
          angfi2=((fi2*180)/pi);
          sinc2 = tabsinc[angfi2];
          fifs=0;    //para que la division no de indefinida
          angfifs=((fifs*180)/pi);
          sincfs = tabsinc[angfifs];
        }
        else if(k < (Nfir/2)){
          fi1=L-k;
          fi1=(fi1*W1)/180;
          if (fi1 > 15){
            sinc1 =0;
          }
          else{
            angfi1=((fi1*180)/pi);
            sinc1 = tabsinc[angfi1];
          }
          fi2=L-k;
          fi2=(fi2*W2)/180;
          if (fi2 > 15){
            sinc2 =0;
          }
          else{
            angfi2=((fi2*180)/pi);
            sinc2 = tabsinc[angfi2];
          }
          fifs=L-k;
          //fifs=fifs;
         if (fifs > 15){      //para truncar la funcion sinc por arriba de 15 radianes a 0
            sincfs =0;
          }
          else{
            angfifs=((fifs*180)/pi);
            sincfs = tabsinc[angfifs];
          }
        }

        fvent=360*k;
        fvent=fvent/(Nfir-1);
        angfvent=angulo360(fvent);
        coseno1 = tabcoseno[angfvent];
        auhd1= ((W1)*(sinc1*100)); // /1000
        //auhd1=auhd1;
        auhd2= ((W2)*(sinc2*100)); // /1000
        //auhd2=auhd2;
        hdd[k]=(sincfs*100)+((auhd1-auhd2)/180);
        auhd2=(coseno1*0.46)/1000;
        wn[k]=(0.54-auhd2)*(100);         // w[n]
        hd[k]=(hdd[k]*wn[k])/(100);      //4.6 h[n] del filtro pasabanda

        //Serial.print(hd[k]);
       /* Serial.print("--");
        Serial.print(k);
        Serial.print("--");
        Serial.print(fi1);
        Serial.print("--");
        Serial.print(angfi1);
        Serial.print("--");
        Serial.print(sinc1);
        */
       // Serial.println(" ");
        /*
        Serial.print("--");
        Serial.print(angfi1);
        Serial.print("--");
        Serial.print(seno1);
        Serial.print("--");
        Serial.print(auhd1);
        Serial.print("--");
        Serial.print(angfi2);
        Serial.print("--");
        Serial.print(seno2);
        Serial.print("--");
        Serial.print(auhd2);
        Serial.print("----");
        Serial.print(k);
        Serial.println(" ");
        */
        k=k+1;
      }
  Tretint=((Fclock/2)*Tret);
 // REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
}

//****************funcion para mostrar el menu
void menufiltro(){
 deleteAllButtons();
 clrScr(); //borra pantalla
 setColorRGB(255,0, 0); //establece el color r,g,b en el rectangulo
 drawfillRoundRect(0, 0, ResH-1, 15); //dibuja un rectangulo
 //setColorRGB(64, 64, 64);  //establece color
 setColorRGB(255, 255, 255); //establece color de fondo
 setBackColorRGB(255, 0, 0); //establece color de fondo
 setFont(SmallFont);
 print("FILTROS", CENTER,1, 0);//imprime texto en el centro
 setColorRGB(0, 0, 255);
 drawRectangulo(0, 15, ResH-1, ResV-1); //dibuja rectangulo de la pantalla

  setButtonColors(VGA_YELLOW, VGA_RED, VGA_RED, VGA_LIME, VGA_BLUE);
  but1 = addButton( 4,  25, 200,  60, "FILTROS",0);
  but2 = addButton( 210,  25, 200,  60, "LP",0);
  but3 = addButton( 210,  95, 200,  60, "HP",0);
  but4 = addButton( 210,  165, 200,  60, "BP",0);
  but5 = addButton( 210,  235, 200,  60, "BR",0);
  but6 = addButton( 210, 305, 200,  60, "VOLVER",0);
  drawButtons();
}



#endif /* FILTRO_H_ */
