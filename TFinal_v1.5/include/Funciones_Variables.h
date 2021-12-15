/*
 *Declaracion de funciones y variables
 */

#ifndef FUNCIONES_VARIABLES_H_
#define FUNCIONES_VARIABLES_H_

//+++++++++++++++++++++variables de display
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];
extern uint8_t Dingbats1_XL[];
short ResH = 800;
short ResV = 480;

//*********************Variables
int xn[1000];    //senal muestreada
int xns[1000];    //senal muestreada con signo
int xnf[1000];   //senal filtrada
int I[900];     //senal sin desfasar
int Q[900];     //senal de entrada desfasada 90
double Xam[900];    //senal demodulada de am
int Xfam[900];
int xnc[400];
int Xkr[400];   //valores de Xk reales
int Xkrp[400];  //valores promedio de Xk reales
int Xki[400];   //valores de Xk imaginarios
int Xkip[400];  //valores promedio de Xk imaginarios
int prom=1;   //contador de pasadas de calculos para sacar el promedio
int N=250;        //variable que define la cantidad de datos muestrear
short Nsal;   //variable que define la cantidad de salida de datos.
short i=0;
double df; //resolucion espectral
long Fs=1000000; //frecuencia de muestreo
double auFs; //frecuencia de muestreo
double Fc=640000; //frecuencia central a muestrear en Hz
int Fclock=84; //frecuencia de trabajo en MHZ
uint8_t Gan=8;    //ganancia para la salida de la senal de la antitransformada
double GanV;   //ganancia de voltage
int GanVdac=1000; //ganancia de voltage para el dac
uint8_t Nout;
short n;
short k;
uint8_t conD;
int aur;
int aui;
short coseno;
short seno;
short cosenoa;
short senoa;
short angulo;
short facdiv;
short w;
short valor;
int salXk[200];          //para mostrar los valores de los Xk
int sal;
int bana,kd,banaM;
int kds;
int kdi;
int banaa;
double Tret=6;    //periodo de muestreo en microsegundos
int Tvisual=3;
int iT;
int iTClear;
int Tretint;
short Tpers=1000;
short Tprom=200;
short TmenuF=9;
short bandver=2;
int menugraf=0;     //para elegir el tipo de grafica para ver en fft
double mayorr=0;
double mayori=0;
double mayorabs=0;
int dBmR = 0;
int dBmI = 0;
int dBmA = 0;
char kar=0;
char kai=0;
char kaa=0;
int Cmd=6;       //desfasaje de la senal Q
double AB=2000;   //ancho de banda en hz
double Armonico=5; // armonico elegido para calcular el m del submuestro y con ello la Fs
double m;          // para calcular la Fs
double aum;
int bandtriger=0;			//para habilitar el disparo del trigger
int leveltriger=2048;	//nivel por defecto del trigger OV

//************************Variables Osciloscopio
int desplazamiento=3;
float vpmas=2048;
float vpmenos=2048;
int bandf=0;
int periodo=0;
float Fsenial=0;

//++++++++++++++++++++++++Variables de filtro Fir
double F1;
double F2;
double auF;
double AW;
double AWventana;
int Nfir=240; //80
int auNfir;
double L;
double W1;
double W2;
double Ws;
double Wr;
double Fr;    //ancho de la banda de rechazo en Hz
double fi1;
double fi2;
double fifs;
double fvent;
int angfi1;
int angfi2;
int angfifs;
int angfvent;
int coseno1;
int seno1;
double sinc1;
int coseno2;
int seno2;
double sinc2;
double sincfs;
double auhd1;
double auhd2;
double hd[1000];
double hdd[1000];
double wn[1000];
double hdpb[1000];
double auhd;
double auhdpb;
double auxnf;
int auxnf1;
int Nruido;     //cantidad de muestras a tomar para calcular la SNR
int ausnrN;
int ausnrD;
double SNR;
double xnfd[1000];
double pi=3.141592654;

//+++++++++++++++++++++++++++Variables de Demodulacion
int demo=0;

//+++++++++++++++++++++++++++Variables de Modulacion
short port[20] = {0, 414, 516, 618, 720, 824, 720, 618, 516, 414, 0, -414, -516, -618, -720, -824, -720, -618, -516, -414};
short mod[20] = {0, 100, 150, 200, 250, 200, 150, 100, 0, -100, -150, -200, -250, -200, -150, -100};
short mod1[50] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 90, 80, 70, 60, 50, 40, 30, 20, 10, 0, -10, -20, -30, -40, -50, -60, -70, -80, -90, -100, -90, -80, -70, -60, -50, -40, -30, -20, -10 };
int bandi;
int c;
int f;
int amp;
int CC;
int volt;
long cont;
long cont1;
short sallcd[400];
int ii;
int bandint=0;
int bandintau=0;

//++++++++++++++++++++++++++Variables de interrupcion
int intvalor;

//++++++++++++++++++++++++++++Variables globales
extern TIM_HandleTypeDef htim1;
extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc1;
uint16_t datostx=101;
uint16_t ADCread=0;
int valortouch;
uint16_t valorx;
uint16_t valory;
int ban = 1;
int boton;

//++++++++++++++++++Variables de botones
int but1, but2, but3, but4, but5, but6, but7,but8,but9,but10,but11,but12,but13, butY, pressed_button;
bool default_colors = true;
int pressed_button;

//+++++++++++++++++++++++++++Definicion de funciones
extern void menu(void);

extern void entrada(); //funcion para el osciloscopio

extern void FFT(); //funcion para calcular la transformada de fourier.

extern void Filtros(); //funcion para los filtros

extern double angulo360(double);

/*
extern void Modulacion(); //funcion para calcular las modulaciones
extern void Generador(); //funcion para calcular las funciones de senales
extern void Demodulacion(); //funcion para demodular

*/




#endif /* FUNCIONES_VARIABLES_H_ */
