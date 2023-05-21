#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char anime[50];
  int episode_num;
  int length;
} Node;

typedef struct Stack {
  Node *data;
  int top;
  int capacity;
} Stack;

Stack *create_stack(int capacity) {
  Stack *stack = (Stack *)malloc(sizeof(Stack));
  stack->data = (Node *)malloc(capacity * sizeof(Node));
  stack->top = -1;
  stack->capacity = capacity;
  return stack;
}

void push(Stack *stack, char *anime) {
  if (stack->top == stack->capacity - 1) {
    printf("Stack overflow\n");
    return;
  }
  stack->top++;
  strcpy(stack->data[stack->top].anime, anime);
}

typedef struct Queue {
  Node *data;
  int front;
  int rear;
  int capacity;
} Queue;

Queue *create_queue(int capacity) {
  Queue *queue = (Queue *)malloc(sizeof(Queue));
  queue->data = (Node *)malloc(capacity * sizeof(Node));
  queue->front = 0;
  queue->rear = -1;
  queue->capacity = capacity;
  return queue;
}

void enqueue(Queue *queue, Stack *stack, int num_episodes, int length) {
  for (int i = 1; i <= num_episodes; i++) {
    if (queue->rear == queue->capacity - 1) {
      printf("Queue overflow\n");
      return;
    }
    queue->rear++;
    strcpy(queue->data[queue->rear].anime, stack->data[stack->top].anime);
    queue->data[queue->rear].episode_num = i;
    queue->data[queue->rear].length = length;
  }
}

Node dequeue(Queue *queue) {
  if (queue->front > queue->rear) {
    printf("Queue underflow\n");
    exit(1);
  }
  Node temp = queue->data[queue->front];
  queue->front++;
  return temp;
}

void print_queue(Queue *queue) {
  if (queue->front > queue->rear) {
    printf("Queue is empty\n");
    return;
  }
  for (int i = queue->front; i <= queue->rear; i++) {
    printf("%s %d ", queue->data[i].anime, queue->data[i].episode_num);
  }
  printf("\n");
}

#define MAX_ANIME 10

Stack *stack = create_stack(MAX_ANIME);
int top = -1;

Queue *queues[MAX_ANIME];
int num_queues = 0;

Queue *get_queue(char *anime) {
  for (int i = 0; i < num_queues; i++) {
    if (strcmp(queues[i]->data[0].anime, anime) == 0) {
      return queues[i];
    }
  }
  if (num_queues == MAX_ANIME) {
    printf("Maximum number of anime reached\n");
    exit(1);
  }
  num_queues++;
  queues[num_queues - 1] = create_queue(MAX_ANIME);
  strcpy(queues[num_queues - 1]->data[0].anime, anime);
  queues[num_queues - 1]->front = 0;
  queues[num_queues - 1]->rear = -1;
  return queues[num_queues - 1];
}

int main() {
  char input[10];

  char anime[50];

  int num_episodes, length;

  int remaining_time = 0;

  Queue *current_queue = NULL;

  while (1)

  {
    scanf("%s", input);

    if (strcmp(input, "f") == 0)

    {
      break;

    } else

        if (strcmp(input, "start") == 0)

    {
      scanf("%s", anime);

      printf("starting %s\n", anime);

      push(stack, anime);

      current_queue = get_queue(anime);

    } else

        if (strcmp(input, "download") == 0)

    {
      scanf("%d %d", &num_episodes, &length);

      enqueue(current_queue, stack, num_episodes, length);

      printf("downloading %d episodes of %s of %d minutes each\n", num_episodes,
             stack->data[stack->top].anime, length);

    } else

        if (strcmp(input, "watch") == 0)

    {
      scanf("%d", &num_episodes);

      if (current_queue->front > current_queue->rear && stack->top > 0)

      {
        stack->top--;

        current_queue = get_queue(stack->data[stack->top].anime);

        printf("no more episodes of %s left to watch\n",
               stack->data[stack->top + 1].anime);

        continue;

      } else

          if (current_queue->front > current_queue->rear && stack->top == 0)

      {
        printf("no more episodes of %s left to watch\n",
               stack->data[stack->top].anime);

        continue;
      }

      Node temp = current_queue->data[current_queue->front];

      remaining_time +=
          (current_queue->rear - current_queue->front + 1) * temp.length;

      if (num_episodes > current_queue->rear - current_queue->front + 1)

      {
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
               strcmp(current_queue->data[current_queue->front].anime,
                      stack->data[stack->top].anime) == 0)

          dequeue(current_queue);

        if (stack->top > 0) stack->top--;

        current_queue = get_queue(stack->data[stack->top].anime);

      } else

      {
        remaining_time -= num_episodes * temp.length;

        printf("%d watched (%d minutes)\n", num_episodes,
               num_episodes * temp.length);

        printf("%d remaining\n",
               current_queue->rear - current_queue->front + 1 - num_episodes);

        for (int i = 0; i < num_episodes &&
                        strcmp(current_queue->data[current_queue->front].anime,
                               stack->data[stack->top].anime) == 0;
             i++)

          dequeue(current_queue);
      }

    } else

        if (strcmp(input, "print_queue") == 0)

    {
      print_queue(current_queue);
    }
  }

  return

      0;
}
