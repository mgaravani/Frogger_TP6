/*------------INCLUDES-----------*/
#include "../Backend/logic.h"


/*----- Functions -----*/

/*-----Initialize_game-----*/
// Función para inicializar el juego
void initialize_game(frog_t *frog_position, AllegroResources *resources_for_main, ALLEGRO_EVENT_QUEUE **event_queue) 
{
    init_frog(frog_position, 7, 11.96, 0, 1, 3, 0, 0, 0, 0, 0, 1);
    frog_position->pass_level_state = 0;
    frog_position->paused_state = 0; //DEBERIA IR INCLUIDO EN LA FUNCION DE INIT_FROG
    frog_position->playing_game = 1;
    frog_position->actual_row = ROWS - 1;
    for (uint8_t i = 0; i < ROWS; i++) 
    {
        frog_position->reached_rows[i] = 0;
    };
    *resources_for_main = allegro_init(map);
    *event_queue = init_events(resources_for_main->display);
    initialize_matrix();
}

/*-----Function Handle_menu-----*/
// Función para manejar el menú
void handle_menu(AllegroResources *resources_for_main, ALLEGRO_EVENT_QUEUE *event_queue, frog_t *frog_position, map_t map) 
{
    while (resources_for_main->menu_state == 1) 
    {
        events_managment(resources_for_main, event_queue, frog_position, map);
        allegro_menu(resources_for_main);
    }
}

/*-----Function Game_loop-----*/
// Función para el loop del juego
void game_loop(frog_t *frog_position, AllegroResources *resources_for_main, ALLEGRO_EVENT_QUEUE *event_queue, map_t map)
{
    while (frog_position->playing_game == 1) 
    {
        int row = 12 - (int)((-(get_frog_y(frog_position) - 11.96)) / 0.96);
        events_managment(resources_for_main, event_queue, frog_position, map);
        process_row_movements(frog_position, row);
        if (detect_arrival(frog_position, &map)) 
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
        frog_in_range(&map, frog_position);
        Screen(resources_for_main, map, frog_position);
    }
}

/*-----Function Process_row_movements-----*/
// Función para procesar los movimientos de las filas
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

/*-----Function Handle_game_over-----*/
// Función para manejar el fin del juego
void handle_game_over(frog_t *frog_position, AllegroResources *resources_for_main, ALLEGRO_EVENT_QUEUE *event_queue, map_t map) 
{
    resources_for_main->menu_state = 1;
    resources_for_main->selected_option = 1;
    resources_for_main->name_state = 1;
    resources_for_main->highscores_state = 1;
    player_t players[MAX_PLAYERS];
    loadScores("highscores.txt", players);
    enter_player_name(event_queue, resources_for_main);
    player_t newPlayer;
    strcpy(newPlayer.name, resources_for_main->player_name);
    newPlayer.score = get_frog_points(frog_position);
    newScore(players, newPlayer);
    saveScores("highscores.txt", players);
    FILE* pointer = fopen("highscores.txt", "r");
    if (pointer == NULL) {
        fprintf(stderr, "Error: no se pudo abrir el archivo de highscores.\n");
    }
    while (resources_for_main->highscores_state == 1) {
        events_managment(resources_for_main, event_queue, frog_position, map);
        menu_highscores(pointer, resources_for_main);
    }
}