#include "frog_raspy.h"

#include "frog_raspy.h"

void move_frog_by_joystick(frog_t *frog) {
    dcoord_t pos = {frog->x, frog->y};  // Posición actual de la rana
    dcoord_t npos = pos;                // Próxima posición
    joyinfo_t coord = {0, 0, J_NOPRESS}; // Coordenadas medidas del joystick

    coord = joy_read();  // Lee el estado del joystick
    
    // Establece la próxima posición según las coordenadas medidas
    if (coord.x > THRESHOLD && npos.x < DISP_CANT_X_DOTS - 1) {
        npos.x++;
    }
    if (coord.x < -THRESHOLD && npos.x > 0) {
        npos.x--;
    }
    if (coord.y > THRESHOLD && npos.y > 0) {
        npos.y--;
    }
    if (coord.y < -THRESHOLD && npos.y < DISP_CANT_Y_DOTS - 1) {
        npos.y++;
    }

    // Actualiza la matriz de display
    disp_write(pos, D_OFF);  // Apaga la posición anterior en el buffer
    disp_write(npos, D_ON);  // Enciende la nueva posición en el buffer

    // Actualiza la posición de la rana
    frog->x = npos.x;
    frog->y = npos.y;

    // Imprime las coordenadas del joystick y la posición de la rana
    printf("Joystick: (%4d,%4d) | Frog Position: (%2d,%2d)\n", coord.x, coord.y, frog->x, frog->y);
}


#define MAX_COORD 16  // Valor máximo para x e y

void update_frog_position(frog_t *frog) {
    static uint8_t last_x_dir = 0;  // Última dirección en X detectada
    static uint8_t last_y_dir = 0;  // Última dirección en Y detectada

    joyinfo_t joy_state = joy_read();

    // Detectar movimiento en el eje X
    if (joy_state.x > THRESHOLD) {
        if (last_x_dir != 1) {
            uint8_t new_x = get_frog_x(frog) + 1;
            if (new_x <= MAX_COORD) {  // Verificar que no exceda el límite
                set_frog_x(frog, new_x);
            }
            last_x_dir = 1;
        }
    } else if (joy_state.x < -THRESHOLD) {
        if (last_x_dir != 2) {
            uint8_t new_x = get_frog_x(frog) - 1;
            if (new_x <= MAX_COORD) {  // Verificar que no sea menor que 0 (underflow)
                set_frog_x(frog, new_x);
            }
            last_x_dir = 2;
        }
    } else if (abs(joy_state.x) < THRESHOLD_OFF) {
        last_x_dir = 0;  // Resetear la dirección cuando el joystick vuelve al centro
    }

    // Detectar movimiento en el eje Y
    if (joy_state.y > THRESHOLD) {
        if (last_y_dir != 1) {
            uint8_t new_y = get_frog_y(frog) + 1;
            if (new_y <= MAX_COORD) {  // Verificar que no exceda el límite
                set_frog_y(frog, new_y);
            }
            last_y_dir = 1;
        }
    } else if (joy_state.y < -THRESHOLD) {
        if (last_y_dir != 2) {
            uint8_t new_y = get_frog_y(frog) - 1;
            if (new_y <= MAX_COORD) {  // Verificar que no sea menor que 0 (underflow)
                set_frog_y(frog, new_y);
            }
            last_y_dir = 2;
        }
    } else if (abs(joy_state.y) < THRESHOLD_OFF) {
        last_y_dir = 0;  // Resetear la dirección cuando el joystick vuelve al centro
    }
}