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
}