    #include "frog_raspy.h"
    
    void move_frog_by_joystick(frog_t *frog) {
    static int8_t prev_x = 0, prev_y = 0;
    
    joyinfo_t joy;
    static int old_x, old_y;
    int8_t New_x, New_y;

    joy =joy_read();
    if (prev_x == 0) {
        if (joy.x > THRESHOLD) {
            if (frog->x < DISP_CANT_X_DOTS) { // Verificar límite derecho
                old_x = frog->x;
                old_y = frog->y;
                handle_move_right(frog);
                New_x = frog->x;
                New_y = frog->y;
                
                // Actualizar matriz global map
                map[old_y][old_x] = 0; // Borrar la posición anterior
                map[New_y][New_x] = 2; // Poner 2 en la nueva posición
                
                // Actualizar display: apagar la posición anterior y encender la nueva
            }
            prev_x = joy.x;
        } else if (joy.x < -THRESHOLD) {
            if (frog->x > 0) { // Verificar límite izquierdo
                old_x = frog->x;
                old_y = frog->y;
                handle_move_left(frog);
                New_x = frog->x;
                New_y = frog->y;
                
                // Actualizar matriz global map
                map[old_y][old_x] = 0; // Borrar la posición anterior
                map[New_y][New_x] = 2; // Poner 2 en la nueva posición
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
                
                // Actualizar matriz global map
                map[old_y][old_x] = 0; // Borrar la posición anterior
                map[New_y][New_x] = 2; // Poner 2 en la nueva posición
            }
            prev_y = joy.y;
        } else if (joy.y < -THRESHOLD) {
            if (frog->y < DISP_CANT_Y_DOTS) { // Verificar límite inferior
                old_x = frog->x;
                old_y = frog->y;
                handle_move_down(frog);
                New_x = frog->x;
                New_y = frog->y;
                
                // Actualizar matriz global map
                map[old_y][old_x] = 0; // Borrar la posición anterior
                map[New_y][New_x] = 2; // Poner 2 en la nueva posición
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
        printf("Joystick: (%4d,%4d)" , joy.x, joy.y);	//Imprime las coordenadas del joystick
		printf(" | ");

    
}