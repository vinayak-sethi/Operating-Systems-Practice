#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
	pid_t pid;
	int i,n, sum=0;

	printf("Enter the value of n : ");
	scanf("%d", &n);

	pid = fork();

	if(pid == 0) //child block
	{
		printf("Child Process...\n");
		printf("Sum of Even terms till %d is : ",n);
		for(i=1; i<=n/2; i++)
		{
			sum = sum + 2*i;
		}
		printf("%d\n",sum);
	}

	else //parent block
	{
		wait(NULL);
		printf("Parent Process...\n");
		printf("Sum of Odd terms till %d is : ",n);
		if(n%2 == 0)
		{
			for(i=1; i<=n/2; i++)
			{
				sum = sum + (2*i - 1);
			}
			printf("%d\n",sum);
		}
		else
		{
			for(i=1; i<=(n/2 + 1); i++)
			{
				sum = sum + (2*i - 1);
			}
			printf("%d\n",sum);
		}
	}

	return 0;
}