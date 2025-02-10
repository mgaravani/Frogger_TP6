#ifndef TOP_SCORE
#define TOP_SCORE

/*------------INCLUDES-----------*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*-----DEFINES-----*/
#define MAX_PLAYERS 10 // Máximo de jugadores que puede haber en el archivo

/*-----STRUCTS-----*/
// Se cuardan los datos del jugador
typedef struct {
    char name[50]; // Nombre del jugador
    uint32_t score; // Puntaje del jugador
} player_t;

/*-----------PROTOTYPES--------*/

/*-----Function loadScores-----*/
// Se encarga de abrir, leer y guardar en el arreglo players el top que está guardado en el archivo highscores.txt
void loadScores(const char *filename, player_t players[]);

/*-----Function saveScores-----*/
// Se encarga de guardar en el archivo highscores.txt el nuevo top (o dejarlo igual) al terminar la partida
void saveScores(const char *filename, player_t players[]);

/*-----Function newScore-----*/
// Re-ordena el nuevo top en base a la puntuación de la partida mas reciente.
void newScore(player_t players[], player_t newPlayer);

/*-----Function swap-----*/
// Usada en newScore para intercambiar posiciones
void swap(player_t *a, player_t *b);

#endif // TOP_SCORE