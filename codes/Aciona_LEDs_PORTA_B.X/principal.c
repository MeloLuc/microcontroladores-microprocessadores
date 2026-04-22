/*
 * File:   principal.c
 * Author: Mauro Hemerly Gazzani
 * Placa: McLab1
 * Microcontrolador: PIC16F628A
 * Compilador: XC8
 * Aciona os LEDs conectados na porta B de forma intercalada, iniciando no
 * bit 0 da porta B, e, em seguida, aciona os demais LEDS.
 * Created on 6 de Março de 2026, 10:40
 */


#include "config.h"

void main(void) {
    TRISB = 0x00; // configura o registrador da porta B com todos de saída
   
    LEDs_PORTA_B = 0x01;  //inicialmente aciona o LED no bit RB0 durante 200 ms
    
    while (TRUE) {
        
        
        for(ubyte i = 0;i < 7;i++) { 
            __delay_ms(50);
            LEDs_PORTA_B = (ubyte)(LEDs_PORTA_B << 1);            
            
        }
        
        
         for(ubyte i = 0;i < 7;i++) { 
            __delay_ms(50);
            LEDs_PORTA_B = (ubyte)(LEDs_PORTA_B >> 1);            
            
        }
        
    }
}
