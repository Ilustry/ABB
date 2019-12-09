#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct{
    int dia, mes, ano;
    char nome[50], tel[12];
}Contato;

typedef struct{
    Contato cont;
    struct Arvore *esq, *dir;
}Arvore;

void Incluir(Arvore** folha, Contato cont){
    if(*folha == NULL){
        *folha = malloc(sizeof(Arvore));
        (*folha)->dir = NULL;
        (*folha)->esq = NULL;
        (*folha)->cont = cont;
        if(raiz == NULL){
            raiz = folha;
            exc = raiz;
        }
    }
    else{
        if(strcmp(cont.nome, (*folha)->cont.nome) < 0)
            Incluir(&(*folha)->esq, cont);
        else if(strcmp(cont.nome, (*folha)->cont.nome) > 0)
            Incluir(&(*folha)->dir, cont);
        else if(strcmp(cont.nome, (*folha)->cont.nome) == 0)
            printf("Contato ja cadastrado.\n");
    }

}

void Consultar(Arvore *folha, char *p){
    if(folha == NULL)
        return;

    if(strcmp(folha->cont.nome, p) == 0){
        printf("\n-------------------------\n");
        printf("'Nome: %s", folha->cont.nome);
        printf("'Telefone: %s", folha->cont.tel);
        printf("'Nascimento: %d/%d/%d\n", folha->cont.dia, folha->cont.mes, folha->cont.ano);
        printf("-------------------------\n\n");
        getch();
        return;
    }
        Consultar(folha->esq, p);
        Consultar(folha->dir, p);
}

Arvore* remover(Arvore* folha, char *p);

Contato Alterar(Arvore *folha, char *p, int opc){
    if(folha == NULL){
        Contato ctt;
        ctt.ano = -1;
        return ctt;
    }
    if(strcmp(p, folha->cont.nome) == 0){
        Contato ctt;
        switch(opc){
            case 2:
                printf("Informe o novo numero.\n");
                fflush(stdin);
                fgets(folha->cont.tel, 50, stdin);
                break;

            case 3:
                fflush(stdin);
                printf("Informe a nova data.\nModelo: DD/MM/AAAA\n\n");
                scanf("%d/%d/%d", &folha->cont.dia, &folha->cont.mes, &folha->cont.ano);
                break;
        }

    }
    Alterar(folha->esq, p, opc);
    Alterar(folha->dir, p, opc);

}

Contato cts;

int Alterar_Nome(Arvore* folha, char *p){
    if(folha == NULL)
            return 0;

    if(strcmp(folha->cont.nome, p) == 0){
        fflush(stdin);
        cts = folha->cont;
        printf("Informe o novo nome.\n");
        fgets(cts.nome, 50, stdin);
        return 1;
    }
    return strcmp(folha->cont.nome, p) == 0 || Alterar_Nome(folha->esq, p) || Alterar_Nome(folha->dir, p);

}


Arvore* remover(Arvore* folha, char *p){

 if(folha == NULL){
    return NULL;
 }
     else if(strcmp(p, folha->cont.nome) < 0)
        folha->esq = remover(folha->esq, p);

     else if(strcmp(p, folha->cont.nome) > 0)
        folha->dir = remover(folha->dir, p);

     else{
        if(folha->esq == NULL && folha->dir == NULL) {
           free(folha);
           folha = NULL;
        }
        else if(folha->esq == NULL) {
           Arvore* t = folha;
           folha = folha->dir;
           free(t);
        }
        else if(folha->dir == NULL) {
           Arvore* t = folha;
           folha = folha->esq;
           free(t);
        }
        else{
           Arvore* f = folha->esq;
           while(f->dir != NULL) {
              f = f->dir;
           }
           folha->cont = f->cont;
           f->cont.nome[50] = p;
           folha->esq = remover(folha->esq, p);
        }
     }
    return folha;
}

void Exibir(Arvore *folha){
    if(folha == NULL)
        return;

        Exibir(folha->esq);
        printf("\n-------------------------\n");
        printf("'Nome: %s", folha->cont.nome);
        printf("'Telefone: %s", folha->cont.tel);
        printf("'Nascimento: %d/%d/%d\n", folha->cont.dia, folha->cont.mes, folha->cont.ano);
        printf("-------------------------\n\n");
        Exibir(folha->dir);
}

void Aniversariantes(Arvore *folha, int mes){
    if(folha == NULL)
        return;

    Aniversariantes(folha->esq, mes);
    if(mes == folha->cont.mes){
        printf("\n-------------------------\n");
        printf("'Nome: %s", folha->cont.nome);
        printf("'Telefone: %s", folha->cont.tel);
        printf("'Nascimento: %d/%d/%d\n", folha->cont.dia, folha->cont.mes, folha->cont.ano);
        printf("-------------------------\n\n");
    }
    Aniversariantes(folha->dir, mes);

}

int Quantidade (Arvore * folha){

if (folha == NULL)
    return 0;

    return 1 + Quantidade(folha->esq) + Quantidade(folha->dir);


}

int main()
{

    Arvore *folha = NULL;
    Contato cont, consulta;
    int opc, retorno = 0;
    char *p;
    char nome[50];

    do{
        fflush(stdin);
        printf("//////////////////////////////\n");
        printf("/'          'MENU'          '/\n");
        printf("/'--------------------------'/\n");
        printf("/'1.Cadastrar               '/\n");
        printf("/'2.Listar                  '/\n");
        printf("/'3.Consultar               '/\n");
        printf("/'4.Excluir                 '/\n");
        printf("/'5.Buscar por Aniversario  '/\n");
        printf("/'6.Total de Contatos       '/\n");
        printf("/'7.Alterar contato         '/\n");
        printf("/'0.Sair                    '/\n");
        printf("//////////////////////////////\n");

        scanf("%d", &opc);

        switch(opc){
            case 1:
                printf("Informe a data de nascimento.\nModelo: DD/MM/AAAA\n\n");
                scanf("%d/%d/%d", &cont.dia, &cont.mes, &cont.ano);
                printf("Informe o Nome.\n");
                fflush(stdin);
                fgets(cont.nome, 50, stdin);
                printf("Informe o Telefone.\n");
                fgets(cont.tel, 13, stdin);
                Incluir(&folha, cont);
                break;

            case 2:
                Exibir(folha);
                break;

            case 3:
                printf("Informe o nome.\n");
                fflush(stdin);
                fgets(cont.nome, 50, stdin);
                p = cont.nome;
                Consultar(folha, p);
                break;

            case 4:
                printf("Informe o nome.\n");
                fflush(stdin);
                fgets(nome, 50, stdin);
                p = nome;
                folha = remover(folha, p);
                break;

            case 5:

                printf("Informe o mes: \n");
                scanf("%d", &cont.mes);
                Aniversariantes(folha, cont.mes);
                break;

            case 6:
                opc = Quantidade(folha);
                printf("\n O total de contatos: %d\n", opc);
                opc = 6;
                break;

            case 7:
                printf("\n1. Alterar nome.\n");
                printf("2. Alterar numero.\n");
                printf("3. Alterar data de nascimento.\n");
                printf("4. Alterar tudo.\n");
                scanf("%d", &opc);
                fflush(stdin);
                printf("Informe o nome do contato a ser alterado.\n");
                fgets(consulta.nome, 50, stdin);
                p = consulta.nome;

                if(opc == 1){
                    retorno = Alterar_Nome(folha, p);
                    if(retorno == 1){
                        folha = remover(folha, p);
                        Incluir(&folha, cts);
                    }
                }
                else if(opc == 2 || opc == 3){
                    Alterar(folha, p, opc);
                }
                else if(opc == 4){
                    cont = Alterar(folha, p, opc);
                    if(cont.ano != -1){
                        folha = remover(folha, p);
                        fflush(stdin);
                        printf("Informe a data de nascimento.\nModelo: DD/MM/AAAA\n\n");
                        scanf("%d/%d/%d", &cont.dia, &cont.mes, &cont.ano);
                        printf("Informe o Nome.\n");
                        fflush(stdin);
                        fgets(cont.nome, 50, stdin);
                        printf("Informe o Telefone.\n");
                        fgets(cont.tel, 13, stdin);
                        Incluir(&folha, cont);
                    }

                }
                opc = 7;
                break;
        }
    }while(opc != 0);



    return 0;
}
