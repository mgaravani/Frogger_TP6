#ifndef MAPA_H
#define MAPA_H

/*-----------INCLUDES--------*/
#include <stdint.h>

/*-----------DEFINES--------*/
#define ROWS 13
#define COLUMNS 20

/*-----------TYPEDEF--------*/
typedef uint8_t map_t[ROWS][COLUMNS];
/*------------ GLOBAL VARIABLE ----------------*/
extern map_t map;

/*-----------PROTOTYPES--------*/

/*------Function print_matrix------*/
// Función usada para debugear durante el desarrollo
void print_matrix(void);

/*------Funcion initialize_matrix------*/
// Función para inicializar la matriz de juego con spawn aleatorio de ciertos obstáculos y de su largo (troncos, autos, camiones, etc.)
void initialize_matrix(void);

/*------Funcion shift_row------*/
// Funcion para pasar desplazar las filas de la matriz de juego (Derecha e izquierda)
// Dirección (1 para derecha y 0 izquierda)
void shift_row(uint8_t row, uint8_t direction);


/*------Funcion set_map_ToZero------*/
// Setea toda la matriz en 0
void set_map_ToZero(void);

#endif