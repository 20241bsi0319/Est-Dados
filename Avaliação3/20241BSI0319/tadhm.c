/* ESTE PROJETO DE TAD SEMPRE USARÁ UM FATOR DE CAR IGUAL 0.5 */
#include "tadlista.h"
#include "tadhm.h"

long int fh3(char *s, int d){
  long int soma = 0;
  for(int i=0; i < strlen(s); i++)
    soma = soma * i + s[i]*(i+1);
  return soma % d;
}

t_hashmap cria_hm(){
  t_hashmap hm = malloc(sizeof(struct cabec_hm));
  hm->vet_lista = malloc(sizeof(Lista) * TAM_VET_ARMAZENAM);
  hm->tam_vet_lista = TAM_VET_ARMAZENAM;
  
  for(int i=0; i < TAM_VET_ARMAZENAM; i++)
    hm->vet_lista[i] = NULL;
  return hm;
} // fim cria_hm

t_hashmap cria_hm_tam(int quant_dados){
  // VER OBSERVAÇÃO SOBRE FC NO INÍCIO DO ARQUIVO.
  long tam_vet_armazen = quant_dados/FATOR_DE_CARGA;
  
  t_hashmap hm = malloc(sizeof(struct cabec_hm));
  hm->vet_lista = malloc(sizeof(Lista) * tam_vet_armazen);
  hm->tam_vet_lista = tam_vet_armazen;
  
  for(int i=0; i < tam_vet_armazen; i++)
    hm->vet_lista[i] = NULL;
  return hm;
} // fim cria_hm_tam

t_item getItem(t_hashmap hm,char *k){
  t_item it = NULL;
  long h = fh3(k,hm->tam_vet_lista);  

  if(hm->vet_lista[h] == NULL){
    return NULL;
  }
  else {
    Lista lst = hm->vet_lista[h];
    int i = 0;

    for(i=0;i < lenLista(lst); i++){
      it = dadoLista(lst,i);
      if(strcmp(it->key,k) == 0)
        break; 
    } // for i ..
    
    if(i < lenLista(lst))
      return it;
    else
      return NULL;
  } // else if(hm..
} // fim getItem

t_hashmap addDado(t_hashmap hm,char *k,t_dado dado){
  t_item it;
  
  it = getItem(hm,k);

  if(it == NULL){ // INCLUSÃO DE UMA NOVA CHAVE NA TAB HASHING
    long h = fh3(k,hm->tam_vet_lista);
    it = malloc(sizeof(struct tipo_item));
    it->key = k;
    it->valor = dado;
    
    if(hm->vet_lista[h] == NULL)
      hm->vet_lista[h] = criaLista();
      
    appendLista(hm->vet_lista[h],it);    
  }
  else { // ALTERAÇÃO DO VALOR DE UMA CHAVE JÁ EXISTENTE
    it->valor = dado;    
  } 
  
  return hm; 
} // fim addItem

t_dado getDado(t_hashmap hm,char *k){
  t_item it = getItem(hm,k);
  
  if(it == NULL)
    return NULL;
  else
    return it->valor;
}

Lista keys(t_hashmap hm){
  Lista lst = criaLista();
   
  for(int i=0; i < hm->tam_vet_lista; i++){
    if(hm->vet_lista[i] != NULL){
      for(int j=0; j < lenLista(hm->vet_lista[i]); j++){
        t_item it = dadoLista(hm->vet_lista[i],j);
        appendLista(lst,it->key);       
      }       
    }     
   }
   
   return lst;   
 } // fim keys