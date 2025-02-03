#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

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
#include "display.h"
// Aquí puedes agregar más directivas de inclusión según tus necesidades

// Declaración de funciones y clases
void move_frog_by_joystick(frog_t *frog);
void move_matrix_level(uint8_t nivel);
uint8_t calcular_velocidad(uint8_t fila, uint8_t nivel);
uint8_t playGame(uint8_t choice , frog_t *frog);
void *thread_matrix(void *arg);
void *thread_frog(void *arg); 
#endif // GAME_LOGIC_H