#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct produto{
    int id;
    char nome[64];
    char fab[64];
    float preco;
    int quant;
} prod;

typedef prod tabela[10]; 

prod str2prod(const char *frs){
    prod aux;
    char linha[64];
    strcpy(linha, frs);

    char *id = strtok(linha, ",");
    char *nome = strtok(NULL, ",");
    char *fab = strtok(NULL, ",");
    char *preco = strtok(NULL, ",");
    char *quant = strtok(NULL, ",");

    aux.id = atoi(id);
    strcpy(aux.nome, nome);
    strcpy(aux.fab, fab);
    aux.preco = atof(preco);
    aux.quant = atoi(quant);

    return aux;
}

void open_arq(char *filename, tabela tab, int *size){
    FILE *arq = fopen(filename, "rt");
    if(!arq){ //confere se o arquivo possui conteúdo
        return;
    }

    char buffer[256];
    *size = 0;

    fgets(buffer, 255, arq); //remove o cabeçalho

    while(fgets(buffer, 255, arq) && *size < 10){
        tab[*size] = str2prod(buffer); //quebra a linha e transforma em um produto
        (*size)++; //atualiza o tamanho da tabela

    }

    fclose(arq);
}

void print_tab(tabela tab, int size){
    printf("\nTABELA DE PRODUTOS:\n");
    printf(" ID | NOME                      | FABRICANTE | PREÇO     | QTD\n");
    printf("-------------------------------------------------------------\n");
    
    for(int i = 0; i < size; i++){
        printf("%2d  | %-25s | %-10s | R$%8.2f | %3d\n",
        tab[i].id, tab[i].nome, tab[i].fab, tab[i].preco, tab[i].quant);
    }
}

int mais_caro(tabela tab, int size){
    int maisCaro = 0;
    for(int i = 0; i < size; i++){
        if(tab[i].preco > tab[maisCaro].preco){
            maisCaro = i;
        }
    }
    return maisCaro;
}

int maior_est(tabela tab, int size){
    int maior = 0;

    for(int i = 0; i < size; i++){
        if(tab[i].quant > tab[maior].quant){
            maior = i;
        }
    }
    return maior;
}

void gera_relatorio(tabela tab, int size){
    FILE *arq = fopen("relatorio.txt", "wt");

    //tabela completa
    fprintf(arq, "\nRELATÓRIO DE PRODUTOS:\n");
    fprintf(arq, " ID | NOME                      | FABRICANTE | PREÇO      | QTD\n");
    fprintf(arq, "-------------------------------------------------------------\n");
    
    for(int i = 0; i < size; i++){
        fprintf(arq, "%2d  | %-25s | %-10s | R$%8.2f | %3d\n",
        tab[i].id, tab[i].nome, tab[i].fab, tab[i].preco, tab[i].quant);
    }

    //produto mais caro
    int caro = mais_caro(tab, size);
    fprintf(arq, "\nPRODUTO MAIS CARO:\n");
    fprintf(arq, "\n%s (R$%.2f)\n",tab[caro].nome, tab[caro].preco);

    //produto maior quantidade
    int maior = maior_est(tab, size);
    fprintf(arq, "\nPRODUTO DE MAIOR QUANTIDADE:\n");
    fprintf(arq, "\n%s (%d)\n", tab[maior].nome, tab[maior].quant);
}

int main(){
    tabela produtos;
    int tam;

    open_arq("tabela.txt", produtos, &tam);
    print_tab(produtos, tam);
    gera_relatorio(produtos, tam);

    return 0;
}