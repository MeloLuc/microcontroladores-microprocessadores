/*
 * File:   principal.c
 * Author: mauro
 *
 * Created on 27 de Março de 2026, 10:22
 */


#include "config.h"
#include "display7s.h"

int main(void) {
    
    // Configuração da porta do display de 7 segmentos
    TRISB = 0x00;
    unsigned char digito = 97;  // 00 -- 99
   
    while (TRUE) {
        for(int i=0;i<30;i++) {
            display7s(digito);
            __delay_ms(10);
       }
        
        digito = (digito+1)%100;
        
    }
}
