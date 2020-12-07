#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void Fibonacci(int n);
void Prime(int n);

int main()
{
	pid_t pid;
	int i,n;

	printf("Enter the value of n: ");
	scanf("%d", &n);

	pid = fork();

	if(pid == 0) //child block
	{
		printf("Child Process...\n");
		printf("Prime numbers till %d are : ",n);
		Prime(n);
	}
	
	else //parent block
	{
		wait(NULL);
		printf("Parent Process...\n");
		printf("Fibonacci Series till %d is : ",n);
		Fibonacci(n);	
	}

	return 0;
}

void Fibonacci(int n)
{
	int sum = 0, a = 0, b = 1;
	while(sum <= n)
	{
		printf("%d  ", sum);
		a = b; //swap elements
		b = sum;
		sum = a+b; // next term
	}
	printf("\n");
}

void Prime(int n)
{
	int i,j;
	for(i=2; i<=n; i++)
	{
		int count=0;
		for(j=1; j<=i; j++)
		{
			if(i%j == 0)
				count++;
		}

		if(count == 2)
			printf("%d  ",i);
	}
	printf("\n");
}