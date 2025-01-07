#ifndef FROG_H
#define FROG_H

#include <stdint.h>

// Definición de la estructura para la rana
typedef struct {
    int8_t x;           // Coordenada x de la rana
    int8_t y;           // Coordenada y de la rana
    uint8_t vidas;      // Cantidad de vidas
    int16_t puntos;     // Puntos acumulados por el jugador
    int8_t llegadas;    // Cantidad de veces que el jugador llegó al final
} frog_t;

// Funciones relacionadas con la rana

// Inicialización
void init_frog(frog_t *frog, int8_t x, int8_t y, uint8_t vidas, int16_t puntos, int8_t llegadas);

// Accesores (getter)
int8_t get_frog_x(const frog_t *frog);
int8_t get_frog_y(const frog_t *frog);
uint8_t get_frog_vidas(const frog_t *frog);
int16_t get_frog_puntos(const frog_t *frog);
int8_t get_frog_llegadas(const frog_t *frog);

// Modificadores (setter)
void set_frog_x(frog_t *frog, int8_t x);
void set_frog_y(frog_t *frog, int8_t y);
void set_frog_vidas(frog_t *frog, uint8_t vidas);
void set_frog_puntos(frog_t *frog, int16_t puntos);
void set_frog_llegadas(frog_t *frog, int8_t llegadas);

// Incrementales
void increase_frog_puntos(frog_t *frog, int16_t puntos);
void decrease_frog_vidas(frog_t *frog, uint8_t vidas);
void increase_frog_llegadas(frog_t *frog);

// Movimiento
void move_frog(frog_t *frog, int8_t dx, int8_t dy);

#endif // FROG_H