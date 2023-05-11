#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
typedef struct{
        char *nome[MAX];
        int length;
        int ep;
}serie;
typedef struct {
    char data[MAX][100];
    int inicio, fim, tamanho;
} fila;

void criaFila(fila* f) {
    f->inicio = 0;
    f->fim = -1;
    f->tamanho = 0;
}

int filaVazia(fila* f) {
    return (f->tamanho == 0);
}

int filaCheia(fila* f) {
    return (f->tamanho == MAX);
}

void insere(fila* f, const char* data) {
    if (filaCheia(f)) {
        printf("Fila Cheia");
        return;
    }
    f->fim = (f->fim + 1) % MAX;
    strncpy(f->data[f->fim], data, sizeof(f->data[f->fim]));
    f->tamanho++;

  //  printf("Inserted: %s\n", f->data[f->fim]);
}

void printNodes(fila *f) {
    if (filaVazia(f)) {
        printf("Fila vazia\n");
        return;
    }

    printf("Series na fila:\n");
    int i;
    for (i = 0; i < f->tamanho; i++) {
        printf("%s\n", f->data[(f->inicio + i) % MAX]);
    }
}


void compareStrings(fila* f, char* S) {
    char S_compare_start[] = "comeca", S_compare_download[] = "download", S_compare_assiste[] = "assiste", S_compare_fila[] = "fila";
    serie anime;


    if (strcmp(S, S_compare_start) == 0) {
        scanf("%s %d", anime.nome, &anime.ep);
        printf("comecando %s %d\n", anime.nome, anime.ep);
        insere(f, anime.nome);


    }

    if (strcmp(S, S_compare_download) == 0) {
        printf("%s\n", f->data[f->inicio]);
        scanf("%d %d", &anime.ep, &anime.length);
        printf("%d episodios de %s baixados\n", anime.ep, f->data[f->inicio]);
    }

    if (strcmp(S, S_compare_assiste) == 0) {

        printf("%d eps de %s assistidos (%d minutos)\n", anime.ep, f->data[f->inicio], (anime.length*anime.ep));
    }

    if(strcmp(S, S_compare_fila)==0){
        printNodes(f);
    }

}

int main() {
    fila f;
    criaFila(&f);

    char S[6], S_compare_exit[] = "f";

    while (1) {
        scanf("%s", S);
        if (strcmp(S, S_compare_exit) == 0) {
            return 1;
        }
        compareStrings(&f, S);
    }

    return 0;
}

