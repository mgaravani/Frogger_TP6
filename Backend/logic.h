#ifndef LOGIC_H
#define LOGIC_H

/*------------ INCLUDES -----------*/
#include "../Backend/frog.h"
#include "../Backend/map.h"
#include "../Backend/topScore.h"
#include "../Backend/delay.h"
#include <stdio.h>
#include <unistd.h>
//#define PC
#define RASPBERRY_PI
/*----- EXTERN VARIABLES -----*/
extern uint8_t directions[11]; // Vector de direcciones de las filas

/***************************************************************************
*                                PROTOTIPOS                                *
***************************************************************************/

/*----- Initialize_game -----*/
void initialize_game_state(frog_t *frog_position);

#ifdef PC
    #include "../Frontend/Frontend_Allegro/allegro.h"
    void initialize_allegro_resources(AllegroResources *resources_for_main, ALLEGRO_EVENT_QUEUE **event_queue);
    void handle_menu_allegro(AllegroResources *resources_for_main, ALLEGRO_EVENT_QUEUE *event_queue, frog_t *frog_position, map_t map);
    void game_loop_allegro(frog_t *frog_position, AllegroResources *resources_for_main, ALLEGRO_EVENT_QUEUE *event_queue, map_t map);
    void handle_game_over(frog_t *frog_position, AllegroResources *resources_for_main, ALLEGRO_EVENT_QUEUE *event_queue, map_t map);
#endif

#ifdef RASPBERRY_PI
    #include "../Frontend/Frontend_Raspberry/raspberry.h"
    void initialize_raspy_resources(frog_t *frog_position);
    void handle_menu_raspy(frog_t *frog_position, uint8_t matriz[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS]);
    uint8_t game_loop_raspy(frog_t *frog_position, uint8_t matriz[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS]);
#endif

/*----- Function Process_row_movements -----*/
void process_row_movements(frog_t *frog_position, uint8_t row);

#endif /* LOGIC_H */
