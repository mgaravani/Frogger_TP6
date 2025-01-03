#ifndef MAPA_H
#define MAPA_H
#include <stdint.h>

#define ROWS 13
#define COLUMNS 15
typedef int8_t map_t[ROWS][COLUMNS];


void print_matrix(); // BORRAR DESPUES DE NO USAR MAS (FUN PARA TESTEAT LA MAT)

/*------Funcion initialize_matrix------*/
/*
    @brief  Función para inicializar la matriz de juego con spawn aleatorio de ciertos obstáculos y de su largo (troncos, autos, camiones, etc.)

    @param  Fila a desplazar y dirección (derecha 1 e izquierda 0)

    TESTEADA
*/
void initialize_matrix();

/*------Funcion shift_row------*/
/*
    @brief  Funcion para pasar desplazar las filas de la matriz de juego (Derecha e izquierda)

    @param  Fila a desplazar y dirección (derecha 1 e izquierda 0)

    TESTEADA
*/
void shift_row(int8_t row, int8_t direction);

#endif