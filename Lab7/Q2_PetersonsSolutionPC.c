#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>

#define BS 5
int in = 0;
int out = 0;
int buffer[BS];

//0: Producer
//1: Consumer
bool flag[2] = {false, false}; //flag[i] = true means P(i) wants to enter the critical section
int turn = -1; //turn stores which variable is there in critical section

void *producer(void *param);
void *consumer(void *param);

int main()
{
    pthread_t pid, cid; //returns the thread id of thread created
    pthread_attr_t attr1, attr2; //to define thread attributes

    //initializes the thread attributes
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);

    //creates a new thread
    pthread_create(&pid, &attr1, producer, NULL);
    pthread_create(&cid, &attr2, consumer, NULL);

    //wait for termination of the thread
    pthread_join(pid, NULL);
    pthread_join(cid, NULL);

    return 0;
}

void *producer(void *param)
{
    do
    {
        int next_produced_item;
        flag[0] = true;
        turn = 1;

        while(flag[1] && turn == 1); //means consumer is inside Critical Section 
        
        //Critical Section starts
        next_produced_item = rand() % 1000; //Filling the random numbers
        while((in + 1) % BS == out); //do nothing as buffer is full
        buffer[in] = next_produced_item;
        in = (in + 1) % BS;
        printf("[PRODUCER] Produced Item: %d\n", next_produced_item);
        printf("[PRODUCER] Buffer: %d %d %d %d %d\t\tin: %d\tout: %d\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], in, out);
        printf("\n");
        sleep(2);

        flag[0] = false; //exit condition from Critical Section
    }while(true);

    pthread_exit(0); //to exit a thread
}

void *consumer(void *param)
{
    do
    {
        int next_consumed_item;
        flag[1] = true;
        turn = 0;

        while(flag[0] && turn == 1); //means producer is inside Critical Section 
        

        //Critical Section starts
        while(in == out); //do nothing as buffer is empty
        next_consumed_item = buffer[out];
        out = (out + 1) % BS;
        printf("[CONSUMER] Consumed Item: %d\n", next_consumed_item);
        printf("[CONSUMER] Buffer: %d %d %d %d %d\t\tin: %d\tout: %d\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], in, out);
        printf("\n");
        sleep(3);

        flag[1] = false; //exit condition from Critical Section
    }while(true);
    
    pthread_exit(0); //to exit a thread
}

