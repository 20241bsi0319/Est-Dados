#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tadlista.h"

typedef struct tipo_p{
    char idProjeto[10];
    char nomeProjeto[128];
} * t_projeto;

typedef struct tipo_m{
    char idMembro[10];
    char nomeMembro[128];
} * t_membro;

typedef struct tipo_r{
    char idMembro[10];
    char idProjeto[10];
} * t_relacao;

Lista load_projetos(char *filename){
    FILE * arq = fopen(filename, "r");
    char buffer[128];

    Lista lst = newLista();
    t_projeto proj;

    while(fgets(buffer, sizeof(buffer), arq) != NULL){
        proj = (t_projeto)malloc(sizeof(struct tipo_p));

        char *token = strtok(buffer, ", ");
        strcpy(proj->idProjeto, token);

        token = strtok(NULL, ".");
        strcpy(proj->nomeProjeto, token);

        appendLista(lst, proj);
    }
    fclose(arq);
    return lst;
}

Lista load_membros(char *filename){
    FILE * arq = fopen(filename, "r");
    char buffer[128];

    Lista lst = newLista();
    t_membro member;

    while(fgets(buffer, sizeof(buffer), arq) != NULL){
        member = (t_membro)malloc(sizeof(struct tipo_m));

        char *token = strtok(buffer, ", ");
        strcpy(member->idMembro, token);

        token = strtok(NULL, ".");
        strcpy(member->nomeMembro, token);

        appendLista(lst, member);
    }
    fclose(arq);
    return lst;
}

Lista load_relacoes(char *filename){
    FILE * arq = fopen(filename, "r");
    char buffer[128];

    Lista lst = newLista();
    t_relacao rel;

    while(fgets(buffer, sizeof(buffer), arq)){
        rel = (t_relacao)malloc(sizeof(struct tipo_r));

        if(buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';

        char *token = strtok(buffer, ", ");
        strcpy(rel->idMembro, token);

        token = strtok(NULL, ".");
        strcpy(rel->idProjeto, token);

        appendLista(lst, rel);
    }
    fclose(arq);
    return lst;
}

Lista membros_projeto(char *id_proj, Lista lst_relacoes, Lista lst_membros){
    Lista membros_proj = newLista();

    for(int i = 0; i < lenLista(lst_relacoes); i++){
        t_relacao relacao = getElem(lst_relacoes, i);
        if(atoi(relacao->idProjeto) == atoi(id_proj))
            for(int j = 0; j < lenLista(lst_membros); j++){
                t_membro membro = getElem(lst_membros, j);
                if(atoi(membro->idMembro) == atoi(relacao->idMembro))
                    appendLista(membros_proj, membro);
        }
    }
    return membros_proj;
}

Lista projetos_membro(char *id_mem, Lista lst_relacoes, Lista lst_projetos){
    Lista projetos_mem = newLista();

    for(int i = 0; i < lenLista(lst_relacoes); i++){
        t_relacao relacao = getElem(lst_relacoes, i); 
        if(atoi(relacao->idMembro) == atoi(id_mem))
            for(int j = 0; j < lenLista(lst_projetos); j++){
                t_projeto projeto = getElem(lst_projetos, j);
                if(atoi(projeto->idProjeto) == atoi(relacao->idProjeto))
                    appendLista(projetos_mem, projeto);
            }
    }
    return projetos_mem;
}

int main(){
    Lista listaP = load_projetos("bdprojetos.txt");
    Lista listaM = load_membros("bdmembros.txt");
    Lista listaR = load_relacoes("bdrelacoes.txt");

    int opcao = 0; char id[10];

    printf("\n MENU APP LISTA");
    while(opcao != 3){
        printf("\n ===========================\n");
        printf(" 1. Membros de 1 Projeto\n");
        printf(" 2. Projetos de 1 membro\n");
        printf(" 3. Sair\n");
        printf(" Escolha uma opcao: ");
        scanf("%d", &opcao);
        printf(" ===========================\n\n");

        if(opcao == 1){
            printf(" Digite o ID de um Projeto: ");
            scanf("%s", id);
            if(atoi(id) > 104 || atoi(id) < 101){
                printf("\n ID invalido, tente novamente...\n");
                continue;
            }
            Lista resultado = membros_projeto(id, listaR, listaM);

            printf(" -> Membros do projeto %s:\n", id);
            printf("\n ID:  Nome do Membro:\n");
            for(int i = 0; i < lenLista(resultado); i++){
                t_membro membro = getElem(resultado, i);
                printf(" %-3s %s\n", membro->idMembro, membro->nomeMembro);
            }
        }
        else if(opcao == 2){
            printf(" Digite o ID de um Membro: ");
            scanf("%s", id);
            if(atoi(id) > 10 || atoi(id) < 1){
                printf("\n ID invalido, tente novamente...\n");
                continue;
            }
            Lista resultado = projetos_membro(id, listaR, listaP);

            printf(" -> Projetos do membro %s:\n", id);
            printf("\n ID:  Nome dos Projetos:\n");
            for(int i = 0; i < lenLista(resultado); i++){
                t_projeto projeto = getElem(resultado, i);
                printf(" %-3s %s\n", projeto->idProjeto, projeto->nomeProjeto);
            }
        }
        else if(opcao > 3 || opcao < 3){
            printf(" Opcao invalida, tente novamente...\n");

        }
    }
    printf(" Voce saiu!\n");
    return 0;
}