#include "display.h"


// Función para leer la matriz y actualizar el display
void mostrar_matriz(uint8_t matriz[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS]) {
    dcoord_t myPoint;

    for (uint8_t i = 0; i < DISP_CANT_Y_DOTS; i++) {  // Función para leer la matriz
        for (uint8_t j = 0; j < DISP_CANT_X_DOTS; j++) {
            myPoint.x = j;
            myPoint.y = i;
            if (matriz[i][j] == 1) {
                disp_write(myPoint, D_ON);
            } if (matriz[i][j] == 0) {
                disp_write(myPoint, D_OFF);
            }if (matriz[i][j] == 2)
            {
                /* code */
            }
            
        }
    }
    disp_update();
}
// Función para recortar la matriz de 13x20 a 13x16 columna 3 a columna 18
void recortar_matriz(uint8_t matriz_original[ROWS_ORIGINAL][COLS_ORIGINAL], uint8_t matriz_recortada[DISP_CANT_Y_DOTS][16]) {
    for (int i = 0; i < DISP_CANT_Y_DOTS; i++) {  // Recorrer todas las filas (0 a 12)
        for (int j = 0; j < 16; j++) {  // Recorrer las columnas 3 a 18 (índices 2 a 17 en la original)
            matriz_recortada[i+1][j] = matriz_original[i+1][j + 2];  // Copiar desde la columna 3 (índice 2)
        }
    }
}
