#ifndef MENU_H
#define MENU_H

// Librerías

#include <stdio.h>//Librerias estandares
#include <stdlib.h>
#include <stdint.h>
#include "disdrv.h" //librerias de control del display
#include "joydrv.h" //librerias de control del joystick 
#include "macros.h"


// Funciones
int8_t ShowMenu(void);//funcion inicial para mostrar el menu
void ShowFrogger(void);//funcion para mostrar el juego
void Pause(void);//funcion para pausar el juego
#endif // MENU_H