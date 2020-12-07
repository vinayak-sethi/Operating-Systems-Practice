#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define SHARE 0 //means semaphore is shared between the threads of a process
#define DINE_CAPACITY 5

int eating = 0;
int readyToLeave = 0;
sem_t mutex, okToLeave;

void *dininghall(void *arg);

int main()
{
    pthread_t tid[DINE_CAPACITY]; //returns the thread id of thread created

    //initializes the unnamed semaphore at the address pointed to
    sem_init(&mutex, SHARE, 1);
    sem_init(&okToLeave, SHARE, 0);

    int temp[DINE_CAPACITY];
    for(int i=0; i<DINE_CAPACITY; i++)
        temp[i] = i+1;
    
    //creates a new thread
    for(int i=0; i<DINE_CAPACITY; i++)
        pthread_create(&tid[i], NULL, dininghall, &temp[i]);

    //wait for termination of the thread
    for(int i=0; i<DINE_CAPACITY; i++)
        pthread_join(tid[i], NULL);

    //destroys the unnamed semaphore at the address pointed to
    sem_destroy(&mutex);
    sem_destroy(&okToLeave);

    return 0;
}

void *dininghall(void *arg)
{
    int *param = arg;
    printf("Diner %d entered the hall and ready to eat\n", *param);

    sem_wait(&mutex); //decrements(locks) the semaphore pointed to by mutex
    eating ++;
    printf("Diner %d is eating\n", *param);
    if(eating == 2 && readyToLeave == 1)
    {
        sem_post(&okToLeave); //increments(unlocks) the semaphore pointed to by okToLeave
        readyToLeave --;
    }
    sem_post(&mutex); //increments(unlocks) the semaphore pointed to by mutex
    sleep(3);

    sem_wait(&mutex); //decrements(locks) the semaphore pointed to by mutex
    eating--;
    readyToLeave++;
    printf("Diner %d is ready to leave\n", *param);

    if(eating == 1 && readyToLeave == 1)
    {
        sem_post(&mutex); //increments(unlocks) the semaphore pointed to by mutex
        sem_wait(&okToLeave); //increments(unlocks) the semaphore pointed to by okToLeave
    }
    else if(eating == 0 && readyToLeave == 2)
    {
        sem_post(&okToLeave); //increments(unlocks) the semaphore pointed to by okToLeave
        readyToLeave -= 2;
        sem_post(&mutex); //increments(unlocks) the semaphore pointed to by mutex
    }
    else
    {
        readyToLeave--;
        sem_post(&mutex); //increments(unlocks) the semaphore pointed to by mutex
    }
    
    printf("Diner %d has left the hall\n", *param);

    pthread_exit(0); //to exit a thread
}


