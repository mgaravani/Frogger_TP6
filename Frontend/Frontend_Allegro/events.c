/*------------INCLUDES-----------*/
#include <stdio.h>
#include <string.h>
#include "allegro.h"
#include "../../Backend/frog.h"

#define MAX_NAME_LENGTH 10

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
                // Lógica para manejar la pausa
                case ALLEGRO_KEY_P:
                    if(resources->menu_state == 0)
                    {
                    frog->paused_state = !frog->paused_state;
                    }
                    break;
                // Lógica para manejar el reinicio
                //AGREGAR MENSAJE DE JUEGO REINICIADO
                case ALLEGRO_KEY_R:
                    if(resources->menu_state == 0)
                    {
                    restart(frog);
                    initialize_matrix();
                    }
                    break;
                // Lógica para manejar la flecha abajo y la tecla S
                case ALLEGRO_KEY_DOWN:
                case ALLEGRO_KEY_S:
                    if(resources->menu_state == 1)
                    {
                        if (resources->selected_option < 3) 
                        {
                            resources->selected_option++;
                        }
                    }
                    else if(frog->paused_state == 0 && resources->menu_state == 0)
                    {
                        if (handle_move_down(frog)) al_play_sample(resources->sounds[0], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    }
                    break;
                // Lógica para manejar la flecha arriba y la tecla W    
                case ALLEGRO_KEY_UP:
                case ALLEGRO_KEY_W:
                    if(resources->menu_state == 1)
                    {
                        if (resources->selected_option > 1)
                        {
                            resources->selected_option--;
                        }
                    }
                    else if(frog->paused_state == 0 && resources->menu_state == 0)
                    {
                        if (handle_move_up(frog)) al_play_sample(resources->sounds[0], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    }
                    break;
                // Lógica para manejar la flecha izquierda y la tecla A
                case ALLEGRO_KEY_LEFT:
                case ALLEGRO_KEY_A:
                    if (frog->paused_state == 0 && resources->menu_state == 0)
                    {
                        if (handle_move_left(frog)) al_play_sample(resources->sounds[0], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    }
                    break;
                // Lógica para manejar la flecha derecha y la tecla D
                case ALLEGRO_KEY_RIGHT:
                case ALLEGRO_KEY_D:
                    if (frog->paused_state == 0 && resources->menu_state == 0)
                    {
                        if (handle_move_right(frog)) al_play_sample(resources->sounds[0], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    }
                    break;
                // Lógica para manejar la tecla ENTER
                case ALLEGRO_KEY_ENTER:
                if(resources->selected_option == 1) //Si se eligio Play game
                {   
                    resources->menu_state = 0;
                }
                else if(resources->selected_option == 2) //Si se eligio High Scores
                {
                    FILE* pointer = fopen("highscores.txt", "r");
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
                // Lógica para manejar la tecla ESCAPE
                case ALLEGRO_KEY_ESCAPE:
                    // Lógica para manejar FLECHA ESCAPE
                    //DEBERIA LLEVARTE AL MENU PRINCIPAL
                    cleanup_allegro(resources);
                    exit(EXIT_SUCCESS);
                    break;
            }
        }
    }
}


// Función para manejar la entrada del nombre del jugador
//No deja apretar escape para salir
void enter_player_name(ALLEGRO_EVENT_QUEUE *event_queue, AllegroResources *resources)
{
    ALLEGRO_EVENT event;
    uint16_t name_length = 0;
    resources->player_name[0] = '\0'; // Inicializa el string vacío
    image_drawing(resources->images[30], 0, 0, WIDTH /12 -70 , HEIGHT / 2 - 9 , (resources->width) / (COLUMNS-6) * 14, resources->height / ROWS );
    al_flip_display();
    while (1) 
    {
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_KEY_DOWN) 
        {
            uint16_t key = event.keyboard.keycode;

            // Si se presiona Enter, finaliza la entrada del nombre
            if (key == ALLEGRO_KEY_ENTER && name_length > 0) 
            {
                resources->name_state = 0;
                break;
            }
            // Si se presiona Backspace, borra el último carácter
            else if (key == ALLEGRO_KEY_BACKSPACE && name_length > 0) 
            {
                resources->player_name[--name_length] = '\0';
            }
            // Si se presiona una letra y no se supera el límite
            else if (name_length < MAX_NAME_LENGTH - 1) 
            {
                if ((key >= ALLEGRO_KEY_A && key <= ALLEGRO_KEY_Z)) 
                {
                    resources->player_name[name_length++] = (key == ALLEGRO_KEY_SPACE) ? ' ' : ('A' + (key - ALLEGRO_KEY_A));
                    resources->player_name[name_length] = '\0'; // Asegura que la cadena termine en NULL
                }
            }
            else if (key == ALLEGRO_KEY_ESCAPE)
            {
                // Borra el nombre ingresado y sale del bucle
                resources->player_name[0] = '\0';
                resources->name_state = 0;
                break;
            }
        }

        // Dibujar un recuadro en lugar de limpiar toda la pantalla
        image_drawing(resources->images[30], 0, 0, WIDTH /12 -70 , HEIGHT / 2 - 9 , (resources->width) / (COLUMNS-6) * 14, resources->height / ROWS );
        al_draw_text(resources->fonts[5], al_map_rgb(220, 250, 6), 590, HEIGHT / 2 , ALLEGRO_ALIGN_CENTER, resources->player_name);
        al_flip_display();
    }
}
