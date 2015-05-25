#include <stdio.h>

int main (void)
{
	FILE* file = fopen("helloWorld", "w");

	if (file == NULL)
	{
		return 1;
	}
	
	fprintf(file, "Hello World");
	
	fclose(file);
	return 0;
}
