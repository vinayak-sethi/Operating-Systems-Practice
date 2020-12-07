#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<math.h>

int main()
{
	 int start, end;
	 printf("Enter the starting number of the range: ");
	 scanf("%d", &start);
	 printf("Enter the ending number of the range: ");
	 scanf("%d", &end);

	 int n = end - start + 1, temp, count = 0, digit, i;
	 int arr[n];

	 for(i = 0; i < n; i++)
	 		arr[i] = 0;

	 pid_t pid = vfork();

	 if(pid == 0) //child block
	 {
	 	for(i = start; i < end + 1; i++)
	 	{
	 		temp = i;

			while(temp != 0)
	 		{
	 			temp /= 10;
				count++;
	 		}

	 		temp = i;

	 		while(temp != 0)
			{
	 			digit = temp % 10;
	 			temp /= 10;
	 			arr[i - start] += pow(digit, count);
	 		}
	 		count = 0;
	 	}
	 	exit(0);
	 }

	 else //parent block
	 {
	 	wait(NULL);
	 	printf("Set of Armstrong numbers between %d and %d are { ", start, end);
	 	for(i = start; i < end + 1; i++)
	 		if(arr[i - start] == i)
	 			printf("%d, ", i);
	 	printf("\b\b }\n");
	 }

	 return 0;
}