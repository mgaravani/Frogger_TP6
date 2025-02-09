#ifndef ALLEGRO_H
#define ALLEGRO_H

//ESTARIA BUENO AGREGAR PARA CADA FUNCION UNA DESCRIPCION DE LO QUE HACE, LO QUE RECIBE Y LO QUE DEVUELVE

/*-------INCLUDES------*/
#include <stdio.h>  
#include <stdint.h>  
#include <allegro5/allegro.h> 
#include <allegro5/allegro_primitives.h> 
#include <allegro5/allegro_ttf.h>  
#include <allegro5/allegro_font.h> 
#include <allegro5/allegro_color.h> 
#include <allegro5/allegro_image.h> 
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "../../Backend/frog.h"

/*-------DEFINES------*/
#define ROWS 13
#define COLUMNS 20
#define WIDTH 870
#define HEIGHT 650
#define SOUNDS 4
#define FONTS 6
#define IMAGES 34

/*------STRUCTS------*/

/*Creo un tipo de dato de estructura llamado AllegroResources 
donde se guardan las fuentes, puntero a display y otros recursos*/
typedef struct 
{
    ALLEGRO_DISPLAY *display; //Puntero al tipo de dato ALLEGRO_DISPLAY para la pantalla
    ALLEGRO_FONT *fonts[FONTS]; // Array de punteros al tipo ALLEGRO_FONT para las fuentes a utilizar
    ALLEGRO_BITMAP *images[IMAGES]; // Array de punteros al tipo ALLEGRO_BITMAP para las imagenes a utilizar 
    ALLEGRO_SAMPLE *sounds[SOUNDS]; // Para almacenar los sonidos cargados

    uint32_t width; //Ancho de la pantalla
    uint32_t height; //Alto de la pantalla
    uint32_t selected_option; //Guardo la opcion seleccionada en el menu de inicio
    uint8_t menu_state:1; //Guardo el estado del menu
    uint8_t highscores_state:1; //Guardo el estado de los puntajes altos
    uint8_t name_state:1; //Guardo el estado del nombre del jugador
    char player_name[20]; //Guardo el nombre del jugador
    uint16_t final_points; //Guardo los puntos finales del jugador

} AllegroResources;


/*------PROTOTYPES------*/

/*-----allegro_init-----*/
// Función para inicializar allegro
AllegroResources allegro_init(uint8_t map[ROWS][COLUMNS]);

/*-----Screen-----*/
// Función para mostrar la pantalla
void Screen(AllegroResources *resources, uint8_t map[ROWS][COLUMNS], frog_t *frog);

/*-----cleanup_allegro-----*/
// Función para limpiar allegro
void cleanup_allegro(AllegroResources *resources, ALLEGRO_EVENT_QUEUE *event_queue);

/*-----enter_player_name-----*/
// Función para manejar la entrada del nombre del jugador
void enter_player_name(ALLEGRO_EVENT_QUEUE *event_queue, AllegroResources *resources);

/*-----init_events-----*/
// Función para inicializar los eventos
ALLEGRO_EVENT_QUEUE *init_events(ALLEGRO_DISPLAY *pantalla);

/*-----events_managment-----*/
// Función para manejar los eventos
void events_managment(AllegroResources *resources, ALLEGRO_EVENT_QUEUE * event_queue, frog_t *frog, uint8_t map[ROWS][COLUMNS]);

/*-----allegro_menu-----*/
// Función para mostrar el menu
void allegro_menu(AllegroResources *resources);

/*-----menu_highscores-----*/
// Función para mostrar los puntajes altos
void menu_highscores(FILE *pointer_highscores, AllegroResources *resources);

/*-----image_drawing-----*/
// Función para dibujar una imagen
void image_drawing(ALLEGRO_BITMAP *image_to_draw, float origin_x, float origin_y, float position_x , float position_y, float width, float height);


#endif /* ALLEGRO_H */