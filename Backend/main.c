/*------------INCLUDES-----------*/
#include "../Backend/frog.h"
#include "../Frontend/Frontend_Allegro/allegro.h"
#include "../Backend/map.h"
#include "delay.h"
#include <stdio.h>
#include <unistd.h>

/* FUNCION MAIN */
int main(void)
{
  extern map_t map; // Variable global de la matriz
  frog_t frog_position;
  init_frog(&frog_position, 7, 11.96, 0, 1, 3, 0, 0, 0); // Inicializo la rana
  AllegroResources resources_for_main = allegro_init(map); // Inicializa allegro
  ALLEGRO_EVENT_QUEUE *event_queue = init_events(resources_for_main.display); // Crea la cola de eventos
  //allegro_menu(&resources_for_main);
  initialize_matrix();

  while (1) // EN VEZ DE WHILE 1, QUE FUNCIONE MIENTRAS NO SE APRIETE LA TECLA ESCAPE O SALIR DEL JUEGO
  {
    int row = 12 - (int)(((-(get_frog_y(&frog_position) - 11.96)) / 0.96));
    events_managment(&resources_for_main, event_queue, &frog_position, map);


    // ESTE FOR HABRIA QUE HACERLO DENTRO DE ALGUNA FUNCION Y LLAMAR SOLO LA FUNCION CON EL NIVEL Y VIDAS //
    for (int fila = 0; fila < 6; fila++) // FOR PARA MOVER LAS DISTINTAS FILAS
    {

      // Desplazar fila par (de izquierda a derecha)
      if (waiting_time(5, 2 * fila)) // SI ES UNA FILA PAR
      {
        // SI LA FILA CONCUERDA CON LA POSICION DE LA RANA Y LA FLAG DE MOVERSE SE ACTIVA
        if ((row == (2 * fila)) && (get_frog_move(&frog_position) == 1)) 
        {
          if ((int)(get_frog_x(&frog_position)) + 1 > 13) // IF PARA MORIR SI SE VA DE LOS LIMITES
            // DESPUES HACER UNA FUNCION MAS PROLIJA....
          {
            set_frog_life(&frog_position, 0);
            set_frog_start(&frog_position);
          }
          // SINO LA DESPLAZA
          else set_frog_x(&frog_position, get_frog_x(&frog_position) + 1);

        }

        shift_row(2 * fila, 1); // Desplazar fila 0, 2, 4, 6, etc. a la derecha
      }
      // Desplazar fila impar (de derecha a izquierda)
      if (waiting_time(1, ((2 * fila) + 1))) // SI ES UNA FILA IMPAR
      {
        // SI LA FILA CONCUERDA CON LA POSICION DE LA RANA Y LA FLAG DE MOVERSE SE ACTIVA
        if ((row == ((2 * fila) + 1))  && (get_frog_move(&frog_position) == 1)) {
          if ((int)(get_frog_x(&frog_position)) - 1 < 1) { // IF PARA MORIR SI SE VA DE LOS LIMITES
            set_frog_life(&frog_position, 0);
            set_frog_start(&frog_position);
          }
          // SINO LA DESPLAZA
          else set_frog_x(&frog_position, get_frog_x(&frog_position) - 1);
        }
        shift_row((2 * fila) + 1, 0); // Desplazar fila 1, 3, 5, etc. a la izquierda
      }
      

      if(get_frog_lives(&frog_position) == 0) // SI LA RANA NO TIENE VIDAS, TERMINA EL JUEGO
      {
        resources_for_main.menu_state = 1;
        allegro_menu(&resources_for_main);
        return 0;
      }
      
    }
    //print_matrix();
    //usleep(900000);
    frog_in_range(map, &frog_position); // FUNCION QUE CHEQUEA QUE ESTE DENTRO DE LOS LIMITES
    Screen(&resources_for_main, map, &frog_position);
  }

  return 0;
}