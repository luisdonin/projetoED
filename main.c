#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tam_max 2000
#define anime_max 10

typedef struct {
  char anime[50];
  int num_episodio;
  int tempo_episodio;
} Nodo;

typedef struct {
  Nodo pilha_est[tam_max];
  int topo;
} Pilha_estatica;

void push(Pilha_estatica *s, char *anime) {
  if (s->topo == tam_max - 1) {
    printf("stack overflow\n");
    return;
  }
  s->topo++;
  strcpy(s->pilha_est[s->topo].anime, anime);
}

typedef struct {
  Nodo fila_est[tam_max];
  int inicio;
  int fim;
  int max_episodes;
} Fila_estatica;

typedef struct {
  Fila_estatica animes[anime_max];
  int num_animes;
  int assistidos[anime_max];
} animes;

Fila_estatica *get_Fila_estatica(animes *q, char *anime) {
  for (int i = 0; i < q->num_animes; i++) {
    if (strcmp(q->animes[i].fila_est[0].anime, anime) == 0) {
      return &q->animes[i];
    }
  }
  if (q->num_animes == anime_max) {
    printf("numero maximo de animes atingido\n");
    exit(1);
  }
  q->num_animes++;
  strcpy(q->animes[q->num_animes - 1].fila_est[0].anime, anime);
  q->animes[q->num_animes - 1].inicio = 0;
  q->animes[q->num_animes - 1].fim = -1;
  return &q->animes[q->num_animes - 1];
}

void insere_fila(Fila_estatica *fila_est, Pilha_estatica *s, int num_episodes, int tempo_episodio) {
    int episodes_to_add = num_episodes;
    if (fila_est->fim - fila_est->inicio + 1 + num_episodes > fila_est->max_episodes) {
        episodes_to_add = fila_est->max_episodes - (fila_est->fim - fila_est->inicio + 1);
    }
    for (int i = 1; i <= episodes_to_add; i++) {
        if (fila_est->fim == tam_max - 1) {
            printf("acima do limite\n");
            return;
        }
        fila_est->fim++;
        strcpy(fila_est->fila_est[fila_est->fim].anime, s->pilha_est[s->topo].anime);
        fila_est->fila_est[fila_est->fim].num_episodio = i;
        fila_est->fila_est[fila_est->fim].tempo_episodio = tempo_episodio;
    }
    printf(" %d episodios de %s baixados\n", episodes_to_add,
           s->pilha_est[s->topo].anime);
}

Nodo remove_fila(Fila_estatica *fila_est) {
  if (fila_est->inicio > fila_est->fim) {
    printf("Fila_estatica underflow\n");
    exit(1);
  }
  Nodo temp = fila_est->fila_est[fila_est->inicio];
  fila_est->inicio++;
  return temp;
}

void print_Fila_estatica(Fila_estatica *fila_est) {
  if (fila_est->inicio > fila_est->fim) {
    printf("Fila vazia\n");
    return;
  }
  for (int i = fila_est->inicio; i <= fila_est->fim; i++) {
    printf("%s %d ", fila_est->fila_est[i].anime, fila_est->fila_est[i].num_episodio);
  }
  printf("\n");
}

void print_remaining(animes *q) {
  int remaining_anime = 0;
  for (int i = 0; i < q->num_animes; i++) {
    Fila_estatica *fila_est = &q->animes[i];
    if (fila_est->fim - fila_est->inicio + 1 > 0 ||
        q->assistidos[i] < fila_est->max_episodes) {
      remaining_anime++;
      printf("%s: faltam baixar %d e assistir %d\n",
             fila_est->fila_est[fila_est->inicio].anime,
             fila_est->max_episodes - (fila_est->fim - fila_est->inicio + 1) -
                 q->assistidos[i],
             fila_est->max_episodes - q->assistidos[i]);
    }
  }
  if (remaining_anime == 0) {
    printf("nao ha anime para assistir\n");
  }
}

void comeca(Pilha_estatica *s, animes *q, char *anime, int num_episodes) {
  printf("comecando %s\n", anime);
  push(s, anime);
  Fila_estatica *filaAtual = get_Fila_estatica(q, anime);
  filaAtual->max_episodes = num_episodes;
}

void download( Pilha_estatica *s, Fila_estatica **filaAtual, int num_episodes,int tempo_episodio) {
  insere_fila(*filaAtual, s, num_episodes, tempo_episodio);
}

void assiste(animes *q, Pilha_estatica *s, Fila_estatica **filaAtual, int num_episodes) {
  if ((*filaAtual)->inicio > (*filaAtual)->fim && s->topo > 0) {
    s->topo--;
    *filaAtual = get_Fila_estatica(q, s->pilha_est[s->topo].anime);
    printf("nao ha mais episodios de %s para assistir\n",
           s->pilha_est[s->topo + 1].anime);
    return;
  } else if ((*filaAtual)->inicio > (*filaAtual)->fim && s->topo == 0) {
    printf("nao ha mais episodios de %s para assistir\n",
           s->pilha_est[s->topo].anime);
    return;
  }

  Nodo temp = (*filaAtual)->fila_est[(*filaAtual)->inicio];
  if (num_episodes > (*filaAtual)->fim - (*filaAtual)->inicio + 1) {
    printf("apenas %d restantes\n",
           (*filaAtual)->fim - (*filaAtual)->inicio + 1);

    printf("%d episodios assistidos (%d minutoss)\n",
           (*filaAtual)->fim - (*filaAtual)->inicio + 1,
           (*filaAtual)->fim - (*filaAtual)->inicio + 1 * temp.tempo_episodio);

           
    while ((*filaAtual)->inicio <= (*filaAtual)->fim && 
    strcmp((*filaAtual)->fila_est[(*filaAtual)->inicio].anime,s->pilha_est[s->topo].anime) == 0)
      remove_fila(*filaAtual);


    if (s->topo > 0) s->topo--;
    *filaAtual = get_Fila_estatica(q, s->pilha_est[s->topo].anime);
  } 
  
  
  else {
    printf("%d episodios de %s assistidos (%d minutos)\n", num_episodes,
           s->pilha_est[s->topo].anime, num_episodes * temp.tempo_episodio);
    for (int i = 0;
         i < num_episodes &&
         strcmp((*filaAtual)->fila_est[(*filaAtual)->inicio].anime,
                s->pilha_est[s->topo].anime) == 0;
         i++)
      remove_fila(*filaAtual);
  }
}

int main() {
  Pilha_estatica s = {.topo = -1};
  animes q = {.num_animes = 0};
  char entrada[10];
  char anime[50];
  int num_episodes, tempo_episodio;
  Fila_estatica *filaAtual = NULL;

  while (1) {
    scanf("%s", entrada);

    if (strcmp(entrada, "f") == 0) {
      print_remaining(&q);
      break;
    } else if (strcmp(entrada, "comeca") == 0) {
      scanf("%s %d", anime, &num_episodes);
      comeca(&s, &q, anime, num_episodes);
      filaAtual = get_Fila_estatica(&q, anime);
    } else if (strcmp(entrada, "download") == 0) {
      scanf("%d %d", &num_episodes, &tempo_episodio);
      download( &s, &filaAtual, num_episodes, tempo_episodio);
    } else if (strcmp(entrada, "assiste") == 0) {
      scanf("%d", &num_episodes);
      assiste(&q, &s, &filaAtual, num_episodes);
    }
  }
}
