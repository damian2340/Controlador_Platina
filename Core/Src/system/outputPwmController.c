/*
 * outputPwmController.c
 *
 *  Created on: 6 dic. 2021
 *      Author: damian
 */

#include "system/outputPwmController.h"

#define MAX_OUTPUT_VALUE 50147.0
#define MIN_OUTPUT_VALUE 147.0

extern HRTIM_HandleTypeDef hhrtim1;

/**
 * Enciende los PWM para setear el voltaje de salida que mueve los piezoelectricos
 *      uint8_t eje: caracter
 *                      X enciende la salida que controla em moviiento del eje x
 *                      Y enciende la salida que controla em moviiento del eje y
 *                      Z enciende la salida que controla em moviiento del eje z
 */
void outputTurnOn(uint8_t eje) {
    switch (eje) {
        case 'x':
        case 'X':
            HAL_HRTIM_SimpleBaseStart(&hhrtim1, HRTIM_TIMERINDEX_MASTER);
            HAL_HRTIM_SimplePWMStart(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_OUTPUT_TA1);
            HAL_HRTIM_SimplePWMStart(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_OUTPUT_TA2);
            HAL_HRTIM_SimplePWMStart(&hhrtim1, HRTIM_TIMERINDEX_TIMER_B, HRTIM_OUTPUT_TB1);
            HAL_HRTIM_SimplePWMStart(&hhrtim1, HRTIM_TIMERINDEX_TIMER_B, HRTIM_OUTPUT_TB2);
            break;
        case 'y':
        case 'Y':
            HAL_HRTIM_SimpleBaseStart(&hhrtim1, HRTIM_TIMERINDEX_MASTER);
            HAL_HRTIM_SimplePWMStart(&hhrtim1, HRTIM_TIMERINDEX_TIMER_C, HRTIM_OUTPUT_TC1);
            HAL_HRTIM_SimplePWMStart(&hhrtim1, HRTIM_TIMERINDEX_TIMER_C, HRTIM_OUTPUT_TC2);
            HAL_HRTIM_SimplePWMStart(&hhrtim1, HRTIM_TIMERINDEX_TIMER_D, HRTIM_OUTPUT_TD1);
            HAL_HRTIM_SimplePWMStart(&hhrtim1, HRTIM_TIMERINDEX_TIMER_D, HRTIM_OUTPUT_TD2);
            break;
        case 'z':
        case 'Z':
            HAL_HRTIM_SimpleBaseStart(&hhrtim1, HRTIM_TIMERINDEX_MASTER);
            HAL_HRTIM_SimplePWMStart(&hhrtim1, HRTIM_TIMERINDEX_TIMER_E, HRTIM_OUTPUT_TE1);
            HAL_HRTIM_SimplePWMStart(&hhrtim1, HRTIM_TIMERINDEX_TIMER_E, HRTIM_OUTPUT_TE2);
            break;
    }
}

void outputTurnOff(uint8_t eje) {
    switch (eje) {
        case 'x':
        case 'X':
            HAL_HRTIM_SimplePWMStop(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_OUTPUT_TA1);
            HAL_HRTIM_SimplePWMStop(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_OUTPUT_TA2);
            HAL_HRTIM_SimplePWMStop(&hhrtim1, HRTIM_TIMERINDEX_TIMER_B, HRTIM_OUTPUT_TB1);
            HAL_HRTIM_SimplePWMStop(&hhrtim1, HRTIM_TIMERINDEX_TIMER_B, HRTIM_OUTPUT_TB2);
            break;
        case 'y':
        case 'Y':
            HAL_HRTIM_SimplePWMStop(&hhrtim1, HRTIM_TIMERINDEX_TIMER_C, HRTIM_OUTPUT_TC1);
            HAL_HRTIM_SimplePWMStop(&hhrtim1, HRTIM_TIMERINDEX_TIMER_C, HRTIM_OUTPUT_TC2);
            HAL_HRTIM_SimplePWMStop(&hhrtim1, HRTIM_TIMERINDEX_TIMER_D, HRTIM_OUTPUT_TD1);
            HAL_HRTIM_SimplePWMStop(&hhrtim1, HRTIM_TIMERINDEX_TIMER_D, HRTIM_OUTPUT_TD2);
            break;
        case 'z':
        case 'Z':
            HAL_HRTIM_SimplePWMStop(&hhrtim1, HRTIM_TIMERINDEX_TIMER_E, HRTIM_OUTPUT_TE1);
            HAL_HRTIM_SimplePWMStop(&hhrtim1, HRTIM_TIMERINDEX_TIMER_E, HRTIM_OUTPUT_TE2);
            break;
    }
}

void outputSetValue(uint8_t eje, float value) {
    value = outputConstrainValue(value);
    switch (eje) {
        case 'x':
        case 'X':
            __HAL_HRTIM_SETCOMPARE(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_COMPAREUNIT_1, (uint16_t) value);
            __HAL_HRTIM_SETCOMPARE(&hhrtim1, HRTIM_TIMERINDEX_TIMER_B, HRTIM_COMPAREUNIT_1, (uint16_t) value);
            break;
        case 'y':
        case 'Y':
            __HAL_HRTIM_SETCOMPARE(&hhrtim1, HRTIM_TIMERINDEX_TIMER_C, HRTIM_COMPAREUNIT_1, (uint16_t) value);
            __HAL_HRTIM_SETCOMPARE(&hhrtim1, HRTIM_TIMERINDEX_TIMER_D, HRTIM_COMPAREUNIT_1, (uint16_t) value);
            break;
        case 'z':
        case 'Z':
            __HAL_HRTIM_SETCOMPARE(&hhrtim1, HRTIM_TIMERINDEX_TIMER_E, HRTIM_COMPAREUNIT_1, (uint16_t) value);
            break;
    }
}

float outputConstrainValue(float value) {
    if (value > MAX_OUTPUT_VALUE) {
        value = MAX_OUTPUT_VALUE;
    } else if (value < MIN_OUTPUT_VALUE) {
        value = MIN_OUTPUT_VALUE;
    }
    return value;
}
