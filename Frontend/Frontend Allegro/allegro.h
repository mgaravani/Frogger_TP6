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

#define FILAS 14
#define COLUMNAS 40

/*PASAR LOS INT A UINT_32T*/
/*ESTRUCTURAS*/

//Definicion de estructura para guardar coordenadas de rectangulos
typedef struct {
    uint32_t x1, y1; // Coordenadas de la esquina superior izquierda
    uint32_t x2, y2; // Coordenadas de la esquina inferior derecha
} ALLEGRO_RECTANGLE;

/*Creo un tipo de dato de estructura llamado AllegroResources 
donde se guardan las fuentes, puntero a display y otros recursos*/
typedef struct 
{
    ALLEGRO_DISPLAY *pantalla; //Puntero al tipo de dato ALLEGRO_DISPLAY para la pantalla
    ALLEGRO_FONT *fuentes[10]; // Array de punteros al tipo ALLEGRO_FONT para las fuentes a utilizar 
    uint32_t width; //Guardo a..
    uint32_t height; //Guardo...
    uint32_t selected_option; //Guardo la opcion seleccionada en el menu de inicio
    uint32_t (*obstaculos)[COLUMNAS];

} AllegroResources;

/*PROTOTYPES*/

/*FUNCION init_allegro*/
//Recibira dos punteros a matrices y algo mas....COMPLETAR CUANDO SE DISEÑE
AllegroResources init_allegro(uint32_t matriz[FILAS][COLUMNAS]); //Encargada de realizar todas las inicializaciones necesarias para el funcionamento

/*FUNCION menu_allegro*/
//Da inicio al juego mostrando un menu de inicio para seleccionar el modo de juego y dar comienzo a la partida
//Recibe la estructura resources
void menu_allegro(AllegroResources resources);

/*FUNCION cleanup_allegro*/
//Borra todos los recursos utilizados
void cleanup_allegro(AllegroResources resources);

/*FUNCION inicio_partida*/
//Utilizada para imprimir en pantalla el mapa de juego
void inicio_partida(uint32_t matriz[FILAS][COLUMNAS]);

/*FUNCION events*/
//Creacion de eventos
ALLEGRO_EVENT_QUEUE *init_events(ALLEGRO_DISPLAY *pantalla);

/*FUNCION manejo_eventos*/
//Utilizada para el manejo de los eventos
void manejo_eventos(AllegroResources *resources, ALLEGRO_EVENT_QUEUE * event_queue);

/*     PRUEBA DE MOVIMIENTO CONTINUO      */
void prueba_impresion( AllegroResources);
/*     PRUEBA DE MOVIMIENTO CONTINUO      */


#endif /* ALLEGRO_H */