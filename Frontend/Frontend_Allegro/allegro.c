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
    resources.display = display;

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
    resources.images[13] = al_load_bitmap("Resources/Auto4.png"); // Imagen 14
    resources.images[14] = al_load_bitmap("Resources/cocodrilo.png"); // Imagen 15
    
    /*ANALIZA SI LAS IMAGENES SE CARGARON CORRECTAMENTE*/
    for (uint16_t i = 0; i < 15; i++) 
    {
        if (!resources.images[i]) 
        {
            printf("Error al cargar la imagen %d!\n", i + 1);
            al_destroy_display(resources.display); //Destruye el display
            exit(EXIT_FAILURE); //Ante un fallo termina el programa y borra los recursos
        }
    }

    /*************************************************************************************************
    * Inicialización del sistema de eventos                                                          *
    * Se crea una cola de eventos que manejará las entradas del sistema,                             *
    * como eventos de teclado y pantalla. Se asocia la pantalla del recurso 'resources.pantalla'     *
    * con la cola de eventos para monitorear eventos relacionados con esa pantalla.          
    *************************************************************************************************/        
    ALLEGRO_EVENT_QUEUE *event_queue = init_events(resources.display);                             

    /*************************************************************************************************
    * Bucle principal del menú                                                                       *
    * El bucle se mantendrá activo hasta que 'done' sea verdadero.                                   *
    * Inicialmente, 'done' está en 'false' para que el menú continúe corriendo.                      *
    *************************************************************************************************/ 
    bool done = true;
    //inicio_partida(resources);
    while (!done) {
        // Se llama a la función 'manejo_eventos' que gestiona cualquier evento 
        // capturado en la cola de eventos. Esto incluye detectar entradas de teclado,
        // cierres de ventana, etc., y actuar en consecuencia.
        events_managment(&resources, event_queue);
        
        // 'menu_allegro' se llama en cada iteración del bucle para redibujar el menú
        // en función del estado actual. Dependiendo de la selección del usuario, el menú
        // se actualizará visualmente, mostrando el rectángulo alrededor de la opción seleccionada.
    }


    return resources;
}


//TODAVIA NO FUNCIONA DEL TODO BIEN ASI QUE NUNCA SE REALIZA EL LLAMADO A LA FUNCION
void allegro_menu(AllegroResources resources)
{   
    // Limpia la pantalla con el color negro
    al_clear_to_color(al_map_rgb(0, 0, 0)); 

    // Dibuja el título "FROGGER" en la parte superior central de la pantalla
    al_draw_text(resources.fonts[0], al_map_rgb(66, 194, 29), resources.width / 2, resources.height / 8,
                 ALLEGRO_ALIGN_CENTRE, "FROGGER");

    // Opciones del menú
    const char *options[3] = {"Play Game", "High Scores", "Quit Game"};
    //Coordenadas en Y para los rectangulos
    int y_positions[3] = {
        (resources.height / 8) * 4, // Play Game
        (resources.height / 8) * 5, // High Scores
        (resources.height / 8) * 6  // Quit Game
    };
    //Para ver que opcion esta seleccionada y segun eso pintar la pantalla de determinada forma
    for (int i = 0; i < 3; i++) {
        //Me fijo que opcion esta seleccionada
        if (resources.selected_option == i + 1) {
            //Obtengo el ancho del texto
            int text_width = al_get_text_width(resources.fonts[4], options[i]);
            //Dibujo un rectangulo de color en funcion del ancho del texto alrededor de el
            al_draw_rectangle(resources.width / 2 - text_width / 2 - 10, y_positions[i] - 10,
                              resources.width / 2 + text_width / 2 + 10, y_positions[i] + 65 + 10,
                              al_map_rgb(255, 255, 255), 3);
        }
        //Escribo el texto con las coordenadas correctas
        al_draw_text(resources.fonts[4], al_map_rgb(66, 194, 29), resources.width / 2, y_positions[i],
                     ALLEGRO_ALIGN_CENTRE, options[i]);
    }

    al_flip_display();

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