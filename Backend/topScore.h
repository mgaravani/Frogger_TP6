#ifndef TOP_SCORE
#define TOP_SCORE
#include <stdint.h>

#define MAX_PLAYERS 10 // Máximo de jugadores que puede haber en el archivo

typedef struct {
    char name[50];
    uint32_t score;
} player;

void loadScores(const char *filename, player players[]);
void saveScores(const char *filename, player players[]);
void newScore(player players[], player newPlayer);
void swap(player *a, player *b);

#endif