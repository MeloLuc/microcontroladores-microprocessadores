/*
 * File:   principal.c
 * Author: mauro
 *
 * Created on 27 de Maio de 2025, 20:56
 */


#include "config.h"
#include "lcd.h"
#include "float_str.h"

int contador = 0; 

// Variáveis de estado para as chaves (Assumindo pull-up: 1 = solto, 0 = pressionado)
unsigned char estado_b0 = 1; 
unsigned char estado_b1 = 1;
unsigned char estado_b2 = 1;

// Flag para evitar que o LCD fique piscando (flicker). Só atualiza quando o número muda.
unsigned char atualiza_display = 1;

// Função dedicada à leitura com Debounce em pressionamento e soltura
void ler_botoes() {
    
    // --- CHAVE 1 (RB0): Incrementar ---
    if (PORTBbits.RB0 == 0) {
        if (estado_b0 == 1) { // Detecta borda de descida (acabou de apertar)
            __delay_ms(20); // Debounce de pressionamento
            if (PORTBbits.RB0 == 0) { // Confirma
                if (contador < 9999) { // Limita o valor máximo em 9999
                    contador++;
                    atualiza_display = 1;
                }
                estado_b0 = 0; // Trava o botão como pressionado
            }
        }
    } else {
        if (estado_b0 == 0) { // Detecta borda de subida (acabou de soltar)
            __delay_ms(20); // Debounce de soltura
            if (PORTBbits.RB0 == 1) { // Confirma soltura
                estado_b0 = 1; // Libera a trava do botão
            }
        }
    }

    // --- CHAVE 2 (RB1): Decrementar ---
    if (PORTBbits.RB1 == 0) {
        if (estado_b1 == 1) {
            __delay_ms(20); 
            if (PORTBbits.RB1 == 0) {
                if (contador > 0) { // Previne o estouro negativo (limite 0)
                    contador--;
                    atualiza_display = 1;
                }
                estado_b1 = 0; 
            }
        }
    } else {
        if (estado_b1 == 0) {
            __delay_ms(20); 
            if (PORTBbits.RB1 == 1) {
                estado_b1 = 1; 
            }
        }
    }

    // --- CHAVE 3 (RB2): Zerar ---
    if (PORTBbits.RB2 == 0) {
        if (estado_b2 == 1) {
            __delay_ms(20); 
            if (PORTBbits.RB2 == 0) {
                if (contador != 0) { // Só zera e atualiza se já não for zero
                    contador = 0;
                    atualiza_display = 1;
                }
                estado_b2 = 0; 
            }
        }
    } else {
        if (estado_b2 == 0) {
            __delay_ms(20); 
            if (PORTBbits.RB2 == 1) {
                estado_b2 = 1; 
            }
        }
    }
}

int main(void) {
    // Configuração das portas conectadas ao LCD (conforme sua biblioteca)
    TRISD = 0x00; 
    TRISE = 0x00; 
    
    // Configuração de Entradas para as 3 Chaves [cite: 10]
    TRISBbits.TRISB0 = 1; // Chave 1: Incrementa [cite: 11]
    TRISBbits.TRISB1 = 1; // Chave 2: Decrementa [cite: 12]
    TRISBbits.TRISB2 = 1; // Chave 3: Zera [cite: 13]
    
    // Inicialização do LCD
    lcd_init();
    lcd_cmd(L_NCR); // Desliga cursor
    
    // Impressão da linha estática [cite: 15]
    lcd_cmd(L_L1);
    print_lcd("Contador:");
    
    char str[16]; 
    
    while (TRUE) {
        // Faz a leitura contínua com tratamento de debouncing
        ler_botoes(); 
        
        // Atualiza a linha 2 em tempo real [cite: 16] apenas se o valor mudou
        if (atualiza_display == 1) {
            lcd_cmd(L_L2);
            print_lcd("                "); // Limpa a linha 2 enviando espaços
            lcd_cmd(L_L2);                 // Retorna o cursor ao início da linha 2
            
            // Converte o contador (inteiro) para formato string usando sua função de float.
            // Obs: A função float_str do seu projeto adicionará vírgula e zeros (ex: 5,00).
            float_str((float)contador, str);
            print_lcd(str);
            
            atualiza_display = 0; // Desce a flag de atualização
        }
        
        // Delay minúsculo para o ciclo não "engasgar" a simulação
        __delay_ms(1);  
    }
}

