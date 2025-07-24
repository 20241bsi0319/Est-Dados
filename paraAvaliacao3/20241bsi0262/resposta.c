#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tadhm.h"

typedef struct {
    char nome[64];
    char simb[10];
    int numAtom;
    double massAtom;
    int numMassa;
} * t_ElemQuimico;

t_hashmap load_tabPeriodica(char *fileName) {
    FILE *arquivo = fopen(fileName, "r");

    t_hashmap tabela = cria_hm();
    char linha[128];

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (linha[strlen(linha) - 1] == '\n')
            linha[strlen(linha) - 1] = '\0';

        char *token = strtok(linha, ",");
        t_ElemQuimico elemento = malloc(sizeof(struct {
            char nome[64];
            char simb[10];
            int numAtom;
            double massAtom;
            int numMassa;
        }));

        strcpy(elemento->nome, token);

        token = strtok(NULL, ",");
        strcpy(elemento->simb, token);

        token = strtok(NULL, ",");
        elemento->numAtom = atoi(token);

        token = strtok(NULL, ",");
        elemento->massAtom = atof(token);

        token = strtok(NULL, ",");
        elemento->numMassa = atoi(token);

        addDado(tabela, elemento->simb, elemento);
    }

    fclose(arquivo);
    return tabela;
}


float massaMolar(char *substancia, t_hashmap tabPeriod) {
    char copia[64], simb[10];
    strcpy(copia, substancia);

    float total = 0;
    char *parte = strtok(copia, ".");

    while (parte != NULL) {
        int i = 0, j = 0;
        int quantidade = 1;

        while (isalpha(parte[i])) {
            simb[j++] = parte[i++];
        }
        simb[j] = '\0';

        if (parte[i] != '\0') {
            quantidade = atoi(&parte[i]);
        }

        t_ElemQuimico e = getDado(tabPeriod, simb);
        if (e != NULL) {
            total += e->massAtom * quantidade;
        }

        parte = strtok(NULL, ".");
    }

    return total;
}

char *tostring(char *substancia, t_hashmap tabPeriod) {
    char copia[64];
    strcpy(copia, substancia);

    char *saida = malloc(1024);
    saida[0] = '\0';

    strcat(saida, substancia);
    strcat(saida, "\n");

    char *parte = strtok(copia, ".");
    char simb[10];

    while (parte != NULL) {
        int i = 0, j = 0;

        while (isalpha(parte[i])) {
            simb[j++] = parte[i++];
        }
        simb[j] = '\0';

        t_ElemQuimico e = getDado(tabPeriod, simb);
        if (e != NULL) {
            char linha[128];
            sprintf(linha, "%s, %s, %d, %.3f u, %d\n", e->nome, e->simb, e->numAtom, e->massAtom, e->numMassa);
            strcat(saida, linha);
        }

        parte = strtok(NULL, ".");
    }

    float m = massaMolar(substancia, tabPeriod);
    char linhaFinal[64];
    sprintf(linhaFinal, "Massa molar da substancia = %.3f g/mol", m);
    strcat(saida, linhaFinal);

    return saida;
}

int main() {
    t_hashmap tabela = load_tabPeriodica("bdtabperiodica.txt");

    FILE *arq = fopen("bdsubstancias.txt", "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo de substâncias.\n");
        return 1;
    }

    char linha[64];

    while (fgets(linha, sizeof(linha), arq)) {
        if (linha[strlen(linha) - 1] == '\n') {
            linha[strlen(linha) - 1] = '\0';
        }

        char *texto = tostring(linha, tabela);
        printf("%s\n\n", texto);
        free(texto);
    }

    fclose(arq);
    return 0;
}
