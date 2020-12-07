#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdbool.h>

int binarysearch(int *a, int n, int x);
void bubblesort(int *arr, int n);
void swap(int *a,int *b);
void print(int *arr,int n);

int main()
{
	int size, mid, x, i, count = 0;
	int arr[size];
	pid_t pid;

	printf("Enter the size of Array : ");
	scanf("%d",&size);
	printf("Enter the Elements of the Array : ");
	for(i=0; i<size; i++)
	{
		scanf("%d", &arr[i]);
	}

	printf("\nEnter the search key: ");
	scanf("%d", &x);

	bubblesort(arr, size);
	printf("\nThe sorted array is: ");
	print(arr,size);
	
	pid = vfork();

	if(pid == 0) //child block
	{
	 	if((mid = binarysearch(arr, size, x)) == -1)
	 	{
			printf("\n%d is not found in the array\n", x);
			exit(1);
		}
		else
			printf("\n%d found at index %d\n", x, mid);
		
		i = mid - 1;
		while(i > -1 && arr[i] == x)
		{
			printf("%d found at index %d\n", x, i);
			i--;
		}
	
		exit(0);
	}

	else //parent block
	{
		wait(NULL);
		i = mid + 1;
		while(i<size && arr[i] == x)
		{
			printf("%d found at index %d\n", x, i);
			i++;
		}
	}

	return 0;
}

int binarysearch(int* a, int n, int x)
{
	int left = 0, right = n - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if(a[mid] == x)
			return mid;
		else if(a[mid] < x)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return -1;
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
		printf("%d\t",arr[i]);
	}
	printf("\n");
}
