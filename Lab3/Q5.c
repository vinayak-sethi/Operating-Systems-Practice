#include<stdio.h>
#include<unistd.h>
#include<stdbool.h>
#include<sys/types.h>
#include<sys/wait.h>

void bubblesort(int *arr, int n, bool comp(const void* , const void*));
bool asc(const void* a, const void* b);
bool desc(const void* a, const void* b);
void swap(int *a,int *b);
void print(int *arr,int n);

int main()
{
	int i,size;
	int arr[size];
	pid_t pid;

	printf("Enter the size of Array : ");
	scanf("%d",&size);
	printf("Enter the Elements of the Array : ");
	for(i=0; i<size; i++)
	{
		scanf("%d", &arr[i]);
	}

	pid = fork();

	if(pid == 0) //child block
	{
		printf("Child Process...\n");
		printf("Array sorted in Descending order is : ");
		bubblesort(arr,size,desc);
		print(arr,size);
	}

	else //parent block
	{
		wait(NULL);
		printf("Parent Process...\n");
		printf("Array sorted in Ascending order is : ");
		bubblesort(arr,size,asc);
		print(arr,size);
	}

	return 0;
}

void bubblesort(int *arr,int n, bool comp(const void* , const void*))
{
	for(int i=0; i<n-1; i++)
	{
		for(int j=0; j<n-i-1; j++)
		{
			if(comp(&arr[j], &arr[j+1]))
				swap(&arr[j],&arr[j+1]);
		}
	}
}

bool asc(const void* a, const void* b)
{
	return *(int*)a > *(int*)b;
}

bool desc(const void* a, const void* b)
{
	return *(int*)a < *(int*)b;
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
