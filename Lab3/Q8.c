#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>

int buff[100];
int fib(int n);

int main()
{
	int n, i;
	printf("Enter the number of terms to be generated: ");
	scanf("%d", &n);

	for(i = 0; i <100; i++)
	{
		buff[i] = -1 ;
	}
	printf("The set of first '%d' fibonacci series numbers are { ", n);

	for(i=0; i<n; i++)
	{
		printf("%d, ", fib(i));
	}
	printf("\b\b }\n");

	return 0;
}

int fib(int n)
{
	int temp = 0;

	if (buff[n] == -1)
	{
		if (n <= 1)
			buff[n] = n;

		else
		{
			pid_t pid = vfork();
			
			if(pid == 0) //child block
			{
				temp += fib(n - 1);
				exit(0);
			}
			else //parent block
			{
				wait(NULL);
				temp += fib(n - 2);
			}
			
			buff[n] = temp;
		}
	}

	return buff[n];
}