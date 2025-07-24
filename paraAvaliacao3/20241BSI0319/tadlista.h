#ifndef ___BSI_ED_2023_1___

#define ___BSI_ED_2023_1___

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *t_dado;

typedef struct tipo_noh {
  struct tipo_noh *ant;
  struct tipo_noh *prox;
  t_dado dado;
} *tnoh;

typedef struct {
  int tamlista;
  tnoh prim;
  tnoh ult;
} tcabec;

typedef tcabec *Lista;

int lenLista(Lista lst);
Lista criaLista(void);
Lista appendLista(Lista lst,t_dado dado);
Lista insereLista(Lista lst, t_dado dd, int pos);
t_dado dadoLista(Lista lst, int pos);
t_dado removeLista(Lista lst, int pos);
Lista limpaLista(Lista lst);
Lista destroiLista(Lista lst);

#endif
