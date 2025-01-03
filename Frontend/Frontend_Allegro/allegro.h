#ifndef ALLEGRO_H
#define ALLEGRO_H

/*INCLUDES*/
#include <stdio.h>  // Incluyo la librería estándar stdio
#include <pthread.h> //Incluyo la libreria de threads
#include <stdint.h>  //Incluyo la libreria estandar para tener tipo de datos multiplataforma
#include <allegro5/allegro.h> // Incluyo la librería Allegro
#include <allegro5/allegro_primitives.h> // Incluyo el addon primitives
#include <allegro5/allegro_ttf.h>  // Incluye el addon para fuentes TTF
#include <allegro5/allegro_font.h> // Incluyo el addon font
#include <allegro5/allegro_color.h> //Incluyo el addon color
#include <allegro5/allegro_image.h> // Necesario para cargar imágenes

/*DEFINES*/
#define ROWS 16
#define COLUMNS 18
#define WIDTH 1000
#define HEIGHT 800

/*STRUCTS*/
/*Creo un tipo de dato de estructura llamado AllegroResources 
donde se guardan las fuentes, puntero a display y otros recursos*/
typedef struct 
{
    ALLEGRO_DISPLAY *display; //Puntero al tipo de dato ALLEGRO_DISPLAY para la pantalla
    ALLEGRO_FONT *fonts[10]; // Array de punteros al tipo ALLEGRO_FONT para las fuentes a utilizar
    ALLEGRO_BITMAP *images[12]; // Array de punteros al tipo ALLEGRO_BITMAP para las imagenes a utilizar 
    uint32_t width; //Ancho de la pantalla
    uint32_t height; //Alto de la pantalla
    uint32_t selected_option; //Guardo la opcion seleccionada en el menu de inicio
    uint32_t (*obstacles)[COLUMNS];

} AllegroResources;


/*PROTOTYPES*/
void allegro_init(uint32_t map[ROWS][COLUMNS]);
void Screen(AllegroResources *resources, uint32_t map[ROWS][COLUMNS]);
void cleanup_allegro(AllegroResources *resources);


#endif /* ALLEGRO_H */