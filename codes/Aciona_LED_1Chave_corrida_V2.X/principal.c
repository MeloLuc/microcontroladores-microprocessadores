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

// Função para leitura da chave com debounce e detecção de borda de descida
unsigned char chave_pressionada(void) {
    static unsigned char estado_anterior = CHAVE_LIBERADA; // mantém valor entre chamadas
    unsigned char estado_atual;
    
    estado_atual = CHAVE_ON_OFF;
    
    // detecção da borda de descida
    if (BORDA_DESCIDA(estado_atual, estado_anterior)) {
        __delay_ms(1); // debounce
        
        // confirma pressionamento
        if (CHAVE_ON_OFF == CHAVE_PRESSIONADA) {
            estado_anterior = CHAVE_PRESSIONADA;
            return 1; // evento de pressionamento válido
        }
    }
    
    // detecção da borda de subida (apenas para atualizar estado)
    if (BORDA_SUBIDA(estado_atual, estado_anterior)) {
        __delay_ms(1); // debounce
        estado_anterior = CHAVE_LIBERADA;
        return 0;
    }
    
    estado_anterior = estado_atual;
    return 0;
}

void main(void) {
    TRISA = 0b00000010; // RA1 entrada
    TRISB = 0b00000000; // PORTB saída
   
    LEDs = OFF;
    
    unsigned char pos_led = 0;
    
    while (TRUE) {
        
        // usa a função
        if (chave_pressionada()) {
            LEDs = (unsigned char)(1 << pos_led);
            pos_led = (pos_led + 1) % 8;
        }
        
    }
}