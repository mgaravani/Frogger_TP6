#include "allegro.h"
#include <stdio.h>
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
//Utilizada para el manejo de los eventos
void events_managment(AllegroResources *resources, ALLEGRO_EVENT_QUEUE *event_queue, frog_t *frog)
{
    ALLEGRO_EVENT event;
    if (al_get_next_event(event_queue, &event)) {
        // Manejo de teclado
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (event.keyboard.keycode) {

                case ALLEGRO_KEY_DOWN:
                    // Lógica para manejar FLECHA ABAJO
                    al_play_sample(resources->sounds[0], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); // Reproduce el sonido
                    set_frog_y(frog, get_frog_y(frog) + 0.96); // Mueve a la rana en el mapa
                    set_frog_state(frog, 1); // LOGICA PARA MOSTRAR LA RANA EN SUS 4 LADOS
                    printf("FILA: %f\n", (-(get_frog_y(frog)-11.96))/0.96);
                    break;
                case ALLEGRO_KEY_UP:
                    // Lógica para manejar FLECHA ARRIBA   
                    al_play_sample(resources->sounds[0], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); // Reproduce el sonido
                    set_frog_y(frog, get_frog_y(frog) - 0.96); // Mueve a la rana en el mapa
                    set_frog_state(frog, 0); // LOGICA PARA MOSTRAR LA RANA EN SUS 4 LADOS
                    printf("FILA: %f\n", (-(get_frog_y(frog)-11.96))/0.96);
                    break;
                case ALLEGRO_KEY_LEFT:
                    // Lógica para manejar FLECHA IZQUIERDA
                    al_play_sample(resources->sounds[0], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); // Reproduce el sonido
                    if (get_frog_x(frog) > 1)
                    {
                        set_frog_x(frog, get_frog_x(frog) - 1);
                        //printf("COL: %f\n", ((get_frog_x(frog))));

                    }
                    else {
                        set_frog_x(frog, get_frog_x(frog) - 0.7);
                        //printf("COL: 0\n");
                    }
                    printf("COL: %f\n", ((get_frog_x(frog))));
                    set_frog_state(frog, 2); // LOGICA PARA MOSTRAR LA RANA EN SUS 4 LADOS
                    break;

                case ALLEGRO_KEY_RIGHT:
                    // Lógica para manejar FLECHA DERECHA
                    al_play_sample(resources->sounds[0], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); // Reproduce el sonido
                    if (get_frog_x(frog) >= 1)
                    {
                        set_frog_x(frog, get_frog_x(frog) + 1);
                        //printf("COL: %f\n", ((get_frog_x(frog))));
                    }
                    else {
                        set_frog_x(frog, get_frog_x(frog) + 0.7);
                        //printf("COL: %f\n", ((get_frog_x(frog))));

                    }
                    printf("COL: %f\n", ((get_frog_x(frog))));
                    set_frog_state(frog, 3); // LOGICA PARA MOSTRAR LA RANA EN SUS 4 LADOS
                    break;

                case ALLEGRO_KEY_ENTER:
                    printf("ENTER\n");
                    if (resources->selected_option == 1) {
                        // Código de inicio de partida
                    } else if (resources->selected_option == 2) {
                        // Código para High Scores
                    } else {
                        exit(EXIT_SUCCESS); // Salir del juego
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
