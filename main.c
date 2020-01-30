#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "passageiros.h"
#include "lista_passageiros.h"
#include "fila_espera_passageiros.h"
#include "lista_voo.h"

int num_voo, capacidade_voo, i=0, contador=0;
char destino_voo[20], hora_partida[10], nome_passageiro[75], telefone_passageiro[15], cpf_passageiro[12];
lista_voo* Lista_voo, * Lista_voo_no;
lista_passageiros *Lista_passageiro, *Lista_passageiro_no;
fila_espera_passageiros* Fila_espera_passageiro;
passageiros_info* info_passageiro;

int op, op2;

int main()
{
    printf("\tUniversidade Federal de Ouro Preto - UFOP\n\tDepartamento de Ciencias Exatas e Aplicadas\n\t\tCampus Joao Monnlevade");
    printf("\n\n\n\t\t Trabalho Pratico\n");
    printf("\nProf. Arthur de Assis Silva");
    printf("\nAlunos:\nNome: Felipe Cardoso Lima Molinari\tMatricula:15.1.8102\nNome: Ricardo Matias Silvino\tMatricula:14.1.8205\n\n");
    system("pause");
    system("cls");
    Lista_voo= cria_lista_voo();
    menu();
    return 0;
}

int menu(void)
{
    setlocale(LC_ALL, "Portuguese");
    printf("\t\tSISTEMA DE CONTROLE DO AEROPORTO\n\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("Escolha um item:\n");
    printf("\n1. Criar voo\n");
    printf("2. Acessar voo\n");
    printf("3. SAIR\n\n");
    printf("--------------------------------------------------------------------------------\n");
    fflush(stdin);
    printf("Opcao:  ");
    scanf("%d", &op);

    system("cls");
    opcao (op);

    return op;
}

void opcao(int op)
{
    switch(op)
    {

//CRIA UM NOVO VOO
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    case 1:
        fflush(stdin);
        printf("CRIANDO NOVO VOO...\n\n");
        printf("--------------------------------------------------------------------------------\n");
        printf("Insira o numero do voo: ");
        scanf("%d", &num_voo);

        while(!lista_voo_vazia(busca_numero_voo(Lista_voo, num_voo)))// Verifica se já possui algum voo com o num de voo inserido
        {
            system("cls");

            printf("--------------------------------------------------------------------------------\n");
            printf(".............     O numero do voo inserido já existe!     .............\n");
            printf("--------------------------------------------------------------------------------\n");
            printf("Aperte ENTER para inserir um novo numero");
            fflush(stdin);
            getchar();
            system("cls");
            printf("CRIANDO NOVO VOO...\n\n");
            printf("--------------------------------------------------------------------------------\n");
            printf("Insira o numero do voo: ");
            scanf("%d", &num_voo);
        }

        fflush(stdin);
        printf("\nInsira o destino do voo: ");
        gets(destino_voo);
        fflush(stdin);
        printf("\nInsira a hora do voo: ");
        gets(hora_partida);
        fflush(stdin);
        printf("\nInsira a capacidade do aviao: ");
        scanf("%d", &capacidade_voo);
        if(capacidade_voo<0)
        {
            do
            {
                system("cls");
                printf("--------------------------------------------------------------------------------\n");
                printf("A capacidade não pode ser negativa, digite um numero maior que 0\n");
                printf("--------------------------------------------------------------------------------\n");
                printf("Capacidade: ");
                scanf("%d", &capacidade_voo);
            }while(capacidade_voo<0);
        }
        printf("--------------------------------------------------------------------------------\n");

        Lista_passageiro= CriaListaPassageiros(); //cria a lista de passageiro do voo
        Fila_espera_passageiro= cria_fila_espera();//cria a fila de espera do voo

        Lista_voo=insere_ord_novo_voo(Lista_voo, num_voo, capacidade_voo, hora_partida, destino_voo, Lista_passageiro, Fila_espera_passageiro);
        printf("\n\t...Voo criado com sucesso...\n");// insere de forma ordenada o novo voo na lsita de voo
        fflush(stdin);
        getchar();
        system("cls");
        menu();
        break;

//ACESSA UM VOO DETERMINADO PELO NUMERO DO VOO
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    case 2:
        printf("\t\t.....RELAÇÃO DE VOOS CADASTRADOS.....\n");
        printf("--------------------------------------------------------------------------------\n");
        if(lista_voo_vazia(Lista_voo))//Verifica se a lista de voo está vazia
        {
            fflush(stdin);
            printf(".............     Não existe voo cadastrado     ...........\n\n");
            printf("--------------------------------------------------------------------------------\n");
            printf("Para continuar aperte ENTER...");
            getchar();
            system("cls");
            menu();
        }

        imprime_dados_listaVOO(Lista_voo);//Imprime os dados do voo na tela
        printf("\n\n--------------------------------------------------------------------------------");
        fflush(stdin);
        printf("\nDigite o numero do voo desejado: ");
        scanf("%d", &num_voo);//Recebe o numero do voo que o usuario deseja acessar
        Lista_voo_no=busca_numero_voo(Lista_voo, num_voo);//busca o voo com o num inserido, retorna NULL se o voo nao for encontrado

        if(lista_voo_vazia(Lista_voo_no))//Verifica se o nó de lista é NULL
        {
            printf("\n\n--------------------------------------------------------------------------------");
            printf("\n.............     Não possui nenhum voo com o numero inserido     .............\n");
            printf("--------------------------------------------------------------------------------");


            fflush(stdin);
            getchar();
            system("cls");
            menu();

        }
        //Voo encontrado
        fflush(stdin);
        printf("Acessando o menu do voo...");
        getchar();
        system("cls");
        menu_voo(Lista_voo_no);//Chama a função do menu de um voo com o numero iserido
        break;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    case 3:// Opção para abordar o programa


        fflush(stdin);
        printf("--------------------------------------------------------------------------------\n");
        printf("Lista de passageiro, fila de espera e Voo foram liberados");
        ExcluiListaPassageiros (Lista_passageiro);
        ExcluiListaVOO(Lista_voo);
        printf("\n--------------------------------------------------------------------------------\n");
        printf("\n\nVolte sempre!!");
        getchar();
        system("cls");
        exit(0);
        break;

//O COMANDO INSERIDO É INVALIDO
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    default:
        printf("\n--------------------------------------------------------------------------------");
        printf("\n!!!COMANDO INVÁLIDO!!!\n\n");
        printf("--------------------------------------------------------------------------------");
        fflush(stdin);
        getchar();
        system("cls");
        menu();//RETORNA PARA O MENU
    }
}
//MENU DO VOO
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void menu_voo(lista_voo* Lista_voo_no)
{
    do
    {
        printf("\t\t.....MENU DO VOO %d.....\n", get_num_voo(Lista_voo_no));
        printf("--------------------------------------------------------------------------------");
        printf("\n1. Verifica dados do voo\n");
        printf("2. Excluir voo\n");
        printf("3. Altera dados do voo\n");
        printf("4. Inserir novo passageiro\n");
        printf("5. Excluir lista de passageiros\n");
        printf("6. Excluir fila de espera\n");
        printf("7. Imprimir fila de espera\n");
        printf("8. Acessar informações de um passageiro\n");
        printf("9. Voltar\n");
        printf("--------------------------------------------------------------------------------\n");
        fflush(stdin);
        printf("Opcao:  ");
        scanf("%d", &op2);//escolhe o comando
        system("cls");

        switch(op2)
        {

//VERIFICA OS DADOS DO VOO
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case 1:
            do
            {
                system("cls");
                printf ("\t\t.....DADOS DO VOO.....\n");
                printf("--------------------------------------------------------------------------------\n");
                imprime_dados_voo(Lista_voo_no);//Imprime os dados de um voo
                printf("\n--------------------------------------------------------------------------------\n");

                printf("\n\n--------------------------------------------------------------------------------\n");
                printf("Deseja voltar no menu do voo? ");
                printf("\n1: SIM");
                printf("\n2: NÃO\n");
                printf("\n--------------------------------------------------------------------------------\n");
                fflush(stdin);
                printf("Opcao:  ");
                scanf("%d", &op);
                system("cls");

                if(op==1)//Opção para voltar pro menu do voo
                {
                    printf("\n--------------------------------------------------------------------------------\n");
                    printf(".............     Voltando para o menu do voo     .............");
                    printf("\n--------------------------------------------------------------------------------\n");
                    printf("\n Aperte ENTER para continuar");
                    fflush(stdin);
                    getchar();
                    system("cls");
                    menu_voo(Lista_voo_no);
                }
                if(op==2)//opção para voltar no menu principal
                {
                    printf("--------------------------------------------------------------------------------\n");
                    printf(".............     Voltando para o menu de controle     .............");
                    printf("\n--------------------------------------------------------------------------------\n");
                    printf("\n Aperte ENTER para continuar");
                    fflush(stdin);
                    getchar();
                    system("cls");
                    menu();
                }
            }
            while(op>1 || op>2);// enquanto o usuario digitar uma opção inválida
            break;

//EXCLUI UM VOO
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case 2:
            do
            {
                system("cls");
                printf ("\t\t.....EXCLUIR O VOO DE NUMERO %d.....\n", get_num_voo(Lista_voo_no));
                printf("--------------------------------------------------------------------------------\n");
                printf("Tem certeza que deseja excluir o voo?");
                printf("\n\nDigite 1 para EXCLUIR o voo ou 2 para VOLTAR para o menu do voo:");
                printf("\n 1: SIM");
                printf("\n 2: NÃO\n");
                printf("\n--------------------------------------------------------------------------------\n");
                fflush(stdin);
                printf("Opção:  ");
                scanf("%d", &op);//VERIFICA SE O USUARIO QUER REALMENTE EXCLUIR O VOO
                system("cls");
                switch(op)
                {
                case 1://USUARIO QUER EXCLUIR O VOO

                    printf ("\t\t.....EXCLUIR O VOO DE NUMERO %d.....\n", get_num_voo(Lista_voo_no));
                    //REMOVE A LISTA DE PASSAGEIRO DO VOO PRIMEIRO
                    while(!lista_vazia(get_lista_passageiro_VOO(Lista_voo_no)))
                    {
                        //ENQUANTO A LISTA NÃO ESTIVER VAZIA

                        retira_pass_listaVOO(Lista_voo_no, get_cpf(get_informacao_passageiro(get_lista_passageiro_VOO(Lista_voo_no))));

                    }

                    while(!verifica_fila_vazia(get_fila_espera_VOO(Lista_voo_no)))
                    {//REMOVE A FILA DE ESPERA DO VOO PRIMEIRO
                        //REMOVE TODOS OS PASSAGEIROS DA FILA
                        retira_passageiro_fila(get_fila_espera_VOO(Lista_voo_no));

                    }

                    Lista_voo=excluir_voo(Lista_voo, get_num_voo(Lista_voo_no));//FUNÇÃO RETORNA A LISTA DE VOO, SEM O VOO REMOVIDO
                    printf("\n--------------------------------------------------------------------------------\n");
                    printf(".............     Voo excluido com sucesso!!!!     .............");
                    printf("\n--------------------------------------------------------------------------------\n");
                    printf("Aperte ENTER para voltar ao menu de controle");
                    fflush(stdin);
                    getchar();
                    system("cls");
                    menu();
                    break;


                case 2://USUARIO NÃO QUER REMOVE O VOO
                    printf ("\t\t.....EXCLUIR O VOO DE NUMERO %d.....\n", get_num_voo(Lista_voo_no));
                    printf("\n--------------------------------------------------------------------------------\n");
                    printf(".............     Voo Não foi excluido!!!!     .............");
                    printf("\n--------------------------------------------------------------------------------\n");
                    printf("\nAperte ENTER para voltar ao menu do voo");
                    fflush(stdin);
                    getchar();
                    menu_voo(Lista_voo_no);
                    system("cls");
                    break;



                default://USUARIO NÃO DIGITOU UMA OPçÃO VALIDA


                    system("cls");
                    printf("\n--------------------------------------------------------------------------------\n");
                    printf("\t!!!COMANDO INVALIDO!!!\n");
                    printf("\n--------------------------------------------------------------------------------\n");
                    printf("Aperte ENTER para continuar");
                    fflush(stdin);
                    getchar();
                    break;
                }


            }
            while(op<1 || op>2);// enquanto o usuario digitar uma opção inválida
            break;

//ALTERA OS DADOS DO VOO
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case 3:
            do
            {
                printf("\t\t....ALTERAÇÃO DE DADOS DO VOO.....\n");
                printf("--------------------------------------------------------------------------------\n");
                printf("Escolha a opção que deseja alterar: \n");
                printf("1: Numero do voo\n");
                printf("2: Hora de partida do voo\n");
                printf("3: Destino do voo\n");
                printf("4: Capacidade do aviao\n");
                printf("5: TODOS\n");
                fflush(stdin);
                printf("\n--------------------------------------------------------------------------------\n");
                printf("Opção:  ");//USUARIO DECIDE OQUE QUER ALTERAR NO VOO
                scanf("%d", &op);

                switch(op)
                {
                //ALTERA O NUMERO DO VOO
                case 1:
                    system("cls");
                    printf("\t\t....ALTERA NUMERO DO VOO.....\n");
                    printf("\n--------------------------------------------------------------------------------\n");
                    printf("\n\Numero atual do voo:  %d", get_num_voo(Lista_voo_no));
                    fflush(stdin);
                    printf("\nInsira o novo numero do voo:  ");
                    scanf("%d", &num_voo);
                    printf("\n--------------------------------------------------------------------------------\n");
                    while(!lista_voo_vazia(busca_numero_voo(Lista_voo, num_voo)))//enquanto o usuario digitar um numero que um outro voo já possui
                    {


                        printf("\n\n--------------------------------------------------------------------------------\n");
                        printf(".............     O numero do voo inserido já existe!     .............\n");
                        printf("--------------------------------------------------------------------------------\n");
                        printf("Aperte ENTER para inserir um novo numero");
                        fflush(stdin);
                        getchar();
                        system("cls");
                        printf("\t\t....ALTERA NUMERO DO VOO.....\n");
                        printf("\n--------------------------------------------------------------------------------\n");
                        printf("\n\Numero atual do voo:  %d", get_num_voo(Lista_voo_no));
                        printf("\nInsira o novo numero do voo: ");
                        scanf("%d", &num_voo);
                    }
                    altera_numero_voo(Lista_voo_no, num_voo);//Altera o numero do voo
                    printf("\n.............     Dado alterado com sucesso     .............\n");
                    break;


                case 2://ALTERA O HORARIO DE PARTIDA DE UM VOO

                    system("cls");
                    printf("\t\t....ALTERA HORARIO DE PARTIDA DO VOO.....\n");
                    printf("\n--------------------------------------------------------------------------------\n");
                    fflush(stdin);
                    printf("\n\Horario atual do voo:  %s", get_horario_voo(Lista_voo_no));
                    printf("\nDigite o novo horario de partida do voo:  ");
                    gets(hora_partida);
                    printf("\n--------------------------------------------------------------------------------\n");
                    altera_horario_voo(Lista_voo_no, hora_partida);//ALTERA O HORARIO
                    printf("\n\t.............     Dado alterado com sucesso     .............\n");
                    break;

                case 3://ALTERA O DESTINO DE UM VOO

                    system("cls");
                    printf("\t\t....ALTERA DESTINO DO VOO.....\n");
                    printf("\n--------------------------------------------------------------------------------\n");
                    fflush(stdin);
                    printf("\n\Destino atual do voo:  %s", get_destino_voo(Lista_voo_no));
                    printf("\nDigite o novo destino do voo:  ");
                    gets(destino_voo);
                    printf("\n--------------------------------------------------------------------------------\n");
                    altera_destino_voo(Lista_voo_no,destino_voo);//ALTERA O DESTINO DE UM VOO
                    printf("\n.............     Dado alterado com sucesso     .............\n");
                    break;

                case 4://ALTERA A CAPACIDADE DE UM VOO

                    system("cls");
                    printf("\t\t....ALTERA CAPACIDADE DO VOO.....\n");
                    printf("\n--------------------------------------------------------------------------------\n");
                    fflush(stdin);
                    printf("\n\Capacidade atual do voo:  %d", get_capacidade_voo(Lista_voo_no));
                    printf("\nDigite a nova capacidade do voo:  ");
                    scanf("%d", &capacidade_voo);
                    printf("\n--------------------------------------------------------------------------------\n");
                    if(capacidade_voo<numero_assentos_ocupados(get_lista_passageiro_VOO(Lista_voo_no)))
                    {
                        //IF QUE VERIFICA SE O USUARIO ESTA INSERINDO UMA CAPACIDADE MENOR QUE O NUMERO DE ASSENTOS OCUPADOS..
                        printf("\nCAPACIDADE NÃO ALTERADA");
                        printf("\n\t\t\tMOTIVO:");
                        printf("\n--------------------------------------------------------------------------------\n");
                        printf("O voo possui %d passageiros, logo, nova capacidade não pode ser menor que\na quantidade de passageiros."
                               ,numero_assentos_ocupados(get_lista_passageiro_VOO(Lista_voo_no)));
                        printf("\n--------------------------------------------------------------------------------\n");
                    }
                    else
                    {
                        printf("\n--------------------------------------------------------------------------------\n");
                        altera_capacidade_voo(Lista_voo_no,capacidade_voo);//ALTERA A CAPACIDADE DO VOO
                        altera_assentos_disponiveis(Lista_voo_no, calcula_assentos_livres(Lista_voo_no));//ALTERA A QUANTIDADE DE ASSENTOS DISPONIVEIS
                        printf(".............     Dado alterado com sucesso!     .............");
                        printf("\n--------------------------------------------------------------------------------\n");
                    }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    break;

                case 5://ALTERA TODOS OS DADOS DO VOO
                    system("cls");
                    printf("\t\t....ALTERA TODOS DADOS DO VOO.....\n");
                    printf("\n--------------------------------------------------------------------------------\n");

                    printf("\nNumero atual do voo:  %d", get_num_voo(Lista_voo_no));
                    fflush(stdin);
                    printf("\nDigite o novo numero do voo: ");
                    scanf("%d", &num_voo);
                    while(!lista_voo_vazia(busca_numero_voo(Lista_voo, num_voo)))//VERIFICA SE ALGUM VOO JA POSSUI O NUMERO INSERIDO
                    {


                        printf("\n\n--------------------------------------------------------------------------------\n");
                        printf(".............     O numero do voo inserido já existe!     .............\n");
                        printf("--------------------------------------------------------------------------------\n");
                        printf("Aperte ENTER para inserir um novo numero");
                        fflush(stdin);
                        getchar();
                        system("cls");
                        printf("\t\t....ALTERA TODOS DADOS DO VOO.....\n");
                        printf("\n--------------------------------------------------------------------------------\n");
                        printf("\n\Numero atual do voo:  %d", get_num_voo(Lista_voo_no));
                        printf("\nInsira o novo numero do voo: ");
                        scanf("%d", &num_voo);
                    }

                    altera_numero_voo(Lista_voo_no, num_voo);

                    //ALTERA O HORARIO DO VOO
                    printf("\n\Horario atual do voo:  %s", get_horario_voo(Lista_voo_no));
                    fflush(stdin);
                    printf("\nDigite o novo horario de partida do voo: ");
                    gets(hora_partida);
                    altera_horario_voo(Lista_voo_no,hora_partida);

                    //ALTERA O HORARIO DO VOO
                    printf("\nDestino atual voo atual:  %s", get_destino_voo(Lista_voo_no));
                    fflush(stdin);
                    printf("\nDigite o novo destino do voo: ");
                    gets(destino_voo);
                    altera_destino_voo(Lista_voo_no,destino_voo);

                    //ALTERA O CAPACIDADE DO VOO
                    printf("\n\Capacidade atual do voo:  %d", get_capacidade_voo(Lista_voo_no));
                    fflush(stdin);
                    printf("\nDigite a nova capacidade do voo: ");
                    scanf("%d", &capacidade_voo);
                    printf("\n--------------------------------------------------------------------------------\n");

                    if(capacidade_voo<numero_assentos_ocupados(get_lista_passageiro_VOO(Lista_voo_no)))
                    {
                        //IF QUE VERIFICA SE O USUARIO ESTA INSERINDO UMA CAPACIDADE MENOR QUE O NUMERO DE ASSENTOS OCUPADOS..
                        system("cls");
                        printf("\nCAPACIDADE NÃO ALTERADA");
                        printf("\n\t\t\tMOTIVO:");
                        printf("\n--------------------------------------------------------------------------------\n");
                        printf("O voo possui %d passageiros, logo, nova capacidade não pode ser menor que\na quantidade de passageiros."
                               ,numero_assentos_ocupados(get_lista_passageiro_VOO(Lista_voo_no)));
                        printf("\n--------------------------------------------------------------------------------\n");
                    }
                    else
                    {

                        altera_capacidade_voo(Lista_voo_no,capacidade_voo);
                        altera_assentos_disponiveis(Lista_voo_no, calcula_assentos_livres(Lista_voo_no));

                        printf("\n--------------------------------------------------------------------------------\n");
                        printf(".............      Dados alterados com sucesso!      .............");
                        printf("\n--------------------------------------------------------------------------------\n");
                        break;

                    }
                    break;


                default://USUARIO DIGITOU UMA OPÇÃO INVALIDA
                    system("cls");
                    printf("\n--------------------------------------------------------------------------------\n");
                    printf("\t!!!COMANDO INVALIDO!!!\n");
                    printf("\n--------------------------------------------------------------------------------\n");
                    printf("\nAperte ENTER para continuar");
                    fflush(stdin);
                    getchar();
                    system("cls");
                    break;

                }
            }
            while(op>5 || op<1);// enquanto o usuario digitar uma opção inválida

            printf("Aperte ENTER para continuar");
            fflush(stdin);
            getchar();
            system("cls");
            menu_voo(Lista_voo_no);

            break;

//INSERE NOVO PASSAGEIRO EM UMA LISTA DE PASSAGEIRO DE UM VOO
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case 4:
            system("cls");
            printf("\t....INSERÇÃO DE NOVO PASSAGEIRO....\n");
            printf("--------------------------------------------------------------------------------\n");
            if(get_assentos_livres(Lista_voo_no)==0)//VERIFICA SE LISTA DE PASSAGEIRO POSSUI ASSENTOS LIVRES
                //SE ENTRAR NESSE IF SIGNIFICA QUE O PASSAGEIRO VAI PRA FILA DE ESPERA
            {

                printf("\t....    LISTA DE PASSAGEIRO CHEIA    ....\n");
                if(quantidade_passageiro_fila(get_fila_espera_VOO(Lista_voo_no))!=get_capacidade_voo(Lista_voo_no))
                {
                    //VERIFICA SE A QUANTIDADE DE PASSAGEIROS DA FILA É DIFERENTE DA CAPACIDADE DO VOO;
                    //SE FOR IGUAL, PASSAGEIRO NÃO PODE PODE SER INSERIDO NA FILA
                    do
                    {




                        printf("\nGostaria de inserir passageiro na fila de espera? ");
                        printf("\n1: SIM");
                        printf("\n2: NAO\n");
                        printf("\n--------------------------------------------------------------------------------\n");
                        printf("Opcao: ");
                        scanf("%d", &op);//VERIFICA SE O USUSARIO QUER QUE O PASSAGEIRO ENTRE NA FILA DE ESPERA
                        switch(op)
                        {
                        case 1://CASO 1, PASSAGEIRO ENTRA NA FILA DE ESPERA
                            system("cls");
                            printf("....    Informe os dados do passageiro:    ....");
                            printf("\n--------------------------------------------------------------------------------\n");

                            fflush(stdin);
                            printf("\nCPF: ");
                            gets(cpf_passageiro);
                            while(!lista_vazia(busca_cpf_passageiro(get_lista_passageiro_VOO(Lista_voo_no), cpf_passageiro)))
                            {
                                //VERIFICA SE EXISTE ALGUM PASSAGEIRO COM O CPF INSERIDO

                                printf("\n\nCPF INVALIDO!!!");
                                printf("\n\n--------------------------------------------------------------------------------\n");
                                printf(".............     CPF digitado pertence a outro passageiro     .............\n");
                                printf("--------------------------------------------------------------------------------\n");
                                printf("Aperte ENTER para inserir um novo CPF");
                                fflush(stdin);
                                getchar();
                                system("cls");
                                printf("....    Informe os dados do passageiro:    ....");
                                printf("\n--------------------------------------------------------------------------------\n");
                                fflush(stdin);
                                printf("\nCPF: ");
                                gets(cpf_passageiro);
                            }

                            fflush(stdin);
                            printf("\nNome: ");
                            gets(nome_passageiro);

                            transforma_maiusculo(nome_passageiro, 0);
                            fflush(stdin);
                            printf("\nTelefone: ");
                            gets(telefone_passageiro);



                            info_passageiro=insere_info(nome_passageiro, telefone_passageiro, cpf_passageiro);
                            insere_fila_espera(get_fila_espera_VOO(Lista_voo_no), info_passageiro);
                            printf("\n--------------------------------------------------------------------------------\n");
                            fflush(stdin);
                            printf(".............     Passageiro inserido na fila com sucesso     .............\n\n");
                            printf("-Posição do passageiro na fila de espera: %d\n\n", quantidade_passageiro_fila(get_fila_espera_VOO(Lista_voo_no)));
                            printf("\n--------------------------------------------------------------------------------\n");
                            printf("\nAperte ENTER para continuar");
                            getchar();
                            system("cls");
                            menu_voo(Lista_voo_no);

                            break;
                        //CASO 2: USUARIO NÃO QUER QUE O PASSAGEIRO ENTRE NA FILA
                        case 2:
                            system("cls");
                            printf("\n--------------------------------------------------------------------------------\n");
                            printf(".............     Passageiro não foi inserido na fila de espera     .............\n");
                            printf("\n--------------------------------------------------------------------------------\n");
                            printf("\nAperte ENTER para voltar para o menu do voo");
                            fflush(stdin);
                            getchar();
                            system("cls");
                            menu_voo(Lista_voo_no);

                            break;

                        //USUSARIO NAO DIGITOU UMA OPÇÃO VALIDA
                        default:

                            system("cls");
                            printf("\n--------------------------------------------------------------------------------\n");
                            printf("\t!!!COMANDO INVALIDO!!!\n");
                            printf("\n--------------------------------------------------------------------------------\n");
                            printf("\nAperte ENTER para continuar");
                            fflush(stdin);
                            getchar();
                            system("cls");
                            printf("\t....INSERÇÃO DE NOVO PASSAGEIRO....\n");
                            printf("--------------------------------------------------------------------------------\n");

                            break;
                        }

                    }
                    while(op<1 || op>2);// enquanto o usuario digitar uma opção inválida

                }
                else
                {
                    //SE A QUANTIDADE DE PASSAGEIROS DA FILA DE ESPERA FOR IGUAL À CAPACIDADE DO VOO, PASSAGEIRO NAO PODE SER INSERIDO
                    system("cls");
                    printf("\n--------------------------------------------------------------------------------\n");
                    printf("\n\t!!PASSAGEIRO NÃO PODE SER INSERIDO!!");
                    printf("\n--------------------------------------------------------------------------------\n");
                    printf("\nMOTIVOS:");

                    printf("\n--------------------------------------------------------------------------------\n");
                    printf("-Não possui assentos disponíveis no voo.\n");
                    printf("-Capacidade da fila de espera esgotada.");
                    printf("\n--------------------------------------------------------------------------------\n");


                    printf("\nAperte ENTER para voltar ao menu do voo");
                    fflush(stdin);
                    getchar();
                    system("cls");
                    menu_voo(Lista_voo_no);


                }

            }

            //POSSUI VAGA NA LISTA DE PASSAGEIRO
            else
            {

                printf("\t\t....INSERÇÃO DE PASSAGEITO NA LISTA....\n");
                printf("\n--------------------------------------------------------------------------------\n");

                fflush(stdin);
                printf("\nCPF: ");
                gets(cpf_passageiro);
                while(!lista_vazia(busca_cpf_passageiro(get_lista_passageiro_VOO(Lista_voo_no), cpf_passageiro)))
                {
                    //VERIFICA SE EXISTE ALGUM PASSAGEIRO COM O CPF INSERIDO

                    printf("\n\nCPF INVALIDO!!!");
                    printf("\n\n--------------------------------------------------------------------------------\n");
                    printf(".............     CPF digitado pertence a outro passageiro     .............\n");
                    printf("--------------------------------------------------------------------------------\n");
                    printf("Aperte ENTER para inserir um novo CPF");
                    fflush(stdin);
                    getchar();
                    system("cls");
                    printf("....    Informe os dados do passageiro:    ....");
                    printf("\n--------------------------------------------------------------------------------\n");
                    fflush(stdin);
                    printf("\nCPF: ");
                    gets(cpf_passageiro);
                }

                fflush(stdin);
                printf("\nNome: ");
                gets(nome_passageiro);
                transforma_maiusculo(nome_passageiro, 0);//FUNÇÃO QUE PASSA O NOME DO PASSAGERIRO PARA MAIUSCULO

                fflush(stdin);
                printf("\nTelefone: ");
                gets(telefone_passageiro);


                printf("\n--------------------------------------------------------------------------------\n");
                //INSERE AS INFORMAÇÕES DO PASSAGEIRO EM UMA ESTRUTURA DO TIPO PASSAGEIRO INFO
                info_passageiro=insere_info(nome_passageiro, telefone_passageiro, cpf_passageiro);

                //INSERE O PASSAGEIRO EM UMA LISTA DE PASSAGEIRO DE UM VOO
                insere_lista_pasVOO(Lista_voo_no, info_passageiro);
                printf("\n\n--------------------------------------------------------------------------------\n");
                printf(".............     Passageiro inserido na lista de passageiros     .............");
                printf("\n--------------------------------------------------------------------------------\n");
                printf("\nAperte ENTER para continuar");
                fflush(stdin);
                getchar();
                system("cls");
                menu_voo(Lista_voo_no);
            }

            break;

//EXCLUI UMA LISTA DE PASSAGEIRO
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case 5:


            if(lista_vazia(get_lista_passageiro_VOO(Lista_voo_no)))
            {
                //VERIFICA SE A LISTA ESTA VAZIA
                printf ("\t\tEXCLUIR A LISTA DE PASSAGEIRO\n");
                printf("--------------------------------------------------------------------------------\n");
                printf(".............     A lista de passageiro já está vazia!     .............\n");
                printf("--------------------------------------------------------------------------------\n");
                printf("\nAperte ENTER para voltar ao menu do voo");
                fflush(stdin);
                getchar();
                system("cls");
                menu_voo(Lista_voo_no);

            }
            else
            {
                //SE NÃO TIVER VAZIA VERIFICA SE O USUARIO REALMENTE QUER EXCLUIR A LISTA
                do
                {


                    system("cls");
                    printf ("\t\tEXCLUIR A LISTA DE PASSAGEIRO\n");
                    printf("--------------------------------------------------------------------------------\n");
                    printf("Tem certeza que deseja excluir a lista de passageiro?");
                    printf("\n\nDigite 1 para EXCLUIR a lista ou 2 para VOLTAR para o menu do voo:");
                    printf("\n 1: SIM");
                    printf("\n 2: NÃO\n");
                    printf("\n--------------------------------------------------------------------------------\n");
                    fflush(stdin);
                    printf("Opção:  ");
                    scanf("%d", &op);
                    system("cls");
                    switch(op)
                    {


                    case 1://USUARIO QUER EXCLUIR A LISTA

                        printf ("\t\tEXCLUIR A LISTA DE PASSAGEIRO\n");
                        printf("--------------------------------------------------------------------------------\n");

                        while(!lista_vazia(get_lista_passageiro_VOO(Lista_voo_no)))
                        {
                            //ENQUANTO A LISTA NÃO ESTIVER VAZIA

                            retira_pass_listaVOO(Lista_voo_no, get_cpf(get_informacao_passageiro(get_lista_passageiro_VOO(Lista_voo_no))));

                        }
                        printf(".............     Lista de passageiro excluida com sucesso!!!!     .............");
                        printf("\n--------------------------------------------------------------------------------\n");

                        if(!verifica_fila_vazia(get_fila_espera_VOO(Lista_voo_no)))
                        {
                            //SE A FILA DE ESPERA NÃO ESTIVER VAZIA, APÓS A REMOÇÃO DOS PASSAGEIROS DA LISTA,
                            //OS PASSAGEIROS QUE ESTAVA NA FILA DE ESPERA SERÃO INSERIDOS NA LISTA DE PASSAGEIRO
                            printf ("\n\nPASSAGEIROS DA FILA DE ESPERA FORAM INSERIDOS NA LISTA DE PASSAGEIROS!!\n");
                            printf("--------------------------------------------------------------------------------\n");


                            while(!verifica_fila_vazia(get_fila_espera_VOO(Lista_voo_no)))
                            {
                                //INSERE PASSAGEIROS NA LISTA DE PASSAGEIRO
                                insere_lista_pasVOO(Lista_voo_no, retira_passageiro_fila(get_fila_espera_VOO(Lista_voo_no)));
                                contador++;
                            }

                            printf("Quantidade de passageiros inseridos na lista de passageiros: %d\n", contador);
                            //IMPRIME A QUANTIDADE DE PASSAGEIROS INSERIDOS NA LISTA
                            printf("Quantidade de assentos disponíveis: %d\n ",
                                   //IMPRIME A QUANTIDADE DE ASSENTOS DISPONIVEIS
                                   get_capacidade_voo(Lista_voo_no)-contador);//
                            printf("\n--------------------------------------------------------------------------------\n");
                        }

                        printf("\nAperte ENTER para voltar ao menu do voo");
                        fflush(stdin);
                        getchar();
                        system("cls");
                        menu_voo(Lista_voo_no);//VOLTA AO MENU DO VOO
                        break;

                    case 2://USUARIO DECIDIU NÃO EXCLUIR A LISTA DE PASSAGEIRO
                        printf ("\t\t.....EXCLUIR O VOO DE NUMERO %d.....\n", get_num_voo(Lista_voo_no));
                        printf("\n--------------------------------------------------------------------------------\n");
                        printf(".............     Voo Não foi excluido!!!!     .............");
                        printf("\n--------------------------------------------------------------------------------\n");
                        printf("\nAperte ENTER para voltar ao menu do voo");
                        fflush(stdin);
                        getchar();
                        system("cls");
                        menu_voo(Lista_voo_no);

                        break;



                    default://USUARIO DIGITOU UMA OPÇÃO INVALIDA


                        system("cls");
                        printf("\n--------------------------------------------------------------------------------\n");
                        printf("\t!!!COMANDO INVALIDO!!!\n");
                        printf("\n--------------------------------------------------------------------------------\n");
                        printf("Aperte ENTER para continuar");
                        fflush(stdin);
                        getchar();
                        break;
                    }
                }
                while(op<1 || op>2);// enquanto o usuario digitar uma opção inválida
            }
            break;

//EXCLUI FILA DE ESPERA
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 6:

            if(verifica_fila_vazia(get_fila_espera_VOO(Lista_voo_no)))
            {
                //VERIFICA SE A FILA DE ESPERA JÀ ESTA VAZIA
                printf ("\t\tEXCLUIR A FILA DE ESPERA\n");
                printf("--------------------------------------------------------------------------------\n");
                printf(".............     A fila de espera está vazia!     .............\n");
                printf("--------------------------------------------------------------------------------\n");
                printf("\nAperte ENTER para voltar ao menu do voo");
                fflush(stdin);
                getchar();
                system("cls");
                menu_voo(Lista_voo_no);
            }
            else
            {
                //FILA DE ESPERA NÃO ESTA VAZIA
                printf ("\t\tEXCLUIR A FILA DE ESPERA\n");
                printf("--------------------------------------------------------------------------------\n");
                contador=0;
                while(!verifica_fila_vazia(get_fila_espera_VOO(Lista_voo_no)))
                {
                    //REMOVE TODOS OS PASSAGEIROS DA FILA
                    retira_passageiro_fila(get_fila_espera_VOO(Lista_voo_no));
                    contador++;
                }
                printf("Fila removida com sucesso!!");
                printf("\nQuantidade de passageiros removidos: %d\n", contador);
                printf("--------------------------------------------------------------------------------\n");
                printf("\nAperte ENTER para voltar ao menu do voo");
                fflush(stdin);
                getchar();
                system("cls");
                menu_voo(Lista_voo_no);


            }
            break;

//IMPRIME OS DADOS DO PASSAGEIRO DE UMA FILA DE ESPERA
////////////////////////////////////////////////////////////////////////////////////////////////////
        case 7:

            if(verifica_fila_vazia(get_fila_espera_VOO(Lista_voo_no)))
            {
                //VERIFICA SE A FILA ESTA VAZIA
                system("cls");
                printf ("\t\tPASSAGEIROS DA FILA DE ESPERA\n");
                printf("--------------------------------------------------------------------------------\n");
                printf(".............     A fila de espera está vazia!     .............\n");
                printf("--------------------------------------------------------------------------------\n");
                printf("\nAperte ENTER para voltar ao menu do voo");
                fflush(stdin);
                getchar();
                system("cls");
                menu_voo(Lista_voo_no);
            }
            else
            {
                //FILA NAO ESTA VAZIA
                system("cls");
                printf ("\t\tPASSAGEIROS DA FILA DE ESPERA\n");
                printf("--------------------------------------------------------------------------------");
                imprime_dados_fila_espera(get_fila_espera_VOO(Lista_voo_no));//IMPRIME OS DADOS DOS PASSAGEIROS
                printf("\n--------------------------------------------------------------------------------\n");
                printf("\n\nAperte ENTER para voltar ao menu do voo");
                fflush(stdin);
                getchar();
                system("cls");
                menu_voo(Lista_voo_no);

            }

            break;

//ACESSAR OS DADOS DE UM PASSAGEIRO
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 8:

            system("cls");
            printf ("\t\tRELAÇÃO DOS PASSAGEIROS DO VOO\n");
            printf("\n--------------------------------------------------------------------------------\n");
            if(lista_vazia(get_lista_passageiro_VOO(Lista_voo_no)))
            {
                //VERIFICA SE A LISTA DE PASSAGEIRO ESTA VAZIA
                fflush(stdin);
                printf(".............     Ainda não existe passageiros cadastrado     ...........\n\n");
                printf("--------------------------------------------------------------------------------");
                printf("\nAperte ENTER para continuar");
                getchar();
                system("cls");
                menu_voo(Lista_voo_no);
            }
            //SE A LISTA NAO ESTIVER VAIZA, IMPRIME OS DADOS DOS PASSSAGEIROS
            imprime_dados_passageiros_VOO(Lista_voo_no);
            printf("\n--------------------------------------------------------------------------------\n");

            printf("\nDigite o CPF do Passageiro desejado: ");
            //ACESSA OS DADOS DO PASSAGEIRO ATRÁVES DO CPF
            scanf("%s", &cpf_passageiro);

            //BUSCA UM PASSAGEIRO NA LISTA DE PASSAGEIROS, SE NÃO ENCONTRAR FUNÇÃO RETORNA NULL
            Lista_passageiro_no=busca_cpf_passageiro(get_lista_passageiro_VOO(Lista_voo_no), cpf_passageiro);

            if(lista_vazia(Lista_passageiro_no))
            {
                //PASSAGEIRO NÃO ENCONTRADO
                printf("\n\n--------------------------------------------------------------------------------");
                printf("\n.............     Não possui nenhum passageiro com o CPF inserido     .............\n");
                printf("--------------------------------------------------------------------------------");

                printf("\n\nAperte ENTER para voltar no menu do voo");
                fflush(stdin);
                getchar();
                system("cls");
                menu_voo(Lista_voo_no);

            }
            //PASSAGEIRO FOI ENCONTRADO
            fflush(stdin);
            printf("\n\nAperte ENTER para continuar");
            getchar();
            system("cls");

            menu_passageiro(Lista_passageiro_no);//ACESSANDO O MENU DO PASSAGEIRO
            break;

        case 9:
            system("cls");


            menu();
            break;

        default:
            system("cls");
            printf("\n--------------------------------------------------------------------------------\n");
            printf("\t!!!COMANDO INVALIDO!!!\n");
            printf("\n--------------------------------------------------------------------------------\n");
            printf("Aperte ENTER para continuar");
            fflush(stdin);
            getchar();
            break;

        }



    }
    while(op2 <1 || op2 > 9);// enquanto o usuario digitar uma opção inválida



}

//MENU DO PASSAGEIRO
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void menu_passageiro(lista_passageiros* Lista_passageiro_no)
{
    do
    {
        system("cls");
        printf("MENU DO PASSAGEIRO");
        printf("\n\n--------------------------------------------------------------------------------\n");
        printf("Digite o comando desejado:\n\n");
        printf("1.Acessar dados do passageiro.");
        printf("\n2.Alterar dados do passageiro.");
        printf("\n3.Remover passageiro do Voo.");
        printf("\n4.Voltar.");
        printf("\n--------------------------------------------------------------------------------\n");
        printf("Opção: ");
        scanf("%d", &op2);//USUARIO DIGITA O COMANDO


        switch (op2)
        {
//ACESSAR OS DADOS DO PASSAGEIRO
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case 1:
            do
            {
                system("cls");
                printf("DADOS DO PASSAGEIRO");
                printf("\n\n--------------------------------------------------------------------------------\n");
                imprime_dado_no_passageiro(Lista_passageiro_no);//IMPRIME OS DADOS DO PASSAGEIRO
                printf("\n\n--------------------------------------------------------------------------------\n");

                printf("\n\n--------------------------------------------------------------------------------\n");
                printf("Deseja voltar no menu do passageiro? ");
                printf("\n1: SIM");
                printf("\n2: NÃO\n");
                printf("\n--------------------------------------------------------------------------------\n");
                fflush(stdin);
                printf("Opcao:  ");
                scanf("%d", &op);//VERIFICA SE O USUSARIO DESEJA VOLTAR PARA O MENU DO PASSAGEIRO
                system("cls");
                if(op==1)
                {
                    //USUARIO DESEJA VOLTAR PARA O MENU DO PASSAGEIRO
                    printf("\n--------------------------------------------------------------------------------\n");
                    printf(".............     Voltando para o menu do passageiro     .............");
                    printf("\n--------------------------------------------------------------------------------\n");
                    printf("\n Aperte ENTER para continuar");
                    fflush(stdin);
                    getchar();
                    system("cls");
                    menu_passageiro(Lista_passageiro_no);//CHAMA A FUNÇÃO MENU PASSAGEIRO, PASSACOMO PARAMETRO O NÓ DE LISTA DO PASSAGEIRO
                }
                if(op==2)
                {
                    //USUARIO NÃO QUER VOLTAR NO MENU DO PASSAGEIRO
                    //PROGRAMA VOLTA PARA O MENU DO VOO
                    printf("--------------------------------------------------------------------------------\n");
                    printf(".............     Voltando para o menu do voo     .............");
                    printf("\n--------------------------------------------------------------------------------\n");
                    printf("\n Aperte ENTER para continuar");
                    fflush(stdin);
                    getchar();
                    system("cls");
                    menu_voo(Lista_voo_no);
                }

            }
            while(op>1 || op>2);// enquanto o usuario digitar uma opção inválida
            break;

//ALTERA DADOS DO PASSAGEIRO
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case 2:

            system("cls");
            printf("ALTERAR DADOS DO PASSAGEIRO");
            printf("\n\n--------------------------------------------------------------------------------\n");
            printf("\nCPF atual do passageiro: %s", get_cpf(get_informacao_passageiro(Lista_passageiro_no)));
            printf("\nNovo CPF: ");
            fflush(stdin);
            gets(cpf_passageiro);
            while(!lista_vazia(busca_cpf_passageiro(get_lista_passageiro_VOO(Lista_voo_no), cpf_passageiro)))
            {
                //VERIFICA SE O CPF DIGITADO JÁ ESTA SENDO UTILIZADO POR OUTRO PASSAGEIRO
                printf("\n\nCPF invalido...\n");
                printf("MOTIVO:");
                printf("\n--------------------------------------------------------------------------------\n");
                printf("-Já existe um passageiro com o CPF informado!!\n");
                printf("--------------------------------------------------------------------------------\n");
                printf("Aperte ENTER para inserir um novo CPF");
                fflush(stdin);
                getchar();

                system("cls");
                printf("\t\t....ALTERA DADOS DO PASSAGEIRO.....\n");
                printf("\n--------------------------------------------------------------------------------\n");
                printf("\n\CPF atual do passageiro:  %s", get_cpf(get_informacao_passageiro(Lista_passageiro_no)));
                printf("\nNovo CPF: ");
                fflush(stdin);
                scanf("%d", &cpf_passageiro);
            }

            printf("\nNome atual: %s", get_nome(get_informacao_passageiro(Lista_passageiro_no)));
            printf("\nNovo nome: ");
            fflush(stdin);
            gets(nome_passageiro);
            transforma_maiusculo(nome_passageiro, 0);//TRANSFORMA O NOME DO USUARIO PARA MAIUSCULO


            printf("\nTelefone atual: %s", get_telefone(get_informacao_passageiro(Lista_passageiro_no)));
            printf("\nNovo telefone: ");
            fflush(stdin);
            gets(telefone_passageiro);

            altera_info_passageiro(Lista_passageiro_no , insere_info(nome_passageiro, telefone_passageiro, cpf_passageiro));
            //ALTERA AS INFORMAÇÕES DO PASSAGEIRO

            printf("\n\n--------------------------------------------------------------------------------\n");
            system("pause");
            menu_passageiro(Lista_passageiro_no);
            break;

//REMOVE O PASSAGEIRO
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case 3:


            system("cls");
            printf ("\t\t.....REMOVER O PASSAGEIRO DE CPF %s.....\n", get_cpf(get_informacao_passageiro(Lista_passageiro_no)));
            printf("--------------------------------------------------------------------------------\n");
            printf("Tem certeza que deseja REMOVER o passageiro?");
            printf("\n\nDigite 1 para EXCLUIR o voo ou 2 para VOLTAR para o menu do passageiro:");
            printf("\n 1: REMOVER");
            printf("\n 2: VOLTAR\n");
            printf("\n--------------------------------------------------------------------------------\n");
            fflush(stdin);
            printf("Opção:  ");
            scanf("%d", &op);//VERIFICA SE O USUARIO QUER REALMENTE REMOVER O PASSAGEIRO
            system("cls");
            switch(op)
            {
                do
                {

                case 1://USUARIO QUER REMOVER O PASSAGEIRO

                    printf ("\t\t.....REMOVER O PASSAGEIRO DE CPF %s.....\n",  get_cpf(get_informacao_passageiro(Lista_passageiro_no)));
                    retira_pass_listaVOO(Lista_voo_no, get_cpf(get_informacao_passageiro(Lista_passageiro_no)) );
                    printf("\n--------------------------------------------------------------------------------\n");
                    printf(".............     Passageiro removido com sucesso!!!!     .............");
                    printf("\n--------------------------------------------------------------------------------\n");

                    if(verifica_fila_vazia(get_fila_espera_VOO(Lista_voo_no)))
                    {
                        //VERIFICA SE A FILA DE ESPERA ESTA VAZIA
                        //SE ESTIVER NÃO EXECUTA NADA
                        printf("Aperte ENTER para voltar");
                        fflush(stdin);
                        getchar();
                        system("cls");

                    }
                    else
                    {
                        //SE A FILA DE ESPERA NÃO ESTIVER VAZIA, O PRIMEIRO PASSAGEIRO DA FILA SERA INSERIDO NA LISTA DE PASSAGEIRO

                        printf("\nAperte ENTER para continuar");
                        fflush(stdin);
                        getchar();
                        system("cls");
                        printf("PRIMEIRO PASSAGEIRO DA FILA DE ESPERA FOI INSERIDO NA LISTA DE PASSAGEIROS.\n\n");
                        printf("\tDADOS DO PASSAGEIRO :");
                        printf("\n--------------------------------------------------------------------------------\n");
                        //INFORMA OS DADOS DO PASSAGEIRO QUE SERA INSERIDO NA LISTA
                        info_passageiro = get_info_filaespera(get_fila_espera_VOO(Lista_voo_no));
                        printf("NOME: %s", get_nome(info_passageiro));
                        printf("\nCPF: %s", get_cpf(info_passageiro));
                        printf("\nTELEFONE: %s", get_telefone(info_passageiro));
                        printf("\n--------------------------------------------------------------------------------\n");
                        insere_lista_pasVOO(Lista_voo_no, retira_passageiro_fila(get_fila_espera_VOO(Lista_voo_no)));
                        printf("Aperte ENTER para voltar ao menu do voo");
                        fflush(stdin);
                        getchar();
                        system("cls");
                    }

                    menu_voo(Lista_voo_no);//VOLTA PARA O MENU DO VOO
                    break;

                case 2://USUARIO DECIDIU NÃO REMOVER O PASSAGEIRO

                    printf ("\t\t.....REMOVER O PASSAGEIRO DE CPF %s.....\n", get_cpf(get_informacao_passageiro(Lista_passageiro_no)));
                    printf("\n--------------------------------------------------------------------------------\n");
                    printf(".............     Passageiro não foi removido!!!!     .............");
                    printf("\n--------------------------------------------------------------------------------\n");
                    printf("\nAperte ENTER para voltar ao menu do voo");
                    fflush(stdin);
                    getchar();
                    menu_passageiro(Lista_passageiro_no);
                    system("cls");
                    break;



                default://USUARIO INSERIO UMA OPÇÃO INVALIDA


                    system("cls");
                    printf("\n--------------------------------------------------------------------------------\n");
                    printf("\t!!!COMANDO INVALIDO!!!\n");
                    printf("\n--------------------------------------------------------------------------------\n");
                    printf("Aperte ENTER para continuar");
                    fflush(stdin);
                    getchar();
                    system("cls");
                    break;
                }
                while(op<1 || op>2);// enquanto o usuario digitar uma opção inválida
            }

            break;

//VOLTA PARA O MENU DO VOO
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case 4:
            printf("\n--------------------------------------------------------------------------------\n");
            printf("\tVoltando para o menu do voo..\n");
            printf("\n--------------------------------------------------------------------------------\n");
            printf("Digite ENTER para voltar para o menu do voo");
            fflush(stdin);
            getchar();
            system("cls");
            menu_voo(Lista_voo_no);//CHAMA A FUNÇÃO DO MENU DO VOO PASSANDO COMO PARAMENTRO O NÓ DE VOO

            break;

        default:// PASSAEGEIRO INSERIU OPÇÃO INVALIDA


            system("cls");
            printf("\n--------------------------------------------------------------------------------\n");
            printf("\t!!!COMANDO INVALIDO!!!\n");
            printf("\n--------------------------------------------------------------------------------\n");
            printf("Aperte ENTER para continuar");
            fflush(stdin);
            getchar();
            system("cls");
            break;


        }
    }
    while(op2<1 || op2>4);// enquanto o usuario digitar uma opção inválida
}

////////////////////////////////////////////FIM/////////////////////////////////////////////////////////////////
