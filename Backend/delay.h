#ifndef DELAY_H
#define DELAY_H

/*------------INCLUDES-----------*/
#include <stdint.h>
#include <time.h>

/*------Funcion waiting_time------*/
/*
    @brief  Funcion para controlar el tiempo entre los desplazamientos de los objetos

    @param  Nivel actual y la fila a controlar

    TESTEADA
*/

/*-----------PROTOTYPES--------*/

/*------Function waiting_time------*/
// Funcion para controlar el tiempo entre los desplazamientos de los objetos
uint8_t waiting_time (uint8_t nivel, uint8_t fila);

#endif