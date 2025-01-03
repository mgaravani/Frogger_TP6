#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mapa.h"

/*------------ VARIABLE GLOBAL ----------------*/
mapa_t mapa;


/*------------ FUNCIONES ----------------*/
void inicializar_matriz() { //NO FUNCIONA BIEN revisar
    srand(time(NULL));
    
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (i == 0 || i == 10 || i == 15 || j == 0 || j == 17 ) { // Filas y columnas específicas llenas de ceros
                mapa[i][j] = 0;
            } else if (i >= 1 && i <= 9) { // Filas entre la 1 y la 9
                if (j == 0 || mapa[i][j - 1] == 0) { // Si es el primer elemento o el anterior es cero
                    // Genera grupos de 2 a 4 unos seguidos
                    while (j < COLUMNAS) {
                        int num_ones = rand() % 3 + 2; // Generar un grupo de 2 a 4 unos seguidos
                        int ones_added = 0;
                        
                        // Añadir el grupo de unos, asegurando no exceder el máximo de 4
                        while (ones_added < num_ones && j < COLUMNAS) {
                            mapa[i][j++] = 1;
                            ones_added++;
                        }

                        // Después de cada grupo de unos, colocar ceros entre los grupos (se pueden colocar más de un cero)
                        if (j < COLUMNAS) {
                            int num_zeros = rand() % (COLUMNAS - j); // Número aleatorio de ceros entre grupos
                            for (int z = 0; z < num_zeros && j < COLUMNAS; z++) {
                                mapa[i][j++] = 0;
                            }
                        }

                        // Evitar que se agreguen más de 4 unos seguidos
                        if (ones_added >= 4 || j >= COLUMNAS) {
                            break; // Si se alcanzan los 4 unos seguidos o el final de la fila, terminar
                        }
                    }
                }
            } else { // Filas restantes (excepto las 0, 10, 15)
                if (j == 0 || mapa[i][j - 1] == 0) { // Si es el primer elemento o el anterior es cero
                    mapa[i][j] = rand() % 2; // Genera 0 o 1 aleatorio
                } else {
                    mapa[i][j] = 0; // Si el anterior es 1, el actual debe ser 0
                }
            }
        }
    }
}

// Función auxiliar (hasta tener todo con la interfaz allegro)para imprimir la matriz
void imprimir_matriz() {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            printf("%d ", mapa[i][j]);
        }
        printf("\n");
    }
}

void shift_row(int8_t row, int8_t direction)
{
    if (direction) // Desplazar a la derecha
    {
        // Guardamos el último valor de la fila
        int8_t ultimo_valor = mapa[row][COLUMNAS - 1];

        // Desplazamos todos los elementos hacia la derecha
        for (int8_t i = COLUMNAS - 1; i > 0; i--)
        {
            mapa[row][i] = mapa[row][i - 1];
        }

        // Colocamos el valor del final al principio si era un punto válido
        if (ultimo_valor != 0)
        {
            mapa[row][0] = ultimo_valor;
        }
        else
        {
            mapa[row][0] = 0; // Limpiamos la primera columna si no hay punto
        }
    }
    else // Desplazar a la izquierda
    {
        // Guardamos el primer valor de la fila
        int8_t primer_valor = mapa[row][0];

        // Desplazamos todos los elementos hacia la izquierda
        for (int8_t i = 0; i < COLUMNAS - 1; i++)
        {
            mapa[row][i] = mapa[row][i + 1];
        }

        // Colocamos el valor del principio al final si era un punto válido
        if (primer_valor != 0)
        {
            mapa[row][COLUMNAS - 1] = primer_valor;
        }
        else
        {
            mapa[row][COLUMNAS - 1] = 0; // Limpiamos la última columna si no hay punto
        }
    }
}