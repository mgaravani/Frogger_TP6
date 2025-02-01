#include "raspberry.h"




int main() {
    int choice = 0;
    int running = 1; // Variable de control para mantener el programa en ejecución
    ShowFrogger();
    while (running) { // Mientras `running` sea 1, el menú se mostrará
       while (choice == 0)
       {
         choice = ShowMenu(); // Mostrar el menú
        
        switch (choice) {
            case 1:
                usleep(500000); // Esperar 500 ms	
                choice = playGame(choice); // Lógica del juego
                break;
            case 2:
                printf("Saliendo del juego. ¡Hasta pronto!\n");
                running = 0; // Cambiar el valor de `running` para salir del bucle
                break;
            default:
                printf(".\n");
        }
       }
    }
    return 0;
}

// Función principal del juego
int playGame(int choice) {
    printf("\n[Iniciando el juego...]\n");
    disp_init();
    disp_clear();
    extern map_t map; // Declarar la variable global map
   // pthread_t matrix_tid;
    //pthread_create(&matrix_tid, NULL, matrix_thread, NULL);  // Crear el hilo de la matriz
    pthread_t frog_tid;
    pthread_create(&frog_tid, NULL, frog_thread, NULL);  // Crear el hilo de la rana
   // pthread_join(matrix_tid, NULL);  // Esperar a que termine el hilo de la matriz
    pthread_join(frog_tid, NULL);  // Esperar a que termine el hilo de la rana
    disp_clear();
    disp_update();


    return 0;
}



void shiftDisplay(uint8_t display[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS], uint8_t bitmap[DISP_CANT_Y_DOTS][46], int offset) {
    // Copiar una ventana de 16x16 del bitmap al display
    for (int y = 0; y < DISP_CANT_Y_DOTS; y++) {
        for (int x = 0; x < DISP_CANT_X_DOTS; x++) {
            display[y][x] = bitmap[y][x + offset];
        }
    }
}
