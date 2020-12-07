#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<sys/wait.h>
#include<sys/mman.h>
#include<unistd.h>

FILE * openFile(char * filename) // open a file in read mode and return the pointer
{
    FILE * file;
    file = fopen(filename, "r");

    if(!file)
    {
        printf("Error!\n");
        return NULL;
    }

    return file;
}

void outputResults(int * charCount)
{
    long numbers_letters = 0;
    long total_characters = 0;

    for(int i = 32; i < 128; i = i+1)
    {
        total_characters = total_characters + charCount[i];
        if(i >= 97 && i <= 122)
        {
            numbers_letters = numbers_letters + charCount[i];
    	}
    }

    printf("\n\t ALPHABETS FREQUENCY \n\n");
    printf("| Letter |  Count\t  [%%]\t\tGraphical\n");
    printf("| ------ | --------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 97; i < 123; i = i+1)
    {
        printf("|   %c    |  %0d ", i, charCount[i]);
        printf("  \t%.2f%%\t\t", ((double)charCount[i] / numbers_letters) * 100);
        	
        for(int j = 0; j < charCount[i]; j = j+1)
        {
            printf("♦");
        }
            printf("\n");
    }

    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\n\t FILE DATA STATISTICS \n\n");
    printf("| Char Type |  Count\t  [%%]\n");
   	printf("|---------- | ---------------------\n");

    printf("|  Letters  |  %li", numbers_letters);
    printf(" \t[%.2f%%]  |\n", ((double)numbers_letters / total_characters) * 100);
    printf("|  Other    |  %li", total_characters - numbers_letters);
    printf(" \t[%.2f%%]  |\n", ((double)(total_characters - numbers_letters) / total_characters) * 100);
    printf("|  Total    |  %li\t\t  |\n\n", total_characters);
}

int * countLetters(char * filename)
{
    int * charCount;
    FILE * file;

    charCount = mmap(NULL, 128 * sizeof( * charCount), PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    for(int i = 0; i < 27; i++)
    {
        int c;

        if((file = openFile(filename)) == NULL)
        {
            printf("Error opening file. %s\n", filename);
            exit(1);
        }

        pid_t pid = fork();

        if (pid == -1) 
        {
            exit(1);
        }
        else if (pid == 0)
        {
            while((c = tolower(fgetc(file))) != EOF)
            {
                if(i == 26 && (c < 97 || c > 122))
                    charCount[c]++; // Count other char
                else if (c == i + 97)
                    charCount[i + 97] += 1; // Count letters
            }

            fclose(file);
            exit(0);
        }
        else
            rewind(file);
    }

    for(int i = 0; i < 27; i++)
        wait(NULL);

    return charCount;
}

int main(int argc, char * argv[]) //command line arguments
{
    if(argc != 2) 
    {
        printf("Syntax: ./a.out <filename>\n");
        exit(EXIT_FAILURE);
    }

    char * filename = argv[1];
    FILE * file;

    if((file = openFile(filename)) == NULL)
        return 1;

    outputResults(countLetters(filename));

    if (fclose(file) != 0)
    {
        printf("Error closing file!\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}