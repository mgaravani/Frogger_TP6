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
    initialize_matrix();   
     for (int i = 0; i < 13; i++) {
                for (int j = 0; j < 20; j++) {
                    printf("%d ", map[i][j]);  // Imprime el valor en la posición (i, j)
                }
                printf("\n");  // Nueva línea después de imprimir cada fila
            }
    uint16_t pattern = 0b1101101101101101; // Patrón binario de 16 bits
    for (int i = 0; i < DISP_CANT_X_DOTS; i++) {
        matriz[2][i] = (pattern >> (15 - i)) & 1; // Desplazar el patrón y colocar en la fila 3
    }      
}

/*-----Handle Menu Raspberry Pi-----*/
uint8_t handle_menu_raspy(frog_t *frog_position) 
{
    uint8_t choice = 0;
    uint8_t running = 1;
    joy_init();

    while (running) 
    {
        if (choice == 0) 
        {
            choice = ShowMenu(); // Mostrar el menú principal
        }
        else if (choice == 1) // Jugar
        {
            sleep(1);
            frog_position->x = 7;
            frog_position->y = 15;         
            frog_position->life = 3;       
            frog_position->playing_game = 1; 

            uint8_t game_running = 1;
            while (game_running) 
            {
                if (game_loop_raspy(frog_position) == 0) 
                {
                    choice = 0;
                    game_running = 0;
                }
            }

            frog_position->x = 7;
            frog_position->y = 15;
            frog_position->life = 3;       
            frog_position->playing_game = 1;
        }
        else if (choice == 2) 
        {
            printf("Saliendo del juego. ¡Hasta pronto!\n");
            running = 0;
            disp_clear();
            disp_update();
        }
        else
        {
            printf("Opción no válida.\n");
            choice = 0;
        }
    }
    return 0;
}

uint8_t game_loop_raspy(frog_t *frog_position)
{
    uint8_t game_status = 1; 

    while (frog_position->playing_game) 
    {
        joyinfo_t joy = joy_read();

        uint8_t frog_x = (uint8_t)get_frog_x(frog_position);
        uint8_t frog_y = (uint8_t)get_frog_y(frog_position);

        printf("Frog Position: (%d, %d) Frog life: %d\n", frog_x, frog_y, get_frog_lives(frog_position));
        printf("Frog Arrivals: %d\n", get_frog_arrivals(frog_position));
        printf("matriz: %d\n", matriz[frog_x][frog_y]);

        uint8_t row = 12 - (uint8_t)((-(get_frog_y(frog_position) - 11.96)) / 0.96);
        process_row_movements(frog_position, row);
        screen_raspy(frog_position); 
        update_frog_position(frog_position); 

        if (check_collision(frog_position)) 
        {
            // La colisión se maneja dentro de check_collision
        }
        if (detect_arrival_raspy(frog_position)) 
        {
            set_frog_arrivals(frog_position, get_frog_arrivals(frog_position) + 1);
            frog_position->x = 7;
            frog_position->y = 15;
        }
        if (get_frog_lives(frog_position) == 0) 
        {
            ShowGameOver();
            return 0; 
        }
        if (get_frog_arrivals(frog_position) == 5) 
        {
            pass_level(frog_position);
        }

        if (joy.sw == J_PRESS)
        {
            frog_position->paused_state = 1;
            uint8_t choice = ShowCONT();

            if (choice == 1)
            {
                frog_position->paused_state = 0;

                // En lugar de un while bloqueante, verificamos sin frenar la ejecución
                while ((joy = joy_read()).sw == J_PRESS) 
                {
                    usleep(10000);  // Pequeña espera de 10ms para no consumir CPU
                }
            }
            else 
            {
                return 0;
            }   
        }
    }
    return game_status;
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
