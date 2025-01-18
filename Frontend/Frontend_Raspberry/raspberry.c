#include "functions.h"
#include "arrays.h"
#include <pthread.h>
#include <stdio.h>

int main()
{
     joy_init();// inicia la lectura del joystick
    disp_init();// inicia el display    
    disp_clear();// borra el display
    pthread_t frogger, map;

    // Crear los hilos
    pthread_create(&hilo1, NULL, hilo1_func, NULL);
    pthread_create(&hilo2, NULL, hilo2_func, NULL);


    disp_clear();
    disp_update();

    return 0;
}