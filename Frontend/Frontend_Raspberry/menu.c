#include "menu.h"
int8_t ShowMenu(void) {
    int8_t  status = 0;
    uint8_t menuBitmap[16][16] = {
        // "PLAY" (Arriba)
        {0,0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, },
        {0,1, 1, 1, 0, 1,  0, 0, 1, 1, 1, 0, 0, 1,  0, 1, },
        {0,1, 0, 1, 0, 1,  0, 0, 1, 0, 1, 0, 0, 1,  0, 1, },
        {0,1, 1, 1, 0, 1,  0, 0, 1, 1, 1, 0, 0, 0,  1, 0, },
        {0,1, 0, 0, 0, 1,  0, 0, 1, 0, 1, 0, 0, 1,  0, 0, },
        {0,1, 0, 0, 0, 1,  1, 0, 1, 0, 1, 0, 1, 0,  0, 0, },
        {0,0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, },
        {0,0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, },

        // "EXIT" (Abajo)
        {0, 0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0},
        {0, 1, 1, 1, 0,  1, 0, 1, 0,  1, 1, 1, 0,  1, 1, 1},
        {0, 1, 0, 0, 0,  1, 0, 1, 0,  0, 1, 0, 0,  0, 1, 0},
        {0, 1, 1, 1, 0,  0, 1, 0, 0,  0, 1, 0, 0,  0, 1, 0},
        {0, 1, 0, 0, 0,  1, 0, 1, 0,  0, 1, 0, 0,  0, 1, 0},
        {0, 1, 1, 1, 0,  1, 0, 1, 0,  1, 1, 1, 0,  0, 1, 0},
        {0, 0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0},
        {0, 0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0}
    };
    mostrar_matriz(menuBitmap);
    joy_init();	
    joyinfo_t coord = {0,0,J_NOPRESS};
    do {
        coord = joy_read();
        if (coord.y > THRESHOLD) {//estado de arriba
            status = 1;
        }
        if (coord.y < -THRESHOLD) {//estado de abajo
            status = 2;
        }       
    }while (coord.sw == J_NOPRESS  );//termina si se presiona el switch
    disp_clear();
    return status; //retorna el estado
}

void ShowFrogger(void){
    uint8_t display[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS] = {0}; // Matriz del display 16x16


    uint8_t froggerBitmap[DISP_CANT_Y_DOTS][46] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    
};

    for (int offset = 0; offset <= 46 - DISP_CANT_X_DOTS; offset++) {
        shiftDisplay(display, froggerBitmap, offset); // Desplazar la vista del display
        mostrar_matriz(display);                       // Imprimir el display actual
        usleep(200000);                              // Pausa de 200 ms
    }
    sleep(.5);//pausa de 0.5 segundos 
}
/*void Pause(void){//aun no se usa es pasa simular la pausa
    uint8_t pauseBitmap[16][16] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0},
        {0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0},
        {0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0},
        {0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0},
        {0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0},
        {0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0},
        {0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0},
        {0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0}
    };
}*/
void shiftDisplay(uint8_t display[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS], uint8_t bitmap[DISP_CANT_Y_DOTS][46], int offset) {
    // Copiar una ventana de 16x16 del bitmap al display
    for (int y = 0; y < DISP_CANT_Y_DOTS; y++) {
        for (int x = 0; x < DISP_CANT_X_DOTS; x++) {
            display[y][x] = bitmap[y][x + offset];
        }
    }
}
int8_t ShowCONT(void) {
    int8_t  status = 0;
    uint8_t menuBitmap[16][16] = {
        // "CONT" (Arriba)
        {0,0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, },
        {0,1, 1, 1, 0, 1,  1, 1, 0, 1, 0, 0, 1, 1,  1, 1, },
        {0,1, 0, 1, 0, 1,  0, 1, 0, 1, 0, 0, 1, 0,  1, 0, },
        {0,1, 0, 0, 0, 1,  0, 1, 0, 1, 1, 0, 1, 0,  1, 0, },
        {0,1, 0, 0, 0, 1,  0, 1, 0, 1, 1, 0, 1, 0,  1, 0, },
        {0,1, 0, 1, 0, 1,  0, 1, 0, 1, 0, 1, 1, 0,  1, 0, },
        {0,1, 1, 1, 0, 1,  1, 1, 0, 1, 0, 0, 1, 0,  1, 0, },
        {0,0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, },

        // "EXIT" (Abajo)
        {0, 0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0},
        {0, 1, 1, 1, 0,  1, 0, 1, 0,  1, 1, 1, 0,  1, 1, 1},
        {0, 1, 0, 0, 0,  1, 0, 1, 0,  0, 1, 0, 0,  0, 1, 0},
        {0, 1, 1, 1, 0,  0, 1, 0, 0,  0, 1, 0, 0,  0, 1, 0},
        {0, 1, 0, 0, 0,  1, 0, 1, 0,  0, 1, 0, 0,  0, 1, 0},
        {0, 1, 1, 1, 0,  1, 0, 1, 0,  1, 1, 1, 0,  0, 1, 0},
        {0, 0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0},
        {0, 0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0}
    };
    mostrar_matriz(menuBitmap);
    joy_init();	
    joyinfo_t coord = {0,0,J_NOPRESS};
    do {
        coord = joy_read();
        if (coord.y > THRESHOLD) {//estado de arriba
            status = 1;
        }
        if (coord.y < -THRESHOLD) {//estado de abajo
            status = 2;
        }       
    }while (coord.sw == J_NOPRESS  );//termina si se presiona el switch
    disp_clear();
    return status; //retorna el estado
}