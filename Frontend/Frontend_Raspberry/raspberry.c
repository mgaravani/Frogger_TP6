#include "raspberry.h"

void ShowFrogger(void); // Declaración de ShowFrogger
int8_t ShowMenu(void); // Declaración de ShowMenu
extern map_t map;
int main() {
    int choice = 0;
    int running = 1; // Variable de control para mantener el programa en ejecución
    ShowFrogger();
    while (running) { // Mientras `running` sea 1, el menú se mostrará
       while (choice == 0)
       {
         choice = ShowMenu(); // Mostrar el menú
        
        switch (choice) {
            case 1:	
                choice = playGame(choice); // Lógica del juego
                break;
            case 2:
                printf("Saliendo del juego. ¡Hasta pronto!\n");
                running = 0; // Cambiar el valor de `running` para salir del bucle
                break;
            default:
                printf(".\n");
        }
       }
    }
    return 0;
}

void ShowFrogger(void) {
    uint8_t display[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS] = {0}; // Matriz del display 16x16


    uint8_t froggerBitmap[DISP_CANT_Y_DOTS][46] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    
};

    for (int offset = 0; offset <= 46 - DISP_CANT_X_DOTS; offset++) {
        shiftDisplay(display, froggerBitmap, offset); // Desplazar la vista del display
        mostrar_matriz(display);                       // Imprimir el display actual
        usleep(200000);                              // Pausa de 200 ms
    }
    sleep(.5);//pausa de 0.5 segundos 
}

int8_t ShowMenu(void) {
    int8_t  status = 0;
    uint8_t menuBitmap[16][16] = {
        // "PLAY" (Arriba)
        {0,0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, },
        {0,1, 1, 1, 0, 1,  0, 0, 1, 1, 1, 0, 0, 1,  0, 1, },
        {0,1, 0, 1, 0, 1,  0, 0, 1, 0, 1, 0, 0, 1,  0, 1, },
        {0,1, 1, 1, 0, 1,  0, 0, 1, 1, 1, 0, 0, 0,  1, 0, },
        {0,1, 0, 0, 0, 1,  0, 0, 1, 0, 1, 0, 0, 1,  0, 0, },
        {0,1, 0, 0, 0, 1,  1, 0, 1, 0, 1, 0, 1, 0,  0, 0, },
        {0,0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, },
        {0,0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, },

        // "EXIT" (Abajo)
        {0, 0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0},
        {0, 1, 1, 1, 0,  1, 0, 1, 0,  1, 1, 1, 0,  1, 1, 1},
        {0, 1, 0, 0, 0,  1, 0, 1, 0,  0, 1, 0, 0,  0, 1, 0},
        {0, 1, 1, 1, 0,  0, 1, 0, 0,  0, 1, 0, 0,  0, 1, 0},
        {0, 1, 0, 0, 0,  1, 0, 1, 0,  0, 1, 0, 0,  0, 1, 0},
        {0, 1, 1, 1, 0,  1, 0, 1, 0,  1, 1, 1, 0,  0, 1, 0},
        {0, 0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0},
        {0, 0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0}
    };
    mostrar_matriz(menuBitmap);
    joy_init();	
    joyinfo_t coord = {0,0,J_NOPRESS};
    do {
        coord = joy_read();
        if (coord.y > THRESHOLD) {//estado de arriba
            status = 1;
        }
        if (coord.y < -THRESHOLD) {//estado de abajo
            status = 2;
        }       
    }while (coord.sw == J_NOPRESS  );//termina si se presiona el switch
    uint8_t mat0[16][16]= {0};
    mostrar_matriz(mat0);
    return status; // Asegúrate de retornar un valor
}



/*
// Hilo de la matriz
void *matrix_thread(void *arg) {
    (void)arg;  // Evitar warning por argumento no usado

    initialize_matrix(); // Generar la matriz inicial
    //joyinfo_t coord;

    // Declarar la matriz recortada de 13x16
    uint8_t map_recortada[DISP_CANT_X_DOTS][DISP_CANT_Y_DOTS];  

    do {
        for (uint8_t fila = 1; fila <= 15; fila++) {
            uint8_t direccion = (fila % 2 == 0) ? 1 : 0;  // Par → derecha (1), Impar → izquierda (0)
            desplazar_fila(map, fila, direccion);  // Usar map, que es 13x20
        }

        // Recortar map (13x20) a map_recortada (13x16)
        recortar_matriz(map, map_recortada);

        mostrar_matriz(map_recortada);  // Mostrar la matriz recortada en el display
        usleep(500000);       // Esperar 500 ms

        coord = joy_read();    // Leer estado del joystick para salir si es necesario
    } while (coord.sw == J_NOPRESS);

    return NULL;
}*/
void *frog_thread(void *arg) {
    usleep(500000);
    (void)arg;  // Evitar warning por argumento no usado
    joy_init();
    frog_t frog;
    uint8_t map_recortada[DISP_CANT_X_DOTS][DISP_CANT_Y_DOTS]; // Declarar la matriz recortada de 13x16
    init_frog(&frog, 0, 0, 0, 1, 3, 0, 0, 0, 0, 0, 1);
    initialize_matrix();

    frog.pass_level_state = 0;
    frog.paused_state = 0;
    frog.actual_row = ROWS - 1;

    dcoord_t pos = {DISP_MAX_X >> 1, DISP_MAX_Y - 1};
    dcoord_t npos = pos;
    joyinfo_t coord = {0, 0, J_NOPRESS};
    uint8_t can_move = 1;
    do {
        disp_update();
        coord = joy_read();

        if (coord.x > -THRESHOLD_OFF && coord.x < THRESHOLD_OFF &&
            coord.y > -THRESHOLD_OFF && coord.y < THRESHOLD_OFF) {
            can_move = 1;
        }

        if (can_move && coord.x > THRESHOLD && npos.x < DISP_MAX_X) {
            handle_move_right(&frog);
            npos.x++;
            can_move = 0;
        }
        if (can_move && coord.x < -THRESHOLD && npos.x > DISP_MIN) {
            handle_move_left(&frog);
            npos.x--;
            can_move = 0;
        }
        if (can_move && coord.y > THRESHOLD && npos.y > DISP_MIN) {
            handle_move_up(&frog);
            npos.y--;
            can_move = 0;
        }
        if (can_move && coord.y < -THRESHOLD && npos.y < DISP_MAX_Y) {
            handle_move_down(&frog);
            npos.y++;
            can_move = 0;
        }

        disp_write(pos, D_OFF);
        disp_write(npos, D_ON);
        disp_update();
        pos = npos;
        for (uint8_t fila = 1; fila <= 15; fila++) {
        uint8_t direccion = (fila % 2 == 0) ? 1 : 0;  // Par → derecha (1), Impar → izquierda (0)
        uint8_t velocidad = 1;  // Desplazar 2 posiciones por llamada
        desplazar_fila(map, fila, direccion, velocidad);  // Usar map, que es 13x20
    }

        // Recortar map (13x20) a map_recortada (13x16)
        recortar_matriz(map, map_recortada);

        mostrar_matriz(map_recortada);  // Mostrar la matriz recortada en el display
        usleep(100000);       // Esperar 500 ms
        
    } while (coord.sw == J_NOPRESS);
    return NULL;
}
// Función principal del juego
int playGame(int choice) {
    printf("\n[Iniciando el juego...]\n");
    disp_init();
    disp_clear();
    extern map_t map; // Declarar la variable global map
   // pthread_t matrix_tid;
    //pthread_create(&matrix_tid, NULL, matrix_thread, NULL);  // Crear el hilo de la matriz
    pthread_t frog_tid;
    pthread_create(&frog_tid, NULL, frog_thread, NULL);  // Crear el hilo de la rana
   // pthread_join(matrix_tid, NULL);  // Esperar a que termine el hilo de la matriz
    pthread_join(frog_tid, NULL);  // Esperar a que termine el hilo de la rana
    disp_clear();
    disp_update();


    return 0;
}



void shiftDisplay(uint8_t display[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS], uint8_t bitmap[DISP_CANT_Y_DOTS][46], int offset) {
    // Copiar una ventana de 16x16 del bitmap al display
    for (int y = 0; y < DISP_CANT_Y_DOTS; y++) {
        for (int x = 0; x < DISP_CANT_X_DOTS; x++) {
            display[y][x] = bitmap[y][x + offset];
        }
    }
}
