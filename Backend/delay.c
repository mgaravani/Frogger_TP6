/*------------INCLUDES-----------*/
#include "delay.h"

/*------------ FUNCTIONS ----------------*/

/*------Function waiting_time------*/
// Funcion para controlar el tiempo entre los desplazamientos de los objetos
uint8_t waiting_time(uint8_t level, uint8_t row) 
{
    static clock_t flags[ROWS] = {0};  // Inicializa el arreglo a 0
    double elapsed_time = 0, time_reference = 0, speed = 0; 

    // Configuración de velocidad de desplazamiento según la fila
    if (row == 1)
    {
        speed = 1.5 + (level * 0.3); // Incremento de velocidad según el nivel
    } 
    else if (row == 2 || row == 4) // Con estos if podemos personalizar mas las velocidades de las filas
    {
        speed = 1 + (level * 0.1); 
    } 
    else if(row == 3)
    {
        speed = 2 + (level * 0.3);
    }

    else if (row == 5) 
    {
        speed = 1 + (level * 0.2);  
    } 
    else if (row == 7) 
    {
        speed = 2 + (level * 0.5);  
    }
    else if (row == 8) 
    {
        speed = 2 + (level * 0.2); 
    } 
    else if (row == 9 || row == 11)
    {
        speed = 2 + (level * 0.5);  
    }
    else if (row == 10)
    {
        speed = 2 + (level * 0.2);
    }

    else 
    {
        speed = 2 + (level * 0.2);  // Incremento estándar para las demás filas
    }

    // Inicializa el temporizador para la fila específica si es la primera vez que se llama la función
    if (flags[row] == 0) 
    {
        flags[row] = clock();
    }

    // Guarda el tiempo transcurrido desde que se reinició
    elapsed_time = ((double)(clock() - flags[row])) / CLOCKS_PER_SEC;
    // Relación de tiempo para comparar con el transcurrido en función del nivel y la velocidad
    time_reference = 0.8 / speed;

    // Verifica si ha pasado el tiempo necesario
    if (elapsed_time >= time_reference) 
    {
        flags[row] = clock();  // Reinicia el temporizador
        return 1;  // Ha pasado el tiempo, devuelve 1
    }
    return 0;  // No ha pasado el tiempo, devuelve 0
}
