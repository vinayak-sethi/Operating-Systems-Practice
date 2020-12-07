#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define MAX_THREAD 4
int arr[100];

struct limit
{
    int low;
    int high;
};

int partition(int low, int high);
void *QuickSort(void *arg);
void swap(int *a, int *b);

int main()
{
    struct limit *a = (struct limit *)malloc(sizeof(struct limit));

    int size;
	printf("\nEnter the size of the Array: ");
    scanf("%d", &size);

    printf("\nEnter the Elements of the Array : ");
	for(int i=0; i<size; i++)
	{
		scanf("%d", &arr[i]);
	}

    a->low = 0, a->high = size-1;

	pthread_t tid; //returns the thread id of thread created
    pthread_attr_t attr; //to define thread attributes
	pthread_attr_init(&attr); //initializes the thread attributes

    pthread_create(&tid, &attr, QuickSort, (void *)a); //creates a new thread
    pthread_join(tid, NULL); //wait for termination of the thread

    printf("\nSorted Array using Quick sort is: ");
    for(int i=0; i<size; i++)
    {
        printf("%d ",arr[i]);
    }

    printf("\n\n");
    return 0;
}

int partition(int low, int high)
{
    int pivot = arr[high]; // pivot 
    int i = (low - 1); // Index of smaller element 
  
    for (int j = low; j <= high- 1; j++) 
    { 
        // If current element is smaller than the pivot 
        if (arr[j] < pivot) 
        { 
            i++; // increment index of smaller element 
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
}

void *QuickSort(void *arg) 
{ 
    struct limit *a = (struct limit *)arg;
    int i;

    struct limit *left = (struct limit *)malloc(sizeof(struct limit)); //for left partition
    struct limit *right = (struct limit *)malloc(sizeof(struct limit)); //for right partition

    if (a->low < a->high) 
    { 
        int pi = partition(a->low, a->high); 

        left->low = a->low, left->high = pi-1;
        right->low = pi+1; right->high = a->high;

        pthread_t tid[2]; //returns the thread id of thread created
        pthread_attr_t attr; //to define thread attributes
	    pthread_attr_init(&attr); //initializes the thread attributes

	    pthread_create(&tid[0], &attr, QuickSort, (void *)left); //creates a new thread for left part
	    pthread_create(&tid[1], &attr, QuickSort, (void *)right); //creates a new thread for right part
    
        for(i=0; i<2; i++)
        {
            pthread_join(tid[i], NULL); //wait for termination of the thread
        }
    } 

    pthread_exit(0); //to exit a thread
}

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
