#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "topScore.h"

void loadScores(const char *filename, player_t players[]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) 
    {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (fscanf(file, "%49s %u", players[i].name, &players[i].score) == 2) 
    {
        i++;
        if (i >= MAX_PLAYERS) 
        {
            fprintf(stderr, "Se alcanzó el límite de jugadores permitidos (%d).\n", MAX_PLAYERS);
            break;
        }
    }

    fclose(file);
}

void saveScores(const char *filename, player_t players[]) {
    FILE *file = fopen(filename, "w"); // Abrimos el archivo en modo escritura
    if (file == NULL)
    {
        perror("Error al abrir el archivo para guardar los puntajes");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MAX_PLAYERS; i++) 
    {
        fprintf(file, "%s %u\n", players[i].name, players[i].score); // Escribimos cada jugador en el archivo
    }

    fclose(file);
    printf("Puntajes guardados exitosamente en '%s'.\n", filename);
}

void newScore(player_t players[], player_t newPlayer) {
    // Solo reemplazamos el último jugador si el nuevo puntaje es mayor
    if (newPlayer.score > players[MAX_PLAYERS - 1].score) {
        players[MAX_PLAYERS - 1] = newPlayer;
    }

    // Ordenar el arreglo por puntaje en orden descendente (Mayor puntaje primero)
    for (int i = 0; i < MAX_PLAYERS - 1; i++) {
        for (int j = 0; j < MAX_PLAYERS - i - 1; j++) {
            if (players[j].score < players[j + 1].score) {
                swap(&players[j], &players[j + 1]);
            }
        }
    }
}

/*----- Intercambia a por b ------*/
void swap(player_t *a, player_t *b) {
    player_t aux;
    aux = *a;
    *a = *b;
    *b = aux;
}


