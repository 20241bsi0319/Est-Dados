#include <stdio.h>
#include <stdlib.h>

typedef struct residente{
    long rg;
    char nome[64];
    int age;
    char prof[64];
}t_pessoas;

typedef struct residencia{
    int num;
    int rooms;
    int gar;
    t_pessoas pessoa[5];
}t_casas;

t_casas str4house(char *lin){
    t_casas aux;
    //char linha[256];
    //strcpy(linha, lin);

    char *num = strtok(*lin, ',');
    char *rooms = strtok(NULL, ',');
    char *gar = strtok(NULL, ',');

    aux.num = atoi(num);
    aux.rooms = atoi(rooms);
    aux.gar = atoi(gar);

    return aux;
}

t_pessoas str2ppl(const char *lin){
    t_pessoas aux;
    char linha[256];
    strcpy(linha, lin);

    char *rg = strtok(linha, ',');
    char *nome = strtok(NULL, ',');
    char *age = strtok(NULL, ',');
    char *prof = strtok(NULL, ',');

    aux.rg = atoli(rg);
    strcpy(aux.nome, nome);
    aux.age = atoi(age);
    strcpy(aux.prof, prof);

    return aux;
}

void gera_condominio(char *filename, t_pessoas pessoa, t_casas casa, int *size){
    FILE *arq = fopen(filename, "rt");
    *size = 0;
    char buffer[256];
    fgets(buffer, 255, arq); //remove cabeçalho

    while(fgets(buffer, 255, arq) && size < 5){
        pessoa = str2ppl(&buffer);
        casa = str4house(buffer);
    }

    fclose(arq);
}

//void gera_condominio(char *filename, t_casas casa){

}

int main(){

    open_arq();
    print_relatorio();

    return 0;
}