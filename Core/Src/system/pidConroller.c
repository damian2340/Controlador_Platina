/*
 * pidConroller.c
 *
 *  Created on: 7 dic. 2021
 *      Author: damian
 */

#include "system/pidController.h"
#include "system/outputPwmController.h"

myPid_t ejeX;
myPid_t ejeY;
myPid_t ejeZ;

void pidInt(myPid_t* pid) {

    pid->a[0] = pid->kp + pid->ki + pid->kd;
    pid->a[1] = -pid->kp - 2 * pid->kd;
    pid->a[2] = pid->kd;

    pid->record[0] = 0;
    pid->record[1] = 0;
    pid->record[2] = 0;
}

void pidReset(myPid_t* pid) {
    pid->record[0] = 0;
    pid->record[1] = 0;
    pid->record[2] = 0;
}

float pidUpdateInRuntime(myPid_t* pid, float feedBack) {
    pid->record[2] = pid->record[1];
    pid->record[1] = pid->record[0];
    pid->record[0] = pid->setPoint - feedBack;
    /*
     y[n] = y[n-1] + A0 * x[n] + A1 * x[n-1] + A2 * x[n-2]
     */
    pid->output += pid->record[0] * pid->a[0] + pid->record[1] * pid->a[1] + pid->record[2] * pid->a[2];

    /*AntiWindUp*/
    pid->output = outputConstrainValue(pid->output);

    return pid->output;
}
