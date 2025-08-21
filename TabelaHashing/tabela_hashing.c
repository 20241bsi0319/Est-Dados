#include <stdio.h>
#include <string.h>

#define TAMANHO_TABELA 10

char *tabela[TAMANHO_TABELA];

int hash(char *str){
    int soma = 0;
    for(int i = 0; str[i] != '\0'; i++){
        soma += str[i] * i;
    }
    return soma % TAMANHO_TABELA;
}

void armazenar_nome(char *nome){
    int indice = hash(nome);
    tabela[indice] = nome;
}

int main(){
    char *nomes[10] = {"Ana", "Joao", "Maria", "Julia", "Marcos", "Sergio", "Lais", "Jose", "Felipe", "Thais"};

    for(int i = 0; i < 10; i++)
        armazenar_nome(nomes[i]);
    
    for(int i = 0; i < TAMANHO_TABELA; i++){
        if(tabela[i] != NULL){
            printf("Indice %d: %s\n", i, tabela[i]);
        }
    }

    // char *palavra = "teste";
    // printf("Hash de %s: %d", palavra, hash(palavra));
    return 0;
}
