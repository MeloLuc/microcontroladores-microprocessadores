/*
 * File:   principal.c
 * Author: Lucas Melo Monteiro
 * Resolução da atividade 5 da matéria de microcontrolador e microprocessador
 * exibir um contador de segundos no formato mm:ss para a placa mcLab2 com pic16f877a
 * contador com limite em 59:59 e botões de start/pause e reset.
 * Created on 6 de Maio de 2026, 14:08
 */

#include "config.h"
#include "display.h"

volatile unsigned char rodando = 1;
volatile unsigned char estouros = 0;

volatile unsigned char digitoRB7 = 0;
volatile unsigned char digitoRB6 = 0;
volatile unsigned char digitoRB5 = 0;
volatile unsigned char digitoRB4 = 0;

void main(void) {
    //FOSC = 4MHZ -> FOSC/4 = 1MHZ -> CM = 1.10^(-6)s 
    
    //Configurando  o T2CON - TIMER2
    //POSTSCALE 1:10
    T2CONbits.TOUTPS3 = 1;
    T2CONbits.TOUTPS2 = 0;
    T2CONbits.TOUTPS1 = 0;
    T2CONbits.TOUTPS0 = 1;
    
    //PRESCALE 1:16
    T2CONbits.T2CKPS1 = 1;
    T2CONbits.T2CKPS0 = 0;
    
    //PR2 = 249 -> (249 + 1)
    PR2 = 0xF9;
    //t=40ms * 25estouros = 1s
    
    //Configurando pinos
    TRISD = 0x00; //00000000
    PORTD = 0x00; //00000000
    
    TRISB = 0x0F; //00001111
    PORTB = 0x00; //00000000
    
    //Registradores realcionados a timer2 interrupção
    PIR1bits.TMR2IF = 0;
    PIE1bits.TMR2IE = 1; //Habilita interrupção do timer2
    INTCONbits.PEIE = 1; //Habilita periféricos
    INTCONbits.GIE = 1;  //Habilita o global    
    
    //timer2 ON
    T2CONbits.TMR2ON = 1;
    
    unsigned char estado_btn_start = 1; //pull-up
    unsigned char estado_btn_reset = 1; //pull-up

    while(1){
       multiplexar_display(digitoRB7, digitoRB6, digitoRB5, digitoRB4);
       
        //START/PAUSE
        // Verifica se o botão foi pressionado (nível lógico 0)
        if (PORTBbits.RB0 == 0) {
            // Só executa se o botão estava solto antes (nível lógico 1)
            if (estado_btn_start == 1) {
                rodando = !rodando;
                estado_btn_start = 0; // Trava para não inverter de novo até soltar
            }
        } else {
            estado_btn_start = 1; // Libera a trava quando o botão é solto
        }


        // RESET
        if (PORTBbits.RB1 == 0) {
            if (estado_btn_reset == 1) {
                //Pausa o relógio também
                rodando = 0; 
                estouros = 0;
                
                // Zera todos os painéis
                digitoRB7 = 0;
                digitoRB6 = 0;
                digitoRB5 = 0;
                digitoRB4 = 0;
                
                estado_btn_reset = 0;
            }
        } else {
            estado_btn_reset = 1;
        }
    }
}

void __interrupt() sdr() {
    if (PIR1bits.TMR2IF == 1) {
        PIR1bits.TMR2IF = 0; //flag
        
        if(rodando == 1){
            estouros++;

            //25 estoruros equivale a 1 segundo
            if(estouros >= 25) {
                estouros = 0;

                //Unidades de segundo (0 a 9)
                digitoRB4++;
                if (digitoRB4 >= 10) {
                    digitoRB4 = 0;

                    //Dezenas de segundo (0 a 5)
                    digitoRB5++;
                    if (digitoRB5 >= 6) {
                        digitoRB5 = 0;

                        //Unidades de minuto (0 a 9)
                        digitoRB6++;
                        if (digitoRB6 >= 10) {
                            digitoRB6 = 0;

                            // Dezenas de minuto (0 a 5)
                            digitoRB7++;
                            if (digitoRB7 >= 6) {
                                digitoRB7 = 0; // Chegou em 59:59, zera tudo
                            }
                        }
                    }
                }
            }
        }
    }

}
