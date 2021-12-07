/*
 * com.c
 *
 *  Created on: 6 dic. 2021
 *      Author: damian
 */
#include <stdio.h>
#include <stdlib.h>
#include "system/comm.h"
#include "system/pidController.h"

extern cBufferHandler_t TxbufferHandler;
extern bufferType_t CurrentBufferType;
extern uint8_t stdInBuffer[SDIN_BUFFER_SIZE];

extern myPid_t ejeX;
extern myPid_t ejeY;
extern myPid_t ejeZ;

extern volatile uint8_t isCloseLoop;

void txTask() {
	static txState_t requestState = StateTxIDLE;
	static txContext_t txContext = { .TxState = StateTxSTOPPED, };

	switch (txContext.TxState) {
	case StateTxSTOPPED:
		txInitialize(&txContext);
		break;
	case StateTxIDLE:
		if (txContext.CurrentBuffer->BufferState == BUFFER_idle) {
			txContext.TxState = requestState;
			if (txContext.TxState == StateTxIDLE) {
				if (txContext.CurrentBuffer->BufferDataLength > 0) {
					TransmitionStart(txContext.CurrentBuffer);
				}
			} else {
				requestState = StateTxIDLE;
			}
		}
		break;
	case StateTxBUSY:
		break;
	case StateSetDataBuffer:
		if (txContext.CurrentBuffer->BufferState == BUFFER_idle) {
			txContext.TxState = StateTxIDLE;
		}
		break;
	case StateSetStdoBuffer:
		if (txContext.CurrentBuffer->BufferState == BUFFER_idle) {
			txContext.CurrentBuffer = &TxbufferHandler;
			CurrentBufferType = sdoutBufferType;
			txContext.TxState = StateTxIDLE;
		}
		break;
	case StateResetDataBuffer:
		if (txContext.CurrentBuffer->BufferState == BUFFER_idle) {
			txContext.TxState = StateTxIDLE;
		}
		break;
	case StateResetStdoBuffer:
		if (txContext.CurrentBuffer->BufferState == BUFFER_idle) {
			txContext.TxState = StateTxIDLE;
		}
		break;
	case StateTxERROR:
		break;
	}
}

void rxTask() {
	static rxContext_t rxContext = { .RxState = StateRxSTOPPED, };
	float value;
	switch (rxContext.RxState) {
	case StateRxSTOPPED: {
		rxInitialize(&rxContext);
	}
		break;
	case StateRxIDLE: {
		if (sdinIsBusy() == BUFFER_busy) {
			rxContext.RxState = StateRxBUSY;
		}
	}
		break;
	case StateRxBUSY: {

		switch (stdInBuffer[0]) {
		case 'S':
		case 's':
			if (stdInBuffer[2] == 'A' || stdInBuffer[2] == 'a') {
				outputTurnOn('x');
				outputTurnOn('y');
				outputTurnOn('z');

			} else if (stdInBuffer[2] == 'O' || stdInBuffer[2] == 'o') {
				outputTurnOff('x');
				outputTurnOff('y');
				outputTurnOff('z');
			}
			break;
		case 'X':
		case 'x':
			value = atof((char const *) (stdInBuffer + 1));
			if(isCloseLoop == 0){
				outputSetValue('x', value);
			}else{
				ejeX.setPoint = value;
			}
			break;
		case 'Y':
		case 'y':
			value = atof((char const *) (stdInBuffer + 1));
			if(isCloseLoop == 0){
				outputSetValue('y', value);
			}else{
				ejeY.setPoint = value;
			}
			break;
		case 'Z':
		case 'z':
			value = atof((char const *) (stdInBuffer + 1));
			if(isCloseLoop == 0){
				outputSetValue('z', value);
			}else{
				ejeZ.setPoint = value;
			}
			break;
		case 'C':
			if(isCloseLoop){
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
				isCloseLoop = 0;
			}
			else{
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
				isCloseLoop = 1;
			}
		case 'K':
		case 'k':
			value = atof((char const *) (stdInBuffer + 3));
			if (stdInBuffer[1] == 'P' || stdInBuffer[1] == 'p') {
				setKp(stdInBuffer[2], value);
			} else if (stdInBuffer[1] == 'I' || stdInBuffer[1] == 'i') {
				setKi(stdInBuffer[2], value);
			} else if (stdInBuffer[1] == 'D' || stdInBuffer[1] == 'd') {
				setKd(stdInBuffer[2], value);
			}

			break;
		default: {
			printf("Comando Desconocido\n\r");
		}
		}
		printf("Receive: %s \n\r", stdInBuffer);
		stdinSetter(BUFFER_idle);
		rxContext.RxState = StateRxIDLE;
	}
		break;
	case StateRxERROR: {
	}
		break;
	}
}

void setKp(uint8_t eje, float value ){
	switch(eje){
	case 'x':
	case 'X':
		ejeX.kp = value;
		pidInt(&ejeX);
		break;
	case 'y':
	case 'Y':
		ejeY.kp = value;
		pidInt(&ejeY);
		break;
	case 'z':
	case 'Z':
		ejeZ.kp = value;
		pidInt(&ejeZ);
		break;
	}
}
void setKi(uint8_t eje, float value ){
	switch(eje){
	case 'x':
	case 'X':
		ejeX.ki = value;
		pidInt(&ejeX);
		break;
	case 'y':
	case 'Y':
		ejeY.ki = value;
		pidInt(&ejeY);
		break;
	case 'z':
	case 'Z':
		ejeZ.ki = value;
		pidInt(&ejeZ);
		break;
	}
}
void setKd(uint8_t eje, float value ){
	switch(eje){
	case 'x':
	case 'X':
		ejeX.kd = value;
		pidInt(&ejeX);
		break;
	case 'y':
	case 'Y':
		ejeY.kd = value;
		pidInt(&ejeY);
		break;
	case 'z':
	case 'Z':
		ejeZ.kd = value;
		pidInt(&ejeZ);
		break;
	}
}

void txInitialize(txContext_t * txContext) {
	txContext->TxState = StateTxIDLE;
	txContext->CurrentBuffer = &TxbufferHandler;
}

void rxInitialize(rxContext_t * rxContext) {
	rxContext->RxState = StateRxIDLE;
}
