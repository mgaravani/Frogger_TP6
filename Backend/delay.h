#ifndef DELAY_H
#define DELAY_H

/*------------INCLUDES-----------*/
#include <stdint.h>
#include <time.h>

/*------Function waiting_time------*/
// Funcion para controlar el tiempo entre los desplazamientos de los objetos
uint8_t waiting_time (uint8_t nivel, uint8_t fila);

#endif // DELAY_H