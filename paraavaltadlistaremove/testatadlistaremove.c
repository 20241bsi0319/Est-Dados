#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tadlista.h"

int main(){
	Lista lst = new_lista();

	puts("1. INSERINDO 10 ELEMENTOS VIA APPEND");
	printf("Nova Nova lista (appendLista(lst,p))\n");
	printf("tamanho da lista ANTES (appendLista(lst,p): %d\n",lenLista(lst));	

	for(int i=0; i < 10; i++){
		int *p = (int *)malloc(sizeof(int));
		*p = i + 1;
		appendLista(lst,p);
	}

	for(int i=0; i < 10; i++){
		int *p = (int *)elemLista(lst,i);
		printf("%d,",*p);
	}
	printf("tamanho da lista DEPOIS (appendLista(lst,p): %d\n",lenLista(lst));

	//destroiLista(lst);-----------------------
	puts("\n2. REMOVENDO 10 ELEMENTOS SOMENTE USANDO A POSIÇÂO ZERO");
	printf("tamanho da lista ANTES de removeLista: %d\n",lenLista(lst));

	for(int i=0; i < 10; i++){
		int *p = (int *)removeLista(lst,0);
		free(p);
	}

	printf("tamanho da lista DEPOIS de removeLista: %d\n",lenLista(lst));

	free(lst);
	//-----------------------------------------
	
	puts("\n3. INSERINDO 10 ELEMENTOS VIA APPEND");
	printf("Nova lista (appendLista(lst,p))\n");

	lst = new_lista();

	for(int i=0; i < 10; i++){
		int *p = (int *)malloc(sizeof(int));
		*p = i + 1;
		appendLista(lst,p);
	}

	for(int i=0; i < 10; i++){
		int *p = (int *)elemLista(lst,i);
		printf("%d,",*p);
	}

	printf("\n");


	//destroiLista(lst);-----------------------
	puts("\n4. REMOVENDO 10 ELEMENTOS SOMENTE USANDO A ÚLTIMA POSIÇÃO DA LISTA");
	printf("tamanho da lista ANTES de removeLista(lst,lenLista(lst)-1): %d\n",lenLista(lst));

	for(int i=0; i < 10; i++){
		int *p = (int *)removeLista(lst,lenLista(lst)-1);
		free(p);
	}

	printf("tamanho da lista DEPOIS de removeLista(lst,lenLista(lst)-1): %d\n",lenLista(lst));

	free(lst);
	//-----------------------------------------

	puts("\n5. INSERINDO 20 ELEMENTOS VIA APPEND");
	printf("Nova lista (appendLista(lst,p))\n");

	lst = new_lista();

	for(int i=0; i < 20; i++){
		int *p = (int *)malloc(sizeof(int));
		*p = i + 1;
		appendLista(lst,p);	}


	for(int i=0; i < 20; i++){
		int *p = (int *)elemLista(lst,i);
		printf("%d,",*p);
	}

	printf("\n");

	//destroiLista(lst);-----------------------
	puts("\n6. REMOVENDO 5 ELEMENTOS ENTRE A PRIMEIRA E A ÚLTIMA POSIÇÃO: POSIÇÔES 1,3,5,7,9");
	printf("tamanho da lista ANTES removeLista(lst,pos): %d\n",lenLista(lst));

	int arraypos[5] = {1,3,5,7,9};
	
    puts("\nLISTA ANTES DA REMOÇÃO");
    for(int i=0; i < lenLista(lst); i++){
		int *p = (int *)elemLista(lst,i);
		printf("%d,",*p);
	}


	for(int i=0; i < 5; i++){
		int *p = (int *)removeLista(lst,arraypos[i]);
		free(p);
	}

	puts("\n\nLISTA DEPOIS DA REMOÇÃO DAS POSIÇÔES 1,3,5,7,9");
	for(int i=0; i < lenLista(lst); i++){
		int *p = (int *)elemLista(lst,i);
		printf("%d,",*p);
	}

	printf("\n\ntamanho da lista DEPOIS de aplicar removeLista(lst,pos): %d\n",lenLista(lst));

	free(lst);	

	printf("\n");
	
	return 0;
}
