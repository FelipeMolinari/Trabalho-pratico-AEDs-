#ifndef _lista_voo_H
#define _lista_voo_H

#include "fila_espera_passageiros.h"

typedef struct lista_voo lista_voo;

//Função que cria uma lista de voo
lista_voo* cria_lista_voo();

//Função que insere de forma ordenada um nó de lista de voo, em uma lista de voo
lista_voo* insere_ord_novo_voo(lista_voo* l, int numero_voo, int capacidade, char* horario_partida, char* destino, lista_passageiros* lista, fila_espera_passageiros* fila);

//Função que imprime na tela os dados de um voo passado por parametro
void imprime_dados_listaVOO(lista_voo* l);

//Função que virefica se uma lista de voo esta vazia
int lista_voo_vazia(lista_voo* l);

//funçaõ que retorna o calculo de assentos livres(quantidade de passageiros na lista - a capacidade)
int calcula_assentos_livres(lista_voo* l);

//Função que busca um voo através de um numero de voo;
lista_voo* busca_numero_voo(lista_voo* l, int num_voo);

//função que imprime todos os dados do voo
void imprime_dados_voo(lista_voo* l);

//função que remove o voo da lista de voos
lista_voo* excluir_voo(lista_voo* l, int num_voo);

//Função que altera a capacidade do voo;
void altera_capacidade_voo(lista_voo* l, int capacidade);

//Função que altera o numero do voo
void altera_numero_voo(lista_voo* l, int numero);

//Função que altera o horario do voo
void altera_horario_voo(lista_voo* l, char* horario);

//Função que altera o destino do voo
void altera_destino_voo(lista_voo* l, char* destino);

//Função que altera todos os dados de um determinado voo
void altera_todos_dados_voo(lista_voo* l, int capacidade, int numero, char* horario, char* destino);

//Função que retorna o num do voo de um nó de lista de voo
int get_num_voo(lista_voo* l);

//Função que retorna o horario do voo de um nó de lista de voo
int get_horario_voo(lista_voo* l);

//Função que retorna a capacidade do voo de um nó de lista de voo
int get_capacidade_voo(lista_voo* l);

//Função que retorna o destino do voo de um nó de lista de voo
int get_destino_voo(lista_voo* l);

//Função que retorna q quantidade de assentos livres de um nó de lista de voo
int get_assentos_livres(lista_voo* l);

//Função que retorna a fila de espera de um determinado voo
fila_espera_passageiros* get_fila_espera_VOO(lista_voo* l);

//função que retorna a lista passageiros de um determinado voo
lista_passageiros* get_lista_passageiro_VOO(lista_voo* l);

//função que insere um passageiro na lista de passageiro de um determinado voo
lista_voo* insere_lista_pasVOO(lista_voo* l, passageiros_info* info);

//função que remove um passageiro da lista de passageiro de um determinado voo
lista_voo* retira_pass_listaVOO(lista_voo* l, char* cpf);

//Função que altera a quantidade de assentos disponiveis
void altera_assentos_disponiveis(lista_voo* l, int num_assentos);

//função que imprime os dados do passageiro
void imprime_dados_passageiros_VOO(lista_voo* l);

void ExcluiListaVOO(lista_voo* l);
#endif // _lista_voo_H
