#ifndef FROG_H
#define FROG_H

#include <stdint.h>

// Definición de la estructura para la rana
typedef struct {
    float x;           // Coordenada x de la rana
    float y;           // Coordenada y de la rana
    uint8_t state;      // Estado de la rana
    uint8_t vidas;      // Cantidad de vidas
    int16_t puntos;     // Puntos acumulados por el jugador
    int8_t llegadas;    // Cantidad de veces que el jugador llegó al final
} frog_t;

// Funciones relacionadas con la rana

// Inicialización
void init_frog(frog_t *frog, float x, float y, uint8_t state, uint8_t vidas, int16_t puntos, int8_t llegadas);

// Accesores (getter)
float get_frog_x(const frog_t *frog);
float get_frog_y(const frog_t *frog);
uint8_t get_frog_state(const frog_t *frog);
uint8_t get_frog_vidas(const frog_t *frog);/*------PASAR A INGLES------*/
int16_t get_frog_puntos(const frog_t *frog);/*------PASAR A INGLES------*/
int8_t get_frog_llegadas(const frog_t *frog);/*------PASAR A INGLES------*/

// Modificadores (setter)
void set_frog_x(frog_t *frog, float x);
void set_frog_y(frog_t *frog, float y);
void set_frog_state(frog_t *frog, uint8_t state);
void set_frog_vidas(frog_t *frog, uint8_t vidas);/*------PASAR A INGLES------*/
void set_frog_puntos(frog_t *frog, int16_t puntos);/*------PASAR A INGLES------*/
void set_frog_llegadas(frog_t *frog, int8_t llegadas);/*------PASAR A INGLES------*/

// Incrementales
void increase_frog_puntos(frog_t *frog, int16_t puntos);/*------PASAR A INGLES------*/
void decrease_frog_vidas(frog_t *frog, uint8_t vidas);/*------PASAR A INGLES------*/
void increase_frog_llegadas(frog_t *frog);/*------PASAR A INGLES------*/

// Movimiento
void move_frog(frog_t *frog, float dx, float dy);

#endif // FROG_H