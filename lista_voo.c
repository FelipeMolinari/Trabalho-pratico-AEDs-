#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_voo.h"

struct lista_voo
{
    int numero_voo;
    int capacidade;
    int num_assentos_disponiveis;
    char horario_partida[10] ;
    char destino[30];
    struct lista_voo *prox;
    struct lista_voo *ant;

    lista_passageiros* lista_passageiros;
    fila_espera_passageiros* fila_passageiro;

};

lista_voo* cria_lista_voo()
{
    return NULL;
}

lista_voo* insere_ord_novo_voo(lista_voo* l, int numero_voo, int capacidade, char* horario_partida, char* destino, lista_passageiros* lista, fila_espera_passageiros* fila)
{

    lista_voo* novo=(lista_voo*)malloc(sizeof(lista_voo));
    novo->numero_voo=numero_voo;
    novo->capacidade=capacidade;
    novo->num_assentos_disponiveis=capacidade;
    strcpy(novo->horario_partida, horario_partida);
    strcpy(novo->destino, destino);
    novo->lista_passageiros=lista;
    novo->fila_passageiro=fila;

    if(lista_voo_vazia(l))
    {

        novo->prox=l;
        novo->ant=NULL;
        return novo;
    }

    lista_voo* p=l;
    lista_voo* aux=NULL;

    while(!lista_voo_vazia(p) && novo->numero_voo > p->numero_voo)
    {
        aux=p;
        p=p->prox;
    }

    if(p==l)// se primeiro elemento da lista for maior q o novo
    {
        novo->prox=p;
        p->ant=novo;
        novo->ant=NULL;
        return novo;

    }

    if(lista_vazia(p))
    {

        aux->prox=novo;
        novo->ant=aux;
        novo->prox=NULL;
        return l;
    }
    p->ant->prox=novo;
    novo->prox=p;
    novo->ant=p->ant;
    p->ant=novo;
    return l;

}

void imprime_dados_listaVOO(lista_voo* l)
{

    lista_voo* p=l;

    while(!lista_vazia(p))
    {
        printf("\n>. Numero. %d  \t", p->numero_voo);
        printf("Destino -> %s \t", p->destino);
        printf("Horario. %s \t ", p->horario_partida);

        p=p->prox;

    }

}

lista_voo* excluir_voo(lista_voo* l, int num_voo)
{

    lista_voo* p=busca_numero_voo(l, num_voo);

    if(lista_voo_vazia(p))
    {
        printf("Voo com o numero informado não encontrado");
        return NULL;
    }



    if(p==l)
    {


        l=p->prox;
        if(lista_voo_vazia(p->prox))
        {
            free(p);
            return l;
        }

        l->ant=NULL;

        free(p);

        return l;
    }
    if(lista_voo_vazia(p->prox))
    {
        p->ant->prox=NULL;
        free(p);
        return l;
    }
    p->ant->prox=p->prox;
    p->prox->ant=p->ant;
    free(p);
    return l;

}


void imprime_dados_voo(lista_voo* l)
{
    printf("Numero:  %d\n", l->numero_voo);
    printf("Hora:  %s\n", l->horario_partida);
    printf("Destino:  %s\n", l->destino);
    printf("Capacidade:  %d\n", l->capacidade);
    printf("Assentos disponiveis:  %d\n", get_assentos_livres(l));
}
//
void imprime_dados_passageiros_VOO(lista_voo* l)
{
    imprime_dados_passageiro(l->lista_passageiros);

}



int lista_voo_vazia(lista_voo* l)
{
    if(l==NULL)
        return 1;
    return 0;
}

int get_assentos_livres(lista_voo* l)
{
    return l->num_assentos_disponiveis;

}

int calcula_assentos_livres(lista_voo* l)
{
    return (l->capacidade)-(numero_assentos_ocupados(l->lista_passageiros));
}

void altera_assentos_disponiveis(lista_voo* l, int num_assentos)
{
    l->num_assentos_disponiveis=num_assentos;
}

lista_voo* insere_lista_pasVOO(lista_voo* l, passageiros_info* info)
{
    l->lista_passageiros=InserePassageiroVoo_ord(l->lista_passageiros, info);
    l->num_assentos_disponiveis--;

}

lista_voo* retira_pass_listaVOO(lista_voo* l, char* cpf)
{

    l->lista_passageiros=remove_passageiro_lista(l->lista_passageiros, cpf);
    l->num_assentos_disponiveis++;

    return l;
}




lista_passageiros* get_lista_passageiro_VOO(lista_voo* l)
{
        return l->lista_passageiros;
}

fila_espera_passageiros* get_fila_espera_VOO(lista_voo* l)
{
    return l->fila_passageiro;
}


int get_num_voo(lista_voo* l)
{
    return l->numero_voo;

}

int get_capacidade_voo(lista_voo* l)
{
    return l->capacidade;

}

int get_horario_voo(lista_voo* l)
{
    return l->horario_partida;

}

int get_destino_voo(lista_voo* l)
{
    return l->destino;

}



lista_voo* busca_numero_voo(lista_voo* l, int num_voo)
{
    lista_voo* p=l;
    while(!lista_voo_vazia(p))
    {

        if(p->numero_voo == num_voo)
        {
            return p;
        }
        p=p->prox;
    }
    return NULL;
}

void altera_destino_voo(lista_voo* l, char* destino)
{
    strcpy(l->destino, destino);
}

void altera_horario_voo(lista_voo* l, char* horario)
{
    strcpy(l->horario_partida, horario);
}

void altera_numero_voo(lista_voo* l, int numero)
{
    l->numero_voo=numero;
}

void altera_capacidade_voo(lista_voo* l, int capacidade)
{
    l->capacidade=capacidade;
}


void altera_todos_dados_voo(lista_voo* l, int capacidade, int numero, char* horario, char* destino)
{
    l->capacidade=capacidade;
    l->numero_voo=numero;
    strcpy(l->horario_partida, horario);
    strcpy(l->destino, destino);
}

void ExcluiListaVOO(lista_voo* l)
{

    lista_voo* p = l;
    lista_voo* t;

    while (p != NULL)
    {
        t = p->prox;
        free(p);
        p = t;
    }
}
