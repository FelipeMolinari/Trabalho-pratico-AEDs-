#ifndef _passageiros_H
#define _passageiros_H


typedef struct passageiros_info passageiros_info;

// funcao que insere as informações de um passageiro na estrutura passageiros_info
passageiros_info* insere_info(char* nome, char* telefone, char* cpf);

 // funcao que retorna o nome do passageiro
char* get_nome(passageiros_info* passageiro);

// função que retorna o telefone do passageiro
char* get_telefone(passageiros_info* passageiro);

// função que retorna o cpf do passageiro
char* get_cpf(passageiros_info* passageiro);

//função que transforma os nomes dos passageiros de minusculo para maiusculo
void transforma_maiusculo(char* nome_passageiro, int i);


#endif // _passageiros_h
