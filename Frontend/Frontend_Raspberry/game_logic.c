#include "game_logic.h"

// Definición de las dimensiones actualizadas
#define THRESHOLD 40
#define MAX_POSITION 16

// Variables globales para el control de hilos y estado del joystick
volatile bool stopGame = false;
volatile joyinfo_t globalJoy; // Estado global actualizado por thread_joy

// Funciones de movimiento de la rana
// Hilo encargado de mover la rana según el estado del joystick
void *thread_frog(void *arg) {
    frog_t *frog = (frog_t *)arg;
    while (!stopGame) {
        move_frog_by_joystick(frog);
        usleep(10000); // Espera 10 ms
    }
    return NULL;
}

// Hilo encargado de mover la matriz (nivel) del juego
void *thread_matrix(void *arg) {
    uint8_t nivel = *(uint8_t *)arg;
    while (!stopGame) {
        move_matrix_level(nivel);
        usleep(100000); // Espera 100 ms (ajusta este valor según sea necesario)
    }
    return NULL;
}

// Función principal del juego
uint8_t playGame(uint8_t choice, frog_t *frog) {
    sleep(1); // Esperar 1 segundo
    printf("\n[Iniciando el juego...]\n");
    
    disp_init();
    disp_clear();
    disp_update();
    joy_init();

    uint8_t nivel = 1;
    pthread_t threadFrog, threadMatrix;

    // Crear el hilo para mover la rana
    if (pthread_create(&threadFrog, NULL, thread_frog, (void *)frog) != 0) {
        perror("Error al crear el hilo de la rana");
        stopGame = true;
        return 1;
    }
    // Crear el hilo para actualizar la matriz del nivel
    if (pthread_create(&threadMatrix, NULL, thread_matrix, (void *)&nivel) != 0) {
        perror("Error al crear el hilo de la matriz");
        stopGame = true;
        pthread_join(threadFrog, NULL);
        return 1;
    }
    
    // El hilo principal monitorea el botón del joystick para salir del juego
    while (!stopGame) {
        globalJoy = joy_read(); // Actualizar el estado del joystick
        disp_update(); // Actualizar el display

        // Verificar si el botón del joystick ha sido presionado
        if (globalJoy.sw != J_NOPRESS) {
            printf("Botón presionado. Saliendo del juego...\n");
            stopGame = true; // Detener el juego
        }

        usleep(10000); // Esperar 10 ms
    }
    
    // Esperar a que los hilos terminen
    pthread_join(threadFrog, NULL);
    pthread_join(threadMatrix, NULL);

    disp_clear();
    disp_update();
    printf("Saliendo\n");
    
    uint8_t status = 3; // Valor de salida del juego
    printf("status: %d\n", status);
    return status;
}

// Función para mover la rana según el estado del joystick
void move_frog_by_joystick(frog_t *frog) {
    static int8_t prev_x = 0, prev_y = 0;
    joyinfo_t joy = globalJoy;
    static int old_x, old_y;
    int8_t New_x, New_y;

    if (prev_x == 0) {
        if (joy.x > THRESHOLD) {
            if (frog->x < MAX_POSITION) { // Verificar límite derecho
                old_x = frog->x;
                old_y = frog->y;
                handle_move_right(frog);
                New_x = frog->x;
                New_y = frog->y;
                
                // Actualizar display: apagar la posición anterior y encender la nueva
                disp_write((dcoord_t){old_x, old_y}, D_OFF);
                disp_write((dcoord_t){New_x, New_y}, D_ON);
            }
            prev_x = joy.x;
        } else if (joy.x < -THRESHOLD) {
            if (frog->x > 0) { // Verificar límite izquierdo
                old_x = frog->x;
                old_y = frog->y;
                handle_move_left(frog);
                New_x = frog->x;
                New_y = frog->y;
                
                disp_write((dcoord_t){old_x, old_y}, D_OFF);
                disp_write((dcoord_t){New_x, New_y}, D_ON);
            }
            prev_x = joy.x;
        }
    }
    
    if (prev_y == 0) {
        if (joy.y > THRESHOLD) {
            if (frog->y > 0) { // Verificar límite superior
                old_x = frog->x;
                old_y = frog->y;
                handle_move_up(frog);
                New_x = frog->x;
                New_y = frog->y;
                
                disp_write((dcoord_t){old_x, old_y}, D_OFF);
                disp_write((dcoord_t){New_x, New_y}, D_ON);
            }
            prev_y = joy.y;
        } else if (joy.y < -THRESHOLD) {
            if (frog->y < MAX_POSITION) { // Verificar límite inferior
                old_x = frog->x;
                old_y = frog->y;
                handle_move_down(frog);
                New_x = frog->x;
                New_y = frog->y;
                
                disp_write((dcoord_t){old_x, old_y}, D_OFF);
                disp_write((dcoord_t){New_x, New_y}, D_ON);
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

// Función para mover la matriz según el nivel actual
void move_matrix_level(uint8_t nivel) {
    for (uint8_t fila = 0; fila <= 12; fila++) {
        // Para filas pares: desplazamiento a la derecha (1); impares: izquierda (0)
        uint8_t direccion = (fila % 2 == 0) ? 1 : 0;
        
        // Calcular la velocidad según la fila y el nivel
        uint8_t velocidad = calcular_velocidad(fila, nivel);
        
        // Desplazar la fila según la velocidad
        for (uint8_t i = 0; i < velocidad; i++) {
            shift_row(fila, direccion);
        }
        
        // Mostrar la matriz recortada en el display
        mostrar_matriz_recortada();
        usleep(100000);  // Espera de 100 ms
    }
}

// Función para calcular la velocidad de desplazamiento según la fila y el nivel
uint8_t calcular_velocidad(uint8_t fila, uint8_t nivel) {
    // Tabla de velocidades base para 3 niveles y 3 rangos de filas
    uint8_t velocidades_nivel[3][3] = {
        {1, 2, 3},  // Nivel 1: lenta, media, rápida
        {2, 3, 4},  // Nivel 2: media, rápida, muy rápida
        {3, 4, 5}   // Nivel 3: rápida, muy rápida, extremadamente rápida
    };

    uint8_t indice_velocidad;
    if (fila <= 5) {
        indice_velocidad = 0;
    } else if (fila <= 10) {
        indice_velocidad = 1;
    } else {
        indice_velocidad = 2;
    }
    
    // Restamos 1 al nivel ya que los niveles inician en 1
    return velocidades_nivel[nivel - 1][indice_velocidad];
}