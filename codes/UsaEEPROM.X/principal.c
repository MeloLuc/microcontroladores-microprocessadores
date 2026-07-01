/*
 * File:   principal.c
 * Author: mauro
 *
 * Created on 11 de Novembro de 2025, 20:03
 */

// Protótipos das funções da EEPROM
void salvarSenha(void);
void lerSenha(void);

#include "config.h"
#include "lcd_4bits.h"

// Variáveis globais
char senha[5];

// Macro de endereço base do bloco de senha
#define EEPROM_BASE 0x00


// Função para salvar senha na EEPROM
void salvarSenha(void) {
    lcd_cmd(L_CLR);
    lcd_str("Gravando Senha");
    lcd_cmd(L_L2);
    lcd_str("na EEPROM...");
   

    atraso_ms(2000); // 2s
    
    // Escrita na EEPROM
    // A gravação na EEPROM interna do PIC não é instantânea. 
    // O hardware precisa de alguns milissegundos 
    // para concluir o processo de programação da célula de memória. 
    // Portanto, após cada escrita aguardar 10 ms.
    eeprom_write(EEPROM_BASE, '1');
    //atraso_ms(10); segundo a documentação da Microchip,a função eeprom_write
    // usa o bit WR do registrador EECON1 para verificar se há algum
    // processo de escrita em andamento.

    eeprom_write(EEPROM_BASE+1, '2');
    //atraso_ms(10);

    eeprom_write(EEPROM_BASE+2, '3');
    //atraso_ms(10);

    eeprom_write(EEPROM_BASE+3, '4');
    //atraso_ms(10);

    lcd_cmd(L_CLR);
    lcd_str("Senha Salva...");

    atraso_ms(2000); // 2s
}


// Função para leitura da EEPROM
void lerSenha(void) {
    senha[0] = eeprom_read(0x00);
    senha[1] = eeprom_read(0x01);
    senha[2] = eeprom_read(0x02);
    senha[3] = eeprom_read(0x03);

    senha[4] = '\0';
}


void main(void) {
    TRISD = 0x00; // LCD (RD7 RD6 RD5 RD4)
    TRISE = 0x00; // LCD

    lcd_init();
    lcd_str("Sistema PIC");  
    lcd_cmd(L_L2);
    lcd_str("Placa PICGenios");

    atraso_ms(3000); // 3s

    salvarSenha(); // escrita na eeprom
    atraso_ms(2000);
    
    lcd_cmd(L_L2);
    lcd_str("Lendo EEPROM...");
    lerSenha(); // leitura da eeprom
    atraso_ms(2000);

    lcd_cmd(L_CLR);
    lcd_str("Senha EEPROM");
    lcd_cmd(L_L2);
    lcd_str(senha);

    

    while(TRUE){}
}