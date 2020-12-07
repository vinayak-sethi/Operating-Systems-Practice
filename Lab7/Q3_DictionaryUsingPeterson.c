#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<pthread.h>

//dictionary variables
char word[100][100];
char primary[100][1000];
char secondary[100][1000];
char search_word[100];
int size;

//0: Producer
//1: Consumer
bool flag[2] = {false, false}; //flag[i] = true means P(i) wants to enter the critical section
int turn = -1; //turn stores which variable is there in critical section

void filesize();
void create_dict();
void *producer(void *param);
void *consumer(void *param);
void search();

int main()
{
    filesize();
    pthread_t pid, cid; //returns the thread id of thread created
    pthread_attr_t attr1, attr2; //to define thread attributes

    //initializes the thread attributes
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);

    //creates a new thread
    pthread_create(&pid, &attr1, producer, NULL);
    pthread_create(&cid, &attr2, consumer, NULL);

    //wait for termination of the thread
    pthread_join(pid, NULL);
    pthread_join(cid, NULL);

    return 0;
}

void filesize()
{
    FILE *fp = fopen("Words.txt", "r");
    char c;
    for(c = getc(fp); c != EOF; c = getc(fp))
    {
        if(c == '\n') //whenever encounters a new line
            size += 1;
    }

    fclose(fp);
}

void create_dict()
{
    FILE *fp = fopen("Words.txt", "r");
    char c = fgetc(fp);
    for(int i=0; i<size; i++)
    {
        memset(word[i], 0, sizeof(word[i]));
        memset(primary[i], 0, sizeof(primary[i]));
        memset(secondary[i], 0, sizeof(secondary[i]));

        //stores word
        int index = 0;
        while (c != ';')
        {
            word[i][index++] = c;
            c = fgetc(fp);
        }

        //stores primary meaning
        index = 0;
        c = fgetc(fp);
        while (c != ';')
        {
            primary[i][index++] = c;
            c = fgetc(fp);
        }

        //stores secondary meaning
        index = 0;
        c = getc(fp);
        while (c != '$')
        {
            secondary[i][index++] = c;
            c = fgetc(fp);
        }

        //for last ($) and EOF
        for (int j = 0; j < 2; j++)
            c = fgetc(fp);
    }

    fclose(fp);
}

void *producer(void *param)
{
    printf("\n[PRODUCER] Setting up the Dictionary...\n");
    flag[0] = true;
    turn = 1;
    while(flag[1] && turn == 1); //means consumer is inside Critical Section 
    
    //Critical Section starts
    create_dict();

    flag[0] = false; //exit condition from Critical Section

    pthread_exit(0); //to exit a thread
}

void *consumer(void *param)
{
    printf("[CONSUMER] Enter the word to be searched : ");
    scanf("%s", search_word);
    
    flag[1] = true;
    turn = 0;

    while(flag[0] && turn == 1); //means producer is inside Critical Section 
    
    //Critical Section starts
    search();

    flag[1] = false; //exit condition from Critical Section
        
    pthread_exit(0); //to exit a thread
}

void search()
{
    int flag = 0;
    for(int i=0; i<size; i++)
    {
        if(strcmp(word[i], search_word) == 0) 
        {
            printf("\nWord found in the dictionary by the Consumer\n\n\tWord:\t\t\t%s\n\tPrimary Meaning:\t%s\n\tSecondary Meaning:\t%s\n\n", word[i], primary[i], secondary[i]);
            flag = 1;
        }
    }
    if(flag == 0)
            printf("\nWord cannot be searched by Consumer as it is not present in Dictionary\n\n");
}