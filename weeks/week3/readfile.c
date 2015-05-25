#include <stdio.h>

int main( int argc, char* argv[])
{	
	// check arguments are correct
	if (argc < 2)
	{
		printf("You're doing it wrong: readfile file [file...]\n");
		return 1;
	}

	// for each argument after the name of the file
	for(int i = 1; i < argc; i++)
	{
		// create pointer to the file being opened each time
		FILE* file = fopen(argv[i], "r");
		
		// check file exists
		if (file == NULL)
		{
			printf("readfile: %s: No such file in the directory", argv[i]);
			return 1;
		}
		// if the file exists, read each character until we get to EOF
		for (int c = fgetc(file); c != EOF; c = fgetc(file))
		{
			// rpint each character
			putchar(c);
		}
		
		// close file
		fclose(file);
	}
	// close program
	return 0;
}
