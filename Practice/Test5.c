#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

void sig_handler(int signum)
{
    printf("Inside handler function\n");
}

int main()
{
    signal(SIGUSR1, sig_handler);
    printf("Inside main function\n");
    raise(SIGUSR1);
    printf("Inside main function\n");

    return 0;
}