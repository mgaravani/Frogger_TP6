#include "game_logic.h"


// Definición de las dimensiones actualizadas



#define THRESHOLD 40
#define MAX_POSITION 16



int playGame(int choice) {
    sleep(1); // Esperar 1 segundo
    printf("\n[Iniciando el juego...]\n");
    disp_init();
    disp_clear();
    initialize_matrix();
    joyinfo_t joy = joy_read();
    frog_t frog_position;
    init_frog(&frog_position, 7, 11.96, 0, 1, 3, 0, 0, 0, 0, 0, 1); // Inicializo la rana
    do
    {
        joy = joy_read();
        //move_frog_by_joystick(&frog_position);
        move_matrix_level(3);
    } while (joy.sw == J_NOPRESS); // Mientras no se presione el switch del joystick, el juego se mantendrá en ejecución
    disp_clear();
    disp_update();
    printf("Saliendo\n");
    return 3; // Retornar un valor para salir del juego
}


void move_frog_by_joystick(frog_t *frog) {
    static int8_t prev_x = 0, prev_y = 0;
    joyinfo_t joy = joy_read();
    static int old_x, old_y;
    int8_t New_x, New_y;

    if (prev_x == 0) {
        if (joy.x > THRESHOLD) {
            if (frog->x < MAX_POSITION) { // Check right boundary
                old_x = frog->x;
                old_y = frog->y;
                handle_move_right(frog);
                New_x = frog->x;
                New_y = frog->y;
                map[old_y][old_x]--; // Resta 1 de la posición anterior
                map[New_y][New_x]++; // Suma 1 a la nueva posición
            }
            prev_x = joy.x;
        } else if (joy.x < -THRESHOLD) {
             if (frog->x > 0) { // Check left boundary
                old_x = frog->x;
                old_y = frog->y;
                handle_move_left(frog);
                New_x = frog->x;
                New_y = frog->y;
                map[old_y][old_x]--; // Resta 1 de la posición anterior
                map[New_y][New_x]++; // Suma 1 a la nueva posición
            }
            prev_x = joy.x;
        }
    }

    if (prev_y == 0) {
        if (joy.y > THRESHOLD) {
            if (frog->y > 0) { // Check up boundary
                old_x = frog->x;
                old_y = frog->y;
                handle_move_up(frog);
                New_x = frog->x;
                New_y = frog->y;
                map[old_y][old_x]--; // Resta 1 de la posición anterior
                map[New_y][New_x]++; // Suma 1 a la nueva posición
            }
            prev_y = joy.y;
        } else if (joy.y < -THRESHOLD) {
            if (frog->y < MAX_POSITION) { // Check down boundary
                old_x = frog->x;
                old_y = frog->y;
                handle_move_down(frog);
                New_x = frog->x;
                New_y = frog->y;
                map[old_y][old_x]--; // Resta 1 de la posición anterior
                map[New_y][New_x]++; // Suma 1 a la nueva posición
            }
            prev_y = joy.y;
        }
    }

    if (joy.x > -THRESHOLD && joy.x < THRESHOLD) {
        prev_x = 0;
    }
    if (joy.y > -THRESHOLD && joy.y < THRESHOLD) {
        prev_y = 0;
    }
}
void move_matrix_level(uint8_t nivel) {
    for (uint8_t fila = 0; fila <= 12; fila++) {
        uint8_t direccion = (fila % 2 == 0) ? 1 : 0;  // Par → derecha (1), Impar → izquierda (0)

        // Calcular la velocidad según la fila y el nivel
        uint8_t velocidad = calcular_velocidad(fila, nivel);

        // Desplazar la fila la cantidad de veces determinada por la velocidad
        for (uint8_t i = 0; i < velocidad; i++) {
            shift_row(fila, direccion);  // Usar shift_row para desplazar la fila
        }

        // Mostrar la matriz recortada en el display (optimizado)
        mostrar_matriz_recortada(map);

        // Esperar un tiempo para controlar la velocidad general del juego (opcional)
        usleep(100000);  // 100 ms 
        printf("bien\n");
        disp_clear();
        disp_update(); 
        printf("saliendo de mostrar\n"); 
    }
}

uint8_t calcular_velocidad(uint8_t fila, uint8_t nivel) {
    // Tabla de velocidades base para cada nivel (puedes ajustarla)
    uint8_t velocidades_nivel[3][3] = {  // Ejemplo para 3 niveles y 3 rangos de filas
        {1, 2, 3},  // Nivel 1: lenta, media, rápida
        {2, 3, 4},  // Nivel 2: media, rápida, muy rápida
        {3, 4, 5}   // Nivel 3: rápida, muy rápida, extremadamente rápida
    };

    // Determinar el índice de velocidad según la fila
    uint8_t indice_velocidad;
    if (fila <= 5) {
        indice_velocidad = 0;
    } else if (fila <= 10) {
        indice_velocidad = 1;
    } else {
        indice_velocidad = 2;
    }

    // Devolver la velocidad correspondiente al nivel y la fila
    return velocidades_nivel[nivel - 1][indice_velocidad]; // Restamos 1 porque los niveles empiezan en 1
}