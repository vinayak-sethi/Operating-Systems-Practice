#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
	int a = 50;
	if((fork() == 0))
	a--;
	printf("%d",a);
	return 0;
}