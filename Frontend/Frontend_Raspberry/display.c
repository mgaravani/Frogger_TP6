#include "display.h"


// Función para leer la matriz y actualizar el display
void recortar_matriz(uint8_t matriz_recortada[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS]) {
    

    // Recortar la matriz original (map) a la matriz recortada
    for (int i = 0; i < DISP_CANT_Y_DOTS; i++) {  
        for (int j = 0; j < DISP_CANT_X_DOTS; j++) {  
            matriz_recortada[i+2][j] = map[i + 1][j + 2];  // Recortar desde (1, 2) de la matriz original
        }
    }
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
void screen_raspy(frog_t* frog_position, uint8_t matriz[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS]) {
    dcoord_t myPoint;
    myPoint.x = (uint8_t)(get_frog_x(frog_position));
    myPoint.y = (uint8_t)(get_frog_y(frog_position));
    disp_write(myPoint, D_ON);
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