#include <stdio.h>
#include <cs50.h>
#include <string.h>

// Declared two functions, one to check for initials, and one to print them.
void letterCheck(string name);
void initPrinter(char init);

int main(void)
{
    // get name as string
    string nam = GetString();
    if (nam != NULL)
    {
        letterCheck(nam);
    }
}
// Function for checking if character is printed
void letterCheck(string name)
{
    // first character is always printed
    initPrinter(name[0]);
    // change character to ASCII integer
    int iter = 0;
    int nameLength = strlen(name);
    // if the character is after a space
    while(iter < nameLength)
    {
        int letAsc = name[iter];
        // if character is a space, change character 
        // and call the init printer function
        if (letAsc == 32)
        {
            iter++;
            initPrinter(name[iter]);
        }
        // if character is after another character, simply go to next iteration
        else
        {
            iter++;
        }
    }
    printf("\n");
}

// this function checks if the character is lower or uppercase
void initPrinter(char init)
{
    // change character to ascci integer
    int inPos = init;
    // if character is lower case, change to uppercase
    if (inPos > 96 && inPos < 96 + 26)
    {
        inPos = inPos - 32;
    }
    // change back to character and print
    init = inPos;
    printf("%c",init);  
}

