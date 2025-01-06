#ifndef FROG_H
#define FROG_H
#include <stdint.h>

typedef struct 
{  
    int8_t x;           // coordenada x de la rana
    int8_t y;           // coordenada y de la rana
    uint8_t vidas;      // Cantidad de vidas
    int16_t puntos;     // Puntos acumulados por el jugador
    int8_t llegadas;    // Cantidad de veces que el jugador llego al final
}frog_t;

#endif