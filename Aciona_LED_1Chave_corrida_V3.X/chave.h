/**
 * Realiza a leitura da chave com debounce e detecção de borda de descida.
 *
 * A função monitora o estado da chave (ativo em nível baixo) e identifica
 * o evento de pressionamento por meio da detecção de borda de descida
 * (transição de CHAVE_LIBERADA para CHAVE_PRESSIONADA).
 *
 * Internamente, utiliza uma variável estática para armazenar o estado anterior
 * da chave, permitindo a detecção da transição entre leituras sucessivas.
 * Também realiza um pequeno atraso para debounce, garantindo a estabilidade
 * do sinal durante o acionamento e liberação da chave.
 *
 * retorno: bool
 *         - 1: indica que houve um pressionamento válido da chave
 *         - 0: nenhum evento de pressionamento detectado
 */

#ifndef CHAVE_H
#define	CHAVE_H

#include <stdbool.h>

bool chave_pressionada(void);


#define CHAVE_PRESSIONADA   0
#define CHAVE_LIBERADA      1

#define BORDA_DESCIDA(atual, anterior) \
    ((atual == CHAVE_PRESSIONADA) && (anterior == CHAVE_LIBERADA))

#define BORDA_SUBIDA(atual, anterior) \
    ((atual == CHAVE_LIBERADA) && (anterior == CHAVE_PRESSIONADA))


#endif	

