#include <stdio.h>
#include <stdlib.h>

typedef struct E{
    int dado;
    struct E *ant;
    struct E *prox;
} no;

typedef struct{
    no *inicio;
    no *fim;
    int tam;
} lista;

lista new_lista(){
    lista *lst = (lista)malloc(sizeof(struct E));
    if(lst != NULL){
        lst -> tam = 0;
        lst -> inicio = NULL;
        lst -> fim = NULL;
    }
    return *lst;
}

int len(lista lst){
    int tam = 0;
    while(lst -> prox != NULL){
        tam++;
    }
    return tam;
}

no append(lista *lst, int valor){
    no *aux = (no*)malloc(sizeof(aux));
    aux -> dado = valor;
    aux -> ant = lst;
    aux -> prox = NULL;
    return aux;
}

int main(){
    lista lst1 = new_lista();
    int tam = len(lst1);
    printf("%d\n", tam);
    append(lst1, 23);
    append(lst1, 44);
    tam = len(lst1);
    printf("%d\n", tam);
    return 0;
}
