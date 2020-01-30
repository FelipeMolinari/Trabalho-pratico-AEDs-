#ifndef _lista_passageiros_H
#define _lista_passageiros_H
#include "passageiros.h"

typedef struct lista_passageiros lista_passageiros;

// função que libera uma lista de passageiro
void ExcluiListaPassageiros (lista_passageiros* l);

// função que cria uma lista de passageiro
lista_passageiros* CriaListaPassageiros();

//fucão que insere em uma lista de passageiro um novo passageiro com informações info
lista_passageiros* InserePassageiroVoo_ord (lista_passageiros* l, passageiros_info* info);

//função que verifica se a lista esta vazia
int lista_vazia(lista_passageiros* l);

//função que imprime os nomes de uma lista de passageiros
void imprime_nomes_passageiros(lista_passageiros* l);

//função que calcula a quantidade de nós que possui uma lista de passageiros
int numero_assentos_ocupados(lista_passageiros* l);

//funcao que retorna o proximo nó da lista ou sublista passada por parametro
lista_passageiros* get_prox(lista_passageiros* l);

//funcao que retorna o nó anterior da lista ou sublista passada por parametro
lista_passageiros* get_ant(lista_passageiros* l);

//funcao que retorna as informações de um passageiro.. usada na função (imprime_fila_espera)
passageiros_info* get_informacao_passageiro(lista_passageiros* l);

//função que retira as informações de um determinado passageiro(RETORNA NULL SE NAO ENCONTRAR PASSAGEIRO OU SE A LISTA FOR VAZIA)
passageiros_info* retira_info_passageiro(lista_passageiros* l, char* cpf);

//função que remove o passageiro que possui o CPF passado por parametro;
lista_passageiros* remove_passageiro_lista(lista_passageiros* l, char* cpf);

//função que busca um cpf em uma lista e retorna o nó de lista do passageiro que possui o CPF passado por parametro
lista_passageiros* busca_cpf_passageiro(lista_passageiros* l, char* cpf);

//muda para (l_prox) o proximo nó de uma lista (l)
void muda_prox(lista_passageiros* l, lista_passageiros* l_prox);

//muda para (l_ant) o nó anterior de uma lista (l)
void muda_ant(lista_passageiros* l, lista_passageiros* l_ant);

void imprime_dados_passageiro(lista_passageiros* l);

void imprime_dado_no_passageiro(lista_passageiros* l);

void altera_info_passageiro(lista_passageiros* l, passageiros_info* info);

void ExcluiListaPassageiros (lista_passageiros* l);

#endif // _lista_passageiros_H
