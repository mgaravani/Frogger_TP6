#ifndef DELAY_H
#define DELAY_H
#include <stdint.h>
#include <time.h>

/*------Funcion waiting_time------*/
/*
    @brief  Funcion para controlar el tiempo entre los desplazamientos de los objetos

    @param  Nivel actual y la fila a controlar

    TESTEADA
*/
int8_t waiting_time (int8_t nivel, int8_t fila);

#endif