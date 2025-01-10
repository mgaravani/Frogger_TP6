/*------------INCLUDES-----------*/
#include "delay.h"
#include "map.h" // Incluyo map.h para saber la cantidad de filas utilizadas
#include <stdio.h>

/*------Function waiting_time------*/
// Funcion para controlar el tiempo entre los desplazamientos de los objetos
uint8_t waiting_time (uint8_t level, uint8_t row) 
{
    static clock_t flags[ROWS] = {0};  // Inicializa el arreglo a 0
    double elapsed_time = 0, time_reference = 0, speed = 0; 

    // Configuración de velocidad de desplazamiento segun la fila
    if (row >= 0 && row <= 5) 
    {
        speed = 1;
    } 
    else
    {
        speed = 2;
    } 

    // Inicializa el temporizador para la fila específica si es la primera vez que se llama la función
    if (flags[row] == 0) 
    {
        flags[row] = clock();
    }

    // Guarda el tiempo transcurrido desde que se reinicio
    elapsed_time = ((double)(clock() - flags[row])) / CLOCKS_PER_SEC;
    // Relacion de tiempo para comparar con el transcurrido en funcion del nivel y la velocidad
    time_reference = 0.00001 / (level * speed);


    // Verifica si ha pasado el tiempo necesario
    if (elapsed_time >= time_reference) 
    {
        flags[row] = clock();  // Reinicia el temporizador
        return 1;  // Ha pasado el tiempo, devuelve 1
    }
    return 0;  // No ha pasado el tiempo, devuelve 0
}