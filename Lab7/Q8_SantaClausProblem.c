#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define SHARE 1 //means semaphore is shared between processes

int elves_count = 0;
int reindeer_count = 0;
sem_t santa_sem, reindeer_sem, elves_sem, mutex;

void *santa(void *arg);
void *reindeer(void *arg);
void *elves(void *arg);

int main()
{
    pthread_t santathread, elfthread[3], reindeerthread[9]; //returns the thread id of thread created

    //initializes the unnamed semaphore at the address pointed to
    sem_init(&santa_sem, SHARE, 0);
    sem_init(&reindeer_sem, SHARE, 0);
    sem_init(&elves_sem, SHARE, 1);
    sem_init(&mutex, SHARE, 1);

    //creates a new thread
    pthread_create(&santathread, NULL, santa, NULL);
    for(int i=0; i<9; i++)
        pthread_create(&reindeerthread[i], NULL, reindeer, NULL);
    for(int i=0; i<3; i++)
        pthread_create(&elfthread[i], NULL, elves, NULL);
    
    //wait for termination of the thread
    pthread_join(santathread, NULL);
    for(int i=0; i<9; i++)
        pthread_join(reindeerthread[i], NULL);
    for(int i=0; i<3; i++)
        pthread_join(elfthread[i], NULL);

    //destroys the unnamed semaphore at the address pointed to
    sem_destroy(&santa_sem);
    sem_destroy(&reindeer_sem);
    sem_destroy(&elves_sem);
    sem_destroy(&mutex);

    printf("\n");
    return 0;
}

void *santa(void *arg)
{
    while(1)
    {
        sem_wait(&santa_sem); //decrements(locks) the semaphore pointed to by santa_sem
        sem_wait(&mutex); //decrements(locks) the semaphore pointed to by mutex

        if(reindeer_count == 9)
        {
            printf("\nHurray! Santa woke up..\n");
            printf("Sleigh is being prepared\n");

            reindeer_count = 0;

            for(int i=0; i<9; i++)
                sem_post(&reindeer_sem); //increments(unlocks) the semaphore pointed to by reindeer_sem
        }
        else if(elves_count == 3)
        {
            sleep(1);
            printf("Elves having difficulty to build toys!\n");
            printf("\nHurray! Santa Woke Up...\n");
            printf("Santa helped Elves and toys are made!\n");
        }

        sem_post(&mutex); //increments(unlocks) the semaphore pointed to by mutex
    }

    pthread_exit(0); //to exit a thread
}

void *reindeer(void *arg)
{
    printf("Reindeer back from Vacation!\n");
    while(1)
    {
        sem_wait(&mutex); //decrements(locks) the semaphore pointed to by mutex
        reindeer_count += 1;
        if(reindeer_count == 9)
            sem_post(&santa_sem); //increments(unlocks) the semaphore pointed to by santa_sem
        sem_post(&mutex); //increments(unlocks) the semaphore pointed to by mutex

        sem_wait(&reindeer_sem); //decrements(locks) the semaphore pointed to by reindeer_sem
        printf("Reindeer being hitched...\n");
        sleep(1);
    }

    pthread_exit(0); //to exit a thread
}

void *elves(void *arg)
{
    while(1)
    {
        sem_wait(&elves_sem); //decrements(locks) the semaphore pointed to by elves_sem
        sem_wait(&mutex); //decrements(locks) the semaphore pointed to by mutex

        elves_count += 1;

        if(elves_count == 3)
            sem_post(&santa_sem); //increments(unlocks) the semaphore pointed to by santa_sem
        else
            sem_post(&elves_sem); //increments(unlocks) the semaphore pointed to by elves_sem

        sem_post(&mutex); //increments(unlocks) the semaphore pointed to by mutex

        sleep(1);
        printf("Elves waiting for help!\n");
        sleep(1); 

        sem_wait(&mutex); //decrements(locks) the semaphore pointed to by mutex
        elves_count -= 1;
        if(elves_count == 0)
            sem_post(&elves_sem); //increments(unlocks) the semaphore pointed to by elves_sem
        sem_post(&mutex); //increments(unlocks) the semaphore pointed to by mutex
    }

    pthread_exit(0); //to exit a thread
}