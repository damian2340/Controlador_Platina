/*
 * pidController.h
 *
 *  Created on: 7 dic. 2021
 *      Author: damian
 */

#ifndef INC_SYSTEM_PIDCONTROLLER_H_
#define INC_SYSTEM_PIDCONTROLLER_H_

typedef struct PID{
        /*param*/
        float kp;
        float ki;
        float kd;
        /*vector for fast vector pid*/
        float a[3];
        /*record*/
        float record[3];
        float output;
        float setPoint;

}myPid_t;

void pidInt(myPid_t* pid);
void pidReset(myPid_t* pid);
float pidUpdateInRuntime(myPid_t* pid, float feedBack);

#endif /* INC_SYSTEM_PIDCONTROLLER_H_ */
