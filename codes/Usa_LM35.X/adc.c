/*
 * File:   adc.c
 * Author: Mauro Hemerly (Hämmerli) Gazzani
 *
 * Created on 9 de Junho de 2025, 09:49
 */


#include "adc.h" 
#include "config.h"

void adc_init(void) {
    TRIMPOT1 = 1;   // entrada AN0
    
    // Registrador ADCON0: controla a operação do módulo A/D
    // Bits 7:6 ? ADCS1:ADCS0 = 01 ? Fosc/16
    // Bits 5-3 ? CHS1:CHS0 = 00 ? seleciona o canal AN0 (RA0)
    // Bit 2   ? GO/DONE = 0 (a conversão ainda não começou)
    // Bit 1   ? não usado
    // Bit 0   ? ADON = 1 ? liga o módulo ADC
    ADCON0 = 0b01000001;   // 0x41 - pág. 127
    
    // Registrador ADCON1: configura os pinos da porta
    // Bit 7 ? ADFM = 1 ? justificação à direita
    // Bits 6 ? ADCS2 = 1 ? Fosc/16
    // Bits 5:4 ? não usados (considere como '0')
    // Bits 3-0 ? PCFG3:PCFG0 = 0000 (modo padrão)
    // Nesse modo padrão, os canais AN0 a AN7 são analógicos,
    // e as tensões de referência são Vref+ = VDD e Vref? = VSS
    ADCON1 = 0xC0; //0b11000000;  // 0xC0
   
    
}

uint16_t adc_read(uint8_t canal) {
    // Espera o tempo de aquisição recomendado (~20 µs)
    // pág. 130 manual PIC16F877A
    
    ADCON0bits.CHS = canal;
    //ADCON0 &= 0xC5;
    //ADCON0 |= (canal << 3);
    __delay_us(20);
    
    GO_nDONE = 1;   // Inicia a conversão AD
    
    while(GO_nDONE);    // Espera conversão terminar
    
    return ((uint16_t)(ADRESH << 8) | ADRESL);    // Retorna valor de 10 bits
}
