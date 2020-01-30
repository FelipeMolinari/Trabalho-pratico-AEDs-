#ifndef _fila_espera_passageiros_H
#define _fila_espera_passageiros_H
#include "lista_passageiros.h"


typedef struct fila_espera_passageiros fila_espera_passageiros;

//funcao aloca um espaço de memoria de uma fila, faz o ponteiro para o fim da fila apontar pra NULL e retorna a fila.
fila_espera_passageiros* cria_fila_espera();

//funcao que insere em uma fila um nó de uma lista que possui informações de um passageiro, utiliza a logica de fila (FIFO)
fila_espera_passageiros* insere_fila_espera(fila_espera_passageiros* f, passageiros_info* info);

//função que imprime os nomes de uma fila de espera
void imprime_dados_fila_espera(fila_espera_passageiros* f);

//funcao que libera uma fila de espera
void exclui_fila_passageiros(fila_espera_passageiros* f);

//funcao que verifica se uma fila esta vazia
int verifica_fila_vazia(fila_espera_passageiros* f);

//retira o primeiro nó de uma lista retornando as informações do passageiro retirado.
passageiros_info* retira_passageiro_fila(fila_espera_passageiros* f);

passageiros_info* get_info_filaespera(fila_espera_passageiros* f);

#endif // _fila_espera_passageiros_H

