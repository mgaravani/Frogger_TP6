#include "frog.h"

// Función para inicializar la rana con valores predeterminados
void init_frog(frog_t *frog, float x, float y, uint8_t state, uint8_t vidas, int16_t puntos, int8_t llegadas) {
    frog->x = x;
    frog->y = y;
    frog->state = state;
    frog->vidas = vidas;
    frog->puntos = puntos;
    frog->llegadas = llegadas;
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

uint8_t get_frog_vidas(const frog_t *frog) {
    return frog->vidas;
}

int16_t get_frog_puntos(const frog_t *frog) {
    return frog->puntos;
}

int8_t get_frog_llegadas(const frog_t *frog) {
    return frog->llegadas;
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

void set_frog_vidas(frog_t *frog, uint8_t vidas) {
    frog->vidas = vidas;
}

void set_frog_puntos(frog_t *frog, int16_t puntos) {
    frog->puntos = puntos;
}

void set_frog_llegadas(frog_t *frog, int8_t llegadas) {
    frog->llegadas = llegadas;
}

// Funciones para actualizar valores de forma incremental
void increase_frog_puntos(frog_t *frog, int16_t puntos) {
    frog->puntos += puntos;
}

void decrease_frog_vidas(frog_t *frog, uint8_t vidas) {
    if (frog->vidas > vidas) {
        frog->vidas -= vidas;
    } else {
        frog->vidas = 0; // Evita valores negativos
    }
}

void increase_frog_llegadas(frog_t *frog) {
    frog->llegadas++;
}

// Función para mover la rana
void move_frog(frog_t *frog, float dx, float dy) {
    frog->x += dx;
    frog->y += dy;
}
