#include "raspberry.h"
//void *frogger_func(void *arg);  // Declaración de la función
//void *map_func(void *arg);      // Declaración de la función 

int main()
{
    
    joy_init();
    disp_init();
    joyinfo_t info;
    //extern map_t map;
    //pthread_t frogger, map1;
 
  joyinfo_t coord = {0, 0, J_NOPRESS};            //coordenadas medidas del joystick
    do
    {
        info = joy_read();	
    mostrar_matriz(Menu_Display);
    } while (coord.sw == J_NOPRESS);  //termina si se presiona el switch

    //Borro el display al salir
    disp_clear();
    disp_update();
   

    return 0;
}
/*void raspberry_menu(){
        
    }*/
/*void *frogger_func(void *arg) {
    
    disp_clear(); // borra el display   
    printf("frogger\n");
    dcoord_t pos = {DISP_MAX_X >> 1 , DISP_MAX_Y >> 1};  //pos es la posición actual, empieza en el centro de la matriz
    dcoord_t npos = pos;                            //npos es la próxima posición
    joyinfo_t coord = {0, 0, J_NOPRESS};            //coordenadas medidas del joystick
    do
    {
       //rana
    } while (coord.sw == J_NOPRESS);  //termina si se presiona el switch

    //Borro el display al salir
    disp_clear();
    disp_update();
    return NULL;
}

void *map_func(void *arg) {
    int nueva[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS];
    // Uso correcto de la matriz
    initialize_matrix();
    cortar_y_copiar_matriz(map,nueva);
    mostrar_matriz(nueva);  // Pasar la matriz completa
    return NULL;
}*/
