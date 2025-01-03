#include "funciones.h"
#include "matrices.h"

int main()
{
     joy_init();
    disp_init();
    disp_clear();
    joyinfo_t coord = {0, 0, J_NOPRESS};
    dcoord_t npos = {DISP_MAX_X / 2, DISP_MAX_Y / 2};


    do {
        // Simular lectura del joystick
        coord = joy_read(); // Función que lee la posición del joystick

        if (coord.x > THRESHOLD && npos.x < DISP_MAX_X - 2) {
            moveMatrix(Matriz, Sapo, ++npos.x, npos.y);
        }
        if (coord.x < -THRESHOLD && npos.x > DISP_MIN) {
            moveMatrix(Matriz, Sapo, --npos.x, npos.y);
        }
        if (coord.y > THRESHOLD && npos.y < DISP_MAX_Y - 2) {
            moveMatrix(Matriz, Sapo, npos.x, ++npos.y);
        }
        if (coord.y < -THRESHOLD && npos.y > DISP_MIN) {
            moveMatrix(Matriz, Sapo, npos.x, --npos.y);
        }

        mostrar_matriz(Matriz);

        // Actualizar la pantalla
        disp_update();

        // Simular una pausa para evitar la lectura excesiva

    } while (coord.sw == J_NOPRESS ); 
    // Limpiar y finalizar
    disp_clear();
    disp_update();

    return 0;
}