/*
 * File:   principal.c
 * Author: mauro
 * Placa: McLab1
 * Microcontrolador: PIC16F628A
 * Emulador: PICSimLab 0.92
 * Controlar o acionamento de LED no pino RB0 da porta B
 * por meio de uma única chave de pressão. O teste da chave
 * usado nesse caso é borda de descida.
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
   
    LEDs = OFF;  // led inicialmente desligado.
    
    unsigned char estado_anterior = 1;  // chave inicialmente não pressionada
    unsigned char estado_atual;      // estado atual da chave: 1:chave aberta 0:chave fechada
    unsigned char pos_led = 0;  // inicialmente nenhum led acionado
    
    while (TRUE) {
        estado_atual = CHAVE_ON_OFF;  // leitura do estado da chave
        
        // detecção da borda de descida
        if (estado_atual == 0 && estado_anterior == 1) { // chave comutada 1->0
            __delay_ms(1); // debounce - eliminar o bounce de pressionamento

            // confirma se ainda está pressionada
            if (CHAVE_ON_OFF == 0) {
                LEDs = (unsigned char) (1 << pos_led);
                pos_led = (pos_led + 1) % 8;
            }
        }
        
        // detecção da borda de subida
        if (estado_atual == 1 && estado_anterior == 0) {  // chave comutada 0->1?
            __delay_ms(1);  // debounce - eliminar o bounce de liberação
        }
        
        estado_anterior = estado_atual;
    }
}
