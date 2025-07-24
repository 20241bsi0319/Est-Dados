#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct{
    char mat[10]; char aluno[64]; float notas[3];
} t_aluno;

t_aluno str2class(const char *linha){
    char lin[100]; strcpy(lin, linha); t_aluno aux;

    char *mat = strtok(lin, ";");
    strcpy(aux.mat, mat);

    char *aluno = strtok(NULL, ";");
    strcpy(aux.aluno, aluno);

    for(int i = 0; i < 3; i++){
        char *nota = strtok(NULL, ";");
        aux.notas[i] = atof(nota);
    }
    return aux;
}

void open_arq(char *filename, t_aluno alunos[], int *qtd){
    FILE *arq = fopen(filename, "r");
    char buffer[100];
    *qtd = 0;

    fgets(buffer, sizeof(buffer), arq); //ignora cabeçalho

    while(fgets(buffer, sizeof(buffer), arq)){
        alunos[*qtd] = str2class(buffer);
        (*qtd)++;
    }
    fclose(arq);
}

void calc_medias(t_aluno alunos[], int qtd, float medias_alunos[], float *media_turma){
    float soma_medias = 0;
    for(int i = 0; i < qtd; i++){
        float soma = 0;
        for(int j = 0; j < 3; j++){
            soma += alunos[i].notas[j];
        }
        medias_alunos[i] = soma / 3;
        soma_medias += medias_alunos[i];
    }
    *media_turma = soma_medias / qtd;
}

void gera_relatorio(t_aluno alunos[], int qtd){
    float med_alunos[qtd];
    float med_turma = 0;
    calc_medias(alunos, qtd, med_alunos, &med_turma);

    FILE *arq = fopen("relatorio_turma.txt", "w");
    fprintf(arq, "\nRELATORIO FINAL DE NOTAS: \nMEDIA FINAL DE CADA ALUNO:\n");

    for(int i = 0; i < qtd; i++){ //grava a média final dos alunos no arquivo
        fprintf(arq, "\n%s - %s, MF: %.2f", alunos[i].mat, alunos[i].aluno, med_alunos[i]);
    }

    fprintf(arq, "\n\nMEDIA DA TURMA: %.2f\n", med_turma); //grava a média final da turma

    fprintf(arq, "\nALUNOS APROVADOS:\n"); //grava os alunos aprovados
    for(int i = 0; i < qtd; i++){
        if(med_alunos[i] >= 7){
            fprintf(arq, "%s\n", alunos[i].aluno);
        }
    }

    fprintf(arq, "\nALUNOS REPROVADOS:\n"); //grava os alunos reprovados
    for(int i = 0; i < qtd; i++){
        if(med_alunos[i] < 7){
            fprintf(arq, "%s\n", alunos[i].aluno);
        }
    }

    int aluno_maior_med = 0, maior = med_alunos[0];
    for(int i = 1; i < qtd; i++){
        if(med_alunos[i] > maior){
            aluno_maior_med = i;
        }
    }
    fprintf(arq, "\nALUNO COM MAIOR MEDIA:");
    fprintf(arq, "\n%s", alunos[aluno_maior_med].aluno);

    fclose(arq);
}

int main(){
    t_aluno turma[40]; int quant_alunos;
    open_arq("turma.txt", turma, &quant_alunos);
    gera_relatorio(turma, quant_alunos);

    return 0;
}