#include "config.h"
#include <xc.h>

void main( void ){
    
    //Configure the oscillator(64MHz using PLL)
    OSCCON  = 0b01110000;
    OSCTUNE = 0b01000000;
    
    
    //Set the RD2 pin as digital output
    ANSELDbits.ANSD2 = 0;
    TRISD = 0x00;
    TRISB = 0X00;
    
    //Sets all leds off before starts
    LATD = 0X00;
    
    //Blinking RD2
    while(1){
        LATDbits.LATD2 = 1;
        __delay_ms(1000);
        LATDbits.LATD2 = 0;
        __delay_ms(1000);
        __delay_ms(1000);
    }
    
return;
}