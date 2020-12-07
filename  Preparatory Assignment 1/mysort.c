//sorting program
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void bubblesortAsc(int *arr, int n);
void bubblesortDesc(int *arr, int n);
void swap(int *a,int *b);
void print(int *arr,int n);

int main(int argc, char ** argv)
{
	//Validate correct number of arguments
	if(argc < 4)
	{
		printf("Few arguments passed.\n");
		exit(EXIT_FAILURE);
	}

	int size = atoi(argv[1]);
	int choice = atoi(argv[2]);

	if(choice != 1 && choice != 2) 
	{
		printf("Incorrect choice entered.\n");
		exit(EXIT_FAILURE);
	}

	if(argc-3 != size)
	{
		printf("Enter array of specified size.\n");
		exit(EXIT_FAILURE);
	}

	int arr[size];
	char *a;

	// convert ascii to int
	for(int i = 4; i<= argc; i++)
	{
		arr[i-4] = atoi(argv[i-1]);
		sprintf(a, "%d", arr[i-4]); //convert int to string
		if(strcmp(a,argv[i-1]) != 0)
		{
			printf("Enter only integers!\n");
			exit(EXIT_FAILURE);
		}
	}

	if(choice == 1)
		bubblesortAsc(arr,size);
	if(choice == 2)
		bubblesortDesc(arr,size);

	printf("Sorted array is: ");
	print(arr,size);
	return 0;
}

void bubblesortAsc(int *arr,int n)
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

void bubblesortDesc(int *arr,int n)
{
	for(int i=0; i<n-1; i++)
	{
		for(int j=0; j<n-i-1; j++)
		{
			if(arr[j] < arr[j+1])
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