#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

#define N 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (ph_num+4)%N
#define RIGHT (ph_num+1)%N

sem_t mutex;
sem_t S[N];

void *philosopher(void *num);
void take_fork(int);
void put_fork(int);
void test(int);

int state[N];
int phil_num[N] = {0, 1, 2, 3, 4};

int main()
{
    int i;
    pthread_t thread_id[N]; //returns the thread id of thread created

    //initializes the unnamed semaphore at the address pointed to
    sem_init(&mutex, 0, 1);
    for(int i = 0; i < N; i++)
        sem_init(&S[i], 0, 0);

    //creates a new thread
    for(int i = 0; i < N; i++)
    {
        pthread_create(&thread_id[i], NULL, philosopher, &phil_num[i]);
        printf("Philosopher %d is thinking\n", i+1);
    }

    //wait for termination of the thread
    for(int i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);

    //destroys the unnamed semaphore at the address pointed to
    sem_destroy(&mutex);
    for(int i = 0; i < N; i++)
        sem_destroy(&S[i]);

    return 0;
}

void *philosopher(void *num)
{
    while(1)
    {
        int *i = num;
        sleep(1);
        take_fork(*i);
        printf("Philosopher %d has finished eating\n", *i+1);
        put_fork(*i);
    }

    pthread_exit(0); //to exit a thread
}

void take_fork(int ph_num)
{
    sem_wait(&mutex); // so that state update remains critical section
    state[ph_num] = HUNGRY;
    printf("Philosopher %d is Hungry\n", ph_num + 1);
    test(ph_num);
    sem_post(&mutex); //increments(unlocks) the semaphore pointed to by mutex
    sem_wait(&S[ph_num]); //decrements(locks) the semaphore pointed to by S[ph_num]
    sleep(1);
}

void test(int ph_num)
{
    if(state[ph_num] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
    {
        state[ph_num] = EATING;
        sleep(2);
        printf("Philosopher %d takes fork %d and %d\n", ph_num + 1, LEFT + 1, ph_num + 1);
        printf("Philosopher %d is eating\n", ph_num + 1);
        sem_post(&S[ph_num]); //increments(unlocks) the semaphore pointed to by S[ph_num]
    }
}

void put_fork(int ph_num)
{
    sem_wait(&mutex); //decrements(locks) the semaphore pointed to by mutex
    state[ph_num] = THINKING;
    printf("Philosopher %d putting fork %d and %d down\n", ph_num + 1, LEFT + 1, ph_num + 1);
    printf("Philosopher %d is thinking\n", ph_num + 1);
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex); //increments(unlocks) the semaphore pointed to by mutex
}