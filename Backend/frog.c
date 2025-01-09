#include "frog.h"

// Función para inicializar la rana con valores predeterminados
void init_frog(frog_t *frog, float x, float y, uint8_t state, uint8_t lives, int16_t points, int8_t arrivals) {
    frog->x = x;
    frog->y = y;
    frog->state = state;
    frog->lives = lives;
    frog->points = points;
    frog->arrivals = arrivals;
}

// Funciones para obtener los valores
float get_frog_x(const frog_t *frog) {
    return frog->x;
}

float get_frog_y(const frog_t *frog) {
    return frog->y;
}

uint8_t get_frog_state(const frog_t *frog) {
    return frog->state;
}

uint8_t get_frog_lives(const frog_t *frog) {
    return frog->lives;
}

int16_t get_frog_points(const frog_t *frog) {
    return frog->points;
}

int8_t get_frog_arrivals(const frog_t *frog) {
    return frog->arrivals;
}

// Funciones para modificar los valores
void set_frog_x(frog_t *frog, float x) {
    frog->x = x;
}

void set_frog_y(frog_t *frog, float y) {
    frog->y = y;
}

void set_frog_state(frog_t *frog, uint8_t state) {
    frog->state = state;
}

void set_frog_lives(frog_t *frog, uint8_t lives) {
    frog->lives = lives;
}

void set_frog_points(frog_t *frog, int16_t points) {
    frog->points = points;
}

void set_frog_arrivals(frog_t *frog, int8_t arrivals) {
    frog->arrivals = arrivals;
}

// Funciones para actualizar valores de forma incremental
void increase_frog_points(frog_t *frog, int16_t points) {
    frog->points += points;
}

void decrease_frog_lives(frog_t *frog, uint8_t lives) {
    if (frog->lives > lives) {
        frog->lives -= lives;
    } else {
        frog->lives = 0; // Evita valores negativos
    }
}

void increase_frog_arrivals(frog_t *frog) {
    frog->arrivals++;
}

// Función para mover la rana
void move_frog(frog_t *frog, float dx, float dy) {
    frog->x += dx;
    frog->y += dy;
}

// Limitadores
/*uint16_t frog_in_range(frog_t *frog){
    if (frog->x ){

    }
}*/