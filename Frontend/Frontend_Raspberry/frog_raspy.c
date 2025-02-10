#include "frog_raspy.h"


void update_frog_position(frog_t *frog) {
    static uint8_t last_x_dir = 0;  // Última dirección en X detectada
    static uint8_t last_y_dir = 0;  // Última dirección en Y detectada

    joyinfo_t joy_state = joy_read();

    // Detectar movimiento en el eje X (sin cambios)
    if (joy_state.x > THRESHOLD) {
        if (last_x_dir != 1) {
            uint8_t new_x = get_frog_x(frog) + 1;
            if (new_x < DISP_CANT_X_DOTS) {  // Verificar que no exceda el límite del display
                set_frog_x(frog, new_x);
            }
            last_x_dir = 1;
        }
    } else if (joy_state.x < -THRESHOLD) {
        if (last_x_dir != 2) {
            uint8_t new_x = get_frog_x(frog) - 1;
            if (new_x < DISP_CANT_X_DOTS) {  // Verificar que no sea menor que 0 (underflow)
                set_frog_x(frog, new_x);
            }
            last_x_dir = 2;
        }
    } else if (abs(joy_state.x) < THRESHOLD_OFF) {
        last_x_dir = 0;  // Resetear la dirección cuando el joystick vuelve al centro
    }

    // Detectar movimiento en el eje Y (dirección invertida)
    if (joy_state.y > THRESHOLD) {
        if (last_y_dir != 1) {
            uint8_t new_y = get_frog_y(frog) - 1;  // Disminuir Y en lugar de aumentar
            if (new_y < DISP_CANT_Y_DOTS) {  // Verificar que no sea menor que 0 (underflow)
                set_frog_y(frog, new_y);
            }
            last_y_dir = 1;
        }
    } else if (joy_state.y < -THRESHOLD) {
        if (last_y_dir != 2) {
            uint8_t new_y = get_frog_y(frog) + 1;  // Aumentar Y en lugar de disminuir
            if (new_y < DISP_CANT_Y_DOTS) {  // Verificar que no exceda el límite del display
                set_frog_y(frog, new_y);
            }
            last_y_dir = 2;
        }
    } else if (abs(joy_state.y) < THRESHOLD_OFF) {
        last_y_dir = 0;  // Resetear la dirección cuando el joystick vuelve al centro
    }
    if (get_frog_y(frog) <= 6 && get_frog_y(frog) > 1) {
        set_frog_move(frog, 1);
    }
    if (get_frog_y(frog) > 6) {
        set_frog_move(frog, 0);
    }
    
}
uint8_t detect_arrival_raspy(frog_t *frog) {
    // Ajusta las columnas y filas en función de la posición de la rana
    uint8_t frog_col = (uint8_t)(get_frog_x(frog));
    uint8_t frog_row = (uint8_t)get_frog_y(frog);

    // Convertir la posición de la rana según la transformación de map a matriz
    uint8_t matrix_col = frog_col ;
    uint8_t matrix_row = frog_row ;

    // Verifica si la rana llegó a la fila 2 de la matriz
    if (matrix_row == 1) {
        // Si el lugar está libre (matriz[matrix_row][matrix_col] == 0), marca la posición como ocupada
        if (matriz[matrix_row][matrix_col] == 0) {
            matriz[matrix_row][matrix_col] = 1; // Marca la posición como ocupada
            disp_write((dcoord_t){frog_col, frog_row}, D_ON); // Enciende el punto en la pantalla
            disp_update();  // Actualiza la pantalla
            sleep(1);  // Espera 1 segundo
            frog->arrival_state = 1;
            increase_frog_points(frog, 50); // Sumar puntos por llegada

            // Reiniciar las filas alcanzadas por la rana
            for (uint8_t i = 0; i < ROWS; i++) {
                frog->reached_rows[i] = 0;
            }

            return 1; // Indica que la rana llegó a la fila 2
        } 
        // Si la posición ya está ocupada (matriz[matrix_row][matrix_col] == 1)
        else if (matriz[matrix_row][matrix_col] == 1) {
            // Si la posición ya está ocupada, marca la rana como muerta
            set_frog_move(frog, 0); // Detener el movimiento de la rana
            set_frog_life(frog, 1);  // Vida en 1 (podría ser un valor de vida completa)
            set_frog_dead(frog, 1);  // Marcar la rana como muerta
        }
    }
    
    // Si la rana no llegó a la fila 2, simplemente retornamos 0
    return 0;
}

