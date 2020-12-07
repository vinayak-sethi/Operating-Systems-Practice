#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<time.h>

sem_t coke, slots, mutex;
int ncoke = 5; //count of cokes

void *producer(void *arg);
void *consumer(void *arg);

int main()
{
    pthread_t p[2], c[2]; //returns the thread id of thread created

    //initializes the unnamed semaphore at the address pointed to
    sem_init(&mutex, 0, 2);
    sem_init(&coke, 0, 1);
    sem_init(&slots, 0, 1);

    //creates a new thread
    for(int i=0; i<2; i++)
    {
        pthread_create(&p[i], NULL, producer, NULL);
        pthread_create(&c[i], NULL, consumer, NULL);
    }

    //wait for termination of the thread
    for(int i=0; i<2; i++)
    {
        pthread_join(p[i], NULL);
        pthread_join(c[i], NULL);
    }

    //destroys the unnamed semaphore at the address pointed to
    sem_destroy(&coke);
    sem_destroy(&slots);
    sem_destroy(&mutex);
    return 0;
}

void *producer(void *arg)
{
    while(1)
    {
        sem_wait(&slots);
        sem_wait(&mutex);
        if (ncoke == 10)
            continue;
        ncoke++;
        printf("\n[PRODUCER] Number of cokes in the machine currently after production: %d\n", ncoke);
        sem_post(&mutex);
        sem_post(&slots);
        sleep(1);
    }

    pthread_exit(0); //to exit a thread
}

void *consumer(void *arg)
{
    while(1)
    {
        sem_wait(&coke);
        sem_wait(&mutex);
        if(ncoke == 0)
            continue;
        ncoke--;
        printf("[CONSUMER] Number of cokes in the machine currently after consumption: %d\n", ncoke);
        sem_post(&mutex);
        sem_post(&coke);
        sleep(1);
    }

    pthread_exit(0); //to exit a thread
}