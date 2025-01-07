/*------------INCLUDES-----------*/
#include "../Backend/frog.h"
#include "../Frontend/Frontend_Allegro/allegro.h"
#include "../Backend/map.h"
#include "delay.h"

/* FUNCION MAIN */
int main(void) 
{
    extern map_t map; // Variable global de la matriz
    frog_t frog_position;
    init_frog(&frog_position, 6, 12, 3, 0, 0);
    AllegroResources resources_for_main = allegro_init(map); // Inicializa allegro
    ALLEGRO_EVENT_QUEUE *event_queue = init_events(resources_for_main.display); // Crea la cola de eventos


    initialize_matrix();
    while (1) 
    {
        events_managment(&resources_for_main, event_queue, &frog_position);

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
        //print_matrix();
        Screen(&resources_for_main, map, &frog_position);
    }

    //mostrar_mensaje(); // Funcion de allegro
    return 0;
}