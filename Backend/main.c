/* INCLUDES */
#include <stdio.h>
#include "../Frontend/Frontend_Allegro/allegro.h"
#include "../Backend/mapa.h"

/* FUNCION MAIN */
int main(void) {
// Definir el tamaño de la matriz (16x18)
    #define SIZELINEA 18

    // Inicializar la matriz
    inicializar_matriz();
    int prueba = 0;
    while ( prueba != 20) {
        sleep(2);
        prueba++;
        shift_row(14, 0);
        imprimir_matriz();
        printf("\n");
    }

    //mostrar_mensaje(); // Funcion de allegro
    return 0;
}