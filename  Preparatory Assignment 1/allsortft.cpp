//sorting program using function template
#include<iostream>
#include<stdbool.h>
#include<string.h>
#include<sstream>
#include<ctype.h>
using namespace std;

template<typename T>
void bubblesortAsc(T *arr,int n) //using function template
{
	for(int i=0; i<n-1; i++)
	{
		for(int j=0; j<n-i-1; j++)
		{
			if(arr[j] > arr[j+1])
			{
				T c = arr[j+1];
				arr[j+1] = arr[j];
				arr[j] = c;
			}
		}
	}
}

template<typename T>
void bubblesortDesc(T *arr,int n)
{
	for(int i=0; i<n-1; i++)
	{
		for(int j=0; j<n-i-1; j++)
		{
			if(arr[j] < arr[j+1])
			{
				T c = arr[j+1];
				arr[j+1] = arr[j];
				arr[j] = c;
			}
		}
	}
}

template<typename T>
void print(T *arr,int n)
{
	cout << "Sorted Array is: ";
	for(int i=0; i<n; i++)
	{
		cout << arr[i] << "\t";
	}
	cout << "\n";
}

bool isallLen1(int argc, char *argv[]);
bool ischar(int argc, char *argv[]);
bool isint(int argc, char *argv[]);
bool isfloat(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	//Validate correct number of arguments
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
				bubblesortAsc<char>(chr_arr,size);
			if(choice == 2)
				bubblesortDesc<char>(chr_arr,size);
			print<char>(chr_arr,size);
			exit(EXIT_SUCCESS);
		}
		else
		{
			for(int i=4; i<=argc; i++) //or it is a integer of length 1
				int_arr[i-4] = atoi(argv[i-1]);
			if(choice == 1)
				bubblesortAsc<int>(int_arr,size);
			if(choice == 2)
				bubblesortDesc<int>(int_arr,size);
			print<int>(int_arr,size);
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
				bubblesortAsc<int>(int_arr,size);
			if(choice == 2)
				bubblesortDesc<int>(int_arr,size);
			print<int>(int_arr,size);
			exit(EXIT_SUCCESS);
		}
		else if(isfloat(argc,argv))
		{
			for(int i=4; i<=argc; i++) 
				flt_arr[i-4] = atof(argv[i-1]);
			if(choice == 1)
				bubblesortAsc<float>(flt_arr,size);
			if(choice == 2)
				bubblesortDesc<float>(flt_arr,size);
			print<float>(flt_arr,size);
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
    for(int i= 4; i<=argc; i++){
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
