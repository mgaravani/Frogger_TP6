#include "allegro.h"
#include <stdio.h>
#include "../../Backend/frog.h"

ALLEGRO_EVENT_QUEUE *init_events(ALLEGRO_DISPLAY *display)
{
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
                    printf("Tecla presionada: FLECHA ABAJO\n");
                    set_frog_y(frog, get_frog_y(frog) + 0.96);
                    set_frog_state(frog, 1);
                    // Lógica para manejar FLECHA ABAJO
                    /* if (resources->selected_option < 3) 
                        resources->selected_option++; */
                    break;
                case ALLEGRO_KEY_UP:
                    printf("Tecla presionada: FLECHA ARRIBA\n");
                    set_frog_y(frog, get_frog_y(frog) - 0.96);
                    set_frog_state(frog, 0);
                    // Lógica para manejar FLECHA ARRIBA

                    /* if (resources->selected_option > 1) 
                        resources->selected_option--; */
                    break;
                case ALLEGRO_KEY_LEFT:
                    printf("Tecla presionada: FLECHA IZQUIERDA\n");
                    set_frog_x(frog, get_frog_x(frog) - 1);
                    set_frog_state(frog, 2);
                    // Lógica para manejar FLECHA IZQUIERDA
                    break;

                case ALLEGRO_KEY_RIGHT:
                    printf("Tecla presionada: FLECHA DERECHA\n");
                    set_frog_x(frog, get_frog_x(frog) + 1);
                    set_frog_state(frog, 3);
                    // Lógica para manejar FLECHA DERECHA
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
                    printf("Saliendo del programa...\n");
                    cleanup_allegro(resources);
                    exit(EXIT_SUCCESS);
                    break;
            }
        }

        // Manejo del cierre de la ventana
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            printf("Cerrando ventana...\n");
            cleanup_allegro(resources);
            exit(EXIT_SUCCESS);
        }
    }
}
