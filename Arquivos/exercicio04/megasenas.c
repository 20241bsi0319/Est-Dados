#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int dezenas[60];

void str2sort(const char *lin, int aux[6]){
    char linha[20];
    strcpy(linha, lin);

    char *dezena = strtok(linha, " ");
    for(int i = 0; i < 6; i++){
        aux[i] = atoi(dezena);
        dezena = strtok(NULL, " ");
    };
}

void armazena_num(dezenas *sort, int vetor[6]){
    for(int j = 0; j < 6; j++){
        int dezena = vetor[j];
        if(dezena >= 1 && dezena <= 60){
            (*sort)[dezena - 1]++;
        }
    }
}

void open_arq(char *filename, dezenas *sorteadas){
    FILE *arq = fopen(filename, "rt");
    char buffer[20];
    int aux[6];

    while(!feof(arq)){
        fgets(buffer, 19, arq);
        str2sort(buffer, aux);
        armazena_num(sorteadas, aux);
    }
    fclose(arq);
}

void print_sorteados(dezenas sorteadas){
    printf(" RELATÓRIO DE FREQUÊNCIA DE NÚMEROS SORTEADOS NA MEGASENA DE 2024:\n");
    printf("\n NÚMERO  | FREQUÊNCIA");
    printf("\n ---------------------");
    for(int i = 0; i < 60; i++){
        printf("\n    %-4d |    %-2d", i + 1, sorteadas[i]);
    }
}   

void gera_relatorio(dezenas sorteadas){
    FILE *arq = fopen("relatorio.txt", "wt");
    fprintf(arq, " RELATÓRIO DE FREQUÊNCIA DE NÚMEROS SORTEADOS NA MEGASENA DE 2024:\n");
    fprintf(arq, "\n NÚMERO | FREQUÊNCIA");
    fprintf(arq, "\n ---------------------");
    for(int i = 0; i < 60; i++){
        fprintf(arq, "\n    %-4d |    %-2d", i + 1, sorteadas[i]);
    }
    fclose(arq);
}   

int main(){
    dezenas num_sorteados = {0};
    open_arq("bdmegasena2024.txt", &num_sorteados);
    print_sorteados(num_sorteados);
    gera_relatorio(num_sorteados);

    return 0;
}