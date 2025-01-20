/*------------INCLUDES-----------*/
#include "../Frontend/Frontend_Allegro/allegro.h"
#include "../Backend/highscores.h"


/*-----Function highscores-----*/
// Función para manejar los puntajes altos
FILE* highscores(uint32_t newscore, char *name)
{
    FILE *pointer_highscores; // Puntero al archivo de puntajes altos

    pointer_highscores = fopen("highscores.txt", "r"); // Abrir el archivo en modo lectura y escritura

    if(pointer_highscores == NULL) // Si no se pudo abrir el archivo
    {
        printf("Error al abrir el archivo\n");
        exit(1);
    }

    //ACA DEBERIA HACER EL ANALISIS DE MI NUEVO PUNTAJE Y COMPARARLO Y SOBREESCRIBIR DE SER NECESARIO

    return pointer_highscores;
}