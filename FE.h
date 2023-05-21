#define MAX_SIZE 2000
#define MAX_ANIME 10
#include "node.h"

typedef struct {
  Node queue[MAX_SIZE];
  int front;
  int rear;
  int max_episodes;
} Queue;

typedef struct {
  Queue queues[MAX_ANIME];
  int num_queues;
  int watched[MAX_ANIME];
} filas;