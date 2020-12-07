//Forking Example 1
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
	pid_t pid;
	pid = fork(); //A
	if (pid != 0)
	fork(); //B
	fork(); //C
	printf("Count \n");
	return 0;
}