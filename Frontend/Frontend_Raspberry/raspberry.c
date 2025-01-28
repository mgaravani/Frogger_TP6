#include "raspberry.h"

void ShowFrogger(void); // Declaración de ShowFrogger
int8_t ShowMenu(void); // Declaración de ShowMenu

int main() {
    int choice = 0;
    int running = 1; // Variable de control para mantener el programa en ejecución
    ShowFrogger();
    while (running) { // Mientras `running` sea 1, el menú se mostrará
       while (choice == 0)
       {
         choice = ShowMenu(); // Mostrar el menú
        
        switch (choice) {
            case 1:	
                choice = playGame(choice); // Lógica del juego
                break;
            case 2:
                printf("Saliendo del juego. ¡Hasta pronto!\n");
                running = 0; // Cambiar el valor de `running` para salir del bucle
                break;
            default:
                printf(".\n");
        }
       }
    }
    return 0;
}

void ShowFrogger(void) {
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
    uint8_t mat0[16][16]= {0};
    mostrar_matriz(mat0);
    return status; // Asegúrate de retornar un valor
}


int playGame(int choice) {
    printf("\n[Iniciando el juego...]\n");
    joy_init();										//inicializa el joystick
	disp_init();									//inicializa el display
	disp_clear();									//limpia todo el display
	dcoord_t pos = {DISP_MAX_X>>1 , DISP_MAX_Y>>1};	//pos es la posición actual, empieza en el centro de la matriz
	dcoord_t npos = pos;							//npos es la próxima posición
	joyinfo_t coord = {0,0,J_NOPRESS};							//coordenadas medidas del joystick
	do
	{
		disp_update();	//Actualiza el display con el contenido del buffer
		coord = joy_read();	//Guarda las coordenadas medidas
		
		//Establece la próxima posición según las coordenadas medidas
		if(coord.x > THRESHOLD && npos.x < DISP_MAX_X)
		{
			npos.x++;
		}
		if(coord.x < -THRESHOLD && npos.x > DISP_MIN)
		{
			npos.x--;
		}
		if(coord.y > THRESHOLD && npos.y > DISP_MIN)
		{
			npos.y--;
		}
		if(coord.y < -THRESHOLD && npos.y < DISP_MAX_Y)
		{
			npos.y++;
		}
		
		disp_write(pos,D_OFF);	//apaga la posición vieja en el buffer
		disp_write(npos,D_ON);	//enciende la posición nueva en el buffer
		pos = npos;				//actualiza la posición actual
		
	} while( coord.sw == J_NOPRESS );	//termina si se presiona el switch
	//Borro el display al salir
	disp_clear();
    disp_update();
    return choice = 0;
}
void shiftDisplay(uint8_t display[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS], uint8_t bitmap[DISP_CANT_Y_DOTS][46], int offset) {
    // Copiar una ventana de 16x16 del bitmap al display
    for (int y = 0; y < DISP_CANT_Y_DOTS; y++) {
        for (int x = 0; x < DISP_CANT_X_DOTS; x++) {
            display[y][x] = bitmap[y][x + offset];
        }
    }
}
