#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define MAX_THREAD 4 //maximum number of threads

struct limit
{
	int low;
	int high;
};

void *runner(void *arg);

int main(int argc, char *argv[])
{
	//Validate the correct usage of command line arguments
	if(argc != 2)
	{
		printf("\nSyntax: %s <Upper Limit>\n\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if(atoi(argv[1]) < 0)
	{
		printf("\nn value should be greater than zero...\n\n");
		exit(EXIT_FAILURE);
	}

	int last = atoi(argv[1]);
	struct limit *l[4];

	for(int i=0; i<4; i++)
		l[i] = (struct limit *)malloc(sizeof(struct limit)); 

	//creating the limits for different threads
	l[0]->low = 2, l[0]->high = last/4;
	l[1]->low = l[0]->high+1, l[1]->high = l[0]->high*2;
	l[2]->low = l[1]->high+1, l[2]->high = l[0]->high*3;
	l[3]->low = l[2]->high+1, l[3]->high = last;

	pthread_t *tid = (pthread_t *)malloc(MAX_THREAD*sizeof(pthread_t)); //returns the thread id of thread created
    pthread_attr_t attr; //to define thread attributes
	pthread_attr_init(&attr); //initializes the thread attribute

	printf("\nSet of Prime numbers upto %d are { ", last);

	for(int i=0; i<MAX_THREAD; i++)
    {
        pthread_create(&tid[i], &attr, runner, (void *)l[i]); //creates a new thread
    }

	for(int i=0; i<MAX_THREAD; i++)
    {
		pthread_join(tid[i], NULL); //wait for termination of the thread
    }

	printf("\b }\n\n");
    return 0;
}

void *runner(void *arg)
{
	struct limit *l = (struct limit *)arg;
	int i, j, isprime = 1;

	for(i=l->low; i<=l->high; i++)
	{
		isprime = 1;

		for(j=2; j<= i/2; j++)
		{
			if(i%j == 0)
			{
				isprime = 0;
				break;
			}
		}

		if(isprime == 1) //if number is prime
		{
			printf("%d ", i);
		}
	}

	pthread_exit(0); //to exit a thread
}