# Variables
CC = gcc
CFLAGS = -Wall
OBJ = joydrv.o disdrv.o funciones.o
HDR = joydrv.h disdrv.h matrices.h funciones.h #Librerias necesarias

# Targets
all: frontend_raspberry

frontend_raspberry: raspberry.o $(OBJ)
	$(CC) $(CFLAGS) raspberry.o $(OBJ) -o frontend_raspberry

# Compile object files
raspberry.o: raspberry.c $(HDR)
	$(CC) $(CFLAGS) -c raspberry.c

funciones.o: funciones.c $(HDR)
	$(CC) $(CFLAGS) -c funciones.c

# Clean up build files
clean:
	rm -f *.o

.PHONY: all clean
