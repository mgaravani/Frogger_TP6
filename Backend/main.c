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
        // Inicializar la rana con los valores iniciales
        init_frog(&frog_position, 7, 14, 0, 1, 3, 0, 0, 0, 0, 0, 1);
        
        // Inicializar estados adicionales
        frog_position.pass_level_state = 0;
        frog_position.paused_state = 0; // Incluir en init_frog si es posible
        frog_position.playing_game = 1; // Juego activo
        frog_position.actual_row = ROWS - 1; // Fila inicial (inferior)
        frog_position.life = 3; // 3 vidas iniciales
        
        // Inicializar el arreglo de filas alcanzadas
        for (uint8_t i = 0; i < ROWS; i++) 
        {
            frog_position.reached_rows[i] = 0;
        }
        
        // Inicializar la matriz del juego
        initialize_raspy_resources();
        // Manejar el menú y la lógica del juego
        handle_menu_raspy(&frog_position);
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