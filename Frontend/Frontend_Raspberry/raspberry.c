#include "functions.h"
#include "arrays.h"
#include <pthread.h>
#include <stdio.h>

void *frogger_func(void *arg);  // Declaración de la función
void *map_func(void *arg);      // Declaración de la función 
int main()
{
     
    pthread_t frogger, map;

    // Crear los hilos
    pthread_create(&frogger, NULL, frogger_func, NULL);
    pthread_create(&map, NULL, map_func, NULL);

    pthread_join(frogger, NULL);
    pthread_join(map, NULL);

   

    return 0;
}

void *frogger_func(void *arg) {
    joy_init(); // inicia la lectura del joystick
    disp_init(); // inicia el display    
    disp_clear(); // borra el display   
    printf("frogger\n");
    dcoord_t pos = {DISP_MAX_X >> 1 , DISP_MAX_Y >> 1};  //pos es la posición actual, empieza en el centro de la matriz
    dcoord_t npos = pos;                            //npos es la próxima posición
    joyinfo_t coord = {0, 0, J_NOPRESS};            //coordenadas medidas del joystick
    do
    {
        printf("Joystick: (%4d,%4d)", coord.x, coord.y);  //Imprime las coordenadas del joystick
        printf(" | ");
        printf("Display: (%2d,%2d)\n", npos.x, npos.y);  //Imprime la posición del LED encendido

        disp_update();  //Actualiza el display con el contenido del buffer
        coord = joy_read();  //Guarda las coordenadas medidas
        
        //Establece la próxima posición según las coordenadas medidas
        if (coord.x > THRESHOLD && npos.x < DISP_MAX_X) {
            npos.x++;
        }
        if (coord.x < -THRESHOLD && npos.x > DISP_MIN) {
            npos.x--;
        }
        if (coord.y > THRESHOLD && npos.y > DISP_MIN) {
            npos.y--;
        }
        if (coord.y < -THRESHOLD && npos.y < DISP_MAX_Y) {
            npos.y++;
        }
        
        disp_write(pos, D_OFF);  //apaga la posición vieja en el buffer
        disp_write(npos, D_ON);  //enciende la posición nueva en el buffer
        pos = npos;  //actualiza la posición actual
        
    } while (coord.sw == J_NOPRESS);  //termina si se presiona el switch

    //Borro el display al salir
    disp_clear();
    disp_update();
    return NULL;
}

void *map_func(void *arg) {
    // Uso correcto de la matriz
    uint8_t matriz[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS];

    generar_matriz(matriz);  // Pasar la matriz completa
    mostrar_matriz(matriz);  // Pasar la matriz completa
    return NULL;
}
