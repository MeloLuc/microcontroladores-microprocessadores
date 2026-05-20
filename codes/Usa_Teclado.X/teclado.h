
#ifndef TECLADO_H
#define	TECLADO_H

// ESTRUTURA DO TECLADO MATRICIAL  4X3
//             C1(RB0)         C2(RB1)       C3(RB2)
//   L1(RD0)     1               2             3
//   L2(RD1)     4               5             6
//   L3(RD2)     7               8             9
//   L4(RD3)     *               0             #


// CONFIGURAÇÃO DE HARDWARE DO TECLADO MATRICIAL
// Pino          Função              Direção
// RD0-RD2    linhas (varredura)     saída
// RB0-RB2    colunas (leitura)      entrada


// Definição de macros para linhas e colunas
#define L1 RD0
#define L2 RD1
#define L3 RD2
#define L4 RD3

// Colunas do teclado 4x3 (entrada)
#define C1 RB0
#define C2 RB1
#define C3 RB2

// Protótipos das funções
ubyte le_tecla(void);
void teclado_config(void);

#endif	

