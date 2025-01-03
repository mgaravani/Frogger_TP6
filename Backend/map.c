/*------------INCLUDES-----------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"

/*------------ GLOBAL VARIABLE ----------------*/
map_t map;

/*------------ FUNCTIONS ----------------*/

/*------Funcion initialize_matrix------*/
void initialize_matrix() {
    srand(time(NULL));
    
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (i == 6 || i == 12 || j == 0 || j == 14) { // Filas y columnas específicas llenas de ceros
                map[i][j] = 0;
            }
            else if (i == 0){ // Fila 0 (fila de llegada) es fija.
                if (j == 1 || j == 4 || j == 7 || j == 10 || j == 13){ // Posiciones de posible llegada (objetivos).
                    map[i][j] = 1;
                }
                else { // Posiciones sin llegada (pared).
                    map[i][j] = 0;
                }
            } 
            else if (i >= 1 && i <= 5) { // Filas entre la 1 y la 5
                if (j == 0 || map[i][j - 1] == 0) { 
                    // Genera grupos de 2 a 4 unos seguidos
                    int num_ones = rand() % 3 + 2; // Tamaño del grupo: 2 a 4 unos
                    int remaining_space = COLUMNS - j; // Espacios disponibles en la fila

                    if (num_ones > remaining_space - 1) {
                        // Si no hay espacio suficiente para el grupo, rellenar con ceros
                        while (j < COLUMNS) {
                            map[i][j++] = 0;
                        }
                        break;
                    }

                    int ones_added = 0;
                    while (ones_added < num_ones && j < COLUMNS - 1) { 
                        // Generar grupo de unos
                        map[i][j++] = 1;
                        ones_added++;
                    }

                    if (j < COLUMNS - 1) {
                        // Colocar ceros entre los grupos (al menos uno)
                        int num_zeros = rand() % 2 + 1; // 1 o 2 ceros entre grupos
                        for (int z = 0; z < num_zeros && j < COLUMNS - 1; z++) {
                            map[i][j++] = 0;
                        }
                    }
                }
            } 
            else if (i == 7) { // Fila 7
                if (j == 0 || map[i][j - 1] == 0) { 
                    // Genera solo grupos de 2 unos seguidos (camiones)
                    int num_ones = 2; // Tamaño fijo del grupo: 2 unos seguidos
                    int remaining_space = COLUMNS - j; // Espacios disponibles en la fila

                    if (num_ones > remaining_space - 1) {
                        // Si no hay espacio suficiente para el grupo, rellenar con ceros
                        while (j < COLUMNS) {
                            map[i][j++] = 0;
                        }
                        break;
                    }

                    int ones_added = 0;
                    while (ones_added < num_ones && j < COLUMNS - 1) { 
                        // Generar grupo de 2 unos seguidos
                        map[i][j++] = 1;
                        ones_added++;
                    }

                    if (j < COLUMNS - 1) {
                        // Colocar ceros entre los grupos (al menos uno)
                        int num_zeros = rand() % 2 + 1; // 1 o 2 ceros entre grupos
                        for (int z = 0; z < num_zeros && j < COLUMNS - 1; z++) {
                            map[i][j++] = 0;
                        }
                    }
                }
            } 
            else { // Filas restantes (excepto las 0, 6, 7, 12)
                if (j == 0 || map[i][j - 1] == 0) { 
                    map[i][j] = rand() % 2; // Genera 0 o 1 aleatorio
                } 
                else {
                    map[i][j] = 0; // Si el anterior es 1, el actual debe ser 0
                }
            }
        }
    }
}

/*------Function print_matrix------*/
// Función auxiliar (hasta tener todo con la interfaz allegro)para imprimir la matriz
void print_matrix() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
}

/*------Function shift_row------*/
// Función para desplazar las filas de la matriz de juego (Derecha e izquierda)
void shift_row(uint8_t row, uint8_t direction) {
    if (direction) { // Desplazar a la derecha
        // Guardamos el último valor de la fila
        uint8_t last_value = map[row][COLUMNS - 1];

        // Desplazamos todos los elementos hacia la derecha
        for (uint8_t i = COLUMNS - 1; i > 0; i--) {
            map[row][i] = map[row][i - 1];
        }

        // Colocamos el valor del final al principio si era un punto válido
        if (last_value != 0) {
            map[row][0] = last_value;
        } else {
            map[row][0] = 0; // Limpiamos la primera columna si no hay punto
        }
    } else { // Desplazar a la izquierda
        // Guardamos el primer valor de la fila
        uint8_t first_value = map[row][0];

        // Desplazamos todos los elementos hacia la izquierda
        for (uint8_t i = 0; i < COLUMNS - 1; i++) {
            map[row][i] = map[row][i + 1];
        }

        // Colocamos el valor del principio al final si era un punto válido
        if (first_value != 0) {
            map[row][COLUMNS - 1] = first_value;
        } else {
            map[row][COLUMNS - 1] = 0; // Limpiamos la última columna si no hay punto
        }
    }
}


