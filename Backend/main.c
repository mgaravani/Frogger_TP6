/*------------INCLUDES-----------*/
#include "../Backend/logic.h"



/*-----Function main-----*/
int main(void)
{
  extern map_t map; // Variable global de la matriz
  frog_t frog_position;
  uint8_t directions[11] = {0,1,0,1,1,0,0,0,1,0,1}; 
  init_frog(&frog_position, 7, 11.96, 0, 1, 3, 0, 0, 0, 0, 0, 1); // Inicializo la rana
  frog_position.pass_level_state = 0;
  frog_position.paused_state = 0;
  frog_position.actual_row = ROWS - 1;
  for(uint8_t i = 0; i < ROWS; i++)
  {
    frog_position.reached_rows[i] = 0 ; // Vector para conteo de puntos
  }
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
    for (int fila = 1; fila < 12; fila++) // FOR PARA MOVER LAS DISTINTAS FILAS, escribir en ingles
    {
      if (waiting_time(frog_position.levels, fila))
      {
        // SI LA FILA CONCUERDA CON LA POSICION DE LA RANA Y LA FLAG DE MOVERSE SE ACTIVA
        if ((row == fila) && (get_frog_move(&frog_position) == 1)) 
        {
          if ((((int)(get_frog_x(&frog_position)) + 1 > 13) && directions[fila]) || ((((int)(get_frog_x(&frog_position)) - 1 < 1)) && (!directions[fila]))) // IF PARA MORIR SI SE VA DE LOS LIMITES
            // DESPUES HACER UNA FUNCION MAS PROLIJA....
          {

            set_frog_life(&frog_position, 0);
            set_frog_dead(&frog_position, 1);
          }
          else // SINO LA DESPLAZA
          {
            if (directions[fila]) set_frog_x(&frog_position, get_frog_x(&frog_position) + 1);
            else set_frog_x(&frog_position, get_frog_x(&frog_position) - 1);   
          }
        }
        if(frog_position.paused_state == 0)
        {
        shift_row(fila, directions[fila]); // Desplazar fila 0, 2, 4, 6, etc. a la derecha
        }
      }
      
      if (detect_arrival(&frog_position, &map)) //Deteccion de llegada
      {
        set_frog_arrivals(&frog_position, get_frog_arrivals(&frog_position) + 1);
        set_frog_start(&frog_position);
      }

      if(get_frog_lives(&frog_position) == 0) // SI LA RANA NO TIENE VIDAS, TERMINA EL JUEGO
      {
        resources_for_main.menu_state = 1;
        resources_for_main.selected_option = 1;
        resources_for_main.name_state = 1;
        resources_for_main.highscores_state = 1;
        
        player_t players[MAX_PLAYERS];

        // Cargar puntajes desde el archivo
        loadScores("highscores.txt", players);

        enter_player_name(event_queue, &resources_for_main);

        player_t newPlayer;
        strcpy(newPlayer.name, resources_for_main.player_name);  // Copia la cadena en el array
        newPlayer.score = get_frog_points(&frog_position);      // Asigna el puntaje
        newScore(players, newPlayer);                            // Agrega el nuevo puntaje

        // Guardar los puntajes actualizados
        saveScores("highscores.txt", players);

        FILE* pointer = fopen("highscores.txt", "r");
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
        /*
        fclose(pointer);
        cleanup_allegro(&resources_for_main); //CREO QUE ESTAS TRES COSAS SON INNECESARIAS ACA
        return 0;
        */
      }

      if(get_frog_arrivals(&frog_position) == 5) // SI LLEGASTE 5 VECES PASAS DE NIVEL
      {
        pass_level(&frog_position);
      }
    }

    frog_in_range(&map, &frog_position); // FUNCION QUE CHEQUEA QUE ESTE DENTRO DE LOS LIMITES
    Screen(&resources_for_main, map, &frog_position);
  }

  return 0;
}


/*-----Function main-----*/
/*
int main(void) { 
  frog_t frog_position; // Estructura de la rana
  AllegroResources resources_for_main; // Estructura de recursos de allegro
  ALLEGRO_EVENT_QUEUE *event_queue; // Cola de eventos

  initialize_game(&frog_position, &resources_for_main, &event_queue);
  handle_menu(&resources_for_main, event_queue, &frog_position, map);
  //Sgame_loop(&frog_position, &resources_for_main, event_queue, map);
  while (frog_position.playing_game == 1) 
  {
      int row = 12 - (int)((-(get_frog_y(&frog_position) - 11.96)) / 0.96);
      events_managment(&resources_for_main, event_queue, &frog_position, map);
      process_row_movements(&frog_position, row);
      if (detect_arrival(&frog_position, map)) 
      {
          set_frog_arrivals(&frog_position, get_frog_arrivals(&frog_position) + 1);
          set_frog_start(&frog_position);
      }
      if (get_frog_lives(&frog_position) == 0) 
      {
          handle_game_over(&frog_position, &resources_for_main, event_queue, map);
      }
      if (get_frog_arrivals(&frog_position) == 5) 
      {
          pass_level(&frog_position);
      }
      frog_in_range(map, &frog_position);
      Screen(&resources_for_main, map, &frog_position);
  }
  return 0;
}
*/
