#ifndef TOP_SCORE
#define TOP_SCORE
#include <stdint.h>

/*-----DEFINES-----*/
#define MAX_PLAYERS 10 // Máximo de jugadores que puede haber en el archivo

/*-----STRUCTS-----*/
// Se cuardan los datos del jugador
typedef struct {
    char name[50]; // Nombre del jugador
    uint32_t score; // Puntaje del jugador
} player_t;

/*-----Función loadScores-----*/
// Se encarga de abrir, leer y guardar en el arreglo players el top que está guardado en el archivo highscores.txt
void loadScores(const char *filename, player_t players[]);

/*-----Función saveScores-----*/
// Se encarga de guardar en el archivo highscores.txt el nuevo top (o dejarlo igual) al terminar la partida
void saveScores(const char *filename, player_t players[]);

/*-----Función newScore-----*/
// Re-ordena el nuevo top en base a la puntuación de la partida mas reciente.
void newScore(player_t players[], player_t newPlayer);

/*-----Función swap-----*/
// Usada en newScore para intercambiar posiciones
void swap(player_t *a, player_t *b);

#endif