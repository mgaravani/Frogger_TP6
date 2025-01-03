#include "allegro.h"

void Screen(AllegroResources *resources, uint8_t map[ROWS][COLUMNS])
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
    
    al_flip_display();
/*
    // Tamaño de cada celda
    uint32_t cell_width = resources->width / COLUMNS;
    uint32_t cell_height = resources->height / ROWS;

    // Dibujar elementos del mapa
    for (uint16_t i = 0; i < ROWS; i++) {
        for (uint16_t j = 0; j < COLUMNS; j++) {
            if (map[i][j] == 1) { // Solo dibuja si hay un elemento en la celda
                int x = j * cell_width;  // Coordenada x basada en la columna
                int y = i * cell_height; // Coordenada y basada en la fila

                // Selección de imagen basada en la fila (i)
                switch (i) {
                    case 1:
                        al_draw_bitmap(resources->images[2], x, y, 0); // Auto 1
                        break;
                    case 2:
                        al_draw_bitmap(resources->images[4], x, y, 0); // Auto 2
                        break;
                    case 3:
                        al_draw_bitmap(resources->images[6], x, y, 0); // Auto 3
                        break;
                    case 4:
                        al_draw_bitmap(resources->images[8], x, y, 0); // Camión
                        break;
                    case 5:
                        al_draw_bitmap(resources->images[2], x, y, 0); // Auto 1 
                        break;
                    case 7:
                        al_draw_bitmap(resources->images[10], x, y, 0); // Tortuga
                        break;
                    case 8:
                    case 9:
                    case 11:
                        al_draw_bitmap(resources->images[1], x, y, 0); // Tronco
                        break;
                    case 10:
                        al_draw_bitmap(resources->images[10], x, y, 0); // Tortuga 
                        break;
                    default:
                        break; // Sin dibujo para otras filas
                }
            }
        }
    }
    
    // Muestra la ventana
    al_flip_display();*/
}