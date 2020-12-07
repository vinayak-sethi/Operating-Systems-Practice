#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
    int pipefd1[2], pipefd2[2]; //0 -> read, 1 -> write

    char input_str1[100];
    char input_str2[100];
    char concat_str[100];
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
        sleep(5);
        close(pipefd2[0]); //close reading end of child pipe
        close(pipefd1[1]); //close writing end of parent pipe

        printf("\nIn Child :- Enter string 2: ");
        gets(input_str2);

        //write the input string to child pipe and close it
        write(pipefd2[1], input_str2, strlen(input_str2) + 1);
        close(pipefd2[1]);

        //read string from parent, print it and close the reading end
        read(pipefd1[0], concat_str, 100);
        printf("\nIn Child :- Concatenated string from parent side: %s\n\n", concat_str);
        close(pipefd1[0]);
    }

    else //parent block
    {
        close(pipefd1[0]); //close reading end of parent pipe
        close(pipefd2[1]); //close writing end of child pipe
        
        printf("\nIn Parent :- Enter string 1: ");
        gets(input_str1);

        //read the input string by child from the child pipe
        read(pipefd2[0], input_str2, 100);
        printf("\nIn Parent :- Strings to be concatenated are %s and %s\n", input_str1, input_str2);
        
        //Concat the child string to the parent string
        strcat(input_str1, input_str2);

        close(pipefd2[0]); //close reading end of second pipe
        
        //Write concatinated string and close the writing end of parent pipe
        write(pipefd1[1], input_str1, 100);
        close(pipefd1[1]);
    }

    return 0;
}