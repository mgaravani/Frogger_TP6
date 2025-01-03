/*
 * Joystick Driver
 *
 * Copyright 2019  Catedra Programacion I - ITBA
 *
 * Author(s):
 *  Daniel Jacoby
 *  Nicolas Magliola
 *  Pablo Vacatello
 */

#ifndef JOYDRV_H
#define JOYDRV_H


/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdint.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

//Las coordenadas del joystick varían entre -128 y 127 para cada coordenada
#define JOY_MAX_POS     127		
#define JOY_MAX_NEG     -128


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/


typedef enum {J_NOPRESS, J_PRESS} jswitch_t;


typedef struct {
    int8_t x;
    int8_t y;
    jswitch_t sw;
} joyinfo_t;


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Inicializa el joystick. Debe llamarse UNA vez antes de empezar a usar el joystick.
*/
void joy_init(void);

/**
 * @brief Devuelve toda la información del joystick en una sola estructura. 
 * @return Una estructura de tipo joyinfo_t con las coordenadas del joystick y 
 * además una variable de tipo jswich_t, es decir, J_NOPRESS o J_PRESS.
*/
joyinfo_t joy_read(void);


/*******************************************************************************
 ******************************************************************************/

#endif // JOYDRV_H
