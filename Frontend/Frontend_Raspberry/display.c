#include "display.h"


// Función para leer la matriz y actualizar el display
void mostrar_matriz_recortada(uint8_t matriz_original[ROWS_ORIGINAL][COLS_ORIGINAL]) {
    uint8_t matriz_recortada[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS];
    dcoord_t myPoint;

    // Recortar la matriz original
    for (int i = 1; i < DISP_CANT_Y_DOTS; i++) {  
        for (int j = 0; j < 16; j++) {  
            matriz_recortada[i+1][j] = matriz_original[i][j + 2];  
        }
    }

    // Mostrar la matriz recortada
    for (uint8_t i = 0; i < DISP_CANT_Y_DOTS; i++) {  
        for (uint8_t j = 0; j < 16; j++) {
            myPoint.x = j;
            myPoint.y = i;
            if (matriz_recortada[i][j] == 2) {
                // Parpadear el punto
                for (int k = 0; k < 2; k++) {
                    disp_write(myPoint, D_ON);
                    disp_update(); // Actualizar la pantalla
                    usleep(100);
                    disp_write(myPoint, D_OFF);
                    disp_update(); // Actualizar la pantalla
                    usleep(100);
                }
            } else if (matriz_recortada[i][j] == 1) {
                disp_write(myPoint, D_ON);
            } else {
                disp_write(myPoint, D_OFF);
            }
        }
    }
    
    disp_update(); // Actualizar la pantalla finalmente
}
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
            }
            
        }
    }
    disp_update();
}
