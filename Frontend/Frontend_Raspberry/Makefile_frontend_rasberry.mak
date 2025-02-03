# Variables
CC = gcc
CFLAGS = -Wall -pthread
OBJ = joydrv.o disdrv.o  ../../Backend/map.o ../../Backend/frog.o #Objetos necesarios
HDR = joydrv.h disdrv.h  ../../Backend/map.h ../../Backend/frog.h #Librerias necesarias

# Targets
all: Frogger

Frogger: raspberry.o game_logic.o display.o menu.o $(OBJ) 
	$(CC) $(CFLAGS) raspberry.o game_logic.o display.o menu.o $(OBJ) -o Frogger

# Compile object files
raspberry.o: raspberry.c $(HDR) raspberry.h game_logic.h display.h menu.h
	$(CC) $(CFLAGS) -c raspberry.c


game_logic.o: game_logic.c $(HDR) game_logic.h 
	$(CC) $(CFLAGS) -c game_logic.c 

display.o: display.c $(HDR) display.h
	$(CC) $(CFLAGS) -c display.c 

menu.o: menu.c $(HDR) menu.h
	$(CC) $(CFLAGS) -c menu.c
# Clean up build files
clean:
	rm -f *.o

.PHONY: all clean
