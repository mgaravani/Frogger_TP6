/* INCLUDES */
#include <stdio.h>
#include "../Frontend/Frontend_Allegro/allegro.h"
#include "../Backend/mapa.h"
#include "delay.h"
#include <time.h> // LO PONGO PARA HACER PRUEBAS, DESPUES SACAR

/* FUNCION MAIN */
int main(void) {
// Definir el tamaño de la matriz (16x18)
    #define SIZELINEA 18  // PARA QUE SIRVE? BAUTI

    // Inicializar la matriz
/*     inicializar_matriz(); // Genera una matriz aleatoria
    int prueba = 0;
    while ( prueba != 20) {
        sleep(2);
        prueba++;
        shift_row(14, 0);
        imprimir_matriz();
        printf("\n");
    } */

    clock_t start_time = clock(); // Tiempo inicial
    double delay = 10.0;          
    inicializar_matriz();
    while (1) {
        // Calcula el tiempo transcurrido
        double elapsed = (double)(clock() - start_time) / CLOCKS_PER_SEC;

        if (elapsed >= delay) {
            printf("Han pasado %.1f segundos.\n", elapsed);
            break; // Sal del bucle cuando el tiempo se cumpla
        }
        // Simula otras tareas
        for (int fila = 0; fila < 13 ; fila++) {
            if (waiting_time(1, fila)){
                shift_row(fila, 0);
            }
            
        }
        for (int fila = 13; fila < 16 ; fila++) {
            if (waiting_time(5, fila)){
                shift_row(fila, 0);
            }
        }
        imprimir_matriz();
        usleep(100000);
    }

    //mostrar_mensaje(); // Funcion de allegro
    return 0;
}