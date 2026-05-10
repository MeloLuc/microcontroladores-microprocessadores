/*
 * File:   display.c
 * Author: Lucas Melo Monteiro
 *
 * Created on 10 de Maio de 2026, 14:25
 */

#include "config.h"
#include "display.h"

void imprimir_display(unsigned char valor) {
    switch (valor) {
        case 0: PORTD = 0x3F; break;
        case 1: PORTD = 0x06; break;
        case 2: PORTD = 0x5B; break;
        case 3: PORTD = 0x4F; break;
        case 4: PORTD = 0x66; break;
        case 5: PORTD = 0x6D; break;
        case 6: PORTD = 0x7D; break;
        case 7: PORTD = 0x07; break;
        case 8: PORTD = 0x7F; break;
        case 9: PORTD = 0x6F; break;
        default: PORTD = 0x00; break;
    }
}

void multiplexar_display(unsigned char d7, unsigned char d6, unsigned char d5, unsigned char d4) {
    PORTB = 0x00;
    imprimir_display(d4);
    PORTBbits.RB4 = 1;
    __delay_ms(1);  // retina = 16ms/4 displays -> 4ms (resultado melhor com 1ms)
    
    PORTB = 0x00;
    imprimir_display(d5);
    PORTBbits.RB5 = 1;
    __delay_ms(1); 
    
    PORTB = 0x00;
    imprimir_display(d6);
    PORTBbits.RB6 = 1;
    __delay_ms(1); 
    
    PORTB = 0x00;
    imprimir_display(d7);
    PORTBbits.RB7 = 1;
    __delay_ms(1); 
    
    PORTB = 0x00;
}
