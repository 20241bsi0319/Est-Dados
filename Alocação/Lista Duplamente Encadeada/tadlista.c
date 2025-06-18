#include <stdlib.h>
#include "tadlista.h"

lista new_lista(){
    lista aux = (lista)malloc(sizeof(struct tcabec));
    aux -> tam = 0; // (inicializa lista com 0 elementos)
    aux -> prim = NULL;
    aux -> ult = NULL;
    
    return aux;
}

int len(lista lst){
    return lst -> tam; // (retorna o tamanho da lista)
}

lista append(lista lst, int valor){
    t_no aux = (t_no)malloc(sizeof(struct No));
    aux -> dado = valor;
    aux -> prox = NULL;

    if(lst -> tam > 0){ // (confere se a lista possui elementos)
        aux -> ant = lst -> ult;
        lst -> ult -> prox = aux;
    }
    else{ // (adiciona o valor numa lista vazia)
        aux -> ant = NULL;
        lst -> prim = aux;
    }
    lst -> ult = aux;
    lst -> tam++;
    return lst;
}

lista insert(lista lst, int pos, int valor){
    if(pos < 0 || pos > lst -> tam){ // (não aceita posições que não existem na lista)
        return lst;
    }

    t_no novo = (t_no)malloc(sizeof(struct No));
    novo -> dado = valor;
    novo -> ant = NULL;
    novo -> prox = NULL;

    if(pos == 0){ // (insere na posição inicial)
        novo -> prox = lst -> prim;
        if(lst -> tam > 0){ // (confere se a lista possui elementos)
            lst -> prim -> ant = novo;
        }    
        else{ // (adiciona o valor numa lista vazia)
            lst -> ult = novo;
        }
        lst -> prim = novo;
    }
    else if(pos == lst -> tam){ // (insere na posição final)
        novo -> ant = lst -> ult;
        if(lst -> tam > 0){ // (confere se a lista possui elementos)
            lst -> ult -> prox = novo;
        }
        else{ // (adiciona o valor numa lista vazia)
            lst -> prim = novo; 
        }
        lst -> ult = novo; 
    }
    else{ // (insere em qualquer outra posição)
        t_no aux = lst -> prim;

        for(int i = 0; i < pos; i++)
            aux = aux -> prox;
        
        novo -> ant = aux -> ant;
        novo -> prox = aux;
        aux -> ant -> prox = novo;
        aux -> ant = novo;
    }
    lst -> tam++;
    return lst;
}

lista removeElem(lista lst, int pos){
    if(pos < 0 || pos >= lst -> tam || lst -> tam == 0){
        return lst;
    }

    t_no aux;

    if(pos == 0){ // (confirma se é o primeiro elemento)
        aux = lst -> prim;
        lst -> prim = aux -> prox;
        lst -> prim -> ant = NULL;
    }
    else if(pos == lst -> tam - 1){  // (confirma se é o último elemento)
        aux = lst -> ult;
        lst -> ult = lst -> ult -> ant;
        lst -> ult -> prox = NULL;
    }
    else{  // (cornfirma que é outro elemento)
        aux = lst -> prim;

        for(int i = 1; i < pos; i++){
            aux = aux -> prox;
        }
        aux -> ant -> prox = aux -> prox;
        aux -> prox -> ant = aux -> ant;
    }
    free(aux); // (limpa o conteúdo do nó)
    aux = NULL; // (apaga o nó)
    lst -> tam--;
    return lst;
}

int getElem(lista lst, int pos){
    t_no cursor = lst -> prim;

    for(int i = 0; i < pos; i++){ // (anda até a posição desejada)
        cursor = cursor -> prox;
    }
    return cursor -> dado; // (retorna o dado)
}