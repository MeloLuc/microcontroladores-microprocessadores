/*
 * File: teclado_matricial.c
 * Author: Lucas Melo Monteiro
 *
 * Created on 20 de Maio de 2026, 10:53
 */

#include "config.h"
#include "teclado_matricial.h"

char ler_teclado(void) {
    char tecla = 0; // 0 significa nenhuma tecla pressionada no momento

    // Coluna 1
    COL1 = 0; COL2 = 1; COL3 = 1;
    __delay_ms(2); // Para o sinal elétrico estabilizar
    if (ROW1 == 0) tecla = '1';
    if (ROW2 == 0) tecla = '4';
    if (ROW3 == 0) tecla = '7';
    if (ROW4 == 0) tecla = '*';

    // Coluna 2
    COL1 = 1; COL2 = 0; COL3 = 1;
    __delay_ms(2);
    if (ROW1 == 0) tecla = '2';
    if (ROW2 == 0) tecla = '5';
    if (ROW3 == 0) tecla = '8';
    if (ROW4 == 0) tecla = '0';

    // Coluna 3
    COL1 = 1; COL2 = 1; COL3 = 0;
    __delay_ms(2);
    if (ROW1 == 0) tecla = '3';
    if (ROW2 == 0) tecla = '6';
    if (ROW3 == 0) tecla = '9';
    if (ROW4 == 0) tecla = '#';

    COL1 = 1; COL2 = 1; COL3 = 1;

    return tecla;
}
