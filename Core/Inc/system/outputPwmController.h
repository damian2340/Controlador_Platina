/*
 * outputPwmController.h
 *
 *  Created on: 6 dic. 2021
 *      Author: damian
 */

#ifndef INC_SYSTEM_OUTPUTPWMCONTROLLER_H_
#define INC_SYSTEM_OUTPUTPWMCONTROLLER_H_

#include "hrtim.h"

void outputTurnOn(uint8_t eje);
void outputTurnOff(uint8_t eje);
void outputSetValue(uint8_t eje, float value);
float outputConstrainValue(float value);

#endif /* INC_SYSTEM_OUTPUTPWMCONTROLLER_H_ */
