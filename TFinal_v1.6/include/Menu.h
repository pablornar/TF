/*
 * Menu del lcd
 */
#ifndef MENU_H_
#define MENU_H_

void displaymenu(void);

void menu(){
  displaymenu(); //funcion para inicializar el display

  while(ban==1)
  {

    if (dataAvailable() == true)
    {
    	HAL_Delay(200);
      pressed_button = checkButtons();

      if (pressed_button == but1){
        //myGLCD.print("Button 1", 110, 220);
        HAL_Delay(100);
        entrada();
        ban=1;
        clrScr(); //borra pantalla
        displaymenu();

    }
      else if (pressed_button == but2){
        //myGLCD.print("Button 2", 110, 220);
    	HAL_Delay(100);
        FFT();
        ban=1;
        clrScr(); //borra pantalla
        displaymenu();
    }
      else if (pressed_button == but3){
        //myGLCD.print("Button 3", 110, 220);
    	  HAL_Delay(100);
       // Generador();
        ban=1;
        clrScr();
        displaymenu();

     }
      else if (pressed_button == but4){
        //myGLCD.print("Button 4", 110, 220);
    	  HAL_Delay(100);
       // Modulacion();
        ban=1;
        clrScr();
        displaymenu();

     }
       else if (pressed_button == but5){
        //myGLCD.print("Button 5", 110, 220);
    	   HAL_Delay(100);
       // Demodulacion();
        ban=1;
        clrScr(); //borra pantalla
        displaymenu();

       }
       else if (pressed_button == but6){
        //myGLCD.print("Button 5", 110, 220);
    	   HAL_Delay(100);
        Filtros();
        ban=1;
        clrScr(); //borra pantalla
        displaymenu();

       }
       else if (pressed_button == -1){
        //myGLCD.print("None    ", 110, 220);
       }
    }
  }


}

void displaymenu(){
  deleteAllButtons();		//borra los botones que pudieren quedar
  setColor(VGA_RED); //establece el color r,g,b en el rectangulo
  drawfillRoundRect(0, 0, ResH-1, 17); //dibuja un rectangulo
  //myGLCD.setColor(64, 64, 64);  //establece color
  setBackColor(VGA_RED); //establece color de fondo
  setColor(VGA_AQUA); //establece color de LETRAS
  setFont(BigFont);
  printRLC("ANALIZADOR DE B.F.", CENTER,1, 0);//imprime texto en el centro
  setColorRGB(0, 0, 255);
  drawRoundRect(0, 18, ResH-1, ResV-1); //dibuja rectangulo de la pantalla
  drawRoundRect(0, 0, ResH-1, 17);

  setButtonColors(VGA_SILVER, VGA_RED, VGA_RED, VGA_LIME, VGA_BLUE);
  but1 = addButton(50,50, 200,  100, "OSCILOSCOPIO",0);
  but2 = addButton(300,50, 200,  100, "FFT",0);
  but3 = addButton(550,50, 200,  100, "GENERADOR",0);
  but4 = addButton(50,200, 200,  100, "MODULACION",0);
  but5 = addButton(300,200, 200,  100, "DEMODULACION",0);
  but6 = addButton(550,200, 200,  100, "FILTROS",0);
  //but4 = myButtons.addButton( 10, 140, 300,  30, "AntiTransformada", BUTTON_DISABLED);
  //butX = myButtons.addButton(279, 199,  40,  40, "a", BUTTON_SYMBOL);
  //butY = myButtons.addButton(  0, 199, 100,  40, "I", BUTTON_SYMBOL | BUTTON_SYMBOL_REP_3X);
  drawButtons();
}




#endif /* MENU_H_ */
