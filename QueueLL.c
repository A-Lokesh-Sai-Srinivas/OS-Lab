#include <stdio.h>
#include <stdlib.h>


typedef struct Node 
{
    int data;
    struct Node *next;
} Node;

typedef struct Queue 
{
    Node *front;
    Node *rear;
} Queue;

Node* createNode(int data) 
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void initQueue(Queue *q) 
{
    q->front = q->rear = NULL;
}

void enqueue(Queue *q, int data) 
{
    Node *newNode = createNode(data);
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

int dequeue(Queue *q) 
{
    if (q->front == NULL) {
        printf("Queue is empty.\n");
        return -1;
    }
    Node *temp = q->front;
    int data = temp->data;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return data;
}

void displayQueue(Queue *q) 
{
    Node *temp = q->front;
    if (temp == NULL) {
        printf("Queue is empty.\n");
        return;
    }
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}


wait(S)
{
    while(S<=0);
    S--;
}
    
signal(S)
{
    S++;
}


int main() {
    Queue q;
    initQueue(&q);


    
    printf("Queue: ");
    displayQueue(&q);

    printf("Dequeued: %d\n", dequeue(&q));

    printf("Queue after dequeue: ");
    displayQueue(&q);

    return 0;
}
