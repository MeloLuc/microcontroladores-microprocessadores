/*
 * File:   system.c
 * Author: Lucas Melo Monteiro
 *
 * Created on 28 de Junho de 2026, 22:13
 */

#include "system.h"

// Configuração do PIC16F877A
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

void system_init(void)
{
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    PORTE = 0x00;

    TRISA = 0x21; /* RA0 (LM35) e RA5 (Botão de Power) como entradas */
    TRISB = 0x38; /* RB3, RB4 e RB5 como entradas para os botões */
    TRISC = 0x00; /* RC5 como saída para o Heater */
    TRISD = 0x00; /* LCD data bus */
    TRISE = 0x00; /* LCD control pins */
}