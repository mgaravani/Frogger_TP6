/*------------INCLUDES-----------*/
#include <stdio.h>
#include "allegro.h"
#include "../../Backend/frog.h"

/*-----Function init_events-----*/
// Función para inicializar los eventos
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

/*-----Function events_managment-----*/
// Función principal de manejo de eventos
void events_managment(AllegroResources *resources, ALLEGRO_EVENT_QUEUE *event_queue, frog_t *frog, uint8_t map[ROWS][COLUMNS]) 
{
    ALLEGRO_EVENT event;
    if (al_get_next_event(event_queue, &event)) 
    {
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) 
        {
            switch (event.keyboard.keycode) 
            {
                case ALLEGRO_KEY_P:
                    frog->paused_state = !frog->paused_state;
                    break;
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
                    if (handle_move_down(frog)) al_play_sample(resources->sounds[0], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
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
                    if (handle_move_up(frog)) al_play_sample(resources->sounds[0], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    }
                    break;
                case ALLEGRO_KEY_LEFT:
                case ALLEGRO_KEY_A:
                    if (handle_move_left(frog)) al_play_sample(resources->sounds[0], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    break;
                case ALLEGRO_KEY_RIGHT:
                case ALLEGRO_KEY_D:
                   if (handle_move_right(frog)) al_play_sample(resources->sounds[0], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    break;
                case ALLEGRO_KEY_ENTER:
                if(resources->selected_option == 1) //Si se eligio Play game
                {   
                    resources->menu_state = 0;
                }
                else if(resources->selected_option == 2) //Si se eligio High Scores
                {
                    FILE* pointer = highscores(get_frog_points(frog), "Jugador");
                    if(pointer == NULL)
                    {
                        fprintf(stderr, "Error: no se pudo abrir el archivo de highscores.\n");
                        return;
                    }
                    while(resources->highscores_state == 1)
                    { 
                    menu_highscores(pointer, resources);
                    }
                }
                else
                {
                    cleanup_allegro(resources);
                    exit(EXIT_SUCCESS);//Si se eligio Quit Game
                }
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    // Lógica para manejar FLECHA ESCAPE
                    cleanup_allegro(resources);
                    exit(EXIT_SUCCESS);
                    break;
            }
        }
    }
}