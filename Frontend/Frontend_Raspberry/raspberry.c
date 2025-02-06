#include "raspberry.h"




int main() {
    uint8_t choice = 0;
    uint8_t running = 1; // Variable de control para mantener el programa en ejecución
    disp_init();									//inicializa el display
	disp_clear();                                   //limpia todo el display
    ShowFrogger();
    initialize_matrix();
    frog_t frog_position;
    init_frog(&frog_position, 7, 11.96, 0, 1, 3, 0, 0, 0, 0, 0, 1); // Inicializo la rana
    joy_init();
    while (running) { // Mientras `running` sea 1, el menú se mostrará
      
        
        switch (choice) {
            case 0:
                choice = ShowMenu(); // Mostrar el menú
                break;
            case 1:
                disp_clear(); 	
                choice = playGame(choice , &frog_position); // Lógica del juego
                printf("Choice: %d \n", choice);
                break;
            case 2:
                printf("Saliendo del juego. ¡Hasta pronto!\n");
                running = 0; // Cambiar el valor de `running` para salir del bucle
                disp_clear();
                disp_update();
                break;
            case 3:
                    choice = ShowCONT();
                    printf("Choice: %d \n", choice);
                break;
            case 4:
                choice = 0;
                ShowGameOver();  
                printf("Choice: %d \n", choice);
            break;
            default:
                printf(".\n");
                break;
       }
    }
    return 0;
}

// Función principal del juego





