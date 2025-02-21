#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 5

int buffer[MAX_SIZE];
int in = 0, out = 0;
int empty = MAX_SIZE, mutex = 1, full = 0;

void wait(int *s) {
    while (*s <= 0);
    (*s)--;
}

void signal(int *s) {
    (*s)++;
}

void producer() {
    int item;
    wait(&empty);
    wait(&mutex);

    item = rand() % 100;
    buffer[in] = item;
    printf("Producer produces item: %d at index %d\n", item, in);
    in = (in + 1) % MAX_SIZE;

    signal(&mutex);
    signal(&full);
}

void consumer() {
    int item;
    wait(&full);
    wait(&mutex);

    item = buffer[out];
    printf("Consumer consumes item: %d from index %d\n", item, out);
    out = (out + 1) % MAX_SIZE;

    signal(&mutex);
    signal(&empty);
}

int main() {
    int choice;
    while (1) {
        printf("\n1. Producer\n2. Consumer\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                if (full != MAX_SIZE) {
                    producer();
                } else {
                    printf("Buffer is full!\n");
                }
                break;
            case 2:
                if (empty != MAX_SIZE) {
                    consumer();
                } else {
                    printf("Buffer is empty!\n");
                }
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }

    return 0;
}
