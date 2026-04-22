/*
 * File:   main.c
 * Author: Lucas Melo Monteiro
 *
 * Created on April 21, 2026, 12:44 PM
 */


#include "config.h"

int main(void) {
    // Configure the oscilator Block
    OSCCONbits.IRCF = 0b111;
    OSCTUNEbits.PLLEN = 0b1;
    
    // Configure the input pins
    TRISCbits.TRISC2 = 1;
    TRISCbits.TRISC3 = 1;
    TRISDbits.TRISD0 = 1;
    TRISDbits.TRISD1 = 1;
    
    // Looking in datasheets all has the analog capabilities
    // Configure the input as digital
    ANSELCbits.ANSC2 = 0;
    ANSELCbits.ANSC3 = 0;
    ANSELDbits.ANSD0 = 0;
    ANSELDbits.ANSD1 = 0;
    
    // Configure the output pins
    TRISCbits.TRISC5 = 0;
    TRISCbits.TRISC4 = 0;
    TRISDbits.TRISD3 = 0;
    TRISDbits.TRISD2 = 0;
    
    while (1) {
        
        LATCbits.LATC5 = PORTCbits.RC5;
        LATCbits.LATC4 = PORTCbits.RC4;
        LATDbits.LATD3 = PORTDbits.RD0;
        LATDbits.LATD2 = PORTDbits.RD1;
        
    }
}
