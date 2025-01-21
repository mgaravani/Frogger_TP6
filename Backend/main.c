/*------------INCLUDES-----------*/
#include "../Backend/frog.h"
#include "../Frontend/Frontend_Allegro/allegro.h"
#include "../Backend/map.h"
#include "delay.h"
#include <stdio.h>
#include <unistd.h>

/*-----Function main-----*/
int main(void)
{
  extern map_t map; // Variable global de la matriz
  frog_t frog_position;
  int directions[11] = {0,1,0,1,1,0,0,0,1,0,1}; 
  init_frog(&frog_position, 7, 11.96, 0, 1, 3, 0, 0, 0, 0, 0, 1); // Inicializo la rana
  AllegroResources resources_for_main = allegro_init(map); // Inicializa allegro
  ALLEGRO_EVENT_QUEUE *event_queue = init_events(resources_for_main.display); // Crea la cola de eventos
  initialize_matrix(); // Inicializa la matriz

  // Mientras el estado del menu sea 1, se ejecuta el menu
  while(resources_for_main.menu_state == 1)
  { 
    events_managment(&resources_for_main, event_queue, &frog_position, map);
    allegro_menu(&resources_for_main);
  }

  
  while (1) // EN VEZ DE WHILE 1, QUE FUNCIONE MIENTRAS NO SE APRIETE LA TECLA ESCAPE O SALIR DEL JUEGO
  {
    int row = 12 - (int)(((-(get_frog_y(&frog_position) - 11.96)) / 0.96));
    events_managment(&resources_for_main, event_queue, &frog_position, map);

    // ESTE FOR HABRIA QUE HACERLO DENTRO DE ALGUNA FUNCION Y LLAMAR SOLO LA FUNCION CON EL NIVEL Y VIDAS //
    for (int fila = 1; fila < 7; fila++) // FOR PARA MOVER LAS DISTINTAS FILAS
    {
      // Desplazar fila par (de izquierda a derecha)
      if (waiting_time(frog_position.levels+4, 2 * fila)) // SI ES UNA FILA PAR
      {

        // SI LA FILA CONCUERDA CON LA POSICION DE LA RANA Y LA FLAG DE MOVERSE SE ACTIVA
        if ((row == (2 * fila)) && (get_frog_move(&frog_position) == 1)) 
        {
          if ((int)(get_frog_x(&frog_position)) + 1 > 13) // IF PARA MORIR SI SE VA DE LOS LIMITES
            // DESPUES HACER UNA FUNCION MAS PROLIJA....
          {
            set_frog_life(&frog_position, 0);
            set_frog_dead(&frog_position, 1);
          }
          // SINO LA DESPLAZA
          else 
          {
            if (directions[2 * fila]) set_frog_x(&frog_position, get_frog_x(&frog_position) + 1);
            else set_frog_x(&frog_position, get_frog_x(&frog_position) - 1);   
          }
        }

        shift_row(2 * fila, directions[2 * fila]); // Desplazar fila 0, 2, 4, 6, etc. a la derecha
      }
      // Desplazar fila impar (de derecha a izquierda)
      if (waiting_time(frog_position.levels, ((2 * fila) - 1))) // SI ES UNA FILA IMPAR
      {
        // SI LA FILA CONCUERDA CON LA POSICION DE LA RANA Y LA FLAG DE MOVERSE SE ACTIVA
        if ((row == ((2 * fila) - 1))  && (get_frog_move(&frog_position) == 1)) 
        {
          if ((int)(get_frog_x(&frog_position)) - 1 < 1) // IF PARA MORIR SI SE VA DE LOS LIMITES
          { 
            set_frog_life(&frog_position, 0);
            set_frog_dead(&frog_position, 1);
          }
          // SINO LA DESPLAZA
          else 
          {
              if (directions[(2 * fila) - 1]) set_frog_x(&frog_position, get_frog_x(&frog_position) + 1);
              else set_frog_x(&frog_position, get_frog_x(&frog_position) - 1);     
          }
        }
        shift_row((2 * fila) - 1, directions[(2 * fila) - 1]); // Desplazar fila 1, 3, 5, etc. a la izquierda
      }
      
      
      if (detect_arrival(&frog_position, &map)) //Deteccion de llegada
      {
        set_frog_arrivals(&frog_position, get_frog_arrivals(&frog_position) + 1);
        set_frog_start(&frog_position);
        printf("LLEGASTE\n");
      }

      if(get_frog_lives(&frog_position) == 0) // SI LA RANA NO TIENE VIDAS, TERMINA EL JUEGO
      {
        resources_for_main.menu_state = 1;
        resources_for_main.selected_option = 1;
        FILE* pointer = highscores(get_frog_points(&frog_position), "Jugador"); //ACA DEBERIA PASAR EL NOMBRE INGRESADO POR EL USUARIO
        if(pointer == NULL)
        {
          fprintf(stderr, "Error: no se pudo abrir el archivo de highscores.\n");
        }
        
        // Mientras el estado del menu de highscores sea 1, se ejecuta 
        while(resources_for_main.highscores_state == 1)
        { 
          events_managment(&resources_for_main, event_queue, &frog_position, map);
          menu_highscores(pointer, &resources_for_main);
        }
        fclose(pointer);
        cleanup_allegro(&resources_for_main);
        return 0;
      }

      if(get_frog_arrivals(&frog_position) == 5) // SI LLEGASTE 5 VECES PASAS DE NIVEL
      {
        set_frog_arrivals(&frog_position, 0);
        //set_frog_points(&frog_position, get_frog_points(&frog_position) + 1000);
        frog_position.levels++;
        set_frog_start(&frog_position);
        printf("NIVEL COMPLETADO\n");
      }
    }

    frog_in_range(&map, &frog_position); // FUNCION QUE CHEQUEA QUE ESTE DENTRO DE LOS LIMITES
    Screen(&resources_for_main, map, &frog_position);
  }

  return 0;
}