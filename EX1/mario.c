#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // prompt user to write number
    printf("Write a number between 1 and 23: ");
    int pyramid = GetInt();
    // check if number is between 1 and 23
    if (pyramid < 0 || pyramid > 23)
    {
        do
        {
            printf("Height: ");
            pyramid = GetInt();
        }
        while (pyramid < 1 || pyramid > 23);
    }
    // prints the last hash and a new line
    for (int line = 0; pyramid > line; line++)
    {
    // space printer
        for (int space = 2 + line ; space <= pyramid; space++)
        {
            printf(" ");
        }
        for (int hash = pyramid - line; hash <= pyramid; hash++)
        {
            printf("#");        
        }
        printf("#\n");
    }       
}
