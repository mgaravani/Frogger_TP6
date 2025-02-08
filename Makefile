# Regla principal para compilar el ejecutable final 'main' a partir de los archivos objeto 'allegro.o' y 'main.o'
# Variables
CC = gcc
CFLAGS = -Wall -pthread
OBJ = Frontend/Frontend_Raspberry/joydrv.o Frontend/Frontend_Raspberry/disdrv.o   #Objetos necesarios de raspy
HDR = Frontend/Frontend_Raspberry/joydrv.h Frontend/Frontend_Raspberry/disdrv.h   #Librerias necesarias de raspy

main_PC: Frontend/Frontend_Allegro/allegro.o Backend/main.o Frontend/Frontend_Allegro/events.o Backend/logic.o Backend/map.o Backend/topScore.o Backend/delay.o Backend/frog.o Frontend/Frontend_Allegro/screen.o 
	# Enlaza los archivos objeto y genera el ejecutable 'main', enlazando las bibliotecas necesarias
	gcc Frontend/Frontend_Allegro/allegro.o Frontend/Frontend_Allegro/events.o Frontend/Frontend_Allegro/screen.o Backend/topScore.o Backend/frog.o Backend/main.o Backend/logic.o Backend/map.o Backend/delay.o -g -o main -Wall -lallegro -lallegro_image -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_acodec -lallegro_audio -lpthread
main_Raspy: Frontend/Frontend_Raspberry/display.o Backend/main.o Frontend/Frontend_Raspberry/menu.o Backend/logic.o Backend/map.o Backend/topScore.o Backend/delay.o Backend/frog.o  
	# Enlaza los archivos objeto y genera el ejecutable 'main', enlazando las bibliotecas necesarias
	$(CC) Frontend/Frontend_Raspberry/display.o Frontend/Frontend_Raspberry/menu.o Backend/topScore.o Backend/frog.o Backend/main.o Backend/logic.o Backend/map.o Backend/delay.o $(CFLAGS) $(OBJ) -g -o main  
		
Frontend/Frontend_Raspberry/display.o: Frontend/Frontend_Raspberry/display.c $(HDR) Frontend/Frontend_Raspberry/display.h
	$(CC) $(CFLAGS) -c Frontend/Frontend_Raspberry/display.c -o Frontend/Frontend_Raspberry/display.o

Frontend/Frontend_Raspberry/menu.o: Frontend/Frontend_Raspberry/menu.c $(HDR) Frontend/Frontend_Raspberry/menu.h
	$(CC) $(CFLAGS) -c Frontend/Frontend_Raspberry/menu.c -o Frontend/Frontend_Raspberry/menu.o

# Regla para compilar 'allegro.c' en el archivo objeto 'allegro.o'
Frontend/Frontend_Allegro/allegro.o: Frontend/Frontend_Allegro/allegro.c Frontend/Frontend_Allegro/allegro.h  
	# Compila 'allegro.c' con advertencias habilitadas
	gcc -c Frontend/Frontend_Allegro/allegro.c -Wall -o Frontend/Frontend_Allegro/allegro.o

# Regla para compilar 'screen.c' en el archivo objeto 'screen.o'
Frontend/Frontend_Allegro/screen.o: Frontend/Frontend_Allegro/screen.c Frontend/Frontend_Allegro/allegro.h 
	# Compila 'screen.c' con advertencias habilitadas
	gcc -c Frontend/Frontend_Allegro/screen.c -Wall -o Frontend/Frontend_Allegro/screen.o

# Regla para compilar 'events.c' en el archivo objeto 'events.o'
Frontend/Frontend_Allegro/events.o: Frontend/Frontend_Allegro/events.c Frontend/Frontend_Allegro/allegro.h 
	# Compila 'events.c' con advertencias habilitadas
	gcc -c Frontend/Frontend_Allegro/events.c -Wall -o Frontend/Frontend_Allegro/events.o

# Regla para compilar 'main.c' en el archivo objeto 'main.o'
Backend/main.o: Backend/main.c
	# Compila 'main.c' con advertencias habilitadas
	gcc Backend/main.c -c -Wall -o Backend/main.o

# Regla para compilar 'map.c' en el archivo objeto 'map.o'
Backend/map.o: Backend/map.c
	# Compila 'map.c' con advertencias habilitadas
	gcc Backend/map.c -c -Wall -o Backend/map.o

# Regla para compilar 'delay.c' en el archivo objeto 'delay.o'
Backend/delay.o: Backend/delay.c
	# Compila 'delay.c' con advertencias habilitadas
	gcc Backend/delay.c -c -Wall -o Backend/delay.o

# Regla para compilar 'logic.c' en el archivo objeto 'logic.o'
Backend/logic.o: Backend/logic.c
	# Compila 'logic.c' con advertencias habilitadas
	gcc Backend/logic.c -c -Wall -o Backend/logic.o

# Regla para compilar 'frog_position.c' en el archivo objeto 'frog_position.o'
Backend/frog.o: Backend/frog.c
	# Compila 'frog.c' con advertencias habilitadas
	gcc Backend/frog.c -c -Wall -o Backend/frog.o

# Regla para compilar 'topScore.c' en el archivo objeto 'topScore.o'
Backend/topScore.o: Backend/topScore.c
	# Compila 'topScore.c' con advertencias habilitadas
	gcc Backend/topScore.c -c -Wall -o Backend/topScore.o

# Regla de limpieza para eliminar los archivos objeto y el ejecutable
clean:
	# Elimina los archivos objeto y el ejecutable
	rm -f Backend/*.o main
	
