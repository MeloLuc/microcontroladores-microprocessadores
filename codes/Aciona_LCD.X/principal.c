/*
 * File:   principal.c
 * Author: mauro
 *
 * Created on 27 de Maio de 2025, 20:56
 */


#include "config.h"
#include "lcd.h"
#include "float_str.h"


int main(void) {
    TRISD = 0X00;
    TRISE = 0X00;
    
    lcd_init();
    lcd_cmd(L_L1);
    lcd_cmd(L_NCR);
    print_lcd("Teste do LCD");
    float contador = -1.00;
    char str[8]; 
    
    while (TRUE) {
        float_str(contador, str);
        lcd_cmd(L_L2);
        print_lcd(str);
        contador = contador+0.1;
        __delay_ms(200);  
    }
}


