#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<time.h>

int GetMax(int *arr, int n); //finds the maximum element in the array
void radixsort(int *arr, int n); 

void bubblesort(int *arr,int n);
void swap(int *a,int *b);

void insertionsort(int *arr, int n);

void print(int arr[], int n);

int main()
{
    int i, size;
    clock_t t1, t2;
    printf("\nEnter the size of the Array: ");
    scanf("%d", &size);

    int lower, upper;
    int arr1[size], arr2[size], arr3[size];

    //to take the range of elements to be entered in array using rand() function
    printf("\nEnter the smallest value in array : "); 
    scanf("%d", &lower);
    printf("Enter the largest value in an array : ");
    scanf("%d", &upper);

    for(i=0; i<size; i++)
    {
        int num = (rand() % (upper - lower + 1)) + lower; //Filling the random numbers
        arr1[i] = arr2[i] = arr3[i] = num;
    }

    printf("\nUnsorted Array is: ");
    print(arr1, size);
    printf("\n");
    printf("\nRadix Sort starting...\n\n");
    t1 = clock(); //start of clock
    radixsort(arr1, size);
    t2 = clock(); //end of clock
    printf("\nSorted Array using Multiprocessing version of radix sort is: ");
    print(arr1, size);
    printf("\nTime taken by Multiprocessing radix sort is: %lf\n", (t2 - t1) / (double) CLOCKS_PER_SEC);
    

    printf("\nBubble sort starting...\n");
    t1 = clock(); //start of clock
    bubblesort(arr2, size);
    t2 = clock(); //end of clock
    printf("\nSorted Array using Sequential Bubble sort is: ");
    print(arr2, size);
    printf("\nTime taken by Sequential Bubble sort is: %lf\n\n", (t2 - t1) / (double) CLOCKS_PER_SEC);

    printf("Insertion Sort starting...\n");
    t1 = clock(); //start of clock
    insertionsort(arr3, size);
    t2 = clock(); //end of clock
    printf("\nSorted Array using Sequential Insertion Sort is: ");
    print(arr3, size);
    printf("\nTime taken by Sequential Insertion sort is: %lf\n\n", (t2 - t1) / (double) CLOCKS_PER_SEC);
    
    return 0;
}

int GetMax(int *arr, int n)
{
    int max = arr[0];
    for(int i=1; i<n; i++)
        if(arr[i] > max)
            max = arr[i];

  return max;
}

void radixsort(int *arr, int n)
{
    int bucket[10][10], bucket_cnt[10];
    int i, j, k, r, NOP = 0, divisor = 1, lar, pass;
    lar = GetMax(arr, n); //finds the largest number in array
    while (lar > 0)
    {
        NOP++; //stores the total number of digits of largest number
        lar /= 10;
    }

	pid_t pid;

    for(pass = 0; pass < NOP; pass++) 
    {
    	if((pid = vfork()) == 0)
        {
		    for(i = 0; i < 10; i++)
		    {
		        bucket_cnt[i] = 0; //initialize complete bucket with 0
		    }
		    exit(0);
        }

        else
        {
		    wait(NULL);
		    pid_t pid1;
		    if((pid1 = vfork() == 0))
            {
                //starts from LSB to MSB
				for(i = 0; i < n; i++)
				{
				    r = (arr[i] / divisor) % 10; //stores the digit of number
				    bucket[r][bucket_cnt[r]] = arr[i]; //store the number at the corresponding index equivalent to digit
				    bucket_cnt[r] += 1; //if same digits encountered increase the index value
				}
				exit(0);
		    }
			else
            {
				wait(NULL);
				i = 0;
				for(k = 0; k < 10; k++)
				{
				    for(j = 0; j < bucket_cnt[k]; j++)
				    {
				        arr[i] = bucket[k][j]; //sorted array is stored 
				        i++;
				    }
				}
		    }
        }

        divisor *= 10; //switch to next digit
        printf ("After Pass : %d\n", pass + 1);
        for(i = 0; i < n; i++)
            printf ("%d ", arr[i]);
        
        printf ("\n");
   }
}

void bubblesort(int *arr,int n)
{
	for(int i=0; i<n-1; i++)
	{
        printf("\nAfter Pass : %d\n", i+1); 
        for(int i=0; i<n; i++)
            printf("%d ", arr[i]);
		
        for(int j=0; j<n-i-1; j++)
		{
			if(arr[j] > arr[j+1])
            {
				swap(&arr[j],&arr[j+1]);
            }
		}
	}
    printf("\n");
}

void swap(int *a,int *b)
{
	int c = *a;
	*a = *b;
	*b = c;
}

void insertionsort(int *arr, int n)
{
    int i, key, j; 
    for(i = 1; i < n; i++)
    {
        printf("\nAfter Pass : %d\n", i);
        for(int i=0; i<n; i++)
            printf("%d ", arr[i]);
        key = arr[i]; 
        j = i - 1; 
  
        /* Move elements of arr[0..i-1], that are 
          greater than key, to one position ahead 
          of their current position */
        while(j >= 0 && arr[j] > key)
        { 
            arr[j + 1] = arr[j];
            j = j - 1; 
        } 
        arr[j + 1] = key; 
    } 

    printf("\n");
}

void print(int arr[], int n)
{
    for(int i=0; i<n; i++)
    {
        printf("%d  ",arr[i]);
    }
}