#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

struct array
{
	int a[100];
	int size;
};

void *Mean(void *arg);
void *Median(void *arg);
void *Mode(void *arg);
void bubblesort(int *arr, int n);
void swap(int *a,int *b);
void print(int *arr,int n);

int main(int argc, char *argv[])
{
	//Validate correct number of arguments
	if(argc < 2)
	{
		printf("\nWrong usage.. Syntax: %s <Array elements> \n\n", argv[0]);
        exit(EXIT_FAILURE);
	}

	struct array *arr = (struct array *)malloc(sizeof(struct array));

	arr->size = argc - 1; //size of array

	pthread_t tid[3]; //returns the thread id of thread created
    pthread_attr_t attr; //to define thread attributes
	pthread_attr_init(&attr); //initializes the thread attributes

	printf("\nThe size of Array : %d", arr->size);
	printf("\nThe Elements of the Array : ");
	for(int i=1; i<argc; i++)
	{
		arr->a[i-1] = atoi(argv[i]);
		printf("%d  ", arr->a[i-1]);
	}

	bubblesort(arr->a, arr->size);
	printf("\nThe sorted array is: ");
	print(arr->a,arr->size);

	pthread_create(&tid[0], &attr, Mean, (void *)arr); //creates a new thread for computing mean
	pthread_create(&tid[1], &attr, Median, (void *)arr); //creates a new thread for computing median
	pthread_create(&tid[2], &attr, Mode, (void *)arr); //creates a new thread for computing mode

	for(int i=0; i<3; i++)
	{
		pthread_join(tid[i], NULL); //wait for termination of the thread
	}

	printf("\n");
	return 0;
}

void *Mean(void *arg)
{
	printf("\nThread 1...");
	struct array *arr = (struct array *)arg;
	int sum = 0;
	
	for(int i=0; i<arr->size; i++)
		sum += arr->a[i]; //store the sum of elements of array

	printf("\n\tMean of given array elements: %f\n",(float)sum / arr->size);
	
	pthread_exit(0); //to exit a thread
}

void *Median(void *arg)
{
	printf("\nThread 2...");
	struct array *b = (struct array *)arg;
	bubblesort(b->a, b->size); //sort the elements
	printf("\n\tMedian of given elements: %d\n",b->a[b->size/2]); //choose the middle element

	pthread_exit(0); //to exit a thread
}

void *Mode(void *arg)
{
	printf("\nThread 3...");
	struct array *c = (struct array *)arg;
	int i, j, count = 0, maxcount = 0, maxvalue = 0;

	for(i=0; i<c->size; i++)
	{
		int count = 0;
		for(j=0; j<c->size; j++)
		{
			if(c->a[j] == c->a[i])
				count++; //frequency of given array element
		}

		if(count > maxcount)
		{
			maxcount = count; //max frequency of an array element
			maxvalue = c->a[i]; //array element with maximum frequency
		}
	} 

	printf("\n\tMode of give array elements: %d with frequency %d\n", maxvalue, maxcount);

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