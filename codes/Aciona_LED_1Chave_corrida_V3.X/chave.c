/**
 * A função realiza a leitura da chave com debounce e detecção de borda.
 *
 * Esta função implementa a leitura de uma chave mecânica considerando
 * os efeitos de bounce (repique), utilizando um pequeno atraso para
 * estabilização do sinal.
 *
 * O algoritmo realiza:
 * - Leitura do estado atual da chave
 * - Comparação com o estado anterior (armazenado em variável estática)
 * - Detecção de borda de descida (transição 1 -> 0), caracterizando
 *   o pressionamento da chave
 * - Confirmação do estado após debounce
 * - Atualização do estado anterior
 *
 * A chave é considerada ativa em nível baixo (lógica invertida):
 * - CHAVE_PRESSIONADA = 0
 * - CHAVE_LIBERADA   = 1
 *
 * A detecção da borda de subida (liberação) é utilizada apenas para
 * atualização do estado interno e não gera evento de retorno.
 *
 * retorno: unsigned char
 *         - 1: pressionamento válido detectado (borda de descida)
 *         - 0: nenhum evento detectado
 *
 * OBS: A função utiliza atraso bloqueante (__delay_ms), o que pode
 *       impactar aplicações com requisitos de tempo real mais rigorosos.
 *       Para aplicações mais complexas, recomenda-se o uso de debounce
 *       não bloqueante baseado em temporizadores.
 */


#include "chave.h"
#include "config.h"

// Função para leitura da chave com debounce e detecção de borda de descida
bool chave_pressionada(void) {
    static bool estado_anterior = CHAVE_LIBERADA; // mantém valor entre chamadas
    bool estado_atual;
    
    estado_atual = CHAVE_ON_OFF;
    
    // detecção da borda de descida
    if (BORDA_DESCIDA(estado_atual, estado_anterior)) {
        __delay_ms(1); // debounce
        
        // confirma pressionamento
        if (CHAVE_ON_OFF == CHAVE_PRESSIONADA) {
            estado_anterior = CHAVE_PRESSIONADA;
            return 1; // evento de pressionamento válido
        }
    }
    
    // detecção da borda de subida (apenas para atualizar estado)
    if (BORDA_SUBIDA(estado_atual, estado_anterior)) {
        __delay_ms(1); // debounce
        estado_anterior = CHAVE_LIBERADA;
        return 0;
    }
    
    estado_anterior = estado_atual;
    return 0;
}