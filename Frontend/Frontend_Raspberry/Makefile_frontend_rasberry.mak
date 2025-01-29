# Variables
CC = gcc
CFLAGS = -Wall -pthread
OBJ = joydrv.o disdrv.o functions.o ../../Backend/map.o ../../Backend/frog.o #Objetos necesarios
HDR = joydrv.h disdrv.h arrays.h functions.h ../../Backend/map.h ../../Backend/frog.h #Librerias necesarias

# Targets
all: frontend_raspberry

frontend_raspberry: raspberry.o $(OBJ) 
	$(CC) $(CFLAGS) raspberry.o $(OBJ) -o frontend_raspberry

# Compile object files
raspberry.o: raspberry.c $(HDR) raspberry.h
	$(CC) $(CFLAGS) -c raspberry.c

funciones.o: funciones.c $(HDR)
	$(CC) $(CFLAGS) -c funciones.c

# Clean up build files
clean:
	rm -f *.o

.PHONY: all clean
