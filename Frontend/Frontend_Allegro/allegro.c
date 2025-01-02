<<<<<<< HEAD
#include "allegro.h" //Incluyo el Header allegro
#include <stdio.h>
#include <unistd.h> 

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

int main() {
    // Inicializa Allegro y sus addons
    if (!al_init()) {
        fprintf(stderr, "Fallo al inicializar Allegro.\n");
        return -1;
    }

    if (!al_init_font_addon()) {
        fprintf(stderr, "Fallo al inicializar el addon de fuentes.\n");
        return -1;
    }

    if (!al_init_ttf_addon()) {
        fprintf(stderr, "Fallo al inicializar el addon de fuentes TTF.\n");
        return -1;
    }

    // Crea una ventana
    ALLEGRO_DISPLAY *display = al_create_display(800, 600);
    if (!display) {
        fprintf(stderr, "Fallo al crear la ventana.\n");
        return -1;
    }

    // Carga una fuente (asegúrate de tener el archivo .ttf adecuado)
    ALLEGRO_FONT *font = al_load_font("arial.ttf", 36, 0);
    if (!font) {
        fprintf(stderr, "Fallo al cargar la fuente.\n");
        al_destroy_display(display);
        return -1;
    }

    // Establece el color para el texto
    al_clear_to_color(al_map_rgb(0, 0, 0)); // Fondo negro
    al_draw_text(font, al_map_rgb(255, 255, 255), 400, 300, ALLEGRO_ALIGN_CENTRE, "¡Hola, Allegro!");

    // Muestra el mensaje
    al_flip_display();

    // Espera 5 segundos antes de cerrar
    al_rest(5.0);

    // Limpieza
=======
#include "allegro.h"

int main() {
    // Inicialización de Allegro
    if (!al_init()) {
        fprintf(stderr, "Error: No se pudo inicializar Allegro.\n");
        return -1;
    }

    // Crear ventana
    ALLEGRO_DISPLAY *display = al_create_display(800, 600);
    if (!display) {
        fprintf(stderr, "Error: No se pudo crear la ventana.\n");
        return -1;
    }
    al_set_window_title(display, "Mostrar mensaje con Allegro");

    // Inicializar addon de fuentes y TTF
    if (!al_init_font_addon()) {
        fprintf(stderr, "Error: No se pudo inicializar el addon de fuentes.\n");
        return -1;
    }
    if (!al_init_ttf_addon()) {
        fprintf(stderr, "Error: No se pudo inicializar el addon TTF.\n");
        return -1;
    }

    // Cargar una fuente
    ALLEGRO_FONT *font = al_load_ttf_font("arial.ttf", 36, 0);
    if (!font) {
        fprintf(stderr, "Error: No se pudo cargar la fuente TTF.\n");
        return -1;
    }

    // Dibujar texto
    al_clear_to_color(al_map_rgb(0, 0, 0)); // Fondo negro
    al_draw_text(font, al_map_rgb(255, 255, 255), 400, 280, ALLEGRO_ALIGN_CENTER, "¡Hola, Allegro!");
    al_flip_display();

    // Esperar antes de cerrar
    al_rest(3.0); // Pausa de 3 segundos

    // Liberar recursos
>>>>>>> f64edde (Solucion Make)
    al_destroy_font(font);
    al_destroy_display(display);

    return 0;
}