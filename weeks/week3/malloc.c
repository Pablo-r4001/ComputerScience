#include <stdio.h>
#include <cs50.h>

int main(void)
{
	// call memory allocate for size of an int (usually 4 bytes)
	int* ptr = malloc(sizeof(int));
	
	// check if the ptr pointer is null
	if (ptr== NULL)
	{
		printf("Error -- out of memory.\n");
		return 1;
	}
	
	// ask for an int for the 
	// dereferenced value of ptr and print
	*ptr = GetInt();
	printf("you entered %d.\n", *ptr);
	
	// call free to free the memory allocated.
	free(ptr);

}
