#include "allegro.h" //Incluyo el Header allegro
#include <stdio.h>
#include <unistd.h> 

/*FUNCION init allegro*/
//Encargada de realizar todas las inicializaciones necesarias para el funcionamento
AllegroResources init_allegro(uint32_t matriz[FILAS][COLUMNAS]) 
{
    AllegroResources resources = {.selected_option = 1 , .obstaculos = matriz} ; //Creo la instancia resources del tipo de dato estructura AllegroResources

    /*CHEQUEO DE INCIALIZACIONES*/

    /*INICIALIZACION DE ALLEGRO*/
    if (!al_init()) {
        printf("Error al inicializar Allegro!\n");
        exit(EXIT_FAILURE); //Ante un fallo termina el programa y borra los recursos
    }
    /*INICIALIZACION DE ALLEGRO IMAGE PARA FONDO*/
    if (!al_init_image_addon()) {
        printf("Error al inicializar Allegro image!\n");
        exit(EXIT_FAILURE); //Ante un fallo termina el programa y borra los recursos
    }
    /*INICIALIZACION DE SISTEMA DE ENTRADA DE TECLADO*/
    if (!al_install_keyboard()) {
        printf("No se pudo instalar el teclado.\n");
        exit(EXIT_FAILURE); //Ante un fallo termina el programa y borra los recursos
    }
    
    /*INICIALIZACION DEl ADDON DE FUENTES*/
    if (!al_init_font_addon()) {
        printf("Error al inicializar Allegro Fonts.\n");
        exit(EXIT_FAILURE); //Ante un fallo termina el programa y borra los recursos
    }

    /*INICIALIZACION DEl ADDON TTF PERMITIENDO TRABAJAR CON FUENTES TRUETYPE*/
    if (!al_init_ttf_addon()) {
        printf("Error al inicializar Allegro TTF.\n");
        exit(EXIT_FAILURE); //Ante un fallo termina el programa y borra los recursos
    }

    /*INICIALIZACION DEl ADDON PRIMITIVES*/
    if (!al_init_primitives_addon()) {
        printf("Error al inicializar Allegro PRIMITIVES.\n");
        exit(EXIT_FAILURE); //Ante un fallo termina el programa y borra los recursos
    }

    //Obtener el modo de pantalla completo
    ALLEGRO_DISPLAY_MODE disp_data; //Creo una variable disp_data con informacion sobre el modo de visualizacion

    /*Utilizo la funcion para obtener el modo de visualizacion, el 0 se usa para obtener el primer modo, el segundo 
    parametro es un puntero al tipo de dato ALLEGRO_DISPLAY_MODE, estructura donde se almacenara la informacion*/
    al_get_display_mode(0, &disp_data); 

    resources.width = disp_data.width; //Obtengo el ancho del modo de visualizacion y lo guardo en el campo width
    resources.height = disp_data.height; //Obtengo el alto del modo de visualizacion y lo guardo en el campo height
    printf("Height %d", resources.height);
    printf("WIDTH %d", resources.width);
    // Configura el display con el flag ALLEGRO_FULLSCREEN para que la pantalla se cree en modo pantalla completa
    al_set_new_display_flags(ALLEGRO_FULLSCREEN);

    /*Creo una pantalla del modo pantalla completa, la guardo en la estructura resources en el campo pantalla*/
    resources.pantalla = al_create_display(resources.width, resources.height); 

    /*ANALIZA SI SE CREO CORRECTAMENTE*/
    if (!resources.pantalla) {
        printf("Error al crear el display!\n");
        exit(EXIT_FAILURE); //Ante un fallo termina el programa y borra los recursos
    }

    // Cargar las fuentes en la estructura resources, en el campo fuentes
    resources.fuentes[0] = al_load_font("resources/Bing Bam Boum.ttf", 200, ALLEGRO_ALIGN_CENTER); // Fuente 1
    resources.fuentes[1] = al_load_font("resources/ChineseDragon.ttf", 200, ALLEGRO_ALIGN_CENTER); // Fuente 2
    resources.fuentes[2] = al_load_font("resources/Chubby Relief.ttf", 200, ALLEGRO_ALIGN_CENTER); // Fuente 3
    resources.fuentes[3] = al_load_font("resources/Copyduck.ttf", 250, ALLEGRO_ALIGN_CENTER); // TITULO FROGGER
    resources.fuentes[4] = al_load_font("resources/Copyduck.ttf", 70, ALLEGRO_ALIGN_CENTER); // MENU INICIO
    /*fea*/ resources.fuentes[5] = al_load_font("resources/Fluo Gums.ttf", 200, ALLEGRO_ALIGN_CENTER); // Fuente 6(solo mayuscula)
    resources.fuentes[6] = al_load_font("resources/FunnyKid.ttf", 200, ALLEGRO_ALIGN_CENTER); // Fuente 7
    resources.fuentes[7] = al_load_font("resources/Smasher 312 Custom.ttf", 200, ALLEGRO_ALIGN_CENTER); // Fuente 8
    resources.fuentes[8] = al_load_font("resources/The Amazing Spider-Man.ttf", 200, ALLEGRO_ALIGN_CENTER); // Fuente 9
    resources.fuentes[9] = al_load_font("resources/The Last Comic On Earth.ttf", 200, ALLEGRO_ALIGN_CENTER); // Fuente 10
    
    /*ANALIZA SI LAS FUENTES SE CARGARON CORRECTAMENTE*/
    for (int i = 0; i < 10; i++) 
    {
        if (!resources.fuentes[i]) 
        {
            printf("Error al cargar la fuente %d!\n", i + 1);
            al_destroy_display(resources.pantalla); //Destruye el display
            exit(EXIT_FAILURE); //Ante un fallo termina el programa y borra los recursos
        }
    }

/*************************************************************************************************
* Inicialización del sistema de eventos                                                          *
* Se crea una cola de eventos que manejará las entradas del sistema,                             *
* como eventos de teclado y pantalla. Se asocia la pantalla del recurso 'resources.pantalla'     *
* con la cola de eventos para monitorear eventos relacionados con esa pantalla.          
*************************************************************************************************/        
//  ALLEGRO_EVENT_QUEUE *event_queue = init_events(resources.pantalla);                             

/*************************************************************************************************
* Bucle principal del menú                                                                       *
* El bucle se mantendrá activo hasta que 'done' sea verdadero.                                   *
* Inicialmente, 'done' está en 'false' para que el menú continúe corriendo.                      *
*************************************************************************************************/ 
/*
bool done = true;
//inicio_partida(resources);
while (!done) {
    // Se llama a la función 'manejo_eventos' que gestiona cualquier evento 
    // capturado en la cola de eventos. Esto incluye detectar entradas de teclado,
    // cierres de ventana, etc., y actuar en consecuencia.
    manejo_eventos(&resources, event_queue);
    
    // 'menu_allegro' se llama en cada iteración del bucle para redibujar el menú
    // en función del estado actual. Dependiendo de la selección del usuario, el menú
    // se actualizará visualmente, mostrando el rectángulo alrededor de la opción seleccionada.
}
*/

    return resources;
}


/*FUNCION menu_allegro*/
//Da inicio al juego mostrando un menu de inicio para seleccionar el modo de juego y dar comienzo a la partida
//Recibe la estructura resources
void menu_allegro(AllegroResources resources)
{   
    // Limpia la pantalla con el color negro
    al_clear_to_color(al_map_rgb(0, 0, 0)); 

    // Dibuja el título "FROGGER" en la parte superior central de la pantalla
    al_draw_text(resources.fuentes[0], al_map_rgb(66, 194, 29), resources.width / 2, resources.height / 8,
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
            int text_width = al_get_text_width(resources.fuentes[4], options[i]);
            //Dibujo un rectangulo de color en funcion del ancho del texto alrededor de el
            al_draw_rectangle(resources.width / 2 - text_width / 2 - 10, y_positions[i] - 10,
                              resources.width / 2 + text_width / 2 + 10, y_positions[i] + 65 + 10,
                              al_map_rgb(255, 255, 255), 3);
        }
        //Escribo el texto con las coordenadas correctas
        al_draw_text(resources.fuentes[4], al_map_rgb(66, 194, 29), resources.width / 2, y_positions[i],
                     ALLEGRO_ALIGN_CENTRE, options[i]);
    }

    al_flip_display();

}


/*FUNCION inicio_partida*/
//TESTEO POR EL MOMENTO
/*
void inicio_partida( uint32_t matriz[FILAS][COLUMNAS])
{   
    
  // Cargar la imagen
ALLEGRO_BITMAP *fondo = al_load_bitmap("resources/Fondo.png");

ALLEGRO_BITMAP *tronco = al_load_bitmap("resources/Tronco.png");
ALLEGRO_BITMAP *auto_D = al_load_bitmap("resources/Auto_D.png");
ALLEGRO_BITMAP *auto_I= al_load_bitmap("resources/Auto_I.png");
ALLEGRO_BITMAP *auto2_D = al_load_bitmap("resources/Auto2_D.png");
ALLEGRO_BITMAP *auto2_I= al_load_bitmap("resources/Auto2_I.png");
ALLEGRO_BITMAP *auto3_D = al_load_bitmap("resources/Auto3_D.png");
ALLEGRO_BITMAP *auto3_I= al_load_bitmap("resources/Auto3_I.png");
ALLEGRO_BITMAP *camion_D = al_load_bitmap("resources/Camion_D.png");
ALLEGRO_BITMAP *camion_I = al_load_bitmap("resources/Camion_I.png");
ALLEGRO_BITMAP *tortuga_D = al_load_bitmap("resources/Tortuga_D.png");
ALLEGRO_BITMAP *tortuga_I = al_load_bitmap("resources/Tortuga_I.png");

// Obtener el ancho y alto originales de la imagen
float original_width = al_get_bitmap_width(fondo);
float original_height = al_get_bitmap_height(fondo);

// Establecer los nuevos anchos y altos escalados según las celdas de la matriz
uint32_t cell_width = 1920 / COLUMNAS; // Defino el ancho de las celdas de la matriz
uint32_t cell_height = 1080 / FILAS;   // Defino el alto de las celdas de la matriz

// Dibujar la imagen escalada a las dimensiones de la celda
al_draw_scaled_bitmap(fondo,
    0, 0,                    // Origen en la imagen (x, y)
    original_width, original_height,  // Ancho y alto de la porción original
    0, 0,                    // Posición de destino (x, y)
    cell_width*COLUMNAS, cell_height*FILAS,          // Ancho y alto escalados a las dimensiones de la celda
    0                        // Flags (0 si no hay)
);

     // Bucle para recorrer celda a celda
    for (uint32_t i = 0; i < FILAS; i++) {
        for (uint32_t j = 0; j < COLUMNAS; j++) {
            // Dibuja un círculo en la posición correcta
            int x = j * cell_width + cell_width / 2; //Defino la coordenada x del centro
            int y = i * cell_height + cell_height / 2; //Defino la coordenada y del centro

            if (matriz[i][j] == 2) 
            {
                al_draw_bitmap(tronco, x, y-25, 0);
            }
             if (matriz[i][j] == 3) 
              {
                al_draw_bitmap(tronco, x, y - 25, 0);
              }
               if (matriz[i][j] == 4) 
                {
                  al_draw_bitmap(tronco, x, y - 25, 0);
                }
                 if (matriz[i][j] == 5) 
                  {
                    al_draw_bitmap(tortuga_D, x, y - 25, 0);
                  }
                   if (matriz[i][j] == 6) 
                    {
                      al_draw_bitmap(tortuga_I, x, y - 38, 0);
                    }
                     if (matriz[i][j] == 8) 
                    {
                      al_draw_bitmap(camion_D, x, y - 25, 0);
                    }
                     if (matriz[i][j] == 9) 
                    {
                      al_draw_bitmap(auto3_I, x, y - 25, 0);
                    }
                     if (matriz[i][j] == 10) 
                    {
                      al_draw_bitmap(auto2_D, x, y - 25, 0);
                    }
                     if (matriz[i][j] == 11) 
                    {
                      al_draw_bitmap(auto_D, x, y - 25, 0);
                    }
                        if (matriz[i][j] == 12) 
                    {
                      al_draw_bitmap(auto3_D, x, y - 38, 0);
                    }
                  }
                }

              al_flip_display();
}
*/


/*FUNCION cleanup_allegro*/
//Borra todos los recursos utilizados
void cleanup_allegro(AllegroResources resources) 
{
    for (int i = 0; i < 10; i++) 
    {
        if (resources.fuentes[i]) 
        {
            al_destroy_font(resources.fuentes[i]);
        }
    }
    if (resources.pantalla) 
    {
        al_destroy_display(resources.pantalla);
    }
}

/*
void prueba_impresion(AllegroResources init)
{   
    static clock_t flags[10] = {0};  // Inicializa el arreglo a 0
    static int x = 0, y = 200, z = 600, c = 0;  // Inicializa fuera de la pantalla a la derecha
    int fila = init.height/14;

    printf("CADA FILA ES DE : %d", fila);
    ALLEGRO_BITMAP *fondo = al_load_bitmap("resources/Fondo.png");
    ALLEGRO_BITMAP *tronco = al_load_bitmap("resources/Tronco.png");
    ALLEGRO_BITMAP *camion_D = al_load_bitmap("resources/Camion_D.png");
    ALLEGRO_BITMAP *tortuga_D = al_load_bitmap("resources/Tortuga_D.png");

    // Dibuja el fondo
    al_draw_scaled_bitmap(fondo,
        0, 0,  // Origen en la imagen (x, y)
        al_get_bitmap_width(fondo), al_get_bitmap_height(fondo),  // Ancho y alto originales
        0, 0,  // Posición de destino (x, y)
        init.width, init.height,  // Escalar a las dimensiones de la pantalla
        0  // Flags (0 si no hay)
    );

    // Verifica si ha pasado el tiempo necesario para mover tronco
    if (((double)(clock() - flags[0])) / CLOCKS_PER_SEC >= 0.001) {
        flags[0] = clock();  // Reinicia el temporizador
        x += 2;
    }

    // Verifica si ha pasado el tiempo necesario para mover camion_D
    if (((double)(clock() - flags[1])) / CLOCKS_PER_SEC >= 0.001) {
        flags[1] = clock();  // Reinicia el temporizador
        y += 4;
    }
    if (((double)(clock() - flags[2])) / CLOCKS_PER_SEC >= 0.001) {
        flags[2] = clock();  // Reinicia el temporizador
        z += 4;
    }
    if (((double)(clock() - flags[3])) / CLOCKS_PER_SEC >= 0.001) {
        flags[3] = clock();  // Reinicia el temporizador
        c += 6;
    }

    // Ajusta la posición de tronco y camion_D para reaparecer desde el principio
    if (x > init.width+150) {
        x = 0;  // Reaparece justo fuera de la pantalla por la izquierda
    }
    if (y > init.width+150) {  
        y = 0;  // Reaparece justo fuera de la pantalla por la izquierda
    }
    if (z > init.width+150) {  
        z = 0; // Reaparece justo fuera de la pantalla por la izquierda
    }
    if (c > init.width+150) {  
        c = 0; // Reaparece justo fuera de la pantalla por la izquierda
    }

    // Dibuja las imágenes en sus nuevas posiciones
    al_draw_bitmap(tronco, x-150, fila*8, 0);
    al_draw_bitmap(camion_D, y-150, fila*6, 0);
    al_draw_bitmap(camion_D, z-150, fila*6, 0);
    al_draw_bitmap(tortuga_D, c-150, fila*3, 0);
    
    al_flip_display();
}
*/
