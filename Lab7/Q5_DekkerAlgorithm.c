#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<pthread.h>
#include<unistd.h>

// flags to indicate if each thread is in queue to enter its critical section 
bool thread1_wants_to_enter = false;
bool thread2_wants_to_enter = false;

int favoured_thread = 1; // to denote which thread will enter next
int data = 0;

void *runner1(void *param);
void *runner2(void *param);

int main()
{
    pthread_t tid[2];

    int ttid[2] = {1,2};

    //creates a new thread
    pthread_create(&tid[0], NULL, runner1, &ttid[0]);
    pthread_create(&tid[1], NULL, runner2, &ttid[1]);
    
    //wait for termination of the thread
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    
    return 0;
}
    
void *runner1(void *param)
{
    do
    {
        thread1_wants_to_enter = true;

        while(thread2_wants_to_enter == true)
        {
            if(favoured_thread == 2)
            {
                thread1_wants_to_enter = false;
            }
            while(favoured_thread == 2); // busy waiting
            thread1_wants_to_enter = true;
        }
        //critical section starts
        printf("[Thread1] Data : %d\n", data);
        sleep(3);
        //critical section ends
        favoured_thread = 2;
        thread1_wants_to_enter = false;
    }while(1);
}

void *runner2(void *param)
{
    do
    {
        thread2_wants_to_enter = true;

        while(thread1_wants_to_enter == true)
        {
            if(favoured_thread == 1)
            {
                thread2_wants_to_enter = false;
            }
            while(favoured_thread == 1); // busy waiting
            thread2_wants_to_enter = true;
        }
        //critical section starts
        printf("[Thread2] Data : %d\n", data);
        printf("[Thread2] Adding 1 to data\n");
        data++;
        printf("[Thread2] Incremented data : %d\n", data);
        sleep(3);
        //critical section ends
        favoured_thread = 1;
        thread2_wants_to_enter = false;
    }while (1);
}
