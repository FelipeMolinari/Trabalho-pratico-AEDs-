#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila_espera_passageiros.h"


struct fila_espera_passageiros //FILA CIRCULAR
{

    lista_passageiros* fim;
};

fila_espera_passageiros* cria_fila_espera()
{
    fila_espera_passageiros* f=(fila_espera_passageiros*)malloc(sizeof(fila_espera_passageiros));
    f->fim=NULL;

    return f;
}

fila_espera_passageiros* insere_fila_espera(fila_espera_passageiros* f, passageiros_info* info)
{

    lista_passageiros* novo=CriaListaPassageiros();
    novo=insere_info_no(novo, info);

    if(verifica_fila_vazia(f))
    {
        f->fim=novo;
        muda_prox(novo,novo);
        muda_prox(novo,novo);
    }
    else if(get_prox(f->fim)==f->fim)
    {
        muda_prox(f->fim,novo);
        muda_ant(f->fim,novo);
        muda_ant(novo,f->fim);
        muda_prox(novo,f->fim);
        f->fim=novo;
    }
    else
    {
        muda_ant(get_prox(f->fim), novo);
        muda_prox(novo, get_prox(f->fim));
        muda_prox(f->fim, novo);
        muda_ant(novo, f->fim);
        f->fim=novo;
    }
    return f;
}


void imprime_dados_fila_espera(fila_espera_passageiros* f)//imprime os nomes dos passageiros da fila de espera
{

  lista_passageiros* l=f->fim;

  do
  {
    printf("\n 1. Nome: ");
      puts(get_nome(get_informacao_passageiro(get_prox(l))));
      printf(" 2. CPF: ");
      puts(get_cpf(get_informacao_passageiro(get_prox(l))));
      printf(" 3. Telefone: ");
      puts(get_telefone(get_informacao_passageiro(get_prox(l))));
     // get_informacao_passageiro =função que puxa as informações do passageiro de uma lista.
     //get_prox= funcao que retorna um ponteiro para o prox elemento de uma lista passada por parametro.
     //get_nome=retorna o nome de um passageiro
      l=get_prox(l);
  }while(l!=f->fim);


}


void exclui_fila_passageiros(fila_espera_passageiros* f)
{

    lista_passageiros* l=get_prox(f->fim);

    while(l!=NULL)
    {

        lista_passageiros* aux=get_prox(l);
        free(l);
        l=aux;
    }

    free(f);
}

passageiros_info* get_info_filaespera(fila_espera_passageiros* f)
{
    return get_informacao_passageiro(get_prox(f->fim));
}

passageiros_info* retira_passageiro_fila(fila_espera_passageiros* f)
{

    if(verifica_fila_vazia(f))
    {
        printf("Fila de passageiros está vazia.");
        return NULL;
    }

    if(f->fim==get_prox(f->fim))// PERGUNTAR P/ O ARTHUR SOBRE A OTIMIZAÇÃO DESSA FUNÇÃO:*******************
    {
        passageiros_info* k=get_informacao_passageiro(f->fim);
        lista_passageiros* l= f->fim;
        f->fim=NULL;
        free(l);
        return k;
    }

    lista_passageiros* primeiro=get_prox(f->fim);//******************************** REMOVE CASO F->FIM==GET_PROX(F->FIM)
    lista_passageiros* primeiro_prox= get_prox(primeiro);
    muda_ant(primeiro_prox, f->fim);
    muda_prox(f->fim, primeiro_prox);

    passageiros_info* j=get_informacao_passageiro(primeiro);
    free(primeiro);
    return j;

}

int quantidade_passageiro_fila(fila_espera_passageiros* f)
{
    lista_passageiros* l=f->fim;
    int assentos_ocupados=0;

    if(lista_vazia(l))
    {
        return 0;
    }

    else
    {
        do
        {
            l=get_prox(l);
            assentos_ocupados++;
        }
        while(l!=f->fim);
    }
    return assentos_ocupados;



}

int verifica_fila_vazia(fila_espera_passageiros* f)
{
    if(f->fim==NULL)
        return 1;

    return 0;
}



