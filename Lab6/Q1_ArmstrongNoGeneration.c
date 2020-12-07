#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>

#define MAX 10000

int start, end;
int store_sum[MAX];

void *runner(void *num);

int main(int argc, char *argv[])
{
	//Validate the usage of command line arguments
    if(argc < 3)
    {
        printf("\nSyntax: %s <Starting Number> <Ending Number>\n\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    start = atoi(argv[1]);
    end = atoi(argv[2]);

	printf("\nSet of Armstrong numbers between %d and %d are { ", start, end);

	for(int i=start; i<=end; i++)
    {
        int *val = (int *)malloc(sizeof(int));
        *val = i;

        pthread_t tid; //returns the thread id of thread created
        pthread_attr_t attr; //to define thread attributes
        pthread_attr_init(&attr); //initializes the thread attributes

        pthread_create(&tid, &attr, runner, val); //creates a new thread
        pthread_join(tid, NULL); //wait for termination of the thread
    }

    for(int i=0; i<=end-start; i++)
        if(store_sum[i] == i+start)
            printf("%d ", store_sum[i]);
        
	printf("\b }\n\n");
    return 0;
}

void *runner(void *num)
{
	int *val = (int *)num;
	int temp = *val;
	int i = 0;
	int sum = 0;

	while(temp != 0)
	{
	 	i++; // counts the number of digit in the number
		temp = temp/10;
	}

	temp = *val;	
	while(temp != 0)
	{
		sum = sum + pow(temp%10, i); 
		temp = temp/10;
	}

	store_sum[*val - start] = sum; //stores the value of sum

    pthread_exit(0); //to exit a thread
}

