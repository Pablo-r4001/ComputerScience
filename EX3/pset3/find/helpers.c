/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // check if value of n is negative
    if (n < 0)
    {
        return false;
    }
    else
    // do a binary search
    {
        // set min to 0 and max to the length of the values
        int min = 0;
        int max = n;
        int mid = (max - min) / 2;
        // see if by coincidence these values contain the character.
        if ( value == values[min] || values[max])
        {
            return 1;
        }
        // repeat while diff between min and max greater than 1
        while((max - min) > 1)
        {
            // average the min and max and sum min
            mid = ((max - min) / 2) + min;
            // if any of the values is the value we search return 1
            if (value == values[mid])
            {
                // return 1
                return 1;
            }
            // if value is smaller than the mid set max to mid
            else if(value < values[mid])
            {
                max = mid;
            }
            // if value is larger than the mid set min to mid
            else
            {
                min = mid;
            }
        }
        // if we went through all the items, return 0
        return 0;
    }
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    for(int iter = 0; iter < (n - 1); iter++)
    {
        for(int komp = 0; komp < (n - iter - 1); komp++)
        {
            int rValue = values[komp + 1];
            if (rValue < values[komp])
            {
                values[komp + 1] = values[komp];
                values[komp] = rValue;
            }
        }
    }
   
    return;
}
