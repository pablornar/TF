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
void masF(void);
void menosF(void);
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
        N=30;
        clrScr(); //borra pantalla
        banaM=1;
    }
      else if (pressed_button==but2){
        //print("Button 2", 110, 220);
        clrScr(); //borra pantalla
        N=60;
        clrScr(); //borra pantalla
        banaM=1;
    }
    else if (pressed_button==but3){
        //print("Button 3", 110, 220);
        clrScr(); //borra pantalla
         N=100;
        clrScr(); //borra pantalla
        banaM=1;
    }
    else if (pressed_button==but4){
        //print("Button 4", 110, 220);
        clrScr(); //borra pantalla
         N=250;
        clrScr(); //borra pantalla
        banaM=1;
    }
    else if (pressed_button==but5){
        //print("Button 5", 110, 220);
        clrScr(); //borra pantalla
         N=350;
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
        Tret=1400;
        clrScr(); //borra pantalla
        banaM=1;
    }
      else if (pressed_button==but2){
        //print("Button 2", 110, 220);
        clrScr(); //borra pantalla
        Tret=100;
        clrScr(); //borra pantalla
        banaM=1;
    }
    else if (pressed_button==but3){
        //print("Button 3", 110, 220);
        clrScr(); //borra pantalla
         Tret=15;
        clrScr(); //borra pantalla
        banaM=1;
    }
    else if (pressed_button==but4){
        //print("Button 4", 110, 220);
        clrScr(); //borra pantalla
         Tret=6;
        clrScr(); //borra pantalla
        banaM=1;
    }
    else if (pressed_button==but5){
        //print("Button 5", 110, 220);
        clrScr(); //borra pantalla
         Tret=1;
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
w=360;
facdiv=1000;//el factor de division es por 1000
Nout=30;
Nsal=250;
bana=2;
df= (N*Tret);
df= (1000000/df);
Fs= (1000000/Tret);
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
    setColorRGB(0, 0, 255);
    drawRectangulo(0, 15, ResH-1, ResV-1); //dibuja rectangulo de la pantalla
    drawRectangulo(405, 15, ResH-1, ResV-1); //dibuja rectangulo de menu en pantalla
    drawRectangulo(405, 15, ResH-1,70); //dibuja rectangulo de menu en pantalla para f
    drawRectangulo(405, 70, ResH-1,130 ); //dibuja rectangulo de menu en pantalla para dbm

    setColor(VGA_YELLOW);
    setBackColorRGB(0, 0, 0); //establece color de fondo
    print("0 < F <", 426,30, 0);//imprime texto en el centro
    printNumF(((Nout-1)*df),1,490,30,'.',4,' ');
    print("Df=", 580,30, 0);//imprime la resolucion espectral por coeficiente de frecuencia
    printNumF(df,1,604,30,'.',4,' ');
    print("Fs=", 700,30, 0);//imprime la resolucion espectral por coeficiente de frecuencia
    printNumF(Fs,1,725,30,'.',4,' ');
    print("Gan=", 585,95, 0);//imprime la resolucion espectral por coeficiente de frecuencia
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
    printNumF(GanV,1,620,95,'.',4,' ');
    print("Dac=", 700,95, 0);//imprime la resolucion espectral por coeficiente de frecuencia
    printNumF(GanVdac,1,735,95,'.',4,' ');

    print("Xkreal=", 426,95, 0);//imprime texto en el centro
    printNumF(dBmR,0,484,95,'.',4,' '); //Para que vaya actualizando el valor
    print("k=", 540,95, 0);
    printNumI(kar,560,95,2,0);
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
    //REG_TC0_CCR0=0b00000000000000000000000000000101;    // start counter
    timer_start();
    while(bandint == 0){
    	GPIOE->ODR ^= GPIO_PIN_0;
    }
    GPIOE->ODR ^= GPIO_PIN_0;
    bandint=0;

   i=0;
   while (i != N+1){
    xn[i]= ((xn[i]*33)/4095);
    i=i+1;
    }

//*********Funcion para el calculo de los Xk
    aur=0;
    aui=0;
    k=0;
   while(k < Nout){
        valor= ((w*k)/ (N));
        angulo = valor - ((valor/360)*360); //con esto hago el angulo como maximo de 0 a 360
        cosenoa = tabcoseno[angulo];
        senoa = tabseno[angulo];
        n=0;
      while(n < ((N/2))){
        valor= (w*n*k)/ (N/2);
        angulo = valor - ((valor/360)*360); //con esto hago el angulo como maximo de 0 a 360
        coseno = tabcoseno[angulo];
        seno= tabseno[angulo];
        aur= ((((xn[2*n])+(((xn[(2*n)+1])*cosenoa)/facdiv))*coseno)/facdiv)+aur;
        aui= ((((xn[2*n])+(((xn[(2*n)+1])*senoa)/facdiv))*seno)/facdiv)+aui;
        n=n+1;
      }
      Xkr[k]=(aur);
      Xki[k]=(aui);
      aur=0;
      aui=0;
      k=k+1;
   }

//****calculo de la antitransformada de fourier para Nsas valores con Nout valores de Xk
    /*
    aur=0;
    n=0;
    facdiv=100;
    Nsal=250;
    REG_DACC_MR = (REG_DACC_MR & 0b11111111111111001111111111111111) | 0b00000000000000010000000000000000;//dac user sel en canal 1
    REG_DACC_CHER=0b0000000000000000000000000000010;
    while(n < Nsal){
      aur=((1000*(Xkr[0]))/facdiv); //es el calculo para k=0 es la componente de continua
      k=1; //0
      while(k < Nout){
        valor= (w*n*k)/ (Nout);
        angulo = valor - ((valor/360)*360); //con esto hago el angulo como maximo de 0 a 360
        coseno = tabcoseno[angulo];
        seno= tabseno[angulo];
        aur= (((coseno *((Xkr[k])))/facdiv)*Gan) +aur; //amplifico todo por 5 menos la componente de continua
        k=k+1;
      }
        xnc[n]=aur/(Nout);
        aur=0;

        while ((REG_DACC_ISR & 0b00000000000000000000000000000001)== 0); //espera que el registro este disponible para una conversion
        REG_DACC_CDR = (xnc[n]);//escribe el DAC con el valor del registro pwm
        //Serial.println(xnc[n]);
        n=n+1;
        delayMicroseconds(Tret);
   }
 facdiv=1000;
   */

   /*****************para mostrar los k****/
   k=0;
   mayorr=0;
   mayori=0;
   mayorabs=0;
   if(prom==1){
    while (k != Nout){
      if (bandver==0){
        Xkrp[k]= (abs(Xkr[k]));
        if ((Xkrp[k]>mayorr) && (k>1)){
          mayorr = Xkrp[k];
          kar=k;
          dBmR = mayorr;
        }
      }
      else if (bandver==1){
        Xkrp[k]= (abs(Xki[k]));
        if ((Xkrp[k]>mayori) && (k>1)){
          mayori = Xkrp[k];
          kai=k;
          dBmI = mayori;
         }
      }
      else if (bandver==2){
        Xkrp[k]=(sqrt((Xkr[k]*Xkr[k])+(Xki[k]*Xki[k])));
      //  Xkrp[k]=abs(Xkrp[k]);
        if ((Xkrp[k]>mayorabs) && (k>1)){
          mayorabs = Xkrp[k];
          kaa=k;
          dBmA = mayorabs;
           }
          }
         k=k+1;
    }
    setColor(VGA_YELLOW);
    setBackColorRGB(0, 0, 0); //establece color de fondo
    print("Xkreal=", 426,95, 0);//imprime texto en el centro
    printNumF(dBmR,0,484,95,'.',4,' '); //Para que vaya actualizando el valor
    print("k=", 540,95, 0);
    printNumI(kaa,560,95,2,0);
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
    if (prom > Tprom){   //ESTO LE DA LA SUAVIDAD EN LA CURVA DE SALIDA (SERIA EL FILTRO)
      prom=1;
    }

  k=0;
  kd=4;
  while (k < Nout){
    salXk[k]=(((Xkrp[k])));
    if (salXk[k] > 400){//222
      salXk[k]=400;  //222
    }
    else if(salXk[k]<17){
      salXk[k]=1;
    }

    if(menugraf == 0){
      setColorRGB(0, 0, 0);                           //para borrar los puntos
      if(k == Nout-1){
        drawLine(((4)), 470, ((4)), 16);
        drawLine(((4+1)), 470, ((4+1)),16);
        drawLine(((4+2)), 470, ((4+2)), 16);
        drawLine(((4+3)), 470, ((4+3)),16);
        drawLine(((4+4)), 470, ((4+4)), 16);
        drawLine(((4+5)), 470, ((4+5)),16);
        drawLine(((4+6)), 470, ((4+6)), 16);
        drawLine(((4+7)), 470, ((4+7)),16);
        drawLine(((4+8)), 470, ((4+8)), 16);
        drawLine(((4+9)), 470, ((4+9)),16);
        drawLine(((4+10)), 470, ((4+10)), 16);
        drawLine(((4+11)), 470, ((4+11)),16);
        //drawLine(((4+12)), 470, ((4+12)), 16);
      }
      else{
        drawLine(((kd)+12), 470, ((kd)+12), 16);
        drawLine(((kd+1)+12), 470, ((kd+1)+12),16);
        drawLine(((kd+2)+12), 470, ((kd+2)+12), 16);
        drawLine(((kd+3)+12), 470, ((kd+3)+12),16);
        drawLine(((kd+4)+12), 470, ((kd+4)+12), 16);
        drawLine(((kd+5)+12), 470, ((kd+5)+12),16);
        drawLine(((kd+6)+12), 470, ((kd+6)+12), 16);
        drawLine(((kd+7)+12), 470, ((kd+7)+12),16);
        drawLine(((kd+8)+12), 470, ((kd+8)+12), 16);
        drawLine(((kd+9)+12), 470, ((kd+9)+12),16);
        drawLine(((kd+10)+12), 470, ((kd+10)+12), 16);
        drawLine(((kd+11)+12), 470, ((kd+11)+12),16);
        //drawLine(((kd+12)+12), 470, ((kd+12)+12), 16);
      }

      setColorRGB(0, 255, 255);
      drawLine((kd), 470, (kd), 470-salXk[k]);
      drawLine((kd+1),470, (kd+1), 470-salXk[k]);
      drawLine((kd+2),470, (kd+2), 470-salXk[k]);
      HAL_Delay(Tpers);
      //delayMicroseconds(Tpers); //ESTE DELAY LE DA LA PERSISTENCIA
      k=k+1;
      kd=kd+12;
    }
    else if(menugraf == 1){
      setColorRGB(0, 0, 0);                           //para borrar los puntos
      if(k == Nout-1){
        drawLine(((4)), 470, ((4)), 16);
        drawLine(((4+1)), 470, ((4+1)),16);
        drawLine(((4+2)), 470, ((4+2)), 16);
        drawLine(((4+3)), 470, ((4+3)),16);
        drawLine(((4+4)), 470, ((4+4)), 16);
        drawLine(((4+5)), 470, ((4+5)),16);
        drawLine(((4+6)), 470, ((4+6)), 16);
        drawLine(((4+7)), 470, ((4+7)),16);
        drawLine(((4+8)), 470, ((4+8)), 16);
        drawLine(((4+9)), 470, ((4+9)),16);
        drawLine(((4+10)), 470, ((4+10)), 16);
        drawLine(((4+11)), 470, ((4+11)),16);
        //drawLine(((4+12)), 470, ((4+12)), 16);
      }
      else{
        drawLine(((kd)+12), 470, ((kd)+12), 16);
        drawLine(((kd+1)+12), 470, ((kd+1)+12),16);
        drawLine(((kd+2)+12), 470, ((kd+2)+12), 16);
        drawLine(((kd+3)+12), 470, ((kd+3)+12),16);
        drawLine(((kd+4)+12), 470, ((kd+4)+12), 16);
        drawLine(((kd+5)+12), 470, ((kd+5)+12),16);
        drawLine(((kd+6)+12), 470, ((kd+6)+12), 16);
        drawLine(((kd+7)+12), 470, ((kd+7)+12),16);
        drawLine(((kd+8)+12), 470, ((kd+8)+12), 16);
        drawLine(((kd+9)+12), 470, ((kd+9)+12),16);
        drawLine(((kd+10)+12), 470, ((kd+10)+12), 16);
        drawLine(((kd+11)+12), 470, ((kd+11)+12),16);
        //drawLine(((kd+12)+12), 470, ((kd+12)+12), 16);
      }

      setColorRGB(0, 255, 255);
      if (k==0){
        drawLine((kd), 470-salXk[k], (kd+2), 470-salXk[k]);
      }
      else{
        drawLine((kd-10), 470-salXk[k-1], (kd+2), 470-salXk[k]);
      }
      HAL_Delay(Tpers); //ESTE DELAY LE DA LA PERSISTENCIA
      k=k+1;
      kd=kd+12;
    }

    if (dataAvailable() == true){ //para preguntar si se presiono un boton
    	HAL_Delay(200);
    	pressed_button = checkButtons();
          setColor(VGA_YELLOW);
          setBackColorRGB(0, 0, 0); //establece color de fondo
      if (pressed_button==but1){  //Xkr
        bandver=0;
        print("Xkreal=", 426,95, 0);//imprime texto en el centro
              //dBmfun();
        printNumF(dBmR,0,484,95,'.',4,' '); //Para que vaya actualizando el valor
        print("k=", 540,95, 0);
        printNumI(kar,560,95,2,0);
       }
      else if (pressed_button==but2){ //Xki
        bandver=1;
        print("Xkimag=", 426,95, 0);//imprime texto en el centro
              //dBmfun();
        printNumF(dBmI,0,484,95,'.',4,' ');
      }
      else if (pressed_button==but3){
        bandver=2;
        print("Xkpro=", 426,95, 0);//imprime texto en el centro
              //dBmfun();
        printNumF(dBmA,0,484,95,'.',4,' ');
      }
      else if (pressed_button==but4){
          masF();
          df= (N*Tret);
          df= (1000000/df);
          Fs= (1000000/Tret);
          printNumF(df,1,604,30,'.',4,' ');
          printNumF(Fs,1,725,30,'.',4,' ');
          printNumF(((Nout-1)*df),1,490,30,'.',4,' ');
       }
      else if (pressed_button==but5){
          menosF();
          df= (N*Tret);
          df= (1000000/df);
          Fs= (1000000/Tret);
          printNumF(df,1,604,30,'.',4,' ');
          printNumF(Fs,1,725,30,'.',4,' ');
          printNumF(((Nout-1)*df),1,490,30,'.',4,' ');
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
          printNumF(GanV,1,620,95,'.',4,' ');
          printNumF(GanVdac,1,735,95,'.',4,' ');

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
          printNumF(GanV,1,620,95,'.',4,' ');
          printNumF(GanVdac,1,735,95,'.',4,' ');
          /*
          REG_DACC_MR = (REG_DACC_MR & 0b11111111111111001111111111111111) | 0b00000000000000000000000000000000; //dac user sel canal 0
          REG_DACC_CHER=0b0000000000000000000000000000001;
          while ((REG_DACC_ISR & 0b00000000000000000000000000000001)== 0); //espera que el registro este disponible para una conversion
          REG_DACC_CDR = (GanVdac);//escribe el DAC con el valor del registro pwm
          */

       }
      else if (pressed_button==but9){ //Zoom-
          Tret=Tret-0.1;
          Tretint=((Fclock/2)*Tret);
          //REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          df= (N*Tret);
          df= (1000000/df);
          Fs= (1000000/Tret);
          printNumF(df,1,604,30,'.',4,' ');
          printNumF(Fs,1,725,30,'.',4,' ');
          printNumF(((Nout-1)*df),1,490,30,'.',4,' ');
       }
      else if (pressed_button==but12){ //Zoom+
          Tret=Tret+0.1;
          Tretint=((Fclock/2)*Tret);
          //REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          df= (N*Tret);
          df= (1000000/df);
          Fs= (1000000/Tret);
          printNumF(df,1,604,30,'.',4,' ');
          printNumF(Fs,1,725,30,'.',4,' ');
          printNumF(((Nout-1)*df),1,490,30,'.',4,' ');
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


//****************************************funcion para incremetar la frecuencia
void masF(){
  TmenuF=TmenuF+1;
          if (TmenuF==1){
            Tret=1400;
            Tretint=((Fclock/2)*Tret);
           // REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          }
          else if (TmenuF==2){
            Tret=300;
            Tretint=((Fclock/2)*Tret);
           // REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          }
          else if (TmenuF==3){
            Tret=100;
            Tretint=((Fclock/2)*Tret);
           // REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          }
          else if (TmenuF==4){
            Tret=30;
            Tretint=((Fclock/2)*Tret);
           // REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          }
          else if (TmenuF==5){
            Tret=15;
            Tretint=((Fclock/2)*Tret);
           // REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          }
          else if (TmenuF==6){
            Tret=9;
            Tretint=((Fclock/2)*Tret);
           // REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          }
          else if (TmenuF==7){
            Tret=8;
            Tretint=((Fclock/2)*Tret);
           // REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          }
          else if (TmenuF==8){
            Tret=7;
            Tretint=((Fclock/2)*Tret);
           // REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          }
          else if (TmenuF==9){
            Tret=6;
            Tretint=((Fclock/2)*Tret);
           // REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          }
          else if (TmenuF==10){
            Tret=5;
            Tretint=((Fclock/2)*Tret);
            //REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          }
          else if (TmenuF==11){
            Tret=4;
            Tretint=((Fclock/2)*Tret);
            //REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          }
          else if (TmenuF==12){
            Tret=3;
            Tretint=((Fclock/2)*Tret);
           // REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          }
           else if (TmenuF==13){
            Tret=2;
            Tretint=((Fclock/2)*Tret);
           // REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          }
           else if (TmenuF >= 14){
            TmenuF=14;
            Tret=1;
            Tretint=((Fclock/2)*Tret);
           // REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          }
}

//funcion para decrementar la frecuencia
void menosF(){
  TmenuF=TmenuF-1;
          if (TmenuF <= 1){
            TmenuF=1;
            Tret=1400;
            Tretint=((Fclock/2)*Tret);
            //REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          }
          else if (TmenuF==2){
            Tret=300;
            Tretint=((Fclock/2)*Tret);
          //  REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          }
          else if (TmenuF==3){
            Tret=100;
            Tretint=((Fclock/2)*Tret);
           // REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          }
          else if (TmenuF==4){
            Tret=30;
            Tretint=((Fclock/2)*Tret);
           // REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          }
          else if (TmenuF==5){
            Tret=15;
            Tretint=((Fclock/2)*Tret);
            //REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          }
          else if (TmenuF==6){
            Tret=9;
            Tretint=((Fclock/2)*Tret);
            //REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          }
          else if (TmenuF==7){
            Tret=8;
            Tretint=((Fclock/2)*Tret);
            //REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          }
          else if (TmenuF==8){
            Tret=7;
            Tretint=((Fclock/2)*Tret);
            //REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          }
          else if (TmenuF==9){
            Tret=6;
            Tretint=((Fclock/2)*Tret);
           // REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          }
          else if (TmenuF==10){
            Tret=5;
            Tretint=((Fclock/2)*Tret);
            //REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          }
          else if (TmenuF==11){
            Tret=4;
            Tretint=((Fclock/2)*Tret);
           // REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          }
          else if (TmenuF==12){
            Tret=3;
            Tretint=((Fclock/2)*Tret);
            //REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          }
           else if (TmenuF==13){
            Tret=2;
            Tretint=((Fclock/2)*Tret);
            //REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
          }
           else if (TmenuF==14){
            Tret=1;
            Tretint=((Fclock/2)*Tret);
           // REG_TC0_RC0=(Tretint);  //carga el registro A con el valor a comparar
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
    but1 = addButton( 205,  25, 200,  60, "0<F<109hz",0);
    but2 = addButton( 205,  90, 200,  60, "0<F<1,5Khz",0);
    but3 = addButton( 205, 155, 200,  60, "0<F<9,8Khz",0);
    but4 = addButton( 205, 220, 200,  60, "0<F<23Khz",0);
    but5 = addButton( 205, 285, 200,  60, "0<F<95Khz",0);
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
    but1 = addButton( 205,  25, 200,  60, "N = 30",0);
    but2 = addButton( 205, 90, 200,  60, "N = 60",0);
    but3 = addButton( 205, 155, 200,  60, "N = 100",0);
    but4 = addButton( 205, 220, 200,  60, "N = 250",0);
    but5 = addButton( 205, 285, 200,  60, "N = 350",0);
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
