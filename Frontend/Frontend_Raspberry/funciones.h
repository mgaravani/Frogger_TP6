
#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>//Librerias estandares
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "./disdrv.h" //librerias de control del display
#include "./joydrv.h" //librerias de control del display
#define DISP_CANT_X_DOTS 16
#define DISP_CANT_Y_DOTS 16
#define SAPO_SIZE 1
#define THRESHOLD 40
//Funciones
//mueve la matriz sapo en la matriz grande
void moveMatrix(uint8_t target[DISP_CANT_X_DOTS][DISP_CANT_Y_DOTS], uint8_t source[SAPO_SIZE][SAPO_SIZE], int startRow, int startCol);
void mostrar_matriz(uint8_t matriz[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS]);
void generar_matriz(uint8_t  matriz[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS]);

#endif 
