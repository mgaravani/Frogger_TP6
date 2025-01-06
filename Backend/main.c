/*------------INCLUDES-----------*/
#include <stdio.h>
#include "../Frontend/Frontend_Allegro/allegro.h"
#include "../Backend/map.h"
#include "delay.h"

/* FUNCION MAIN */
int main(void) 
{
    extern map_t map; // Variable global de la matriz
    extern frog_t frog; // Variable global de la rana
    AllegroResources resources_for_main = allegro_init(map); // Inicializa allegro
        
    initialize_matrix();
    //frog_position();
    while (1) 
    {
        for (int fila = 0; fila < 6; fila++) 
        {
            // Desplazar fila par (de izquierda a derecha)
            if (waiting_time(5, 2*fila)) 
            {
                shift_row(2*fila, 1);  // Desplazar fila 0, 2, 4, 6, etc. a la derecha
            }

            // Desplazar fila impar (de derecha a izquierda)
            if (waiting_time(1, ((2*fila) + 1))) 
            {
                shift_row((2*fila) + 1, 0);  // Desplazar fila 1, 3, 5, etc. a la izquierda
            }
        }
        print_matrix();
        Screen(&resources_for_main, map,frog);
        usleep(600000);
    }

    //mostrar_mensaje(); // Funcion de allegro
    return 0;
}