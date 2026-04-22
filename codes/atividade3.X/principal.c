/*
 * File:   principal.c
 * Author: Wander teodoro
 * 
 * Created on 16 de Abril de 2026, 20:26
 */


#include "config.h"

void main(void) {
    CMCON = 0x07;       // Desliga os comparadores analógicos
    
    TRISA = 0b00000010; // Configura RA1 (S1) como entrada
    TRISB = 0b00000000; // Configura todo o PORTB como saída (incluindo RB0 e RB1)
    
    LED1 = DESLIGA;
    LED2 = DESLIGA;

    // Configuração do TMR0
    OPTION_REGbits.T0CS = 0; // Fonte de clock interno (Ciclo de máquina Fosc/4) 
    OPTION_REGbits.PSA = 0;  // Prescaler atribuído ao TMR0 
    OPTION_REGbits.PS = 0b111; // Prescaler máximo configurado para 1:256 
    
    INTCONbits.T0IE = 0;     // Garante que a interrupção do TMR0 está desligada (Polling puro) 
    INTCONbits.T0IF = 0;     // Limpa a flag de estouro
    
    // Variáveis de controle
    unsigned char estado_ciclo = 0;      // 0 = Repouso, 1 = LED1 aceso, 2 = LED2 aceso
    unsigned char contador_overflow = 0; // Conta quantos blocos de 50ms se passaram
    unsigned char ultimo_estado_S1 = 1;  // Lógica para detectar a "borda de descida" do botão

    while (TRUE) {
        
        // Verifica se a chave foi pressionada (Lógica invertida devido ao pull-up da McLab1)
        if (S1 == 0 && ultimo_estado_S1 == 1) {
            __delay_ms(20); // Delay simples para Debouncing (eliminação de ruído mecânico) 
            
            if (S1 == 0) { // Confirma o pressionamento
                estado_ciclo = 1;        // Inicia/Reinicia o ciclo
                LED1 = LIGA;             // Imediato: Acende LED1 indicando comando recebido
                LED2 = DESLIGA;
                
                // Rearme do Timer 
                TMR0 = 61;               // Carrega offset para contagem de ~50ms
                INTCONbits.T0IF = 0;     // Zera a flag 
                contador_overflow = 0;   // Zera a contagem de tempo acumulado
            }
        }
        ultimo_estado_S1 = S1; // Atualiza variável para reconhecer o botão solto
        
        
        if (estado_ciclo > 0) {
            
            // Monitoramento contínuo da flag TOIF (Polling) 
            if (INTCONbits.T0IF == 1) {
                INTCONbits.T0IF = 0;     // Limpa a flag para o próximo ciclo
                TMR0 = 61;               // Recarrega o TMR0 para mais ~50ms
                contador_overflow++;
                
                // Verifica se já passaram 10 estouros de 50ms (Totalizando 500ms)
                if (contador_overflow >= 10) {
                    contador_overflow = 0; // Prepara para a próxima contagem
                    
                    if (estado_ciclo == 1) {
                        // Transição 
                        estado_ciclo = 2;
                        LED1 = DESLIGA; // Apaga LED 1
                        LED2 = LIGA;    // Simultaneamente acende LED 2
                    } 
                    else if (estado_ciclo == 2) {
                        // Finalização
                        estado_ciclo = 0; // Volta ao repouso
                        LED1 = DESLIGA;
                        LED2 = DESLIGA; // Apaga o LED 2
                    }
                }
            }
        }
    }
}
