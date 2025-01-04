/*------------INCLUDES-----------*/
#include "allegro.h"
#include <stdio.h>


/*------Function Screen------*/
// Función para mostrar la pantalla de juego
void Screen(AllegroResources *resources, uint8_t map[ROWS][COLUMNS], uint8_t frog_position[ROWS][COLUMNS]) 
{
    // Limpiar pantalla
    al_clear_to_color(al_map_rgb(0, 0, 0)); // Fondo negro

    // Dibuja la imagen escalada a 1000x800
    al_draw_scaled_bitmap(
        resources->images[0],                  // Imagen original
        0, 0,                   // Coordenadas en la imagen original
        al_get_bitmap_width(resources->images[0]),  // Ancho original de la imagen
        al_get_bitmap_height(resources->images[0]), // Altura original de la imagen
        0, 0,                   // Posición en la pantalla
        resources->width, resources->height,               // Nuevo ancho y alto de la imagen escalada
        0                       // Sin banderas adicionales
    );


    // Tamaño de cada celda
    uint32_t cell_width = resources->width / COLUMNS;
    uint32_t cell_height = resources->height / ROWS;

    // Dibujar elementos del mapa
    for (uint16_t i = 0; i < ROWS; i++) 
    {
        for (uint16_t j = 0; j < COLUMNS; j++) 
        {
            if (map[i][j] == 1) { // Solo dibuja si hay un elemento en la celda
                int x = j * cell_width;  // Coordenada x basada en la columna
                int y = i * cell_height; // Coordenada y basada en la fila

                ALLEGRO_BITMAP *image_to_draw = NULL;
                switch (i) 
                {
                    case 1:
                    case 3:
                    case 4:
                        image_to_draw = resources->images[1]; // Log
                        y +=25;
                        break;
                    case 2:
                    case 5:
                        image_to_draw = resources->images[10]; // Tortuga
                        y+=25;
                        break;
                    case 7:
                        image_to_draw = resources->images[8]; // Camión
                        y+=15;
                        break;
                    case 8:
                        image_to_draw = resources->images[2]; // Auto 1
                        y+=13;
                        break;
                    case 9:
                        image_to_draw = resources->images[6]; // Auto 3
                        y+=10;
                        break;
                    case 10:
                        image_to_draw = resources->images[4]; // Auto 2
                        break;
                    case 11:
                        image_to_draw = resources->images[2]; // Auto 1
                        break;
                    default:
                        break;
                }

                if (image_to_draw) 
                {
                    // Dibujar la imagen escalada al tamaño de la celda
                    al_draw_scaled_bitmap(
                        image_to_draw,
                        0, 0, // Coordenadas de origen
                        al_get_bitmap_width(image_to_draw),  // Ancho original
                        al_get_bitmap_height(image_to_draw), // Alto original
                        x, y, // Posición en la pantalla
                        cell_width, cell_height, // Nuevo ancho y alto
                        0 // Sin banderas adicionales
                    );
                }
            }

            // Dibujar la rana
            if(frog_position[i][j] == 1)
            {
                int x = j * cell_width;  // Coordenada x basada en la columna
                int y = i * cell_height; // Coordenada y basada en la fila
                al_draw_scaled_bitmap(
                    resources->images[12],
                    0, 0, // Coordenadas de origen
                    al_get_bitmap_width(resources->images[12]),  // Ancho original
                    al_get_bitmap_height(resources->images[12]), // Alto original
                    x, y, // Posición en la pantalla
                    cell_width, cell_height, // Nuevo ancho y alto
                    0 // Sin banderas adicionales
                );
            }

        }
    }
    
    // Muestra la ventana
    al_flip_display();
}