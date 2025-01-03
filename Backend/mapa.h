#ifndef MAPA_H
#define MAPA_H
#include <stdint.h>

#define FILAS 16
#define COLUMNAS 18
typedef int8_t mapa_t[FILAS][COLUMNAS];

void imprimir_matriz();
void inicializar_matriz();

/*------Funcion shift_row------*/
/*
    @brief  Funcion para pasar desplazar las filas de la matriz de juego (Derecha e izquierda)

    @param  Fila a desplazar y dirección (derecha 1 e izquierda 0)

    TESTEADA
*/
void shift_row(int8_t row, int8_t direction);

#endif