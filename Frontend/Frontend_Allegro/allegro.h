#ifndef ALLEGRO_H
#define ALLEGRO_H

/*-------INCLUDES------*/
#include <stdio.h>  // Incluyo la librería estándar stdio
#include <pthread.h> //Incluyo la libreria de threads
#include <stdint.h>  //Incluyo la libreria estandar para tener tipo de datos multiplataforma
#include <allegro5/allegro.h> // Incluyo la librería Allegro
#include <allegro5/allegro_primitives.h> // Incluyo el addon primitives
#include <allegro5/allegro_ttf.h>  // Incluye el addon para fuentes TTF
#include <allegro5/allegro_font.h> // Incluyo el addon font
#include <allegro5/allegro_color.h> //Incluyo el addon color
#include <allegro5/allegro_image.h> // Necesario para cargar imágenes
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "../../Backend/frog.h"
#include "../../Backend/highscores.h"

/*-------DEFINES------*/
#define ROWS 13
#define COLUMNS 20 // HAY DOS DEFINES CON EL MISMO NOMBRE, FUSIONAR ESTE CON MAP.H
#define WIDTH 870
#define HEIGHT 650
#define SOUNDS 1
#define FONTS 6
#define IMAGES 22

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
    uint8_t menu_state; //Guardo el estado del menu

} AllegroResources;


/*------PROTOTYPES------*/
AllegroResources allegro_init(uint8_t map[ROWS][COLUMNS]);
void Screen(AllegroResources *resources, uint8_t map[ROWS][COLUMNS], frog_t *frog);
void cleanup_allegro(AllegroResources *resources);
ALLEGRO_EVENT_QUEUE *init_events(ALLEGRO_DISPLAY *pantalla);
void events_managment(AllegroResources *resources, ALLEGRO_EVENT_QUEUE * event_queue, frog_t *frog, uint8_t map[ROWS][COLUMNS]);
void allegro_menu(AllegroResources *resources);
void menu_highscores(FILE *pointer_highscores, AllegroResources *resources);
//void draw_heart(uint32_t x, uint32_t y, uint32_t size);


#endif /* ALLEGRO_H */