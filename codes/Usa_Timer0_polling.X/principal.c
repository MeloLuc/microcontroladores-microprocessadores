/*
 * File:   principal.c
 * Author: mauro
 *
 * Created on 8 de Abril de 2026, 10:36
 */


#include "config.h"

int main(void) {
    TRISB = 0x00;  // porta dos LEDs
    
    // PSA = 0 (Timer 0) (PS2:PS0) = 111 (PRESCALER = 1:256)
    OPTION_REG = 0x07;
    TMR0 = 0;   // valor inicial do contador do Timer 0
    
    ubyte contador_estouros = 0;
    LED = 0;  // LED do pino RB0 inicialmente desligado
    
    while (TRUE) {
        if (FLAG_OVERFLOW) {  // ocorreu estouro do Timer 0 ?
            FLAG_OVERFLOW = 0;
            
            contador_estouros++;          
            if (contador_estouros == 7) {
                LED = !LED;  // pisca o LED
                contador_estouros = 0;
            }
        }
    }
}
