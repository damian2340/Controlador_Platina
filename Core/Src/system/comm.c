/*
 * com.c
 *
 *  Created on: 6 dic. 2021
 *      Author: damian
 */
#include <stdio.h>

#include "system/comm.h"

extern cBufferHandler_t TxbufferHandler;
extern bufferType_t CurrentBufferType;
extern uint8_t stdInBuffer[SDIN_BUFFER_SIZE];

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
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
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

void txInitialize(txContext_t * txContext) {
    txContext->TxState = StateTxIDLE;
    txContext->CurrentBuffer = &TxbufferHandler;
}

void rxInitialize(rxContext_t * rxContext) {
    rxContext->RxState = StateRxIDLE;
}
