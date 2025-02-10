/*------------INCLUDES-----------*/
#include "../Backend/logic.h"

/*----- Functions -----*/

/*-----Function Initialize_game-----*/
// Función para inicializar el estado del juego
void initialize_game_state(frog_t *frog_position) 
{
    // Inicializar la rana con los valores iniciales
    init_frog(frog_position, 7, 11.98, 0, 1, 3, 0, 0, 0, 0, 0, 1);
    
    // Inicializar estados adicionales
    frog_position->pass_level_state = 0;
    frog_position->paused_state = 0; // DEBERÍA IR INCLUIDO EN LA FUNCIÓN DE INIT_FROG
    frog_position->playing_game = 1;
    frog_position->actual_row = ROWS - 1;
    
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

/*-----Function Initialize Allegro Resources-----*/
// Función para inicializar los recursos de Allegro
void initialize_allegro_resources(AllegroResources *resources_for_main, ALLEGRO_EVENT_QUEUE **event_queue) 
{
    *resources_for_main = allegro_init(map);
    *event_queue = init_events(resources_for_main->display);
}

/*-----Function Handle Menu Allegro-----*/
// Función para manejar el menú de Allegro
void handle_menu_allegro(AllegroResources *resources_for_main, ALLEGRO_EVENT_QUEUE *event_queue, frog_t *frog_position, map_t map) 
{
    while (resources_for_main->menu_state == 1) 
    {
        events_managment(resources_for_main, event_queue, frog_position, map);
        allegro_menu(resources_for_main);
    }
}

/*-----Function Game Loop Allegro-----*/
// Función para el bucle del juego en Allegro
void game_loop_allegro(frog_t *frog_position, AllegroResources *resources_for_main, ALLEGRO_EVENT_QUEUE *event_queue, map_t map)
{
    while (frog_position->playing_game == 1) 
    {
        uint16_t row = 12 - (uint16_t)((-(get_frog_y(frog_position) - 11.96)) / 0.96);
        events_managment(resources_for_main, event_queue, frog_position, map);
        process_row_movements(frog_position, row);
        if (detect_arrival(frog_position, map))  // Si la rana llega a la meta
        {
            set_frog_arrivals(frog_position, get_frog_arrivals(frog_position) + 1);
            set_frog_start(frog_position);
        }
        if (get_frog_lives(frog_position) == 0) // Si la rana se queda sin vidas
        {
            handle_game_over(frog_position, resources_for_main, event_queue, map);
        }
        if (get_frog_arrivals(frog_position) == 5) // Si la rana llega a las 5 metas
        {
            pass_level(frog_position);
        }
        frog_in_range(map, frog_position);
        Screen(resources_for_main, map, frog_position);
    }
}

/*-----Function Handle Game Over Allegro-----*/
// Función para manejar el fin del juego en Allegro
void handle_game_over(frog_t *frog_position, AllegroResources *resources_for_main, ALLEGRO_EVENT_QUEUE *event_queue, map_t map) 
{
    resources_for_main->menu_state = 1;
    resources_for_main->selected_option = 1;
    resources_for_main->name_state = 1;
    resources_for_main->highscores_state = 1;
    resources_for_main->final_points = get_frog_points(frog_position);

    player_t players[MAX_PLAYERS];
    loadScores("highscores.txt", players);
    enter_player_name(event_queue, resources_for_main);

    player_t newPlayer;
    strcpy(newPlayer.name, resources_for_main->player_name);
    newPlayer.score = get_frog_points(frog_position);
    newScore(players, newPlayer);
    saveScores("highscores.txt", players);

    FILE* pointer = fopen("highscores.txt", "r");
    if (pointer == NULL) 
    {
        fprintf(stderr, "Error: no se pudo abrir el archivo de highscores.\n");
    }

    while (resources_for_main->highscores_state == 1) 
    {
        events_managment(resources_for_main, event_queue, frog_position, map);
        menu_highscores(pointer, resources_for_main);
    }
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
      
}

/*-----Handle Menu Raspberry Pi-----*/
void handle_menu_raspy(frog_t *frog_position) 
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
            frog_position->y = 14; // Reiniciar la posición de la rana         
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
            restart(frog_position);
            initialize_matrix();
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
}

/*-----Game Loop Raspberry Pi-----*/
uint8_t game_loop_raspy(frog_t *frog_position)
{
    while (frog_position->playing_game == 1) 
    {
        update_frog_points(frog_position);
        joyinfo_t joy = joy_read();
        uint8_t frog_y = (uint8_t)get_frog_y(frog_position);
        //move_frog_with_log(frog_position);  // Mover la rana con los troncos 
        process_row_movements(frog_position, frog_y - 2);
        update_frog_position(frog_position);
        screen_raspy(frog_position);
        printf("move: %d \n", get_frog_move(frog_position));
        if (check_collision(frog_position)) 
        {
            // La colisión se maneja dentro de check_collision
        }
        if (detect_arrival_raspy(frog_position)) 
        {
            set_frog_arrivals(frog_position, get_frog_arrivals(frog_position) + 1);
            frog_position->x = 7;
            frog_position->y = 14; // Reiniciar la posición de la rana
        }
        if (get_frog_lives(frog_position) == 0) 
        {
            ShowGameOver();
            ShowNumber(get_frog_points(frog_position));
            initialize_matrix();
            return 0; 
        }
        if (get_frog_arrivals(frog_position) == 5) 
        {
            pass_level(frog_position);
        }

        if (joy.sw == J_PRESS || frog_position->paused_state == 1)
        {
            frog_position->paused_state = 1;//cambio el estado de pausa
            printf("Frog: %d\n", frog_position->paused_state);
            uint8_t choice = 0;
            choice = ShowCONT();
            

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
    return 0;
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
        frog_position->y = 14; // Reiniciar la posición de la rana
        return 1; // Hubo colisión
    }
    return 0; // No hubo colisión
}

void move_frog_with_log(frog_t *frog_position) {
    uint8_t frog_x = get_frog_x(frog_position);
    uint8_t frog_y = get_frog_y(frog_position);
    
    // Verifica si la rana está entre las filas 2 y 6 
    if (frog_y >= 2 && frog_y <= 6) {
         if (waiting_time(frog_position->levels, frog_y-2)) 
        {
            // Verifica si está sobre un tronco (valor 0 en la matriz)
            if (matriz[frog_y][frog_x] == 0) {
                // Mueve la rana junto con el tronco
                // Verifica los límites del movimiento (previene desbordamiento fuera del área de la matriz)
                if ((frog_x + 1 <= 15) && directions[frog_y]) {  // Movimiento hacia la derecha
                    set_frog_x(frog_position, frog_x + 1);
                } else if ((frog_x - 1 >= 0) && !directions[frog_y]) {  // Movimiento hacia la izquierda
                    set_frog_x(frog_position, frog_x - 1);
                }
            }
        }
    }
}

void update_frog_points(frog_t *frog_position) 
{
    uint8_t new_row = (uint8_t)get_frog_y(frog_position);  
    // Si la rana ha alcanzado la fila 2, reinicia las filas visitadas manualmente
    if (new_row == 2) 
    {
        for (uint8_t i = 0; i < sizeof(frog_position->reached_rows); i++) 
        {
            frog_position->reached_rows[i] = 0;
        }

        // Sumar puntos adicionales por llegar a la meta (opcional)
    }

    // Verifica si la rana ha alcanzado una nueva fila no visitada
    if (new_row < frog_position->actual_row) 
    {
        uint8_t row_index = frog_position->actual_row;  

        // Si no ha sido alcanzada antes, suma puntos
        if (frog_position->reached_rows[row_index] == 0) 
        {
            frog_position->points += 10; // Ajusta el puntaje por fila
            frog_position->reached_rows[row_index] = 1;
        }

        // Actualiza la fila actual de la rana
        frog_position->actual_row = new_row;
    }
}





#endif // RASPBERRY_PI

/*-----Common Function for Both Platforms-----*/

/*-----Function Process_row_movements-----*/
// Función para procesar los movimientos de las filas
void process_row_movements(frog_t *frog_position, uint8_t row) 
{
    for (int fila = 1; fila < 12; fila++) 
    {
        // Verifica si el tiempo ha pasado y la fila debe moverse
        if (waiting_time(frog_position->levels, fila)) 
        {
            //printf("Fila: %d - waiting_time pasó\n", fila);

            if ((row == fila) && (get_frog_move(frog_position) == 1)) 
            {
                printf("entre\n"); 
                printf("x:%d y:%d\n", (uint8_t)get_frog_x(frog_position), (uint8_t)get_frog_y(frog_position));
                printf("row: %d\n", row);
                //printf("Fila: %d - La rana está en la fila correcta y está lista para moverse\n", fila);
                
                // Verifica si la rana está a punto de salirse de los límites
                if ((((uint8_t)(get_frog_x(frog_position)) + 1 > 13) && directions[fila]) ||
                    (((uint8_t)(get_frog_x(frog_position)) - 1 < 1) && (!directions[fila]))) 
                {
                    printf("Fila: %d - La rana se salió de los límites, perdiendo vida\n", fila);
                    set_frog_life(frog_position, 0);
                    set_frog_dead(frog_position, 1);
                } 
                else 
                {
                    // Mueve la rana en la dirección correcta 
                    set_frog_x(frog_position, get_frog_x(frog_position) + (directions[fila+2] ? 1 : -1));
                    printf("Fila: %d - Mueve la rana a la posición X: %f\n", fila, get_frog_x(frog_position));
                }
            }
            
            // Verifica si el juego no está pausado para mover las filas
            if (frog_position->paused_state == 0) 
            {
                //printf("Fila: %d - El juego no está pausado, desplazando fila\n", fila);
                shift_row(fila, directions[fila]);
            }
        }
        else
        {
            //printf("Fila: %d - waiting_time no pasó aún\n", fila);
        }
    }
}

