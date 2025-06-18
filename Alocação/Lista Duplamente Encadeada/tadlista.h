#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int dado;
    struct No *ant;
    struct No *prox;
} * t_no; // (ponteiro para a struct nó)

typedef struct tcabec{
    int tam;
    t_no prim;
    t_no ult;
} * lista; // (ponteiro para a struct tcabec)

lista new_lista();
lista append(lista lst, int valor);
lista insert(lista lst, int pos, int valor);
lista removeElem(lista lst, int pos);
int getElem(lista lst, int pos);
int len(lista lst);