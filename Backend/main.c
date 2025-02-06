#include "main.h"

int main(void) {
    extern map_t map;
    initialize_matrix();
    frog_t frog_position;
    init_frog(&frog_position, 7, 11.96, 0, 1, 3, 0, 0, 0, 0, 0, 1);
    init_frog(&frog_position, 7, 11.96, 0, 1, 3, 0, 0, 0, 0, 0, 1);
    frog_position.pass_level_state = 0;
    frog_position.paused_state = 0;
    frog_position.actual_row = ROWS - 1;
    for(uint8_t i = 0; i < ROWS; i++) {
        frog_position.reached_rows[i] = 0 ;
    }
    uint8_t running = 1;

#ifdef RASPBERRY_PI
    uint8_t choice = 0;
    disp_init();
    disp_clear();
    ShowFrogger();
    joy_init();

    while (running) {
        switch (choice) {
            case 0:
                choice = ShowMenu();
                break;
            case 1:
                disp_clear();
                choice = playGameLoop(&frog_position,running)
                printf("Choice: %d \n", choice);
                break;
            case 2:
                printf("Saliendo del juego. ¡Hasta pronto!\n");
                running = 0;
                disp_clear();
                disp_update();
                break;
            case 3:
                choice = ShowCONT();
                printf("Choice: %d \n", choice);
                break;
            case 4:
                choice = 0;
                ShowGameOver();
                printf("Choice: %d \n", choice);
                break;
            default:
                printf(".\n");
                break;
        }
    }
#endif
#ifdef PC // PC
    
    AllegroResources resources_for_main = allegro_init(map);
    ALLEGRO_EVENT_QUEUE *event_queue = init_events(resources_for_main.display);
    

    while(resources_for_main.menu_state == 1) {
        events_managment(&resources_for_main, event_queue, &frog_position, map);
        allegro_menu(&resources_for_main);
    }
#endif
    


    return 0;
}


 uint8_t playGameLoop(frog_t *frog_position, uint8_t *running) {
    uint8_t directions[11] = {0,1,0,1,1,0,0,0,1,0,1};
    while (*running) { // Dereference running to access its value
        int row = 12 - (int)(((-(get_frog_y(frog_position) - 11.96)) / 0.96)); // Pass frog_position to get_frog_y
#ifdef PC
        events_managment(&resources_for_main, event_queue, frog_position, map); // Pass frog_position
#endif
#ifdef RASPBERRY_PI
        move_frog_by_joystick(frog_position); // Pass frog_position
#endif
        for (int fila = 1; fila < 12; fila++) {
            if (waiting_time(frog_position->levels, fila)) { // Use -> to access levels
                if ((row == fila) && (get_frog_move(frog_position) == 1)) { // Pass frog_position
                    if ((((int)(get_frog_x(frog_position)) + 1 > 13) && directions[fila]) || ((((int)(get_frog_x(frog_position)) - 1 < 1)) && (!directions[fila]))) { // Pass frog_position
                        set_frog_life(frog_position, 0);  // Pass frog_position
                        set_frog_dead(frog_position, 1);  // Pass frog_position
                        *running = 0; // Game Over, exit the loop
                        return 4; // Return Game Over choice

                    } else {
                        if (directions[fila]) set_frog_x(frog_position, get_frog_x(frog_position) + 1); // Pass frog_position
                        else set_frog_x(frog_position, get_frog_x(frog_position) - 1); // Pass frog_position
                    }
                }
                if (frog_position->paused_state == 0) { // Use -> to access paused_state
                    shift_row(fila, directions[fila]);
                }
            }

            if (detect_arrival(frog_position, &map)) {  // Pass frog_position
                set_frog_arrivals(frog_position, get_frog_arrivals(frog_position) + 1); // Pass frog_position
                set_frog_start(frog_position);  // Pass frog_position
            }

            if (get_frog_lives(frog_position) == 0) { // Pass frog_position
                *running = 0; // No lives left, exit the loop
                return 4; // Return Game Over choice
            }

            if (get_frog_arrivals(frog_position) == 5) { // Pass frog_position
                pass_level(frog_position);  // Pass frog_position
            }
        }

        frog_in_range(&map, frog_position);  // Pass frog_position
#ifdef PC
        Screen(&resources_for_main, map, frog_position); // Pass frog_position
#endif
#ifdef RASPBERRY_PI
        mostrar_matriz_recortada(); // No arguments needed if it uses globals
#endif
}

 }