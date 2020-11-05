/*	Author: Andrew Bazua
 *  Partner(s) Name:
 *	Lab Section:023
 *	Assignment: Lab #5  Exercise #2
 *	Exercise Description: [Buttons are connected to PA0 and PA1. Output for PORTC
        is initially 7. Pressing PA0 increments PORTC once (stopping at 9).
        Pressing PA1 decrements PORTC once (stopping at 0). If both buttons are
        depressed (even if not initially simultaneously), PORTC resets to 0.]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *  Demo Link:
 *  https://drive.google.com/file/d/1VQsMZyiADj8j5En4XNau8AuLcpNGOBtH/view?usp=sharing
 *  Accidentially left sound on in this one
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

typedef enum States {init, waitA, waitInc, waitDec, increment, decrement, reset} States;

int counter(int);

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;

    States state = init;

    /* Insert your solution below */
    while (1) {
        state = counter(state);
    }
    return 1;
}

int counter(int state) {
    static unsigned char tmpC;

    unsigned char A0 = ~PINA & 0x01;
    unsigned char A1 = ~PINA & 0x02;

    switch (state) {        //TRANSITIONS
        case init:
            state = waitA;
            tmpC = 0x07;
            break;

        case waitA:
            if (A0 && !A1){ state = increment; }
            else if (!A0 && A1) { state = decrement; }
            else if (A0 && A1) { state = reset; }
            else { state = waitA; }
            break;

        case increment:
            if (A0 && !A1) { state = waitInc; }
            else if (A0 && A1) { state = reset; }
            else if (!A0 && !A1) { state = waitA; }
            break;

        case waitInc:
            if (!A0 && !A1) { state = waitA; }
            else if (A0 && !A1) { state = waitInc; }
            else if (A0 && A1) { state = reset; }
            break;

        case decrement:
            if (!A0 && A1) { state = waitDec; }
            else if (A0 && A1) { state = reset; }
            else if (!A0 && !A1) { state = waitA; }
            break;

        case waitDec:
            if (!A0 && !A1) { state = waitA; }
            else if (A0 && A1) { state = reset; }
            else if (!A0 && A1) { state = waitDec; }
            break;

        case reset:
            state = (A0 && A1)? reset: waitA;
            break;

        default:
            state = init;
            break;
    }

    switch (state) {        //ACTIONS
        case init: break;

        case waitA: break;

        case increment:
            if (tmpC < 9) { ++tmpC; }
            break;

        case waitInc: break;

        case decrement:
            if (tmpC > 0) { --tmpC; }
            break;

        case waitDec: break;

        case reset:
            tmpC = 0x00;
            break;
    }

    PORTC = tmpC;
    return state;
}
