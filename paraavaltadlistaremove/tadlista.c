#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tadlista.h"

Lista new_lista() {
  Lista l = (Lista)malloc(sizeof(struct tipo_lista));
  l->primeiro = NULL;
  l->ultimo = NULL;
  l->tamanho = 0;
  return l;
}

int lenLista(Lista l) { return l->tamanho; }

Lista appendLista(Lista l, t_dado d) {
  t_no no = (t_no)malloc(sizeof(struct tipo_no));
  no->dado = d;
  no->anterior = NULL;
  no->proximo = NULL;

  if (l->tamanho == 0) {
    l->primeiro = no;
    l->ultimo = no;
  } else {
    l->ultimo->proximo = no;
    no->anterior = l->ultimo;
    l->ultimo = no;
  }
  l->tamanho++;

  return l;
}

t_dado elemLista(Lista l, int pos) {
  t_no aux;
  int cont = 0;

  if ((pos >= 0) && (pos < l->tamanho) && (l->tamanho > 0)) {
    aux = l->primeiro;
    for (cont = 0; cont < pos; cont++) {
      aux = aux->proximo;
    }
    return aux->dado;
  } else
    return NULL;
}

t_dado removeLista(Lista l, int pos) {
  ??????????????????????????

}  // fim removeLista
