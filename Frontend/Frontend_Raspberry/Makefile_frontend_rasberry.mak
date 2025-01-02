# Variables
CC = gcc
CFLAGS = -Wall
OBJ = joydrv.o disdrv.o Funciones.o
HDR = joydrv.h disdrv.h Matrices.h Funciones.h

# Targets
all: Frontend

Frontend: Frontend.o $(OBJ)
	$(CC) $(CFLAGS) Frontend.o $(OBJ) -o Frontend

# Compile object files
Frontend.o: Frontend.c $(HDR)
	$(CC) $(CFLAGS) -c Frontend.c

Funciones.o: Funciones.c $(HDR)
	$(CC) $(CFLAGS) -c Funciones.c

# Clean up build files
clean:
	rm -f *.o Frontend

.PHONY: all clean
