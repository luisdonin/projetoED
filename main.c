#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "headers/heap/FD.h"
//#include "headers/stack/PD.h"

#define MAX  100

/*
 *Rules: 
 *	He can't watch two shows at the same time
 *	When starting a new show, he downloads the episodes in chronological order
 *	He watches it in chronological oder as well
 *	He can only watch the shows he has already downloaded
 *	if he starts show A, he can start show B, but he must finish show B before going back to A, and he must continue A from the point he had stopped before going to B
 *	A show is completed when all episodes are completed
 * */

/*
 * Input: start S E
 * Input: download quantity of show 20min
 *
 * */
//scanf("%s" ,S);
//scanf("%s", E);
//scanf("%d", &A);

/*
 *if (input: start show episode --> starting show) (name of the show)
 *else if(input: download n_episodes len_episode --> n episodes of show downloaded)
 *else if(input: watch n --> n episodes of show watched (n minutes)
 *The problem: I need to compare all these string inputs, efficiently :c
 *
 *
 * */
//strCompare = strcmp(S, S_compare_start);

/*char writeToFile(char *E){
    FILE *f = fopen("shows.txt", "w");
    if(f == NULL){
        printf("Error!");
        exit(1);
    }
    fprintf(f, "Show name: %s", E);
    fclose(f);

    return 1;
}*/
typedef struct Node{

    char *data;
   struct  Node *next;

}node;

typedef struct FILA{

}fila;

node *insert(node *list, char *E){
    node *newNode = (node*)malloc(sizeof(node));
    newNode->data = E;
    newNode->next = list;
    return newNode;
}


void comeca(node *list,char *E, int A){

    scanf("%s %d", E, &A);
    insert(list, E);


}
void compareStrings(node *list, char *S, char *E){
    char S_compare_start[]="comeca", S_compare_download[]="download";

    int A, t;
    if(strcmp(S, S_compare_start) == 0){
        scanf("%s %d", E, &A);
        insert(list, E);

        printf("comecando %s %d\n", E, A);
        //writeToFile(E);


    }else
    if(strcmp(S, S_compare_download) == 0){
        printf("%s\n", E);
        scanf("%d %d", &A, &t);//it's not printing because when it loops again the variable resets

        printf("%d episodios de %s downloaded\n", A,E);

    }
}



int main(){
	/*
	 * S --> instruction "start"
	 * E --> name of the show
	 * A --> episode number
	 * */
    node *list;


	char S[6], E[MAX],  S_compare_exit[] = "f";
    
	while(1){
        scanf("%s", S);
        if(strcmp(S, S_compare_exit) == 0){
            return 1 ;
        }
        compareStrings(list,S, E);
    }


	return 0;
}














