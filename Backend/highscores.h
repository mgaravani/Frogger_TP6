#ifndef HIGHSCORES_H
#define HIGHSCORES_H

/*------------INCLUDES-----------*/
#include <stdint.h>
#include <stdio.h>

/*----------PROTOTYPES----------*/

/*-----highscores-----*/
// Función para manejar los puntajes altos
FILE* highscores(uint32_t newscore, char *name);

#endif /* HIGHSCORES_H */