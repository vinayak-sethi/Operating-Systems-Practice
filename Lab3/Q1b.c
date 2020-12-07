#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main()
{
	pid_t pid = fork();

	if(pid < 0)
		printf("Fork failed \n");

	else if(pid == 0) //child process
		execlp("ls", "ls", "-LR", NULL);

	else
	{
		printf("Parent Process \n");
		wait(NULL); //parent waits for the child to complete execution
		printf("Parent waited for completion of child process \n");
	}

	return 0;
}