/* INCLUDES */
//#include <unistd.h> // Para la función sleep
//#include "logica.h"


/* FUNCION MAIN */
int main(void) {
    AllegroResources init;
    init = iniciar_logica();
    while (1) {
    prueba_impresion(init);
  // actualizar_pantalla();
  //  if (tiempoespera(12, 2)) {
  //    shift_row(2, 0);
  //  }
  //   if (tiempoespera(11, 3)) {
  //     shift_row(3, 1);
  //   }
  //   if (tiempoespera(11, 4)) {
  //     shift_row(4, 0);
  //   }
  //   if (tiempoespera(9, 5)) {
  //     shift_row(5, 1);
  //   }
  //   if (tiempoespera(9, 6)) {
  //     shift_row(6, 0);
  //   }

  //   if (tiempoespera(6, 8)) {
  //     shift_row(8, 1);
  //   }
  //   if (tiempoespera(4, 9)) {
  //     shift_row(9, 0);
  //   }
  //   if (tiempoespera(8, 10)) {
  //     shift_row(10, 1);
  //   }
  //   if (tiempoespera(2, 11)) {
  //     shift_row(11, 1);
  //   }
  //   if (tiempoespera(4, 12)) {
  //     shift_row(12, 1);
  //   }
    }
    return 0;
}