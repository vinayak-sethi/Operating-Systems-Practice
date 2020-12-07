#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void GenerateSubstr(char *input_str, char *substr, int start, int end);

int main()
{
    int pipefd1[2], pipefd2[2]; //0 -> read, 1 -> write

    char input_str[100];
    char substr[100];
    int start, end;
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
        read(pipefd1[0], input_str, 100);

        printf("\nIn Child :- String read from parent pipe: %s\n", input_str);

        printf("\nIn Child :- Enter the start index for substring: ");
        scanf("%d", &start);
        printf("In Child :- Enter the end index for substring: ");
        scanf("%d", &end);

        //Generate the substring for the string given by parent
        GenerateSubstr(input_str, substr, start, end);

        //close both reading ends
        close(pipefd1[0]);
        close(pipefd2[0]);

        //Write substring and close the writing end
        write(pipefd2[1], substr, 100);
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

        //wait for child to send the substring
        wait(NULL);

        close(pipefd2[1]); //close writing end of second pipe

        //read substring from child, print it and close the reading end
        read(pipefd2[0], substr, 100);
        printf("\nIn Parent :- Substring generated from child side: %s\n\n", substr);
        close(pipefd2[0]);
    }

    return 0;
}

void GenerateSubstr(char *input_str, char *substr, int start, int end)
{
    int count = 0;

    while(count < (end - start) + 1)
    {
        substr[count] = input_str[start+count];
        count ++;
    }
    substr[count] = '\0';
}