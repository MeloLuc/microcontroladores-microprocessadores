
#include "config.h"
#include "teclado.h"

// Mapeamento das chaves para caracteres
ubyte teclas[4][3] = {
   //[0]   [1] [2]
   // C1   C2   C3
    {'1', '2', '3'}, // L1  [0]
    {'4', '5', '6'}, // L2  [1]
    {'7', '8', '9'}, // L3  [2]
    {'*', '0', '#'}  // L4  [3]
};


ubyte le_tecla(void) {
    ubyte linha;
    ubyte colunas_ativas;

    for (linha = 0; linha < 4; linha++) {

        // Desabilita todas as linhas
        L1 = L2 = L3 = L4 = 1;

        // Ativa somente a linha atual
        switch (linha) {
            case 0: L1 = 0; break;
            case 1: L2 = 0; break;
            case 2: L3 = 0; break;
            case 3: L4 = 0; break;
        }

        __delay_us(50);   // tempo de acomodação (mais rápido que 5 ms)
                          // aguardando atrasos de propagação

        // Conta quantas colunas estão ativas
        // Se nenhuma tecla for pressionada: C1=1, C2=1, C3=1
        colunas_ativas = (!C1) + (!C2) + (!C3);

        if (colunas_ativas > 1) {
            return '\0';   // múltiplas teclas pressionadas
        }

        if (colunas_ativas == 1) {
            __delay_ms(20);   // debounce somente quando detecta tecla

            // Confirma leitura após debounce
            if (!C1) return teclas[linha][0];
            if (!C2) return teclas[linha][1];
            if (!C3) return teclas[linha][2];
        }
    }

    return '\0';  // nenhuma tecla pressionada
}


void teclado_config(void) {
    TRISD = 0x00;  // os pinos mais baixo da porta como saída (0b0000 0000) - linhas
    TRISB = 0x07;  // 0b0000 0111 - 3 pinos mais baixo como entrada - colunas.
}
