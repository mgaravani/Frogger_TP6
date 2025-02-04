#ifndef RASPBERRY_H
#define RASBERRY_H
//librerias estandares  
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Libreria para sleep
//librerias de Frontend


#include "arrays.h"
#include "menu.h"
#include "macros.h"
#include "display.h"
#include "game_logic.h"
#include "disdrv.h"
#include "joydrv.h"

//librerias de Backend
#include "../../Backend/frog.h"
#include "../../Backend/topScore.h"
#include "../../Backend/map.h"
#include "../../Backend/delay.h"

extern map_t map;

#endif