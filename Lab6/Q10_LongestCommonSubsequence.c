#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

#define MAX 1000

struct length
{
    int len1;
    int len2;
};

char s1[MAX], s2[MAX];

void *LCS(void *arg);
int max(int a, int b);

int main()
{
    printf("\nEnter the string 1: ");
    scanf("%s", s1);

    printf("\nEnter the string 2: ");
    scanf("%s", s2);

    struct length *param = (struct length *)malloc(sizeof(struct length));

    param->len1 = strlen(s1);  //length of string 1
    param->len2 = strlen(s2);  //length of string 2

    pthread_t tid; //returns the thread id of thread created
    pthread_attr_t attr; //to define thread attributes
	pthread_attr_init(&attr); //initializes the thread attributes

    pthread_create(&tid, &attr, LCS, param); //creates a new thread
    
    int *max_len; //define the value from thread

    pthread_join(tid, (void *)&max_len); //wait for termination of the thread

    printf("\nLength of LCS: %d\n\n", *max_len);

    return 0;
}

void *LCS(void *arg)
{
    int len1 = ((struct length *)arg)->len1;
    int len2 = ((struct length *)arg)->len2;

    // Define return variable
	int *ret = malloc(sizeof(int));
	*ret = 0;

    if(len1 == 0 || len2 == 0)
        pthread_exit(ret); //to exit a thread

    if(s1[len1-1] == s2[len2-1])
    {
        // Define a new struct copied from the arg
		struct length arg_1 = *((struct length *)arg);
		--arg_1.len1;
		--arg_1.len2;

		// Recursively call the thread again
		pthread_t tid; //returns the thread id of thread created
        pthread_attr_t attr; //to define thread attributes
	    pthread_attr_init(&attr); //initializes the thread attributes
		pthread_create(&tid,&attr,LCS,(void *)&arg_1); //creates a new thread

		// Get return value from thread
		int *ret_1;
		pthread_join(tid,(void*)&ret_1);
		*ret = *ret_1 + 1;
	}
	else
	{
		// Define new structs copied from the arg
		struct length arg_1 = *((struct length*)arg);
		--arg_1.len2;

		struct length arg_2 = *((struct length*)arg);
		--arg_2.len1;

		// Recursively call the thread again
		pthread_t tid[2]; //returns the thread id of thread created
        pthread_attr_t attr; //to define thread attributes
	    pthread_attr_init(&attr); //initializes the thread attributes
		pthread_create(&tid[0],NULL,LCS,(void *)&arg_1);
		pthread_create(&tid[1],NULL,LCS,(void *)&arg_2);

		// Get return value from both threads
		int *ret_1, *ret_2;
		pthread_join(tid[0],(void*)&ret_1);
		pthread_join(tid[1],(void*)&ret_2);

		*ret = max(*ret_1,*ret_2);
	}
	pthread_exit(ret); //to exit a thread
}

int max(int a, int b)
{
	if(a > b)
		return a;
	return b;
}
