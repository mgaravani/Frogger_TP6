#include "functions.h"
#include "macros.h"
#include "disdrv.h"
#include <stdlib.h>  // Para rand y srand
#include <time.h>    // Para time

// Definición de las dimensiones actualizadas


// Función para generar la matriz con valores aleatorios de 0 y 1
void generar_matriz(uint8_t matriz[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS]) {
    srand(time(NULL));

    for (uint8_t i = 0; i < DISP_CANT_Y_DOTS; i++) {  // Ajustamos a 16 filas
        for (uint8_t j = 0; j < DISP_CANT_X_DOTS; j++) {  // Ajustamos a 16 columnas
            matriz[i][j] = rand() % 2;
        }
    }
}

// Función para desplazar una fila de la matriz
void desplazar_fila(uint8_t matriz[ROWS_ORIGINAL][COLS_ORIGINAL], uint8_t fila, uint8_t direccion, uint8_t velocidad) {
    if (fila >= ROWS_ORIGINAL) return;  // Evitar accesos fuera de rango

    for (uint8_t v = 0; v < velocidad; v++) {  // Repetir según la velocidad
        if (direccion) {  // Desplazar a la derecha
            uint8_t ultimo = matriz[fila][COLS_ORIGINAL - 1];
            for (uint8_t i = COLS_ORIGINAL - 1; i > 0; i--) {
                matriz[fila][i] = matriz[fila][i - 1];
            }
            matriz[fila][0] = ultimo;
        } else {  // Desplazar a la izquierda
            uint8_t primero = matriz[fila][0];
            for (uint8_t i = 0; i < COLS_ORIGINAL - 1; i++) {
                matriz[fila][i] = matriz[fila][i + 1];
            }
            matriz[fila][COLS_ORIGINAL - 1] = primero;
        }
    }
}

// Función para leer la matriz y actualizar el display
// Función para leer la matriz y actualizar el display
void mostrar_matriz(uint8_t matriz[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS]) {
    dcoord_t myPoint;

    for (uint8_t i = 0; i < DISP_CANT_Y_DOTS; i++) {  // Función para leer la matriz
        for (uint8_t j = 0; j < DISP_CANT_X_DOTS; j++) {
            myPoint.x = j;
            myPoint.y = i;
            if (matriz[i][j] == 1) {
                disp_write(myPoint, D_ON);
            } else {
                disp_write(myPoint, D_OFF);
            }
        }
    }
    disp_update();
}

// Función para recortar la matriz de 13x20 a 13x16
void recortar_matriz(uint8_t matriz_original[ROWS_ORIGINAL][COLS_ORIGINAL], uint8_t matriz_recortada[DISP_CANT_Y_DOTS][16]) {
    for (int i = 3; i < DISP_CANT_Y_DOTS; i++) {
        for (int j = 0; j < 16; j++) {  // Copiar de la columna 1 a la columna 16 (índices 0 a 15)
            matriz_recortada[i][j] = matriz_original[i][j];
        }
    }
}

/*
void moveMatrix(uint8_t target[DISP_CANT_X_DOTS][DISP_CANT_Y_DOTS], uint8_t source[SAPO_SIZE][SAPO_SIZE], int startRow, int startCol) {
    // Limpia el área donde se copiará la nueva matriz
    for (int i = 0; i < SAPO_SIZE; i++) {
        for (int j = 0; j < SAPO_SIZE; j++) {
            target[startRow + i][startCol + j] = 0; // Borra el contenido anterior
        }
    }

    // Copia la matriz fuente a la nueva posición
    for (int i = 0; i < SAPO_SIZE; i++) {
        for (int j = 0; j < SAPO_SIZE; j++) {
            target[startRow + i][startCol + j] = source[i][j];
        }
    }
}*/

