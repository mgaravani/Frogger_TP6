#ifndef DISPLAY_H
#define DISPLAY_H


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//Backend
#include "../../Backend/frog.h"
#include "../../Backend/highscores.h"
#include "../../Backend/map.h"
#include "../../Backend/delay.h"
extern map_t map;
//Frontend
#include "disdrv.h"
#include "joydrv.h"
#include "macros.h"

//funciones

void mostrar_matriz(uint8_t matriz[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS]);
void generar_matriz(uint8_t  matriz[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS]);
void desplazar_fila(uint8_t matriz[ROWS_ORIGINAL][COLS_ORIGINAL], uint8_t fila, uint8_t direccion, uint8_t velocidad);
void recortar_matriz(uint8_t matriz_original[ROWS_ORIGINAL][COLS_ORIGINAL], uint8_t matriz_recortada[DISP_CANT_Y_DOTS][16]);
#endif // DISPLAY_H