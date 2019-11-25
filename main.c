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
    if(folha == NULL){
        return;
    }
    if(strcmp(folha->cont.nome, p) == 0){
        printf("\n-------------------------\n");
        printf("'Nome: %s", folha->cont.nome);
        printf("'Telefone: %s", folha->cont.tel);
        printf("'Nascimento: %d/%d/%d\n", folha->cont.dia, folha->cont.mes, folha->cont.ano);
        printf("-------------------------\n\n");
        return;
    }
        Consultar(folha->esq, p);
        Consultar(folha->dir, p);
}

void Alterar(Arvore *folha, char *p){
    if(folha == NULL)
        return;

    Arvore *Ant = folha;


}

Arvore* Excluir(Arvore *folha, char *p){
    if(folha == NULL){
        return folha;
    }

    if(strcmp(p, folha->cont.nome) == 0){
        folha = Remover(folha);
        return folha;
    }

    if(strcmp(p, folha->cont.nome) < 0)
        return Excluir(folha->esq, p);
    else
        return Excluir(folha->dir, p);

}

Arvore* Remover(Arvore *folha){
    Arvore *p;

    if(folha->esq == NULL){
        p = folha;
        folha = folha->dir;
        p = NULL;
        return folha;
    }
    else if(folha->dir == NULL){
        p = folha;
        folha = folha->esq;
        p = NULL;
        return folha;
    }
    else{
        return Substituir(folha, folha->dir);
    }

}

Arvore* Substituir(Arvore *folha, Arvore *Celula){
    Arvore *p;

    if(Celula->esq == NULL){
        folha->cont = Celula->cont;
        p = Celula;
        Celula = Celula->dir;
        p = NULL;
        free(p);
    }
    else
        Substituir(folha, Celula->esq);

    return Celula;
}

Arvore* Exclusao(Arvore *folha, char *p){
    if(folha == NULL)
        return;
    folha = malloc(sizeof(Arvore));
    printf("dsfgadg\n");
    folha = NULL;
    free(folha);

    return folha;
}

void Exibir(Arvore *folha){
    if(folha == NULL)
        return;
    else{
        printf("\n-------------------------\n");
        printf("'Nome: %s", folha->cont.nome);
        printf("'Telefone: %s", folha->cont.tel);
        printf("'Nascimento: %d/%d/%d\n", folha->cont.dia, folha->cont.mes, folha->cont.ano);
        printf("-------------------------\n\n");
        Exibir(folha->esq);
        Exibir(folha->dir);
    }

}


int main()
{

    Arvore *folha = NULL;
    Contato cont;
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
                folha = Excluir(folha, p);
               /* if(Ex)
                    printf("Excluido com sucesso.\n");
                else
                    printf("Nao listado.\n"); */
                break;
        }
    }while(opc != 0);



    return 0;
}
