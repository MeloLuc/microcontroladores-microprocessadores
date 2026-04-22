/*
 * File:   principal.c
 * Author: mauro
 * Placa: McLab1
 * Microcontrolador: PIC16F628A
 * Emulador: PICSimLab 0.92
 * Controlar o acionamento de LED no pino RB0 da porta B
 * por meio de uma única chave de pressão. O teste da chave
 * usado nesse caso é borda de descida com eliminação de bounce.
 * Created on 18 de Março de 2026, 13:50
 */


#include "config.h"
#include "chave.h"
#include <stdbool.h>


void main(void) {
    TRISA = 0b00000010; // RA1 entrada
    TRISB = 0b00000000; // PORTB saída
   
    LEDs = OFF;
    
    unsigned char pos_led = 0;
    
    while (TRUE) {
       
        if (chave_pressionada()) {
            LEDs = (unsigned char)(1 << pos_led);
            pos_led = (pos_led + 1) % 8;
        }
        
    }
}