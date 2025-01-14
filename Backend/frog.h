#ifndef FROG_H
#define FROG_H

#include <stdint.h>
#include "map.h"


// LÍMITES Y CONSTANTES USADAS
#define FROG_LIMIT_UP 1.3
#define FROG_LIMIT_DOWN 11.0
#define FROG_LIMIT_LEFT 0.0
#define FROG_LIMIT_RIGHT 13.0
#define FROG_MOVE_STEP 0.96
#define FROG_SMALL_STEP 0.7

// Definición de la estructura para la rana
typedef struct {
    float x;           // Coordenada x de la rana
    float y;           // Coordenada y de la rana
    uint8_t state;      // Estado de la rana
    uint8_t lives;      // Cantidad de vidas
    int16_t points;     // Puntos acumulados por el jugador
    int8_t arrivals;    // Cantidad de veces que el jugador llegó al final
} frog_t;

// Funciones relacionadas con la rana

// Inicialización
void init_frog(frog_t *frog, float x, float y, uint8_t state, uint8_t lives, int16_t points, int8_t arrivals);

// Accesores (getter)
float get_frog_x(const frog_t *frog);
float get_frog_y(const frog_t *frog);
uint8_t get_frog_state(const frog_t *frog);
uint8_t get_frog_lives(const frog_t *frog);
int16_t get_frog_points(const frog_t *frog);
int8_t get_frog_arrivals(const frog_t *frog);

// Modificadores (setter)
void set_frog_x(frog_t *frog, float x);
void set_frog_y(frog_t *frog, float y);
void set_frog_state(frog_t *frog, uint8_t state);
void set_frog_lives(frog_t *frog, uint8_t lives);
void set_frog_points(frog_t *frog, int16_t points);
void set_frog_arrivals(frog_t *frog, int8_t arrivals);

// Incrementales
void increase_frog_points(frog_t *frog, int16_t points);
void decrease_frog_lives(frog_t *frog, uint8_t lives);
void increase_frog_arrivals(frog_t *frog);

// Movimiento
void handle_move_down(frog_t *frog);
void handle_move_up(frog_t *frog);
void handle_move_left(frog_t *frog);
void handle_move_right(frog_t *frog);

// Limitadores
uint16_t frog_in_range(map_t map,frog_t frog);

#endif // FROG_H