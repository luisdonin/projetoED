
#define tam_max 2000
#define anime_max 100

typedef struct {
    char anime[anime_max];
    int num_episodio;
    int tempo_episodio;
}Nodo;


typedef struct {
    Nodo pilha_est[tam_max];
    int topo;
}Pilha_estatica;

typedef struct 
{
    Nodo fila_est[tam_max];
    int inicio, fim, max_eps;
}Fila_estatica;

typedef struct{
    Fila_estatica filas[anime_max];
    int num_filas, assistidos[anime_max];
}animes;