#ifndef MAIN_H
#define MAIN_H

/*------------INCLUDES-----------*/
#include "../Backend/frog.h"
#include "../Backend/map.h"
#include "../Backend/topScore.h"
#include "../Backend/delay.h"
#include <stdio.h>
#include <unistd.h>

/*------------DEFINES-----------*/

  #ifdef RASPBERRY_PI
    // Definiciones para Raspberry
    #include "../Frontend/Frontend_Raspberry/raspberry.h"
    #endif

  #ifdef PC
    // Definiciones para PC
    #include "../Frontend/Frontend_Allegro/allegro.h"
  #endif 
/*------------Macros-----------*/

#endif // MAIN_H