# Regla principal para compilar el ejecutable final 'main' a partir de los archivos objeto 'allegro.o' y 'main.o'
main: Frontend_Allegro/allegro.o Backend/logica.o Backend/main.o Backend/delay.o Frontend_Allegro/eventos.o 
	# Enlaza los archivos objeto y genera el ejecutable 'main', enlazando las bibliotecas necesarias
	gcc Frontend_Allegro/allegro.o Frontend_Allegro/eventos.o Backend/main.o Backend/delay.o Backend/logica.o -g -o main -Wall -lallegro -lallegro_image -lallegro_primitives -lallegro_font -lallegro_ttf -lpthread

# Regla para compilar 'allegro.c' en el archivo objeto 'allegro.o'
Frontend_Allegro/allegro.o: Frontend_Allegro/allegro.c Frontend_Allegro/allegro.h Frontend_Allegro/eventos.c
	# Compila 'allegro.c' con advertencias habilitadas
	gcc -c Frontend_Allegro/allegro.c -Wall -o Frontend_Allegro/allegro.o

# Regla para compilar 'eventos.c' en el archivo objeto 'eventos.o'
Frontend_Allegro/eventos.o: Frontend_Allegro/eventos.c
	# Compila 'eventos.c' con advertencias habilitadas
	gcc -c Frontend_Allegro/eventos.c -Wall -o Frontend_Allegro/eventos.o


# Regla para compilar 'main.c' en el archivo objeto 'main.o'
Backend/main.o: Backend/main.c
	# Compila 'main.c' con advertencias habilitadas
	gcc Backend/main.c -c -Wall -o Backend/main.o

Backend/logica.o: Backend/logica.c Backend/logica.h
	# Compila 'logica.c' con advertencias habilitadas
	gcc Backend/logica.c -c -Wall -o Backend/logica.o


Backend/delay.o: Backend/delay.c Backend/delay.h
	# Compila 'logica.c' con advertencias habilitadas
	gcc Backend/delay.c -c -Wall -o Backend/delay.o
	

# Regla de limpieza para eliminar los archivos objeto y el ejecutable
clean:
	# Elimina los archivos objeto y el ejecutable
	rm -f Backend/*.o main
