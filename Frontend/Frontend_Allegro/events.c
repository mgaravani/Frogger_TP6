#include <stdio.h>
#include "allegro.h"
#include "../../Backend/frog.h"

ALLEGRO_EVENT_QUEUE *init_events(ALLEGRO_DISPLAY *display)
{
    /*************************************************************************************************
    * Inicialización del sistema de eventos                                                          *
    * Se crea una cola de eventos que manejará las entradas del sistema,                             *
    * como eventos de teclado y pantalla.                                                            *
    * con la cola de eventos para monitorear eventos relacionados con esa pantalla.          
    *************************************************************************************************/ 
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue(); //Crea una cola de eventos

    /*ANALIZA SI SE PUDO CREAR*/
    if (!event_queue) 
    {
        fprintf(stderr, "No se pudo crear la cola de eventos.\n");
        exit(EXIT_FAILURE); //Ante un fallo termina el programa y borra los recursos
    }

    //Registra una fuente de eventos del mouse en la cola especificada
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    //Registra eventos relacionados con el display
    al_register_event_source(event_queue, al_get_display_event_source(display));

    return event_queue;
}

/*FUNCION manejo_eventos*/
// Función principal de manejo de eventos
void events_managment(AllegroResources *resources, ALLEGRO_EVENT_QUEUE *event_queue, frog_t *frog, uint8_t map[ROWS][COLUMNS]) {
    ALLEGRO_EVENT event;
    if (al_get_next_event(event_queue, &event)) {
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_DOWN:
                case ALLEGRO_KEY_S:
                    if(resources->menu_state == 1)
                    {
                        if (resources->selected_option < 3) 
                        {
                            resources->selected_option++;
                        }
                    }
                    else
                    {
                    al_play_sample(resources->sounds[0], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    handle_move_down(frog);
                    }
                    break;
                case ALLEGRO_KEY_UP:
                case ALLEGRO_KEY_W:
                    if(resources->menu_state == 1)
                    {
                        if (resources->selected_option > 1)
                        {
                            resources->selected_option--;
                        }
                    }
                    else
                    {
                    al_play_sample(resources->sounds[0], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    handle_move_up(frog);
                    }
                    break;
                case ALLEGRO_KEY_LEFT:
                case ALLEGRO_KEY_A:
                    al_play_sample(resources->sounds[0], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    handle_move_left(frog);
                    break;
                case ALLEGRO_KEY_RIGHT:
                case ALLEGRO_KEY_D:
                    al_play_sample(resources->sounds[0], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    handle_move_right(frog);
                    break;
                case ALLEGRO_KEY_ENTER:
                if(resources->selected_option == 1) //Si se eligio Play game
                {   
                    resources->menu_state = 0;
                    Screen(&resources, map ,&frog);
                }
                else if(resources->selected_option == 2) //Si se eligio High Scores
                {
                    // Código para High Scores
                }
                else
                {
                    exit(EXIT_SUCCESS);//Si se eligio Quit Game
                }
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    // Lógica para manejar FLECHA ESCAPE
                    printf("Saliendo del programa...\n");
                    cleanup_allegro(resources);
                    exit(EXIT_SUCCESS);
                    break;
            }
        }
    }
}