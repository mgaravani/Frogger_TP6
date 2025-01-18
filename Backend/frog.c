/*------------INCLUDES-----------*/
#include "frog.h"
#include "map.h"
#include <stdio.h>


/*------Function init_frog------*/
// Función para inicializar la rana con valores predeterminados
void init_frog(frog_t *frog, float x, float y, uint8_t state, uint8_t life, uint8_t lives, int16_t points, int8_t arrivals, int8_t move) 
{
  frog->x = x;
  frog->y = y;
  frog->life = life;
  frog->state = state;
  frog->lives = lives;
  frog->points = points;
  frog->arrivals = arrivals;
  frog->move = move;
}

/***************************************************************************
*                                                                          *
*                  FUNCIONES PARA OBTENER LOS VALORES                      *
*                                                                          *
***************************************************************************/

/*-----Function get_frog_x-----*/
// Función para obtener la coordenada x de la rana
float get_frog_x(const frog_t *frog) 
{
  return frog->x;
}

/*-----Function get_frog_y-----*/
// Función para obtener la coordenada y de la rana
float get_frog_y(const frog_t *frog) 
{
  return frog->y;
}

/*-----Function get_frog_state-----*/
// Función para obtener el estado de la rana
uint8_t get_frog_state(const frog_t *frog) 
{
  return frog->state;
}

/*-----Function get_frog_move-----*/
// Función para obtener el estado de movimiento de la rana
uint8_t get_frog_move(const frog_t *frog) 
{
  return frog->move;
}

/*-----Function get_frog_life-----*/
// Función para obtener el estado de vida de la rana
uint8_t get_frog_life(const frog_t *frog) 
{
  return frog->life;
}

/*-----Function get_frog_lives-----*/
// Función para obtener la cantidad de vidas de la rana
uint8_t get_frog_lives(const frog_t *frog) 
{
  return frog->lives;
}

/*-----Function get_frog_points-----*/
// Función para obtener los puntos acumulados por el jugador
int16_t get_frog_points(const frog_t *frog) 
{
  return frog->points;
}

/*-----Function get_frog_arrivals-----*/
// Función para obtener la cantidad de veces que el jugador llegó al final
int8_t get_frog_arrivals(const frog_t *frog) 
{
  return frog->arrivals;
}

/***************************************************************************
*                                                                          *
*                  FUNCIONES PARA MODIFICAR LOS VALORES                    *
*                                                                          *
***************************************************************************/

/*-----Function set_frog_x-----*/
// Función para modificar la coordenada x de la rana
void set_frog_x(frog_t *frog, float x) 
{
  frog->x = x;
}

/*-----Function set_frog_y-----*/
// Función para modificar la coordenada y de la rana
void set_frog_y(frog_t *frog, float y) 
{

  frog->y = y;
}

/*-----Function set_frog_state-----*/
// Función para modificar el estado de la rana
void set_frog_state(frog_t *frog, uint8_t state) 
{
  frog->state = state;
}

/*-----Function set_frog_move-----*/
// Función para modificar el estado de movimiento de la rana
void set_frog_move(frog_t *frog, uint8_t move) 
{
  frog->move = move;
}

/*-----Function set_frog_life-----*/
// Función para modificar el estado de vida de la rana
void set_frog_life(frog_t *frog, uint8_t life) 
{
  frog->life = life;
}

/*-----Function set_frog_lives-----*/
// Función para modificar la cantidad de vidas de la rana
void set_frog_lives(frog_t *frog, uint8_t lives) 
{
  frog->lives = lives;
}

/*-----Function set_frog_points-----*/
// Función para modificar los puntos acumulados por el jugador
void set_frog_points(frog_t *frog, int16_t points) 
{
  frog->points = points;
}

/*-----Function set_frog_arrivals-----*/
// Función para modificar la cantidad de veces que el jugador llegó al final
void set_frog_arrivals(frog_t *frog, int8_t arrivals) 
{
  frog->arrivals = arrivals;
}

/***************************************************************************
*                                                                          *
*       FUNCIONES PARA ACTUALIZAR VALORES DE FORMA INCREMENTAL             *
*                                                                          *
***************************************************************************/

/*-----Function increase_frog_points-----*/
// Función para incrementar los puntos acumulados por el jugador
void increase_frog_points(frog_t *frog, int16_t points) 
{
  frog->points += points;
}

/*-----Function decrease_frog_lives-----*/
// Función para decrementar la cantidad de vidas de la rana
void decrease_frog_lives(frog_t *frog, uint8_t lives) 
{
  if (frog->lives > lives) 
  {
    frog->lives -= lives;
  } 
  else 
  {
    frog->lives = 0; // Evita valores negativos
  }
}

/*-----Function increase_frog_arrivals-----*/
// Función para incrementar la cantidad de veces que el jugador llegó al final
void increase_frog_arrivals(frog_t *frog) 
{
  frog->arrivals++;
}

/***************************************************************************
*                                                                          *
*          FUNCIONES PARA EL MOVIMIENTO y ESTADO DE LA RANA                *
*                                                                          *
***************************************************************************/

/*-----Function handle_move_down-----*/
// Función para mover la rana hacia abajo
void handle_move_down(frog_t *frog) 
{
  if (get_frog_y(frog) <= FROG_LIMIT_DOWN) 
  {
    set_frog_y(frog, get_frog_y(frog) + FROG_MOVE_STEP);
    set_frog_state(frog, 1); // Mostrar rana hacia abajo
  }
}

/*-----Function handle_move_up-----*/
// Función para mover la rana hacia arriba
void handle_move_up(frog_t *frog) 
{
  if (get_frog_y(frog) > FROG_LIMIT_UP) 
  {
    set_frog_y(frog, get_frog_y(frog) - FROG_MOVE_STEP);
    set_frog_state(frog, 0); // Mostrar rana hacia arriba
  }
}

/*-----Function set_frog_start-----*/
// Funcion para reiniciar la posicion de la rana
void set_frog_start(frog_t *frog) 
{
  set_frog_x(frog, 7);
  set_frog_y(frog, 11.96f);
}

/*-----Function handle_move_left-----*/
// Función para mover la rana hacia la izquierda
void handle_move_left(frog_t *frog) 
{
  if (get_frog_x(frog) > 1) 
  {
    set_frog_x(frog, get_frog_x(frog) - 1.0);
    set_frog_state(frog, 2); // Mostrar rana hacia la izquierda
  }
  else if (get_frog_x(frog) == FROG_LIMIT_LEFT) 
  {
    set_frog_x(frog, get_frog_x(frog) - FROG_SMALL_STEP); // Es un paso distinto para que la rana siga quedando bien centrada
    set_frog_state(frog, 2); // Mostrar rana hacia la izquierda
  }
}

/*-----Function handle_move_right-----*/
// Función para mover la rana hacia la derecha
void handle_move_right(frog_t *frog) 
{

  if (get_frog_x(frog) == FROG_LIMIT_LEFT) 
  {
    set_frog_x(frog, get_frog_x(frog) + FROG_SMALL_STEP); // Es un paso distinto para que la rana siga quedando bien centrada
    set_frog_state(frog, 3); // Mostrar rana hacia la derecha
  }
  else if (get_frog_x(frog) < FROG_LIMIT_RIGHT) 
  {
    set_frog_x(frog, get_frog_x(frog) + 1.0);
    set_frog_state(frog, 3); // Mostrar rana hacia la derecha
  }
}

/*-----Function frog_in_range-----*/
// Función para verificar si la rana está en rango de colisión
uint16_t frog_in_range(map_t *map, frog_t *frog) 
{
  int col = (int)(get_frog_x(frog) + 3); // Ajusto las columnas
  int row = 12 - (int)(((-(get_frog_y(frog) - 11.96)) / 0.96)); // Ajusto las filas

  // Rango fijo: filas [0, 12], columnas [3, 15]
  for (int i = 0; i < ROWS; i++) // Iterar por las filas (0 a ROWS-1)
  {
    for (int j = 3; j <= 15; j++) // por las columnas (3 a 15)
    {       
      if ((*map)[i][j] == 1 && (row > 5)) // Si estoy después de la mitad del mapa, solo veo colisiones
      {
        if ((i == row) && (j == col)) // Si la col y fila actual concuerda con la rana
        {
          set_frog_life(frog, 0);
          frog_life_state(frog);
          set_frog_start(frog);
        }
      }
      else if (((*map)[i][j] == 1) && (row <= 5 && row > 0)) // Si estoy en la primera mitad, puede ser tronco o tortuga
      {
        if ((i == row) && (j == col))
        {
          set_frog_move(frog, 1); // Flag para que la rana se desplace lo mismo que la fila en la dirección
        }
      }
      else if (((*map)[i][j] == 0) && (row <= 5 && row > 0)) 
      {
        if ((i == row) && (j == col))
        {
          set_frog_life(frog, 0);
          set_frog_move(frog, 0);
          frog_life_state(frog);
          set_frog_start(frog);
        }
      }
      else
      {
        set_frog_move(frog, 0);
        set_frog_life(frog, 1);
      }
    }
  }
  return 0;
}


/*-----Function frog_life_state*/
// Funcion para analizar el estado de vida de la rana
void frog_life_state(frog_t *frog) 
{
  if (get_frog_life(frog) == 0) 
  {
    decrease_frog_lives(frog, 1);
  }
}

/*------- Detectar llegada de la Rana ---------*/
uint16_t detect_arrival(frog_t *frog, map_t *map)
{
    // Ajusta las columnas y las filas en función de la posición de la rana
    int frog_col = (int)(get_frog_x(frog) + 3);
    int frog_row = 12 - (int)(((-(get_frog_y(frog) - 11.96)) / 0.96));

    // Si la rana está en la fila 0 y la posición tiene un 1
    if (frog_row == 0 && (*map)[frog_row][frog_col] == 1) 
    {
        (*map)[frog_row][frog_col] = 0; // Marca la posición como visitada
        return 1; // Indica que la rana llegó a esta posición
    }

    return 0; // No llegó o no se cumplen las condiciones
}