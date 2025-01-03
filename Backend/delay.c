#include "delay.h"
#include "mapa.h" // Incluyo mapa.h para saber la cantidad de filas utilizadas

int8_t waiting_time (int8_t nivel, int8_t fila) {
    static clock_t flags[FILAS] = {0};  // Inicializa el arreglo a 0
    double elapsed_time = 0, time_reference = 0, speed = 1.0; 

    // Configuración de velocidad de desplazamiento segun la fila
    if (fila >= 1 && fila <= 5) 
    {
        speed = 1.0;
    } 
    else
    {
        speed = 1.25;
    } 

    // Inicializa el temporizador para la fila específica si es la primera vez que se llama la función
    if (flags[fila] == 0) {
        flags[fila] = clock();
    }

    // Guarda el tiempo transcurrido desde que se reinicio
    elapsed_time = ((double)(clock() - flags[fila])) / CLOCKS_PER_SEC;
    // Relacion de tiempo para comparar con el transcurrido en funcion del nivel y la velocidad
    time_reference = 0.01 / (nivel * speed);


    // Verifica si ha pasado el tiempo necesario
    if (elapsed_time >= time_reference) {
        flags[fila] = clock();  // Reinicia el temporizador
        return 1;  // Ha pasado el tiempo, devuelve 1
    }
    return 0;  // No ha pasado el tiempo, devuelve 0
}