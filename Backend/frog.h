#ifndef FROG_H
#define FROG_H

/*------------INCLUDES-----------*/
#include <stdint.h>
#include "map.h"


/*-----LÍMITES Y CONSTANTES USADAS-----*/
#define FROG_LIMIT_UP 1.3
#define FROG_LIMIT_DOWN 11.0
#define FROG_LIMIT_LEFT 0.0
#define FROG_LIMIT_RIGHT 13.0
#define FROG_MOVE_STEP 0.96
#define FROG_SMALL_STEP 0.7

/*-----STRUCTS-----*/
// Definición de la estructura para la rana
typedef struct {
    float x;           // Coordenada x de la rana
    float y;           // Coordenada y de la rana
    uint8_t state;      // Estado de la rana
    uint8_t life;      // Estado de vida de la rana
    uint8_t move;      // Estado de movimiento segun fila
    uint8_t lives;      // Cantidad de vidas
    int16_t points;     // Puntos acumulados por el jugador
    int8_t arrivals;    // Cantidad de veces que el jugador llegó al final
} frog_t;

/*-----------PROTOTYPES--------*/

/***************************************************************************
*                                                                          *
*                  FUNCIONES RELACIONADAS CON LA RANA                      *
*                                                                          *
***************************************************************************/

/*-----init_frog-----*/
// Función para inicializar la rana
void init_frog(frog_t *frog, float x, float y, uint8_t state, uint8_t life, uint8_t lives, int16_t points, int8_t arrivals, int8_t move);


/******************************
*     ACCESORES (GETTER)      *
******************************/

/*-----get_frog_x-----*/
// Función para obtener la coordenada x de la rana
float get_frog_x(const frog_t *frog);

/*-----get_frog_y-----*/
// Función para obtener la coordenada y de la rana
float get_frog_y(const frog_t *frog);

/*-----get_frog_state-----*/
// Función para obtener el estado de la rana
uint8_t get_frog_life(const frog_t *frog);

/*-----get_frog_move-----*/
// Función para obtener el estado de movimiento de la rana
uint8_t get_frog_move(const frog_t *frog);

/*-----get_frog_life-----*/
// Función para obtener el estado de vida de la rana
uint8_t get_frog_state(const frog_t *frog);

/*-----get_frog_lives-----*/
// Función para obtener la cantidad de vidas de la rana
uint8_t get_frog_lives(const frog_t *frog);

/*-----get_frog_points-----*/
// Función para obtener los puntos acumulados por el jugador
int16_t get_frog_points(const frog_t *frog);

/*-----get_frog_arrivals-----*/
// Función para obtener la cantidad de veces que el jugador llegó al final
int8_t get_frog_arrivals(const frog_t *frog);

/******************************
*   MODIFICADORES (SETTER)    *
******************************/

/*-----set_frog_x-----*/
// Función para modificar la coordenada x de la rana
void set_frog_x(frog_t *frog, float x);

/*-----set_frog_y-----*/
// Función para modificar la coordenada y de la rana
void set_frog_y(frog_t *frog, float y);

/*-----set_frog_state-----*/
// Función para modificar el estado de la rana
void set_frog_life(frog_t *frog, uint8_t life);

/*-----set_frog_move-----*/
// Función para modificar el estado de movimiento de la rana
void set_frog_move(frog_t *frog, uint8_t move);

/*-----set_frog_life-----*/
// Función para modificar el estado de vida de la rana
void set_frog_state(frog_t *frog, uint8_t state);

/*-----set_frog_lives-----*/
// Función para modificar la cantidad de vidas de la rana
void set_frog_lives(frog_t *frog, uint8_t lives);

/*-----set_frog_points-----*/
// Función para modificar los puntos acumulados por el jugador
void set_frog_points(frog_t *frog, int16_t points);

/*-----set_frog_arrivals-----*/
// Función para modificar la cantidad de veces que el jugador llegó al final
void set_frog_arrivals(frog_t *frog, int8_t arrivals);

/*-----set_frog_start-----*/
// Función para llevar a la rana al inicio
void set_frog_start(frog_t *frog);

/******************************
*       INCREMENTALES         *
******************************/

/*-----increase_frog_points*/
// Función para incrementar los puntos acumulados por el jugador
void increase_frog_points(frog_t *frog, int16_t points);

/*-----decrease_frog_lives-----*/
// Función para decrementar la cantidad de vidas de la rana
void decrease_frog_lives(frog_t *frog, uint8_t lives);

/*-----increase_frog_arrivals-----*/
// Función para incrementar la cantidad de veces que el jugador llegó al final
void increase_frog_arrivals(frog_t *frog);

/******************************
*         MOVIMIENTO          *
******************************/

/*-----handle_move_down-----*/
// Función para mover la rana hacia abajo
void handle_move_down(frog_t *frog);

/*-----handle_move_up-----*/
// Función para mover la rana hacia arriba
void handle_move_up(frog_t *frog);

/*-----handle_move_left-----*/
// Función para mover la rana hacia la izquierda
void handle_move_left(frog_t *frog);

/*-----handle_move_right-----*/
// Función para mover la rana hacia la derecha
void handle_move_right(frog_t *frog);

/******************************
*        LIMITADORES          *
******************************/

/*-----frog_in_range-----*/
// Función para verificar si la rana está en rango de colisión
uint16_t frog_in_range(map_t map,frog_t *frog);

/******************************
*      ESTADO DE VIDA         *
******************************/

/*-----frog_life_state-----*/
// Funcion para analizar el estado de vida de la rana
void frog_life_state(frog_t *frog);

#endif // FROG_H