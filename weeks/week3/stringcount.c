#include <stdio.h>

// prints the number of chars per string

int main(void)
{
	char* str = "happy cat";
	int counter = 0;
	
	for(char* ptr = str; *ptr != '\0'; ptr++)
	{
		counter++;
	}

	printf("%d\n",counter);
}	
