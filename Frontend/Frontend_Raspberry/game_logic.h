#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

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
// Aquí puedes agregar más directivas de inclusión según tus necesidades

// Declaración de funciones y clases
void *frog_thread(void *arg);
#endif // GAME_LOGIC_H