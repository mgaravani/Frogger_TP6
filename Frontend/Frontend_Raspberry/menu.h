#ifndef MENU_H
#define MENU_H

// Librerías

#include <stdio.h>//Librerias estandares
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h> // Libreria para sleep
#include "disdrv.h" //librerias de control del display
#include "joydrv.h" //librerias de control del joystick 
#include "macros.h"
#include "display.h"



// Funciones
int8_t ShowMenu(void);//funcion inicial para mostrar el menu
int8_t ShowCONT(void) ;//funcion para mostrar el menu de continuar
void ShowFrogger(void);//funcion para mostrar el juego
//void Pause(void);//funcion para pausar el juego
void shiftDisplay(uint8_t display[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS], uint8_t bitmap[DISP_CANT_Y_DOTS][46], int offset);//mueve la matriz mostrada
#endif // MENU_H