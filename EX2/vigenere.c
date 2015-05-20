#include <stdlib.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>


void Decrypt(int lenkey, string key, string plain);

int main(int argc, string argv[])
{
    // check if the arguments are null if so return 1
    if (argv[1] == NULL)
    {
        printf("imput a word with characters from A to Z or a to Z as arg\n");
        return 1;
    }
    // check if argument 1 is all characters from a to z or A to Z
    // if any character is not such, return 1
    int lenkey = strlen(argv[1]) - 1;
    int kcheck = 0;
    string key = argv[1];
    do
    {
        if ( key[kcheck] > 64 && key[kcheck] <= 90)
        {
            kcheck++;  
        }
        else if( key[kcheck] > 96 && key[kcheck] <= 122)
        {
            kcheck++;
        }
        else
        {
            printf("imput a word with characters from A to Z or a to Z\n");    
            return 1;
        }
    }
    while(kcheck <= lenkey);
    // Get string from user and start the Decrypt function.
    string plain = GetString();
    Decrypt(lenkey, key, plain);
}
// Decryption function takes the key string
// key length and the plaintext string
void Decrypt(int lenkey, string key, string plain)
{
    // check plaintext length and initialize key position and
    // plaintext position variables.
    int plainlen = strlen(plain);
    int keypos = 0;
    int plainpos = 0;
    // for each character in the string
    do
    {
        // grab the character and cast it to an int
        int plainasc = plain[plainpos];
        // check if plaintext character uppercase letter
        if (plainasc > 64 && plainasc <= 64 + 26)
        {
            // cast character to ascci value
            int keyasc = key[keypos];
            // check if corresponding key character lower or uppercase
            if (keyasc > 64 && keyasc <= 64 + 26)
            {
                // if lowercase make it so that a = 0, b = 1 etc.
                keyasc = keyasc - 65;
            }
            else
            {
                // if uppercase do the same.
                keyasc = keyasc - 97;
            }
            // Encrypt the plaintext
            plainasc = plainasc + keyasc;
            // Check plaintext is a value from a to z or A to Z
            while (plainasc > 64 + 26)
            {
                plainasc = plainasc - 26;
            }
            // change key position, 
            // in case it's run the length, start from 0 again
            if (keypos == lenkey)
            {
                keypos = 0;
            }
            // otherwise, simply add one to the variable.
            else
            {
                keypos++;
            }
        }
        // check if lowercase letter.
        else if (plainasc > 96 && plainasc <= 96 + 26)
        {
        // This code is repeated, it could be fixed so that it's one function
        // but it works as is.
            int keyasc = key[keypos];
            if (keyasc > 64 && keyasc <= 64 + 26)
            {
                keyasc = keyasc - 65;
            }
            else
            {
                keyasc = keyasc - 97;
            }
            plainasc = plainasc + keyasc;
            while (plainasc > 96 + 26)
            {
                plainasc = plainasc - 26;
            }
            if (keypos == lenkey)
            {
                keypos = 0;
            }
            else
            {
                keypos++;
            }
            // up to here the code is the same as with the lowercase letters
            // this should be a separate function.
        }
        // cast the plainasc int to a char and print, repeat for each character
        char cyph = plainasc;
        printf("%c",cyph);
        plainpos++;
    }
    // if the whole string has finished running, print an addline character
    while(plainpos < plainlen);
    printf("\n");
}
