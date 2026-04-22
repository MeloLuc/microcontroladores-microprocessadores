/*
 * File:   principal.c
 * Author: aluno
 *
 * Created on 6 de Março de 2026, 10:40
 */


#include "config.h"

void main(void) {
    TRISB = 0X00;
    
    while (TRUE) {
        RB0 = LIGA;
        __delay_ms(500);
        
        RB0 = DESLIGA;
        __delay_ms(500);
    }
}
