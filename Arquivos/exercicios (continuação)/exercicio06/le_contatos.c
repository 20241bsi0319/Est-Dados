#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    char name[64];
    long int tel;
    char email[64];
} t_ctt;

t_ctt str2ctt(const char *lin){
    char str[100];
    strcpy(str, lin);
    char *token = strtok(str, " ");
    char tipo[10] = "name";
    t_ctt aux = {"", 0, ""};

    while(token != NULL){
        if(strcmp(tipo, "name") == 0){
            if(isdigit(token[0])){
                aux.tel = atol(token);
                strcpy(tipo, "email");
            }
            else{
                if(strlen(aux.name) > 0){
                strcat(aux.name, " ");
                }
                strcat(aux.name, token);
                }
            }
        else if(strcmp(tipo, "email") == 0){
            strcpy(aux.email, token);
            }
        token = strtok(NULL, " ");
    }
    return aux;
}

void armazena_conts(t_ctt conts[20], t_ctt txt, int tam){
    strcpy(conts[tam].name, txt.name);
    conts[tam].tel = txt.tel;
    strcpy(conts[tam].email, txt.email);
}

void open_arq(char *filename, t_ctt conts[20], int *size){
    FILE *arq = fopen(filename, "rt");
    t_ctt contato;
    char buffer[100];

    while(fgets(buffer, 99, arq) != NULL){
        buffer[strcspn(buffer, "\n")] = '\0';
        contato = str2ctt(buffer);
        int t = *size;
        armazena_conts(conts, contato, t);
        (*size)++;
    }

    fclose(arq);
}

void pesquisa_nome(t_ctt conts[20], int size){
    char pesq[32];
    printf("Digite o que deseja pesquisar: ");
    scanf("%s", pesq);
    printf("Exibindo resultados para %s:\n", pesq);
    int b = 0; //Verifica se foi encontrado

    for(int i = 0; i < size; i++){
        if (strcmp(pesq, conts[i].name) == 0 || 
            atol(pesq) == conts[i].tel ||
            strcmp(pesq, conts[i].email) == 0){

            printf("\nNome: %s\nTelefone: %li\nE-mail: %s\n",
                    conts[i].name, conts[i].tel, conts[i].email);
                b = 1;
        }
    }
    if(b == 0){
            printf("Nenhum resultado encontrado para '%s'\n", pesq);
        }
}

int main(){
    int tam = 0;
    t_ctt contatos[20];
    open_arq("contatos.txt", contatos, &tam);
    //gera_relatorio();
    pesquisa_nome(contatos, tam);

    return 0;
}