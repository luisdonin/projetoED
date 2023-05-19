#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FE.h"
#include "PE.h";


#define MAX 100
typedef struct{
        char *nome[MAX];
        int length;
        int ep;
      
}serie;





void compareStrings(fila* f, char* S, serie *anime, pilhaEstatica *pilha) {
    char S_compare_start[] = "comeca", S_compare_download[] = "download", S_compare_assiste[] = "assiste", S_compare_fila[] = "fila";
    //serie anime;
    int numero_eps=0;


    if (strcmp(S, S_compare_start) == 0) {
        scanf("%s %d", anime->nome[0], &anime->ep);
        printf("comecando %s %d\n", anime->nome[0], anime->ep);
        push(pilha, anime->nome[0]);
    }   

    if (strcmp(S, S_compare_download) == 0) {
        printf("%s\n", pilha->data[pilha->topo]);
        scanf("%d %d", &anime->ep, &anime->length);
        printf("%d episodios de %s baixados\n", anime->ep, pilha->data[pilha->topo]);
        insere(f, anime->ep);
       
    }

    if (strcmp(S, S_compare_assiste) == 0) {
        scanf("%d", &numero_eps);
        printf("%d eps de %s assistidos (%d minutos)\n", numero_eps, pilha->data[pilha->topo], (anime->length*numero_eps));
        if(anime->length*numero_eps >= 0){
            pop(pilha);
            removeNodo(f);
        }
    }

    if(strcmp(S, S_compare_fila)==0){
        printNodes(f);
    }

}

int main() {
    fila f;
    criaFila(&f);
    pilhaEstatica pilha;
    criaPilha(&pilha);
    serie anime;
    anime.nome[0] = malloc(MAX * sizeof(char));
    char S[6], S_compare_exit[] = "f";

    while (1) {
        scanf("%s", S);
        if (strcmp(S, S_compare_exit) == 0) {
            free(anime.nome[0]);
            return 1;
        }
        compareStrings(&f, S, &anime, &pilha);
    }

    return 0;
}

