#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<pthread.h>

struct array
{
	int a[100];
	int size;
};

void *runner1(void *arg); //for ascending order sort
void *runner2(void *arg); //for descending order sort
void bubblesort(int *arr, int n, bool(*oprn)(const void *,const void *)); //using function pointer
bool asc(const void *a, const void *b);
bool desc(const void *a, const void *b);
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
	arr->size = argc - 1;

	printf("\nThe size of Array : %d", arr->size);
	printf("\nThe Elements of the Array : ");
	for(int i=1; i<argc; i++)
	{
		arr->a[i-1] = atoi(argv[i]);
	}
	print(arr->a, arr->size);

	pthread_t tid1, tid2; //returns the thread id of thread created
    pthread_attr_t attr; //to define thread attributes
    pthread_attr_init(&attr); //initializes the thread attributes

    pthread_create(&tid1, &attr, runner1, arr); //creates a new thread for ascending sort
	pthread_create(&tid2, &attr, runner2, arr); //creates a new thread for descending sort
    
	pthread_join(tid1, NULL); //wait for termination of the thread1
	pthread_join(tid2, NULL); //wait for termination of the thread2

	printf("\n");
	return 0;
}

void *runner1(void *arg)
{
	struct array *arr = (struct array *)arg;
	printf("\nArray Sorted in Ascending order : ");
	bubblesort(arr->a, arr->size,asc);
	print(arr->a, arr->size);

	pthread_exit(0); //to exit a thread
}

void *runner2(void *arg)
{
	struct array *arr = (struct array *)arg;
	printf("Array Sorted in Descending order : ");
	bubblesort(arr->a, arr->size, desc);
	print(arr->a, arr->size);

	pthread_exit(0); //to exit a thread
}

void bubblesort(int *arr,int n, bool(*oprn)(const void *,const void *))
{
	for(int i=0; i<n-1; i++)
	{
		for(int j=0; j<n-i-1; j++)
		{
			if(oprn(&arr[j],&arr[j+1]))
				swap(&arr[j],&arr[j+1]);
		}
	}
}

bool asc(const void *a, const void *b)
{
	return *(int *)a > *(int *)b;
}

bool desc(const void *a, const void *b)
{
	return *(int *)a < *(int *)b;
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
		printf("%d ",arr[i]);
	}
	printf("\n");
}