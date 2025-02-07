/*------------INCLUDES-----------*/
#include "../Backend/logic.h"

uint8_t directions[11] = {0,1,0,1,1,0,0,0,1,0,1}; 

/*-----Function main-----*/
int main(void)
{
  frog_t frog_position; // Estructura de la rana
  AllegroResources resources_for_main; // Estructura de recursos de allegro
  ALLEGRO_EVENT_QUEUE *event_queue; // Cola de eventos

  initialize_game(&frog_position, &resources_for_main, &event_queue);
  handle_menu(&resources_for_main, event_queue, &frog_position, map);
  game_loop(&frog_position, &resources_for_main, event_queue, map);
  
  return 0;
}


