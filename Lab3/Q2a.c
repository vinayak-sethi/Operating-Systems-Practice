#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
	pid_t pid;
	int i,n;

	printf("Enter the vaue of n : ");
	scanf("%d", &n);

	pid = fork();

	if(pid == 0) //child block
	{
		printf("Child Process...\n");
		printf("First %d even numbers are : ", n);
		for(i=0; i<n; i++)
		{
			printf("%d  ",2*i);
		}
		printf("\n");
	}

	else
	{
		wait(NULL);
		printf("Parent Process...\n");
		printf("First %d odd numbers are : ", n);
		for(i=1; i<=n; i++)
		{
			printf("%d  ",2*i - 1);
		}
		printf("\n");
	}

	return 0;
}
