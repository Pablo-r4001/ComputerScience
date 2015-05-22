#include <stdio.h>

#define STUDENTS 3

int main(void)
{
	int scores[] = {96, 90, 83 };
	FILE* file = fopen("database", "w");
	
	if (file != NULL)
	{
		for(int i = 0; i < STUDENTS; i++)
		{
			fprintf(file, "%i\n", scores[i]);
		}
	}
	fclose(file);
}
