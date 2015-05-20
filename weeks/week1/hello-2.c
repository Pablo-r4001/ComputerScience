#include <cs50.h>
#include <stdio.h>

int main(void)
{
	printf("Identification, please: ")
	string s = GetString();
	printf("hello, %s\n", s);
}