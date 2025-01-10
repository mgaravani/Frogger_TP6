/*------------INCLUDES-----------*/
#include "allegro.h"
#include <stdio.h>
#include <unistd.h>
#include "../../Backend/frog.h"

/*------Function Screen------*/
// Función para mostrar la pantalla de juego
void Screen(AllegroResources *resources, uint8_t map[ROWS][COLUMNS], frog_t *frog) 
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
    uint32_t cell_width = (resources->width) / (COLUMNS-6);
    uint32_t cell_height = resources->height / ROWS;
    //printf("%d",cell_width);

    // Dibujar elementos del mapa
    for (uint16_t i = 0; i < ROWS; i++) 
    {
        float counter = 0;
        float x = 0;

        for (uint16_t j = 0; j < COLUMNS; j++) 
        {
            float compensate = 1;
            ALLEGRO_BITMAP *image_to_draw = NULL;

            if (map[i][j] == 1) {
                counter++;         
            }
            if ((map[i][j] == 0) && (counter > 0)){
                
            x =  (j - counter + (counter / 2.0) - 0.5) * cell_width;  // Coordenada x basada en la columna
            int y = i * cell_height; // Coordenada y basada en la fila
                switch (i) 
                {
                    case 1:
                    case 3:
                    case 4:
                    
                        image_to_draw = resources->images[1]; // Log
                        if (counter == 2)  x-=29;
                        else if (counter == 3) x-=67;
                        else x-= 100;
                        y+=25;
                        break;
                    case 2:
                    case 5:
                        if (counter == 2){
                            image_to_draw = resources->images[10]; // Tortle x2
                            x-=30;
                            y+=20;
                        } 
                        else {
                            image_to_draw = resources->images[12]; // Tortle x3
                            x-=69;
                            y+=20;
                        }
                        break;
                    case 7:
                        image_to_draw = resources->images[9]; // Truck
                        x-=35;
                        y+=15;
                        break;
                    case 8:
                        image_to_draw = resources->images[2]; // Car 1
                        y+=13;
                        break;
                    case 9:
                        image_to_draw = resources->images[7]; // Car 3
                        compensate = 0.9;
                        y+=8;
                        break;
                    case 10:
                        image_to_draw = resources->images[4]; // Car 2
                        break;
                    case 11:
                        image_to_draw = resources->images[15]; // Car 4
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
                        x-213, y, // Posición en la pantalla compensado por las columnas restantes
                        cell_width * counter, cell_height * compensate, // Nuevo ancho y alto
                        0 // Sin banderas adicionales
                    );
                }
                counter = 0;
            }
            
        // Obtener las coordenadas de la rana desde la estructura frog
        float frog_x = get_frog_x(frog) - 0.25; // Obtener coordenada X de la rana
        float frog_y = get_frog_y(frog) + 0.16; // Obtener coordenada Y de la rana
        // Calcula la posición en la pantalla (si es necesario ajustar la escala)
        float screen_x = frog_x * cell_width;  // Ajusta si la coordenada X se refiere a una celda
        float screen_y = frog_y * cell_height; // Ajusta si la coordenada Y se refiere a una celda
        // Dibujar la rana
        switch (get_frog_state(frog)) 
                {
                    case 0:
                        image_to_draw = resources->images[14] ;
                        break;
                    case 1:
                        image_to_draw = resources->images[19];
                        break;
                    case 2:
                        image_to_draw = resources->images[17];
                        break;
                    case 3:
                        image_to_draw = resources->images[18];
                        break;
                    default:
                    break;
                }
        al_draw_scaled_bitmap(
            image_to_draw,                   // Imagen de la rana
            0, 0,                                    // Coordenadas de origen de la imagen
            al_get_bitmap_width(image_to_draw), // Ancho original de la imagen
            al_get_bitmap_height(image_to_draw), // Alto original de la imagen
            screen_x, screen_y,                      // Posición de la rana en la pantalla
            cell_width*0.9, cell_height*0.9,                 // Tamaño ajustado para la rana
            0                                         // Sin banderas adicionales
        );
    }
  }
    // Muestra la ventana
    al_flip_display();
}