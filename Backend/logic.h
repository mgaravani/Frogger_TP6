/*------------INCLUDES-----------*/
#include "../Backend/frog.h"
#include "../Frontend/Frontend_Allegro/allegro.h"
#include "../Backend/map.h"
#include "../Backend/topScore.h"
#include "../Backend/delay.h"
#include <stdio.h>
#include <unistd.h>

/*----- Prototypes -----*/
void initialize_game(frog_t *frog_position, AllegroResources *resources_for_main, ALLEGRO_EVENT_QUEUE **event_queue);
void handle_menu(AllegroResources *resources_for_main, ALLEGRO_EVENT_QUEUE *event_queue, frog_t *frog_position, map_t map);
void game_loop(frog_t *frog_position, AllegroResources *resources_for_main, ALLEGRO_EVENT_QUEUE *event_queue, map_t map);
void process_row_movements(frog_t *frog_position, uint8_t row);
void handle_game_over(frog_t *frog_position, AllegroResources *resources_for_main, ALLEGRO_EVENT_QUEUE *event_queue, map_t map);