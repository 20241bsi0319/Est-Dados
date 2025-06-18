#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tadlista.h"

int main(){
	puts("1. INSERINDO 10 ELEMENTOS SOMENTE NA POSIÇÂO ZERO");
	printf("Lista (insereLista(lst,p,0))\n");

	Lista lst = new_lista();

	for(int i=0; i < 10; i++){
		int *p = (int *)malloc(sizeof(int));
		*p = i + 1;
		insereLista(lst,p,0);
	}


	for(int i=0; i < 10; i++){
		int *p = (int *)elemLista(lst,i);
		printf("%d,",*p);
	}

	printf("\n");

	//------------------------------------------------------------------
	
	puts("\n2. INSERINDO 10 ELEMENTOS NA ÚLTIMA POSIÇÃO DA LISTA");
	printf("Nova Nova Nova lista (insereLista(lst,p,lenLista(lst))\n");

	lst = new_lista();

	for(int i=0; i < 10; i++){
		int *p = (int *)malloc(sizeof(int));
		*p = i + 1;
		insereLista(lst,p,lenLista(lst));
	}

	for(int i=0; i < 10; i++){
		int *p = (int *)elemLista(lst,i);
		printf("%d,",*p);
	}

	printf("\n");

	//-----------------------------------------

	int arraypos[5] = {1,3,5,7,9};

	puts("\n3. INSERINDO 5 ELEMENTOS ENTRE A PRIMEIRA E A ÚLTIMA POSIÇÃO DA LISTA");
	printf("Nova Nova Nova lista (insereLista(lst,p,pos)\n");

	lst = new_lista();

	for(int i=0; i < 10; i++){
		int *p = (int *)malloc(sizeof(int));
		*p = i + 1;
		insereLista(lst,p,lenLista(lst));
	}

	printf("tamanho da lista ANTES (insereLista(lst,p,pos): %d\n",lenLista(lst));
	for(int i=0; i < 5; i++){
		int *p = (int *)malloc(sizeof(int));
		*p = (i + 1) * 100;
		insereLista(lst,p,arraypos[i]);
	}

	for(int i=0; i < lenLista(lst); i++){
		int *p = (int *)elemLista(lst,i);
		printf("%d,",*p);
	}
	printf("\ntamanho da lista DEPOIS de (insereLista(lst,p,pos): %d\n",lenLista(lst));
	
	return 0;
}
