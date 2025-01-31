#ifndef RASPBERRY_H
#define RASBERRY_H

#include "functions.h"
#include "arrays.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../../Backend/frog.h"
#include "../../Backend/highscores.h"
#include "../../Backend/map.h"
#include "../../Backend/delay.h"

extern map_t map;


#define THRESHOLD 40
#define THRESHOLD_OFF 10
    
void handleJoystickInput(int *choice);
int playGame(int choice);
void ShowFrogger();
int8_t ShowMenu();
void initializeFroggerBitmap(uint8_t bitmap[DISP_CANT_Y_DOTS][46]);//inicializa la matriz inicial de mostrar el juego
void shiftDisplay(uint8_t display[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS], uint8_t bitmap[DISP_CANT_Y_DOTS][46], int offset);//mueve la matriz mostrada
void *matrix_thread(void *arg);
void *frog_thread(void *arg);
#endif