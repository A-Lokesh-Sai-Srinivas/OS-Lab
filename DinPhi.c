#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

#define MAX_SIZE 5

enum{
    THINKING,
    HUNGRY,
    EATING,
} state[5];

int chopL[MAX_SIZE] , chopR[MAX_SIZE];
int cond[MAX_SIZE];


void wait(int *s){
    while ((*s) <= 0);
    (*s)--;
}


void signal(int *s){
    (*s)++;
}


void test (int i)
{
    if ((state[i] == HUNGRY) && state[(i+4) % MAX_SIZE] != EATING && state[(i+1) % MAX_SIZE] != EATING){
        state[i] = EATING;
        printf("Philosopher %d is eating \n" , i+1);
        signal(&cond[i]);
    }

}


void pickup(int i )
{
    state[i] = HUNGRY;
    test(i);
    if (state[i] != EATING)
    {
        wait(&cond[i]);
    }
}


void putdown(int i )
{
    state[i] = THINKING;
    test((i+1)%MAX_SIZE);
    test((i+4)%MAX_SIZE);
}

void* PhilosopherT(void* arg){
    int i = (*((int*) arg) ) % MAX_SIZE + 1;
    int stime = rand() % 15 + 5;
    while (1)
    {    
        printf("Philosopher %d is thinking.\n", i);
        sleep(stime);
        pickup(i);

        sleep(stime);
        printf("Philosopher %d is done eating.\n", i);
        putdown(i);
    
    }
}

int main()
{  
    for (int  i = 0; i < MAX_SIZE; i++)
    {
        state[i] = THINKING;
    }

    pthread_t philo[MAX_SIZE];
    
    for (int  i = 0; i < MAX_SIZE; i++)
    {
        pthread_create(&philo[i] , NULL , PhilosopherT , (void*)&i);
    }

    pthread_exit(NULL);
    

    return 0;
}