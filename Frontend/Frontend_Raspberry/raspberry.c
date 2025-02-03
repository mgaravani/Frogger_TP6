#include "raspberry.h"




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
                disp_clear();
                disp_update();
                break;
            case 3:
                    choice = ShowCONT();
                
                break;
            default:
                printf(".\n");
        }
       }
    }
    return 0;
}

// Función principal del juego





