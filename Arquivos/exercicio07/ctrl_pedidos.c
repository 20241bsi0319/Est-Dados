#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    int idC;
    char name[32];
    long int tel;
} tcliente;

typedef struct{
    int idP;
    int idC;
    float valorT;
} tpedido;

tcliente str2cliente(const char *linha){
    char lin[100];
    strcpy(lin, linha);
    tcliente aux;

    char *id = strtok(lin, " ");
    aux.idC = atoi(id);

    char *name = strtok(NULL, " ");
    strcpy(aux.name, name);

    char *tel = strtok(NULL, " ");
    aux.tel = atol(tel);

    return aux;
}

void open_clientes(char *filename, tcliente clientes[10], int *tam){
    FILE *arq = fopen(filename, 'r');
    char buffer[100];
    *tam = 0;

    while(fgets(buffer, sizeof(buffer), arq)){
        clientes[*tam] = str2cliente(buffer);
        (*tam)++;
    }
    fclose(arq);
}

tpedido str2pedido(const char *linha){
    char lin[100];
    strcpy(lin, linha);
    tpedido aux;

    char *idP = strtok(lin, " ");
    aux.idP = atoi(idP);

    char *idC = strtok(NULL, " ");
    aux.idC = atoi(idC);

    char *valorT = strtok(NULL, " ");
    aux.valorT = atof(valorT);

    return aux;
}

void open_pedidos(char *filename, tpedido pedidos[30], int *tam){
    FILE *arq = fopen(filename, 'r');
    char buffer[100];
    *tam = 0;

    while(fgets(buffer, sizeof(buffer), arq)){
        pedidos[*tam] = str2pedido(buffer);
        (*tam)++;
    }
    fclose(arq);
}

int mais_comprou(tpedido pedidos[], int tam){
    int mais = pedidos[0].idC;

    for(int i = 0; i < tam; i++){
        for(int j = 0; j < 3; j++){
            if(pedidos[i].){

            }
        }
    }
}

int main(){
    tcliente rclientes[10];
    tpedido rpedidos[30];
    int sizeC;
    int sizeP;
    open_clientes("clientes.txt", rclientes, &sizeC);
    open_pedidos("pedidos.txt", rpedidos, &sizeP);
    gera_relatorio();

    return 0;
}