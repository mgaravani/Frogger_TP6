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
            if (matriz[i][j] > 0) {
                disp_write(myPoint, D_ON);
            } if (matriz[i][j] == 0) {
                disp_write(myPoint, D_OFF);
            }
            
        }
    }
    disp_update();
}
void screen_raspy(frog_t* frog_position, uint8_t matriz[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS]) {
    static uint8_t prev_x = 0;  // Almacena la posición anterior en X
    static uint8_t prev_y = 0;  // Almacena la posición anterior en Y
    disp_clear();  // Limpia el display
    dcoord_t myPoint;

    // Borra la posición anterior de la rana
    matriz[prev_y][prev_x]--;

    // Obtiene la nueva posición de la rana
    uint8_t new_x = get_frog_x(frog_position);
    uint8_t new_y = get_frog_y(frog_position);

    // Actualiza la posición anterior
    prev_x = new_x;
    prev_y = new_y;

    // Dibuja la nueva posición de la rana
    matriz[new_y][new_x]++;

    // Itera sobre toda la matriz para mostrarla en el display
    for (uint8_t i = 0; i < DISP_CANT_Y_DOTS; i++) {  // Y (filas)
        for (uint8_t j = 0; j < DISP_CANT_X_DOTS; j++) {  // X (columnas)
            myPoint.x = j;
            myPoint.y = i;

            if (matriz[i][j] == 1) {
                disp_write(myPoint, D_ON);  // Enciende el píxel si es 1
            } else if (matriz[i][j] == 0) {
                disp_write(myPoint, D_OFF);  // Apaga el píxel si es 0
            }
        }
    }

    disp_update();  // Actualiza el display al final
}
