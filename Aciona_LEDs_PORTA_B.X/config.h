
#ifndef CONFIG_H
#define	CONFIG_H

// CONFIG
#pragma config FOSC = EXTRCCLK  // Oscillator Selection bits (RC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, Resistor and Capacitor on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config LVP = ON         // Low-Voltage Programming Enable bit (RB4/PGM pin has PGM function, low-voltage programming enabled)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h> // include processor files - each processor file is guarded.  


#define TRUE 1

#define LEDs_PORTA_B PORTB

#define LIGA 0xFF
#define DESLIGA 0x00

#define RB0_RB2_RB4_R6_R8 0x55
#define RB1_RB3_RB5_R7 0xAA

#define _XTAL_FREQ 8000000L // 8 MHz

typedef unsigned char ubyte;  // define novo tipo inteiro de 8 bits não sinalzado

#endif	

