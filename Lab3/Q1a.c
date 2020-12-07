#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main()
{
	pid_t pid;
	pid = fork();
	if(pid == 0) //child process
		execl("/bin/ls", "ls", NULL); //child image is now ls command
	else
	{
		printf("Parent Process gets the control \n");
		wait(NULL); //parent waits for the child to complete execution
		printf("Parent has waited for Child to Complete");
	}

	return 0;
}