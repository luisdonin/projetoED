#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
    int data[MAX][100];
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

void insere(fila* f, int data) {
    
    if (filaCheia(f)) {
        printf("Fila Cheia");
        return;
    }
    f->fim = (f->fim + 1) % MAX;
    //strncpy(f->data[f->fim], data, sizeof(f->data[f->fim]));
    f->tamanho++;
    printf("insere called with f = %p and data = %d\n", f, data);


 
}
/*void insereTopo(fila* f, char* data) {
    if (filaCheia(f)) {
        printf("Fila Cheia");
        return;
    }

    for (int i = f->tamanho; i >= 0; i--){
        strcpy(f->data[f->inicio + i]% MAX, f->data[f->inicio - 1] % MAX);
    }
}*/

void printNodes(fila *f) {
    if (filaVazia(f)) {
        printf("Fila vazia\n");
        return;
    }
 
    printf("Series na fila:\n");
    int i;
    for (i = 0; i <= f->tamanho; i++) {
        printf("%n\n", f->data[(f->fim - i) % MAX]);
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