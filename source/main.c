/*	Author: papercrane
 *  Partner(s) Name:
 *	Lab Section:
 *	Assignment: Lab #5  Exercise #3
 *	Exercise Description: [Create your own festive lights display with 6 LEDs
        connected to port PB5..PB0, lighting in some attractive sequence.
        Pressing the button on PA0 changes the lights to the next configuration
        in the sequence.  Use a state machine (not synchronous) captured in C. ]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

typedef enum States {init, wait, festive, waitPA0 } States;

int festiveLights(int);

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;

    States state = init;

    while (1) {
        state = festiveLights(state);

    }

    return 1;
}

int festiveLights(int state) {
    static unsigned char tmpB;
    static unsigned char cnt;
    static unsigned char shiftCnt;
    static unsigned char upDown;

    unsigned char A0 = PINA & 0x01;

    switch (state) {
        case init:
            state = wait;
            cnt = 0x00;
            upDown = 0x00;
            break;

        case wait:
            state = A0 ? festive: wait;
            break;

        case festive:
            state = waitPA0;
            break;

        case waitPA0:
            state = A0 ? waitPA0: wait;
            break;

        default:
            state = init;
            break;
    }

    switch (state) {
        case init: break;

        case wait:
            if (tmpB == 0x00) {
                cnt = 0x00;
            }
            break;

        case festive:
            if (shiftCnt == 0x02) {
                ++cnt;
                shiftCnt = 0x00;
            }

            if (upDown) {
                tmpB = 0x28 >> cnt;

            }
            else {
                tmpB = 0x05 << cnt;
            }

            upDown = ~upDown;
            ++shiftCnt;
            break;

        case waitPA0: break;
    }


    PORTB = tmpB;
    return state;
}
