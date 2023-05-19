#include <stdio.h>
#include <string.h>




#define MAX 100
#define tamString 100

typedef struct{
    char data[MAX][tamString];
    int topo;
}pilhaEstatica;


void criaPilha(pilhaEstatica *pilha){
    pilha->topo = -1;
}
void push(pilhaEstatica *pilha, char *string){
    if(pilha->topo == MAX - 1){
        printf("Pilha cheia");
        return;
    }
    
    strcpy(pilha->data[++pilha->topo], string);
    printf("push called with pilha = %p and string = %s\n", pilha, string);

}

void *pop(pilhaEstatica *pilha){
    return pilha->data[pilha->topo--];
}

