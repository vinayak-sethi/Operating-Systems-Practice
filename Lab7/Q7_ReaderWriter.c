#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t mutex, writeblock;

int data = 0, rcount = 0;

void *reader(void *arg);
void *writer(void *arg);

int main()
{
    int i;
    pthread_t rtid[3], wtid[3]; //returns the thread id of thread created

    //initializes the unnamed semaphore at the address pointed to
    sem_init(&mutex, 0, 1);
    sem_init(&writeblock, 0, 1);

    int twid[3] = {0,1,2};
    int trid[3] = {0,1,2};

    //creates a new thread
    for(int i = 0; i <= 2; i++)
    {
        pthread_create(&wtid[i], NULL, writer, &twid[i]);
        pthread_create(&rtid[i], NULL, reader, &trid[i]);
    }

    //wait for termination of the thread
    for(int i = 0; i <= 2; i++)
    {
        pthread_join(wtid[i], NULL);
        pthread_join(rtid[i], NULL);
    }

    //destroys the unnamed semaphore at the address pointed to
    sem_destroy(&mutex);
    sem_destroy(&writeblock);

    return 0;
}

void *reader(void *arg)
{
    int *f = arg;

    sem_wait(&mutex); //decrements(locks) the semaphore pointed to by mutex 
    rcount = rcount + 1;

    if(rcount == 1) // first reader
        sem_wait(&writeblock); //decrements(locks) the semaphore pointed to by writeblock

    sem_post(&mutex); //increments(unlocks) the semaphore pointed to by mutex

    printf("Data read by the reader %d is %d\n", *f, data);

    sem_wait(&mutex); //decrements(locks) the semaphore pointed to by mutex 
    rcount = rcount - 1;

    if(rcount == 0) // last reader
        sem_post(&writeblock); //increments(unlocks) the semaphore pointed to by writeblock
    sleep(3);
    
    sem_post(&mutex); //increments(unlocks) the semaphore pointed to by mutex

    pthread_exit(0); //to exit a thread
}

void *writer(void *arg)
{
    int *f = arg;

    sem_wait(&writeblock); //decrements(locks) the semaphore pointed to by writeblock

    data++;

    printf("Data written by the writer %d is %d\n", *f, data);
    sleep(3);

    sem_post(&writeblock); //increments(unlocks) the semaphore pointed to by writeblock

    pthread_exit(0); //to exit a thread
}