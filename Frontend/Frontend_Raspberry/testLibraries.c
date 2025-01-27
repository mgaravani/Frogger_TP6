/*
testlibraries es un ejemplo de uso de las librerías disdrv y joydrv
Permite mover con el joystick un LED encendido en la matriz de LEDs.
*/
//Como compilar: gcc testLibraries.c disdrv.o joydrv.o -Wall -o testLibs
#include <stdio.h>
#include "disdrv.h"
#include "joydrv.h"

#define THRESHOLD 40	//Límite a partir del cual se mueve el LED encendido

int main(void)
{
	
	joy_init();										//inicializa el joystick
	disp_init();									//inicializa el display
	disp_clear();									//limpia todo el display
	dcoord_t pos = {DISP_MAX_X>>1 , DISP_MAX_Y>>1};	//pos es la posición actual, empieza en el centro de la matriz
	dcoord_t npos = pos;							//npos es la próxima posición
	joyinfo_t coord = {0,0,J_NOPRESS};							//coordenadas medidas del joystick
	do
	{
		printf("Joystick: (%4d,%4d)" , coord.x, coord.y);	//Imprime las coordenadas del joystick
		printf(" | ");
		printf("Display: (%2d,%2d)\n" , npos.x, npos.y);	//Imprime la posición del LED encendio
		
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
}
