/*------------INCLUDES-----------*/
#include "allegro.h"
#include <stdio.h>
#include <unistd.h>
#include "../../Backend/frog.h"
#include <time.h>

/*------Function Screen------*/
// Función para mostrar la pantalla de juego
void Screen(AllegroResources *resources, uint8_t map[ROWS][COLUMNS], frog_t *frog) 
{
    static clock_t death_time = 0; // Almacena el tiempo en que la rana murió
    static u_int16_t showing_dead_frog = 0; // Indica si estamos mostrando la rana muerta
    double dead_frog_duration = 1.0; // Duración de la animación en segundos

    // Limpiar pantalla
    al_clear_to_color(al_map_rgb(0, 0, 0)); // Fondo negro

    // Dibuja el fondo escalado en 870X650
    image_drawing(resources->images[0], 0, 0, 0, 0, resources->width, resources->height);
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
                        if (counter == 2)
                        {
                            image_to_draw = resources->images[11]; // Tortle x2
                            x-=30; // Ajusto el largo de tortugas de 2
                            y+=20;
                        } 
                        else 
                        {
                            image_to_draw = resources->images[13]; // Tortle x3
                            x-=69; // Ajusto el largo de tortugas de 3
                            y+=20;
                        }
                        break;
                    case 5:
                        if (counter == 2)
                        {
                            image_to_draw = resources->images[10]; // Tortle x2
                            x-=30; // Ajusto el largo de tortugas de 2
                            y+=20;
                        } 
                        else 
                        {
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
                    image_drawing(image_to_draw, 0, 0, x-213, y, cell_width * counter, cell_height * compensate);
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

            image_drawing(image_to_draw, 0, 0, screen_x, screen_y, cell_width*0.9, cell_height*0.9);

            //Dibuja las ranas de llegada
            if(map[i][j] == 2)
            {
                float arrival_x = (j-3) * cell_width;
                float arrival_y = 35;
                image_drawing(resources->images[23], 0, 0, arrival_x -30, arrival_y, cell_width * 0.9, cell_height * 0.9);
                if(frog->arrival_state == 1)
                {
                    al_play_sample(resources->sounds[1], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    frog->arrival_state = 0; //REUBICAR AL BACKEND, NO SE EN QUE PARTE FUNCIONA
                }
            }
        }
    }
    
    // Dibujar la rana muerta si es necesario
    if (get_frog_dead(frog) == 1)
    {     
         if (!showing_dead_frog)
        {
            // La rana acaba de morir: inicia el temporizador
            death_time = clock();
            showing_dead_frog = 1;
        }
        
        // Calcula el tiempo transcurrido desde la muerte
        double elapsed_time = (double)(clock() - death_time) / CLOCKS_PER_SEC;

        if (elapsed_time <= dead_frog_duration) 
        {
            // Dibuja la rana muerta mientras no se haya cumplido la duración
            printf("Mostrando rana muerta durante %.2f segundos\n", elapsed_time);
            image_drawing(resources->images[20], 0, 0, 
                          (get_frog_x(frog) - 0.38) * cell_width, 
                          (get_frog_y(frog) + 0.16) * cell_height, 
                          cell_width * 0.9, cell_height * 0.9);
        }  //No siempre dibuja bien la rana muerta cuando se va del mapa
        else 
        {
            printf("MEMORI\n");
            // Reinicia la rana después de mostrarla
            // Finaliza la animación de la rana muerta
            showing_dead_frog = 0;
            set_frog_dead(frog, 0);
            set_frog_start(frog);
            set_frog_life(frog, 0);
            frog_life_state(frog);
            //No detecta bien la perdida de vidas y no reinicia la posicion porque crashea
            //Reinicia luego de la segunda colision en lugar de la primera
        }
    }

    if(get_frog_lives(frog) > 0)
    {
        for(uint8_t i = 1 ; i <= get_frog_lives(frog) ; i++)
        {
            image_drawing(resources->images[22], 0, 0, i*30 -20, 615, 30, 30);
        }
    }
    
    // Muestra la ventana
    al_flip_display();
}

void image_drawing(ALLEGRO_BITMAP *image_to_draw, float origin_x, float origin_y, float position_x , float position_y, float width, float height)
{
                al_draw_scaled_bitmap(
                image_to_draw,                   // Imagen de la rana
                origin_x, origin_y,                                    // Coordenadas de origen de la imagen
                al_get_bitmap_width(image_to_draw), // Ancho original de la imagen
                al_get_bitmap_height(image_to_draw), // Alto original de la imagen
                position_x, position_y,                      // Posición  en la pantalla
                width, height,                 // Tamaño ajustado para la figura
                0                                         // Sin banderas adicionales
            );
}

