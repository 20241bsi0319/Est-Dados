/* ESTE PROJETO DE TAD SEMPRE USARÁ UM FATOR DE CAR IGUAL 0.5 */
#include "tadlista.h"

#define TAM_VET_ARMAZENAM 1024
#define FATOR_DE_CARGA 0.5

typedef struct cabec_hm {
  // VETOR DE LISTAS, LISTAS DE NÓS DE t_item.
  Lista *vet_lista; 
  long tam_vet_lista;
} *t_hashmap; 

typedef struct tipo_item {
    char *key;
    t_dado valor;  
    // DADO DA APLICAÇÃO, APLICAÇÃO QUE SEMPRE DESCONHECE 
    // OS MECANISMOS INTERNOS DO HASH MAP.
} *t_item;

t_hashmap cria_hm();
t_hashmap cria_hm_tam(int quant_dados);
t_hashmap addDado(t_hashmap hm,char *k,t_dado dado);
t_dado getDado(t_hashmap hm,char *k);
Lista keys(t_hashmap hm);




