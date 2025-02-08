#ifndef DISPLAY_H
#define DISPLAY_H


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h> // Libreria para sleep

//Backend
#include "../../Backend/frog.h"
#include "../../Backend/topScore.h"
#include "../../Backend/map.h"
#include "../../Backend/delay.h"
extern map_t map;
//Frontend
#include "disdrv.h"
#include "joydrv.h"
#include "macros.h"

//funciones

void recortar_matriz(uint8_t matriz_recortada[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS]);
void mostrar_matriz(uint8_t matriz[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS]);
void screen_raspy(frog_t *frog_position, uint8_t matriz[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS]);

#endif // DISPLAY_H