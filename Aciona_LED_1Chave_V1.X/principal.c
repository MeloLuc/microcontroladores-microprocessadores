/*
 * File:   principal.c
 * Author: mauro
 * Placa: McLab1
 * Microcontrolador: PIC16F628A
 * Emulador: PICSimLab 0.92
 * Controlar o acionamento de LED no pino RB0 da porta B
 * por meio de uma única chave de pressão. O teste da chave
 * usado nesse caso é por nível (estado da chave.
 * Created on 18 de Março de 2026, 13:50
 */


#include "config.h"


void main(void) {
    // configuração do pino RA1 da porta A como 
    // entrada, e os demais, como saída
    TRISA = 0b00000010; // 0x02 
    
    // configuração do pino RB0 da porta B como 
    // saída, bem como os demais.
    TRISB = 0b00000000; // 0x00
   
    LED = OFF;  // led inicialmente desligado.
    
    while (TRUE) {
        if (CHAVE_PRESSIONADA) {
            LED = !LED;
        }
    }
}
