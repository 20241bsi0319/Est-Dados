#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tadlista.h"

// Compilar com
// gcc -c -I./osehs tadlista.c -Wall

Lista criaLista(void){
  Lista lst = NULL;
  lst = (tcabec *)malloc(sizeof(tcabec));
  lst->tamlista = 0;
  lst->prim = NULL;
  lst->ult = NULL;
  return lst;
}

int lenLista(Lista lst){
  return lst->tamlista;
}

Lista appendLista(Lista lst,t_dado dado){
  tnoh nohnovo = (tnoh)malloc(sizeof(struct tipo_noh));
  nohnovo->dado = dado;
  
  if(lst->tamlista == 0){
    nohnovo->ant = NULL;
    nohnovo->prox = NULL;    

    lst->prim = nohnovo;
    lst->ult = nohnovo;    
  }
  else {
    lst->ult->prox = nohnovo;
    nohnovo->ant = lst->ult;
    nohnovo->prox = NULL;
    lst->ult = nohnovo;    
  }
  
  lst->tamlista++;
  
  return lst;  
}

Lista insereLista(Lista lst, t_dado dd, int pos){
  if((pos < 0) || (pos > lst->tamlista)) return lst;
  
  if((lst->tamlista == 0) || (pos == lst->tamlista))
    appendLista(lst,dd);
  else {
    tnoh nohnovo = (tnoh)malloc(sizeof(struct tipo_noh));
    nohnovo->dado = dd;
    
    if(pos == 0){ // INSERINDO NA POSIÇÃO ZERO.
      nohnovo->ant = NULL;
      nohnovo->prox = lst->prim;
      lst->prim->ant = nohnovo;
      lst->prim = nohnovo;      
    }
    else {// INSERINDO EM QUALQUER POSIÇÃO ENTRE ZERO E A ÚLTIMA.      
        // POSICIONANDO NO NÓ pos
        tnoh aux = lst->prim;    
        for(int i=0; i < pos; i++)
          aux = aux->prox;
          
        // INSERINDO NOVO NÓ.
        nohnovo->prox = aux;
        nohnovo->ant = aux->ant;
        aux->ant = nohnovo;
        nohnovo->ant->prox = nohnovo;
    }
    
    lst->tamlista++;
  }
  return lst;  
}

t_dado dadoLista(Lista lst, int pos){
  if((pos < 0) || (pos >= lst->tamlista)) return NULL;
  
  tnoh aux = lst->prim;    
  for(int i=0; i < pos; i++)
    aux = aux->prox;
    
  return aux->dado;  
}

t_dado removeLista(Lista lst, int pos){
  if((pos < 0) || (pos >= lst->tamlista)) return NULL;

  t_dado bkp;
  
  if(lst->tamlista == 1){ // LISTA COM APENAS 1 ELEMENTO.
    bkp = lst->prim->dado;
    free(lst->prim);
    lst->prim = NULL;
    lst->ult = NULL;
  }
  else 
     if(pos == 0) { // PRIMEIRO MAS NÃO ÚNICO
        bkp = lst->prim->dado;
        lst->prim = lst->prim->prox;
        free(lst->prim->ant);
        lst->prim->ant = NULL;
      }
      else // ÚLTIMO MAS NÃO O ÚNICO
         if(pos == lst->tamlista - 1){ 
            bkp = lst->ult->dado;
            lst->ult = lst->ult->ant;
            free(lst->ult->prox);
            lst->ult->prox = NULL;
         }
         else {// NEM O PRIMEIRO NEM O ÚLTIMO
           tnoh aux = lst->prim;    
           for(int i=0; i < pos; i++)
             aux = aux->prox;
            
           tnoh antes = aux->ant; 
           tnoh depois = aux->prox; 
           bkp = aux->dado;
           
           antes->prox = depois;
           depois->ant = antes;
           
           free(aux);  
         }

  lst->tamlista--;
  return bkp;
}

Lista limpaLista(Lista lst){
  t_dado d;

  if(lst->tamlista > 0){
    int tam = lst->tamlista;
    for(int i=0; i < tam; i++){
      d = removeLista(lst,0);
      if(d != NULL)
        free(d);
    }
  }
  
  return lst;
}

Lista destroiLista(Lista lst){
  limpaLista(lst);

  return NULL;
}
