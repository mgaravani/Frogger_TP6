/*------------INCLUDES-----------*/
#include "../Backend/frog.h"
#include "../Frontend/Frontend_Allegro/allegro.h"
#include "../Backend/map.h"
#include "../Backend/topScore.h"
#include "../Backend/delay.h"
#include <stdio.h>
#include <unistd.h>

extern uint8_t directions[11]; // Vector de direcciones de las filas

/***************************************************************************
*                                                                          *
*                               PROTOTIPOS                                 *
*                                                                          *
***************************************************************************/

/*-----Initialize_game-----*/
// Función para inicializar el juego
void initialize_game(frog_t *frog_position, AllegroResources *resources_for_main, ALLEGRO_EVENT_QUEUE **event_queue);

/*-----Function Handle_menu-----*/
// Función para manejar el menú
void handle_menu(AllegroResources *resources_for_main, ALLEGRO_EVENT_QUEUE *event_queue, frog_t *frog_position, map_t map);

/*-----Function Game_loop-----*/
// Función para el loop del juego
void game_loop(frog_t *frog_position, AllegroResources *resources_for_main, ALLEGRO_EVENT_QUEUE *event_queue, map_t map);

/*-----Function Process_row_movements-----*/
// Función para procesar los movimientos de las filas
void process_row_movements(frog_t *frog_position, uint8_t row);

/*-----Function Handle_game_over-----*/
// Función para manejar el fin del juego
void handle_game_over(frog_t *frog_position, AllegroResources *resources_for_main, ALLEGRO_EVENT_QUEUE *event_queue, map_t map);