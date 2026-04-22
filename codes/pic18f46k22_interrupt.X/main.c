/*
 * File:   main.c
 * Author: Lucas Melo Monteiro
 *
 * Created on April 21, 2026, 7:36 PM
 */


#include "config.h"

short selected_pin = 0;

void main(void) {
    //Oscilator Block 64MHz
    OSCCONbits.IRCF = 0b111;
    OSCTUNEbits.PLLEN = 0b1;
    
    //I/O Configurations
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB0 = 1;
    LATB = 0x00; //OFF
    
    ANSELBbits.ANSB1 = 0;
    ANSELBbits.ANSB0 = 0;
    
    TRISD = 0x00; //Output
    LATD = 0x00; //OFF

    //Configure Global Interrupts bits
    RCONbits.IPEN = 1; //Enable priorities
    INTCONbits.GIEH = 1; //Enable global interrupt high
    INTCONbits.GIEL = 1; //Enable global interrupt low
    
    //Configure the INT1
    INTCON2bits.INTEDG1 = 1; //Rising edge triggered
    INTCON3bits.INT1IP = 0; //Priority low
    INTCON3bits.INT1F = 0; //Clear flag
    INTCON3bits.INT1IE = 1; //Enable the interrupt INT1
    
    //Configure the INT0
    INTCON2bits.INTEDG1 = 1; //Rising edge triggered
    //INT0 high priority
    INTCONbits.INT0IF = 0; //Clear flag
    INTCONbits.INT0IE = 1; //Enable the interrupt INT1
    
    while (1) {
        
        if(selected_pin == 0) {
            LATDbits.LATD0 = 1;
            __delay_ms(500);
            LATDbits.LATD0 = 0;
            __delay_ms(500);
        }
        else if (selected_pin == 1) {
            LATDbits.LATD1 = 1;
            __delay_ms(500);
            LATDbits.LATD1 = 0;
            __delay_ms(500);
        }
        else if (selected_pin == 2) {
            LATDbits.LATD2 = 1;
            __delay_ms(500);
            LATDbits.LATD2 = 0;
            __delay_ms(500);
        }
        else if (selected_pin == 3) {
            LATDbits.LATD3 = 1;
            __delay_ms(500);
            LATDbits.LATD3 = 0;
            __delay_ms(500);
        }
        else if (selected_pin == 4) {
            LATDbits.LATD4 = 1;
            __delay_ms(500);
            LATDbits.LATD4 = 0;
            __delay_ms(500);
        }
        else if (selected_pin == 5) {
            LATDbits.LATD5 = 1;
            __delay_ms(500);
            LATDbits.LATD5 = 0;
            __delay_ms(500);
        }
        else if (selected_pin == 6) {
            LATDbits.LATD6 = 1;
            __delay_ms(500);
            LATDbits.LATD6 = 0;
            __delay_ms(500);
        }
        else if (selected_pin == 7) {
            LATDbits.LATD7 = 1;
            __delay_ms(500);
            LATDbits.LATD7 = 0;
            __delay_ms(500);
        }
        
    }
}

void __interrupt(high_priority) ISR_high(){
    selected_pin--;
    
    if(selected_pin == -1) selected_pin = 7;
    
    //delay for debouncing
    __delay_ms(140);
    
    //clear flag
    INTCONbits.INT0IF = 0;
}

void __interrupt(low_priority) ISR_low(){
    selected_pin++;
    
    if(selected_pin == 8) selected_pin = 0;
    
    //delay for debouncing
    __delay_ms(140);
    
    //clear flag
    INTCON3bits.INT1IF = 0;
}
