//Forking Example 7
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
	pid_t pid;
	pid = fork(); //process 1 and 2

	if(pid > 0) //for parent 1
	{
		fork(); //process 1 and 3
		if(pid == 0) //process 3
		{
			fork(); //process 3 and 7
		}
	}

	else if (pid == 0) //for child 2
	{
		fork(); //process 2 and 4
		if (pid == 0) //for child 4
		{
			fork(); //process 4 and 8
		}
		else if (pid > 0) //for parent 2
		{
			fork(); // process 2 and 5
			fork(); // process 2 create 2 and 6, process 5 creates 5 and 9
		}
	}

	return 0;
}
