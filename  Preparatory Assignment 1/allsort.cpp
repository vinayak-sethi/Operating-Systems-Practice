//sorting function using function overloading
#include<iostream>
#include<stdbool.h>
#include<string.h>
#include<sstream>
#include<ctype.h>
using namespace std;

void bubblesortAsc(int *arr, int n);
void bubblesortDesc(int *arr, int n);
void swap(int *a,int *b);
void print(int *arr,int n);

void bubblesortAsc(float *arr, int n);
void bubblesortDesc(float *arr, int n);
void swap(float *a,float *b);
void print(float *arr,int n);

void bubblesortAsc(char *arr, int n);
void bubblesortDesc(char *arr, int n);
void swap(char *a,char *b);
void print(char *arr,int n);

bool isallLen1(int argc, char *argv[]);
bool ischar(int argc, char *argv[]);
bool isint(int argc, char *argv[]);
bool isfloat(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	//Validate correct number of argumentsclear
	
	if(argc < 4)
	{
		cout << "Few arguments passed.\n";
		exit(EXIT_FAILURE);
	}

	int size = atoi(argv[1]);
	int choice = atoi(argv[2]);

	if(choice != 1 && choice != 2)
	{
		cout << "Incorrect choice entered.\n";
		exit(EXIT_FAILURE);
	}

	if(argc-3 != size)
	{
		cout << "Enter array of specified size.\n";
		exit(EXIT_FAILURE);
	}

	int int_arr[size];
	float flt_arr[size];
	char chr_arr[size];

	if(isallLen1(argc,argv))
	{
		if(ischar(argc,argv)) //either it is a character
		{
			for(int i=4; i<=argc; i++)
				chr_arr[i-4] = argv[i-1][0];
			if(choice == 1)
				bubblesortAsc(chr_arr,size);
			if(choice == 2)
				bubblesortDesc(chr_arr,size);
			print(chr_arr,size);
			exit(EXIT_SUCCESS);
		}
		else
		{
			for(int i=4; i<=argc; i++) //or it is a integer of length 1
				int_arr[i-4] = atoi(argv[i-1]);
			if(choice == 1)
				bubblesortAsc(int_arr,size);
			if(choice == 2)
				bubblesortDesc(int_arr,size);
			print(int_arr,size);
			exit(EXIT_SUCCESS);
		}
	}

	else
	{
		if(isint(argc,argv))
		{
			for(int i=4; i<=argc; i++) 
				int_arr[i-4] = atoi(argv[i-1]);
			if(choice == 1)
				bubblesortAsc(int_arr,size);
			if(choice == 2)
				bubblesortDesc(int_arr,size);
			print(int_arr,size);
			exit(EXIT_SUCCESS);
		}
		else if(isfloat(argc,argv))
		{
			for(int i=4; i<=argc; i++) 
				flt_arr[i-4] = atof(argv[i-1]);
			if(choice == 1)
				bubblesortAsc(flt_arr,size);
			if(choice == 2)
				bubblesortDesc(flt_arr,size);
			print(flt_arr,size);
			exit(EXIT_SUCCESS);
		}
		else
			{
				cout << "Invalid input, check again...\n";
				exit(EXIT_FAILURE);
			}
	}

    return 0;
}

bool isallLen1(int argc, char *argv[])
{
	for (int i=4; i<=argc; i++)
	{
		if (strlen(argv[i-1]) != 1)
			return false;
	}
	return true;
}

bool ischar(int argc, char *argv[])
{
	for(int i=4; i<=argc; i++)
	{
		if(isalpha(argv[i-1][0]) != 0) //check if it is an alphabet or not
			return true;
	}
	return false;
}

bool isint(int argc, char *argv[])
{
	int x;
    string a;
    for(int i=4; i<=argc; i++){
        x = atoi(argv[i-1]);
        a = to_string(x);
        string y = string(argv[i-1]);
        if(y.compare(a) != 0)
            return false;
    }
    return true;
}

bool isfloat(int argc, char *argv[])
{
    float x;
    string a;
    for(int i=4; i<=argc; i++)
    {
    	x = atof(argv[i-1]);
        stringstream ss;
        ss << x;
        a = ss.str();
        string y = string(argv[i-1]);
        if(y.compare(a) != 0)
        	return false;
    }
    return true;
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

void bubblesortAsc(float *arr,int n)
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

void bubblesortDesc(float *arr,int n)
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

void bubblesortAsc(char *arr,int n)
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

void bubblesortDesc(char *arr,int n)
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

void swap(float *a,float *b)
{
	float c = *a;
	*a = *b;
	*b = c;
}

void swap(char *a,char *b)
{
	char c = *a;
	*a = *b;
	*b = c;
}

void print(int *arr,int n)
{
	cout << "Sorted Array is: ";
	for(int i=0; i<n; i++)
	{
		cout << arr[i] << "\t";
	}
	cout << "\n";
}

void print(float *arr,int n)
{
	cout << "Sorted Array is: ";
	for(int i=0; i<n; i++)
	{
		cout << arr[i] << "\t";
	}
	cout << "\n";
}

void print(char *arr,int n)
{
	cout << "Sorted Array is: ";
	for(int i=0; i<n; i++)
	{
		cout << arr[i] << "\t";
	}
	cout << "\n";
}