#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void ReverseString(char *string, int begin, int end);

int main()
{
    int pipefd1[2], pipefd2[2]; //0 -> read, 1 -> write

    char input_str[100];
    char reverse_str[100];
    pid_t pid;

    if(pipe(pipefd1) == -1)
    {
        printf("Unable to create pipe 1..\n");
        exit(EXIT_FAILURE);
    }

    if(pipe(pipefd2) == -1)
    {
        printf("Unable to create pipe 2..\n");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if(pid == 0) //child block
    {
        close(pipefd1[1]); //close writing end of parent pipe

        //Read a string from parent pipe
        read(pipefd1[0], reverse_str, 100);

        printf("\nIn Child :- String read from parent pipe: %s\n", reverse_str);
        
        //Reverse the string given by parent
        ReverseString(reverse_str, 0, strlen(reverse_str) - 1);

        //close both reading ends
        close(pipefd1[0]);
        close(pipefd2[0]);

        //Write reversed string and close the writing end
        write(pipefd2[1], reverse_str, 100);
        close(pipefd2[1]);
        
    }

    else //parent block
    {
        close(pipefd1[0]); // Close reading end of parent pipe

        printf("\nIn Parent :- Enter a string: ");
        gets(input_str);

        //write input string and close writing end of parent pipe
        write(pipefd1[1], input_str, strlen(input_str) + 1);
        close(pipefd1[1]);

        //wait for child to send the reverse string
        wait(NULL);

        close(pipefd2[1]); //close writing end of second pipe

        //read string from child, print it and close the reading end
        read(pipefd2[0], reverse_str, 100);
        printf("\nIn Parent :- Reversed string from child side: %s\n\n", reverse_str);
        close(pipefd2[0]);
    }

    return 0;
}

void ReverseString(char *string, int begin, int end)
{
    char c;

    if(begin >= end)
        return;

    c = *(string + begin);
    *(string + begin) = *(string + end);
    *(string + end) = c;

    ReverseString(string, ++begin , --end); 
}
