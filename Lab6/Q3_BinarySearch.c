#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdbool.h>
#include<pthread.h>

#define MAX_THREAD 4 //maximum number of threads

int mid = -1, i, key, size, part = 0, arr[10];
bool found = false;

void *runner(void *arg);
void bubblesort(int *arr, int n);
void swap(int *a,int *b);
void print(int *arr,int n);

int main( int argc, char *argv[])
{
	//Validate correct number of arguments
	if(argc < 3)
	{
		printf("\nWrong usage.. Syntax: %s <Key> <Array elements> \n\n", argv[0]);
        exit(EXIT_FAILURE);
	}

	key = atoi(argv[1]);  //search key
	size = argc - 2; //size of array

	int count = 0;
	pid_t pid;

	pthread_t *tid = (pthread_t *)malloc(MAX_THREAD*sizeof(pthread_t)); //returns the thread id of thread created
    pthread_attr_t attr; //to define thread attributes
	pthread_attr_init(&attr); //initializes the thread attributes

	printf("\nThe size of Array : %d", size);
	printf("\nThe Elements of the Array : ");
	for(i=2; i<argc; i++)
	{
		arr[i-2] = atoi(argv[i]);
		printf("%d  ", arr[i-2]);
	}

	printf("\nSearch key : %d", key);

	bubblesort(arr, size);
	printf("\nThe sorted array is : ");
	print(arr,size);

	for(i=0; i<MAX_THREAD; i++)
    {
        pthread_create(&tid[i], &attr, runner, NULL); //creates a new thread
        pthread_join(tid[i], NULL); //wait for termination of the thread
    }
	
	pid = vfork();

	if(pid == 0) //child block
	{
		i = mid - 1;
		while(i>=0 && arr[i] == key) //search for other positions where key can be present i.e. first half of mid
		{
			printf("\n%d found at index %d\n", key, i);
			i--;
		}

	 	if(found == false) //search for first appearance of key in array
	 	{
			printf("\n%d is not found in the array\n", key);
			exit(1);
		}
		else
			printf("\n%d found at index %d\n", key, mid);

		exit(0);
	}

	else //parent block
	{
		wait(NULL);

		i = mid + 1;
		while(i<size && arr[i] == key) //search for other positions where key can be present i.e. later half of mid
		{
			printf("%d found at index %d\n", key, i);
			i++;
		}
	}

	printf("\n");
	return 0;
}

void *runner(void *arg)
{
	// Each thread checks 1/4 of the array for the key 
	int thread_part = part++; 

	int low = thread_part * (size / 4); 
	int high = (thread_part + 1) * (size / 4); 

	// search for the key until low < high 
	// or key is found in any portion of array 
	while (low < high && !found)
	{ 
		// normal iterative binary search algorithm 
		mid = (high - low) / 2 + low; 

		if(arr[mid] == key) 
		{ 
			found = true; 
			break; 
		} 

		else if(arr[mid] > key) 
			high = mid - 1; 
		else
			low = mid + 1; 
	} 

	pthread_exit(0); //to exit a thread
}

void bubblesort(int *arr,int n)
{
	for(int i=0; i<n-1; i++)
	{
		for(int j=0; j<n-i-1; j++)
		{
			if(arr[j] > arr[j+1])
				swap(&arr[j],&arr[j+1]);
		}
	}
}

void swap(int *a,int *b)
{
	int c = *a;
	*a = *b;
	*b = c;
}

void print(int *arr,int n)
{
	for(int i=0; i<n; i++)
	{
		printf("%d  ",arr[i]);
	}
	printf("\n");
}
