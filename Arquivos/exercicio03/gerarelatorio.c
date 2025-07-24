#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct veiculo{
    char placa[32];
    char marca[32];
    char modelo[32];
    long cpf;
}t_veic;

typedef struct proprietario{
    long cpf;
    char nome[64];
    char email[32];
    long celular;
}t_owner;

typedef t_veic veic[60];
typedef t_owner own[60];

t_veic str2veic(const char *lin){
    char linha[256];
    strcpy(linha, lin);
    t_veic aux;

    char *placa = strtok(linha, ",");
    char *marca = strtok(NULL, ",");
    char *modelo = strtok(NULL, ",");
    char *cpf = strtok(NULL, ",");

    strcpy(aux.placa, placa);
    strcpy(aux.marca, marca);
    strcpy(aux.modelo, modelo);
    aux.cpf = atol(cpf);

    return aux;
}

t_owner str2owner(const char *lin){
    char linha[256];
    strcpy(linha, lin);
    t_owner aux;

    char *cpf = strtok(linha, ",");
    char *nome = strtok(NULL, ",");
    char *email = strtok(NULL, ",");
    char *celular = strtok(NULL, ",");

    aux.cpf = atol(cpf);
    strcpy(aux.nome, nome);
    strcpy(aux.email, email);
    aux.celular = atol(celular);

    return aux;
}

void le_veiculos(char *filename, veic veiculos, int *size){
    FILE *arq = fopen(filename, "rt");
    char buffer[256];
    *size = 0;

    fgets(buffer, 255, arq); //remove cabeçalho
    while(!feof(arq)){
        fgets(buffer, 255, arq);
        veiculos[*size] = str2veic(buffer);
        (*size)++;
    }
    fclose(arq);
}

void le_prop(char *filename, own props, int *size){
    FILE *arq = fopen(filename, "rt");
    char buffer[256];
    *size = 0;

    fgets(buffer, 255, arq); //remove cabeçalho
    while(!feof(arq)){
        fgets(buffer, 255, arq);
        props[*size] = str2owner(buffer);
        (*size)++;
    }
    fclose(arq);
}

void gera_relatorio(veic tabv, own tabp, int sizev, int sizep){
    FILE *arq = fopen("relatorio.txt", "wt");
    fprintf(arq, "\n RELATÓRIO DE PROPRIETÁRIOS E VEÍCULOS");
    for(int i = 0; i < sizep; i++){
        fprintf(arq, "\n ----------------------------------\n");
        fprintf(arq, "\n PROPRIETÁRIO:\n");
            fprintf(arq, "\n Nome             | E-mail\n");
            fprintf(arq, " %-16s | %-26s\n\n", tabp[i].nome, tabp[i].email);
            fprintf(arq, " VEÍCULOS\n");
            fprintf(arq, "\n Placa   | Modelo    | Marca");
        for(int j = 0; j < sizev; j++){
            if(tabp[i].cpf == tabv[j].cpf){
                fprintf(arq, "\n%8s | %-8s  | %-10s", tabv[j].placa, tabv[j].modelo, tabv[j].marca);
            }
        }
        fprintf(arq, "\n");
    }
    fclose(arq);
}

void print_relatorio(veic tabv, own tabp, int sizev, int sizep){
    printf("\n RELATÓRIO DE PROPRIETÁRIOS E VEÍCULOS\n");
    for(int i = 0; i < sizep; i++){
        printf("\n ----------------------------------\n");
        printf("\n PROPRIETÁRIO:\n");
            printf("\n Nome            | E-mail\n");
            printf(" %-15s | %-26s\n\n", tabp[i].nome, tabp[i].email);
            printf(" VEÍCULOS\n");
            printf("\n Placa   | Modelo    | Marca");
        for(int j = 0; j < sizev; j++){
            if(tabp[i].cpf == tabv[j].cpf){
                printf("\n%8s | %-8s  | %-10s", tabv[j].placa, tabv[j].modelo, tabv[j].marca);
            }
        }
        printf("\n");
    }
}

int main(){
    int tamv, tamp;
    veic tab_veic;
    own tab_prop;
    
    le_veiculos("veiculos.txt", tab_veic, &tamv);
    le_prop("proprietarios.txt", tab_prop, &tamp);
    gera_relatorio(tab_veic, tab_prop, tamv, tamp);
    print_relatorio(tab_veic, tab_prop, tamv, tamp);

    return 0;
}