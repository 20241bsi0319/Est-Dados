#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct aluno{
    char mat[8];
    char name[64];
    char curso[32];
    float notas[3];
}t_aluno;

t_aluno str2dados(const char *lin){
    t_aluno aux;
    char linha[256];
    strcpy(linha, lin);

    char *mat = strtok(linha, ",");
    strcpy(aux.mat, mat);
    char *name = strtok(NULL, ",");
    strcpy(aux.name, name);
    char *curso = strtok(NULL, ",");
    strcpy(aux.curso, curso);
    for(int i = 0; i < 3; i++){
        char *nota = strtok(NULL, ",");
        aux.notas[i] = atof(nota);
    }

    return aux;
}

void armazena_dados(t_aluno aluno[15], t_aluno vetor, int pos){
    strcpy(aluno[pos].mat, vetor.mat);
    strcpy(aluno[pos].name, vetor.name);
    strcpy(aluno[pos].curso, vetor.curso);
    for(int j = 0; j < 3; j++){
        aluno[pos].notas[j] = vetor.notas[j];
    }
}

void open_arq(char *filename, t_aluno students[15]){
    FILE *arq = fopen(filename, "rt");
    char buffer[256];
    int i = 0;

    while (fgets(buffer, sizeof(buffer), arq) != NULL && i < 15) {
        t_aluno aux = str2dados(buffer);
        armazena_dados(students, aux, i);
        i++;
    }

    fclose(arq);
}

void calcula_med(t_aluno students[15], float medias[15]){
    for(int i = 0; i < 15; i++){
        float num = 0;
        for(int j = 0; j < 3; j++){
            num += students[i].notas[j];
        }
        medias[i] = num / 3;
    }
}

void print_maior_med(t_aluno students[15], float medias[15]){
    float maior = medias[0];
    int aluno = 0;
    for(int i = 0; i < 15; i++){
        if(medias[i] > maior){
            maior = medias[i];
            aluno = i;
        }
    }
    printf("ALUNO COM A MAIOR MEDIA:\n");
    printf("%s, %s, %s, %.2f\n", students[aluno].mat,  students[aluno].name, students[aluno].curso, medias[aluno]);
}

int main(){
    t_aluno alunos[15];
    float medias[15];

    open_arq("alunos.txt", alunos);
    calcula_med(alunos, medias);
    print_maior_med(alunos, medias);

    return 0;
}