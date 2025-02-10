/*------------INCLUDES-----------*/
#include "../Backend/logic.h"

/*----- Functions -----*/

/*-----Initialize_game-----*/
void initialize_game_state(frog_t *frog_position) 
{
    // Inicializar la rana con los valores iniciales
    init_frog(frog_position, 7, 11.98, 0, 1, 3, 0, 0, 0, 0, 0, 1);
    
    // Inicializar estados adicionales
    frog_position->pass_level_state = 0;
    frog_position->paused_state = 0; // Incluir en init_frog si es posible
    frog_position->playing_game = 1; // Juego activo
    frog_position->actual_row = ROWS - 1; // Fila inicial (inferior)
    frog_position->life = 3; // 3 vidas iniciales
    
    // Inicializar el arreglo de filas alcanzadas
    for (uint8_t i = 0; i < ROWS; i++) 
    {
        frog_position->reached_rows[i] = 0;
    }
    
    // Inicializar la matriz del juego
    initialize_matrix();
}

#ifdef PC
/*----- PC Specific Functions -----*/

/*-----Initialize Allegro Resources-----*/
void initialize_allegro_resources(AllegroResources *resources_for_main, ALLEGRO_EVENT_QUEUE **event_queue) 
{
    *resources_for_main = allegro_init(map);
    *event_queue = init_events(resources_for_main->display);
}

/*-----Handle Menu Allegro-----*/
void handle_menu_allegro(AllegroResources *resources_for_main, ALLEGRO_EVENT_QUEUE *event_queue, frog_t *frog_position, map_t map) 
{
    while (resources_for_main->menu_state == 1) 
    {
        events_managment(resources_for_main, event_queue, frog_position, map);
        allegro_menu(resources_for_main);
    }
}

/*-----Game Loop Allegro-----*/
void game_loop_allegro(frog_t *frog_position, AllegroResources *resources_for_main, ALLEGRO_EVENT_QUEUE *event_queue, map_t map)
{
    while (frog_position->playing_game == 1) 
    {
        int row = 12 - (int)((-(get_frog_y(frog_position) - 11.96)) / 0.96);
        events_managment(resources_for_main, event_queue, frog_position, map);
        process_row_movements(frog_position, row);
        if (detect_arrival(frog_position, map)) 
        {
            set_frog_arrivals(frog_position, get_frog_arrivals(frog_position) + 1);
            set_frog_start(frog_position);
        }
        if (get_frog_lives(frog_position) == 0) 
        {
            handle_game_over(frog_position, resources_for_main, event_queue, map);
        }
        if (get_frog_arrivals(frog_position) == 5) 
        {
            pass_level(frog_position);
        }
        frog_in_range(map, frog_position);
        Screen(resources_for_main, map, frog_position);
    }
}

/*-----Handle Game Over Allegro-----*/
void handle_game_over(frog_t *frog_position, AllegroResources *resources_for_main, ALLEGRO_EVENT_QUEUE *event_queue, map_t map) 
{
    resources_for_main->menu_state = 1;
    player_t players[MAX_PLAYERS];
    loadScores("highscores.txt", players);
    enter_player_name(event_queue, resources_for_main);
    player_t newPlayer;
    strcpy(newPlayer.name, resources_for_main->player_name);
    newPlayer.score = get_frog_points(frog_position);
    newScore(players, newPlayer);
    saveScores("highscores.txt", players);
}
#endif // PC

#ifdef RASPBERRY_PI
/*----- Raspberry Pi Specific Functions -----*/

/*-----Initialize Raspberry Resources-----*/
void initialize_raspy_resources() 
{
    disp_init();                
    disp_clear();               
    disp_update();              
    ShowFrogger();              
    joy_init();
    
           
}

/*-----Handle Menu Raspberry Pi-----*/
void handle_menu_raspy(frog_t *frog_position) 
{
    uint8_t choice = 0;
    uint8_t running = 1;
    joy_init();
    while (running) 
    {
        switch (choice) 
        {
            case 0:
                choice = ShowMenu(); // Mostrar el menú principal
                break;
            case 1: // Jugar
                sleep(1);
                initialize_matrix();
                frog_position->x = 7;
                frog_position->y = 15;         // Reiniciar posición Y
                frog_position->life = 3;       // Reiniciar vidas a 3
                frog_position->playing_game = 1; // Activar el juego
                while (frog_position->playing_game) 
                {
                    if (game_loop_raspy(frog_position) == 0) 
                    {
                        // Si el juego termina, volver al menú principal
                        choice = 0;

                        break;
                    }
                }
                frog_position->playing_game = 1;
                frog_position->x = 7;
                frog_position->y = 15;
                frog_position->life = 3;       // Reiniciar vidas a 3
                break;
            case 2:
                printf("Saliendo del juego. ¡Hasta pronto!\n");
                running = 0;
                disp_clear();
                disp_update();
                break;
            default:
                printf("Opción no válida.\n");
                break;
        }
    }
}

uint8_t game_loop_raspy(frog_t *frog_position)
{
    while (frog_position->playing_game == 1) 
    {

        
            for (int i = 0; i < 13; i++) {
                for (int j = 0; j < 20; j++) {
                    printf("%d ", map[i][j]);  // Imprime el valor en la posición (i, j)
                }
                printf("\n");  // Nueva línea después de imprimir cada fila
            }
        
        process_row_movements_raspy(frog_position);  
        joyinfo_t joy ;
        joy = joy_read();
        // Castear las coordenadas a uint8_t
        uint8_t frog_x = (uint8_t)get_frog_x(frog_position);
        uint8_t frog_y = (uint8_t)get_frog_y(frog_position);

        // Imprimir la posición de la rana con valores casteados
        printf("Frog Position: (%d, %d) Frog life: %d\n", frog_x, frog_y, get_frog_lives(frog_position));
        printf("Frog Arrivals: %d\n", get_frog_arrivals(frog_position));
        printf("matriz: %d\n", matriz[frog_x][frog_y]);
        screen_raspy(frog_position); // Mostrar la matriz en el display y la rana
        update_frog_position(frog_position); // Actualizar la posición de la rana

        // Verificar colisiones
        if (check_collision(frog_position)) 
        {
            // Si hubo colisión, ya se manejó dentro de check_collision
            // No es necesario hacer nada más aquí, ya que la posición de la rana se reinició
        }
        if ( detect_arrival_raspy(frog_position) ) 
        {
            set_frog_arrivals(frog_position, get_frog_arrivals(frog_position) + 1);
            frog_position->x = 7;
            frog_position->y = 15;
        }
        if (get_frog_lives(frog_position) == 0) 
        {
            ShowGameOver();
            printf("Frog Position: (%d, %d) Frog life: %d\n", frog_x, frog_y, get_frog_lives(frog_position));
            return 0; // Fin del juego
        }
        if (get_frog_arrivals(frog_position) == 5) 
        {
            pass_level(frog_position);
        }
        if(joy.sw == J_PRESS)
        {
            frog_position->paused_state = 0;
            uint8_t choice = ShowCONT();
            if (choice == 1)
            {
                frog_position->paused_state = 1;
                sleep(.5);
                joy.sw = J_NOPRESS;
            }else if(choice == 0)
            {
                frog_position->playing_game = 0;
                return 1;
            }   
        }
    }
    return 1; // Juego en curso
}
uint8_t check_collision(frog_t *frog_position) 
{
    // Castear las coordenadas a uint8_t
    uint8_t frog_x = (uint8_t)get_frog_x(frog_position);
    uint8_t frog_y = (uint8_t)get_frog_y(frog_position);

    // verifico si se choco
    if (matriz[frog_y][frog_x] == 1) 
    {
        set_frog_lives(frog_position, get_frog_lives(frog_position) - 1);
        frog_position->x = 7;
        frog_position->y = 15; // Reiniciar la posición de la rana
        return 1; // Hubo colisión
    }
    return 0; // No hubo colisión
}
void process_row_movements_raspy(frog_t *frog_position) 
{
    // Recorrer las filas de obstáculos
    for (int fila = 1; fila < 12; fila++) 
    {
        if (waiting_time(frog_position->levels, fila)) // Esperar el tiempo adecuado
        {
            uint8_t row = 12 - (uint8_t)(((-(get_frog_y(frog_position) - 11.96)) / 0.96));
            if (row == fila && get_frog_move(frog_position) == 1) // Movimiento de la rana en la fila
            {
                if ((get_frog_x(frog_position) + 1 > 13 && directions[fila]) ||
                    (get_frog_x(frog_position) - 1 < 1 && !directions[fila])) 
                {
                    set_frog_life(frog_position, get_frog_life(frog_position) - 1);
                    set_frog_dead(frog_position, 1);
                } 
                else 
                {
                    set_frog_x(frog_position, get_frog_x(frog_position) + (directions[fila] ? 1 : -1));
                }
            }
            // Desplazar las filas
            if (frog_position->paused_state == 0) 
            {
                shift_row(fila, directions[fila]);
            }
        }
    }
}

#endif // RASPBERRY_PI

/*-----Common Function for Both Platforms-----*/
void process_row_movements(frog_t *frog_position, uint8_t row) 
{
    for (uint8_t fila = 1; fila < 12; fila++) 
    {
        if (waiting_time(frog_position->levels, fila)) 
        {
            if ((row == fila) && (get_frog_move(frog_position) == 1)) 
            {
                if ((((uint8_t)(get_frog_x(frog_position)) + 1 > 13) && directions[fila]) ||
                    (((uint8_t)(get_frog_x(frog_position)) - 1 < 1) && (!directions[fila]))) 
                {
                    set_frog_life(frog_position, 0);
                    set_frog_dead(frog_position, 1);
                } 
                else 
                {
                    set_frog_x(frog_position, get_frog_x(frog_position) + (directions[fila] ? 1 : -1));
                }
            }
            if (frog_position->paused_state == 0) 
            {
                shift_row(fila, directions[fila]);
            }
        }
    }
}
