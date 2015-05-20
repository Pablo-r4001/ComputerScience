#include <stdio.h>
#include <cs50.h>
#include <string.h>

//Declared two functions, one to check for initials, and one to print them.
void letterCheck(string name);
void initPrinter(char init);

int main(void)
{
    // get name as string
    string nam = GetString();
    if(nam != NULL)
    {
        letterCheck(nam);
    }
}

void letterCheck(string name)
{
    initPrinter(name[0]);
    
    int iter = 0;
    int nameLength = strlen(name);
    
    while(iter < nameLength)
    {
        int letAsc = name[iter];
        if(letAsc == 32)
        {
            iter++;
            initPrinter(name[iter]);
        }
        else
        {
            iter++;
        }
    }
    printf("\n");
}

void initPrinter(char init)
{
    int inPos = init;
    if(inPos > 96 && inPos < 96 + 26)
    {
        inPos = inPos - 32;
    }
    init = inPos;
    printf("%c",init);  
}

