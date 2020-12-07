#include<stdio.h>
#include<stdlib.h>

int main(int argc, char ** argv)
{
	//Validate correct number of arguments
	if(argc < 3)
	{
		printf("Few arguments are passed\n");
		exit(EXIT_FAILURE);
	}
	else if(argc > 3)
	{
		printf("More arguments are passed\n");
		exit(EXIT_FAILURE);
	}


	//Copy file from One location to Another
	char ch;
	FILE *source, *target;

	source = fopen(argv[1] , "r");
	if(source == NULL)
	{
		printf("\nPress any key to exit...");
		exit(EXIT_FAILURE);
	}

	target = fopen(argv[2] , "w");
	if(target == NULL)
	{
		fclose(source);
		printf("\nError copying to target...");
		exit(EXIT_FAILURE);
	}

	while((ch = fgetc(source))!= EOF)
		fputc(ch, target);

	printf("\nFile copied successfully!\n");

	fclose(source);
	fclose(target);

	return 0;
}