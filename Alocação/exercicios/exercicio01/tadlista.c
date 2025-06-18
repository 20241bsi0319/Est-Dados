#include <stdio.h>
#include <stdlib.h>

typedef struct E{
    int dado;
    struct E *ant;
    struct E *prox;
    int tam;
} *lista;

lista new_lista(){
    lista lst = (lista)malloc(sizeof(struct E));
    if(lst != NULL){
        lst -> dado = 0;
        lst -> ant = NULL;
        lst -> prox = NULL;
    }
    return lst;
}

int len(lista lst){
    int tam = 0;
    while(lst -> prox != NULL){
        tam++;
    }
    return tam;
}

lista append(lista lst, int valor){
    lista no = (lista)malloc(sizeof(struct E));
    no -> dado = valor;
    no -> ant = lst;
    no -> prox = NULL;
    return no;
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