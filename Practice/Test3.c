#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>

int main()
{
    int n = wait(NULL);
    printf("%d", n);
    printf("Hello world\n");
    return 0;
}