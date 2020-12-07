//Forking Example 5
#include<stdio.h>
#include<unistd.h>

int main()
{
	printf("OS ");
	fork(); //A
	fork(); //B
	fork(); //C
	return 0;
}