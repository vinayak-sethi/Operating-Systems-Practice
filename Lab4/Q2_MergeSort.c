#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>

void merge(int arr[], int low, int mid, int high);
void MergeSortParallel(int arr[], int low, int high);
void MergeSort(int arr[], int low, int high);
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
    MergeSortParallel(arr1, 0, size-1);
    t2 = clock();
    printf("\nSorted Array using Multiprocessing is: ");
    print(arr1, size);
    printf("\nTime taken by Multiprocessing merge sort is: %lf\n", (t2 - t1) / (double) CLOCKS_PER_SEC);
    
    t1 = clock();
    MergeSort(arr2, 0, size-1);
    t2 = clock();
    printf("\nSorted Array using Normalprocessing is: ");
    print(arr2, size);
    printf("\nTime taken by Normalprocessing merge sort is: %lf\n\n", (t2 - t1) / (double) CLOCKS_PER_SEC);
    return 0;
}

void merge(int arr[], int low, int mid, int high)
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

void MergeSortParallel(int arr[], int low, int high)
{
    if(low < high)
    {
        int mid = low + (high - low) / 2;
        pid_t pid;
        pid = vfork();
        if(pid == 0)
        {
            MergeSortParallel(arr, low, mid);
            exit(0);
        }
        else
        {
            MergeSortParallel(arr, mid + 1, high);
            merge(arr, low, mid, high);
        }
    }
}

void MergeSort(int arr[], int low, int high)
{
    if(low < high)
    {
        int mid = low + (high - low) / 2;
        MergeSort(arr, low, mid);
        MergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

void print(int arr[], int n)
{
    for(int i=0; i<n; i++)
    {
        printf("%d  ",arr[i]);
    }
}