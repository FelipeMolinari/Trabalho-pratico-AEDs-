#include <stdio.h>
#include <stdlib.h>
#include "lista_passageiros.h"



struct lista_passageiros
{
    passageiros_info* info;
    struct lista_passageiros *prox;
    struct lista_passageiros *ant;
};

lista_passageiros* CriaListaPassageiros()
{
    return NULL;
}



lista_passageiros* InserePassageiroVoo_ord (lista_passageiros* l, passageiros_info* info)// insere passageiro na lista de forma ordenada
{

    lista_passageiros* novo=(lista_passageiros*)malloc(sizeof(lista_passageiros));

    novo->info=info;

    if(lista_vazia(l))
    {
        novo->prox=l;
        novo->ant=NULL;
        return novo;

    }

    lista_passageiros* p=l;
    lista_passageiros* aux=NULL;

    while(p!=NULL  && strcmp(get_nome(p->info), get_nome(info))<0)
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



void imprime_dados_passageiro(lista_passageiros* l)
{
    lista_passageiros* p=l;
    int cont=1;

    while(lista_vazia(p)!=1)
    {
        printf("\n%d - Nome: %s\t",cont,  get_nome(p->info));
        printf("Telefone: %s\t", get_telefone(p->info));
        printf("CPF: %s", get_cpf(p->info));
        p=p->prox;
        cont++;
    }
}

void imprime_dado_no_passageiro(lista_passageiros* l)
{

    printf("\nNome: %s\n",  get_nome(l->info));
    printf("Telefone: %s\n", get_telefone(l->info));
    printf("CPF: %s", get_cpf(l->info));

}




passageiros_info* retira_info_passageiro(lista_passageiros* l, char* cpf)
{
    if(lista_vazia(l))
    {
        return NULL;
    }
    lista_passageiros* p=l;
    while(!lista_vazia(p))
    {
        if(strcmp(get_cpf(p->info),cpf)==0)
        {
            system("pause");
            return p->info;
        }

        p=p->prox;
    }
    return NULL;
}

lista_passageiros* busca_cpf_passageiro(lista_passageiros* l, char* cpf)
{
    lista_passageiros* p=l;
    while(!lista_vazia(p))
    {
        if(strcmp(get_cpf(p->info),cpf)==0)
            return p;
        p=p->prox;
    }
    return NULL;
}

lista_passageiros* remove_passageiro_lista(lista_passageiros* l, char* cpf)
{

    lista_passageiros* p=busca_cpf_passageiro(l, cpf);

    if(lista_vazia(p))
    {
        printf("\n Passageiro com CPF informado nao encontrado\n");
        return l;
    }

    if(p==l)
    {

        l=p->prox;
        if(lista_vazia(p->prox))
        {
            free(p);
            return l;
        }
        l->ant=NULL;
        free(p);
        return l;
    }
    if(p->prox==NULL)
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

int lista_vazia(lista_passageiros* l)
{
    if(l==NULL)

        return 1;

    return 0;
}

int numero_assentos_ocupados(lista_passageiros* l)
{
    lista_passageiros* p=l;
    int assentos_ocupados=0;
    while(!lista_vazia(p))
    {
        assentos_ocupados++;
        p=p->prox;
    }
    return assentos_ocupados;
}

lista_passageiros* get_ant(lista_passageiros* l)
{
    if(lista_vazia(l))
        return NULL;
    return l->ant;

}

void ExcluiListaPassageiros (lista_passageiros* l)
{

    lista_passageiros* p = l;
    lista_passageiros* t;

    while (p != NULL)
    {
        t = p->prox;
        free(p);
        p = t;
    }
}

lista_passageiros* get_prox(lista_passageiros* l)
{
    if(lista_vazia(l))
        return NULL;
    return l->prox;

}

passageiros_info* get_informacao_passageiro(lista_passageiros* l)
{
    if(lista_vazia(l))
        return NULL;
    return l->info;

}


void muda_prox(lista_passageiros* l, lista_passageiros* l_prox)
{
    l->prox=l_prox;
}

void muda_ant(lista_passageiros* l, lista_passageiros* l_ant)
{
    l->ant=l_ant;
}

lista_passageiros* insere_info_no(lista_passageiros* l, passageiros_info* info)
{
    l=(lista_passageiros*)malloc(sizeof(lista_passageiros));
    l->info=info;
    passageiros_info* lol=info;
    return l;
}


void altera_info_passageiro(lista_passageiros* l, passageiros_info* info)
{
    l->info=info;
}
