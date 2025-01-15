#include "frog.h"
#include "map.h"
#include <stdio.h>

// Función para inicializar la rana con valores predeterminados
void init_frog(frog_t *frog, float x, float y, uint8_t state, uint8_t life, uint8_t lives, int16_t points, int8_t arrivals, int8_t move) {
  frog->x = x;
  frog->y = y;
  frog->life = life;
  frog->state = state;
  frog->lives = lives;
  frog->points = points;
  frog->arrivals = arrivals;
  frog->move = move;
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

uint8_t get_frog_move(const frog_t *frog) {
  return frog->move;
}

uint8_t get_frog_life(const frog_t *frog) {
  return frog->life;
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

void set_frog_move(frog_t *frog, uint8_t move) {
  frog->move = move;
}

void set_frog_life(frog_t *frog, uint8_t life) {
  frog->life = life;
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

// Funciones para el movimiento de la rana
void handle_move_down(frog_t *frog) {
  if (get_frog_y(frog) <= FROG_LIMIT_DOWN) {
    set_frog_y(frog, get_frog_y(frog) + FROG_MOVE_STEP);
    set_frog_state(frog, 1); // Mostrar rana hacia abajo
  }
}

void handle_move_up(frog_t *frog) {
  if (get_frog_y(frog) > FROG_LIMIT_UP) {
    set_frog_y(frog, get_frog_y(frog) - FROG_MOVE_STEP);
    set_frog_state(frog, 0); // Mostrar rana hacia arriba
  }
}

void set_frog_start(frog_t *frog) {
  set_frog_x(frog, 7);
  set_frog_y(frog, 11.96f);
}

void handle_move_left(frog_t *frog) {
  if (get_frog_x(frog) > 1) {
    set_frog_x(frog, get_frog_x(frog) - 1.0);
    set_frog_state(frog, 2); // Mostrar rana hacia la izquierda
  }
  else if (get_frog_x(frog) == FROG_LIMIT_LEFT) {
    set_frog_x(frog, get_frog_x(frog) - FROG_SMALL_STEP); // Es un paso distinto para que la rana siga quedando bien centrada
    set_frog_state(frog, 2); // Mostrar rana hacia la izquierda
  }
}

void handle_move_right(frog_t *frog) {

  if (get_frog_x(frog) == FROG_LIMIT_LEFT) {
    set_frog_x(frog, get_frog_x(frog) + FROG_SMALL_STEP); // Es un paso distinto para que la rana siga quedando bien centrada
    set_frog_state(frog, 3); // Mostrar rana hacia la derecha
  }
  else if (get_frog_x(frog) < FROG_LIMIT_RIGHT) {
    set_frog_x(frog, get_frog_x(frog) + 1.0);
    set_frog_state(frog, 3); // Mostrar rana hacia la derecha
  }
}

uint16_t frog_in_range(map_t map, frog_t *frog) {
  int col = (int)(get_frog_x(frog) + 3); // Ajusto las columnas
  int row = 12 - (int)(((-(get_frog_y(frog) - 11.96)) / 0.96)); // Ajusto las filas

  // Rango fijo: filas [0, 12], columnas [3, 15]
  for (int i = 0; i < ROWS; i++) // Iterar por las filas (0 a ROWS-1)
  {
    for (int j = 3; j <= 15; j++) {       // por las columnas (3 a 15)

      if (map[i][j] == 1 && (row > 5)) // Si estoy despues de la mitad del mapa, solo veo colisiones
      {
        if ((i == row) && (j == col)) // Si la col y fil actual concuerda con la rana
        {
          // HACER UNA FUNCION DE QUE LA RANA SE MUERE, QUE DESCUENTE VIDA, LLEVE AL INICIO Y TENGA ANIMACION DE MUERTE POR UNOS SEGUNDOS
          set_frog_life(frog, 0);
          set_frog_start(frog);
          // ACA VA EL REINICIO SI CHOCA, QUE VUELVA A EMPEZAR Y QUE DESCUENTE UNA VIDA //

        }
      }
      else if ((map[i][j] == 1) && (row <= 5 && row > 0)) // Si estoy en la primera mitad, puede ser tronco o tortuga
      {
        if ((i == row) && (j == col))
        {
          set_frog_move(frog, 1); // FLAG PARA QUE LA RANA SE DESPLACE LO MISMO QUE LA FILA EN LA DIRECCION
          // ACA VA EL REINICIO SI CHOCA, QUE VUELVA A EMPEZAR Y QUE DESCUENTE UNA VIDA //
        }
      }
      else if ((map[i][j] == 0) && (row <= 5 && row > 0)) {
        if ((i == row) && (j == col))
        {
          // HACER UNA FUNCION DE QUE LA RANA SE MUERE, QUE DESCUENTE VIDA, LLEVE AL INICIO Y TENGA ANIMACION DE MUERTE POR UNOS SEGUNDOS
          set_frog_life(frog, 0);
          set_frog_move(frog, 0);
          set_frog_start(frog);
          // ACA VA EL REINICIO SI CHOCA, QUE VUELVA A EMPEZAR Y QUE DESCUENTE UNA VIDA //
        }
      }
      else{
        set_frog_move(frog, 0);
        set_frog_life(frog, 1);
      }
    }
  }
  return (0);
}