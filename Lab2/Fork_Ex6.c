//Forking Example 6
#include<stdio.h>
#include<unistd.h>

int main()
{
	printf("A");
	fork(); //A
	printf("B");
	return 0;
}