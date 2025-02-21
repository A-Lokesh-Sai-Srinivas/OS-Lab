#include <stdio.h>
#include <stdlib.h>

#define MAX 5

typedef struct Queue 
{
    int arr[MAX];
    int front;
    int rear;
} Queue;

void initQueue(Queue *q) 
{
    q->front = -1;
    q->rear = -1;
}

int isFull(Queue *q) 
{
    return q->rear == MAX - 1;
}

int isEmpty(Queue *q) 
{
    return q->front == -1;
}


void enqueue(Queue *q, int data) 
{
    if (isFull(q)) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear++;
    q->arr[q->rear] = data;
    printf("%d enqueued to queue\n", data);
}

int dequeue(Queue *q) 
{
    if (isEmpty(q)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1; 
    }
    int data = q->arr[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return data;
}

void displayQueue(Queue *q) 
{
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->arr[i]);
    }
    printf("\n");
}

wait(int S)
{
    while (S<=0);
    S--;
}

signal(int S)
{
    S++;
}

int main() {
    Queue q;
    initQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);
    enqueue(&q, 50);

    displayQueue(&q);

    printf("Dequeued: %d\n", dequeue(&q));
    displayQueue(&q);

    enqueue(&q, 60);
    displayQueue(&q);

    return 0;
}
