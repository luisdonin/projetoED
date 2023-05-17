#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 3
typedef struct{
    char nome[MAX];
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

void insere(fila* f, char* data) {
    if (filaCheia(f)) {
    printf("Fila Cheia");
    return;
 }
    f->fim = (f->fim + 1) % MAX;
    strncpy(f->data[f->fim], data, sizeof(f->data[f->fim]));
    f->tamanho++;

 // printf("Inserted: %s\n", f->data[f->fim]);
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

void removeNodo(fila* f) {
    if (filaVazia(f)) {
    printf("Fila Vazia");
    return;
 }
    f->inicio = (f->inicio + 1) % MAX;
    f->tamanho--;
}

void compareStrings(fila* f, char* S, serie* anime) {
    char S_compare_start[] = "comeca", S_compare_download[] = "download", S_compare_assiste[] = "assiste", S_compare_fila[] = "fila";

    if (strcmp(S, S_compare_start) == 0) {
    // Check if the user has finished watching all episodes of the current series
        if (anime->ep > 0) {
        printf("You must finish watching all episodes of %s before starting a new series.\n", anime->nome);
    } else {
        scanf("%s %d", anime->nome, &anime->ep);
        printf("comecando %s %d\n", anime->nome, anime->ep);
        insere(f, anime->nome);
    }
 }

    if (strcmp(S, S_compare_download) == 0) {
        printf("%s\n", f->data[f->inicio]);
        scanf("%d %d", &anime->ep, &anime->length);
        printf("%d episodios de %s baixados\n", anime->ep, f->data[f->inicio]);
 }

    if (strcmp(S, S_compare_assiste) == 0) {
        printf("%d eps de %s assistidos (%d minutos)\n", anime->ep, f->data[f->inicio], (anime->length*anime->ep));
        // Decrement the number of episodes remaining
        anime->ep -= anime->ep;
 }

 if(strcmp(S, S_compare_fila)==0){
    printNodes(f);
 }
}



int main() {
    fila f;
    criaFila(&f);

    serie anime = {0};
    char S[6], S_compare_exit[] = "f";

    while (1) {
        scanf("%s", S);
        if (strcmp(S, S_compare_exit) == 0) {
        return 1;
        }
        compareStrings(&f, S, &anime);
    }

    return 0;
}

