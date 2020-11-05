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
 *  Demo Link:
 *  https://drive.google.com/file/d/1W5rNSrHgQm5Sk-TQoCwRo1gJjD4I6N8J/view?usp=sharing
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

typedef enum States {init, wait, waitPA0, festive } States;

int festiveLights(int);

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;

    States state = init;

    while (1) {
        state = festiveLights(state);

    }

    return 1;
}

/*
    Light Pattern:
        will alternate between
        00| 00 0101     //these bits shifting to the left
        00| 10 1000     //and these to the right

        00| 00 1010
        00| 01 0100

        00| 01 0100
        00| 00 1010

        and so on

        when output reaches 0x00 all variables reset

*/

int festiveLights(int state) {
    static unsigned char tmpC;      //variable to output
    static unsigned char cnt;       //keeps track of bits to shift by
    static unsigned char shiftCnt;  //tracks when both sides have been output
                                    //to increment cnt

    static unsigned char upDown;    //determines which side is being output

    unsigned char A0 = PINA & 0x01; //grabs input from PORTA

    switch (state) {
        case init:
            state = wait;
            cnt = 0x00;
            upDown = 0x00;
            shiftCnt = 0x00;
            tmpC = 0x00;
            break;

        case wait:
            state = A0 ? festive: wait;
            break;

        case waitPA0:
            state = A0 ? waitPA0: wait;
            break;

        case festive:
            state = waitPA0;
            break;

        default:
            state = init;
            break;
    }

    switch (state) {
        case init: break;

        case wait:
            if (tmpC == 0x00) {
                cnt = 0x00;
                shiftCnt = 0x00;
                upDown = 0x00;
            }
            break;

        case festive:
            if (shiftCnt == 0x02) {
                ++cnt;          //both sides have been output, increase shift
                shiftCnt = 0x00;
            }

            if (upDown) {           //prints upper lights
                tmpC = 0x28 >> cnt;

            }
            else {                  //prints lower lights
                tmpC = 0x05 << cnt;
            }

            if (upDown == 0x00) { upDown = 0x01; }  //flip flops upDown
            else { upDown = 0x00; }

            ++shiftCnt;

            //prevents output from reaching PB6 & PB7
            if (tmpC > 0x0F) { tmpC = tmpC & 0x3F; }


            break;

        case waitPA0: break;
    }
    PORTC = tmpC;

    return state;
}
