/* PRIVADO: NÃO PODE SER ALTERADO. t_no NÃO PODE SER MENCIONADO PELO USUARIO DO TAD */
typedef void *t_dado;

/* PRIVADO: NÃO PODE SER ALTERADO. t_no NÃO PODE SER MENCIONADO PELO USUARIO DO TAD */
typedef struct tipo_no {
	t_dado dado;
	struct tipo_no *ant;
	struct tipo_no *prox;
} * t_no;

/* PRIVADO: NÃO PODE SER ALTERADO. O TIPO struct tcabec NÃO PODE SER MENCIONADO PELO USUARIO DO TAD */
typedef struct tcabec {
	t_no prim;
	t_no ult;
	int tam;
} * Lista; /* PUBLICO: O TIPO LISTA PODE SER MENCIONADO PELO USUARIO DO TAD */

/* PUBLICO: INTERFACE DO TAD DISPONIVEL PARA O USUARIO DO TAD */
Lista newLista();
int lenLista(Lista lst);
Lista appendLista(Lista lst, t_dado ptr);
t_dado getElem(Lista lst, int pos);
Lista insereLista(Lista lst, int pos, t_dado ptr);
t_dado remLista(Lista lst, int pos);
