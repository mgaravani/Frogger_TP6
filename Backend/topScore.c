#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "topScore.h"

void loadScores(const char *filename, player_t players[]) {
    FILE *file = fopen(filename, "r"); // Abrimos el archivo en modo lectura
    if (file == NULL) 
    {
        perror("Error al abrir el archivo"); // Mensaje de error si el archivo no se puede abrir
        exit(EXIT_FAILURE);
    }

    int i = 0;
    // Leemos los nombres y puntajes del archivo hasta llenar el arreglo
    while (fscanf(file, "%49s %u", players[i].name, &players[i].score) == 2) 
    {
        i++;
        // Si llegamos al límite de jugadores, mostramos un mensaje y terminamos la lectura
        if (i >= MAX_PLAYERS) 
        {
            fprintf(stderr, "Se alcanzó el límite de jugadores permitidos (%d).\n", MAX_PLAYERS);
            break;
        }
    }

    fclose(file); // Cerramos el archivo después de la lectura
}

void saveScores(const char *filename, player_t players[]) {
    FILE *file = fopen(filename, "w"); // Abrimos el archivo en modo escritura
    if (file == NULL)
    {
        perror("Error al abrir el archivo para guardar los puntajes"); // Mensaje de error si no se puede abrir
        exit(EXIT_FAILURE);
    }

    // Escribimos en el archivo cada jugador con su puntaje
    for (int i = 0; i < MAX_PLAYERS; i++) 
    {
        fprintf(file, "%s %u\n", players[i].name, players[i].score);
    }

    fclose(file); // Cerramos el archivo después de guardar
    printf("Puntajes guardados exitosamente en '%s'.\n", filename);
}

void newScore(player_t players[], player_t newPlayer) {
    // Solo reemplazamos el último jugador si el nuevo puntaje es mayor
    if (newPlayer.score > players[MAX_PLAYERS - 1].score) {
        players[MAX_PLAYERS - 1] = newPlayer;
    }

    // Ordenamos la lista de jugadores por puntaje en orden descendente (mayor puntaje primero)
    for (int i = 0; i < MAX_PLAYERS - 1; i++) {
        for (int j = 0; j < MAX_PLAYERS - i - 1; j++) {
            if (players[j].score < players[j + 1].score) {
                swap(&players[j], &players[j + 1]); // Intercambiamos los jugadores si es necesario
            }
        }
    }
}

// Función auxiliar para intercambiar dos jugadores en el arreglo
void swap(player_t *a, player_t *b) {
    player_t aux;
    aux = *a;
    *a = *b;
    *b = aux;
}
