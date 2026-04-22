/*
 * File:   principal.c
 * Author: Lucas De Melo Monteiro Peixoto
 * Aciona os lEDS conectados na porta B de formar intercalada iniciando no bit 0
 * da porta b e em seguido aciona os demais leds.
 * Created on 11 de Março de 2026, 15:18
 */


#include "config.h"

void main(void) {
    TRISB = 0X00;
    
    while (TRUE) {
        LEDs_PORTA_B = 0x01;
        
        for(ubyte i = 0; i < 7; i++) {
            __delay_ms(200);
            LEDs_PORTA_B = (ubyte) (LEDs_PORTA_B << 1);
        }
        
        __delay_ms(200);
    }
}
