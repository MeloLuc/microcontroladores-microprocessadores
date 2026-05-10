/*
 * File:   principal.c
 * Author: mauro
 *
 * Created on 27 de Maio de 2025, 20:56
 */


#include "config.h"
#include "lcd.h"
#include "float_str.h"
float contador = 0;
unsigned char estadoAnterior = 1;
unsigned char estadoAtual = 1;

void contador_ciclo() {
    estadoAtual = PORTBbits.RB0;
    if( && estadoAnterior == 1){
    
    }
};


int main(void) {
    TRISD = 0X00;
    TRISE = 0X00;
    
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 1;
    
    lcd_init();
    lcd_cmd(L_L1);
    lcd_cmd(L_NCR);
    print_lcd("Contador:");
    char str[8]; 
    
    while (TRUE) {
        float_str(contador, str);
        lcd_cmd(L_L2);
        print_lcd(str);
        contador_ciclo();
        __delay_ms(200);  
    }
}

