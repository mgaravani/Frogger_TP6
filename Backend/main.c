/*------------INCLUDES-----------*/
#include <stdio.h>
#include "../Frontend/Frontend_Allegro/allegro.h"
#include "../Backend/map.h"
#include "delay.h"
#include <time.h> // LO PONGO PARA HACER PRUEBAS, DESPUES SACAR

/* FUNCION MAIN */
int main(void) {
    extern map_t map; // Variable global de la matriz
    AllegroResources resourcesformain = allegro_init(map); // Inicializa allegro
// Definir el tamaño de la matriz (13x18)
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
    initialize_matrix();
    while (1) {
        // Calcula el tiempo transcurrido
        double elapsed = (double)(clock() - start_time) / CLOCKS_PER_SEC;

        if (elapsed >= delay) {
            printf("Han pasado %.1f segundos.\n", elapsed);
            break; // Sal del bucle cuando el tiempo se cumpla
        }
        // Simula otras tareas
        for (int fila = 0; fila < 10 ; fila++) {
            if (waiting_time(1, fila)){
                shift_row(fila, 0);
            }
            
        }
        for (int fila = 10; fila < 13 ; fila++) {
            if (waiting_time(5, fila)){
                shift_row(fila, 0);
            }
        }
        print_matrix();
        Screen(&resourcesformain, map);
        usleep(100000);
    }

    //mostrar_mensaje(); // Funcion de allegro
    return 0;
}