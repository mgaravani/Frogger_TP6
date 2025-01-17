/*------------INCLUDES-----------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"

/*------------ GLOBAL VARIABLE ----------------*/
map_t map;

/*------------ FUNCTIONS ----------------*/

/*------initialize_matrix------*/
//Funcion encargada de inicializar la matriz de juego
void initialize_matrix(void) 
{
    srand(time(NULL)); // Semilla para generar números aleatorios

    for (int i = 0; i < ROWS; i++) 
    {
        int ones_count = 0; // Contador de unos por fila

        for (int j = 0; j < COLUMNS; j++) 
        {
            if (i == 6 || i == 12 || j == 0 || j == 14) 
            { // Filas y columnas específicas llenas de ceros
                map[i][j] = 0;
            } 
            else if (i == 0) 
            { // Fila 0 (fila de llegada) es fija.
                if (j == 1 || j == 4 || j == 7 || j == 10 || j == 13) //CHEQUEAR ESTOS VALORES
                { // Posiciones de posible llegada (objetivos).
                    map[i][j] = 1;
                } 
                else 
                { // Posiciones sin llegada (pared).
                    map[i][j] = 0;
                }
            } 
            else if (i == 2 || i == 5) 
            { // Filas 2 y 5
                if (j == 0 || map[i][j - 1] == 0) 
                { 
                    // Generar grupos de 2 o 3 unos seguidos
                    int num_ones = rand() % 2 + 2; // Tamaño del grupo: 2 o 3 unos
                    int remaining_space = COLUMNS - j; // Espacios disponibles en la fila

                    if (num_ones > remaining_space - 1) 
                    {
                        // Si no hay espacio suficiente para el grupo, rellenar con ceros
                        while (j < COLUMNS) 
                        {
                            map[i][j++] = 0;
                        }
                        break;
                    }

                    int ones_added = 0;
                    while (ones_added < num_ones && j < COLUMNS - 1) 
                    { 
                        // Generar grupo de unos
                        map[i][j++] = 1;
                        ones_added++;
                    }

                    if (j < COLUMNS - 1) 
                    {
                        // Colocar ceros entre los grupos (al menos uno)
                        int num_zeros = rand() % 2 + 1; // 1 o 2 ceros entre grupos
                        for (int z = 0; z < num_zeros && j < COLUMNS - 1; z++) 
                        {
                            map[i][j++] = 0;
                        }
                    }
                }
            } 
            else if (i >= 8 && i <= 11) 
            { // Filas 8, 9, 10 y 11 con máximo 4 unos
                if (ones_count >= 4) 
                {
                    map[i][j] = 0; // Rellenar con ceros si se alcanzó el máximo de unos
                } 
                else if (j == 0 || map[i][j - 1] == 0) 
                { 
                    // Decidir si colocar un 1 o 0
                    int is_one = rand() % 2; // 50% probabilidad de colocar un 1
                    map[i][j] = is_one;
                    ones_count += is_one; // Incrementar contador si es un 1
                } 
                else 
                {
                    map[i][j] = 0; // Si el anterior es 1, el actual debe ser 0
                }
            } 
            else if (i == 7) 
            { // Fila 7 con máximo 6 unos
                if (ones_count >= 6) 
                {
                    map[i][j] = 0; // Rellenar con ceros si se alcanzó el máximo de unos
                } 
                else if (j == 0 || map[i][j - 1] == 0) 
                { 
                    // Generar grupos de 2 unos seguidos (camiones)
                    int num_ones = 2; // Tamaño fijo del grupo: 2 unos seguidos
                    int remaining_space = COLUMNS - j; // Espacios disponibles en la fila

                    if (num_ones > remaining_space - 1) 
                    {
                        // Si no hay espacio suficiente para el grupo, rellenar con ceros
                        while (j < COLUMNS) 
                        {
                            map[i][j++] = 0;
                        }
                        break;
                    }

                    int ones_added = 0;
                    while (ones_added < num_ones && j < COLUMNS - 1 && ones_count < 6) 
                    { 
                        // Generar grupo de 2 unos seguidos
                        map[i][j++] = 1;
                        ones_added++;
                        ones_count++;
                    }

                    if (j < COLUMNS - 1 && ones_count < 6) 
                    {
                        // Colocar ceros entre los grupos (al menos uno)
                        int num_zeros = rand() % 2 + 1; // 1 o 2 ceros entre grupos
                        for (int z = 0; z < num_zeros && j < COLUMNS - 1; z++) 
                        {
                            map[i][j++] = 0;
                        }
                    }
                }
            } 
            else if (i >= 1 && i <= 5 && i != 2 && i != 5) 
            { // Filas entre la 1 y la 5, excepto 2 y 5
                if (j == 0 || map[i][j - 1] == 0) 
                { 
                    // Generar grupos de 2 a 4 unos seguidos
                    int num_ones = rand() % 3 + 2; // Tamaño del grupo: 2 a 4 unos
                    int remaining_space = COLUMNS - j; // Espacios disponibles en la fila

                    if (num_ones > remaining_space - 1) 
                    {
                        // Si no hay espacio suficiente para el grupo, rellenar con ceros
                        while (j < COLUMNS) 
                        {
                            map[i][j++] = 0;
                        }
                        break;
                    }

                    int ones_added = 0;
                    while (ones_added < num_ones && j < COLUMNS - 1) 
                    { 
                        // Generar grupo de unos
                        map[i][j++] = 1;
                        ones_added++;
                    }

                    if (j < COLUMNS - 1) 
                    {
                        // Colocar ceros entre los grupos (al menos uno)
                        int num_zeros = rand() % 2 + 1; // 1 o 2 ceros entre grupos
                        for (int z = 0; z < num_zeros && j < COLUMNS - 1; z++) 
                        {
                            map[i][j++] = 0;
                        }
                    }
                }
            } 
            else 
            { // Filas restantes (excepto las 0, 6, 7, 12)
                if (j == 0 || map[i][j - 1] == 0) 
                { 
                    map[i][j] = rand() % 2; // Genera 0 o 1 aleatorio
                } 
                else 
                {
                    map[i][j] = 0; // Si el anterior es 1, el actual debe ser 0
                }
            }
        }
    }
}



/*------print_matrix------*/
// Función auxiliar (hasta tener todo con la interfaz allegro)para imprimir la matriz
void print_matrix() 
{
    for (int i = 0; i < ROWS; i++) 
    {
        for (int j = 0; j < COLUMNS; j++) 
        {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
}

/*------shift_row------*/
// Función para desplazar las filas de la matriz de juego (Derecha e izquierda)
void shift_row(uint8_t row, uint8_t direction) 
{
    if (direction) 
    { // Desplazar a la derecha
        // Guardamos el último valor de la fila
        uint8_t last_value = map[row][COLUMNS - 1];

        // Desplazamos todos los elementos hacia la derecha
        for (uint8_t i = COLUMNS - 1; i > 0; i--) 
        {
            map[row][i] = map[row][i - 1];
        }

        // Colocamos el valor del final al principio si era un punto válido
        if (last_value != 0) 
        {
            map[row][0] = last_value;
        } else {
            map[row][0] = 0; // Limpiamos la primera columna si no hay punto
        }
        } 
    else 
        { // Desplazar a la izquierda
            // Guardamos el primer valor de la fila
            uint8_t first_value = map[row][0];

            // Desplazamos todos los elementos hacia la izquierda
            for (uint8_t i = 0; i < COLUMNS - 1; i++) 
            {
                map[row][i] = map[row][i + 1];
            }

            // Colocamos el valor del principio al final si era un punto válido
            if (first_value != 0) 
            {
                map[row][COLUMNS - 1] = first_value;
            } else {
                map[row][COLUMNS - 1] = 0; // Limpiamos la última columna si no hay punto
            }
        }
}
