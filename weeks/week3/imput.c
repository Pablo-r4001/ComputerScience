
// Standard imput output
#include <stdio.h>

// Define constant
#define STUDENTS 3

int main(void)
{
	// scores to be added
	int scores[] = {96, 90, 83 };

	// to database file (overwrite)
	FILE* file = fopen("database", "w");
	
	// if the file was succesfully created
	if (file != NULL)
	{
		// add each score in a new line.
		for(int i = 0; i < STUDENTS; i++)
		{
			to the file
			fprintf(file, "%i\n", scores[i]);
		}
	}
	// and close it
	fclose(file);
}
