#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int *fibseq, i;

void *runner(void *arg);

int main(int argc, char *argv[])
{
    //proper usage of command line arguments
    if(argc != 2)
    {
        printf("\nWrong usage.. Syntax: %s <n value> \n\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    if(atoi(argv[1]) < 0)
    {
        printf("\nn value should be greater than zero\n\n");
        exit(EXIT_SUCCESS);
    }

    int n = atoi(argv[1]); //number of elements to generate
    fibseq = (int *)malloc(n*sizeof(int)); //array to store fibonacci series

    pthread_t *tid = (pthread_t *)malloc(n*sizeof(pthread_t)); //returns the thread id of thread created
    pthread_attr_t attr; //to define thread attributes
    pthread_attr_init(&attr); //initializes the thread attributes

    for(i=0; i<n; i++)
    {
        pthread_create(&tid[i], &attr, runner, (void *) fibseq); //creates a new thread
        pthread_join(tid[i], NULL); //wait for termination of the thread
    }

    printf("\nThe set of first '%d' fibonacci series numbers are { ", n);

	for(i=0; i<n; i++)
	{
		printf("%d, ", fibseq[i]);
	}
	printf("\b\b }\n\n");

	return 0;
}

void *runner(void *arg)
{
    if(i == 0 || i == 1)
    {
        fibseq[i] = i;
        pthread_exit(0); //to exit a thread
    }

    else
    {
        fibseq[i] = fibseq[i-1] + fibseq[i-2];
        pthread_exit(0);
    }
}
