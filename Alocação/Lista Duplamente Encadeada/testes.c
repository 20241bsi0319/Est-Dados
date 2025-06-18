#include <stdlib.h>
#include "tadlista.h"

int main() {
    // (teste da função new_lista)
    lista lst = new_lista();
    printf("Tamanho inicial: %d\n", len(lst)); // (Esperado: 0)

    // (teste da função append)
    for(int i = 0; i < 5; i++) {
        append(lst, i);
    }
    printf("Tamanho após append: %d\n", len(lst)); // (Esperado: 5)

    // (teste da função getElem)
    printf("Elemento na posição 3: %d\n", getElem(lst, 3)); // (Esperado: 3)

    // (teste da função insert)
    insert(lst, 2, 99);
    printf("Elemento na posição 2 após insert: %d\n", getElem(lst, 2)); // (Esperado: 99)
    printf("Elemento na posição 3 após insert: %d\n", getElem(lst, 3)); // (Esperado: 2)

    // (teste da função removeElem)
    removeElem(lst, 2);
    printf("Elemento na posição 2 após remoção: %d\n", getElem(lst, 2)); // (Esperado: 2)

    // (teste final do tamanho)
    printf("Tamanho final: %d\n", len(lst)); // (Esperado: 5)

    return 0;
}