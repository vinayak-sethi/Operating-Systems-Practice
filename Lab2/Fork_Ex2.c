//Forking Example 2
#include<stdio.h>
#include<unistd.h>

int main()
{
	printf("OS \n");
	fork(); //A
	fork(); //B
	fork(); //C
	return 0;
}