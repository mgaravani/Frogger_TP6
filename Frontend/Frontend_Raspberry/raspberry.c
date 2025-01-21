#include "raspberry.h"
void *frogger_func(void *arg);  // Declaración de la función
void *map_func(void *arg);      // Declaración de la función 
int main()
{
    extern map_t map;
    pthread_t frogger, map;

    // Crear los hilos
    pthread_create(&frogger, NULL, frogger_func, NULL);
    pthread_create(&map, NULL, map_func, NULL);

    pthread_join(frogger, NULL);
    pthread_join(map, NULL);

   

    return 0;
}

void *frogger_func(void *arg) {
    joy_init(); // inicia la lectura del joystick
    disp_init(); // inicia el display    
    disp_clear(); // borra el display   
    printf("frogger\n");
    dcoord_t pos = {DISP_MAX_X >> 1 , DISP_MAX_Y >> 1};  //pos es la posición actual, empieza en el centro de la matriz
    dcoord_t npos = pos;                            //npos es la próxima posición
    joyinfo_t coord = {0, 0, J_NOPRESS};            //coordenadas medidas del joystick
    /*do
    {
       //rana
    } while (coord.sw == J_NOPRESS);  //termina si se presiona el switch

    //Borro el display al salir
    disp_clear();
    disp_update();*/
    return NULL;
}

void *map_func(void *arg) {
    int nueva[DISP_CANT_Y_DOTS][DISP_CANT_X_DOTS];
    // Uso correcto de la matriz
    initialize_matrix();
    cortar_y_copiar_matriz(map,nueva);
    mostrar_matriz(nueva);  // Pasar la matriz completa
    return NULL;
}
