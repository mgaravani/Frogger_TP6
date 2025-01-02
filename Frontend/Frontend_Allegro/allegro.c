#include "allegro.h"

void mostrar_mensaje() {
    // Inicializa Allegro y sus addons
    if (!al_init()) {
        fprintf(stderr, "Fallo al inicializar Allegro.\n");
        return;
    }

    if (!al_init_font_addon()) {
        fprintf(stderr, "Fallo al inicializar el addon de fuentes.\n");
        return;
    }

    if (!al_init_ttf_addon()) {
        fprintf(stderr, "Fallo al inicializar el addon de fuentes TTF.\n");
        return;
    }
    if (!al_init_image_addon()) {
        fprintf(stderr, "Fallo al inicializar el addon de imágenes.\n");
        return;
    }

    // Crea una ventana
    ALLEGRO_DISPLAY *display = al_create_display(1000, 800);
    if (!display) {
        fprintf(stderr, "Fallo al crear la ventana.\n");
        return;
    }

    // Carga una fuente (asegúrate de tener el archivo .ttf adecuado)
    ALLEGRO_FONT *font = al_load_font("Resources/Copyduck.ttf", 36, 0);
    if (!font) {
        fprintf(stderr, "Fallo al cargar la fuente: %s\n", "arial.ttf");
        
    }

    // Carga una imagen
    ALLEGRO_BITMAP *image = al_load_bitmap("Resources/Fondo.png");
    if (!image) {
        fprintf(stderr, "Fallo al cargar la imagen: %s\n", "Resources/Fondo.png");
        al_destroy_font(font);
        al_destroy_display(display);
        return;
    }

    // Limpiar pantalla
    al_clear_to_color(al_map_rgb(0, 0, 0)); // Fondo negro

    // Dibuja la imagen escalada a 1000x800
    al_draw_scaled_bitmap(
        image,                  // Imagen original
        0, 0,                   // Coordenadas en la imagen original
        al_get_bitmap_width(image),  // Ancho original de la imagen
        al_get_bitmap_height(image), // Altura original de la imagen
        0, 0,                   // Posición en la pantalla
        1000, 800,               // Nuevo ancho y alto de la imagen escalada
        0                       // Sin banderas adicionales
    );

    // Dibujar el texto
    al_draw_text(font, al_map_rgb(255, 255, 255), 500, 550, ALLEGRO_ALIGN_CENTRE, "¡Hola, Allegro!");

    // Muestra la ventana
    al_flip_display();

    // Espera 5 segundos
    al_rest(5.0);

    // Limpieza
    al_destroy_bitmap(image);
    al_destroy_font(font);
    al_destroy_display(display);
}