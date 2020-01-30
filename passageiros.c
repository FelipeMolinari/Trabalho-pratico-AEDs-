#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "passageiros.h"


struct passageiros_info
{
    char nome[75];
    char telefone[15];
    char cpf[12];
};

passageiros_info* insere_info(char* nome, char* telefone, char* cpf)
{
    passageiros_info* novo=(passageiros_info*)malloc(sizeof(passageiros_info));
    strcpy(novo->nome, nome);
    strcpy(novo->telefone, telefone);
    strcpy(novo->cpf, cpf);

    return novo;
}

void transforma_maiusculo(char* nome_passageiro, int i)
{

    if(nome_passageiro[i]!='\0')
    {
        if(nome_passageiro[i]>='A' && nome_passageiro[i]<='Z')//Se a letra for maiúscula...
             transforma_maiusculo(nome_passageiro, i+1);

        else if(nome_passageiro[i]>='a' && nome_passageiro[i]<='z')
        {
            nome_passageiro[i]=nome_passageiro[i]-32;
            transforma_maiusculo(nome_passageiro, i+1);
        }
        else if(nome_passageiro[i]==' ')
        {
            transforma_maiusculo(nome_passageiro, i+1);
        }

    }

}

char* get_nome(passageiros_info* passageiro)
{
    return passageiro->nome;
}

char* get_telefone(passageiros_info* passageiro)
{
    return passageiro->telefone;
}

char* get_cpf(passageiros_info* passageiro)
{
    return passageiro->cpf;
}
