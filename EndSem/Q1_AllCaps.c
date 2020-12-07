#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<string.h>
#include<ctype.h>
#include<fcntl.h>

void print_uppercase(char buff);

int main(int argc,char *argv[])
{
    if(argc == 1)
    {
        printf("Invalid arguments !!\n try : ./<%s> filename\n",argv[0]);
        exit(1);
    }
    int fd1[2];
    char str[100];
    pid_t pid;
    if((pipe(fd1))== -1)
    {
        fprintf(stderr,"pipe failed");
        return 1;
    }
    FILE *fp;
    fp = fopen(argv[1],"r");
    pid = fork();
    if(pid == -1)
    {
        printf("fork failed\n");
        exit(1);
    }
    else if (pid == 0)
    {
        dup2(fd1[1],1);
        fp = fopen(argv[1],"r");
        close(fd1[0]);
        char ch;
        while ((ch = fgetc(fp)) != EOF)
        {
            write(fd1[1],&ch,sizeof(ch));
        }
        close(fd1[1]);
        exit(1);
    }
    else
    {
        close(fd1[1]);
        char buf;
        while(read(fd1[0],&buf,sizeof(buf))>0)
        {
            print_uppercase(buf);
        }
    }
    return 0;
}
void print_uppercase(char buff)
{
        printf("%c",toupper(buff));
}