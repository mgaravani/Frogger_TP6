#include "../Frontend/Frontend_Allegro/allegro.h"
#include "../Backend/highscores.h"

FILE* highscores(uint32_t newscore, char *name)
{
    FILE *pointer_highscores;

    pointer_highscores = fopen("highscores.txt", "r+");

    if(pointer_highscores == NULL)
    {
        printf("Error al abrir el archivo\n");
        exit(1);
    }

    char line[256]; // Buffer para almacenar cada línea
    while (fgets(line, sizeof(line), pointer_highscores)) {
        printf("%s", line); // Imprimir la línea leída
    }

    putchar('\n');

    return pointer_highscores;
}