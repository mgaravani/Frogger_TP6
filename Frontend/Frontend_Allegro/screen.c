#include "allegro.h"

void Screen(AllegroResources *resources, uint32_t map[ROWS][COLUMNS])
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

    // Muestra la ventana
    al_flip_display();

    // Espera 5 segundos
    al_rest(5.0);

    for(uint16_t i = 0; i < ROWS ;i++ )
    {
        for(uint16_t j ; j < COLUMNS ; j++)
        {
            int x = j * resources->width + resources->width / 2; //Defino la coordenada x del centro
            int y = i * resources->height + resources->height / 2; //Defino la coordenada y del centro

            if(map[1][j]==1)
            {
                al_draw_bitmap(resources->images[2], x, y-25, 0);//auto 1
            }
            if(map[2][j]==1)
            {
                al_draw_bitmap(resources->images[4], x, y-25, 0);//auto 2
            }
            if(map[3][j]==1)
            {
                al_draw_bitmap(resources->images[6], x, y-25, 0);//auto 3
            }
            if(map[4][j]==1)
            {
                al_draw_bitmap(resources->images[8], x, y-25, 0);//camion
            }
            if(map[5][j]==1)
            {
                al_draw_bitmap(resources->images[2], x, y-25, 0);//auto 1
            }
            if(map[6][j]==1)
            {
                al_draw_bitmap(resources->images[8], x, y-25, 0);//camion
            }
            if(map[7][j]==1)
            {
                al_draw_bitmap(resources->images[4], x, y-25, 0);//auto 2
            }
            if(map[8][j]==1)
            {
                al_draw_bitmap(resources->images[6], x, y-25, 0);//auto 3
            }
            if(map[10][j]==1)
            {
                al_draw_bitmap(resources->images[10], x, y-25, 0);//tortuga
            }
            if(map[11][j]==1)
            {
                al_draw_bitmap(resources->images[1], x, y-25, 0);//tronco
            }           
            if(map[12][j]==1)
            {
                al_draw_bitmap(resources->images[1], x, y-25, 0);//tronco
            }
            if(map[13][j]==1)
            {
                al_draw_bitmap(resources->images[10], x, y-25, 0);//tortuga
            }             
            if(map[14][j]==1)
            {
                al_draw_bitmap(resources->images[1], x, y-25, 0);//tronco
            }                       
        }

    }

    // Muestra la ventana
    al_flip_display();
}