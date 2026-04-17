/*
 * File:   principal.c
 * Author: mauro
 * Duas chaves na porta A (RA1 e RA2) e o LED na porta B (RB0). 
 * A chave do bit RA1 liga o LED, e a chave do bit RA2 desliga o LED.
 * Created on 13 de Março de 2026, 10:35
 */


#include "config.h"

int main(void) {
    // Configuração das portas
    PORTA_CONF = 0x06; // 0b00000110;
    PORTB_CONF = 0x00;  // 0b00000000;
   
    while (TRUE) {
        if (CHAVE_LIGA==ON) {
            LED = LIGA;
        }
        
        if (CHAVE_DESLIGA==ON) {
            LED = DESLIGA;
        }
        
        
    }
}
