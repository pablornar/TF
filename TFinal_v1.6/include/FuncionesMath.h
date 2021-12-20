/*
 *Funciones matematicas
 */

#ifndef FUNCIONESMATH_H_
#define FUNCIONESMATH_H_

/*
 * prototipos de funciones
 */
double angulo360(double ang);
void FFT_calculo(void);
void IFFT_calculo(void);
void Mayor_Xk(uint8_t SelMXk);

/*
 * Funciones implementadas
 */

//********Dado un angulo superior a 360 lo convierte en su equivalente de 0 a 360
double angulo360(double ang){
  int n;
  int bandang;
  n=1;
  bandang=1;
  while (bandang==1){
    if(ang > ((360*n))){
      n=n+1;
    }
    else if(ang <= 360){
      bandang=0;
    }
    else{
      ang=ang-((360*(n-1)));
      bandang=0;
    }
  }
  return ang;
}


/*
 * Funcion para calcular los coeficientes de la FFT con datos de entrada de un vector de N muestras
 */
void FFT_calculo(void){
	w= 360;		//360
	facdiv=1000;//el factor de division es por 1000
	Nout=60;	//cantidad de coeficientes de la FFT a calcular
	Nsal=250;
	df= (Fs/N);

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
}

/*
 * Funcion para calcular Nsal valores de la IFFT con datos de entrada de los vectores de coeficientes de la FFT
 */
void IFFT_calculo(void){
	    aur=0;
	    n=0;
	    facdiv=100;
	    Nsal=250;
	    //REG_DACC_MR = (REG_DACC_MR & 0b11111111111111001111111111111111) | 0b00000000000000010000000000000000;//dac user sel en canal 1
	    //REG_DACC_CHER=0b0000000000000000000000000000010;
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

	        //while ((REG_DACC_ISR & 0b00000000000000000000000000000001)== 0); //espera que el registro este disponible para una conversion
	        //REG_DACC_CDR = (xnc[n]);//escribe el DAC con el valor del registro pwm
	        //Serial.println(xnc[n]);
	        n=n+1;
	        delay_us(Tret);
	   }
	 facdiv=1000;
}

/*
 * Funcion para calcular el mayor de los Coefientes de la FFT
 * 0 Coeficientes Reales
 * 1 Coeficientes Imaginarios
 * 2 Coeficientes del modulo
 */
void Mayor_Xk(uint8_t SelMXk){
	/*****************para mostrar los k****/
	   k=0;
	   mayorr=0;
	   mayori=0;
	   mayorabs=0;

	    while (k != Nout){
	      if (SelMXk==0){
	        Xkrp[k]= (abs(Xkr[k]));
	        if ((Xkrp[k]>mayorr) && (k>1)){
	          mayorr = Xkrp[k];
	          kar=k;
	          dBmR = mayorr;
	        }
	      }
	      else if (SelMXk==1){
	        Xkrp[k]= (abs(Xki[k]));
	        if ((Xkrp[k]>mayori) && (k>1)){
	          mayori = Xkrp[k];
	          kai=k;
	          dBmI = mayori;
	         }
	      }
	      else if (SelMXk==2){
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
}

#endif /* FUNCIONESMATH_H_ */
