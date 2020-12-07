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

void merge(int low, int mid, int high);
void *MergeSort(void *arg);

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

    pthread_create(&tid, &attr, MergeSort, (void *)a); //creates a new thread
    pthread_join(tid, NULL); //wait for termination of the thread

    printf("\nSorted Array using Merge sort is: ");
    for(int i=0; i<size; i++)
    {
        printf("%d ",arr[i]);
    }

    printf("\n\n");
    return 0;
}

void merge(int low, int mid, int high)
{
    int i, j, k; 
    int n1 = mid - low + 1; 
    int n2 = high - mid; 
  
    /* create temp arrays */
    int L[n1], R[n2]; 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[low + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[mid + 1 + j]; 
  
    /* Merge the temp arrays back into arr[low..high]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = low; // Initial index of merged subarray 
    while (i < n1 && j < n2)
    { 
        if (L[i] <= R[j])
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there are any */
    while (i < n1)
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there are any */
    while (j < n2)
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
}

void *MergeSort(void *arg)
{
    struct limit *a = (struct limit *)arg;
    int i;

    struct limit *left = (struct limit *)malloc(sizeof(struct limit)); //for left partition
    struct limit *right = (struct limit *)malloc(sizeof(struct limit)); //for right partition

    if(a->low < a->high)
    {
        int mid = a->low + (a->high - a->low) / 2;

        pthread_t tid[2]; //returns the thread id of thread created
        pthread_attr_t attr; //to define thread attributes
	    pthread_attr_init(&attr); //initializes the thread attributes

        left->low = a->low, left->high = mid;
        right->low = mid+1, right->high = a->high;

	    pthread_create(&tid[0], &attr, MergeSort, (void *)left); //creates a new thread for left part
	    pthread_create(&tid[1], &attr, MergeSort, (void *)right); //creates a new thread for right part
    
        for(i=0; i<2; i++)
        {
            pthread_join(tid[i], NULL); //wait for termination of the thread
        }

        merge(left->low, mid, right->high);
    }

    pthread_exit(0); //to exit a thread
}
