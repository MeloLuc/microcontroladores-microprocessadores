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
        LEDs_PORTA_B = RB0_RB2_RB4_RB6_RB8;
        __delay_ms(500);
        
        LEDs_PORTA_B = RB1_RB3_RB5_RB7;
        __delay_ms(500);
    }
}
