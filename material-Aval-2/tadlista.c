#include "tadlista.h"
#include <stdlib.h>
#include <stdio.h>

Lista newLista(){
	Lista aux = (struct tcabec *)malloc(sizeof(struct tcabec));
	aux->tam = 0;
	aux->prim = NULL;
	aux->ult = NULL;
	return aux;
}

int lenLista(Lista lst){
	return lst->tam;
}

Lista appendLista(Lista lst, t_dado ptr){
	t_no aux = (struct tipo_no *)malloc(sizeof(struct tipo_no));
	aux->dado = ptr;
	aux->prox = NULL;

	if(lst->tam > 0){
		aux->ant = lst->ult;
		lst->ult->prox = aux;
		lst->ult = aux;
	}
	else { // tam igual a zero, lista vazia
		aux->ant = NULL;
		lst->prim = aux;
		lst->ult = aux;
	}
	lst->tam++;
	return lst;
}

t_dado getElem(Lista lst, int pos){
	if((pos < 0) || (pos >= lst->tam) || (lst->tam == 0)) return NULL;
	
	t_no cursor = lst->prim;
	for(int i=0; i < pos; i++){
		cursor = cursor->prox;
	}
	return cursor->dado;
}

Lista insereLista(Lista lst, int pos, t_dado ptr){
    if((pos < 0) || (pos > lst->tam)) return lst;

	t_no novo_no = (struct tipo_no *)malloc(sizeof(struct tipo_no));
	novo_no->dado = ptr;

	if(lst->tam == 0)
		lst = appendLista(lst, ptr);
	else 
		if(pos == lst->tam)
			lst = appendLista(lst, ptr);
		else {
			if(pos == 0){ // lista não vazia e inicio da lista
				novo_no->ant = NULL;
				novo_no->prox = lst->prim;
				lst->prim->ant = novo_no;
				lst->prim = novo_no;
		    }
		    else { // inserir entre a posição 1 e a ultima, inclusive.
		    	t_no cursor = lst->prim;    // salta até a posição pos
				for(int i=0; i < pos; i++){
					cursor = cursor->prox;
				}

				novo_no->prox = cursor;     // costura o novo nó
				novo_no->ant = cursor->ant;

				novo_no->ant->prox = novo_no; // constura o anterior e o 
				cursor->ant = novo_no;        // próximo ao novo nó
		    }
		    lst->tam = lst->tam + 1; // ou lst->tam++;
		}
	return lst;
}

t_dado remLista(Lista lst, int pos){
	if((pos < 0) || (pos >= lst->tam) || (lst->tam == 0)) return NULL;

	t_no alvo;
	t_dado salva_dado;

	if(pos == 0){
	   alvo = lst->prim;
       salva_dado = alvo->dado;

       if(lst->tam > 1){
       	lst->prim = alvo->prox;
       	lst->prim->ant = NULL;
       }
       else { // tam == 1. tam < 1 já foi ratado no primeiro if linha 80
       	alvo = lst->prim;
       	salva_dado = alvo->dado;

       	lst->prim = NULL;
       	lst->ult = NULL;
       }

       free(alvo);
       lst->tam--;
       return salva_dado;
    }
    else { // lista com mais de 1 elemento
    	if(pos == lenLista(lst)-1){ // remover ultima posição da lista
    		alvo = lst->ult;
            salva_dado = alvo->dado;
    		alvo->ant->prox = NULL;
    		lst->ult = alvo->ant;

    		free(alvo);
		    lst->tam--;
		    return salva_dado;
		}
		else {  // qualquer elemento entre o segundo e o penultimo, inclusive.
			alvo = lst->prim;    // salta até a posição pos
			for(int i=0; i < pos; i++){
				alvo = alvo->prox;
			}
			salva_dado = alvo->dado;
			t_no antes = alvo->ant;
			t_no depois = alvo->prox;

			antes->prox = depois;
			depois->ant = antes;

			free(alvo);
		    lst->tam--;
		    return salva_dado;
		}
    }
} // fim remLista