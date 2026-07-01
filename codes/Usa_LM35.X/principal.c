/*
 * File:   principal.c
 * Autor: Mauro Hemerly Gazzani
 * Emulador PICSimLab 0.9.2
 * Placa: PICGenios
 * Data: 9 de Junho de 2026, 17:54
 */


#include <stdint.h>
#include "config.h"
#include "float_str.h"
#include "adc.h"
#include "lcd_4bits.h"



int main(void) {
    uint16_t adc;
    float temperatura;
    char temperatura_txt[8];
    
    TRISA = 0x04;   // RA2 entrada (LM35)
    TRISD = 0x00;   // LCD
    TRISE = 0x00;   // LCD
    TRISC = 0x00;   // RC5 saída (Heater)

    adc_init();  // conversor A/D
    lcd_init();  // display LCD 16x2
    
    

    while(TRUE){
        
        // Aquecimento
        // Liga aquecedor
        HEATER = ON;  // heater (aquecedor))  =1 : ligado   =0 : desligado
        for(uint16_t i=0;i<70;i++) {
            adc = adc_read(2);

            temperatura = (adc * 500.0)/1023.0;
        
            lcd_gotoxy(1,1);
            print_lcd("Heater ON ");

            float_str(temperatura, temperatura_txt);  // converte para string

            lcd_gotoxy(2,1);
            print_lcd(temperatura_txt);
            lcd_dat(GRAU); 
            lcd_dat(CELSIUS); 
             lcd_dat(TEMP_SUBINDO);
        }
        
        // Resfriamento
        // Desliga aquecedor
        HEATER = OFF;  // heater (aquecedor))  =1 : ligado   =0 : desligado
        for(uint16_t i=0;i<140;i++) {
            adc = adc_read(2);

            temperatura = (adc * 500.0)/1023.0;
        
            lcd_gotoxy(1,1);
            print_lcd("Heater OFF");

            float_str(temperatura, temperatura_txt);

            lcd_gotoxy(2,1);
            print_lcd(temperatura_txt);
            lcd_dat(GRAU); 
            lcd_dat(CELSIUS); 
            lcd_dat(TEMP_DESCENDO);
        }

       
    }
}
