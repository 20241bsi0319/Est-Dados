#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char id[3];
    char nome[64];
    char categoria[64];
    char marca[64];
    float preco;
    int garantia;
    int qtd_est;
} t_produto;

typedef t_produto t_tab_produto[100];

t_produto str2prod(const char *linha){
    char lin[100];
    strcpy(lin, linha);
    t_produto aux;

    char *id = strtok(lin, ",");
    strcpy(aux.id, id);
    char *nome = strtok(NULL, ",");
    strcpy(aux.nome, nome);
    char *categoria = strtok(NULL, ",");
    strcpy(aux.categoria, categoria);
    char *marca = strtok(NULL, ",");
    strcpy(aux.marca, marca);

    char *preco = strtok(NULL, ",");
    aux.preco = atof(preco);

    char *garantia = strtok(NULL, ",");
    aux.garantia = atoi(garantia);
    char *qtd_est = strtok(NULL, ",");
    aux.qtd_est = atoi(qtd_est);

    return aux;
}

void load_tabela(char *filename, t_tab_produto tab, int *ptam){
    FILE *arq = fopen(filename, "r");
    char buffer[100];
    
    fgets(buffer, sizeof(buffer), arq); //remove cabeçalho
    while(fgets(buffer, sizeof(buffer), arq)){
        tab[*ptam] = str2prod(buffer);
        (*ptam)++;
    }
    fclose(arq);
}

float calc_total(t_produto tabela){
    return tabela.preco * tabela.qtd_est;
}

typedef struct{
    char marca[64];
    float total;
} t_total;

void faz_relatorio(char *filename, t_tab_produto tab, int tam){
    FILE *arq = fopen(filename, "w");

    fprintf(arq, "\nRELATORIO TOTAL EM ESTOQUE (R$)\n");

    int maior = 0, menor = 0;
    float maior_est, menor_est;
    t_total tabela[tam];
    int tam2 = 0;

    for(int i = 0; i < tam; i++){
        float total = calc_total(tab[i]);
        if(strcmp(tabela[i].marca, tab[i].marca) == 0){
            continue;
        }
        else{
            strcpy(tabela[i].marca, tab[i].marca);
            tam2++;
        }
        tabela[i].total += total;

        if(total > calc_total(tab[maior])){
            maior_est = total;
            maior = i;
        }
        if(total < calc_total(tab[menor])){
            menor_est = total;
            menor = i;
        }
    }

    for(int i = 0; i < tam2; i++){
        fprintf(arq, "\n%-15s %10.2f", tabela[i].marca, tabela[i].total);
    }

    fprintf(arq, "\nMAIOR TOTAL EM ESTOQUE: %s, %.2f", tab[maior].marca, maior_est);
    fprintf(arq, "\nMENOR TOTAL EM ESTOQUE: %s, %.2f", tab[menor].marca, menor_est);

    fclose(arq);
}

int main(){
    t_tab_produto tabelaProd;
    int size = 0;
    load_tabela("tabti.txt", tabelaProd, &size);
    faz_relatorio("relat1.txt", tabelaProd, size);

    return 0;
}