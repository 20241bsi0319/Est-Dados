#ifndef ___BSI_ED_2024_1_LISTA__

#define ___BSI_ED_2024_1_LISTA__

/* PRIVADO: NÃO PODE SER ALTERADO */
typedef void *t_dado;

typedef struct tipo_no {
  t_dado dado;
  struct tipo_no *anterior;
  struct tipo_no *proximo;
} *t_no;

/* PRIVADO: NÃO PODE SER ALTERADO */
typedef struct tipo_lista {
  t_no primeiro;
  t_no ultimo;
  int tamanho;
} *Lista;

/* PÚBLICO: NÃO PODE SER ALTERADO, OS NOMES DAS FUNÇÕES PODEM SER INVOCADOS NA APLICAÇÃO USUÁRIA */
Lista new_lista();
int lenLista(Lista lst);
Lista appendLista(Lista lst, t_dado d);
t_dado elemLista(Lista lst, int pos);
Lista insereLista(Lista lst, t_dado dado, int pos);
t_dado removeLista(Lista lst, int pos);

#endif
