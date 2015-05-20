#include <stdlib.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>


void Decrypt(int key, string plain);

int main(int argc, string argv[])
{
    // check if the arguments are null
    if (argv[1] == NULL)
    {
        printf("imput a positive number as an argument.\n");
        return 1;
    }
    else
        /* if the argument is not null, convert to int, get a string
        from the user and then execute the Decrypt Function using
        they key int and the plain (for plaintext) string
        */
    {
        int key = atoi(argv[1]);
        string plain = GetString();
        Decrypt(key, plain);
    }
}
// Decryption function.
void Decrypt(int key, string plain)
{
    // check string length and intialize a position int
    int len = strlen(plain);
    int pos = 0;
    // for each character in the string
    do
    {
        // grab the character and cast it to an int
        int plainasc = plain[pos];
        // check if uppercase letter
        if (plainasc > 64 && plainasc <= 64 + 26)
        {
            // sum key to the letter and check if it's still an uppercase char
            // if it's not a uppercase char substract until it is.
            plainasc = plainasc + key;
            while (plainasc > 64 + 26)
            {
                plainasc = plainasc - 26;
            }
        }
        // check if lowercase letter.
        else if (plainasc > 96 && plainasc <= 96 + 26)
        {
        // sum key to the letter and check if it's still a lowercase char
        // if it's not a lowercase char substract until it is.
            plainasc = plainasc + key;
            while (plainasc > 96 + 26)
            {
                plainasc = plainasc - 26;
            }
        }
        // cast the plainasc int to a char and print, repeat for each character
        char cyph = plainasc;
        printf("%c",cyph);
        pos++;
    }
    // if the whole thing has finished running, print an addline character
    while(pos < len);
    printf("\n");
}
