/*------------INCLUDES-----------*/
#include "allegro.h"

/*------Function allegro_init------*/
// Inicializa Allegro y sus addons, crea la instancia de la estructura AllegroResources donde se guardan los datos utilizados
AllegroResources allegro_init(uint8_t map[ROWS][COLUMNS]) 
{
    //Creo la instancia resources del tipo de dato estructura AllegroResources
    AllegroResources resources = {.selected_option = 1}; 

    // Inicializa Allegro y sus addons
    if (!al_init()) 
    {
        printf("Error al inicializar Allegro!\n");
        exit(EXIT_FAILURE); //Ante un fallo termina el programa y borra los recursos
    }

    if (!al_init_image_addon()) 
    {
        printf("Error al inicializar Allegro image!\n");
        exit(EXIT_FAILURE); //Ante un fallo termina el programa y borra los recursos
    }

    if (!al_install_keyboard()) 
    {
        printf("No se pudo instalar el teclado.\n");
        exit(EXIT_FAILURE); //Ante un fallo termina el programa y borra los recursos
    }
    
    if (!al_init_font_addon()) 
    {
        printf("Error al inicializar Allegro Fonts.\n");
        exit(EXIT_FAILURE); //Ante un fallo termina el programa y borra los recursos
    }

    if (!al_init_ttf_addon()) 
    {
        printf("Error al inicializar Allegro TTF.\n");
        exit(EXIT_FAILURE); //Ante un fallo termina el programa y borra los recursos
    }

    if (!al_init_primitives_addon()) 
    {
        printf("Error al inicializar Allegro PRIMITIVES.\n");
        exit(EXIT_FAILURE); //Ante un fallo termina el programa y borra los recursos
    }
    
    // Crea una ventana
    resources.width = WIDTH;
    resources.height = HEIGHT;

    ALLEGRO_DISPLAY *display = al_create_display(resources.width, resources.height);

    if (!display) 
    {
        fprintf(stderr, "Fallo al crear la ventana.\n");
        exit(EXIT_FAILURE);
    }

    // Cargar las fuentes en la estructura resources, en el campo fuentes
    resources.fonts[0] = al_load_font("Resources/Bing Bam Boum.ttf", 200, ALLEGRO_ALIGN_CENTER); // Fuente 1
    resources.fonts[1] = al_load_font("Resources/ChineseDragon.ttf", 200, ALLEGRO_ALIGN_CENTER); // Fuente 2
    resources.fonts[2] = al_load_font("Resources/Chubby Relief.ttf", 200, ALLEGRO_ALIGN_CENTER); // Fuente 3
    resources.fonts[3] = al_load_font("Resources/Copyduck.ttf", 250, ALLEGRO_ALIGN_CENTER); // TITULO FROGGER
    resources.fonts[4] = al_load_font("Resources/Copyduck.ttf", 70, ALLEGRO_ALIGN_CENTER); // MENU INICIO
    /*fea*/ resources.fonts[5] = al_load_font("Resources/Fluo Gums.ttf", 200, ALLEGRO_ALIGN_CENTER); // Fuente 6(solo mayuscula)
    resources.fonts[6] = al_load_font("Resources/FunnyKid.ttf", 200, ALLEGRO_ALIGN_CENTER); // Fuente 7
    resources.fonts[7] = al_load_font("Resources/Smasher 312 Custom.ttf", 200, ALLEGRO_ALIGN_CENTER); // Fuente 8
    resources.fonts[8] = al_load_font("Resources/The Amazing Spider-Man.ttf", 200, ALLEGRO_ALIGN_CENTER); // Fuente 9
    resources.fonts[9] = al_load_font("Resources/The Last Comic On Earth.ttf", 200, ALLEGRO_ALIGN_CENTER); // Fuente 10

    /*ANALIZA SI LAS FUENTES SE CARGARON CORRECTAMENTE*/
    for (uint16_t i = 0; i < 10; i++) 
    {
        if (!resources.fonts[i]) 
        {
            printf("Error al cargar la fuente %d!\n", i + 1);
            al_destroy_display(resources.display); //Destruye el display
            exit(EXIT_FAILURE); //Ante un fallo termina el programa y borra los recursos
        }
    }

    //Cargo las imagenes en la estructura resources, en el campo images
    resources.images[0] = al_load_bitmap("Resources/Fondo.png"); // Imagen 1
    resources.images[1] = al_load_bitmap("Resources/Tronco.png"); // Imagen 2
    resources.images[2] = al_load_bitmap("Resources/Auto_D.png"); // Imagen 3
    resources.images[3] = al_load_bitmap("Resources/Auto_I.png"); // Imagen 4
    resources.images[4] = al_load_bitmap("Resources/Auto2_D.png"); // Imagen 5
    resources.images[5] = al_load_bitmap("Resources/Auto2_I.png"); // Imagen 6
    resources.images[6] = al_load_bitmap("Resources/Auto3_D.png"); // Imagen 7
    resources.images[7] = al_load_bitmap("Resources/Auto3_I.png"); // Imagen 8
    resources.images[8] = al_load_bitmap("Resources/Camion_D.png"); // Imagen 9
    resources.images[9] = al_load_bitmap("Resources/Camion_I.png"); // Imagen 10
    resources.images[10] = al_load_bitmap("Resources/Tortuga_D.png"); // Imagen 11
    resources.images[11] = al_load_bitmap("Resources/Tortuga_I.png"); // Imagen 12
    resources.images[12] = al_load_bitmap("Resources/ranita.png"); // Imagen 13
    
    /*ANALIZA SI LAS IMAGENES SE CARGARON CORRECTAMENTE*/
    for (uint16_t i = 0; i < 12; i++) 
    {
        if (!resources.images[i]) 
        {
            printf("Error al cargar la imagen %d!\n", i + 1);
            al_destroy_display(resources.display); //Destruye el display
            exit(EXIT_FAILURE); //Ante un fallo termina el programa y borra los recursos
        }
    }
    return resources;
}

/*------Function Cleanup_allegro------*/
//Borra todos los recursos utilizados
void cleanup_allegro(AllegroResources *resources) 
{
    for (int i = 0; i < 10; i++) 
    {
        if (resources->fonts[i]) 
        {
            al_destroy_font(resources->fonts[i]);
        }
        if(resources->images[i])
        {
            al_destroy_bitmap(resources->images[i]);
        }
    }
    if (resources->display) 
    {
        al_destroy_display(resources->display);
    }
}