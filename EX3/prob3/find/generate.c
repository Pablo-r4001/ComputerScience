/***************************************************************************
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 ***************************************************************************/
 
// standard libraries
#define _XOPEN_SOURCE
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constant
#define LIMIT 65536

int main(int argc, string argv[])
{
    // if there's not 2 or 3 aguments (incluiding the program's name)
    // print instructions and get out by returning 1.
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    // 2nd argument becomes int n
    int n = atoi(argv[1]);

    // if there's three arguments initialize the pseudorandom generator 
    // using the third argument as the key. else use a NULL value as key.
    if (argc == 3)
    {
        srand48((long int) atoi(argv[2]));
    }
    else
    {
        srand48((long int) time(NULL));
    }

    // For all values from 0 to n (argv[1])
    // generate a pseudorandom float from 0.0 to 1.0
    // multiply by the limit constant, cast as an integer and print
    // with a changeline at the end.
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
