
#ifndef FROG_RASPY_H
#define FROG_RASPY_H
//librerias de uso de raspy
#include "menu.h"
#include "macros.h"
#include "display.h"
#include "disdrv.h"
#include "joydrv.h"
#include "../../Backend/frog.h"
#include "../../Backend/map.h"
void move_frog_by_joystick(frog_t *frog);//mueve la rana con el joystick
void update_frog_position(frog_t *frog);//actualiza la posicion de la rana
uint8_t detect_arrival_raspy(frog_t *frog);//detecta si la rana llego a la meta
#endif // FROG_RASPY_H