#include "display.h"


// Función para leer la matriz y actualizar el display
void mostrar_matriz_recortada() {
    uint8_t matriz_recortada[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS];
    dcoord_t myPoint;

    // Recortar la matriz original (map) a la matriz recortada
    for (int i = 0; i < DISP_CANT_Y_DOTS; i++) {  
        for (int j = 0; j < DISP_CANT_X_DOTS; j++) {  
            matriz_recortada[i+2][j] = map[i + 1][j + 2];  // Recortar desde (1, 2) de la matriz original
        }
    }

    // Mostrar la matriz recortada
    for (uint8_t i = 0; i < DISP_CANT_Y_DOTS; i++) {  
        for (uint8_t j = 0; j < DISP_CANT_X_DOTS; j++) {
            myPoint.x = j;
            myPoint.y = i;
             if (matriz_recortada[i][j] == 1) {
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
