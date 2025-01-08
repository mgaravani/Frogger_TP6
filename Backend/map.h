#ifndef MAPA_H
#define MAPA_H

/*-----------INCLUDES--------*/
#include <stdint.h>

/*-----------DEFINES--------*/
#define ROWS 13
#define COLUMNS 20

/*-----------TYPEDEF--------*/
typedef uint8_t map_t[ROWS][COLUMNS];

/*-----------PROTOTYPES--------*/

/*------Function print_matrix------*/
void print_matrix(); // BORRAR DESPUES DE NO USAR MAS (FUN PARA TESTEAT LA MAT)

/*------Funcion initialize_matrix------*/
/*
    @brief  Función para inicializar la matriz de juego con spawn aleatorio de ciertos obstáculos y de su largo (troncos, autos, camiones, etc.)

    @param  Fila a desplazar y dirección (derecha 1 e izquierda 0)

    TESTEADA
*/

/*------Function initialize_matrix*/
void initialize_matrix();

/*------Funcion shift_row------*/
/*
    @brief  Funcion para pasar desplazar las filas de la matriz de juego (Derecha e izquierda)

    @param  Fila a desplazar y dirección (derecha 1 e izquierda 0)

    TESTEADA
*/
void shift_row(uint8_t row, uint8_t direction);

#endif