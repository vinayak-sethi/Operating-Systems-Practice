#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

int main()
{
int i, p, pid;

pid = fork(); // create child process

if (pid == 0) // execution of child
{
for (i=1; i<=10; i++)
{
if (i % 2 != 0) // if odd number
printf("Child = %d \n", i);
sleep (1); // pause and goes to parent
}
}

else // execution of parent
{
for (p=1; p<=10; p++)
{
if (p % 2 == 0) // if even number
printf("parent = %d \n", p);
sleep (1); // pause and goes to child
}
}
}