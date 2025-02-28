#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

#define MAX_SIZE 5

int product = 0;
int buffer [MAX_SIZE];
int in = 0, out = 0;

int empty = MAX_SIZE, mutex = 1, full = 0;

void wait(int *s) {
    while (*s <= 0);
    (*s)--;
}

void signal(int *s) {
    (*s)++;
}

void* ProducerT(void* vargap)
{   
    while (1)
    {
        wait(&empty);

        wait(&mutex);

        sleep(1);
        int item = rand() % (100 - 10 + 1) + 10; 
        
        printf("Producer produced : %d at index - %d \n",item , in );
        in = (in + 1) % MAX_SIZE;
        product++;

        signal(&mutex);

        signal(&full);    

    }
    
    
}

void* ConsumerT(void* vargap)
{
    while (1)
    {
        wait(&full);

        wait(&mutex);
    
        sleep(2);
        int item = buffer[out];
    
        printf("Consumer consumes : %d at index - %d \n",item , out);
        product--;
        out = (out + 1) % MAX_SIZE;
    
        signal(&mutex);
    
        signal(&empty);    

    }
}

int main()
{
    pthread_t producer, consumer;
    printf("Program started: [ctrl + c for exit]");
    pthread_create(&producer, NULL, ProducerT, NULL);
    pthread_create(&consumer, NULL, ConsumerT, NULL);

    pthread_exit(NULL);

}