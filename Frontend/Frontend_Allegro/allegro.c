/*------------INCLUDES-----------*/
#include "allegro.h"

/*------Function allegro_init------*/
// Inicializa Allegro y sus addons, crea la instancia de la estructura AllegroResources donde se guardan los datos utilizados
AllegroResources allegro_init(uint8_t map[ROWS][COLUMNS]) 
{
    //Creo la instancia resources del tipo de dato estructura AllegroResources
    AllegroResources resources = {.selected_option = 1 , .menu_state = 1, .highscores_state = 1}; 

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

    if (!al_install_audio()) {
    printf("Error al inicializar el sistema de audio.\n");
    exit(EXIT_FAILURE);
    }

    if (!al_reserve_samples(10)) {
        printf("Error al reservar muestras de audio.\n");
        exit(EXIT_FAILURE);
    }

    if (!al_init_acodec_addon()) {
        printf("Error al inicializar los codecs de audio.\n");
        exit(EXIT_FAILURE);
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
    resources.display = display;

    if (!display) 
    {
        fprintf(stderr, "Fallo al crear la ventana.\n");
        exit(EXIT_FAILURE);
    }

    resources.sounds[0] = al_load_sample("Resources/move.wav");
    //resources.sounds[1] = al_load_sample("Resources/frog_arrival.wav");
    
    for (int i = 0; i < SOUNDS ; i++) 
    {
        if (!resources.sounds[i]) 
        {
            printf("Error al cargar el sonido %d!\n", i + 1);
            al_destroy_display(resources.display);
            exit(EXIT_FAILURE);
        }
    }

    // Cargar las fuentes en la estructura resources, en el campo fuentes
    resources.fonts[0] = al_load_font("Resources/Bing Bam Boum.ttf", 45, ALLEGRO_ALIGN_CENTER); // Fuente 1
    resources.fonts[1] = al_load_font("Resources/ChineseDragon.ttf", 100, ALLEGRO_ALIGN_CENTER); // USADA PARA CALCULO DE RECTANGULOS BLANCOS EN MENU DE INICIO
    resources.fonts[2] = al_load_font("Resources/Chubby Relief.ttf", 45, ALLEGRO_ALIGN_CENTER); // Fuente 3
    resources.fonts[3] = al_load_font("Resources/Copyduck.ttf", 45, ALLEGRO_ALIGN_CENTER); // TITULO FROGGER
    resources.fonts[4] = al_load_font("Resources/Copyduck.ttf", 45, ALLEGRO_ALIGN_CENTER); // HIGHSCORES
    resources.fonts[5] = al_load_font("Resources/FunnyKid.ttf", 45, ALLEGRO_ALIGN_CENTER); // Fuente 6

    /*ANALIZA SI LAS FUENTES SE CARGARON CORRECTAMENTE*/
    for (uint16_t i = 0; i < FONTS ; i++) 
    {
        if (!resources.fonts[i])
        {
            printf("Error al cargar la fuente %d!\n", i + 1);
            al_destroy_display(resources.display); //Destruye el display
            exit(EXIT_FAILURE); //Ante un fallo termina el programa y borra los recursos
        }
    }

    //Cargo las imagenes en la estructura resources, en el campo images
    resources.images[0] = al_load_bitmap("Resources/background.png"); // Imagen 1
    resources.images[1] = al_load_bitmap("Resources/Tronco.png"); // Imagen 2
    resources.images[2] = al_load_bitmap("Resources/car_R.png"); // Imagen 3
    resources.images[3] = al_load_bitmap("Resources/car_L.png"); // Imagen 4
    resources.images[4] = al_load_bitmap("Resources/car2_R.png"); // Imagen 5
    resources.images[5] = al_load_bitmap("Resources/car2_L.png"); // Imagen 6
    resources.images[6] = al_load_bitmap("Resources/car3_R.png"); // Imagen 7
    resources.images[7] = al_load_bitmap("Resources/car3_L.png"); // Imagen 8
    resources.images[8] = al_load_bitmap("Resources/truck_R.png"); // Imagen 9
    resources.images[9] = al_load_bitmap("Resources/truck_L.png"); // Imagen 10
    resources.images[10] = al_load_bitmap("Resources/tortoise_2_L.png"); // Imagen 11
    resources.images[11] = al_load_bitmap("Resources/tortoise_2_R.png"); // Imagen 12
    resources.images[12] = al_load_bitmap("Resources/tortoise_3_L.png"); // Imagen 13
    resources.images[13] = al_load_bitmap("Resources/tortoise_3_R.png"); // Imagen 14
    resources.images[14] = al_load_bitmap("Resources/frog_front.png"); // Imagen 15
    resources.images[15] = al_load_bitmap("Resources/car4_L.png"); // Imagen 16
    resources.images[16] = al_load_bitmap("Resources/crocodile.png"); // Imagen 17
    resources.images[17] = al_load_bitmap("Resources/frog_L.png"); // Imagen 18
    resources.images[18] = al_load_bitmap("Resources/frog_R.png"); // Imagen 19
    resources.images[19] = al_load_bitmap("Resources/frog_back.png"); // Imagen 20
    resources.images[20] = al_load_bitmap("Resources/frog_die.png"); // Imagen 21
    resources.images[21] = al_load_bitmap("Resources/menubackground.png"); // Imagen 22
    resources.images[22] = al_load_bitmap("Resources/heart.png"); // Imagen 23
    
    /*ANALIZA SI LAS IMAGENES SE CARGARON CORRECTAMENTE*/
    for (uint16_t i = 0; i < IMAGES ; i++) 
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

//FALTA CORREGIR EL RELLAMADO
/*------Function allegro_menu------*/
// Función para mostrar el menú de inicio
void allegro_menu(AllegroResources *resources)
{   
    // Limpia la pantalla con el color negro
    al_clear_to_color(al_map_rgb(0, 0, 0)); 
    
    image_drawing(resources->images[21],0,0,0,0,resources->width, resources->height);

    // Opciones del menú
    const char *options[3] = {"Play Game", "High Scores", "Quit Game"};
    //Coordenadas en Y para los rectangulos
    uint16_t y_positions[3] = {
        (resources->height / 8) * 4.85, // Play Game
        (resources->height / 8) * 5.65, // High Scores
        (resources->height / 8) * 6.46  // Quit Game
    };
    //Para ver que opcion esta seleccionada y segun eso pintar la pantalla de determinada forma
    for (uint16_t i = 0; i < 3; i++) {
        //Me fijo que opcion esta seleccionada
        if (resources->selected_option == i+1 ) {
            //Obtengo el ancho del texto
            u_int32_t text_width = al_get_text_width(resources->fonts[1], options[i]);
            //Dibujo un rectangulo de color en funcion del ancho del texto alrededor de el
            al_draw_rectangle(resources->width / 2 - text_width / 3 - 10, y_positions[i] - 1,
                              resources->width / 2 + text_width / 3 + 10, y_positions[i] + 31,
                              al_map_rgb(255, 255, 255), 3);
        }

    }

    al_flip_display();
    
}

//TODAVIA NO DIBUJA COMO ME GUSTARIA
/*------Function menu_highscores------*/
// Función para mostrar los highscores
void menu_highscores(FILE *pointer_highscores, AllegroResources *resources)
{
    // Limpia la pantalla con el color negro
    al_clear_to_color(al_map_rgb(0, 0, 0));

    rewind(pointer_highscores); // Rebobina el archivo para leer desde el inicio

    char line[256]; // Buffer para almacenar cada línea
    u_int16_t y_position = resources->height / 4; // Comienza a dibujar en 1/4 de la pantalla
    const u_int16_t line_spacing = 50;           // Espaciado entre líneas

    while (fgets(line, sizeof(line), pointer_highscores)) 
    {
        line[strcspn(line, "\n")] = 0; // Elimina el salto de línea al final

        al_draw_text(resources->fonts[4], al_map_rgb(220, 250, 6), 
                     resources->width / 4, y_position, 0, line);

        y_position += line_spacing; // Ajusta la posición para la siguiente línea
    }

    al_flip_display(); // Muestra los cambios en pantalla
    //FALTA AGREGAR ALGO PARA QUE TE SAQUE DE ESTE MENU
}


/*------Function Cleanup_allegro------*/
//Borra todos los recursos utilizados
void cleanup_allegro(AllegroResources *resources) 
{
    printf("Saliendo del programa...\n");

    // Destruir los recursos utilizados
    for (int i = 0; i < SOUNDS; i++) { // USAR UNA MACRO PARA MAXIMOS SONIDOS, IMAGENES, ETC.
    if (resources->sounds[i]) {
        al_destroy_sample(resources->sounds[i]);
    }
    }

    for (int i = 0; i < FONTS; i++) 
    {
        if (resources->fonts[i]) 
        {
            al_destroy_font(resources->fonts[i]);
        }
    }

    for (int i = 0; i < IMAGES; i++) 
    {
        if (resources->images[i]) 
        {
            al_destroy_bitmap(resources->images[i]);
        }
    }

    if (resources->display) 
    {
        al_destroy_display(resources->display);
    }
}