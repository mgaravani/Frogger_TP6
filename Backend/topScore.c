#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "topScore.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "topScore.h"


void loadScores(const char *filename, player players[]) {
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

void saveScores(const char *filename, player players[]) {
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

void newScore(player players[], player newPlayer) {
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
void swap(player *a, player *b) {
    player aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

/*
int main() {
    player players[MAX_PLAYERS];

    // Cargar puntajes desde el archivo
    loadScores("highscores.txt", players);

    // Mostrar puntajes antes de agregar el nuevo
    printf("Top actual:\n");
    for (int i = 0; i < MAX_PLAYERS; i++) {
        printf("Jugador: %s, Puntaje: %d\n", players[i].name, players[i].score);
    }

    // Crear un nuevo jugador
    player newPlayer = {"PRUEBA3", 1985};

    // Agregar el nuevo jugador y reordenar el arreglo
    newScore(players, newPlayer);

    // Mostrar los puntajes después de agregar el nuevo jugador
    printf("\nTop actualizado:\n");
    for (int i = 0; i < MAX_PLAYERS; i++) {
        printf("Jugador: %s, Puntaje: %d\n", players[i].name, players[i].score);
    }

    // Guardar los puntajes actualizados
    saveScores("highscores.txt", players);

    return 0;
}
*/

