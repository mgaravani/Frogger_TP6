/*------------INCLUDES-----------*/
#include "../Backend/logic.h"


uint8_t directions[11] = {0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1};

/*-----Function main-----*/
int main(void)
{
    frog_t frog_position; // Estructura de la rana
    initialize_game_state(&frog_position);
    #ifdef PC // PC
        AllegroResources resources_for_main; // Estructura de recursos de Allegro
        ALLEGRO_EVENT_QUEUE *event_queue;    // Cola de eventos
    #endif
    // Inicialización del estado del juego
    

    #ifdef RASPBERRY_PI
        // Inicializar recursos de la Raspberry Pi
        initialize_raspy_resources(&frog_position);
        uint8_t matriz[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS] = {0}; // Matriz del display 16x16
        // Manejar el menú y la lógica del juego
        handle_menu_raspy(&frog_position, matriz);
    #endif

    #ifdef PC
        // Inicialización de recursos de Allegro (solo para PC)
        initialize_allegro_resources(&resources_for_main, &event_queue); 
        // Manejo del menú y bucle del juego
        handle_menu_allegro(&resources_for_main, event_queue, &frog_position, map);
        //funcion de inico de juego y bucle en allegro
        game_loop_allegro(&frog_position, &resources_for_main, event_queue, map); 
    #endif

    
    

    return 0;
}