/*
 *Declaracion de funciones Matematicas
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
int Fclock=84; //frecuencia de trabajo en MHZ
uint8_t Gan=8;    //ganancia para la salida de la senal de la antitransformada
double GanV;   //ganancia de voltage
int GanVdac=1000; //ganancia de voltage para el dac
int prom=1;   //contador de pasadas de calculos para sacar el promedio

int salXk[200];          //para mostrar los valores de los Xk
int sal;
int bana,kd,banaM;
int banaa;
int kds;
int kdi;
int Tvisual=3;
int iT;
int iTClear;

double Tret=6;    //periodo de muestreo en microsegundos
short Tpers=1;
short Tprom=200;
short bandver=2;	//para elegir entre mostrar los K reales o Imaginarios
int menugraf=0;     //para elegir el tipo de grafica para ver en fft


//************************Variables Osciloscopio
int desplazamiento=3;
float vpmas=2048;
float vpmenos=2048;
int bandf=0;
int periodo=0;
float Fsenial=0;
int contFs=2;
int bandtriger=0;			//para habilitar el disparo del trigger
int leveltriger=2048;	//nivel por defecto del trigger OV
int trigger=0;			//para habilitar el trigger 1

//************************Variables Analizador de Espectro
int ABmed=0;
long Fmed=0;

//++++++++++++++++++++++++Variables de filtro Fir
double m;          // para calcular la Fs
double aum;
double Fc=640000; //frecuencia central a muestrear en Hz
double AB=2000;   //ancho de banda en hz
double Armonico=5; // armonico elegido para calcular el m del submuestro y con ello la Fs
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
double auFs; //frecuencia de muestreo

//+++++++++++++++++++++++++++Variables de Demodulacion
int demo=0;
int Cmd=6;       //desfasaje de la senal Q

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

//++++++++++++++++++++++++++++Variables globales
extern TIM_HandleTypeDef htim1;
extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc1;
extern DAC_HandleTypeDef hdac;
uint16_t datostx=101;
uint16_t ADCread=0;
int valortouch;
uint16_t valorx;
uint16_t valory;
int ban = 1;
int boton;

//*********Variables de Delay_us
int bandelayus=0;			//para usar el systick como delayus (1) o para el muestreo (0)
long contdelayus=0;			//para contar el tiempo de retardo en pasos de 500nseg

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

extern void FFT_calculo(void);
extern void Mayor_Xk(uint8_t SelMXk);

extern void IFFT_calculo(void);
/*
extern void Modulacion(); //funcion para calcular las modulaciones
extern void Generador(); //funcion para calcular las funciones de senales
extern void Demodulacion(); //funcion para demodular

*/




#endif /* FUNCIONES_VARIABLES_H_ */
