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
    al_destroy_font(font);
    al_destroy_display(display);

    return 0;
}
