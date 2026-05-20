/* 
 * File:  teclado_matricial.h 
 * Author: Lucas de Melo Monteiro Peixoto
 * Comments: Declaração da Macros para as colunas e linhas do teclado matricial
 * da placa PICGenios e da função de leitura do teclado.
 * Revision history: 
 */

#ifndef TECLADO_MATRIX_H
#define	TECLADO_MATRIX_H

#define COL1 PORTBbits.RB0
#define COL2 PORTBbits.RB1
#define COL3 PORTBbits.RB2

#define ROW1 PORTDbits.RD3
#define ROW2 PORTDbits.RD2
#define ROW3 PORTDbits.RD1
#define ROW4 PORTDbits.RD0

char ler_teclado(void);

#include <xc.h>


#endif	/* TECLADO_MATRIX_H */

