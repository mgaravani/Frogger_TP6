#include <time.h>

#define NIVELES 5
#define FILA 14

int tiempoespera(int nivel, int fila) {
    static clock_t flags[FILA] = {0};  // Inicializa el arreglo a 0
    double tiempo_transcurrido;
    double vel = 1.0;

    // Configuración de velocidad basada en la fila
    if (fila >= 1 && fila <= 5) {
        vel = 1.0;
    } else if (fila >= 6 && fila <= 14) {
        vel = 1.25;
    } else {
        vel = 1.0;  // Valor predeterminado si la fila no está en los rangos definidos
    }

    // Inicializa el temporizador para la fila específica si es la primera vez
    if (flags[fila] == 0) {
        flags[fila] = clock();
    }

    tiempo_transcurrido = ((double)(clock() - flags[fila])) / CLOCKS_PER_SEC;

    // Verifica si ha pasado el tiempo necesario
    if (tiempo_transcurrido >= 1.0 / (nivel * vel)) {
        flags[fila] = clock();  // Reinicia el temporizador
        return 1;  // Ha pasado el tiempo, devuelve 1
    }

    return 0;  // No ha pasado el tiempo, devuelve 0
}