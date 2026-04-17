#ifndef CONFIG_H
#define	CONFIG_H

// CONFIGURAÇÕES DO PIC16F628A [cite: 134]
#pragma config FOSC = INTOSCIO  // Oscilador Interno (ou XT caso a McLab1 esteja usando cristal externo de 4MHz)
#pragma config WDTE = OFF       // Watchdog Timer desativado
#pragma config PWRTE = OFF      // Power-up Timer desativado
#pragma config MCLRE = ON       // Pino de MCLR ativado
#pragma config BOREN = ON       // Brown-out Detect ativado
#pragma config LVP = OFF        // Low-Voltage Programming desativado (Libera o pino RB4)
#pragma config CPD = OFF        // Proteção da EEPROM desativada
#pragma config CP = OFF         // Proteção de Código desativada

#include <xc.h>

// Frequência de 4 MHz solicitada 
#define _XTAL_FREQ 4000000L 

// Macros de facilidade
#define TRUE 1
#define LIGA 1
#define DESLIGA 0

// Mapeamento de Hardware conforme a placa McLab1 [cite: 136]
#define S1 PORTAbits.RA1   // Chave conectada ao RA1 [cite: 138]
#define LED1 PORTBbits.RB0 // LED1 conectado ao RB0 [cite: 139]
#define LED2 PORTBbits.RB1 // LED2 conectado ao RB1 [cite: 140]

#endif	/* CONFIG_H */