# Regla principal para compilar el ejecutable final 'main' a partir de los archivos objeto 'allegro.o' y 'main.o'
main: Frontend/allegro.o Backend/main.o 
	# Enlaza los archivos objeto y genera el ejecutable 'main', enlazando las bibliotecas necesarias
	gcc Frontend/allegro.o Backend/main.o -g -o main -Wall -lallegro -lallegro_image -lallegro_primitives -lallegro_font -lallegro_ttf -lpthread

# Regla para compilar 'allegro.c' en el archivo objeto 'allegro.o'
Frontend/allegro.o: Frontend/allegro.c Frontend/allegro.h
	# Compila 'allegro.c' con advertencias habilitadas
	gcc -c Frontend_Allegro/allegro.c -Wall -o Frontend_Allegro/allegro.o

# Regla para compilar 'main.c' en el archivo objeto 'main.o'
Backend/main.o: Backend/main.c
	# Compila 'main.c' con advertencias habilitadas
	gcc Backend/main.c -c -Wall -o Backend/main.o

# Regla de limpieza para eliminar los archivos objeto y el ejecutable
clean:
	# Elimina los archivos objeto y el ejecutable
	rm -f Backend/*.o main
