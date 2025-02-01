#include "game_logic.h"


// Definición de las dimensiones actualizadas


// Función para generar la matriz con valores aleatorios de 0 y 1

void *frog_thread(void *arg) {
    
    (void)arg;  // Evitar warning por argumento no usado
    joy_init();
    frog_t frog;
    uint8_t map_recortada[DISP_CANT_X_DOTS][DISP_CANT_Y_DOTS]; // Declarar la matriz recortada de 13x16
    init_frog(&frog, 10, 0, 0, 1, 3, 0, 0, 0, 0, 0, 0);
    initialize_matrix();

    frog.pass_level_state = 0;
    frog.paused_state = 0;
    frog.actual_row = ROWS - 1;

    dcoord_t pos = {DISP_MAX_X >> 1, DISP_MAX_Y - 1};
    dcoord_t npos = pos;
    joyinfo_t coord = {0, 0, J_NOPRESS};
    uint8_t can_move = 1;
    do {
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

        //disp_write(pos, D_OFF);
        map[frog.actual_row][npos.x]++;
        map[frog.actual_row][npos.x]--;
        //disp_write(npos, D_ON);
        disp_update();
        pos = npos;
        for (uint8_t fila = 1; fila <= 15; fila++) {
        uint8_t direccion = (fila % 2 == 0) ? 1 : 0;  // Par → derecha (1), Impar → izquierda (0)
        uint8_t velocidad = 1;  // Desplazar 1 posición por llamada (más lento)
        desplazar_fila(map, fila, direccion, velocidad);  // Usar map, que es 13x20
            
    }
        // Recortar map (13x20) a map_recortada (13x16)
        recortar_matriz(map, map_recortada);

        mostrar_matriz(map_recortada);  // Mostrar la matriz recortada en el display
        //usleep(100000);       // Esperar 500 ms
        
    } while (coord.sw == J_NOPRESS);
    return NULL;
}