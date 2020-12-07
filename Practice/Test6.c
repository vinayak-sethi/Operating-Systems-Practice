#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
    for(int i=0; i<2; i++)
    {
        if(fork() == 0)
            printf("OS 2020\n");
    }

    return 0;
}