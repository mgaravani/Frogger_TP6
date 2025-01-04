/*------------INCLUDES-----------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"

frog_t frog;


//TESTEO DE LA POSICION DE LA RANA
void frog_position(void)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            if (i == 12 && j == 7)
            {
                frog[i][j] = 1;
            }
            else
            {
                frog[i][j] = 0;
            }
        }
    }
}