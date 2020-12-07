#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main(int argc, char ** argv)
{

	//Validate correct number of arguments
	if (argc < 2)
	{
		printf("Few arguments passed\n");
		exit(EXIT_FAILURE);
	}

	int i;

	//check if file exists or not
	for(i=1; i<=argc -1; i++)
	{
		char * filename = argv[i];
		if(access(filename,F_OK) != -1)  //check accessibilty of a file
			printf("File %s exist\n",argv[i]);
		else
			printf("File %s does not exist\n",argv[i]);
	}

	printf("\n");

	//remove the given files
	int del;

	for(i=1; i<= argc -1 ; i++)
	{
		del = remove(argv[i]);
		if(del == 0)
			printf("Successfully removed %s\n",argv[i]);
		else 
			printf("Cannot remove %s\n",argv[i]);
	}

	return 0;
}