#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100
#define MAX_ANIME 10

typedef struct {
  char anime[50];
  int episode_num;
  int length;
} Node;

Node stack[MAX_SIZE];
int top = -1;

void push(char *anime) {
  if (top == MAX_SIZE - 1) {
    printf("Stack overflow\n");
    return;
  }
  top++;
  strcpy(stack[top].anime, anime);
}

typedef struct {
  Node queue[MAX_SIZE];
  int front;
  int rear;
  int max_episodes;
} Queue;

Queue queues[MAX_ANIME];
int num_queues = 0;

Queue *get_queue(char *anime) {
  for (int i = 0; i < num_queues; i++) {
    if (strcmp(queues[i].queue[0].anime, anime) == 0) {
      return &queues[i];
    }
  }
  if (num_queues == MAX_ANIME) {
    printf("Maximum number of anime reached\n");
    exit(1);
  }
  num_queues++;
  strcpy(queues[num_queues - 1].queue[0].anime, anime);
  queues[num_queues - 1].front = 0;
  queues[num_queues - 1].rear = -1;
  return &queues[num_queues - 1];
}

void enqueue(Queue *queue, int num_episodes, int length) {
  if (queue->rear - queue->front + 1 + num_episodes > queue->max_episodes) {
    printf("cannot download more than %d episodes\n", queue->max_episodes);
    return;
  }
  for (int i = 1; i <= num_episodes; i++) {
    if (queue->rear == MAX_SIZE - 1) {
      printf("Queue overflow\n");
      return;
    }
    queue->rear++;
    strcpy(queue->queue[queue->rear].anime, stack[top].anime);
    queue->queue[queue->rear].episode_num = i;
    queue->queue[queue->rear].length = length;
  }
  printf("downloading %d episodes of %d %s of %d minutes each\n", num_episodes,
         queue->max_episodes, stack[top].anime, length);
}

Node dequeue(Queue *queue) {
  if (queue->front > queue->rear) {
    printf("Queue underflow\n");
    exit(1);
  }
  Node temp = queue->queue[queue->front];
  queue->front++;
  return temp;
}

void print_queue(Queue *queue) {
  if (queue->front > queue->rear) {
    printf("Queue is empty\n");
    return;
  }
  for (int i = queue->front; i <= queue->rear; i++) {
    printf("%s %d ", queue->queue[i].anime, queue->queue[i].episode_num);
  }
  printf("\n");
}

void print_remaining() {
  int remaining_shows = 0;
  for (int i = 0; i < num_queues; i++) {
    Queue *q = &queues[i];
    if (q->rear - q->front + 1 > 0) {
      remaining_shows++;
      printf("%s has %d episodes remaining of %d\n", q->queue[q->front].anime,
             q->rear - q->front + 1, q->max_episodes);
    }
  }
  if (remaining_shows == 0) {
    printf("no shows to watch\n");
  }
}

int main() {
  char input[10];
  char anime[50];
  int num_episodes, length;
  int remaining_time = 0;
  Queue *current_queue = NULL;
  int first_input = 1;
  while (1) {
    scanf("%s", input);
    if (strcmp(input, "f") == 0) {
      print_remaining();
      break;
    } else if (strcmp(input, "start") == 0) {
      scanf("%s %d", anime, &num_episodes);
      printf("starting %s with %d episodes\n", anime, num_episodes);
      push(anime);
      current_queue = get_queue(anime);
      current_queue->max_episodes = num_episodes;
      first_input = 0;
    } else if (strcmp(input, "download") == 0) {
      if (first_input) {
        printf("no shows to download\n");
        continue;
      }
      scanf("%d %d", &num_episodes, &length);
      enqueue(current_queue, num_episodes, length);
    } else if (strcmp(input, "watch") == 0) {
      if (first_input) {
        printf("no shows to watch\n");
        continue;
      }
      scanf("%d", &num_episodes);
      if (current_queue->front > current_queue->rear && top > 0) {
        top--;
        current_queue = get_queue(stack[top].anime);
        printf("no more episodes of %s left to watch\n", stack[top + 1].anime);
        continue;
      } else if (current_queue->front > current_queue->rear && top == 0) {
        printf("no more episodes of %s left to watch\n", stack[top].anime);
        continue;
      }
      Node temp = current_queue->queue[current_queue->front];
      remaining_time +=
          (current_queue->rear - current_queue->front + 1) * temp.length;
      if (num_episodes > current_queue->rear - current_queue->front + 1) {
        printf("only %d left\n",
               current_queue->rear - current_queue->front + 1);
        remaining_time -=
            (current_queue->rear - current_queue->front + 1) * temp.length;
        printf("%d watched (%d minutes)\n",
               current_queue->rear - current_queue->front + 1,
               (current_queue->rear - current_queue->front + 1) * temp.length);
        printf("%d remaining\n",
               current_queue->rear - current_queue->front + 1);
        while (current_queue->front <= current_queue->rear &&
               strcmp(current_queue->queue[current_queue->front].anime,
                      stack[top].anime) == 0)
          dequeue(current_queue);
        if (top > 0) top--;
        current_queue = get_queue(stack[top].anime);
      } else {
        remaining_time -= num_episodes * temp.length;
        printf("%d watched (%d minutes)\n", num_episodes,
               num_episodes * temp.length);
        printf("%d remaining\n",
               current_queue->rear - current_queue->front + 1 - num_episodes);
        for (int i = 0; i < num_episodes &&
                        strcmp(current_queue->queue[current_queue->front].anime,
                               stack[top].anime) == 0;
             i++)
          dequeue(current_queue);
      }
    } else if (strcmp(input, "print_queue") == 0) {
      print_queue(current_queue);
    }
  }
  return 0;
}
    