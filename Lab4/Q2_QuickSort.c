#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>

int partition(int arr[], int low, int high);
void QuickSortParallel(int arr[], int low, int high);
void QuickSort(int arr[], int low, int high);
void swap(int *a, int *b);
void print(int arr[], int n);

int main()
{
    int i, size;
    clock_t t1, t2;
    printf("Enter the size of the Array: ");
    scanf("%d", &size);
    int arr1[size], arr2[size];

    for(i=0; i<size; i++)
    {
        int x = rand();  //Filling the random numbers
        arr1[i] = arr2[i] = x;
    }

    printf("\nUnsorted Array is: ");
    print(arr1, size);
    printf("\n");
    t1 = clock();
    QuickSortParallel(arr1, 0, size-1);
    t2 = clock();
    printf("\nSorted Array using Multiprocessing is: ");
    print(arr1, size);
    printf("\nTime taken by Multiprocessing merge sort is: %lf\n", (t2 - t1) / (double) CLOCKS_PER_SEC);
    
    t1 = clock();
    QuickSort(arr2, 0, size-1);
    t2 = clock();
    printf("\nSorted Array using Normalprocessing is: ");
    print(arr2, size);
    printf("\nTime taken by Normalprocessing merge sort is: %lf\n\n", (t2 - t1) / (double) CLOCKS_PER_SEC);
    return 0;
}

int partition(int arr[], int low, int high)
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

void QuickSortParallel(int arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now 
           at right place */
        int pi = partition(arr, low, high); 
        pid_t pid;
        pid = vfork();
        // Separately sort elements before partition and after partition 
        if(pid == 0)
        {
            QuickSort(arr, low, pi - 1); 
            exit(0);
        }
        else
        {
            QuickSort(arr, pi + 1, high);
        }
    } 
}

void QuickSort(int arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        int pi = partition(arr, low, high); 
        QuickSort(arr, low, pi - 1); 
        QuickSort(arr, pi + 1, high); 
    } 
} 

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void print(int arr[], int n)
{
    for(int i=0; i<n; i++)
    {
        printf("%d  ",arr[i]);
    }
}