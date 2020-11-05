/*	Author: Andrew Bazua [abazu001]
 *  Partner(s) Name:
 *	Lab Section:
 *	Assignment: Lab #05  Exercise #1
 *	Exercise Description: [ car has a fuel-level sensor that sets PA3..PA0 to a value between 0 (empty)
        and 15 (full). A series of LEDs connected to PC5..PC0 should light to graphically indicate the
        fuel level. If the fuel level is 1 or 2, PC5 lights. If the level is 3 or 4, PC5 and PC4 light.
        Level 5-6 lights PC5..PC3. 7-9 lights PC5..PC2. 10-12 lights PC5..PC1. 13-15 lights PC5..PC0.
        Also, PC6 connects to a "Low fuel" icon, which should light if the level is 4 or less. ]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *  Demo Link:
 *  https://drive.google.com/file/d/1Q1zxgVYX7jrb_YHWA12pDViGBiZHUmGP/view?usp=sharing
 *  NOTE: link can only be accessed using rmail, it is set to only R'mail group can view
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;  // Sets PORTA as input PINA
    DDRC = 0xFF; PORTC = 0x00;  // Sets PORTC as output

    unsigned char tmpA = 0x00;
    unsigned char tmpC = 0x00;

    /* Insert your solution below */
    while (1) {
        tmpA = ~PINA;

        if ((tmpA & 0x3F) == 0x00) { tmpC = 0x40; }

        else if ((tmpA & 0x3F) <= 0x02) { tmpC = 0x60; }

        else if ((tmpA & 0x3F) <= 0x04) { tmpC = 0x70; }

        else if ((tmpA & 0x3F) <= 0x06) { tmpC = 0x38; }

        else if ((tmpA & 0x3F) <= 0x09) { tmpC = 0x3C; }

        else if ((tmpA & 0x3F) <= 0x0C) { tmpC = 0x03E; }

        else { tmpC = 0x3F; }

        PORTC = tmpC;

    }
    return 1;
}
