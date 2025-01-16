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

    // Dibuja el fondo escalado en 870X650
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

    // Dibujar elementos del mapa
    for (uint16_t i = 0; i < ROWS; i++) 
    {
        float counter = 0;
        float x = 0;

        for (uint16_t j = 0; j < COLUMNS; j++) 
        {
            float compensate = 1;
            ALLEGRO_BITMAP *image_to_draw = NULL;

            if (map[i][j] == 1) counter++; // Funcion para el largo de troncos o tortugas

            if ((map[i][j] == 0) && (counter > 0))
            {
            x =  (j - counter + (counter / 2.0) - 0.5) * cell_width;  // Centro el objeto segun el largo
            int y = i * cell_height; // Coordenada y basada en la fila
                switch (i) 
                {
                    case 1:
                    case 3:
                    case 4:
                    
                        image_to_draw = resources->images[1]; // Tronco
                        if (counter == 2)  x-=29; // Ajusto el largo de troncos de 2 
                        else if (counter == 3) x-=67; // Ajusto el largo de troncos de 3
                        else x-= 100; // Ajusto el largo de troncos de 4
                        y+=25;
                        break;
                    case 2:
                    case 5:
                        if (counter == 2){
                            image_to_draw = resources->images[10]; // Tortle x2
                            x-=30; // Ajusto el largo de tortugas de 2
                            y+=20;
                        } 
                        else {
                            image_to_draw = resources->images[12]; // Tortle x3
                            x-=69; // Ajusto el largo de tortugas de 3
                            y+=20;
                        }
                        break;
                    case 7:
                        image_to_draw = resources->images[9]; // Truck
                        x-=35; // Ajusto largo de camion
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
            float frog_x = get_frog_x(frog) - 0.38; // Obtener coordenada X de la rana
            float frog_y = get_frog_y(frog) + 0.16; // Obtener coordenada Y de la rana
            // Calcula la posición en la pantalla (si es necesario ajustar la escala)
            float screen_x = frog_x * cell_width;  // Ajusta si la coordenada X se refiere a una celda
            float screen_y = frog_y * cell_height; // Ajusta si la coordenada Y se refiere a una celda

            switch (get_frog_state(frog)) 
                    {
                        case 0:
                            image_to_draw = resources->images[14];
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

            // Dibujar la rana, no estaria funcionando correctamente
            /* NO ESTA FUNCIONANDOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
            if (get_frog_life(frog) == 0) 
            {
                al_draw_scaled_bitmap(
                resources->images[20],                   // Imagen de la rana
                0, 0,                                    // Coordenadas de origen de la imagen
                al_get_bitmap_width(resources->images[20]), // Ancho original de la imagen
                al_get_bitmap_height(resources->images[20]), // Alto original de la imagen
                get_frog_x(frog) - 0.38, get_frog_y(frog) + 0.16,                      // Posición de la rana en la pantalla
                cell_width*0.9, cell_height*0.9,                 // Tamaño ajustado para la rana
                0                                         // Sin banderas adicionales
                );
                // Dibuja un rectángulo con transparencia
                al_draw_filled_rectangle(
                0, resources->height/2 - 8, resources->width, resources->height/2 +41,             // Coordenadas (x1, y1, x2, y2)
                al_map_rgba(0, 0, 0, 128)     // Color negro con  opacidad
                );
                al_draw_text(resources->fonts[4], al_map_rgb(66, 194, 29), resources->width / 2, resources->height/2 -15,
                ALLEGRO_ALIGN_CENTRE, "Vida perdida");
                
            }
    if(get_frog_lives(frog) > 0)
    {
        draw_heart(resources->width -50, resources->height -50 ,50);
    }*/
    
    // Muestra la ventana
    al_flip_display();
}

/*
void draw_heart(uint32_t x, uint32_t y, uint32_t size)
{
   // Radio de los círculos
    float radius = size / 2.0;

    // Coordenadas de los círculos
    float left_circle_x = x - radius;
    float right_circle_x = x + radius;
    float circle_y = y - radius;

    // Coordenadas para el triángulo inferior
    float triangle_x1 = x - radius;
    float triangle_y1 = y;
    float triangle_x2 = x + radius;
    float triangle_y2 = y;
    float triangle_x3 = x;
    float triangle_y3 = y + size;

    // Dibujar los dos círculos
    al_draw_filled_circle(left_circle_x, circle_y, radius, al_map_rgb(255, 0, 0));  // Rojo
    al_draw_filled_circle(right_circle_x, circle_y, radius, al_map_rgb(255, 0, 0)); // Rojo

    // Dibujar el triángulo
    ALLEGRO_VERTEX vertices[3] = {
        {triangle_x1, triangle_y1, 0, 0, 0},
        {triangle_x2, triangle_y2, 0, 0, 0},
        {triangle_x3, triangle_y3, 0, 0, 0}
    };
    al_draw_filled_polygon(vertices, 3, al_map_rgb(255, 0, 0)); // Rojo
}*/