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
*                                PROTOTYPES                                *
***************************************************************************/

/*----- Function Initialize_game -----*/
// Función para inicializar el estado del juego
void initialize_game_state(frog_t *frog_position);

#ifdef PC
    /*-----INCLUDE-----*/
    #include "../Frontend/Frontend_Allegro/allegro.h"
    /*-----PROTOTYPES-----*/

    /*-----Function initialize_allegro_resources-----*/
    // Función para inicializar los recursos de Allegro
    void initialize_allegro_resources(AllegroResources *resources_for_main, ALLEGRO_EVENT_QUEUE **event_queue);

    /*-----Function handle_menu_allegro-----*/
    // Función para manejar el menú de Allegro
    void handle_menu_allegro(AllegroResources *resources_for_main, ALLEGRO_EVENT_QUEUE *event_queue, frog_t *frog_position, map_t map);
    
    /*-----Function game_loop_allegro-----*/
    // Función para el bucle del juego en Allegro
    void game_loop_allegro(frog_t *frog_position, AllegroResources *resources_for_main, ALLEGRO_EVENT_QUEUE *event_queue, map_t map);
    
    /*-----Function handle_game_over-----*/
    // Función para manejar el fin del juego en Allegro
    void handle_game_over(frog_t *frog_position, AllegroResources *resources_for_main, ALLEGRO_EVENT_QUEUE *event_queue, map_t map);
#endif

#ifdef RASPBERRY_PI
    #include <wiringPi.h>
    #include "../Frontend/Frontend_Raspberry/raspberry.h"
    void initialize_raspy_resources();
    void handle_menu_raspy(frog_t *frog_position);
    uint8_t game_loop_raspy(frog_t *frog_position);
    uint8_t check_collision(frog_t *frog_position);
    void move_frog_with_log(frog_t *frog_position);
    void update_frog_points(frog_t *frog_position);
    #define BUZZER_PIN 1
#endif

/*----- Function Process_row_movements -----*/
// Función para procesar los movimientos de las filas
void process_row_movements(frog_t *frog_position, uint8_t row);

#endif /* LOGIC_H */
