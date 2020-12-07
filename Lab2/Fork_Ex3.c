//Forking Example 3
#include<stdio.h>
#include<unistd.h>

int main()
{
	printf("This will be printed ?.\n");
	fork(); //A
	printf("This will be printed ?.\n");
	fork(); //B
	printf("This will be printed ? .\n");
	fork(); //C
	printf("This will be printed ?\n");
	return 0;
}