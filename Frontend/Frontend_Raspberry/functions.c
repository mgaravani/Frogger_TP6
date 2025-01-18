#include "functions.h"
#include "macros.h"
//Los Macros DISP_CANT_Y/X_DOTS son definidas por el tamaño de la matriz de led dada, si se modifica se podra cambiar en Macros.h
// Función para generar la matriz con valores aleatorios de 0 y 1
void generar_matriz(uint8_t  matriz[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS]) {//funcion generica para primer uso de generamiento de matriz
    srand(time(NULL));

    for (uint8_t  i = 0; i < DISP_CANT_Y_DOTS; i++) {
        for (uint8_t  j = 0; j < DISP_CANT_X_DOTS; j++) {
            matriz[i][j] = rand() % 2;
        }
    }
}

// Función para leer la matriz y actualizar el display
void mostrar_matriz(uint8_t  matriz[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS]) {
    dcoord_t myPoint;

    for (uint8_t i = 0; i < DISP_CANT_Y_DOTS; i++) { //funcion para leer la matriz y 
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
}


/*do {
        // Simular lectura del joystick
        coord = joy_read(); // Función que lee la posición del joystick

        if (coord.x > THRESHOLD && npos.x < DISP_MAX_X - 2) {
            moveMatrix(Matriz, Sapo, ++npos.x, npos.y);
        }
        if (coord.x < -THRESHOLD && npos.x > DISP_MIN) {
            moveMatrix(Matriz, Sapo, --npos.x, npos.y);
        }
        if (coord.y > THRESHOLD && npos.y < DISP_MAX_Y - 2) {
            moveMatrix(Matriz, Sapo, npos.x, ++npos.y);
        }
        if (coord.y < -THRESHOLD && npos.y > DISP_MIN) {
            moveMatrix(Matriz, Sapo, npos.x, --npos.y);
        }

        mostrar_matriz(Matriz);

        // Actualizar la pantalla
        disp_update();

        // Simular una pausa para evitar la lectura excesiva

    } while (coord.sw == J_NOPRESS ); */