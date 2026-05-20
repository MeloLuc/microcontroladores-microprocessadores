/*
 * File:   main.c
 * Author: Lucas Melo Monteiro
 * Ativação do lcd baseado em 4 bits com os dados oriundos do teclado matricial
 * Created on 20 de Maio de 2026, 09:01
 */


#include <xc.h>
#include "config.h"
#include "lcd_4bits.h"
#include "teclado_matricial.h"

void main(void) {
 
    // Desliga conversores analógicos. 
    ADCON1 = 0x06; 
    // Desliga comparadores internos no PORTA/PORTE
    CMCON = 0x07;

    // RD4 a RD7 = Saídas (LCD) -> 0
    // RD0 a RD3 = Entradas (Linhas do Teclado) -> 1
    TRISD = 0x0F;

    // Configurando o PORTB (Colunas do Teclado)
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB2 = 0;

    // Configurando o PORTE (Controles do LCD E e RS)
    TRISEbits.TRISE1 = 0;
    TRISEbits.TRISE2 = 0;

    // INICIALIZAÇÃO
    lcd_init();

    char tecla_pressionada;
    char trava_tecla = 0; // Variável para controle de "Debounce" e repetição

    while(1) {
        tecla_pressionada = ler_teclado();

        // Se detectou uma tecla E a trava estiver solta (0)
        if (tecla_pressionada != 0 && trava_tecla == 0) {
            lcd_dat(tecla_pressionada); // Manda o caractere para o LCD
            trava_tecla = 1;            // Ativa a trava para não imprimir '111111'
        }
        
        // Nenhuma tecla presscionada
        if (tecla_pressionada == 0) {
            trava_tecla = 0; 
        }

        __delay_ms(20); //(Debounce)
    }
}
