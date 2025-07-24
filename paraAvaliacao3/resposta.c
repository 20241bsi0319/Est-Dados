#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> // para usar  o isalpha()
#include "tadhm.h"

typedef struct{
    char nome[64];
    char simb[10];
    int numAtom;
    double massAtom;
    int numMassa;
} * t_ElemQuimico;

t_hashmap load_tabPeriodica(char *filename){
    FILE *arq = fopen(filename, "r");
    char buffer[64];
    t_hashmap hm = cria_hm();
    t_ElemQuimico elem;

    while (fgets(buffer, 63, arq) != NULL) {
        if(buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';

        elem = (t_ElemQuimico)malloc(sizeof(*elem));

        char * token = strtok(buffer, ",");
        strcpy(elem->nome, token);

        token = strtok(NULL, ",");
        strcpy(elem->simb, token);

        token = strtok(NULL, ",");
        elem->numAtom = atoi(token);

        token = strtok(NULL, ",");
        elem->massAtom = atof(token);

        token = strtok(NULL, ",");
        elem->numMassa = atoi(token);

        addDado(hm, elem->simb, elem);
    }

    fclose(arq);
    return hm;
}

float massaMolar(char *substancia, t_hashmap tabPeriod){
    char buffer[32];
    strcpy(buffer, substancia);
    float massaMol = 0;
    char simbol[10];

    char * token;
    token = strtok(buffer, ".");
    while(token != NULL){
        int coef = 1;
        int j = 0;
        for(int i = 0; i < strlen(token); i++){
            if(isalpha(token[i])){
                simbol[j++] = token[i];
            }
            else{
                simbol[j] = '\0';
                coef = atoi(&token[i]);
                break;
            }
        }
        simbol[j] = '\0'; // garantir o fim da string

        t_ElemQuimico elem = getDado(tabPeriod, simbol);
        if (elem != NULL) {
            massaMol += elem->massAtom * coef;
        }

        token = strtok(NULL, ".");
    }
    return massaMol;
}

char *tostring(char *substancia, t_hashmap tabPeriod){
    char buffer[64];
    strcpy(buffer, substancia);

    char *strSub = (char *)malloc(1024); // alocação dinâmica
    strSub[0] = '\0'; // inicializa como string vazia

    strcat(strSub, substancia);
    strcat(strSub, "\n");

    char *token = strtok(buffer, ".");
    char simbol[10];

    while(token != NULL){
        int i = 0, j = 0;
        while (isalpha(token[i])) {
            simbol[j++] = token[i++];
        }
        simbol[j] = '\0';

        t_ElemQuimico elem = (t_ElemQuimico)getDado(tabPeriod, simbol);
        if (elem != NULL) {
            char linha[128];
            snprintf(linha, sizeof(linha), "%s, %s, %d, %.3f u, %d\n",
                     elem->nome, elem->simb, elem->numAtom, elem->massAtom, elem->numMassa);
            strcat(strSub, linha);
        }

        token = strtok(NULL, ".");
    }

    float massa = massaMolar(substancia, tabPeriod);
    char massaStr[64];
    snprintf(massaStr, sizeof(massaStr), "Massa molar da substancia = %.3f g/mol", massa);
    strcat(strSub, massaStr);

    return strSub;
}

int main(){
    t_hashmap tabPeriod = load_tabPeriodica("bdtabperiodica.txt");

    FILE *arqSubst = fopen("bdsubstancias.txt", "r");

    char linha[64];
    while(fgets(linha, sizeof(linha), arqSubst)){
        if(linha[strlen(linha)-1] == '\n'){
            linha[strlen(linha)-1] = '\0';
        }

        char *resposta = tostring(linha, tabPeriod);
        printf("%s\n\n", resposta);
    }

    fclose(arqSubst);
    return 0;
}
