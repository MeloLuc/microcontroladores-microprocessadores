/*
 * File:   display7s.c
 * Author: mauro
 *
 * Created on 27 de Março de 2026, 10:23
 */


#include "display7s.h"
#include "config.h"

// Decodificador de display de 7 segmentos

unsigned char display7s_dir(unsigned char digito) {
    switch(digito) {
        case 0 : return 0xFE;
        case 1 : return 0x38;
        case 2 : return 0xDD;
        case 3 : return 0x7D;
        case 4 : return 0x3B;
        case 5 : return 0x77;
        case 6 : return 0xF7;
        case 7 : return 0x3C;
        case 8 : return 0xFF;
        case 9 : return 0x7F;
        default: return 0x01;  // caracter '-'
    }
}


unsigned char display7s_esq(unsigned char digito) {
    return display7s_dir(digito) & 0xEF;
}


void display7s(unsigned char digito) {
    DISPLAY = display7s_dir(digito%10);
    __delay_ms(10);     
    DISPLAY = display7s_esq(digito/10); 
}