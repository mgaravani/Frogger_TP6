#include "display.h"


// Función para leer la matriz y actualizar el display
void recortar_matriz() {
    
    
    // Recortar la matriz original (map) a la matriz recortada
    
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


void screen_raspy(frog_t* frog_position) {
    
    // Copiar el valor de map a matriz
    for (int i = 0; i < DISP_CANT_Y_DOTS; i++) {  
        for (int j = 0; j < DISP_CANT_X_DOTS; j++) {  
            // Verificar si i está en el rango de 0 a 5
            if (i > 0 && i <= 4) {
                // Invertir los valores de map en matriz
                if (map[i+1][j + 1] == 0) {
                    matriz[i + 2][j] = 1; // Si map tiene 0, poner 1 en matriz
                } else if (map[i+1][j + 1] == 1) {
                    matriz[i + 2][j] = 0; // Si map tiene 1, poner 0 en matriz
                }
            } else {
                // Para i fuera del rango 0-5, copiar el valor de map a matriz sin cambios
                matriz[i + 2][j] = map[i+1][j + 1];
            }
        }
    }
    
    // Fila 15: Enciende todos los LEDs de la fila 15 
    for (int j = 0; j < DISP_CANT_X_DOTS; j++) {
        matriz[15][j] = 1;  // La fila 16 está en índice 16 (contando desde 0)
    }

    static uint8_t prev_x = 0;  // Almacena la posición anterior en X
    static uint8_t prev_y = 0;  // Almacena la posición anterior en Y
    static clock_t last_toggle_time = 0; // Almacena el último momento en que se cambió el estado
    static uint8_t frog_visible = 1; // Estado actual de la rana (1: visible, 0: invisible)

    // Obtener el tiempo actual
    clock_t current_time = clock();

    // Cambiar el estado de la rana cada 50 milisegundos (0.05 segundos) 
    if ((current_time - last_toggle_time) >= (CLOCKS_PER_SEC * 0.05)) {
        frog_visible = !frog_visible; // Alternar entre visible e invisible
        last_toggle_time = current_time; // Actualizar el último momento de cambio
    }

    dcoord_t myPoint;

    // Borra la posición anterior de la rana
    myPoint.x = prev_x;
    myPoint.y = prev_y;
    disp_write(myPoint, D_OFF);

    // Obtiene la nueva posición de la rana
    uint8_t new_x = get_frog_x(frog_position);
    uint8_t new_y = get_frog_y(frog_position);

    // Actualiza la posición anterior
    prev_x = new_x;
    prev_y = new_y;

    // Itera sobre toda la matriz para mostrarla en el display
    for (uint8_t i = 0; i < DISP_CANT_Y_DOTS; i++) {  // Y (filas)
        for (uint8_t j = 0; j < DISP_CANT_X_DOTS; j++) {  // X (columnas)
            myPoint.x = j;
            myPoint.y = i;

            if (matriz[i][j] >= 1) {
                disp_write(myPoint, D_ON);  // Enciende el píxel si es 1
            } else {
                disp_write(myPoint, D_OFF);  // Apaga el píxel si es 0
            }
        }
    }

    // Dibuja la nueva posición de la rana solo si está visible
    if (frog_visible) {
        myPoint.x = new_x;
        myPoint.y = new_y;
        disp_write(myPoint, D_ON);
    }

    disp_update();  // Actualiza el display al final
}
