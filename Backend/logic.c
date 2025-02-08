/*------------INCLUDES-----------*/
#include "../Backend/logic.h"

/*----- Functions -----*/

/*-----Initialize_game-----*/
void initialize_game_state(frog_t *frog_position) 
{
    init_frog(frog_position, 7, 11.96, 0, 1, 3, 0, 0, 0, 0, 0, 1);
    frog_position->pass_level_state = 0;
    frog_position->paused_state = 0; // DEBERÍA IR INCLUIDO EN LA FUNCIÓN DE INIT_FROG
    frog_position->playing_game = 1;
    frog_position->actual_row = ROWS - 1;
    
    for (uint8_t i = 0; i < ROWS; i++) 
    {
        frog_position->reached_rows[i] = 0;
    }
    
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
void initialize_raspy_resources(frog_t *frog_position) 
{
    disp_init();                
    disp_clear();               
    disp_update();              
    ShowFrogger();              
    joy_init();                 
}

/*-----Handle Menu Raspberry Pi-----*/
void handle_menu_raspy(frog_t *frog_position, uint8_t matriz[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS]) 
{
    uint8_t choice = 0;
    uint8_t running = 1;

    while (running) 
    {
        switch (choice) 
        {
            case 0:
                choice = ShowMenu();
                break;
            case 1:
                disp_clear();
                choice = game_loop_raspy(frog_position, matriz);
                break;
            case 2:
                printf("Saliendo del juego. ¡Hasta pronto!\n");
                running = 0;
                disp_clear();
                disp_update();
                break;
            case 3:
                choice = ShowCONT();
                break;
            default:
                printf("Opción no válida.\n");
                break;
        }
    }
}

/*-----Game Loop Raspberry Pi-----*/
uint8_t game_loop_raspy(frog_t *frog_position, uint8_t matriz[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS])
{
    while (frog_position->playing_game == 1) 
    {
        uint8_t row = 12 - get_frog_y(frog_position);
        process_row_movements(frog_position, row);
        if (detect_arrival(frog_position, map)) 
        {
            set_frog_arrivals(frog_position, get_frog_arrivals(frog_position) + 1);
            set_frog_start(frog_position);
        }
        if (get_frog_lives(frog_position) == 0) 
        {
            ShowGameOver();
        }
        if (get_frog_arrivals(frog_position) == 5) 
        {
            pass_level(frog_position);
        }
        frog_in_range(map, frog_position);
        screen_raspy(&frog_position, matriz);
    }
    return 0;
}
#endif // RASPBERRY_PI

/*-----Common Function for Both Platforms-----*/
void process_row_movements(frog_t *frog_position, uint8_t row) 
{
    for (int fila = 1; fila < 12; fila++) 
    {
        if (waiting_time(frog_position->levels, fila)) 
        {
            if ((row == fila) && (get_frog_move(frog_position) == 1)) 
            {
                if ((((int)(get_frog_x(frog_position)) + 1 > 13) && directions[fila]) ||
                    (((int)(get_frog_x(frog_position)) - 1 < 1) && (!directions[fila]))) 
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
